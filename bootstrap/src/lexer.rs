//! Hand-written lexer for Plew (stage0).
//!
//! Operates on the source `&str` with a byte cursor, peeking by `char` so
//! multi-byte UTF-8 inside string literals is handled correctly while spans
//! stay as byte offsets.
//!
//! Not yet handled (tracked for later): string interpolation `"{ expr }"`,
//! raw/multiline strings, char literals. A `{` inside a string is currently
//! taken literally.

use crate::span::Span;
use crate::token::{Keyword, Token, TokenKind};

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct LexError {
    pub msg: String,
    pub span: Span,
}

pub fn lex(src: &str) -> (Vec<Token>, Vec<LexError>) {
    let mut lx = Lexer::new(src);
    let toks = lx.run();
    (toks, lx.errors)
}

struct Lexer<'a> {
    src: &'a str,
    /// Byte offset of the cursor.
    pos: usize,
    errors: Vec<LexError>,
}

impl<'a> Lexer<'a> {
    fn new(src: &'a str) -> Self {
        Self { src, pos: 0, errors: Vec::new() }
    }

    fn run(&mut self) -> Vec<Token> {
        let mut toks = Vec::new();
        loop {
            self.skip_trivia();
            let start = self.pos;
            match self.peek() {
                None => {
                    toks.push(Token::new(TokenKind::Eof, Span::point(self.pos as u32)));
                    break;
                }
                Some(c) => {
                    let kind = self.lex_token(c);
                    let span = Span::new(start as u32, self.pos as u32);
                    if let Some(kind) = kind {
                        toks.push(Token::new(kind, span));
                    }
                }
            }
        }
        toks
    }

    // --- cursor helpers ---------------------------------------------------

    fn peek(&self) -> Option<char> {
        self.src[self.pos..].chars().next()
    }

    fn peek2(&self) -> Option<char> {
        let mut it = self.src[self.pos..].chars();
        it.next();
        it.next()
    }

    fn bump(&mut self) -> Option<char> {
        let c = self.peek()?;
        self.pos += c.len_utf8();
        Some(c)
    }

    /// Consume `c` if it is next; report whether it matched.
    fn eat(&mut self, c: char) -> bool {
        if self.peek() == Some(c) {
            self.pos += c.len_utf8();
            true
        } else {
            false
        }
    }

    fn error(&mut self, start: usize, msg: impl Into<String>) {
        self.errors.push(LexError {
            msg: msg.into(),
            span: Span::new(start as u32, self.pos as u32),
        });
    }

    // --- trivia -----------------------------------------------------------

    fn skip_trivia(&mut self) {
        loop {
            match self.peek() {
                Some(c) if c.is_whitespace() => {
                    self.bump();
                }
                Some('/') if self.peek2() == Some('/') => {
                    // line comment
                    while let Some(c) = self.peek() {
                        if c == '\n' {
                            break;
                        }
                        self.bump();
                    }
                }
                Some('/') if self.peek2() == Some('*') => {
                    // block comment (nested, like Rust)
                    let start = self.pos;
                    self.bump();
                    self.bump();
                    let mut depth = 1u32;
                    while depth > 0 {
                        match self.bump() {
                            None => {
                                self.error(start, "unterminated block comment");
                                break;
                            }
                            Some('/') if self.peek() == Some('*') => {
                                self.bump();
                                depth += 1;
                            }
                            Some('*') if self.peek() == Some('/') => {
                                self.bump();
                                depth -= 1;
                            }
                            Some(_) => {}
                        }
                    }
                }
                _ => break,
            }
        }
    }

    // --- token dispatch ---------------------------------------------------

    /// Returns `None` only on a hard error where no token is produced.
    fn lex_token(&mut self, c: char) -> Option<TokenKind> {
        if is_ident_start(c) {
            return Some(self.lex_ident());
        }
        if c.is_ascii_digit() {
            return Some(self.lex_number());
        }
        if c == '"' {
            return Some(self.lex_string());
        }
        self.lex_punct(c)
    }

    fn lex_ident(&mut self) -> TokenKind {
        let start = self.pos;
        while let Some(c) = self.peek() {
            if is_ident_continue(c) {
                self.bump();
            } else {
                break;
            }
        }
        let text = &self.src[start..self.pos];
        match Keyword::from_str(text) {
            Some(kw) => TokenKind::Kw(kw),
            None => TokenKind::Ident(text.to_string()),
        }
    }

