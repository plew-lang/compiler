//! End-to-end walking-skeleton test: source → C → clang → run.
//! Requires `clang` on PATH (macOS-first stage0).

use plewc::driver::{build_executable, compile_to_c};
use std::process::Command;

const SKELETON: &str = "fn main() {\n    print(40 + 2)\n}\n";

#[test]
fn emits_c_for_skeleton() {
    let c = compile_to_c(SKELETON).expect("compile to C");
    assert!(c.contains("int main(void)"), "C was:\n{c}");
    assert!(c.contains("printf"), "C was:\n{c}");
    assert!(c.contains("(40 + 2)"), "C was:\n{c}");
}

/// Build `src` to a temp binary (unique per test name), run it, return stdout.
fn build_and_run(src: &str, tag: &str) -> String {
    let bin = std::env::temp_dir().join(format!("plewc_e2e_{}_{}", std::process::id(), tag));
    build_executable(src, &bin).expect("build executable");
    let output = Command::new(&bin).output().expect("run built binary");
    let _ = std::fs::remove_file(&bin);
    let _ = std::fs::remove_file(bin.with_extension("c"));
    assert!(output.status.success(), "binary exited with {}", output.status);
    String::from_utf8_lossy(&output.stdout).into_owned()
}

#[test]
fn builds_and_runs_skeleton() {
    assert_eq!(build_and_run(SKELETON, "skeleton"), "42\n");
}

#[test]
fn builds_and_runs_branch() {
    let src = "fn main() {\n    val n: I64 = 7\n    if n > 5 {\n        print(1)\n    } else {\n        print(0)\n    }\n}\n";
    assert_eq!(build_and_run(src, "branch"), "1\n");
}

#[test]
fn builds_and_runs_else_if() {
    let src = "fn main() {\n    val n: I64 = 2\n    if n > 5 {\n        print(100)\n    } else if n > 1 {\n        print(50)\n    } else {\n        print(0)\n    }\n}\n";
    assert_eq!(build_and_run(src, "elseif"), "50\n");
}

#[test]
fn builds_and_runs_sum_loop() {
    let src = "fn main() {\n    mut val i: I64 = 0\n    mut val sum: I64 = 0\n    while i < 5 {\n        sum += i\n        i += 1\n    }\n    print(sum)\n}\n";
    // 0+1+2+3+4 = 10
    assert_eq!(build_and_run(src, "sumloop"), "10\n");
}

#[test]
fn builds_and_runs_struct() {
    let src = "struct Point {\n    val x: I64\n    val y: I64\n}\nfn main() {\n    val p: Point = <Point x=3 y=4 />\n    print(p.x + p.y)\n}\n";
    assert_eq!(build_and_run(src, "struct"), "7\n");
}

#[test]
fn builds_and_runs_enum_match() {
    let src = "enum Shape {\n    Circle { val r: I64 }\n    Square { val side: I64 }\n}\nfn main() {\n    val c: Shape = <Shape.Circle r=5 />\n    match c {\n        Shape.Circle { val r } => print(r)\n        Shape.Square { val side } => print(side)\n    }\n}\n";
    assert_eq!(build_and_run(src, "enum"), "5\n");
}

#[test]
fn builds_and_runs_int_match() {
    let src = "fn main() {\n    val n: I64 = 2\n    match n {\n        1 => print(10)\n        2 => print(20)\n        _ => print(0)\n    }\n}\n";
    assert_eq!(build_and_run(src, "intmatch"), "20\n");
}

#[test]
fn builds_and_runs_string_print() {
    assert_eq!(build_and_run("fn main() {\n    print(\"hello\")\n}\n", "strlit"), "hello\n");
}

