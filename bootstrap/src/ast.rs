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

#[derive(Clone, Copy, PartialEq, Eq, Debug, Hash)]
pub struct PatId(pub u32);

#[derive(Clone, Debug, Default)]
pub struct Ast {
    exprs: Vec<Expr>,
    stmts: Vec<Stmt>,
    items: Vec<Item>,
    pats: Vec<Pattern>,
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

    pub fn alloc_pat(&mut self, kind: PatKind, span: Span) -> PatId {
        let id = PatId(self.pats.len() as u32);
        self.pats.push(Pattern { kind, span });
        id
    }

    pub fn pat(&self, id: PatId) -> &Pattern {
        &self.pats[id.0 as usize]
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
    /// A `{ ... }` block used as an expression (its value comes from `give`).
    Block(Block),
    /// `if cond { .. } else { .. }`. `then_branch` is a `Block` expr; an
    /// `else_branch` is a `Block` expr or another `If` (for `else if`).
    If {
        cond: ExprId,
        then_branch: ExprId,
        else_branch: Option<ExprId>,
    },
    /// `while cond { .. }`. `body` is a `Block` expr. Yields `()`.
    While { cond: ExprId, body: ExprId },
    /// JSX construction `<Type field=expr ... />`. `path` is the dotted type
    /// path (`["Point"]`, or `["Color","Red"]` for an enum variant).
    New {
        path: Vec<String>,
        fields: Vec<(String, ExprId)>,
    },
    /// `match scrutinee { pat => body  ... }`.
    Match {
        scrutinee: ExprId,
        arms: Vec<MatchArm>,
    },
    /// Placeholder inserted on a parse error so parsing can continue.
    Error,
}

#[derive(Clone, Debug)]
pub struct MatchArm {
    pub pat: PatId,
    pub body: ExprId,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub struct Pattern {
    pub kind: PatKind,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum PatKind {
    /// `_`
    Wildcard,
    /// `val name` / `mut val name`
    Binding { mutable: bool, name: String },
    Int(String),
    Bool(bool),
    Str(String),
    /// `Enum.Variant` or `Enum.Variant { field: subpat, .. }`.
    Variant {
        path: Vec<String>,
        fields: Vec<(String, PatId)>,
    },
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
    /// `give expr` — yields the enclosing block's value.
    Give(ExprId),
    /// Assignment `target = value`, or compound `target OP= value` (op = Some).
    Assign {
        target: ExprId,
        op: Option<BinOp>,
        value: ExprId,
    },
    /// An expression used as a statement.
    Expr(ExprId),
}

#[derive(Clone, Debug)]
pub struct Item {
    pub kind: ItemKind,
    pub span: Span,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Vis {
    Private,
    Pub,
    /// `pub(get)`: public read, private write.
    PubGet,
}

/// A struct field or an enum-variant field.
#[derive(Clone, Debug)]
pub struct Field {
    pub vis: Vis,
    pub mutable: bool,
    pub name: String,
    pub ty: Type,
    pub default: Option<ExprId>,
    pub span: Span,
}

/// An enum variant: `Name` (no fields) or `Name { val f: T, .. }`.
#[derive(Clone, Debug)]
pub struct Variant {
    pub name: String,
    pub fields: Vec<Field>,
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
    Struct {
        name: String,
        generics: Vec<String>,
        fields: Vec<Field>,
    },
    Enum {
        name: String,
        generics: Vec<String>,
        variants: Vec<Variant>,
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
            ExprKind::Block(block) => self.write_block(block, out),
            ExprKind::If { cond, then_branch, else_branch } => {
                out.push_str("(if ");
                self.write_sexpr(*cond, out);
                out.push(' ');
                self.write_sexpr(*then_branch, out);
                if let Some(e) = else_branch {
                    out.push(' ');
                    self.write_sexpr(*e, out);
                }
                out.push(')');
            }
            ExprKind::While { cond, body } => {
                out.push_str("(while ");
                self.write_sexpr(*cond, out);
                out.push(' ');
                self.write_sexpr(*body, out);
                out.push(')');
            }
            ExprKind::New { path, fields } => {
                out.push_str("(new ");
                out.push_str(&path.join("."));
                for (name, val) in fields {
                    out.push(' ');
                    out.push_str(name);
                    out.push('=');
                    self.write_sexpr(*val, out);
                }
                out.push(')');
            }
            ExprKind::Match { scrutinee, arms } => {
                out.push_str("(match ");
                self.write_sexpr(*scrutinee, out);
                for arm in arms {
                    out.push_str(" (=> ");
                    self.write_pat(arm.pat, out);
                    out.push(' ');
                    self.write_sexpr(arm.body, out);
                    out.push(')');
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
            ItemKind::Struct { name, generics, fields } => {
                out.push_str("(struct ");
                out.push_str(name);
                write_generics(generics, out);
                for f in fields {
                    out.push(' ');
                    self.write_field(f, out);
                }
                out.push(')');
            }
            ItemKind::Enum { name, generics, variants } => {
                out.push_str("(enum ");
                out.push_str(name);
                write_generics(generics, out);
                for v in variants {
                    out.push_str(" (variant ");
                    out.push_str(&v.name);
                    for f in &v.fields {
                        out.push(' ');
                        self.write_field(f, out);
                    }
                    out.push(')');
                }
                out.push(')');
            }
        }
    }

    fn write_pat(&self, id: PatId, out: &mut String) {
        match &self.pat(id).kind {
            PatKind::Wildcard => out.push('_'),
            PatKind::Binding { mutable, name } => {
                out.push_str(if *mutable { "(mutval " } else { "(val " });
                out.push_str(name);
                out.push(')');
            }
            PatKind::Int(s) => out.push_str(s),
            PatKind::Bool(b) => out.push_str(if *b { "true" } else { "false" }),
            PatKind::Str(s) => {
                out.push('"');
                out.push_str(s);
                out.push('"');
            }
            PatKind::Variant { path, fields } => {
                out.push_str(&path.join("."));
                if !fields.is_empty() {
                    out.push('{');
                    for (i, (n, p)) in fields.iter().enumerate() {
                        if i > 0 {
                            out.push_str(", ");
                        }
                        out.push_str(n);
                        out.push('=');
                        self.write_pat(*p, out);
                    }
                    out.push('}');
                }
            }
        }
    }

    fn write_field(&self, f: &Field, out: &mut String) {
        out.push_str("(field");
        match f.vis {
            Vis::Pub => out.push_str(" pub"),
            Vis::PubGet => out.push_str(" pubget"),
            Vis::Private => {}
        }
        if f.mutable {
            out.push_str(" mut");
        }
        out.push(' ');
        out.push_str(&f.name);
        out.push(':');
        self.write_type(&f.ty, out);
        out.push(')');
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
            StmtKind::Give(e) => {
                out.push_str("(give ");
                self.write_sexpr(*e, out);
                out.push(')');
            }
            StmtKind::Assign { target, op, value } => {
                out.push('(');
                if let Some(o) = op {
                    out.push_str(o.symbol());
                }
                out.push_str("= ");
                self.write_sexpr(*target, out);
                out.push(' ');
                self.write_sexpr(*value, out);
                out.push(')');
            }
            StmtKind::Expr(e) => self.write_sexpr(*e, out),
        }
    }
}

fn write_generics(generics: &[String], out: &mut String) {
    if !generics.is_empty() {
        out.push('[');
        for (i, g) in generics.iter().enumerate() {
            if i > 0 {
                out.push_str(", ");
            }
            out.push_str(g);
        }
        out.push(']');
    }
}
