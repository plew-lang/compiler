//! Minimal C code generator (stage0 walking skeleton).
//!
//! This is deliberately tiny: it assumes everything is a 64-bit integer, has no
//! type checking, and special-cases `print(<int>)` to `printf`. Its purpose is
//! to prove the whole spine — source → C → clang → run — end to end. Real type
//! lowering, the ARC runtime, strings, etc. replace it incrementally.

use crate::ast::{
    Ast, BinOp, Block, ExprId, ExprKind, ItemId, ItemKind, MatchArm, PatKind, StmtId, StmtKind,
    Type, UnOp,
};
use crate::typeck::{Ty, TypeTable};

/// Generate a complete C translation unit for `items`, or a list of
/// "unsupported construct" errors if the program uses features the skeleton
/// codegen does not handle yet.
pub fn emit_c(
    ast: &Ast,
    items: &[ItemId],
    expr_ty: &[Ty],
    table: &TypeTable,
) -> Result<String, Vec<String>> {
    let mut cg = Codegen {
        ast,
        items,
        expr_ty,
        table,
        out: String::new(),
        errors: Vec::new(),
        tmp: 0,
        inout_params: Vec::new(),
    };
    cg.out.push_str("#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\n");
    // stage0 String: immutable view over a (literal) UTF-8 buffer.
    cg.out.push_str("typedef struct { const char* data; int64_t len; } PlewString;\n");
    cg.out.push_str(
        "static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (int64_t i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }\n\n",
    );
    // Type emission must respect C's "declare before use", with two wrinkles:
    // a struct/enum may contain an array (by value) and an array's element may
    // be a struct/enum. We break the cycle with: (1) forward decls of every
    // nominal type, (2) array *typedefs* (which only need a forward decl since
    // they hold a pointer to the element), (3) full struct/enum bodies in
    // dependency order, (4) array *runtime* (operates on elements by value, so
    // needs full bodies). Functions then get prototypes before bodies so they
    // can be mutually recursive.
    for &id in items {
        match ast.item(id).kind {
            ItemKind::Struct { .. } => cg.emit_nominal_fwd(id),
            ItemKind::Enum { .. } => cg.emit_nominal_fwd(id),
            ItemKind::Fn { .. } => {}
        }
    }
    cg.out.push('\n');
    cg.emit_array_typedefs();
    cg.emit_nominal_defs();
    cg.emit_array_runtime();
    cg.emit_fn_prototypes();
    for &id in items {
        cg.emit_item(id);
    }
    if cg.errors.is_empty() {
        Ok(cg.out)
    } else {
        Err(cg.errors)
    }
}

struct Codegen<'a> {
    ast: &'a Ast,
    items: &'a [ItemId],
    /// Inferred type of every expression, from the type checker.
    expr_ty: &'a [Ty],
    /// Shared nominal/array type table (id → name, array element types).
    table: &'a TypeTable,
    out: String,
    errors: Vec<String>,
    /// Counter for generated temporaries (e.g. match scrutinees).
    tmp: u32,
    /// Names of the current function's `inout` parameters (lowered to C
    /// pointers; their uses are dereferenced).
    inout_params: Vec<String>,
}

