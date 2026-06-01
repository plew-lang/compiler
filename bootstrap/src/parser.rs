//! Hand-written recursive-descent parser (stage0).
//!
//! Expression parsing uses precedence climbing driven by [`infix_bp`], which
//! encodes the operator ladder from spec/12 (Rust-based, 14 levels). Only the
//! binary/unary/grouping core exists so far; `as`, postfix (call/field/index),
//! `try`/`await`, and statements/items follow.

use crate::ast::{
    Arg, Ast, BinOp, Block, ExprId, ExprKind, Field, Item, ItemId, ItemKind, MatchArm, Param, PatId,
    PatKind, Stmt, StmtKind, Type, UnOp, Variant, Vis,
};
use crate::lexer::lex;
use crate::span::Span;
use crate::token::{Keyword, Token, TokenKind};

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ParseError {
    pub msg: String,
    pub span: Span,
}

/// Parse a single expression from `src` (used by tests and, later, the REPL).
/// Returns the arena, the root expr, and any lex+parse errors.
pub fn parse_expr(src: &str) -> (Ast, ExprId, Vec<ParseError>) {
    let (tokens, lex_errors) = lex(src);
    let mut p = Parser::new(tokens);
    for e in lex_errors {
        p.errors.push(ParseError { msg: e.msg, span: e.span });
    }
    let root = p.expr_bp(0);
    p.expect_eof();
    (p.ast, root, p.errors)
}

/// Parse a whole program: a sequence of top-level items.
pub fn parse_program(src: &str) -> (Ast, Vec<ItemId>, Vec<ParseError>) {
    let (tokens, lex_errors) = lex(src);
    let mut p = Parser::new(tokens);
    for e in lex_errors {
        p.errors.push(ParseError { msg: e.msg, span: e.span });
    }
    let items = p.program();
    (p.ast, items, p.errors)
}

/// Associativity of an infix operator.
#[derive(Clone, Copy, PartialEq, Eq)]
enum Assoc {
    Left,
    Right,
    None,
}

/// Binding power (precedence) + associativity for an infix operator.
/// Higher precedence binds tighter. Levels leave room above for `as` (12),
/// prefix (13) and postfix (14).
fn infix_bp(op: BinOp) -> (u8, Assoc) {
    use BinOp::*;
    match op {
        Mul | Div | Rem => (11, Assoc::Left),
        Add | Sub => (10, Assoc::Left),
        Shl | Shr => (9, Assoc::Left),
        BitAnd => (8, Assoc::Left),
        BitXor => (7, Assoc::Left),
        BitOr => (6, Assoc::Left),
        Coalesce => (5, Assoc::Right),
        Eq | Ne | Lt | Gt | Le | Ge => (4, Assoc::None),
        And => (3, Assoc::Left),
        Or => (2, Assoc::Left),
        RangeHalf | RangeClosed => (1, Assoc::None),
    }
}

fn token_to_binop(kind: &TokenKind) -> Option<BinOp> {
    use TokenKind as T;
    Some(match kind {
        T::Star => BinOp::Mul,
        T::Slash => BinOp::Div,
        T::Percent => BinOp::Rem,
        T::Plus => BinOp::Add,
        T::Minus => BinOp::Sub,
        T::Shl => BinOp::Shl,
        T::Shr => BinOp::Shr,
        T::Amp => BinOp::BitAnd,
        T::Caret => BinOp::BitXor,
        T::Pipe => BinOp::BitOr,
        T::QuestionQuestion => BinOp::Coalesce,
        T::EqEq => BinOp::Eq,
        T::Ne => BinOp::Ne,
        T::Lt => BinOp::Lt,
        T::Gt => BinOp::Gt,
        T::Le => BinOp::Le,
        T::Ge => BinOp::Ge,
        T::AmpAmp => BinOp::And,
        T::PipePipe => BinOp::Or,
        T::DotDotLt => BinOp::RangeHalf,
        T::DotDotEq => BinOp::RangeClosed,
        _ => return None,
    })
}

