//! Expression parser tests. We parse a snippet and assert on the S-expression
//! dump of the resulting tree, which makes precedence/associativity explicit.

use plewc::parser::{parse_expr, parse_program};

/// Parse `src`, assert there are no errors, return the S-expr dump.
fn sexpr(src: &str) -> String {
    let (ast, root, errs) = parse_expr(src);
    assert!(errs.is_empty(), "unexpected parse errors for {src:?}: {errs:?}");
    ast.dump(root)
}

/// Parse a whole program, assert no errors, return items dumped (one per line).
fn prog(src: &str) -> String {
    let (ast, items, errs) = parse_program(src);
    assert!(errs.is_empty(), "unexpected parse errors for {src:?}: {errs:?}");
    items.iter().map(|&i| ast.dump_item(i)).collect::<Vec<_>>().join("\n")
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
fn postfix_field_index_call() {
    assert_eq!(sexpr("a.b"), "(. a b)");
    assert_eq!(sexpr("a.b.c"), "(. (. a b) c)");
    assert_eq!(sexpr("xs[0]"), "([] xs 0)");
    assert_eq!(sexpr("m[i][j]"), "([] ([] m i) j)");
    assert_eq!(sexpr("f()"), "(call f)");
    assert_eq!(sexpr("f(1, 2)"), "(call f 1 2)");
    // method call = field then call; mixed chains
    assert_eq!(sexpr("a.b(1).c"), "(. (call (. a b) 1) c)");
    assert_eq!(sexpr("xs[0].len()"), "(call (. ([] xs 0) len))");
}

#[test]
fn call_args_with_labels() {
    assert_eq!(sexpr("print(text: x, terminator: y)"), "(call print text:x terminator:y)");
    assert_eq!(sexpr("f(a, x: b)"), "(call f a x:b)");
    assert_eq!(sexpr("g(1,)"), "(call g 1)"); // trailing comma
}

#[test]
fn postfix_binds_tighter_than_prefix_and_operators() {
    // postfix(14) > prefix(13): -a.b == -(a.b)
    assert_eq!(sexpr("-a.b"), "(- (. a b))");
    // postfix > `*`: a.b * c == (a.b) * c
    assert_eq!(sexpr("a.b * c"), "(* (. a b) c)");
    // call result indexed then added
    assert_eq!(sexpr("f(x)[0] + 1"), "(+ ([] (call f x) 0) 1)");
}

#[test]
fn minimal_fn_and_call() {
    assert_eq!(
        prog("fn main() {\n    print(40 + 2)\n}"),
        "(fn main () (block (call print (+ 40 2))))"
    );
    assert_eq!(prog("fn main() {}"), "(fn main () (block))");
}

#[test]
fn statements_in_block() {
    let src = "fn main() {\n    val x = 1 + 2\n    mut val y = x\n    print(y)\n    return\n}";
    assert_eq!(
        prog(src),
        "(fn main () (block (val x (+ 1 2)) (mutval y x) (call print y) (return)))"
    );
}

#[test]
fn params_return_and_generic_types() {
    assert_eq!(
        prog("fn add(a: I32, b: I32) -> I32 {\n    return a + b\n}"),
        "(fn add (a:I32 b:I32) -> I32 (block (return (+ a b))))"
    );
    // generic type in a parameter, and a suppressed label
    assert_eq!(
        prog("fn f(xs: Array[I32], text~: String) {\n    return\n}"),
        "(fn f (xs:Array[I32] text~:String) (block (return)))"
    );
    assert_eq!(
        prog("fn g(d: Dictionary[String, I32]) {}"),
        "(fn g (d:Dictionary[String, I32]) (block))"
    );
}

#[test]
fn return_with_value_on_same_line() {
    assert_eq!(
        prog("fn two() -> I32 {\n    return 2\n}"),
        "(fn two () -> I32 (block (return 2)))"
    );
}

#[test]
fn if_else_as_statement() {
    let src = "fn main() {\n    if n > 5 {\n        print(1)\n    } else {\n        print(0)\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn main () (block (if (> n 5) (block (call print 1)) (block (call print 0)))))"
    );
}

#[test]
fn else_if_chain() {
    let src = "fn pick() -> I32 {\n    if a {\n        give 1\n    } else if b {\n        give 2\n    } else {\n        give 3\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn pick () -> I32 (block (if a (block (give 1)) (if b (block (give 2)) (block (give 3))))))"
    );
}

