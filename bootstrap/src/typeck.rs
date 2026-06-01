//! Minimal type checker (stage0).
//!
//! Bidirectional: an *expected* type is pushed down so polymorphic numeric
//! literals are resolved from context. A numeric literal with no expected
//! numeric type is an error — Plew has **no default numeric type** (spec/02).
//!
//! Supports: numeric/Bool primitives, arithmetic/comparison, `if`/`while`,
//! bindings, calls, the `print` builtin, **structs** (construction, field
//! access), and **enums + `match`** (variant construction, pattern matching,
//! exhaustiveness). Strings, arrays, generics, traits come later.

use std::collections::{HashMap, HashSet};

use crate::ast::{
    Ast, BinOp, Block, ExprId, ExprKind, ItemKind, MatchArm, PatId, PatKind, StmtKind, Type, UnOp,
};
use crate::span::Span;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Ty {
    I8,
    I16,
    I32,
    I64,
    U8,
    U16,
    U32,
    U64,
    F32,
    F64,
    Bool,
    /// Immutable UTF-8 string (stage0: literal-backed, no heap/ARC yet).
    String,
    Unit,
    Struct(u32),
    Enum(u32),
    /// `Array[T]`; the u32 indexes [`TypeTable::array_elems`] for the element.
    Array(u32),
    /// A type error already reported; suppresses cascades.
    Error,
}

impl Ty {
    fn is_integer(self) -> bool {
        use Ty::*;
        matches!(self, I8 | I16 | I32 | I64 | U8 | U16 | U32 | U64)
    }
    fn is_float(self) -> bool {
        matches!(self, Ty::F32 | Ty::F64)
    }
    fn is_numeric(self) -> bool {
        self.is_integer() || self.is_float()
    }
    fn is_signed(self) -> bool {
        use Ty::*;
        matches!(self, I8 | I16 | I32 | I64 | F32 | F64)
    }
    fn prim_name(self) -> &'static str {
        use Ty::*;
        match self {
            I8 => "I8",
            I16 => "I16",
            I32 => "I32",
            I64 => "I64",
            U8 => "U8",
            U16 => "U16",
            U32 => "U32",
            U64 => "U64",
            F32 => "F32",
            F64 => "F64",
            Bool => "Bool",
            String => "String",
            Unit => "()",
            Struct(_) => "<struct>",
            Enum(_) => "<enum>",
            Array(_) => "<array>",
            Error => "<error>",
        }
    }
}

/// Type information shared with codegen: id → name for nominal types, and the
/// element type of every interned `Array[T]`. Built by the type checker so
/// codegen can spell a [`Ty`] as a C type (and emit one monomorphized array
/// runtime per element type).
#[derive(Default)]
pub struct TypeTable {
    pub struct_names: Vec<String>,
    pub enum_names: Vec<String>,
    /// `Array[T]` element types, indexed by the `Ty::Array(id)` id.
    pub array_elems: Vec<Ty>,
}

impl TypeTable {
    /// Intern `Array[elem]`, returning its array-type id (deduplicated).
    fn intern_array(&mut self, elem: Ty) -> u32 {
        if let Some(i) = self.array_elems.iter().position(|&e| e == elem) {
            return i as u32;
        }
        let i = self.array_elems.len() as u32;
        self.array_elems.push(elem);
        i
    }

