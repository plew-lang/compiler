//! Expression parser tests. We parse a snippet and assert on the S-expression
//! dump of the resulting tree, which makes precedence/associativity explicit.

use plewc::parser::parse_expr;

/// Parse `src`, assert there are no errors, return the S-expr dump.
fn sexpr(src: &str) -> String {
    let (ast, root, errs) = parse_expr(src);
    assert!(errs.is_empty(), "unexpected parse errors for {src:?}: {errs:?}");
    ast.dump(root)
}

/// Parse `src` expecting at least one error; return the error messages.
fn errors(src: &str) -> Vec<String> {
    let (_ast, _root, errs) = parse_expr(src);
    assert!(!errs.is_empty(), "expected a parse error for {src:?}");
    errs.into_iter().map(|e| e.msg).collect()
}

#[test]
fn literals_and_idents() {
    assert_eq!(sexpr("42"), "42");
    assert_eq!(sexpr("3.14"), "3.14");
    assert_eq!(sexpr(r#""hi""#), "\"hi\"");
    assert_eq!(sexpr("true"), "true");
    assert_eq!(sexpr("false"), "false");
    assert_eq!(sexpr("foo"), "foo");
}

#[test]
fn arithmetic_precedence() {
    assert_eq!(sexpr("1 + 2 * 3"), "(+ 1 (* 2 3))");
    assert_eq!(sexpr("1 * 2 + 3"), "(+ (* 1 2) 3)");
    assert_eq!(sexpr("1 + 2 - 3"), "(- (+ 1 2) 3)"); // left assoc
    assert_eq!(sexpr("2 * 3 % 4"), "(% (* 2 3) 4)"); // same level, left assoc
}

#[test]
fn grouping_overrides_precedence() {
    assert_eq!(sexpr("(1 + 2) * 3"), "(* (+ 1 2) 3)");
    assert_eq!(sexpr("((42))"), "42");
}

#[test]
fn unary_prefix() {
    assert_eq!(sexpr("-5"), "(- 5)");
    assert_eq!(sexpr("!flag"), "(! flag)");
    assert_eq!(sexpr("~bits"), "(~ bits)");
    assert_eq!(sexpr("- -5"), "(- (- 5))");
    // prefix binds looser than `*`: -a * b == (-a) * b
    assert_eq!(sexpr("-a * b"), "(* (- a) b)");
}

#[test]
fn full_ladder_ordering() {
    // shift < add ; & < shift ; ^ < & ; | < ^
    assert_eq!(sexpr("1 + 2 << 3"), "(<< (+ 1 2) 3)");
    assert_eq!(sexpr("1 & 2 << 3"), "(& 1 (<< 2 3))");
    assert_eq!(sexpr("1 ^ 2 & 3"), "(^ 1 (& 2 3))");
    assert_eq!(sexpr("1 | 2 ^ 3"), "(| 1 (^ 2 3))");
    // ?? below bitor, above comparison, right-assoc
    assert_eq!(sexpr("a | b ?? c"), "(?? (| a b) c)");
    assert_eq!(sexpr("a ?? b ?? c"), "(?? a (?? b c))");
    // comparison below ?? ; && below comparison ; || below &&
    assert_eq!(sexpr("a ?? b == c"), "(== (?? a b) c)");
    assert_eq!(sexpr("a == b && c"), "(&& (== a b) c)");
    assert_eq!(sexpr("a && b || c"), "(|| (&& a b) c)");
}

#[test]
fn coalesce_is_weaker_than_arithmetic() {
    // spec/12: `count ?? 0 + 1` == `count ?? (0 + 1)`
    assert_eq!(sexpr("count ?? 0 + 1"), "(?? count (+ 0 1))");
}

#[test]
fn range_is_lowest_and_nonassoc() {
    assert_eq!(sexpr("a..<b"), "(..< a b)");
    assert_eq!(sexpr("1 + 2 ..= n - 1"), "(..= (+ 1 2) (- n 1))");
    // chaining ranges is a non-assoc error
    assert!(errors("a..<b..<c").iter().any(|m| m.contains("non-associative")));
}

#[test]
fn comparison_is_nonassociative() {
    assert!(errors("a < b < c").iter().any(|m| m.contains("non-associative")));
    assert!(errors("a < b == c").iter().any(|m| m.contains("non-associative")));
    // a single comparison is fine, and richer operands bind inside it
    assert_eq!(sexpr("a + b < c * d"), "(< (+ a b) (* c d))");
}

#[test]
fn errors_on_garbage() {
    assert!(errors("1 +").iter().any(|m| m.contains("expected an expression")));
    assert!(errors("1 2").iter().any(|m| m.contains("trailing")));
    assert!(errors("(1 + 2").iter().any(|m| m.contains("expected `)`")));
}
