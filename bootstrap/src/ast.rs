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

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
pub struct StmtId(pub u32);

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
pub struct ItemId(pub u32);

#[derive(Clone, Debug, Default)]
pub struct Ast {
    exprs: Vec<Expr>,
    stmts: Vec<Stmt>,
    items: Vec<Item>,
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

    pub fn alloc_stmt(&mut self, stmt: Stmt) -> StmtId {
        let id = StmtId(self.stmts.len() as u32);
        self.stmts.push(stmt);
        id
    }

    pub fn stmt(&self, id: StmtId) -> &Stmt {
        &self.stmts[id.0 as usize]
    }

    pub fn alloc_item(&mut self, item: Item) -> ItemId {
        let id = ItemId(self.items.len() as u32);
        self.items.push(item);
        id
    }

    pub fn item(&self, id: ItemId) -> &Item {
        &self.items[id.0 as usize]
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
    /// Field access `base.name` (named only; no positional tuple indexing).
    Field { base: ExprId, name: String },
    /// Index `base[index]`.
    Index { base: ExprId, index: ExprId },
    /// Call `callee(args)`. Method calls are `Call { callee: Field { .. } }`.
    Call { callee: ExprId, args: Vec<Arg> },
    /// Placeholder inserted on a parse error so parsing can continue.
    Error,
}

/// A call argument. Plew requires labels except where suppressed with `~:`;
/// that requirement is a later semantic check, so `label` is optional here.
#[derive(Clone, Debug)]
pub struct Arg {
    pub label: Option<String>,
    pub value: ExprId,
}

// --- types, statements, items -------------------------------------------

/// A type reference, e.g. `I32`, `Array[I32]`, `Dictionary[String, I32]`.
/// (Function types, `any P`, etc. are added later.)
#[derive(Clone, Debug)]
pub struct Type {
    pub name: String,
    pub args: Vec<Type>,
    pub span: Span,
}

/// A function parameter `label: Type` (or `label~: Type` to suppress the label).
#[derive(Clone, Debug)]
pub struct Param {
    pub label: String,
    /// `~:` label suppression (positional call site).
    pub suppressed: bool,
    pub ty: Type,
    pub span: Span,
}

/// A `{ ... }` block: newline-separated statements.
#[derive(Clone, Debug)]
pub struct Block {
    pub stmts: Vec<StmtId>,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub struct Stmt {
    pub kind: StmtKind,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum StmtKind {
    /// `val name = expr` / `mut val name = expr`, with optional type annotation.
    Let {
        mutable: bool,
        name: String,
        ty: Option<Type>,
        value: ExprId,
    },
    /// `return expr?`
    Return(Option<ExprId>),
    /// An expression used as a statement.
    Expr(ExprId),
}

#[derive(Clone, Debug)]
pub struct Item {
    pub kind: ItemKind,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum ItemKind {
    Fn {
        name: String,
        params: Vec<Param>,
        ret: Option<Type>,
        body: Block,
    },
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
            ExprKind::Field { base, name } => {
                out.push_str("(. ");
                self.write_sexpr(*base, out);
                out.push(' ');
                out.push_str(name);
                out.push(')');
            }
            ExprKind::Index { base, index } => {
                out.push_str("([] ");
                self.write_sexpr(*base, out);
                out.push(' ');
                self.write_sexpr(*index, out);
                out.push(')');
            }
            ExprKind::Call { callee, args } => {
                out.push_str("(call ");
                self.write_sexpr(*callee, out);
                for arg in args {
                    out.push(' ');
                    if let Some(label) = &arg.label {
                        out.push_str(label);
                        out.push(':');
                    }
                    self.write_sexpr(arg.value, out);
                }
                out.push(')');
            }
            ExprKind::Error => out.push_str("<error>"),
        }
    }

    /// Render an item as an S-expression (for tests).
    pub fn dump_item(&self, id: ItemId) -> String {
        let mut out = String::new();
        self.write_item(id, &mut out);
        out
    }

    fn write_item(&self, id: ItemId, out: &mut String) {
        match &self.item(id).kind {
            ItemKind::Fn { name, params, ret, body } => {
                out.push_str("(fn ");
                out.push_str(name);
                out.push_str(" (");
                for (i, p) in params.iter().enumerate() {
                    if i > 0 {
                        out.push(' ');
                    }
                    out.push_str(&p.label);
                    if p.suppressed {
                        out.push('~');
                    }
                    out.push(':');
                    self.write_type(&p.ty, out);
                }
                out.push(')');
                if let Some(ret) = ret {
                    out.push_str(" -> ");
                    self.write_type(ret, out);
                }
                out.push(' ');
                self.write_block(body, out);
                out.push(')');
            }
        }
    }

    fn write_type(&self, ty: &Type, out: &mut String) {
        out.push_str(&ty.name);
        if !ty.args.is_empty() {
            out.push('[');
            for (i, a) in ty.args.iter().enumerate() {
                if i > 0 {
                    out.push_str(", ");
                }
                self.write_type(a, out);
            }
            out.push(']');
        }
    }

    fn write_block(&self, block: &Block, out: &mut String) {
        out.push_str("(block");
        for &sid in &block.stmts {
            out.push(' ');
            self.write_stmt(sid, out);
        }
        out.push(')');
    }

    fn write_stmt(&self, id: StmtId, out: &mut String) {
        match &self.stmt(id).kind {
            StmtKind::Let { mutable, name, ty, value } => {
                out.push_str(if *mutable { "(mutval " } else { "(val " });
                out.push_str(name);
                if let Some(ty) = ty {
                    out.push(':');
                    self.write_type(ty, out);
                }
                out.push(' ');
                self.write_sexpr(*value, out);
                out.push(')');
            }
            StmtKind::Return(Some(e)) => {
                out.push_str("(return ");
                self.write_sexpr(*e, out);
                out.push(')');
            }
            StmtKind::Return(None) => out.push_str("(return)"),
            StmtKind::Expr(e) => self.write_sexpr(*e, out),
        }
    }
}