impl Codegen<'_> {
    fn emit_item(&mut self, id: ItemId) {
        match &self.ast.item(id).kind {
            ItemKind::Fn { name, params, ret, body } => {
                let is_main = name == "main";
                if is_main {
                    self.out.push_str("int main(void) {\n");
                } else {
                    let sig = self.fn_signature(name, params, ret);
                    self.out.push_str(&sig);
                    self.out.push_str(" {\n");
                }
                // Track inout params so their uses are dereferenced in the body.
                self.inout_params = params
                    .iter()
                    .filter(|p| p.mode == crate::ast::Mode::Inout)
                    .map(|p| p.label.clone())
                    .collect();
                let stmts: Vec<StmtId> = body.stmts.clone();
                for sid in stmts {
                    self.emit_stmt(sid, is_main);
                }
                self.inout_params.clear();
                if is_main {
                    self.out.push_str("    return 0;\n");
                }
                self.out.push_str("}\n\n");
            }
            ItemKind::Struct { .. } | ItemKind::Enum { .. } => {} // emitted in the typedef pass
        }
    }

    /// Forward declaration: `typedef struct Name Name;` so the name can be used
    /// (through a pointer) before its body is emitted.
    fn emit_nominal_fwd(&mut self, id: ItemId) {
        let name = match &self.ast.item(id).kind {
            ItemKind::Struct { name, generics, .. } | ItemKind::Enum { name, generics, .. } => {
                if !generics.is_empty() {
                    self.errors.push("generic type codegen is not supported by stage0 yet".into());
                    return;
                }
                name.clone()
            }
            ItemKind::Fn { .. } => return,
        };
        self.out.push_str(&format!("typedef struct {name} {name};\n"));
    }

    /// Emit full struct/enum bodies in dependency order: a type that contains
    /// another nominal type *by value* (not via an array, which is a pointer)
    /// must be defined after it.
    fn emit_nominal_defs(&mut self) {
        // Collect nominal items and their by-value nominal dependencies.
        let mut order: Vec<ItemId> = Vec::new();
        let mut visiting: Vec<String> = Vec::new();
        let mut done: Vec<String> = Vec::new();
        let nominals: Vec<ItemId> = self
            .items
            .iter()
            .copied()
            .filter(|&id| matches!(self.ast.item(id).kind, ItemKind::Struct { .. } | ItemKind::Enum { .. }))
            .collect();
        for &id in &nominals {
            self.topo_visit(id, &nominals, &mut order, &mut visiting, &mut done);
        }
        for id in order {
            self.emit_nominal_body(id);
        }
    }

    fn topo_visit(
        &mut self,
        id: ItemId,
        nominals: &[ItemId],
        order: &mut Vec<ItemId>,
        visiting: &mut Vec<String>,
        done: &mut Vec<String>,
    ) {
        let name = match &self.ast.item(id).kind {
            ItemKind::Struct { name, .. } | ItemKind::Enum { name, .. } => name.clone(),
            ItemKind::Fn { .. } => return,
        };
        if done.contains(&name) || visiting.contains(&name) {
            return; // already emitted, or a cycle (broken arbitrarily)
        }
        visiting.push(name.clone());
        for dep in self.nominal_deps(id) {
            if let Some(&dep_id) = nominals
                .iter()
                .find(|&&n| matches!(&self.ast.item(n).kind, ItemKind::Struct { name, .. } | ItemKind::Enum { name, .. } if *name == dep))
            {
                self.topo_visit(dep_id, nominals, order, visiting, done);
            }
        }
        visiting.retain(|n| n != &name);
        done.push(name);
        order.push(id);
    }

    /// Names of nominal types this type embeds *by value* (a direct field of
    /// struct/enum type). `Array[T]` fields don't count (they hold a pointer).
    fn nominal_deps(&self, id: ItemId) -> Vec<String> {
        let mut deps = Vec::new();
        let add = |t: &Type, deps: &mut Vec<String>| {
            if t.name != "Array"
                && !is_primitive_type(&t.name)
                && !deps.contains(&t.name)
            {
                deps.push(t.name.clone());
            }
        };
        match &self.ast.item(id).kind {
            ItemKind::Struct { fields, .. } => {
                for f in fields {
                    add(&f.ty, &mut deps);
                }
            }
            ItemKind::Enum { variants, .. } => {
                for v in variants {
                    for f in &v.fields {
                        add(&f.ty, &mut deps);
                    }
                }
            }
            ItemKind::Fn { .. } => {}
        }
        deps
    }

    fn emit_nominal_body(&mut self, id: ItemId) {
        match &self.ast.item(id).kind {
            ItemKind::Struct { name, fields, .. } => {
                let name = name.clone();
                let fields: Vec<(String, Type)> =
                    fields.iter().map(|f| (f.name.clone(), f.ty.clone())).collect();
                self.out.push_str(&format!("struct {name} {{\n"));
                for (fname, fty) in &fields {
                    let cty = c_type(fty);
                    self.out.push_str(&format!("    {cty} {fname};\n"));
                }
                self.out.push_str("};\n\n");
            }
            ItemKind::Enum { name, variants, .. } => {
                let name = name.clone();
                let variants: Vec<(String, Vec<(String, Type)>)> = variants
                    .iter()
                    .map(|v| {
                        (v.name.clone(), v.fields.iter().map(|f| (f.name.clone(), f.ty.clone())).collect())
                    })
                    .collect();
                self.out.push_str(&format!("struct {name} {{\n    int tag;\n"));
                if variants.iter().any(|(_, fs)| !fs.is_empty()) {
                    self.out.push_str("    union {\n");
                    for (vname, fs) in &variants {
                        if fs.is_empty() {
                            continue;
                        }
                        self.out.push_str("        struct { ");
                        for (fname, fty) in fs {
                            self.out.push_str(&format!("{} {fname}; ", c_type(fty)));
                        }
                        self.out.push_str(&format!("}} {vname};\n"));
                    }
                    self.out.push_str("    } data;\n");
                }
                self.out.push_str("};\n\n");
            }
            ItemKind::Fn { .. } => {}
        }
    }

    /// Array typedefs: `{T* data; len; cap}`. The element is held via a pointer
    /// so a forward declaration of `T` suffices (emitted before full bodies).
    fn emit_array_typedefs(&mut self) {
        for id in 0..self.table.array_elems.len() as u32 {
            let elem = self.table.array_elem(id);
            let at = self.array_c_name(id);
            let et = self.ty_c_name(elem);
            self.out.push_str(&format!(
                "typedef struct {{ {et}* data; int64_t len; int64_t cap; }} {at};\n"
            ));
        }
        self.out.push('\n');
    }

    /// Array (leaked) runtime — operates on elements by value, so it must come
    /// after full struct/enum bodies. Memory is never freed (throwaway stage0).
    fn emit_array_runtime(&mut self) {
        for id in 0..self.table.array_elems.len() as u32 {
            let elem = self.table.array_elem(id);
            let at = self.array_c_name(id);
            let et = self.ty_c_name(elem);
            self.out.push_str(&format!(
                "static {at} {at}_new(void) {{ {at} a; a.data = 0; a.len = 0; a.cap = 0; return a; }}\n"
            ));
            self.out.push_str(&format!(
                "static {et} {at}_get({at} a, int64_t i) {{ if (i < 0 || i >= a.len) {{ fprintf(stderr, \"panic: index out of range\\n\"); exit(1); }} return a.data[i]; }}\n"
            ));
            self.out.push_str(&format!(
                "static void {at}_set({at}* a, int64_t i, {et} v) {{ if (i < 0 || i >= a->len) {{ fprintf(stderr, \"panic: index out of range\\n\"); exit(1); }} a->data[i] = v; }}\n"
            ));
            // Growable push (old buffer leaked on realloc — stage0 never frees).
            self.out.push_str(&format!(
                "static void {at}_push({at}* a, {et} v) {{ if (a->len >= a->cap) {{ int64_t nc = a->cap < 4 ? 4 : a->cap * 2; {et}* nd = ({et}*)malloc(sizeof({et}) * nc); for (int64_t i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; }} a->data[a->len] = v; a->len++; }}\n\n"
            ));
        }
    }

    /// Emit a prototype for every non-`main` function so they can be mutually
    /// recursive (and called before their definition).
    fn emit_fn_prototypes(&mut self) {
        for &id in self.items {
            if let ItemKind::Fn { name, params, ret, .. } = &self.ast.item(id).kind {
                if name == "main" {
                    continue;
                }
                let sig = self.fn_signature(name, params, ret);
                self.out.push_str(&sig);
                self.out.push_str(";\n");
            }
        }
        self.out.push('\n');
    }

    /// Render a C function signature `ret name(params)` (no body / trailing
    /// semicolon). `inout` params become pointers.
    fn fn_signature(
        &self,
        name: &str,
        params: &[crate::ast::Param],
        ret: &Option<Type>,
    ) -> String {
        let rty = match ret {
            Some(t) => c_type(t),
            None => "void".to_string(),
        };
        let mut s = format!("{rty} {name}(");
        if params.is_empty() {
            s.push_str("void");
        } else {
            for (i, p) in params.iter().enumerate() {
                if i > 0 {
                    s.push_str(", ");
                }
                s.push_str(&c_type(&p.ty));
                s.push(' ');
                if p.mode == crate::ast::Mode::Inout {
                    s.push('*');
                }
                s.push_str(&p.label);
            }
        }
        s.push(')');
        s
    }

    /// Inferred type of expression `id` (from the type checker).
    fn ty_of(&self, id: ExprId) -> Ty {
        self.expr_ty.get(id.0 as usize).copied().unwrap_or(Ty::Error)
    }

    /// C type name of `Array[elem]` for array-type id `id`.
    fn array_c_name(&self, id: u32) -> String {
        format!("PlewArray_{}", self.mangle(self.table.array_elem(id)))
    }

    /// Spell a [`Ty`] as a C type name (used where no syntactic `Type` exists,
    /// e.g. array literals and `for`-each element bindings).
    fn ty_c_name(&self, t: Ty) -> String {
        match t {
            Ty::I8 => "int8_t".into(),
            Ty::I16 => "int16_t".into(),
            Ty::I32 => "int32_t".into(),
            Ty::I64 => "int64_t".into(),
            Ty::U8 => "uint8_t".into(),
            Ty::U16 => "uint16_t".into(),
            Ty::U32 => "uint32_t".into(),
            Ty::U64 => "uint64_t".into(),
            Ty::F32 => "float".into(),
            Ty::F64 => "double".into(),
            Ty::Bool => "int".into(),
            Ty::String => "PlewString".into(),
            Ty::Struct(id) => self.table.struct_names[id as usize].clone(),
            Ty::Enum(id) => self.table.enum_names[id as usize].clone(),
            Ty::Array(id) => self.array_c_name(id),
            Ty::Unit => "void".into(),
            Ty::Error => "int".into(),
        }
    }

    /// A C-identifier-safe mangling of a [`Ty`] (for type/function name parts).
    fn mangle(&self, t: Ty) -> String {
        match t {
            Ty::I8 => "I8".into(),
            Ty::I16 => "I16".into(),
            Ty::I32 => "I32".into(),
            Ty::I64 => "I64".into(),
            Ty::U8 => "U8".into(),
            Ty::U16 => "U16".into(),
            Ty::U32 => "U32".into(),
            Ty::U64 => "U64".into(),
            Ty::F32 => "F32".into(),
            Ty::F64 => "F64".into(),
            Ty::Bool => "Bool".into(),
            Ty::String => "String".into(),
            Ty::Struct(id) => self.table.struct_names[id as usize].clone(),
            Ty::Enum(id) => self.table.enum_names[id as usize].clone(),
            Ty::Array(id) => format!("Arr_{}", self.mangle(self.table.array_elem(id))),
            Ty::Unit => "Unit".into(),
            Ty::Error => "Error".into(),
        }
    }

    /// Tag index of `variant` within `enum_name`, by scanning the item list.
    fn enum_variant_tag(&self, enum_name: &str, variant: &str) -> Option<usize> {
        for &id in self.items {
            if let ItemKind::Enum { name, variants, .. } = &self.ast.item(id).kind {
                if name == enum_name {
                    return variants.iter().position(|v| v.name == variant);
                }
            }
        }
        None
    }

    /// C type of `variant.field` within `enum_name`.
    fn enum_field_ctype(&self, enum_name: &str, variant: &str, field: &str) -> Option<String> {
        for &id in self.items {
            if let ItemKind::Enum { name, variants, .. } = &self.ast.item(id).kind {
                if name == enum_name {
                    let v = variants.iter().find(|v| v.name == variant)?;
                    let f = v.fields.iter().find(|f| f.name == field)?;
                    return Some(c_type(&f.ty));
                }
            }
        }
        None
    }

    /// Find the enum that declares a variant of the given name (used when a
    /// pattern writes a bare `Variant` instead of `Enum.Variant`).
    fn find_enum_by_variant(&self, variant: &str) -> Option<String> {
        for &id in self.items {
            if let ItemKind::Enum { name, variants, .. } = &self.ast.item(id).kind {
                if variants.iter().any(|v| v.name == variant) {
                    return Some(name.clone());
                }
            }
        }
        None
    }

    fn emit_stmt(&mut self, id: StmtId, in_main: bool) {
        match &self.ast.stmt(id).kind {
            StmtKind::Let { name, ty, value, .. } => {
                let name = name.clone();
                let cty = ty.as_ref().map(c_type).unwrap_or_else(|| "int64_t".to_string());
                let v = self.expr(*value);
                self.out.push_str(&format!("    {cty} {name} = {v};\n"));
            }
            StmtKind::Return(value) => match value {
                None => {
                    // `return` with no value: main returns 0, others return.
                    self.out.push_str(if in_main { "    return 0;\n" } else { "    return;\n" });
                }
                Some(e) => {
                    let v = self.expr(*e);
                    self.out.push_str(&format!("    return {v};\n"));
                }
            },
            StmtKind::Give(_) => {
                self.errors
                    .push("`give` / block-as-value is not supported by stage0 codegen yet".into());
            }
            StmtKind::Assign { target, op, value } => {
                let (target, op, value) = (*target, *op, *value);
                // `arr[i] = v` / `arr[i] OP= v` → bounds-checked `_set` (a
                // plain `_get(...) = v` would assign to an rvalue).
                if let ExprKind::Index { base, index } = &self.ast.expr(target).kind {
                    let (base, index) = (*base, *index);
                    if let Ty::Array(id) = self.ty_of(base) {
                        self.emit_index_set(id, base, index, op, value);
                        return;
                    }
                }
                let t = self.expr(target);
                let v = self.expr(value);
                let opc = match op {
                    None => "=".to_string(),
                    Some(o) => match c_binop(o) {
                        Some(s) => format!("{s}="),
                        None => {
                            self.errors.push(format!(
                                "compound assignment with `{}` is not supported yet",
                                o.symbol()
                            ));
                            "=".to_string()
                        }
                    },
                };
                self.out.push_str(&format!("    {t} {opc} {v};\n"));
            }
            StmtKind::Break => self.out.push_str("    break;\n"),
            StmtKind::Continue => self.out.push_str("    continue;\n"),
            StmtKind::Expr(e) => {
                let e = *e;
                self.emit_expr_stmt(e, in_main);
            }
        }
    }

    /// Emit an expression in statement position. Control-flow expressions
    /// (`if`, block) lower to C statements; everything else to `expr;`.
    fn emit_expr_stmt(&mut self, e: ExprId, in_main: bool) {
        // `if` used as a statement
        let if_info = if let ExprKind::If { cond, then_branch, else_branch } = &self.ast.expr(e).kind
        {
            Some((*cond, *then_branch, *else_branch))
        } else {
            None
        };
        if let Some((cond, then_branch, else_branch)) = if_info {
            self.emit_if_stmt(cond, then_branch, else_branch, in_main);
            return;
        }
        // `while` used as a statement
        let while_info = if let ExprKind::While { cond, body } = &self.ast.expr(e).kind {
            Some((*cond, *body))
        } else {
            None
        };
        if let Some((cond, body)) = while_info {
            let c = self.expr(cond);
            self.out.push_str(&format!("    while ({c}) {{\n"));
            self.emit_branch_block(body, in_main);
            self.out.push_str("    }\n");
            return;
        }
        // `for` over a range used as a statement
        let for_info = if let ExprKind::For { var, iter, body, .. } = &self.ast.expr(e).kind {
            Some((var.clone(), *iter, *body))
        } else {
            None
        };
        if let Some((var, iter, body)) = for_info {
            self.emit_for(&var, iter, body, in_main);
            return;
        }
        // `match` used as a statement
        let match_info = if let ExprKind::Match { scrutinee, arms } = &self.ast.expr(e).kind {
            Some((*scrutinee, arms.clone()))
        } else {
            None
        };
        if let Some((scrutinee, arms)) = match_info {
            self.emit_match_stmt(scrutinee, &arms, in_main);
            return;
        }
        // bare block used as a statement
        if matches!(self.ast.expr(e).kind, ExprKind::Block(_)) {
            self.out.push_str("    {\n");
            self.emit_branch_block(e, in_main);
            self.out.push_str("    }\n");
            return;
        }
        if let Some(c) = self.try_emit_print(e) {
            self.out.push_str(&c);
        } else {
            let v = self.expr(e);
            self.out.push_str(&format!("    {v};\n"));
        }
    }

    fn emit_if_stmt(
        &mut self,
        cond: ExprId,
        then_branch: ExprId,
        else_branch: Option<ExprId>,
        in_main: bool,
    ) {
        let c = self.expr(cond);
        self.out.push_str(&format!("    if ({c}) {{\n"));
        self.emit_branch_block(then_branch, in_main);
        self.out.push_str("    }");
        match else_branch {
            None => self.out.push('\n'),
            Some(e) => {
                self.out.push_str(" else {\n");
                if matches!(self.ast.expr(e).kind, ExprKind::Block(_)) {
                    self.emit_branch_block(e, in_main);
                } else {
                    // `else if`: a nested if-expression
                    self.emit_expr_stmt(e, in_main);
                }
                self.out.push_str("    }\n");
            }
        }
    }

    /// Emit the statements of a block-expression (no value).
    fn emit_branch_block(&mut self, block_expr: ExprId, in_main: bool) {
        let stmts: Vec<StmtId> = match &self.ast.expr(block_expr).kind {
            ExprKind::Block(b) => b.stmts.clone(),
            _ => {
                self.errors.push("expected a block".into());
                Vec::new()
            }
        };
        for s in stmts {
            self.emit_stmt(s, in_main);
        }
    }

    /// Lower a `for` loop: a range `a..<b`/`a..=b` becomes a C counting loop;
    /// an array becomes an index loop binding each element.
    fn emit_for(&mut self, var: &str, iter: ExprId, body: ExprId, in_main: bool) {
        let range = if let ExprKind::Binary { op, lhs, rhs } = &self.ast.expr(iter).kind {
            if matches!(op, BinOp::RangeHalf | BinOp::RangeClosed) {
                Some((*op, *lhs, *rhs))
            } else {
                None
            }
        } else {
            None
        };
        if let Some((op, lhs, rhs)) = range {
            let lo = self.expr(lhs);
            let hi = self.expr(rhs);
            let cmp = if op == BinOp::RangeClosed { "<=" } else { "<" };
            self.out
                .push_str(&format!("    for (int64_t {var} = {lo}; {var} {cmp} {hi}; {var}++) {{\n"));
            self.emit_branch_block(body, in_main);
            self.out.push_str("    }\n");
            return;
        }
        // Array iteration: bind each element by index.
        let Ty::Array(arr_id) = self.ty_of(iter) else {
            self.errors.push("`for` over a non-range / non-array is not supported by stage0 codegen yet".into());
            return;
        };
        let et = self.ty_c_name(self.table.array_elem(arr_id));
        let n = self.tmp;
        self.tmp += 1;
        let (av, iv) = (format!("__for{n}"), format!("__fi{n}"));
        let it = self.expr(iter);
        let at = self.array_c_name(arr_id);
        self.out.push_str(&format!("    {at} {av} = {it};\n"));
        self.out
            .push_str(&format!("    for (int64_t {iv} = 0; {iv} < {av}.len; {iv}++) {{\n"));
        self.out.push_str(&format!("        {et} {var} = {av}.data[{iv}];\n"));
        self.emit_branch_block(body, in_main);
        self.out.push_str("    }\n");
    }

    /// Lower `arr[i] = v` / `arr[i] OP= v` to a bounds-checked `_set`. The
    /// receiver must be an addressable C lvalue. For a compound assignment the
    /// base/index are evaluated more than once (fine for stage0's lvalue bases).
    fn emit_index_set(
        &mut self,
        arr_id: u32,
        base: ExprId,
        index: ExprId,
        op: Option<BinOp>,
        value: ExprId,
    ) {
        let at = self.array_c_name(arr_id);
        let b = self.expr(base);
        let i = self.expr(index);
        let v = self.expr(value);
        let rhs = match op {
            None => v,
            Some(o) => match c_binop(o) {
                Some(sym) => format!("{at}_get({b}, (int64_t)({i})) {sym} {v}"),
                None => {
                    self.errors.push(format!(
                        "compound assignment with `{}` is not supported yet",
                        o.symbol()
                    ));
                    v
                }
            },
        };
        self.out.push_str(&format!("    {at}_set(&({b}), (int64_t)({i}), {rhs});\n"));
    }

    /// Lower a builtin `Array` method call. `append` mutates the receiver in
    /// place, so the base must be an addressable C lvalue (Ident / field).
    fn emit_array_method(
        &mut self,
        arr_id: u32,
        base: ExprId,
        name: &str,
        args: &[ExprId],
    ) -> String {
        let at = self.array_c_name(arr_id);
        match name {
            "append" => {
                let b = self.expr(base);
                let v = self.expr(args[0]);
                // Returns Unit; emitted as a (void) call usable in stmt position.
                format!("{at}_push(&({b}), {v})")
            }
            other => {
                self.errors.push(format!("`Array` method `{other}` is not supported by stage0 codegen"));
                "0".into()
            }
        }
    }

    /// Lower a block used as a value to a GNU statement-expression
    /// `({ stmts...; give_value; })`. Statements are captured by temporarily
    /// redirecting `self.out`.
    fn emit_value_block(&mut self, block: &Block) -> String {
        let saved = std::mem::take(&mut self.out);
        let mut tail = String::from("0");
        for &sid in &block.stmts {
            if let StmtKind::Give(e) = &self.ast.stmt(sid).kind {
                let e = *e;
                tail = self.expr(e);
            } else {
                self.emit_stmt(sid, false);
            }
        }
        let body = std::mem::replace(&mut self.out, saved);
        format!("({{ {body}{tail}; }})")
    }

    /// Lower a statement-position `match`. Both enum and integer/Bool
    /// scrutinees become an if-chain on the tag/value. (An if-chain rather than
    /// a C `switch` so a Plew `break` in an arm targets the enclosing loop, not
    /// a switch.) Value-position `match` is not supported by stage0 yet.
    fn emit_match_stmt(&mut self, scrutinee: ExprId, arms: &[MatchArm], in_main: bool) {
        // Classify the match from its patterns.
        let mut enum_name: Option<String> = None;
        let mut is_value = false;
        for arm in arms {
            match &self.ast.pat(arm.pat).kind {
                PatKind::Variant { path, .. } => {
                    enum_name = if path.len() >= 2 {
                        Some(path[0].clone())
                    } else {
                        self.find_enum_by_variant(&path[0])
                    };
                    break;
                }
                PatKind::Int(_) | PatKind::Bool(_) => {
                    is_value = true;
                    break;
                }
                _ => {}
            }
        }

        let scrut = self.expr(scrutinee);
        let id = self.tmp;
        self.tmp += 1;
        let tname = format!("__m{id}");

        if let Some(ename) = enum_name {
            self.out.push_str(&format!("    {ename} {tname} = {scrut};\n"));
            let mut first = true;
            for arm in arms {
                self.emit_enum_arm(&ename, &tname, arm, in_main, &mut first);
            }
            if !first {
                self.out.push('\n');
            }
        } else if is_value {
            self.out.push_str(&format!("    int64_t {tname} = {scrut};\n"));
            self.emit_value_arms(&tname, arms, in_main);
        } else {
            self.errors
                .push("match with only wildcard arms is not supported by stage0 codegen yet".into());
        }
    }

    /// Emit one enum-match arm as a link in an if-chain. `first` tracks whether
    /// this is the leading `if` (vs `else if` / `else`).
    fn emit_enum_arm(
        &mut self,
        ename: &str,
        tname: &str,
        arm: &MatchArm,
        in_main: bool,
        first: &mut bool,
    ) {
        let body = arm.body;
        match &self.ast.pat(arm.pat).kind {
            PatKind::Variant { path, fields } => {
                let vname = path.last().cloned().unwrap_or_default();
                let fields: Vec<(String, crate::ast::PatId)> =
                    fields.iter().map(|(n, p)| (n.clone(), *p)).collect();
                let tag = self.enum_variant_tag(ename, &vname).unwrap_or(0);
                if *first {
                    self.out.push_str(&format!("    if ({tname}.tag == {tag}) {{\n"));
                    *first = false;
                } else {
                    self.out.push_str(&format!(" else if ({tname}.tag == {tag}) {{\n"));
                }
                for (fname, fpat) in &fields {
                    match &self.ast.pat(*fpat).kind {
                        PatKind::Binding { name, .. } => {
                            let name = name.clone();
                            let cty = self
                                .enum_field_ctype(ename, &vname, fname)
                                .unwrap_or_else(|| "int64_t".into());
                            self.out.push_str(&format!(
                                "        {cty} {name} = {tname}.data.{vname}.{fname};\n"
                            ));
                        }
                        PatKind::Wildcard => {}
                        _ => self.errors.push(
                            "nested patterns inside variant fields are not supported by stage0 codegen yet".into(),
                        ),
                    }
                }
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("    }");
            }
            PatKind::Wildcard => {
                if *first {
                    self.out.push_str("    {\n");
                    *first = false;
                } else {
                    self.out.push_str(" else {\n");
                }
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("    }");
            }
            PatKind::Binding { name, .. } => {
                let name = name.clone();
                if *first {
                    self.out.push_str("    {\n");
                    *first = false;
                } else {
                    self.out.push_str(" else {\n");
                }
                self.out.push_str(&format!("        {ename} {name} = {tname};\n"));
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("    }");
            }
            _ => self.errors.push("unsupported pattern in enum match (stage0)".into()),
        }
    }

    fn emit_value_arms(&mut self, tname: &str, arms: &[MatchArm], in_main: bool) {
        let mut first = true;
        for arm in arms {
            let body = arm.body;
            let cond: Option<String> = match &self.ast.pat(arm.pat).kind {
                PatKind::Int(s) => Some(format!("{tname} == {}", s.replace('_', ""))),
                PatKind::Bool(b) => Some(format!("{tname} == {}", if *b { 1 } else { 0 })),
                PatKind::Wildcard | PatKind::Binding { .. } => None,
                _ => {
                    self.errors.push("unsupported pattern in value match (stage0)".into());
                    Some("0".into())
                }
            };
            let bind_name = if let PatKind::Binding { name, .. } = &self.ast.pat(arm.pat).kind {
                Some(name.clone())
            } else {
                None
            };
            match cond {
                Some(c) => {
                    if first {
                        self.out.push_str(&format!("    if ({c}) {{\n"));
                        first = false;
                    } else {
                        self.out.push_str(&format!(" else if ({c}) {{\n"));
                    }
                    self.emit_expr_stmt(body, in_main);
                    self.out.push_str("    }");
                }
                None => {
                    if first {
                        self.out.push_str("    {\n");
                        first = false;
                    } else {
                        self.out.push_str(" else {\n");
                    }
                    if let Some(n) = bind_name {
                        self.out.push_str(&format!("        int64_t {n} = {tname};\n"));
                    }
                    self.emit_expr_stmt(body, in_main);
                    self.out.push_str("    }");
                }
            }
        }
        self.out.push('\n');
    }

    /// Special-case `print(<expr>)` → `printf("%lld\n", (long long)(expr))`.
    fn try_emit_print(&mut self, id: ExprId) -> Option<String> {
        if let ExprKind::Call { callee, args } = &self.ast.expr(id).kind {
            if let ExprKind::Ident(name) = &self.ast.expr(*callee).kind {
                if name == "print" && args.len() == 1 && args[0].label.is_none() {
                    let argid = args[0].value;
                    let aty = self.expr_ty.get(argid.0 as usize).copied().unwrap_or(Ty::Error);
                    let v = self.expr(argid);
                    let line = match aty {
                        Ty::String => {
                            format!("    printf(\"%.*s\\n\", (int)({v}).len, ({v}).data);\n")
                        }
                        Ty::F32 | Ty::F64 => format!("    printf(\"%f\\n\", (double)({v}));\n"),
                        _ => format!("    printf(\"%lld\\n\", (long long)({v}));\n"),
                    };
                    return Some(line);
                }
            }
        }
        None
    }

    /// Lower an expression to a C expression string.
    fn expr(&mut self, id: ExprId) -> String {
        match &self.ast.expr(id).kind {
            ExprKind::Int(s) => s.replace('_', ""),
            ExprKind::Float(s) => s.replace('_', ""),
            ExprKind::Bool(b) => if *b { "1".into() } else { "0".into() },
            ExprKind::Ident(s) => {
                // An `inout` parameter is a C pointer; dereference its uses.
                if self.inout_params.iter().any(|p| p == s) {
                    format!("(*{s})")
                } else {
                    s.clone()
                }
            }
            ExprKind::Str(s) => {
                let (lit, len) = c_string_literal(s);
                format!("((PlewString){{{lit}, {len}}})")
            }
            ExprKind::Unary { op, operand } => {
                let inner = self.expr(*operand);
                let sym = match op {
                    UnOp::Neg => "-",
                    UnOp::Not => "!",
                    UnOp::BitNot => "~",
                };
                format!("({sym}{inner})")
            }
            ExprKind::Binary { op, lhs, rhs } => {
                let (op, lhs, rhs) = (*op, *lhs, *rhs);
                // String equality is by-bytes, not a C struct compare.
                if matches!(op, BinOp::Eq | BinOp::Ne) && self.ty_of(lhs) == Ty::String {
                    let l = self.expr(lhs);
                    let r = self.expr(rhs);
                    let eq = format!("PlewString_eq({l}, {r})");
                    return if op == BinOp::Ne { format!("(!{eq})") } else { eq };
                }
                let l = self.expr(lhs);
                let r = self.expr(rhs);
                match c_binop(op) {
                    Some(sym) => format!("({l} {sym} {r})"),
                    None => {
                        self.errors.push(format!(
                            "operator `{}` is not supported by stage0 codegen yet",
                            op.symbol()
                        ));
                        "0".into()
                    }
                }
            }
            ExprKind::Call { callee, args } => {
                let callee = *callee;
                let arg_modes: Vec<crate::ast::Mode> = args.iter().map(|a| a.mode).collect();
                let arg_ids: Vec<ExprId> = args.iter().map(|a| a.value).collect();
                // Method call `base.method(args)` — stage0 builtin Array methods.
                if let ExprKind::Field { base, name } = &self.ast.expr(callee).kind {
                    let (base, name) = (*base, name.clone());
                    if let Ty::Array(id) = self.ty_of(base) {
                        return self.emit_array_method(id, base, &name, &arg_ids);
                    }
                    self.errors.push(format!("method `{name}` is not supported by stage0 codegen"));
                    return "0".into();
                }
                // Non-method call: emit positional C call (labels ignored for
                // now). An `inout` argument passes the address of its place.
                let callee_c = self.expr(callee);
                let parts: Vec<String> = arg_ids
                    .iter()
                    .zip(&arg_modes)
                    .map(|(&a, &m)| {
                        let c = self.expr(a);
                        if m == crate::ast::Mode::Inout {
                            format!("&({c})")
                        } else {
                            c
                        }
                    })
                    .collect();
                format!("{callee_c}({})", parts.join(", "))
            }
            ExprKind::Field { base, name } => {
                let base = *base;
                let name = name.clone();
                // `arr.count` lowers to the C length field.
                if name == "count" && matches!(self.ty_of(base), Ty::Array(_)) {
                    let b = self.expr(base);
                    return format!("({b}).len");
                }
                // `s.bytes` views the string's buffer as an `Array[U8]` (shared,
                // O(1)) — fine under the stage0 reference-semantics array model.
                if name == "bytes" && self.ty_of(base) == Ty::String {
                    let at = self.ty_c_name(self.ty_of(id));
                    let b = self.expr(base);
                    return format!(
                        "({{ PlewString __s = {b}; ({at}){{(uint8_t*)__s.data, __s.len, __s.len}}; }})"
                    );
                }
                let b = self.expr(base);
                format!("{b}.{name}")
            }
            ExprKind::Array(elems) => {
                let elems = elems.clone();
                let aty = self.ty_of(id);
                let Ty::Array(arr_id) = aty else {
                    self.errors.push("array literal has no array type (stage0)".into());
                    return "0".into();
                };
                let at = self.array_c_name(arr_id);
                if elems.is_empty() {
                    return format!("{at}_new()");
                }
                let et = self.ty_c_name(self.table.array_elem(arr_id));
                let n = elems.len();
                let tmp = self.tmp;
                self.tmp += 1;
                let v = format!("__a{tmp}");
                let mut s = format!(
                    "({{ {at} {v}; {v}.data = ({et}*)malloc(sizeof({et}) * {n}); {v}.len = {n}; {v}.cap = {n}; "
                );
                for (i, &e) in elems.iter().enumerate() {
                    let ce = self.expr(e);
                    s.push_str(&format!("{v}.data[{i}] = {ce}; "));
                }
                s.push_str(&format!("{v}; }})"));
                s
            }
            ExprKind::Index { base, index } => {
                let (base, index) = (*base, *index);
                let aty = self.ty_of(base);
                let Ty::Array(arr_id) = aty else {
                    self.errors.push("indexing a non-array is not supported by stage0 codegen".into());
                    return "0".into();
                };
                let at = self.array_c_name(arr_id);
                let b = self.expr(base);
                let i = self.expr(index);
                format!("{at}_get({b}, (int64_t)({i}))")
            }
            ExprKind::New { path, fields } => {
                let path = path.clone();
                let field_list: Vec<(String, ExprId)> =
                    fields.iter().map(|(n, v)| (n.clone(), *v)).collect();
                if path.len() == 1 {
                    let mut parts = Vec::new();
                    for (n, v) in &field_list {
                        let cv = self.expr(*v);
                        parts.push(format!(".{n} = {cv}"));
                    }
                    format!("(({}){{{}}})", path[0], parts.join(", "))
                } else if path.len() == 2 {
                    let ename = path[0].clone();
                    let vname = path[1].clone();
                    match self.enum_variant_tag(&ename, &vname) {
                        Some(tag) => {
                            let mut parts = vec![format!(".tag = {tag}")];
                            if !field_list.is_empty() {
                                let mut fparts = Vec::new();
                                for (n, v) in &field_list {
                                    let cv = self.expr(*v);
                                    fparts.push(format!(".{n} = {cv}"));
                                }
                                parts.push(format!(".data.{vname} = {{{}}}", fparts.join(", ")));
                            }
                            format!("(({ename}){{{}}})", parts.join(", "))
                        }
                        None => {
                            self.errors.push(format!("`{ename}` has no variant `{vname}`"));
                            "0".into()
                        }
                    }
                } else {
                    self.errors.push("construction path is too deep (stage0)".into());
                    "0".into()
                }
            }
            // value-position `if` → ternary over the branch values (each branch
            // is a block, lowered to a GNU statement-expression).
            ExprKind::If { cond, then_branch, else_branch } => {
                let (cond, then_branch, else_branch) = (*cond, *then_branch, *else_branch);
                let c = self.expr(cond);
                let t = self.expr(then_branch);
                let e = match else_branch {
                    Some(x) => self.expr(x),
                    None => "0".into(),
                };
                format!("(({c}) ? ({t}) : ({e}))")
            }
            // value-position block `{ ...; give v }` → GNU statement-expression.
            ExprKind::Block(block) => {
                let block = block.clone();
                self.emit_value_block(&block)
            }
            ExprKind::While { .. } | ExprKind::For { .. } => {
                self.errors
                    .push("`while` / `for` in value position is not supported by stage0 codegen yet".into());
                "0".into()
            }
            ExprKind::Match { .. } => {
                self.errors
                    .push("`match` in value position is not supported by stage0 codegen yet".into());
                "0".into()
            }
            ExprKind::Error => {
                self.errors.push("cannot generate code from a parse error".into());
                "0".into()
            }
        }
    }
}

