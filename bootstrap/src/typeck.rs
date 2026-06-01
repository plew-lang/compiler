//! Minimal type checker (stage0).
//!
//! Bidirectional: an *expected* type is pushed down so polymorphic numeric
//! literals are resolved from context (annotation, operand, parameter, return).
//! A numeric literal with no expected numeric type is an error — Plew has **no
//! default numeric type** (spec/02). This closes the gap where stage0 silently
//! treated everything as i64.
//!
//! Scope: the currently-implemented language subset (numeric/Bool, arithmetic,
//! comparison, `if`/`while`, bindings, calls, the `print` builtin). Strings,
//! arrays, structs, enums, generics, traits come later.

use std::collections::HashMap;

use crate::ast::{Ast, BinOp, Block, ExprId, ExprKind, ItemId, ItemKind, StmtKind, Type, UnOp};
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
    pub fn name(self) -> &'static str {
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

/// Type-check a whole program. Returns all type errors (empty = well-typed).
pub fn check(ast: &Ast, items: &[ItemId]) -> Vec<TypeError> {
    let mut errors = Vec::new();
    let mut sigs: HashMap<String, FnSig> = HashMap::new();

    // Pass 1: collect function signatures (params/return are always explicit).
    // struct/enum are parsed but not yet type-checked by stage0.
    for &id in items {
        if let ItemKind::Fn { name, params, ret, .. } = &ast.item(id).kind {
            let param_tys = params
                .iter()
                .map(|p| resolve_ty(&p.ty, &mut errors))
                .collect();
            let ret_ty = match ret {
                Some(t) => resolve_ty(t, &mut errors),
                None => Ty::Unit,
            };
            sigs.insert(name.clone(), FnSig { params: param_tys, ret: ret_ty });
        }
    }

    // Pass 2: check each body.
    for &id in items {
        if let ItemKind::Fn { name, params, body, .. } = &ast.item(id).kind {
            let ret = sigs.get(name).map(|s| s.ret).unwrap_or(Ty::Error);
            let mut cx = Checker { ast, sigs: &sigs, errors: &mut errors, scopes: Vec::new(), ret };
            cx.push_scope();
            for p in params {
                let ty = resolve_ty(&p.ty, cx.errors);
                cx.define(&p.label, ty);
            }
            cx.check_block(body);
            cx.pop_scope();
        }
    }

    errors
}

/// Resolve a syntactic type to a [`Ty`]. Only primitives are known so far.
fn resolve_ty(t: &Type, errors: &mut Vec<TypeError>) -> Ty {
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
        other => {
            errors.push(TypeError {
                span: t.span,
                msg: format!("unknown type `{other}` (stage0 supports primitive numeric types and Bool)"),
            });
            Ty::Error
        }
    };
    if !t.args.is_empty() && ty != Ty::Error {
        errors.push(TypeError {
            span: t.span,
            msg: format!("type `{}` does not take type arguments", t.name),
        });
    }
    ty
}

struct Checker<'a> {
    ast: &'a Ast,
    sigs: &'a HashMap<String, FnSig>,
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
                let expected = ty.as_ref().map(|t| resolve_ty(t, self.errors));
                let vty = self.check_expr(value, expected);
                // The variable's type is the annotation if present, else inferred.
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
                            self.error(
                                span,
                                format!("`return` with no value, but the function returns `{}`", self.ret.name()),
                            );
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
                    self.error(span, format!("compound assignment requires a numeric type, found `{}`", tty.name()));
                }
                let vty = self.check_expr(value, Some(tty));
                if tty != Ty::Error && vty != Ty::Error && tty != vty {
                    self.error(span, format!("cannot assign `{}` to `{}`", vty.name(), tty.name()));
                }
            }
            StmtKind::Expr(e) => {
                let e = *e;
                self.check_expr(e, None);
            }
        }
    }

    /// Check `e` against an optional expected type; returns its type.
    /// Synthesizes via [`Self::infer_expr`] then verifies against `expected`
    /// (so e.g. a `while` condition of type `I64` is rejected even though the
    /// `Ident` arm itself ignores the expected type).
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
                    self.error(span, format!("expected `{}`, found an integer literal (use a decimal point for floats)", t.name()));
                    Ty::Error
                }
                Some(t) => {
                    self.error(span, format!("expected `{}`, found an integer literal", t.name()));
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
                    self.error(span, format!("expected `{}`, found a float literal", t.name()));
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
                            self.error(span, format!("unary `-` requires a signed numeric type, found `{}`", t.name()));
                        }
                        t
                    }
                    UnOp::BitNot => {
                        let t = self.check_expr(operand, expected);
                        if t != Ty::Error && !t.is_integer() {
                            self.error(span, format!("`~` requires an integer type, found `{}`", t.name()));
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
                let args: Vec<_> = args.iter().map(|a| (a.label.clone(), a.value)).collect();
                self.check_call(callee, &args, span)
            }
            ExprKind::If { cond, then_branch, else_branch } => {
                let (cond, then_branch, else_branch) = (*cond, *then_branch, *else_branch);
                self.check_expr(cond, Some(Ty::Bool));
                // Value position requires both branches to produce `expected`.
                let want = match expected {
                    Some(t) if t != Ty::Unit => Some(t),
                    _ => None,
                };
                let tty = self.check_expr(then_branch, want);
                match else_branch {
                    Some(e) => {
                        let ety = self.check_expr(e, want.or(Some(tty)));
                        if want.is_some() { want.unwrap() } else if tty == ety { tty } else { Ty::Unit }
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
            ExprKind::Field { .. } | ExprKind::Index { .. } => {
                self.error(span, "field access / indexing is not supported by the stage0 type checker yet");
                Ty::Error
            }
            ExprKind::New { .. } => {
                self.error(span, "construction `<...>` is not supported by the stage0 type checker yet");
                Ty::Error
            }
            ExprKind::Error => Ty::Error,
        }
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
                    self.error(span, format!("operator `{}` requires numeric operands, found `{}`", op.symbol(), lt.name()));
                    return Ty::Error;
                }
                if lt != rt {
                    self.error(span, format!("operator `{}` operand types differ: `{}` vs `{}`", op.symbol(), lt.name(), rt.name()));
                    return Ty::Error;
                }
                lt
            }
            Eq | Ne | Lt | Gt | Le | Ge => {
                let lt = self.check_expr(lhs, None);
                let rt = self.check_expr(rhs, Some(lt));
                if lt != Ty::Error && rt != Ty::Error && lt != rt {
                    self.error(span, format!("comparison operand types differ: `{}` vs `{}`", lt.name(), rt.name()));
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

    fn check_call(&mut self, callee: ExprId, args: &[(Option<String>, ExprId)], span: Span) -> Ty {
        // `print(<int>)` builtin (stage0): pins the argument to I64.
        if let ExprKind::Ident(name) = &self.ast.expr(callee).kind {
            let name = name.clone();
            if name == "print" {
                if args.len() != 1 {
                    self.error(span, "`print` takes exactly one argument (stage0)");
                } else {
                    let t = self.check_expr(args[0].1, Some(Ty::I64));
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
                for (i, (_label, value)) in args.iter().enumerate() {
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
                self.error(span, format!("expected `{}`, found `{}`", e.name(), actual.name()));
            }
        }
    }
}