    /// Element type of an `Array` type id.
    pub fn array_elem(&self, id: u32) -> Ty {
        self.array_elems[id as usize]
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TypeError {
    pub span: Span,
    pub msg: String,
}

/// Result of type-checking: errors plus the inferred type of every expression
/// (indexed by `ExprId.0`), which codegen consults (e.g. to pick a `print`
/// format). Expressions that were never reached stay `Ty::Error`.
pub struct CheckResult {
    pub errors: Vec<TypeError>,
    pub expr_ty: Vec<Ty>,
    pub table: TypeTable,
}

struct FnSig {
    params: Vec<Ty>,
    ret: Ty,
}

struct StructDef {
    name: String,
    fields: Vec<(String, Ty)>,
}

struct VariantDef {
    name: String,
    fields: Vec<(String, Ty)>,
}

struct EnumDef {
    name: String,
    variants: Vec<VariantDef>,
}

/// Name → id maps for nominal types.
#[derive(Default)]
struct Types {
    structs: HashMap<String, u32>,
    enums: HashMap<String, u32>,
}

/// Type-check a whole program.
pub fn check(ast: &Ast, items: &[crate::ast::ItemId]) -> CheckResult {
    let mut errors = Vec::new();
    let mut expr_ty = vec![Ty::Error; ast.expr_count()];

    // Pass 0a: assign ids to all struct/enum names (forward references ok).
    let mut types = Types::default();
    let mut struct_names: Vec<String> = Vec::new();
    let mut enum_names: Vec<String> = Vec::new();
    for &id in items {
        match &ast.item(id).kind {
            ItemKind::Struct { name, .. } => {
                if !types.structs.contains_key(name) {
                    types.structs.insert(name.clone(), struct_names.len() as u32);
                    struct_names.push(name.clone());
                }
            }
            ItemKind::Enum { name, .. } => {
                if !types.enums.contains_key(name) {
                    types.enums.insert(name.clone(), enum_names.len() as u32);
                    enum_names.push(name.clone());
                }
            }
            ItemKind::Fn { .. } => {}
        }
    }

    // The type table shared with codegen: nominal names plus interned arrays.
    let mut table = TypeTable {
        struct_names: struct_names.clone(),
        enum_names: enum_names.clone(),
        array_elems: Vec::new(),
    };

    // Pass 0b: resolve field types of structs and enum variants.
    let mut structs: Vec<StructDef> = struct_names
        .iter()
        .map(|n| StructDef { name: n.clone(), fields: Vec::new() })
        .collect();
    let mut enums: Vec<EnumDef> = enum_names
        .iter()
        .map(|n| EnumDef { name: n.clone(), variants: Vec::new() })
        .collect();
    for &id in items {
        match &ast.item(id).kind {
            ItemKind::Struct { name, fields, generics } => {
                if !generics.is_empty() {
                    errors.push(TypeError {
                        span: ast.item(id).span,
                        msg: "generic structs are not supported by the stage0 type checker yet".into(),
                    });
                }
                let sid = types.structs[name] as usize;
                structs[sid].fields = fields
                    .iter()
                    .map(|f| (f.name.clone(), resolve_ty(&f.ty, &types, &mut table, &mut errors)))
                    .collect();
            }
            ItemKind::Enum { name, variants, generics } => {
                if !generics.is_empty() {
                    errors.push(TypeError {
                        span: ast.item(id).span,
                        msg: "generic enums are not supported by the stage0 type checker yet".into(),
                    });
                }
                let eid = types.enums[name] as usize;
                enums[eid].variants = variants
                    .iter()
                    .map(|v| VariantDef {
                        name: v.name.clone(),
                        fields: v
                            .fields
                            .iter()
                            .map(|f| (f.name.clone(), resolve_ty(&f.ty, &types, &mut table, &mut errors)))
                            .collect(),
                    })
                    .collect();
            }
            ItemKind::Fn { .. } => {}
        }
    }

    // Pass 1: collect function signatures.
    let mut sigs: HashMap<String, FnSig> = HashMap::new();
    for &id in items {
        if let ItemKind::Fn { name, params, ret, .. } = &ast.item(id).kind {
            let param_tys =
                params.iter().map(|p| resolve_ty(&p.ty, &types, &mut table, &mut errors)).collect();
            let ret_ty = match ret {
                Some(t) => resolve_ty(t, &types, &mut table, &mut errors),
                None => Ty::Unit,
            };
            sigs.insert(name.clone(), FnSig { params: param_tys, ret: ret_ty });
        }
    }

    // Pass 2: check each function body.
    for &id in items {
        if let ItemKind::Fn { name, params, body, .. } = &ast.item(id).kind {
            let ret = sigs.get(name).map(|s| s.ret).unwrap_or(Ty::Error);
            let mut cx = Checker {
                ast,
                sigs: &sigs,
                structs: &structs,
                enums: &enums,
                types: &types,
                table: &mut table,
                errors: &mut errors,
                expr_ty: &mut expr_ty,
                scopes: Vec::new(),
                ret,
            };
            cx.push_scope();
            for p in params {
                let ty = resolve_ty(&p.ty, cx.types, cx.table, cx.errors);
                cx.define(&p.label, ty);
            }
            cx.check_block(body);
            cx.pop_scope();
        }
    }

    CheckResult { errors, expr_ty, table }
}

/// Resolve a syntactic type to a [`Ty`]. `Array[T]` interns its element type
/// into `table`; other type arguments are an error (stage0 has no generics).
fn resolve_ty(t: &Type, types: &Types, table: &mut TypeTable, errors: &mut Vec<TypeError>) -> Ty {
    // `Array[T]` is the only stage0 type constructor.
    if t.name == "Array" {
        if t.args.len() != 1 {
            errors.push(TypeError {
                span: t.span,
                msg: "`Array` takes exactly one type argument (e.g. `Array[I32]`)".into(),
            });
            return Ty::Error;
        }
        let elem = resolve_ty(&t.args[0], types, table, errors);
        if elem == Ty::Error {
            return Ty::Error;
        }
        return Ty::Array(table.intern_array(elem));
    }

    let ty = match t.name.as_str() {
        "I8" => Ty::I8,
        "I16" => Ty::I16,
        "I32" => Ty::I32,
        "I64" => Ty::I64,
        "U8" => Ty::U8,
        "U16" => Ty::U16,
        "U32" => Ty::U32,
        "U64" => Ty::U64,
        "F32" => Ty::F32,
        "F64" => Ty::F64,
        "Bool" => Ty::Bool,
        "String" => Ty::String,
        other => {
            if let Some(&id) = types.structs.get(other) {
                Ty::Struct(id)
            } else if let Some(&id) = types.enums.get(other) {
                Ty::Enum(id)
            } else {
                errors.push(TypeError {
                    span: t.span,
                    msg: format!("unknown type `{other}` (stage0 supports primitives, Bool, declared struct/enum types, and `Array[T]`)"),
                });
                Ty::Error
            }
        }
    };
    if !t.args.is_empty() && ty != Ty::Error {
        errors.push(TypeError {
            span: t.span,
            msg: format!("type `{}` does not take type arguments (stage0)", t.name),
        });
    }
    ty
}

struct Checker<'a> {
    ast: &'a Ast,
    sigs: &'a HashMap<String, FnSig>,
    structs: &'a [StructDef],
    enums: &'a [EnumDef],
    types: &'a Types,
    table: &'a mut TypeTable,
    errors: &'a mut Vec<TypeError>,
    expr_ty: &'a mut Vec<Ty>,
    scopes: Vec<HashMap<String, Ty>>,
    ret: Ty,
}

impl Checker<'_> {
    fn push_scope(&mut self) {
        self.scopes.push(HashMap::new());
    }
    fn pop_scope(&mut self) {
        self.scopes.pop();
    }
    fn define(&mut self, name: &str, ty: Ty) {
        self.scopes.last_mut().unwrap().insert(name.to_string(), ty);
    }
    fn lookup(&self, name: &str) -> Option<Ty> {
        self.scopes.iter().rev().find_map(|s| s.get(name).copied())
    }
    fn error(&mut self, span: Span, msg: impl Into<String>) {
        self.errors.push(TypeError { span, msg: msg.into() });
    }
    fn ty_name(&self, t: Ty) -> String {
        match t {
            Ty::Struct(id) => self.structs[id as usize].name.clone(),
            Ty::Enum(id) => self.enums[id as usize].name.clone(),
            Ty::Array(id) => format!("Array[{}]", self.ty_name(self.table.array_elem(id))),
            other => other.prim_name().to_string(),
        }
    }

