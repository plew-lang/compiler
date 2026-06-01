//! Tokens produced by the lexer.
//!
//! Hard keywords get their own [`Keyword`] variant. Contextual keywords
//! (`factory`, `optional`, `result`, `via`, `assoc`, `get`, `set`,
//! `defaultExtension`, `allowUnique`, `noLocal`, ...) are NOT recognized here —
//! they arrive as [`TokenKind::Ident`] and are matched by the parser in the
//! positions where they are meaningful, so they remain usable as identifiers
//! elsewhere.

use crate::span::Span;

#[derive(Clone, PartialEq, Eq, Debug)]
pub struct Token {
    pub kind: TokenKind,
    pub span: Span,
}

impl Token {
    pub fn new(kind: TokenKind, span: Span) -> Self {
        Self { kind, span }
    }
}

#[derive(Clone, PartialEq, Eq, Debug)]
pub enum TokenKind {
    // Literals & names
    Ident(String),
    /// Raw integer literal text (digits, possibly with `_`/radix prefix).
    /// Numeric literals are polymorphic in Plew; the type is resolved later.
    Int(String),
    /// Raw float literal text.
    Float(String),
    /// Decoded string literal contents (escapes processed).
    Str(String),

    Kw(Keyword),

    // Grouping
    LParen,   // (
    RParen,   // )
    LBracket, // [
    RBracket, // ]
    LBrace,   // {
    RBrace,   // }

    // Punctuation
    Comma,      // ,
    Semi,       // ;
    Colon,      // :
    ColonColon, // ::
    Dot,        // .
    DotDot,     // ..
    DotDotLt,   // ..<
    DotDotEq,   // ..=
    Arrow,      // ->
    FatArrow,   // =>
    At,         // @
    Hash,       // #
    HashBang,   // #!
    Question,   // ?
    QuestionDot,      // ?.
    QuestionQuestion, // ??
    Tilde,      // ~
    TildeColon, // ~:

    // Comparison / assignment
    Eq, // =
    EqEq, // ==
    Ne, // !=
    Lt, // <
    Gt, // >
    Le, // <=
    Ge, // >=

    // Arithmetic / bitwise
    Plus,    // +
    Minus,   // -
    Star,    // *
    Slash,   // /
    Percent, // %
    Amp,     // &
    Pipe,    // |
    Caret,   // ^
    Shl,     // <<
    Shr,     // >>
    AmpAmp,  // &&
    PipePipe,// ||
    Bang,    // !

    // Compound assignment
    PlusEq,    // +=
    MinusEq,   // -=
    StarEq,    // *=
    SlashEq,   // /=
    PercentEq, // %=
    AmpEq,     // &=
    PipeEq,    // |=
    CaretEq,   // ^=
    ShlEq,     // <<=
    ShrEq,     // >>=

    Eof,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Keyword {
    Fn,
    Val,
    Mut,
    Struct,
    Enum,
    Trait,
    Impl,
    Extension,
    If,
    Else,
    Match,
    For,
    While,
    Loop,
    Return,
    Give,
    Break,
    Continue,
    Try,
    Await,
    Async,
    Spawn,
    Move,
    Borrow,
    Inout,
    Unique,
    Local,
    Pub,
    Export,
    Import,
    Part,
    Panic,
    Test,
    As,
    Where,
    In,
    True,
    False,
}

impl Keyword {
    pub fn from_str(s: &str) -> Option<Keyword> {
        use Keyword::*;
        Some(match s {
            "fn" => Fn,
            "val" => Val,
            "mut" => Mut,
            "struct" => Struct,
            "enum" => Enum,
            "trait" => Trait,
            "impl" => Impl,
            "extension" => Extension,
            "if" => If,
            "else" => Else,
            "match" => Match,
            "for" => For,
            "while" => While,
            "loop" => Loop,
            "return" => Return,
            "give" => Give,
            "break" => Break,
            "continue" => Continue,
            "try" => Try,
            "await" => Await,
            "async" => Async,
            "spawn" => Spawn,
            "move" => Move,
            "borrow" => Borrow,
            "inout" => Inout,
            "unique" => Unique,
            "local" => Local,
            "pub" => Pub,
            "export" => Export,
            "import" => Import,
            "part" => Part,
            "panic" => Panic,
            "test" => Test,
            "as" => As,
            "where" => Where,
            "in" => In,
            "true" => True,
            "false" => False,
            _ => return None,
        })
    }
}
