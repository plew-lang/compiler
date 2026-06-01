//! Lexer tests. We assert on token *kinds* (spans are checked separately) by
//! lexing a snippet and collecting the non-EOF kinds.

use plewc::lexer::lex;
use plewc::token::{Keyword, TokenKind};

fn kinds(src: &str) -> Vec<TokenKind> {
    let (toks, errs) = lex(src);
    assert!(errs.is_empty(), "unexpected lex errors: {errs:?}");
    let mut k: Vec<TokenKind> = toks.into_iter().map(|t| t.kind).collect();
    assert_eq!(k.pop(), Some(TokenKind::Eof), "stream must end with Eof");
    k
}

fn id(s: &str) -> TokenKind {
    TokenKind::Ident(s.to_string())
}

#[test]
fn empty_source_is_just_eof() {
    let (toks, errs) = lex("   \n\t  ");
    assert!(errs.is_empty());
    assert_eq!(toks.len(), 1);
    assert_eq!(toks[0].kind, TokenKind::Eof);
}

#[test]
fn identifiers_and_keywords() {
    use Keyword::*;
    assert_eq!(
        kinds("fn main val x mut struct"),
        vec![
            TokenKind::Kw(Fn),
            id("main"),
            TokenKind::Kw(Val),
            id("x"),
            TokenKind::Kw(Mut),
            TokenKind::Kw(Struct),
        ]
    );
}

#[test]
fn contextual_keywords_stay_idents() {
    // `factory`, `via`, `result`, `optional` are contextual: lexed as Ident.
    assert_eq!(
        kinds("factory via result optional assoc"),
        vec![id("factory"), id("via"), id("result"), id("optional"), id("assoc")]
    );
}

#[test]
fn integer_and_float_literals() {
    assert_eq!(
        kinds("0 42 1_000 0xFF 0b1010 0o17"),
        vec![
            TokenKind::Int("0".into()),
            TokenKind::Int("42".into()),
            TokenKind::Int("1_000".into()),
            TokenKind::Int("0xFF".into()),
            TokenKind::Int("0b1010".into()),
            TokenKind::Int("0o17".into()),
        ]
    );
    assert_eq!(
        kinds("1.5 3.0e10 2.0E-3"),
        vec![
            TokenKind::Float("1.5".into()),
            TokenKind::Float("3.0e10".into()),
            TokenKind::Float("2.0E-3".into()),
        ]
    );
}

#[test]
fn dot_after_int_is_not_a_float() {
    // `1.foo` => Int(1) Dot Ident(foo); ranges stay intact too.
    assert_eq!(
        kinds("1.foo"),
        vec![TokenKind::Int("1".into()), TokenKind::Dot, id("foo")]
    );
    assert_eq!(
        kinds("0..<10"),
        vec![TokenKind::Int("0".into()), TokenKind::DotDotLt, TokenKind::Int("10".into())]
    );
    assert_eq!(
        kinds("0..=10"),
        vec![TokenKind::Int("0".into()), TokenKind::DotDotEq, TokenKind::Int("10".into())]
    );
}

#[test]
fn string_literal_with_escapes() {
    assert_eq!(
        kinds(r#""hello\n\t\"world\"""#),
        vec![TokenKind::Str("hello\n\t\"world\"".into())]
    );
}

#[test]
fn maximal_munch_operators() {
    use TokenKind::*;
    assert_eq!(
        kinds("-> => :: .. ..< ..= ?? ?. ~: == != <= >= && || << >> <<= >>="),
        vec![
            Arrow, FatArrow, ColonColon, DotDot, DotDotLt, DotDotEq, QuestionQuestion,
            QuestionDot, TildeColon, EqEq, Ne, Le, Ge, AmpAmp, PipePipe, Shl, Shr, ShlEq, ShrEq,
        ]
    );
    assert_eq!(
        kinds("+ - * / % += -= *= /= %= & | ^ &= |= ^="),
        vec![
            Plus, Minus, Star, Slash, Percent, PlusEq, MinusEq, StarEq, SlashEq, PercentEq, Amp,
            Pipe, Caret, AmpEq, PipeEq, CaretEq,
        ]
    );
}

#[test]
fn selectors_and_jsx_punct() {
    use TokenKind::*;
    // method-source selector `#`, view-strip `#!`, import root `@`.
    assert_eq!(kinds("a#P b#!Ext @Std"), vec![id("a"), Hash, id("P"), id("b"), HashBang, id("Ext"), At, id("Std")]);
    // JSX `<S x=42 />` lexes to its component punctuation.
    assert_eq!(
        kinds("<S x=42 />"),
        vec![Lt, id("S"), id("x"), Eq, Int("42".into()), Slash, Gt]
    );
}

#[test]
fn comments_are_trivia() {
    // newline after `a` becomes a statement terminator (Go-style)
    assert_eq!(
        kinds("a // line\nb /* block /* nested */ */ c"),
        vec![id("a"), TokenKind::Newline, id("b"), id("c")]
    );
}

#[test]
fn newline_terminates_after_value_token() {
    use TokenKind::*;
    // newline after an identifier/literal/`)`/`}` terminates the statement
    assert_eq!(kinds("a\nb"), vec![id("a"), Newline, id("b")]);
    assert_eq!(kinds("1\n2"), vec![Int("1".into()), Newline, Int("2".into())]);
    // consecutive blank lines collapse to a single terminator
    assert_eq!(kinds("a\n\n\nb"), vec![id("a"), Newline, id("b")]);
    // no terminator at start, or with only a trailing newline before EOF
    assert_eq!(kinds("\n\na"), vec![id("a")]);
    assert_eq!(kinds("a\n"), vec![id("a")]);
}

#[test]
fn newline_elided_after_operators_and_open_brackets() {
    use TokenKind::*;
    // line ending in an operator continues onto the next line
    assert_eq!(
        kinds("1 +\n2"),
        vec![Int("1".into()), Plus, Int("2".into())]
    );
    // open paren / comma elide the newline
    assert_eq!(
        kinds("f(\n  a,\n  b\n)"),
        vec![id("f"), LParen, id("a"), Comma, id("b"), RParen]
    );
    // but a newline after `)` terminates
    assert_eq!(kinds("f()\ng()"), vec![id("f"), LParen, RParen, Newline, id("g"), LParen, RParen]);
}

#[test]
fn spans_are_byte_accurate() {
    let (toks, errs) = lex("val  x");
    assert!(errs.is_empty());
    assert_eq!(toks[0].span.start, 0);
    assert_eq!(toks[0].span.end, 3); // "val"
    assert_eq!(toks[1].span.start, 5); // after two spaces
    assert_eq!(toks[1].span.end, 6);
}

#[test]
fn reports_unterminated_string() {
    let (_toks, errs) = lex(r#""oops"#);
    assert_eq!(errs.len(), 1);
    assert!(errs[0].msg.contains("unterminated string"));
}