    fn check_block(&mut self, block: &Block) {
        self.push_scope();
        for &sid in &block.stmts {
            self.check_stmt(sid);
        }
        self.pop_scope();
    }

    /// Check a block used as a value: its type is the type of its `give`
    /// expression (checked against `expected`), or `()` if there is none.
    fn check_block_value(&mut self, block: &Block, expected: Option<Ty>) -> Ty {
        self.push_scope();
        let mut val = Ty::Unit;
        for &sid in &block.stmts {
            if let StmtKind::Give(e) = &self.ast.stmt(sid).kind {
                let e = *e;
                val = self.check_expr(e, expected);
            } else {
                self.check_stmt(sid);
            }
        }
        self.pop_scope();
        val
    }

    fn check_stmt(&mut self, sid: crate::ast::StmtId) {
        let span = self.ast.stmt(sid).span;
        match &self.ast.stmt(sid).kind {
            StmtKind::Let { name, ty, value, .. } => {
                let name = name.clone();
                let value = *value;
                let expected = match ty {
                    Some(t) => Some(resolve_ty(t, self.types, self.table, self.errors)),
                    None => None,
                };
                let vty = self.check_expr(value, expected);
                self.define(&name, expected.unwrap_or(vty));
            }
            StmtKind::Return(value) => {
                let value = *value;
                match value {
                    Some(e) => {
                        let ret = self.ret;
                        self.check_expr(e, Some(ret));
                    }
                    None => {
                        if self.ret != Ty::Unit && self.ret != Ty::Error {
                            let rn = self.ty_name(self.ret);
                            self.error(span, format!("`return` with no value, but the function returns `{rn}`"));
                        }
                    }
                }
            }
            StmtKind::Give(e) => {
                let e = *e;
                self.check_expr(e, None);
            }
            StmtKind::Assign { target, op, value } => {
                let (target, op, value) = (*target, *op, *value);
                let tty = self.check_expr(target, None);
                if op.is_some() && !tty.is_numeric() && tty != Ty::Error {
                    let tn = self.ty_name(tty);
                    self.error(span, format!("compound assignment requires a numeric type, found `{tn}`"));
                }
                let vty = self.check_expr(value, Some(tty));
                if tty != Ty::Error && vty != Ty::Error && tty != vty {
                    let (tn, vn) = (self.ty_name(tty), self.ty_name(vty));
                    self.error(span, format!("cannot assign `{vn}` to `{tn}`"));
                }
            }
            // stage0 does not yet verify these appear inside a loop.
            StmtKind::Break | StmtKind::Continue => {}
            StmtKind::Expr(e) => {
                let e = *e;
                self.check_expr(e, None);
            }
        }
    }

