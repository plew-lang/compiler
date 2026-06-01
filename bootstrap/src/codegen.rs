//! Minimal C code generator (stage0 walking skeleton).
//!
//! This is deliberately tiny: it assumes everything is a 64-bit integer, has no
//! type checking, and special-cases `print(<int>)` to `printf`. Its purpose is
//! to prove the whole spine — source → C → clang → run — end to end. Real type
//! lowering, the ARC runtime, strings, etc. replace it incrementally.

use crate::ast::{Ast, BinOp, ExprId, ExprKind, ItemId, ItemKind, StmtId, StmtKind, UnOp};

/// Generate a complete C translation unit for `items`, or a list of
/// "unsupported construct" errors if the program uses features the skeleton
/// codegen does not handle yet.
pub fn emit_c(ast: &Ast, items: &[ItemId]) -> Result<String, Vec<String>> {
    let mut cg = Codegen { ast, out: String::new(), errors: Vec::new() };
    cg.out.push_str("#include <stdio.h>\n#include <stdint.h>\n\n");
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
    out: String,
    errors: Vec<String>,
}

impl Codegen<'_> {
    fn emit_item(&mut self, id: ItemId) {
        match &self.ast.item(id).kind {
            ItemKind::Fn { name, params, ret: _, body } => {
                let is_main = name == "main";
                if is_main {
                    self.out.push_str("int main(void) {\n");
                } else {
                    // Skeleton: user functions take/return int64_t, labels ignored.
                    self.out.push_str("int64_t ");
                    self.out.push_str(name);
                    self.out.push('(');
                    if params.is_empty() {
                        self.out.push_str("void");
                    } else {
                        for (i, p) in params.iter().enumerate() {
                            if i > 0 {
                                self.out.push_str(", ");
                            }
                            self.out.push_str("int64_t ");
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
        }
    }

    fn emit_stmt(&mut self, id: StmtId, in_main: bool) {
        match &self.ast.stmt(id).kind {
            StmtKind::Let { name, value, .. } => {
                let name = name.clone();
                let v = self.expr(*value);
                self.out.push_str(&format!("    int64_t {name} = {v};\n"));
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

    /// Special-case `print(<expr>)` → `printf("%lld\n", (long long)(expr))`.
    fn try_emit_print(&mut self, id: ExprId) -> Option<String> {
        if let ExprKind::Call { callee, args } = &self.ast.expr(id).kind {
            if let ExprKind::Ident(name) = &self.ast.expr(*callee).kind {
                if name == "print" && args.len() == 1 && args[0].label.is_none() {
                    let v = self.expr(args[0].value);
                    return Some(format!("    printf(\"%lld\\n\", (long long)({v}));\n"));
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
            ExprKind::Str(_) => {
                self.errors.push("string literals are not supported by stage0 codegen yet".into());
                "0".into()
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
            ExprKind::Field { .. } | ExprKind::Index { .. } => {
                self.errors
                    .push("field access / indexing is not supported by stage0 codegen yet".into());
                "0".into()
            }
            ExprKind::If { .. } | ExprKind::Block(_) => {
                self.errors.push(
                    "`if` / block in value position is not supported by stage0 codegen yet".into(),
                );
                "0".into()
            }
            ExprKind::Error => {
                self.errors.push("cannot generate code from a parse error".into());
                "0".into()
            }
        }
    }
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