/// Recognize an assignment operator. `Some(None)` is plain `=`; `Some(Some(op))`
/// is a compound assignment `OP=` (desugars to `target = target OP value`).
fn assign_op(kind: &TokenKind) -> Option<Option<BinOp>> {
    use TokenKind as T;
    Some(match kind {
        T::Eq => None,
        T::PlusEq => Some(BinOp::Add),
        T::MinusEq => Some(BinOp::Sub),
        T::StarEq => Some(BinOp::Mul),
        T::SlashEq => Some(BinOp::Div),
        T::PercentEq => Some(BinOp::Rem),
        T::AmpEq => Some(BinOp::BitAnd),
        T::PipeEq => Some(BinOp::BitOr),
        T::CaretEq => Some(BinOp::BitXor),
        T::ShlEq => Some(BinOp::Shl),
        T::ShrEq => Some(BinOp::Shr),
        _ => return None,
    })
}

struct Parser {
    tokens: Vec<Token>,
    pos: usize,
    ast: Ast,
    errors: Vec<ParseError>,
}

impl Parser {
    fn new(tokens: Vec<Token>) -> Self {
        Self { tokens, pos: 0, ast: Ast::new(), errors: Vec::new() }
    }

    // --- token cursor -----------------------------------------------------

    fn peek(&self) -> &TokenKind {
        &self.tokens[self.pos].kind
    }

    /// Look ahead `n` tokens (clamped to the trailing Eof).
    fn peek_nth(&self, n: usize) -> &TokenKind {
        let i = (self.pos + n).min(self.tokens.len() - 1);
        &self.tokens[i].kind
    }

    fn peek_span(&self) -> Span {
        self.tokens[self.pos].span
    }

    fn at_eof(&self) -> bool {
        matches!(self.peek(), TokenKind::Eof)
    }

    fn bump(&mut self) -> Token {
        let tok = self.tokens[self.pos].clone();
        if !self.at_eof() {
            self.pos += 1;
        }
        tok
    }

    fn error(&mut self, span: Span, msg: impl Into<String>) {
        self.errors.push(ParseError { msg: msg.into(), span });
    }

    fn expect_eof(&mut self) {
        if !self.at_eof() {
            let span = self.peek_span();
            self.error(span, "unexpected trailing tokens after expression");
        }
    }

    // --- expressions ------------------------------------------------------

    /// Precedence-climbing core: parse an expression whose operators bind at
    /// least `min_bp`.
    fn expr_bp(&mut self, min_bp: u8) -> ExprId {
        let mut lhs = self.unary();

        loop {
            let Some(op) = token_to_binop(self.peek()) else { break };
            let (bp, assoc) = infix_bp(op);
            if bp < min_bp {
                break;
            }
            let op_span = self.peek_span();
            self.bump();

            let next_min = match assoc {
                Assoc::Left | Assoc::None => bp + 1,
                Assoc::Right => bp,
            };
            let rhs = self.expr_bp(next_min);
            let span = self.ast.expr(lhs).span.merge(self.ast.expr(rhs).span);
            lhs = self.ast.alloc_expr(ExprKind::Binary { op, lhs, rhs }, span);

            // Non-associative operators (comparison, range) may not chain.
            if assoc == Assoc::None {
                if let Some(next) = token_to_binop(self.peek()) {
                    if infix_bp(next).0 == bp {
                        let span = self.peek_span();
                        self.error(
                            span.merge(op_span),
                            "this operator is non-associative; add parentheses",
                        );
                        break;
                    }
                }
            }
        }

        lhs
    }

    /// Prefix unary operators, then a primary.
    fn unary(&mut self) -> ExprId {
        let op = match self.peek() {
            TokenKind::Minus => Some(UnOp::Neg),
            TokenKind::Bang => Some(UnOp::Not),
            TokenKind::Tilde => Some(UnOp::BitNot),
            _ => None,
        };
        if let Some(op) = op {
            let start = self.peek_span();
            self.bump();
            let operand = self.unary();
            let span = start.merge(self.ast.expr(operand).span);
            // NB: `-<intlit>` stays as Unary(Neg, Int); the spec's literal
            // folding (`-128: I8`) is handled later at const/type resolution,
            // since postfix binds tighter than prefix `-`.
            return self.ast.alloc_expr(ExprKind::Unary { op, operand }, span);
        }
        self.postfix()
    }

