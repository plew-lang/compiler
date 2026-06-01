//! Type-checker tests. We parse (asserting no parse errors) then run the
//! checker and inspect the messages.

use plewc::parser::parse_program;
use plewc::typeck::check;

fn errs(src: &str) -> Vec<String> {
    let (ast, items, perrs) = parse_program(src);
    assert!(perrs.is_empty(), "unexpected parse errors: {perrs:?}");
    check(&ast, &items).errors.into_iter().map(|e| e.msg).collect()
}

#[test]
fn ambiguous_numeric_literal_is_rejected() {
    // The gap we are closing: no annotation, no context → ambiguous.
    let e = errs("fn main() {\n    val x = 6 * 7\n}");
    assert!(e.iter().any(|m| m.contains("ambiguous")), "errors: {e:?}");
}

#[test]
fn annotation_resolves_literal() {
    assert!(errs("fn main() {\n    val x: I64 = 6 * 7\n}").is_empty());
}

#[test]
fn print_pins_its_argument() {
    // stage0: `print` pins the literal to I64, so this is well-typed.
    assert!(errs("fn main() {\n    print(40 + 2)\n}").is_empty());
}

#[test]
fn literal_type_mismatch() {
    let e = errs("fn main() {\n    val x: Bool = 1\n}");
    assert!(!e.is_empty(), "expected a mismatch error");
}

#[test]
fn unbound_name_is_reported() {
    let e = errs("fn main() {\n    val x: I64 = y\n}");
    assert!(e.iter().any(|m| m.contains("unbound")), "errors: {e:?}");
}

#[test]
fn condition_must_be_bool() {
    let e = errs("fn main() {\n    val n: I64 = 1\n    while n {\n        n += 1\n    }\n}");
    assert!(e.iter().any(|m| m.contains("Bool")), "errors: {e:?}");
}

#[test]
fn binding_to_wrong_type_is_reported() {
    // y is I64; binding it to a Bool slot must error.
    let e = errs("fn main() {\n    val y: I64 = 1\n    val b: Bool = y\n}");
    assert!(!e.is_empty(), "expected a mismatch error");
}

#[test]
fn function_calls_typecheck() {
    let src = "fn add(a: I64, b: I64) -> I64 {\n    return a + b\n}\nfn main() {\n    val r: I64 = add(1, 2)\n    print(r)\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn return_type_mismatch_is_reported() {
    let e = errs("fn f() -> Bool {\n    return 1\n}");
    assert!(!e.is_empty(), "expected a return type error");
}

#[test]
fn mixed_operand_types_rejected() {
    // a: I32, b: I64 — arithmetic on differing types must error (no implicit conv).
    let e = errs("fn main() {\n    val a: I32 = 1\n    val b: I64 = 2\n    val c: I64 = a + b\n}");
    assert!(!e.is_empty(), "expected an operand-type error");
}

#[test]
fn array_literal_checks_and_indexes() {
    let src = "fn main() {\n    val xs: Array[I64] = [1, 2, 3]\n    val a: I64 = xs[0]\n    val n: U64 = xs.count\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn empty_array_without_annotation_is_ambiguous() {
    let e = errs("fn main() {\n    val xs = []\n}");
    assert!(e.iter().any(|m| m.contains("empty array")), "errors: {e:?}");
}

#[test]
fn array_element_type_mismatch_is_reported() {
    // Element `true` is not I64.
    let e = errs("fn main() {\n    val xs: Array[I64] = [1, true]\n}");
    assert!(!e.is_empty(), "expected an element-type error");
}

#[test]
fn indexing_a_non_array_is_reported() {
    let e = errs("fn main() {\n    val x: I64 = 1\n    val y: I64 = x[0]\n}");
    assert!(e.iter().any(|m| m.contains("cannot be indexed")), "errors: {e:?}");
}

#[test]
fn for_each_over_array_binds_element() {
    let src = "fn main() {\n    val xs: Array[I64] = [1, 2, 3]\n    mut val s: I64 = 0\n    for val x in xs {\n        s += x\n    }\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn array_append_typechecks() {
    let src = "fn main() {\n    mut val xs: Array[I64] = []\n    xs.append(1)\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn array_append_wrong_element_type_is_reported() {
    let e = errs("fn main() {\n    mut val xs: Array[I64] = []\n    xs.append(true)\n}");
    assert!(!e.is_empty(), "expected an append element-type error");
}

#[test]
fn unknown_array_method_is_reported() {
    let e = errs("fn main() {\n    mut val xs: Array[I64] = [1]\n    xs.frobnicate(2)\n}");
    assert!(e.iter().any(|m| m.contains("no method")), "errors: {e:?}");
}

#[test]
fn string_bytes_is_a_u8_array() {
    let src = "fn main() {\n    val s: String = \"x\"\n    val n: U64 = s.bytes.count\n    val b: U8 = s.bytes[0]\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn string_equality_is_bool() {
    let src = "fn main() {\n    val s: String = \"x\"\n    val eq: Bool = s == \"y\"\n}";
    assert!(errs(src).is_empty(), "errors: {:?}", errs(src));
}

#[test]
fn unknown_string_member_is_reported() {
    let e = errs("fn main() {\n    val s: String = \"x\"\n    val n: U64 = s.length\n}");
    assert!(e.iter().any(|m| m.contains("no member")), "errors: {e:?}");
}