    /// Synthesize a type then verify it against `expected`.
    fn check_expr(&mut self, id: ExprId, expected: Option<Ty>) -> Ty {
        let span = self.ast.expr(id).span;
        let t = self.infer_expr(id, expected);
        self.expect_eq(t, expected, span);
        self.expr_ty[id.0 as usize] = t;
        t
    }

    fn infer_expr(&mut self, id: ExprId, expected: Option<Ty>) -> Ty {
        let span = self.ast.expr(id).span;
        match &self.ast.expr(id).kind {
            ExprKind::Int(_) => match expected {
                Some(t) if t.is_integer() => t,
                Some(t) if t.is_float() => {
                    self.error(span, format!("expected `{}`, found an integer literal (use a decimal point for floats)", self.ty_name(t)));
                    Ty::Error
                }
                Some(t) => {
                    let tn = self.ty_name(t);
                    self.error(span, format!("expected `{tn}`, found an integer literal"));
                    Ty::Error
                }
                None => {
                    self.error(span, "ambiguous numeric literal: no type can be inferred here (add a type annotation; Plew has no default numeric type)");
                    Ty::Error
                }
            },
            ExprKind::Float(_) => match expected {
                Some(t) if t.is_float() => t,
                Some(t) => {
                    let tn = self.ty_name(t);
                    self.error(span, format!("expected `{tn}`, found a float literal"));
                    Ty::Error
                }
                None => {
                    self.error(span, "ambiguous float literal: no type can be inferred here (add a type annotation)");
                    Ty::Error
                }
            },
            ExprKind::Str(_) => Ty::String,
            ExprKind::Bool(_) => Ty::Bool,
            ExprKind::Ident(name) => {
                let name = name.clone();
                match self.lookup(&name) {
                    Some(t) => t,
                    None => {
                        self.error(span, format!("unbound name `{name}`"));
                        Ty::Error
                    }
                }
            }
            ExprKind::Unary { op, operand } => {
                let (op, operand) = (*op, *operand);
                match op {
                    UnOp::Not => {
                        self.check_expr(operand, Some(Ty::Bool));
                        Ty::Bool
                    }
                    UnOp::Neg => {
                        let t = self.check_expr(operand, expected);
                        if t != Ty::Error && !t.is_signed() {
                            let tn = self.ty_name(t);
                            self.error(span, format!("unary `-` requires a signed numeric type, found `{tn}`"));
                        }
                        t
                    }
                    UnOp::BitNot => {
                        let t = self.check_expr(operand, expected);
                        if t != Ty::Error && !t.is_integer() {
                            let tn = self.ty_name(t);
                            self.error(span, format!("`~` requires an integer type, found `{tn}`"));
                        }
                        t
                    }
                }
            }
            ExprKind::Binary { op, lhs, rhs } => {
                let (op, lhs, rhs) = (*op, *lhs, *rhs);
                self.check_binary(op, lhs, rhs, expected, span)
            }
            ExprKind::Array(elems) => {
                let elems = elems.clone();
                self.check_array(&elems, expected, span)
            }
            ExprKind::Call { callee, args } => {
                let callee = *callee;
                let args: Vec<_> = args.iter().map(|a| a.value).collect();
                self.check_call(callee, &args, span)
            }
            ExprKind::If { cond, then_branch, else_branch } => {
                let (cond, then_branch, else_branch) = (*cond, *then_branch, *else_branch);
                self.check_expr(cond, Some(Ty::Bool));
                let want = match expected {
                    Some(t) if t != Ty::Unit => Some(t),
                    _ => None,
                };
                let tty = self.check_expr(then_branch, want);
                match else_branch {
                    Some(e) => {
                        let ety = self.check_expr(e, want.or(Some(tty)));
                        if let Some(w) = want {
                            w
                        } else if tty == ety {
                            tty
                        } else {
                            Ty::Unit
                        }
                    }
                    None => {
                        if want.is_some() {
                            self.error(span, "`if` used as a value must have an `else` branch");
                        }
                        Ty::Unit
                    }
                }
            }
            ExprKind::While { cond, body } => {
                let (cond, body) = (*cond, *body);
                self.check_expr(cond, Some(Ty::Bool));
                self.check_expr(body, None);
                Ty::Unit
            }
            ExprKind::For { var, iter, body, .. } => {
                let var = var.clone();
                let (iter, body) = (*iter, *body);
                let elem = self.check_iter(iter);
                self.push_scope();
                self.define(&var, elem);
                self.check_expr(body, None);
                self.pop_scope();
                Ty::Unit
            }
            ExprKind::Block(block) => {
                let block = block.clone();
                self.check_block_value(&block, expected)
            }
            ExprKind::New { path, fields } => {
                let path = path.clone();
                let fields: Vec<(String, ExprId)> = fields.iter().map(|(n, v)| (n.clone(), *v)).collect();
                self.check_new(&path, &fields, span)
            }
            ExprKind::Field { base, name } => {
                let (base, name) = (*base, name.clone());
                let bt = self.check_expr(base, None);
                match bt {
                    Ty::Struct(id) => {
                        let def = &self.structs[id as usize];
                        match def.fields.iter().find(|(n, _)| *n == name) {
                            Some((_, fty)) => *fty,
                            None => {
                                let dn = def.name.clone();
                                self.error(span, format!("`{dn}` has no field `{name}`"));
                                Ty::Error
                            }
                        }
                    }
                    // `s.bytes` is the UTF-8 byte view (spec: `Array[U8]`, O(1)).
                    Ty::String if name == "bytes" => Ty::Array(self.table.intern_array(Ty::U8)),
                    Ty::String => {
                        self.error(span, format!("`String` has no member `{name}` (stage0 supports `bytes`)"));
                        Ty::Error
                    }
                    // `arr.count` is the element count (spec: `U64`).
                    Ty::Array(_) if name == "count" => Ty::U64,
                    Ty::Array(_) => {
                        self.error(span, format!("`Array` has no member `{name}` (stage0 supports `count`)"));
                        Ty::Error
                    }
                    Ty::Error => Ty::Error,
                    other => {
                        let on = self.ty_name(other);
                        self.error(span, format!("type `{on}` has no fields"));
                        Ty::Error
                    }
                }
            }
            ExprKind::Index { base, index } => {
                let (base, index) = (*base, *index);
                let bt = self.check_expr(base, None);
                match bt {
                    Ty::Array(id) => {
                        // Index is `U64` (spec); the result is the element type.
                        self.check_expr(index, Some(Ty::U64));
                        self.table.array_elem(id)
                    }
                    Ty::Error => {
                        self.check_expr(index, None);
                        Ty::Error
                    }
                    other => {
                        let on = self.ty_name(other);
                        self.error(span, format!("type `{on}` cannot be indexed"));
                        self.check_expr(index, None);
                        Ty::Error
                    }
                }
            }
            ExprKind::Match { scrutinee, arms } => {
                let scrutinee = *scrutinee;
                let arms = arms.clone();
                self.check_match(scrutinee, &arms, expected, span)
            }
            ExprKind::Error => Ty::Error,
        }
    }