/// Map a Plew type to its C spelling. Primitives map to fixed-width C types;
/// `Array[T]` maps to its monomorphized struct name; any other name is assumed
/// to be a declared struct/enum (its typedef name). Must agree with
/// [`Codegen::ty_c_name`] for the same type.
fn c_type(t: &Type) -> String {
    match t.name.as_str() {
        "I8" => "int8_t".to_string(),
        "I16" => "int16_t".to_string(),
        "I32" => "int32_t".to_string(),
        "I64" => "int64_t".to_string(),
        "U8" => "uint8_t".to_string(),
        "U16" => "uint16_t".to_string(),
        "U32" => "uint32_t".to_string(),
        "U64" => "uint64_t".to_string(),
        "F32" => "float".to_string(),
        "F64" => "double".to_string(),
        "Bool" => "int".to_string(),
        "String" => "PlewString".to_string(),
        "Array" if t.args.len() == 1 => format!("PlewArray_{}", mangle_type(&t.args[0])),
        other => other.to_string(),
    }
}

/// Whether a type name is a stage0 primitive (no nominal definition to order).
fn is_primitive_type(name: &str) -> bool {
    matches!(
        name,
        "I8" | "I16" | "I32" | "I64" | "U8" | "U16" | "U32" | "U64" | "F32" | "F64" | "Bool"
            | "String"
    )
}