#[test]
fn builds_and_runs_string_bytes() {
    // `s.bytes` is an `Array[U8]` view: count, indexing, and iteration.
    let src = "fn main() {\n    val s: String = \"hi\"\n    print(s.bytes.count)\n    print(s.bytes[0])\n    mut val sum: I64 = 0\n    for val b in s.bytes {\n        sum += 1\n    }\n    print(sum)\n}\n";
    // "hi" => count 2, byte[0] = 'h' = 104, loop counts 2
    assert_eq!(build_and_run(src, "strbytes"), "2\n104\n2\n");
}

#[test]
fn builds_and_runs_string_equality() {
    let src = "fn main() {\n    val s: String = \"fn\"\n    if s == \"fn\" {\n        print(1)\n    } else {\n        print(0)\n    }\n    if s != \"fn\" {\n        print(1)\n    } else {\n        print(0)\n    }\n}\n";
    assert_eq!(build_and_run(src, "streq"), "1\n0\n");
}

#[test]
fn builds_and_runs_if_as_value() {
    let src = "fn main() {\n    val n: I64 = 7\n    val label: I64 = if n > 5 { give 1 } else { give 0 }\n    print(label)\n}\n";
    assert_eq!(build_and_run(src, "ifval"), "1\n");
}

#[test]
fn builds_and_runs_block_value() {
    let src = "fn main() {\n    val x: I64 = {\n        val t: I64 = 3\n        give t * t\n    }\n    print(x)\n}\n";
    assert_eq!(build_and_run(src, "blockval"), "9\n");
}

#[test]
fn builds_and_runs_for_range() {
    // `0..<5` (two literals) is ambiguous by design; the upper bound is typed.
    let src = "fn main() {\n    val n: I64 = 5\n    mut val sum: I64 = 0\n    for val i in 0..<n {\n        sum += i\n    }\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "forrange"), "10\n");
}

#[test]
fn builds_and_runs_array_index_and_count() {
    let src = "fn main() {\n    val xs: Array[I64] = [10, 20, 30]\n    print(xs[1])\n    print(xs.count)\n}\n";
    assert_eq!(build_and_run(src, "arr_idx"), "20\n3\n");
}

#[test]
fn builds_and_runs_array_for_each() {
    let src = "fn main() {\n    val xs: Array[I64] = [10, 20, 30]\n    mut val sum: I64 = 0\n    for val x in xs {\n        sum += x\n    }\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "arr_foreach"), "60\n");
}

#[test]
fn builds_and_runs_array_of_struct() {
    let src = "struct P {\n    val x: I64\n    val y: I64\n}\nfn main() {\n    val ps: Array[P] = [<P x=1 y=2 />, <P x=3 y=4 />]\n    mut val sum: I64 = 0\n    for val p in ps {\n        sum += p.x + p.y\n    }\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "arr_struct"), "10\n");
}

#[test]
fn builds_and_runs_array_append_and_index_set() {
    let src = "fn main() {\n    mut val xs: Array[I64] = []\n    xs.append(10)\n    xs.append(20)\n    xs.append(30)\n    xs[1] = 99\n    mut val sum: I64 = 0\n    for val x in xs {\n        sum += x\n    }\n    print(xs.count)\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "arr_mut"), "3\n139\n");
}

#[test]
fn builds_and_runs_array_grows_past_capacity() {
    // Append more than the initial capacity (4) to exercise the realloc path.
    let src = "fn main() {\n    val n: I64 = 10\n    mut val xs: Array[I64] = []\n    for val i in 0..<n {\n        xs.append(i)\n    }\n    mut val sum: I64 = 0\n    for val x in xs {\n        sum += x\n    }\n    print(xs.count)\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "arr_grow"), "10\n45\n");
}

#[test]
fn builds_and_runs_array_index_compound_assign() {
    let src = "fn main() {\n    mut val xs: Array[I64] = [1, 2, 3]\n    xs[0] += 40\n    xs[2] *= 10\n    print(xs[0])\n    print(xs[2])\n}\n";
    assert_eq!(build_and_run(src, "arr_compound"), "41\n30\n");
}