    fn check_new(&mut self, path: &[String], fields: &[(String, ExprId)], span: Span) -> Ty {
        match path.len() {
            1 => {
                let sname = &path[0];
                let Some(&sid) = self.types.structs.get(sname) else {
                    self.error(span, format!("`{sname}` is not a declared struct"));
                    for (_, v) in fields {
                        self.check_expr(*v, None);
                    }
                    return Ty::Error;
                };
                let def_fields = self.structs[sid as usize].fields.clone();
                self.check_record_fields(sname, &def_fields, fields, span);
                Ty::Struct(sid)
            }
            2 => {
                let ename = &path[0];
                let vname = &path[1];
                let Some(&eid) = self.types.enums.get(ename) else {
                    self.error(span, format!("`{ename}` is not a declared enum"));
                    for (_, v) in fields {
                        self.check_expr(*v, None);
                    }
                    return Ty::Error;
                };
                let def_fields = match self.enums[eid as usize].variants.iter().find(|v| &v.name == vname) {
                    Some(v) => v.fields.clone(),
                    None => {
                        self.error(span, format!("`{ename}` has no variant `{vname}`"));
                        for (_, v) in fields {
                            self.check_expr(*v, None);
                        }
                        return Ty::Error;
                    }
                };
                self.check_record_fields(&format!("{ename}.{vname}"), &def_fields, fields, span);
                Ty::Enum(eid)
            }
            _ => {
                self.error(span, "construction path is too deep (stage0)");
                Ty::Error
            }
        }
    }

    /// Check that provided fields exactly match the declared fields (types and
    /// completeness). Shared by struct and enum-variant construction.
    fn check_record_fields(
        &mut self,
        what: &str,
        def_fields: &[(String, Ty)],
        provided: &[(String, ExprId)],
        span: Span,
    ) {
        let mut seen: HashSet<&str> = HashSet::new();
        for (fname, fval) in provided {
            match def_fields.iter().find(|(n, _)| n == fname) {
                Some((_, fty)) => {
                    self.check_expr(*fval, Some(*fty));
                    seen.insert(fname.as_str());
                }
                None => self.error(span, format!("`{what}` has no field `{fname}`")),
            }
        }
        for (n, _) in def_fields {
            if !seen.contains(n.as_str()) {
                self.error(span, format!("missing field `{n}` in construction of `{what}`"));
            }
        }
    }