/// C-identifier-safe mangling of a syntactic type (mirror of
/// [`Codegen::mangle`] on `Ty`, for use where only the AST type is available).
fn mangle_type(t: &Type) -> String {
    if t.name == "Array" && t.args.len() == 1 {
        format!("Arr_{}", mangle_type(&t.args[0]))
    } else {
        t.name.clone()
    }
}

/// Render a Plew string's decoded bytes as a C string literal plus its byte
/// length. Non-printable / non-ASCII bytes use 3-digit octal escapes (which,
/// unlike `\x`, are not greedy and so never merge with a following digit).
fn c_string_literal(s: &str) -> (String, usize) {
    let mut out = String::from("\"");
    for b in s.bytes() {
        match b {
            b'"' => out.push_str("\\\""),
            b'\\' => out.push_str("\\\\"),
            b'\n' => out.push_str("\\n"),
            b'\r' => out.push_str("\\r"),
            b'\t' => out.push_str("\\t"),
            0x20..=0x7e => out.push(b as char),
            _ => out.push_str(&format!("\\{b:03o}")),
        }
    }
    out.push('"');
    (out, s.len())
}

/// Map a binary operator to its C spelling, or `None` if stage0 can't lower it.
fn c_binop(op: BinOp) -> Option<&'static str> {
    use BinOp::*;
    Some(match op {
        Add => "+",
        Sub => "-",
        Mul => "*",
        Div => "/",
        Rem => "%",
        Shl => "<<",
        Shr => ">>",
        BitAnd => "&",
        BitXor => "^",
        BitOr => "|",
        Eq => "==",
        Ne => "!=",
        Lt => "<",
        Gt => ">",
        Le => "<=",
        Ge => ">=",
        And => "&&",
        Or => "||",
        // `??` and ranges have no direct C form; needs real lowering later.
        Coalesce | RangeHalf | RangeClosed => return None,
    })
}