    fn lex_number(&mut self) -> TokenKind {
        let start = self.pos;
        // radix prefixes: 0x / 0b / 0o
        if self.peek() == Some('0') {
            if let Some(r) = self.peek2() {
                if matches!(r, 'x' | 'X' | 'b' | 'B' | 'o' | 'O') {
                    self.bump(); // 0
                    self.bump(); // radix letter
                    while let Some(c) = self.peek() {
                        if c.is_ascii_alphanumeric() || c == '_' {
                            self.bump();
                        } else {
                            break;
                        }
                    }
                    return TokenKind::Int(self.src[start..self.pos].to_string());
                }
            }
        }

        self.eat_digits();
        let mut is_float = false;

        // fractional part: only if a digit follows the dot (so `0..<10` and
        // `1.method()` are not eaten as floats).
        if self.peek() == Some('.') && self.peek2().map_or(false, |c| c.is_ascii_digit()) {
            is_float = true;
            self.bump(); // .
            self.eat_digits();
        }

        // exponent
        if matches!(self.peek(), Some('e' | 'E')) {
            is_float = true;
            self.bump();
            if matches!(self.peek(), Some('+' | '-')) {
                self.bump();
            }
            self.eat_digits();
        }

        let text = self.src[start..self.pos].to_string();
        if is_float {
            TokenKind::Float(text)
        } else {
            TokenKind::Int(text)
        }
    }

    fn eat_digits(&mut self) {
        while let Some(c) = self.peek() {
            if c.is_ascii_digit() || c == '_' {
                self.bump();
            } else {
                break;
            }
        }
    }

    fn lex_string(&mut self) -> TokenKind {
        let start = self.pos;
        self.bump(); // opening "
        let mut out = String::new();
        loop {
            match self.bump() {
                None => {
                    self.error(start, "unterminated string literal");
                    break;
                }
                Some('"') => break,
                Some('\\') => match self.bump() {
                    Some('n') => out.push('\n'),
                    Some('r') => out.push('\r'),
                    Some('t') => out.push('\t'),
                    Some('0') => out.push('\0'),
                    Some('\\') => out.push('\\'),
                    Some('"') => out.push('"'),
                    Some('{') => out.push('{'),
                    Some('}') => out.push('}'),
                    Some(other) => {
                        self.error(start, format!("unknown escape `\\{other}`"));
                        out.push(other);
                    }
                    None => {
                        self.error(start, "unterminated string literal");
                        break;
                    }
                },
                Some(c) => out.push(c),
            }
        }
        TokenKind::Str(out)
    }

    fn lex_punct(&mut self, c: char) -> Option<TokenKind> {
        use TokenKind::*;
        let start = self.pos;
        self.bump(); // consume `c`
        let kind = match c {
            '(' => LParen,
            ')' => RParen,
            '[' => LBracket,
            ']' => RBracket,
            '{' => LBrace,
            '}' => RBrace,
            ',' => Comma,
            ';' => Semi,
            ':' => {
                if self.eat(':') { ColonColon } else { Colon }
            }
            '.' => {
                if self.eat('.') {
                    if self.eat('<') { DotDotLt }
                    else if self.eat('=') { DotDotEq }
                    else { DotDot }
                } else {
                    Dot
                }
            }
            '-' => {
                if self.eat('>') { Arrow }
                else if self.eat('=') { MinusEq }
                else { Minus }
            }
            '=' => {
                if self.eat('>') { FatArrow }
                else if self.eat('=') { EqEq }
                else { Eq }
            }
            '@' => At,
            '#' => {
                if self.eat('!') { HashBang } else { Hash }
            }
            '?' => {
                if self.eat('?') { QuestionQuestion }
                else if self.eat('.') { QuestionDot }
                else { Question }
            }
            '~' => {
                if self.eat(':') { TildeColon } else { Tilde }
            }
            '!' => {
                if self.eat('=') { Ne } else { Bang }
            }
            '<' => {
                if self.eat('=') { Le }
                else if self.eat('<') {
                    if self.eat('=') { ShlEq } else { Shl }
                } else { Lt }
            }
            '>' => {
                if self.eat('=') { Ge }
                else if self.eat('>') {
                    if self.eat('=') { ShrEq } else { Shr }
                } else { Gt }
            }
            '+' => {
                if self.eat('=') { PlusEq } else { Plus }
            }
            '*' => {
                if self.eat('=') { StarEq } else { Star }
            }
            '/' => {
                if self.eat('=') { SlashEq } else { Slash }
            }
            '%' => {
                if self.eat('=') { PercentEq } else { Percent }
            }
            '&' => {
                if self.eat('&') { AmpAmp }
                else if self.eat('=') { AmpEq }
                else { Amp }
            }
            '|' => {
                if self.eat('|') { PipePipe }
                else if self.eat('=') { PipeEq }
                else { Pipe }
            }
            '^' => {
                if self.eat('=') { CaretEq } else { Caret }
            }
            other => {
                self.error(start, format!("unexpected character `{other}`"));
                return None;
            }
        };
        Some(kind)
    }
}

fn is_ident_start(c: char) -> bool {
    c == '_' || c.is_ascii_alphabetic()
}

fn is_ident_continue(c: char) -> bool {
    c == '_' || c.is_ascii_alphanumeric()
}