    /// Postfix chain (highest precedence): field access, indexing, calls.
    /// `-a.b` is `-(a.b)` because this runs inside `unary`'s operand.
    fn postfix(&mut self) -> ExprId {
        let mut base = self.primary();
        loop {
            match self.peek() {
                TokenKind::Dot => {
                    self.bump();
                    let name_span = self.peek_span();
                    let name = match self.peek().clone() {
                        TokenKind::Ident(s) => {
                            self.bump();
                            s
                        }
                        _ => {
                            self.error(name_span, "expected a field name after `.`");
                            String::new()
                        }
                    };
                    let span = self.ast.expr(base).span.merge(name_span);
                    base = self.ast.alloc_expr(ExprKind::Field { base, name }, span);
                }
                TokenKind::LBracket => {
                    self.bump();
                    let index = self.expr_bp(0);
                    let end = self.peek_span();
                    if matches!(self.peek(), TokenKind::RBracket) {
                        self.bump();
                    } else {
                        self.error(end, "expected `]`");
                    }
                    let span = self.ast.expr(base).span.merge(end);
                    base = self.ast.alloc_expr(ExprKind::Index { base, index }, span);
                }
                TokenKind::LParen => {
                    self.bump();
                    let args = self.call_args();
                    let end = self.peek_span();
                    if matches!(self.peek(), TokenKind::RParen) {
                        self.bump();
                    } else {
                        self.error(end, "expected `)`");
                    }
                    let span = self.ast.expr(base).span.merge(end);
                    base = self.ast.alloc_expr(ExprKind::Call { callee: base, args }, span);
                }
                _ => break,
            }
        }
        base
    }

    /// Parse a comma-separated argument list up to (but not consuming) `)`.
    /// Each arg is `label: expr` or a bare `expr`. A trailing comma is allowed.
    fn call_args(&mut self) -> Vec<Arg> {
        let mut args = Vec::new();
        while !matches!(self.peek(), TokenKind::RParen | TokenKind::Eof) {
            // `label: expr` — a leading `ident :` that is not `::`.
            let label = if let TokenKind::Ident(name) = self.peek().clone() {
                if matches!(self.peek_nth(1), TokenKind::Colon) {
                    self.bump(); // ident
                    self.bump(); // :
                    Some(name)
                } else {
                    None
                }
            } else {
                None
            };
            let value = self.expr_bp(0);
            args.push(Arg { label, value });
            if matches!(self.peek(), TokenKind::Comma) {
                self.bump();
            } else {
                break;
            }
        }
        args
    }

    // --- items / statements ----------------------------------------------

    fn program(&mut self) -> Vec<ItemId> {
        let mut items = Vec::new();
        self.eat_newlines();
        while !self.at_eof() {
            match self.item() {
                Some(item) => items.push(item),
                None => self.recover_to_newline(),
            }
            self.eat_newlines();
        }
        items
    }

    fn item(&mut self) -> Option<ItemId> {
        // optional `export` modifier (module-boundary visibility), ignored by
        // stage0 for now.
        if matches!(self.peek(), TokenKind::Kw(Keyword::Export)) {
            self.bump();
        }
        match self.peek() {
            TokenKind::Kw(Keyword::Fn) => Some(self.fn_item()),
            TokenKind::Kw(Keyword::Struct) => Some(self.struct_item()),
            TokenKind::Kw(Keyword::Enum) => Some(self.enum_item()),
            other => {
                let span = self.peek_span();
                self.error(span, format!("expected an item (e.g. `fn`, `struct`, `enum`), found {other:?}"));
                None
            }
        }
    }

    fn struct_item(&mut self) -> ItemId {
        let start = self.peek_span();
        self.bump(); // `struct`
        let name = self.expect_ident("a struct name");
        let generics = self.parse_generics();
        self.reject_where();
        self.expect(&TokenKind::LBrace, "`{` to start the struct body");
        let fields = self.parse_fields();
        let end = self.peek_span();
        self.expect(&TokenKind::RBrace, "`}` to close the struct");
        self.ast.alloc_item(Item {
            kind: ItemKind::Struct { name, generics, fields },
            span: start.merge(end),
        })
    }