    fn check_match(&mut self, scrutinee: ExprId, arms: &[MatchArm], expected: Option<Ty>, span: Span) -> Ty {
        let sty = self.check_expr(scrutinee, None);
        let want = match expected {
            Some(t) if t != Ty::Unit => Some(t),
            _ => None,
        };

        let mut covered_variants: HashSet<String> = HashSet::new();
        let mut has_catchall = false;
        let mut covered_bools: HashSet<bool> = HashSet::new();
        let mut arm_tys: Vec<Ty> = Vec::new();

        for arm in arms {
            // record coverage from the (outermost) pattern
            match &self.ast.pat(arm.pat).kind {
                PatKind::Wildcard | PatKind::Binding { .. } => has_catchall = true,
                PatKind::Variant { path, .. } => {
                    let vname = path.last().cloned().unwrap_or_default();
                    covered_variants.insert(vname);
                }
                PatKind::Bool(b) => {
                    covered_bools.insert(*b);
                }
                PatKind::Int(_) | PatKind::Str(_) => {}
            }

            self.push_scope();
            self.check_pattern(arm.pat, sty);
            let bty = self.check_expr(arm.body, want);
            self.pop_scope();
            arm_tys.push(bty);
        }

        // exhaustiveness
        if !has_catchall {
            match sty {
                Ty::Enum(id) => {
                    let missing: Vec<String> = self.enums[id as usize]
                        .variants
                        .iter()
                        .filter(|v| !covered_variants.contains(&v.name))
                        .map(|v| v.name.clone())
                        .collect();
                    if !missing.is_empty() {
                        let en = self.enums[id as usize].name.clone();
                        self.error(span, format!("non-exhaustive match on `{en}`: missing {}", missing.join(", ")));
                    }
                }
                Ty::Bool => {
                    if covered_bools.len() < 2 {
                        self.error(span, "non-exhaustive match on `Bool`: cover both `true` and `false` (or use `_`)");
                    }
                }
                Ty::Error => {}
                _ => {
                    self.error(span, "non-exhaustive match: this type needs a `_` or binding arm");
                }
            }
        }

        // result type
        if let Some(w) = want {
            w
        } else if !arm_tys.is_empty() && arm_tys.iter().all(|&t| t == arm_tys[0]) {
            arm_tys[0]
        } else {
            Ty::Unit
        }
    }

    /// Check a pattern against the scrutinee type and bind its variables in the
    /// current scope.
    fn check_pattern(&mut self, pat: PatId, expected: Ty) {
        let span = self.ast.pat(pat).span;
        match &self.ast.pat(pat).kind {
            PatKind::Wildcard => {}
            PatKind::Binding { name, .. } => {
                let name = name.clone();
                self.define(&name, expected);
            }
            PatKind::Int(_) => {
                if expected != Ty::Error && !expected.is_integer() {
                    let en = self.ty_name(expected);
                    self.error(span, format!("integer pattern cannot match `{en}`"));
                }
            }
            PatKind::Bool(_) => {
                if expected != Ty::Error && expected != Ty::Bool {
                    let en = self.ty_name(expected);
                    self.error(span, format!("`Bool` pattern cannot match `{en}`"));
                }
            }
            PatKind::Str(_) => {
                self.error(span, "string patterns are not supported by the stage0 type checker yet");
            }
            PatKind::Variant { path, fields } => {
                let path = path.clone();
                let fields: Vec<(String, PatId)> = fields.iter().map(|(n, p)| (n.clone(), *p)).collect();
                self.check_variant_pattern(&path, &fields, expected, span);
            }
        }
    }

    fn check_variant_pattern(&mut self, path: &[String], fields: &[(String, PatId)], expected: Ty, span: Span) {
        let Ty::Enum(eid) = expected else {
            if expected != Ty::Error {
                let en = self.ty_name(expected);
                self.error(span, format!("variant pattern cannot match `{en}`"));
            }
            return;
        };
        // the variant name is the last path component
        let vname = match path.last() {
            Some(v) => v.clone(),
            None => return,
        };
        // optional leading enum name must match
        if path.len() == 2 {
            let en = self.enums[eid as usize].name.clone();
            if path[0] != en {
                self.error(span, format!("pattern names enum `{}`, but the value is `{en}`", path[0]));
            }
        }
        let vfields = match self.enums[eid as usize].variants.iter().find(|v| v.name == vname) {
            Some(v) => v.fields.clone(),
            None => {
                let en = self.enums[eid as usize].name.clone();
                self.error(span, format!("`{en}` has no variant `{vname}`"));
                return;
            }
        };
        let mut seen: HashSet<&str> = HashSet::new();
        for (fname, fpat) in fields {
            match vfields.iter().find(|(n, _)| n == fname) {
                Some((_, fty)) => {
                    self.check_pattern(*fpat, *fty);
                    seen.insert(fname.as_str());
                }
                None => self.error(span, format!("variant `{vname}` has no field `{fname}`")),
            }
        }
        for (n, _) in &vfields {
            if !seen.contains(n.as_str()) {
                self.error(span, format!("pattern for `{vname}` is missing field `{n}` (Plew has no `..`)"));
            }
        }
    }