#[test]
fn block_expression_with_give() {
    let src = "fn main() {\n    val x = {\n        val t = 2\n        give t * 3\n    }\n}";
    assert_eq!(prog(src), "(fn main () (block (val x (block (val t 2) (give (* t 3))))))");
}

#[test]
fn for_range_loop() {
    let src = "fn main() {\n    for val i in 0..<n {\n        print(i)\n    }\n}";
    assert_eq!(prog(src), "(fn main () (block (for val i (..< 0 n) (block (call print i)))))");
}

#[test]
fn while_and_assignment() {
    let src = "fn main() {\n    mut val i: I64 = 0\n    while i < 3 {\n        i = i + 1\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn main () (block (mutval i:I64 0) (while (< i 3) (block (= i (+ i 1))))))"
    );
}

#[test]
fn compound_assignment() {
    let src = "fn main() {\n    mut val s: I64 = 0\n    s += 5\n    s *= 2\n}";
    assert_eq!(prog(src), "(fn main () (block (mutval s:I64 0) (+= s 5) (*= s 2)))");
}

#[test]
fn match_expression() {
    let src = "fn f() {\n    match x {\n        0 => print(1)\n        _ => print(2)\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn f () (block (match x (=> 0 (call print 1)) (=> _ (call print 2)))))"
    );
}

#[test]
fn match_variant_patterns_and_binding() {
    let src = "fn f() {\n    match opt {\n        Optional.Some { value: val v } => print(v)\n        Optional.None => print(0)\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn f () (block (match opt (=> Optional.Some{value=(val v)} (call print v)) (=> Optional.None (call print 0)))))"
    );
}

#[test]
fn match_punning_binding() {
    // `{ val intensity }` is sugar for `{ intensity: val intensity }`
    let src = "fn f() {\n    match c {\n        Color.Red { val intensity } => print(intensity)\n        _ => print(0)\n    }\n}";
    assert_eq!(
        prog(src),
        "(fn f () (block (match c (=> Color.Red{intensity=(val intensity)} (call print intensity)) (=> _ (call print 0)))))"
    );
}

#[test]
fn jsx_construction() {
    assert_eq!(sexpr("<Point x=3 y=4 />"), "(new Point x=3 y=4)");
    // value expressions in attributes; nested call
    assert_eq!(sexpr("<Box value=f(1) />"), "(new Box value=(call f 1))");
    // enum-variant path and empty attributes
    assert_eq!(sexpr("<Color.Red />"), "(new Color.Red)");
    // multi-line attributes (newlines elided inside the tag)
    assert_eq!(sexpr("<Point\n  x=1\n  y=2\n/>"), "(new Point x=1 y=2)");
}

#[test]
fn struct_declaration() {
    let src = "struct Point {\n    val x: I64\n    val y: I64\n}";
    assert_eq!(prog(src), "(struct Point (field x:I64) (field y:I64))");
}

#[test]
fn struct_with_visibility_mut_and_generics() {
    let src = "struct Box[T] {\n    pub val name: String\n    pub(get) val id: I32\n    mut val value: T\n}";
    assert_eq!(
        prog(src),
        "(struct Box[T] (field pub name:String) (field pubget id:I32) (field mut value:T))"
    );
}

#[test]
fn enum_declaration() {
    let src = "enum Color {\n    Red\n    Green\n    Blue\n}";
    assert_eq!(prog(src), "(enum Color (variant Red) (variant Green) (variant Blue))");
}

#[test]
fn enum_with_payload_and_generics() {
    let src = "enum Optional[T] {\n    Some { val value: T }\n    None\n}";
    assert_eq!(
        prog(src),
        "(enum Optional[T] (variant Some (field value:T)) (variant None))"
    );
}

#[test]
fn export_modifier_is_accepted() {
    assert_eq!(prog("export struct S {\n    val x: I64\n}"), "(struct S (field x:I64))");
}

#[test]
fn errors_on_garbage() {
    assert!(errors("1 +").iter().any(|m| m.contains("expected an expression")));
    assert!(errors("1 2").iter().any(|m| m.contains("trailing")));
    assert!(errors("(1 + 2").iter().any(|m| m.contains("expected `)`")));
}

#[test]
fn array_literals() {
    assert_eq!(sexpr("[1, 2, 3]"), "(array 1 2 3)");
    assert_eq!(sexpr("[]"), "(array)");
    // index binds as a postfix on the array
    assert_eq!(sexpr("xs[0]"), "([] xs 0)");
    // trailing comma + newlines inside brackets are allowed
    assert_eq!(sexpr("[\n  1,\n  2,\n]"), "(array 1 2)");
}
