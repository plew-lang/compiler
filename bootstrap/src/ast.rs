//! Abstract syntax tree.
//!
//! Nodes live in arenas inside [`Ast`] and reference each other by typed
//! indices ([`ExprId`], ...) rather than owning pointers. This sidesteps
//! Rust's borrow checker for tree/graph shapes, is cache-friendly, and maps
//! cleanly onto the arena design planned for the Plew self-host.
//!
//! Only expressions exist so far; statements / items / types / patterns get
//! their own arenas as the parser grows.

use crate::span::Span;

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
pub struct ExprId(pub u32);

#[derive(Clone, Debug, Default)]
pub struct Ast {
    exprs: Vec<Expr>,
}

impl Ast {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn alloc_expr(&mut self, kind: ExprKind, span: Span) -> ExprId {
        let id = ExprId(self.exprs.len() as u32);
        self.exprs.push(Expr { kind, span });
        id
    }

    pub fn expr(&self, id: ExprId) -> &Expr {
        &self.exprs[id.0 as usize]
    }

    pub fn expr_count(&self) -> usize {
        self.exprs.len()
    }
}

#[derive(Clone, Debug)]
pub struct Expr {
    pub kind: ExprKind,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum ExprKind {
    /// Raw integer literal text (polymorphic; type resolved later).
    Int(String),
    /// Raw float literal text.
    Float(String),
    /// Decoded string literal.
    Str(String),
    Bool(bool),
    /// A bare name reference (variable / function / type name).
    Ident(String),
    Unary { op: UnOp, operand: ExprId },
    Binary { op: BinOp, lhs: ExprId, rhs: ExprId },
    /// Placeholder inserted on a parse error so parsing can continue.
    Error,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum UnOp {
    Neg,    // -
    Not,    // !  (Bool)
    BitNot, // ~  (integer)
}

impl UnOp {
    pub fn symbol(self) -> &'static str {
        match self {
            UnOp::Neg => "-",
            UnOp::Not => "!",
            UnOp::BitNot => "~",
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum BinOp {
    Mul,
    Div,
    Rem,
    Add,
    Sub,
    Shl,
    Shr,
    BitAnd,
    BitXor,
    BitOr,
    Coalesce, // ??
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    And, // &&
    Or,  // ||
    RangeHalf,   // ..<
    RangeClosed, // ..=
}

impl BinOp {
    pub fn symbol(self) -> &'static str {
        use BinOp::*;
        match self {
            Mul => "*",
            Div => "/",
            Rem => "%",
            Add => "+",
            Sub => "-",
            Shl => "<<",
            Shr => ">>",
            BitAnd => "&",
            BitXor => "^",
            BitOr => "|",
            Coalesce => "??",
            Eq => "==",
            Ne => "!=",
            Lt => "<",
            Gt => ">",
            Le => "<=",
            Ge => ">=",
            And => "&&",
            Or => "||",
            RangeHalf => "..<",
            RangeClosed => "..=",
        }
    }
}

impl Ast {
    /// Render an expression as an S-expression, e.g. `(+ 1 (* 2 3))`.
    /// Used by tests to assert tree shape (and thus precedence/associativity).
    pub fn dump(&self, id: ExprId) -> String {
        let mut out = String::new();
        self.write_sexpr(id, &mut out);
        out
    }

    fn write_sexpr(&self, id: ExprId, out: &mut String) {
        match &self.expr(id).kind {
            ExprKind::Int(s) | ExprKind::Float(s) | ExprKind::Ident(s) => out.push_str(s),
            ExprKind::Str(s) => {
                out.push('"');
                out.push_str(s);
                out.push('"');
            }
            ExprKind::Bool(b) => out.push_str(if *b { "true" } else { "false" }),
            ExprKind::Unary { op, operand } => {
                out.push('(');
                out.push_str(op.symbol());
                out.push(' ');
                self.write_sexpr(*operand, out);
                out.push(')');
            }
            ExprKind::Binary { op, lhs, rhs } => {
                out.push('(');
                out.push_str(op.symbol());
                out.push(' ');
                self.write_sexpr(*lhs, out);
                out.push(' ');
                self.write_sexpr(*rhs, out);
                out.push(')');
            }
            ExprKind::Error => out.push_str("<error>"),
        }
    }
}