    fn enum_item(&mut self) -> ItemId {
        let start = self.peek_span();
        self.bump(); // `enum`
        let name = self.expect_ident("an enum name");
        let generics = self.parse_generics();
        self.reject_where();
        self.expect(&TokenKind::LBrace, "`{` to start the enum body");
        self.eat_newlines();
        let mut variants = Vec::new();
        while !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof) {
            variants.push(self.parse_variant());
            if !self.eat_item_separator() {
                break;
            }
        }
        let end = self.peek_span();
        self.expect(&TokenKind::RBrace, "`}` to close the enum");
        self.ast.alloc_item(Item {
            kind: ItemKind::Enum { name, generics, variants },
            span: start.merge(end),
        })
    }

    fn parse_variant(&mut self) -> Variant {
        let start = self.peek_span();
        let name = self.expect_ident("a variant name");
        let mut fields = Vec::new();
        let mut end = start;
        if matches!(self.peek(), TokenKind::LBrace) {
            self.bump();
            fields = self.parse_fields();
            end = self.peek_span();
            self.expect(&TokenKind::RBrace, "`}` to close the variant fields");
        }
        Variant { name, fields, span: start.merge(end) }
    }

    /// Parse `[ field (sep field)* ]` up to (and consuming) the closing `}`'s
    /// caller. Used for both struct and variant bodies. Stops at `}`.
    fn parse_fields(&mut self) -> Vec<Field> {
        self.eat_newlines();
        let mut fields = Vec::new();
        while !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof) {
            fields.push(self.parse_field());
            if !self.eat_item_separator() {
                break;
            }
        }
        fields
    }

    fn parse_field(&mut self) -> Field {
        let start = self.peek_span();
        let vis = self.parse_vis();
        let mutable = if matches!(self.peek(), TokenKind::Kw(Keyword::Mut)) {
            self.bump();
            true
        } else {
            false
        };
        self.expect(&TokenKind::Kw(Keyword::Val), "`val` in a field declaration");
        let name = self.expect_ident("a field name");
        self.expect(&TokenKind::Colon, "`:` after the field name");
        let ty = self.ty();
        let default = if matches!(self.peek(), TokenKind::Eq) {
            self.bump();
            Some(self.expr_bp(0))
        } else {
            None
        };
        let span = start.merge(ty.span);
        Field { vis, mutable, name, ty, default, span }
    }

    fn parse_vis(&mut self) -> Vis {
        if !matches!(self.peek(), TokenKind::Kw(Keyword::Pub)) {
            return Vis::Private;
        }
        self.bump(); // `pub`
        if matches!(self.peek(), TokenKind::LParen) {
            self.bump();
            let is_get = matches!(self.peek(), TokenKind::Ident(s) if s == "get");
            if is_get {
                self.bump();
            } else {
                let s = self.peek_span();
                self.error(s, "expected `get` in `pub(get)`");
            }
            self.expect(&TokenKind::RParen, "`)` after `pub(get)`");
            Vis::PubGet
        } else {
            Vis::Pub
        }
    }

    fn parse_generics(&mut self) -> Vec<String> {
        let mut g = Vec::new();
        if matches!(self.peek(), TokenKind::LBracket) {
            self.bump();
            while !matches!(self.peek(), TokenKind::RBracket | TokenKind::Eof) {
                g.push(self.expect_ident("a generic parameter name"));
                if matches!(self.peek(), TokenKind::Comma) {
                    self.bump();
                } else {
                    break;
                }
            }
            self.expect(&TokenKind::RBracket, "`]` to close generic parameters");
        }
        g
    }

    fn reject_where(&mut self) {
        if matches!(self.peek(), TokenKind::Kw(Keyword::Where)) {
            let s = self.peek_span();
            self.error(s, "`where` clauses are not supported by stage0 yet");
            while !matches!(self.peek(), TokenKind::LBrace | TokenKind::Eof) {
                self.bump();
            }
        }
    }

    /// Consume a separator (newline(s) or `,`) between fields/variants.
    /// Returns false if the next token is the closer (caller should stop).
    fn eat_item_separator(&mut self) -> bool {
        match self.peek() {
            TokenKind::Newline => {
                self.eat_newlines();
                true
            }
            TokenKind::Comma => {
                self.bump();
                self.eat_newlines();
                true
            }
            TokenKind::RBrace => false,
            _ => {
                let s = self.peek_span();
                self.error(s, "expected a newline, `,`, or `}`");
                self.recover_to_newline();
                self.eat_newlines();
                !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof)
            }
        }
    }

    fn fn_item(&mut self) -> ItemId {
        let start = self.peek_span();
        self.bump(); // `fn`
        let name = self.expect_ident("a function name");
        self.expect(&TokenKind::LParen, "`(` after the function name");
        let params = self.params();
        self.expect(&TokenKind::RParen, "`)` after the parameters");
        let ret = if matches!(self.peek(), TokenKind::Arrow) {
            self.bump();
            Some(self.ty())
        } else {
            None
        };
        let body = self.block();
        let span = start.merge(body.span);
        self.ast.alloc_item(Item { kind: ItemKind::Fn { name, params, ret, body }, span })
    }

    fn params(&mut self) -> Vec<Param> {
        let mut out = Vec::new();
        while !matches!(self.peek(), TokenKind::RParen | TokenKind::Eof) {
            let start = self.peek_span();
            let label = self.expect_ident("a parameter label");
            let suppressed = if matches!(self.peek(), TokenKind::TildeColon) {
                self.bump();
                true
            } else {
                self.expect(&TokenKind::Colon, "`:` after the parameter label");
                false
            };
            let ty = self.ty();
            let span = start.merge(ty.span);
            out.push(Param { label, suppressed, ty, span });
            if matches!(self.peek(), TokenKind::Comma) {
                self.bump();
            } else {
                break;
            }
        }
        out
    }

    fn ty(&mut self) -> Type {
        let start = self.peek_span();
        let name = self.expect_ident("a type name");
        let mut args = Vec::new();
        let mut end = start;
        if matches!(self.peek(), TokenKind::LBracket) {
            self.bump();
            while !matches!(self.peek(), TokenKind::RBracket | TokenKind::Eof) {
                args.push(self.ty());
                if matches!(self.peek(), TokenKind::Comma) {
                    self.bump();
                } else {
                    break;
                }
            }
            end = self.peek_span();
            self.expect(&TokenKind::RBracket, "`]` to close the type arguments");
        }
        Type { name, args, span: start.merge(end) }
    }

    fn block(&mut self) -> Block {
        let start = self.peek_span();
        if !self.expect(&TokenKind::LBrace, "`{` to start a block") {
            return Block { stmts: Vec::new(), span: start };
        }
        let mut stmts = Vec::new();
        self.eat_newlines();
        while !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof) {
            stmts.push(self.stmt());
            match self.peek() {
                TokenKind::Newline => self.eat_newlines(),
                TokenKind::RBrace => break,
                _ => {
                    let span = self.peek_span();
                    self.error(span, "expected a newline or `}` after the statement");
                    self.recover_to_newline();
                    self.eat_newlines();
                }
            }
        }
        let end = self.peek_span();
        self.expect(&TokenKind::RBrace, "`}` to close the block");
        Block { stmts, span: start.merge(end) }
    }

    fn stmt(&mut self) -> crate::ast::StmtId {
        let start = self.peek_span();
        match self.peek() {
            TokenKind::Kw(Keyword::Val) => self.let_stmt(false, start),
            TokenKind::Kw(Keyword::Mut) => {
                self.bump(); // `mut`
                if matches!(self.peek(), TokenKind::Kw(Keyword::Val)) {
                    self.let_stmt(true, start)
                } else {
                    let span = self.peek_span();
                    self.error(span, "expected `val` after `mut`");
                    let value = self.expr_bp(0);
                    self.ast.alloc_stmt(Stmt { kind: StmtKind::Expr(value), span: start })
                }
            }
            TokenKind::Kw(Keyword::Break) => {
                self.bump();
                self.ast.alloc_stmt(Stmt { kind: StmtKind::Break, span: start })
            }
            TokenKind::Kw(Keyword::Continue) => {
                self.bump();
                self.ast.alloc_stmt(Stmt { kind: StmtKind::Continue, span: start })
            }
            TokenKind::Kw(Keyword::Give) => {
                self.bump(); // `give`
                let value = self.expr_bp(0);
                let span = start.merge(self.ast.expr(value).span);
                self.ast.alloc_stmt(Stmt { kind: StmtKind::Give(value), span })
            }
            TokenKind::Kw(Keyword::Return) => {
                self.bump(); // `return`
                let value = if matches!(
                    self.peek(),
                    TokenKind::Newline | TokenKind::RBrace | TokenKind::Eof
                ) {
                    None
                } else {
                    Some(self.expr_bp(0))
                };
                let span = match value {
                    Some(e) => start.merge(self.ast.expr(e).span),
                    None => start,
                };
                self.ast.alloc_stmt(Stmt { kind: StmtKind::Return(value), span })
            }
            _ => {
                let target = self.expr_bp(0);
                if let Some(op) = assign_op(self.peek()) {
                    self.bump();
                    let value = self.expr_bp(0);
                    let span = start.merge(self.ast.expr(value).span);
                    self.ast.alloc_stmt(Stmt {
                        kind: StmtKind::Assign { target, op, value },
                        span,
                    })
                } else {
                    let span = start.merge(self.ast.expr(target).span);
                    self.ast.alloc_stmt(Stmt { kind: StmtKind::Expr(target), span })
                }
            }
        }
    }

    /// `val`/`mut val` binding. Cursor is at `val` (after an optional `mut`).
    fn let_stmt(&mut self, mutable: bool, start: Span) -> crate::ast::StmtId {
        self.bump(); // `val`
        let name = self.expect_ident("a variable name");
        let ty = if matches!(self.peek(), TokenKind::Colon) {
            self.bump();
            Some(self.ty())
        } else {
            None
        };
        self.expect(&TokenKind::Eq, "`=` in a binding");
        let value = self.expr_bp(0);
        let span = start.merge(self.ast.expr(value).span);
        self.ast.alloc_stmt(Stmt { kind: StmtKind::Let { mutable, name, ty, value }, span })
    }

    /// `if cond { .. } (else (if .. | { .. }))?` as an expression.
    fn parse_if(&mut self) -> ExprId {
        let start = self.peek_span();
        self.bump(); // `if`
        let cond = self.expr_bp(0);
        let then_block = self.block();
        let then_span = then_block.span;
        let then_branch = self.ast.alloc_expr(ExprKind::Block(then_block), then_span);
        let else_branch = if matches!(self.peek(), TokenKind::Kw(Keyword::Else)) {
            self.bump();
            if matches!(self.peek(), TokenKind::Kw(Keyword::If)) {
                Some(self.parse_if())
            } else {
                let b = self.block();
                let sp = b.span;
                Some(self.ast.alloc_expr(ExprKind::Block(b), sp))
            }
        } else {
            None
        };
        let end = match else_branch {
            Some(e) => self.ast.expr(e).span,
            None => then_span,
        };
        self.ast.alloc_expr(ExprKind::If { cond, then_branch, else_branch }, start.merge(end))
    }

    /// `match scrutinee { pat => body  ... }`.
    fn parse_match(&mut self) -> ExprId {
        let start = self.peek_span();
        self.bump(); // `match`
        let scrutinee = self.expr_bp(0);
        self.expect(&TokenKind::LBrace, "`{` to start the match body");
        self.eat_newlines();
        let mut arms = Vec::new();
        while !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof) {
            let astart = self.peek_span();
            let pat = self.parse_pattern();
            self.expect(&TokenKind::FatArrow, "`=>` after the pattern");
            let body = self.expr_bp(0);
            let span = astart.merge(self.ast.expr(body).span);
            arms.push(MatchArm { pat, body, span });
            if !self.eat_item_separator() {
                break;
            }
        }
        let end = self.peek_span();
        self.expect(&TokenKind::RBrace, "`}` to close the match");
        self.ast.alloc_expr(ExprKind::Match { scrutinee, arms }, start.merge(end))
    }

    fn parse_pattern(&mut self) -> PatId {
        let span = self.peek_span();
        match self.peek().clone() {
            TokenKind::Int(s) => {
                self.bump();
                self.ast.alloc_pat(PatKind::Int(s), span)
            }
            TokenKind::Str(s) => {
                self.bump();
                self.ast.alloc_pat(PatKind::Str(s), span)
            }
            TokenKind::Kw(Keyword::True) => {
                self.bump();
                self.ast.alloc_pat(PatKind::Bool(true), span)
            }
            TokenKind::Kw(Keyword::False) => {
                self.bump();
                self.ast.alloc_pat(PatKind::Bool(false), span)
            }
            TokenKind::Kw(Keyword::Val) => {
                self.bump();
                let name = self.expect_ident("a binding name after `val`");
                self.ast.alloc_pat(PatKind::Binding { mutable: false, name }, span)
            }
            TokenKind::Kw(Keyword::Mut) => {
                self.bump();
                self.expect(&TokenKind::Kw(Keyword::Val), "`val` after `mut`");
                let name = self.expect_ident("a binding name after `mut val`");
                self.ast.alloc_pat(PatKind::Binding { mutable: true, name }, span)
            }
            TokenKind::Ident(name) if name == "_" => {
                self.bump();
                self.ast.alloc_pat(PatKind::Wildcard, span)
            }
            TokenKind::Ident(_) => self.parse_variant_pattern(span),
            other => {
                self.error(span, format!("expected a pattern, found {other:?}"));
                if !self.at_eof() {
                    self.bump();
                }
                self.ast.alloc_pat(PatKind::Wildcard, span)
            }
        }
    }

    fn parse_variant_pattern(&mut self, start: Span) -> PatId {
        let mut path = vec![self.expect_ident("a variant name")];
        while matches!(self.peek(), TokenKind::Dot) {
            self.bump();
            path.push(self.expect_ident("a name after `.`"));
        }
        let mut fields = Vec::new();
        let mut end = start;
        if matches!(self.peek(), TokenKind::LBrace) {
            self.bump();
            self.eat_newlines();
            while !matches!(self.peek(), TokenKind::RBrace | TokenKind::Eof) {
                fields.push(self.parse_pattern_field());
                if !self.eat_item_separator() {
                    break;
                }
            }
            end = self.peek_span();
            self.expect(&TokenKind::RBrace, "`}` to close the variant pattern fields");
        }
        self.ast.alloc_pat(PatKind::Variant { path, fields }, start.merge(end))
    }

    /// `field: subpattern` or punning `val name` / `mut val name`.
    fn parse_pattern_field(&mut self) -> (String, PatId) {
        if let TokenKind::Ident(name) = self.peek().clone() {
            if matches!(self.peek_nth(1), TokenKind::Colon) {
                self.bump(); // name
                self.bump(); // :
                let pat = self.parse_pattern();
                return (name, pat);
            }
        }
        // punning: the field name is the binding's name
        let pat = self.parse_pattern();
        let name = match &self.ast.pat(pat).kind {
            PatKind::Binding { name, .. } => name.clone(),
            _ => {
                let s = self.ast.pat(pat).span;
                self.error(s, "expected `field: pattern` or a `val name` punning binding");
                String::new()
            }
        };
        (name, pat)
    }

    /// JSX construction `<Type field=expr ... />` (or `<Type.Variant ... />`).
    fn parse_jsx(&mut self) -> ExprId {
        let start = self.peek_span();
        self.bump(); // `<`
        let mut path = vec![self.expect_ident("a type name in `<...>`")];
        while matches!(self.peek(), TokenKind::Dot) {
            self.bump();
            path.push(self.expect_ident("a name after `.` in `<...>`"));
        }
        self.eat_newlines();
        let mut fields = Vec::new();
        loop {
            match self.peek() {
                TokenKind::SlashGt | TokenKind::Eof => break,
                TokenKind::Ident(_) => {
                    let name = self.expect_ident("an attribute name");
                    self.expect(&TokenKind::Eq, "`=` after the attribute name");
                    let value = self.expr_bp(0);
                    fields.push((name, value));
                    self.eat_newlines();
                }
                _ => {
                    let s = self.peek_span();
                    self.error(s, "expected an attribute or `/>`");
                    break;
                }
            }
        }
        let end = self.peek_span();
        self.expect(&TokenKind::SlashGt, "`/>` to close the construction");
        self.ast.alloc_expr(ExprKind::New { path, fields }, start.merge(end))
    }

    /// `for val name in iter { .. }` as an expression (yields `()`).
    fn parse_for(&mut self) -> ExprId {
        let start = self.peek_span();
        self.bump(); // `for`
        let mutable = if matches!(self.peek(), TokenKind::Kw(Keyword::Mut)) {
            self.bump();
            true
        } else {
            false
        };
        self.expect(&TokenKind::Kw(Keyword::Val), "`val` after `for`");
        let var = self.expect_ident("a loop variable name");
        self.expect(&TokenKind::Kw(Keyword::In), "`in` after the loop variable");
        let iter = self.expr_bp(0);
        let body_block = self.block();
        let sp = body_block.span;
        let body = self.ast.alloc_expr(ExprKind::Block(body_block), sp);
        self.ast.alloc_expr(ExprKind::For { var, mutable, iter, body }, start.merge(sp))
    }

    /// Array literal `[e0, e1, ...]` (or empty `[]`). A trailing comma is ok.
    /// Dictionary literals `[k: v]` are not supported by stage0 yet.
    fn parse_array(&mut self, start: Span) -> ExprId {
        self.bump(); // `[`
        self.eat_newlines();
        let mut elems = Vec::new();
        while !matches!(self.peek(), TokenKind::RBracket | TokenKind::Eof) {
            let e = self.expr_bp(0);
            if matches!(self.peek(), TokenKind::Colon) {
                let s = self.peek_span();
                self.error(s, "dictionary literals are not supported by stage0 yet");
            }
            elems.push(e);
            self.eat_newlines();
            if matches!(self.peek(), TokenKind::Comma) {
                self.bump();
                self.eat_newlines();
            } else {
                break;
            }
        }
        let end = self.peek_span();
        self.expect(&TokenKind::RBracket, "`]` to close the array literal");
        self.ast.alloc_expr(ExprKind::Array(elems), start.merge(end))
    }

    /// `while cond { .. }` as an expression (yields `()`).
    fn parse_while(&mut self) -> ExprId {
        let start = self.peek_span();
        self.bump(); // `while`
        let cond = self.expr_bp(0);
        let body_block = self.block();
        let sp = body_block.span;
        let body = self.ast.alloc_expr(ExprKind::Block(body_block), sp);
        self.ast.alloc_expr(ExprKind::While { cond, body }, start.merge(sp))
    }

    // --- small helpers ----------------------------------------------------

    fn eat_newlines(&mut self) {
        while matches!(self.peek(), TokenKind::Newline) {
            self.bump();
        }
    }

    fn recover_to_newline(&mut self) {
        while !matches!(self.peek(), TokenKind::Newline | TokenKind::Eof) {
            self.bump();
        }
    }

    fn expect_ident(&mut self, ctx: &str) -> String {
        if let TokenKind::Ident(s) = self.peek().clone() {
            self.bump();
            s
        } else {
            let span = self.peek_span();
            self.error(span, format!("expected {ctx}"));
            String::new()
        }
    }

    /// Consume a token equal to `want`, or record an error. Returns success.
    fn expect(&mut self, want: &TokenKind, ctx: &str) -> bool {
        if self.peek() == want {
            self.bump();
            true
        } else {
            let span = self.peek_span();
            self.error(span, format!("expected {ctx}"));
            false
        }
    }

    fn primary(&mut self) -> ExprId {
        let span = self.peek_span();
        match self.peek().clone() {
            TokenKind::Int(s) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Int(s), span)
            }
            TokenKind::Float(s) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Float(s), span)
            }
            TokenKind::Str(s) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Str(s), span)
            }
            TokenKind::Ident(s) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Ident(s), span)
            }
            TokenKind::Kw(Keyword::True) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Bool(true), span)
            }
            TokenKind::Kw(Keyword::False) => {
                self.bump();
                self.ast.alloc_expr(ExprKind::Bool(false), span)
            }
            TokenKind::Kw(Keyword::If) => self.parse_if(),
            TokenKind::Kw(Keyword::While) => self.parse_while(),
            TokenKind::Kw(Keyword::For) => self.parse_for(),
            TokenKind::Kw(Keyword::Match) => self.parse_match(),
            TokenKind::Lt => self.parse_jsx(),
            TokenKind::LBracket => self.parse_array(span),
            TokenKind::LBrace => {
                let block = self.block();
                let sp = block.span;
                self.ast.alloc_expr(ExprKind::Block(block), sp)
            }
            TokenKind::LParen => {
                self.bump();
                let inner = self.expr_bp(0);
                if matches!(self.peek(), TokenKind::RParen) {
                    self.bump();
                } else {
                    let s = self.peek_span();
                    self.error(s, "expected `)`");
                }
                inner
            }
            other => {
                if !self.at_eof() {
                    self.bump();
                }
                self.error(span, format!("expected an expression, found {other:?}"));
                self.ast.alloc_expr(ExprKind::Error, span)
            }
        }
    }
}
