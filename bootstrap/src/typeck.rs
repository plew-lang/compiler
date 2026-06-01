//! Minimal type checker (stage0).
//!
//! Bidirectional: an *expected* type is pushed down so polymorphic numeric
//! literals are resolved from context (annotation, operand, parameter, return).
//! A numeric literal with no expected numeric type is an error — Plew has **no
//! default numeric type** (spec/02).
//!
//! Supports: numeric/Bool primitives, arithmetic/comparison, `if`/`while`,
//! bindings, calls, the `print` builtin, and **structs** (declaration, `<...>`
//! construction, field access). Enums/match, strings, arrays, generics, traits
//! come later.

use std::collections::{HashMap, HashSet};

use crate::ast::{Ast, BinOp, Block, ExprId, ExprKind, ItemKind, StmtKind, Type, UnOp};
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
    Unit,
    /// A declared struct, indexed into the registry built by [`check`].
    Struct(u32),
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
    /// Name for primitives; struct names go through [`Checker::ty_name`].
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
            Unit => "()",
            Struct(_) => "<struct>",
            Error => "<error>",
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TypeError {
    pub span: Span,
    pub msg: String,
}

struct FnSig {
    params: Vec<Ty>,
    ret: Ty,
}

struct StructDef {
    name: String,
    fields: Vec<(String, Ty)>,
}

/// Type-check a whole program. Returns all type errors (empty = well-typed).
pub fn check(ast: &Ast, items: &[crate::ast::ItemId]) -> Vec<TypeError> {
    let mut errors = Vec::new();

    // Pass 0a: assign an id to every struct name (so field types may reference
    // other structs, including forward references).
    let mut struct_ids: HashMap<String, u32> = HashMap::new();
    let mut struct_names: Vec<String> = Vec::new();
    for &id in items {
        if let ItemKind::Struct { name, .. } = &ast.item(id).kind {
            if !struct_ids.contains_key(name) {
                struct_ids.insert(name.clone(), struct_names.len() as u32);
                struct_names.push(name.clone());
            }
        }
    }
    // Pass 0b: resolve each struct's field types.
    let mut structs: Vec<StructDef> = struct_names
        .iter()
        .map(|n| StructDef { name: n.clone(), fields: Vec::new() })
        .collect();
    for &id in items {
        if let ItemKind::Struct { name, fields, generics } = &ast.item(id).kind {
            if !generics.is_empty() {
                errors.push(TypeError {
                    span: ast.item(id).span,
                    msg: "generic structs are not supported by the stage0 type checker yet".into(),
                });
            }
            let sid = struct_ids[name] as usize;
            structs[sid].fields = fields
                .iter()
                .map(|f| (f.name.clone(), resolve_ty(&f.ty, &struct_ids, &mut errors)))
                .collect();
        }
    }

    // Pass 1: collect function signatures.
    let mut sigs: HashMap<String, FnSig> = HashMap::new();
    for &id in items {
        if let ItemKind::Fn { name, params, ret, .. } = &ast.item(id).kind {
            let param_tys = params
                .iter()
                .map(|p| resolve_ty(&p.ty, &struct_ids, &mut errors))
                .collect();
            let ret_ty = match ret {
                Some(t) => resolve_ty(t, &struct_ids, &mut errors),
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
                struct_ids: &struct_ids,
                errors: &mut errors,
                scopes: Vec::new(),
                ret,
            };
            cx.push_scope();
            for p in params {
                let ty = resolve_ty(&p.ty, cx.struct_ids, cx.errors);
                cx.define(&p.label, ty);
            }
            cx.check_block(body);
            cx.pop_scope();
        }
    }

    errors
}

/// Resolve a syntactic type to a [`Ty`].
fn resolve_ty(t: &Type, struct_ids: &HashMap<String, u32>, errors: &mut Vec<TypeError>) -> Ty {
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
        other => match struct_ids.get(other) {
            Some(&id) => Ty::Struct(id),
            None => {
                errors.push(TypeError {
                    span: t.span,
                    msg: format!("unknown type `{other}` (stage0 supports primitives, Bool, and declared structs)"),
                });
                Ty::Error
            }
        },
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
    struct_ids: &'a HashMap<String, u32>,
    errors: &'a mut Vec<TypeError>,
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

    fn check_stmt(&mut self, sid: crate::ast::StmtId) {
        let span = self.ast.stmt(sid).span;
        match &self.ast.stmt(sid).kind {
            StmtKind::Let { name, ty, value, .. } => {
                let name = name.clone();
                let value = *value;
                let expected = ty.as_ref().map(|t| resolve_ty(t, self.struct_ids, self.errors));
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
            ExprKind::Str(_) => {
                self.error(span, "string literals are not supported by the stage0 type checker yet");
                Ty::Error
            }
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
            ExprKind::Block(block) => {
                let block = block.clone();
                self.check_block(&block);
                Ty::Unit
            }
            ExprKind::New { path, fields } => {
                let path = path.clone();
                let fields: Vec<(String, ExprId)> =
                    fields.iter().map(|(n, v)| (n.clone(), *v)).collect();
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
                    Ty::Error => Ty::Error,
                    other => {
                        let on = self.ty_name(other);
                        self.error(span, format!("type `{on}` has no fields"));
                        Ty::Error
                    }
                }
            }
            ExprKind::Index { .. } => {
                self.error(span, "indexing is not supported by the stage0 type checker yet");
                Ty::Error
            }
            ExprKind::Match { .. } => {
                self.error(span, "`match` is not supported by the stage0 type checker yet");
                Ty::Error
            }
            ExprKind::Error => Ty::Error,
        }
    }

    fn check_new(&mut self, path: &[String], fields: &[(String, ExprId)], span: Span) -> Ty {
        if path.len() != 1 {
            self.error(span, "enum-variant construction is not supported by the stage0 type checker yet");
            for (_, v) in fields {
                self.check_expr(*v, None);
            }
            return Ty::Error;
        }
        let sname = &path[0];
        let Some(&sid) = self.struct_ids.get(sname) else {
            self.error(span, format!("`{sname}` is not a declared struct"));
            for (_, v) in fields {
                self.check_expr(*v, None);
            }
            return Ty::Error;
        };
        let def_fields = self.structs[sid as usize].fields.clone();
        let mut provided: HashSet<&str> = HashSet::new();
        for (fname, fval) in fields {
            match def_fields.iter().find(|(n, _)| n == fname) {
                Some((_, fty)) => {
                    self.check_expr(*fval, Some(*fty));
                    provided.insert(fname.as_str());
                }
                None => self.error(span, format!("`{sname}` has no field `{fname}`")),
            }
        }
        for (n, _) in &def_fields {
            if !provided.contains(n.as_str()) {
                self.error(span, format!("missing field `{n}` in construction of `{sname}`"));
            }
        }
        Ty::Struct(sid)
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
        if let ExprKind::Ident(name) = &self.ast.expr(callee).kind {
            let name = name.clone();
            if name == "print" {
                if args.len() != 1 {
                    self.error(span, "`print` takes exactly one argument (stage0)");
                } else {
                    let t = self.check_expr(args[0], Some(Ty::I64));
                    if t != Ty::Error && !t.is_numeric() {
                        self.error(span, "`print` expects a numeric argument (stage0)");
                    }
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

    fn expect_eq(&mut self, actual: Ty, expected: Option<Ty>, span: Span) {
        if let Some(e) = expected {
            if e != actual && e != Ty::Error && actual != Ty::Error {
                let (en, an) = (self.ty_name(e), self.ty_name(actual));
                self.error(span, format!("expected `{en}`, found `{an}`"));
            }
        }
    }
}
