//! Hand-written recursive-descent parser (stage0).
//!
//! Expression parsing uses precedence climbing driven by [`infix_bp`], which
//! encodes the operator ladder from spec/12 (Rust-based, 14 levels). Only the
//! binary/unary/grouping core exists so far; `as`, postfix (call/field/index),
//! `try`/`await`, and statements/items follow.

use crate::ast::{Arg, Ast, BinOp, ExprId, ExprKind, UnOp};
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