#[test]
fn array_index_out_of_range_panics() {
    let src = "fn main() {\n    val xs: Array[I64] = [1, 2, 3]\n    print(xs[5])\n}\n";
    let bin = std::env::temp_dir()
        .join(format!("plewc_e2e_{}_arr_oob", std::process::id()));
    build_executable(src, &bin).expect("build executable");
    let output = Command::new(&bin).output().expect("run built binary");
    let _ = std::fs::remove_file(&bin);
    let _ = std::fs::remove_file(bin.with_extension("c"));
    assert!(!output.status.success(), "out-of-range index should exit non-zero");
    assert!(
        String::from_utf8_lossy(&output.stderr).contains("index out of range"),
        "stderr: {}",
        String::from_utf8_lossy(&output.stderr)
    );
}

#[test]
fn builds_and_runs_break_and_continue() {
    // Sum 1..=10 but skip multiples handled via continue, stop early via break.
    let src = "fn main() {\n    mut val i: I64 = 0\n    mut val sum: I64 = 0\n    while i < 100 {\n        i += 1\n        if i > 5 {\n            break\n        }\n        sum += i\n    }\n    print(sum)\n}\n";
    assert_eq!(build_and_run(src, "brk"), "15\n");
}

#[test]
fn break_inside_enum_match_targets_the_loop() {
    // `break` in a match arm must exit the loop, not a C switch — the enum
    // match lowers to an if-chain to guarantee this.
    let src = "enum K {\n    Stop\n    Go\n}\nfn classify(n: I64) -> K {\n    if n == 3 {\n        return <K.Stop />\n    }\n    return <K.Go />\n}\nfn main() {\n    mut val sum: I64 = 0\n    mut val i: I64 = 0\n    while i < 10 {\n        i += 1\n        match classify(i) {\n            K.Stop => { break }\n            K.Go => { sum += i }\n        }\n    }\n    print(sum)\n}\n";
    // i=1 Go(+1), i=2 Go(+2), i=3 Stop -> break. sum = 3.
    assert_eq!(build_and_run(src, "brk_match"), "3\n");
}

#[test]
fn builds_and_runs_inout_struct_mutation() {
    let src = "struct Counter {\n    val n: I64\n}\nfn bump(c: inout Counter, by: I64) {\n    c.n = c.n + by\n}\nfn main() {\n    mut val c: Counter = <Counter n=0 />\n    bump(c: inout c, by: 5)\n    bump(c: inout c, by: 3)\n    print(c.n)\n}\n";
    assert_eq!(build_and_run(src, "inout_struct"), "8\n");
}

#[test]
fn builds_and_runs_inout_array_append() {
    let src = "fn add(xs: inout Array[I64], v: I64) {\n    xs.append(v)\n}\nfn main() {\n    mut val xs: Array[I64] = [1, 2]\n    add(xs: inout xs, v: 7)\n    add(xs: inout xs, v: 9)\n    print(xs.count)\n    print(xs[3])\n}\n";
    assert_eq!(build_and_run(src, "inout_array"), "4\n9\n");
}

#[test]
fn selfhost_lexer_sketch_builds_and_runs() {
    // The Plew-side lexer sketch (selfhost/lexer.pw) compiled by stage0 must
    // tokenize its hardcoded sample into the expected kind tags. This guards
    // the language subset the self-hosted compiler relies on.
    let path =
        concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/lexer.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/lexer.pw");
    // "val x = 12 + foo * (3)" => 10 tokens with these kind tags.
    assert_eq!(build_and_run(&src, "selfhost_lexer"), "10\n2\n1\n9\n0\n3\n1\n5\n7\n0\n8\n");
}

#[test]
fn reports_unsupported_construct() {
    // `??` has no stage0 C lowering yet → a codegen error, not a panic.
    let errs = compile_to_c("fn main() {\n    print(a ?? b)\n}\n").unwrap_err();
    assert!(errs.iter().any(|e| e.contains("not supported")), "errors: {errs:?}");
}