    /// Check an array literal `[e0, e1, ...]`. The element type comes from the
    /// expected `Array[E]` if present, else from the first element; all
    /// elements must share it. An empty literal needs an expected type.
    fn check_array(&mut self, elems: &[ExprId], expected: Option<Ty>, span: Span) -> Ty {
        let expected_elem = match expected {
            Some(Ty::Array(id)) => Some(self.table.array_elem(id)),
            _ => None,
        };
        if elems.is_empty() {
            return match expected_elem {
                Some(e) => Ty::Array(self.table.intern_array(e)),
                None => {
                    self.error(span, "empty array literal needs a type annotation (e.g. `val xs: Array[I32] = []`)");
                    Ty::Error
                }
            };
        }
        // First element establishes the type (unless one is expected).
        let first = self.check_expr(elems[0], expected_elem);
        let elem = expected_elem.unwrap_or(first);
        for &e in &elems[1..] {
            let et = self.check_expr(e, Some(elem));
            if elem != Ty::Error && et != Ty::Error && et != elem {
                let (en, etn) = (self.ty_name(elem), self.ty_name(et));
                let s = self.ast.expr(e).span;
                self.error(s, format!("array elements must share a type: expected `{en}`, found `{etn}`"));
            }
        }
        if elem == Ty::Error {
            return Ty::Error;
        }
        Ty::Array(self.table.intern_array(elem))
    }

    /// Check a `for` iterator and return the loop-variable (element) type.
    /// stage0 supports integer ranges (`a..<b` / `a..=b`) and arrays.
    fn check_iter(&mut self, iter: ExprId) -> Ty {
        let span = self.ast.expr(iter).span;
        let range = if let ExprKind::Binary { op, lhs, rhs } = &self.ast.expr(iter).kind {
            if matches!(op, BinOp::RangeHalf | BinOp::RangeClosed) {
                Some((*lhs, *rhs))
            } else {
                None
            }
        } else {
            None
        };
        let Some((lhs, rhs)) = range else {
            // Non-range: an array iterates its elements.
            let it = self.check_expr(iter, None);
            return match it {
                Ty::Array(id) => self.table.array_elem(id),
                Ty::Error => Ty::Error,
                other => {
                    let on = self.ty_name(other);
                    self.error(span, format!("`for` cannot iterate `{on}` (stage0: a range `a..<b` or an array)"));
                    Ty::Error
                }
            };
        };
        let lhs_lit = matches!(self.ast.expr(lhs).kind, ExprKind::Int(_) | ExprKind::Float(_));
        let elem = if lhs_lit {
            let rt = self.check_expr(rhs, None);
            let exp = if rt.is_integer() { Some(rt) } else { None };
            self.check_expr(lhs, exp)
        } else {
            let lt = self.check_expr(lhs, None);
            let exp = if lt.is_integer() { Some(lt) } else { None };
            self.check_expr(rhs, exp);
            lt
        };
        if elem != Ty::Error && !elem.is_integer() {
            let en = self.ty_name(elem);
            self.error(span, format!("range bounds must be integers, found `{en}`"));
            return Ty::Error;
        }
        elem
    }

