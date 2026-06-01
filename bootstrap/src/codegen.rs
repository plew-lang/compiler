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
    let mut cg =
        Codegen { ast, items, expr_ty, table, out: String::new(), errors: Vec::new(), tmp: 0 };
    cg.out.push_str("#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\n");
    // stage0 String: immutable view over a (literal) UTF-8 buffer.
    cg.out.push_str("typedef struct { const char* data; int64_t len; } PlewString;\n\n");
    // type definitions first (C needs types declared before use)
    for &id in items {
        match ast.item(id).kind {
            ItemKind::Struct { .. } => cg.emit_struct(id),
            ItemKind::Enum { .. } => cg.emit_enum(id),
            ItemKind::Fn { .. } => {}
        }
    }
    // Monomorphized array types + their (leaked) runtime, one per element type.
    cg.emit_arrays();
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
}

impl Codegen<'_> {
    fn emit_item(&mut self, id: ItemId) {
        match &self.ast.item(id).kind {
            ItemKind::Fn { name, params, ret, body } => {
                let is_main = name == "main";
                if is_main {
                    self.out.push_str("int main(void) {\n");
                } else {
                    let rty = match ret {
                        Some(t) => c_type(t),
                        None => "void".to_string(),
                    };
                    self.out.push_str(&rty);
                    self.out.push(' ');
                    self.out.push_str(name);
                    self.out.push('(');
                    if params.is_empty() {
                        self.out.push_str("void");
                    } else {
                        for (i, p) in params.iter().enumerate() {
                            if i > 0 {
                                self.out.push_str(", ");
                            }
                            self.out.push_str(&c_type(&p.ty));
                            self.out.push(' ');
                            self.out.push_str(&p.label);
                        }
                    }
                    self.out.push_str(") {\n");
                }
                let stmts: Vec<StmtId> = body.stmts.clone();
                for sid in stmts {
                    self.emit_stmt(sid, is_main);
                }
                if is_main {
                    self.out.push_str("    return 0;\n");
                }
                self.out.push_str("}\n\n");
            }
            ItemKind::Struct { .. } | ItemKind::Enum { .. } => {} // emitted in the typedef pass
        }
    }

    fn emit_struct(&mut self, id: ItemId) {
        let ItemKind::Struct { name, fields, generics } = &self.ast.item(id).kind else {
            return;
        };
        if !generics.is_empty() {
            self.errors.push("generic struct codegen is not supported by stage0 yet".into());
            return;
        }
        let name = name.clone();
        let fields: Vec<(String, Type)> =
            fields.iter().map(|f| (f.name.clone(), f.ty.clone())).collect();
        self.out.push_str("typedef struct {\n");
        for (fname, fty) in &fields {
            let cty = c_type(fty);
            self.out.push_str(&format!("    {cty} {fname};\n"));
        }
        self.out.push_str(&format!("}} {name};\n\n"));
    }

    fn emit_enum(&mut self, id: ItemId) {
        let ItemKind::Enum { name, variants, generics } = &self.ast.item(id).kind else {
            return;
        };
        if !generics.is_empty() {
            self.errors.push("generic enum codegen is not supported by stage0 yet".into());
            return;
        }
        let name = name.clone();
        let variants: Vec<(String, Vec<(String, Type)>)> = variants
            .iter()
            .map(|v| (v.name.clone(), v.fields.iter().map(|f| (f.name.clone(), f.ty.clone())).collect()))
            .collect();
        // Tagged union: an `int tag` plus a union of the variants that carry data.
        self.out.push_str("typedef struct {\n    int tag;\n");
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
        self.out.push_str(&format!("}} {name};\n\n"));
    }

    /// Emit a monomorphized array struct + its (leaked) runtime for every
    /// interned `Array[T]`. Memory is never freed — fine for a throwaway
    /// stage0 that runs once per compilation.
    fn emit_arrays(&mut self) {
        for id in 0..self.table.array_elems.len() as u32 {
            let elem = self.table.array_elem(id);
            let at = self.array_c_name(id);
            let et = self.ty_c_name(elem);
            self.out.push_str(&format!(
                "typedef struct {{ {et}* data; int64_t len; int64_t cap; }} {at};\n"
            ));
            self.out.push_str(&format!(
                "static {at} {at}_new(void) {{ {at} a; a.data = 0; a.len = 0; a.cap = 0; return a; }}\n"
            ));
            self.out.push_str(&format!(
                "static {et} {at}_get({at} a, int64_t i) {{ if (i < 0 || i >= a.len) {{ fprintf(stderr, \"panic: index out of range\\n\"); exit(1); }} return a.data[i]; }}\n\n"
            ));
        }
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

    /// Lower a statement-position `match`. Enum scrutinees switch on the tag;
    /// integer/Bool scrutinees become an if-chain. (Value-position `match` is
    /// not supported by stage0 yet.)
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
            self.out.push_str(&format!("    switch ({tname}.tag) {{\n"));
            for arm in arms {
                self.emit_enum_arm(&ename, &tname, arm, in_main);
            }
            self.out.push_str("    }\n");
        } else if is_value {
            self.out.push_str(&format!("    int64_t {tname} = {scrut};\n"));
            self.emit_value_arms(&tname, arms, in_main);
        } else {
            self.errors
                .push("match with only wildcard arms is not supported by stage0 codegen yet".into());
        }
    }

    fn emit_enum_arm(&mut self, ename: &str, tname: &str, arm: &MatchArm, in_main: bool) {
        let body = arm.body;
        match &self.ast.pat(arm.pat).kind {
            PatKind::Variant { path, fields } => {
                let vname = path.last().cloned().unwrap_or_default();
                let fields: Vec<(String, crate::ast::PatId)> =
                    fields.iter().map(|(n, p)| (n.clone(), *p)).collect();
                let tag = self.enum_variant_tag(ename, &vname).unwrap_or(0);
                self.out.push_str(&format!("        case {tag}: {{\n"));
                for (fname, fpat) in &fields {
                    match &self.ast.pat(*fpat).kind {
                        PatKind::Binding { name, .. } => {
                            let name = name.clone();
                            let cty = self
                                .enum_field_ctype(ename, &vname, fname)
                                .unwrap_or_else(|| "int64_t".into());
                            self.out.push_str(&format!(
                                "            {cty} {name} = {tname}.data.{vname}.{fname};\n"
                            ));
                        }
                        PatKind::Wildcard => {}
                        _ => self.errors.push(
                            "nested patterns inside variant fields are not supported by stage0 codegen yet".into(),
                        ),
                    }
                }
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("            break;\n        }\n");
            }
            PatKind::Wildcard => {
                self.out.push_str("        default: {\n");
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("            break;\n        }\n");
            }
            PatKind::Binding { name, .. } => {
                let name = name.clone();
                self.out.push_str("        default: {\n");
                self.out.push_str(&format!("            {ename} {name} = {tname};\n"));
                self.emit_expr_stmt(body, in_main);
                self.out.push_str("            break;\n        }\n");
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
            ExprKind::Ident(s) => s.clone(),
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
                let l = self.expr(*lhs);
                let r = self.expr(*rhs);
                match c_binop(*op) {
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
                // Non-print call: emit positional C call (labels ignored for now).
                let callee_c = self.expr(*callee);
                let arg_ids: Vec<ExprId> = args.iter().map(|a| a.value).collect();
                let parts: Vec<String> = arg_ids.iter().map(|&a| self.expr(a)).collect();
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