    fn check_binary(&mut self, op: BinOp, lhs: ExprId, rhs: ExprId, expected: Option<Ty>, span: Span) -> Ty {
        use BinOp::*;
        match op {
            Add | Sub | Mul | Div | Rem | BitAnd | BitXor | BitOr | Shl | Shr => {
                let lt = self.check_expr(lhs, expected);
                let rexp = if lt.is_numeric() { Some(lt) } else { expected };
                let rt = self.check_expr(rhs, rexp);
                if lt == Ty::Error || rt == Ty::Error {
                    return if lt != Ty::Error { lt } else { rt };
                }
                if !lt.is_numeric() {
                    let ln = self.ty_name(lt);
                    self.error(span, format!("operator `{}` requires numeric operands, found `{ln}`", op.symbol()));
                    return Ty::Error;
                }
                if lt != rt {
                    let (ln, rn) = (self.ty_name(lt), self.ty_name(rt));
                    self.error(span, format!("operator `{}` operand types differ: `{ln}` vs `{rn}`", op.symbol()));
                    return Ty::Error;
                }
                lt
            }
            Eq | Ne | Lt | Gt | Le | Ge => {
                let lt = self.check_expr(lhs, None);
                let rt = self.check_expr(rhs, Some(lt));
                if lt != Ty::Error && rt != Ty::Error && lt != rt {
                    let (ln, rn) = (self.ty_name(lt), self.ty_name(rt));
                    self.error(span, format!("comparison operand types differ: `{ln}` vs `{rn}`"));
                }
                Ty::Bool
            }
            And | Or => {
                self.check_expr(lhs, Some(Ty::Bool));
                self.check_expr(rhs, Some(Ty::Bool));
                Ty::Bool
            }
            Coalesce | RangeHalf | RangeClosed => {
                self.error(span, format!("operator `{}` is not supported by the stage0 type checker yet", op.symbol()));
                Ty::Error
            }
        }
    }

    fn check_call(&mut self, callee: ExprId, args: &[ExprId], span: Span) -> Ty {
        // Method call `base.method(args)`.
        if let ExprKind::Field { base, name } = &self.ast.expr(callee).kind {
            let (base, name) = (*base, name.clone());
            let bt = self.check_expr(base, None);
            return self.check_method(bt, &name, args, span);
        }
        if let ExprKind::Ident(name) = &self.ast.expr(callee).kind {
            let name = name.clone();
            if name == "print" {
                // stage0 builtin: accepts any number or a String (real signature:
                // `print[T](~value: T) where T: Format`; import-required). The
                // argument's natural type is used; an otherwise-ambiguous numeric
                // literal falls back to I64 (a stage0 convenience).
                if args.len() != 1 {
                    self.error(span, "`print` takes exactly one argument (stage0)");
                    return Ty::Unit;
                }
                let before = self.errors.len();
                let mut t = self.check_expr(args[0], None);
                if t == Ty::Error && self.errors.len() > before {
                    // Likely an ambiguous literal: discard those errors and retry
                    // with an I64 expectation. A genuine error reappears.
                    self.errors.truncate(before);
                    t = self.check_expr(args[0], Some(Ty::I64));
                }
                if t != Ty::Error && !t.is_numeric() && t != Ty::String {
                    let tn = self.ty_name(t);
                    self.error(span, format!("`print` expects a number or String (stage0), found `{tn}`"));
                }
                return Ty::Unit;
            }
            if let Some(sig) = self.sigs.get(&name) {
                let params = sig.params.clone();
                let ret = sig.ret;
                if args.len() != params.len() {
                    self.error(span, format!("`{name}` expects {} argument(s), found {}", params.len(), args.len()));
                }
                for (i, value) in args.iter().enumerate() {
                    let exp = params.get(i).copied();
                    self.check_expr(*value, exp);
                }
                return ret;
            }
            self.error(span, format!("call to unknown function `{name}`"));
            return Ty::Error;
        }
        self.error(span, "only simple function calls are supported by the stage0 type checker yet");
        Ty::Error
    }

    /// Check a method call on `recv`. stage0 supports a small set of builtin
    /// `Array` methods (the real Array API is core-lib, TBD); like `print`,
    /// these are stage0 fictions until the module/trait machinery exists.
    fn check_method(&mut self, recv: Ty, name: &str, args: &[ExprId], span: Span) -> Ty {
        match recv {
            Ty::Array(id) => {
                let elem = self.table.array_elem(id);
                match name {
                    // `append(value)`: push an element (mutates in place).
                    "append" => {
                        if args.len() != 1 {
                            self.error(span, "`append` takes exactly one argument");
                        } else {
                            self.check_expr(args[0], Some(elem));
                        }
                        Ty::Unit
                    }
                    other => {
                        for &a in args {
                            self.check_expr(a, None);
                        }
                        self.error(span, format!("`Array` has no method `{other}` (stage0 supports `append`)"));
                        Ty::Error
                    }
                }
            }
            Ty::Error => {
                for &a in args {
                    self.check_expr(a, None);
                }
                Ty::Error
            }
            other => {
                for &a in args {
                    self.check_expr(a, None);
                }
                let on = self.ty_name(other);
                self.error(span, format!("type `{on}` has no methods (stage0)"));
                Ty::Error
            }
        }
    }

    fn expect_eq(&mut self, actual: Ty, expected: Option<Ty>, span: Span) {
        if let Some(e) = expected {
            if e != actual && e != Ty::Error && actual != Ty::Error {
                let (en, an) = (self.ty_name(e), self.ty_name(actual));
                self.error(span, format!("expected `{en}`, found `{an}`"));
            }
        }
    }
}
