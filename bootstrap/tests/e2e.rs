//! End-to-end walking-skeleton test: source → C → clang → run.
//! Requires `clang` on PATH (macOS-first stage0).

use plewc::driver::{build_executable, compile_to_c};
use std::process::Command;

const SKELETON: &str = "fn main() {\n    print(40 + 2)\n}\n";

#[test]
fn emits_c_for_skeleton() {
    let c = compile_to_c(SKELETON).expect("compile to C");
    assert!(c.contains("int main("), "C was:\n{c}");
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
    let src = "enum Shape {\n    Circle { r: I64 }\n    Square { side: I64 }\n}\nfn main() {\n    val c: Shape = <Shape.Circle r=5 />\n    match c {\n        Shape.Circle { val r } => print(r)\n        Shape.Square { val side } => print(side)\n    }\n}\n";
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

/// Build a program from `src`, run it feeding `stdin`, return stdout.
fn build_and_run_stdin(src: &str, tag: &str, stdin: &str) -> String {
    use std::io::Write;
    use std::process::Stdio;
    let bin = std::env::temp_dir().join(format!("plewc_e2e_{}_{}", std::process::id(), tag));
    build_executable(src, &bin).expect("build executable");
    let mut child = Command::new(&bin)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("spawn");
    child.stdin.take().unwrap().write_all(stdin.as_bytes()).unwrap();
    let out = child.wait_with_output().expect("wait");
    let _ = std::fs::remove_file(&bin);
    let _ = std::fs::remove_file(bin.with_extension("c"));
    assert!(out.status.success(), "binary exited with {}", out.status);
    String::from_utf8_lossy(&out.stdout).into_owned()
}

#[test]
fn selfhost_lexer_tokenizes_a_function() {
    // The full-subset lexer (selfhost/lexer.pw) prints one kind-code per token.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/lexer.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/lexer.pw");
    let input = "fn add(a: I64, b: I64) -> I64 {\n    return a + b\n}\n";
    // KwFn Ident LParen Ident Colon Ident Comma Ident Colon Ident RParen Arrow
    // Ident LBrace KwReturn Ident Plus Ident Newline RBrace Newline Eof
    // (no Newline after `{` — Go-style: `{` cannot end a statement)
    let codes = [
        10, 4, 40, 4, 47, 4, 46, 4, 47, 4, 41, 64, 4, 44, 20, 4, 56, 4, 1, 45, 1, 0,
    ];
    let expected: String = codes.iter().map(|c| format!("{c}\n")).collect();
    assert_eq!(build_and_run_stdin(&src, "selfhost_lex_fn", input), expected);
}

#[test]
fn selfhost_lexer_suppresses_continuation_newlines() {
    // Go-style: newlines inside `()` and after an operator are continuations;
    // only a token that can end a statement yields a Newline.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/lexer.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/lexer.pw");
    let input = "fn f(\n  a: I64,\n  b: I64\n) -> I64 {\n  val x = a +\n    b\n  return x\n}\n";
    // No Newline inside the parens or after `+`; Newline only after `b`, `x`, `}`.
    let codes = [
        10, 4, 40, 4, 47, 4, 46, 4, 47, 4, 41, 64, 4, 44, 22, 4, 49, 4, 56, 4, 1, 20, 4, 1, 45, 1,
        0,
    ];
    let expected: String = codes.iter().map(|c| format!("{c}\n")).collect();
    assert_eq!(build_and_run_stdin(&src, "selfhost_lex_cont", input), expected);
}

#[test]
fn selfhost_calc_parser_builds_and_runs() {
    // The Plew-side arithmetic parser+evaluator (selfhost/calc.pw): inout
    // cursor threading, arena+index AST, recursive eval. Guards the parser
    // phase's language requirements (and codegen's type-ordering + prototypes).
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/calc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/calc.pw");
    // "2 + 3 * (4 + 5) - 1" = 2 + 27 - 1 = 28
    assert_eq!(build_and_run(&src, "selfhost_calc"), "28\n");
}

#[test]
fn selfhost_token_parser_builds_and_runs() {
    // selfhost/parser.pw: a parser that consumes the LEXER'S TOKEN STREAM
    // (Array[Tok]) rather than raw bytes — advancing a token cursor, dispatching
    // on Tok.kind via match, and reading an Int literal's value back out of the
    // source bytes via its (start, len) span. This is the shape the self-hosted
    // compiler's parser needs: lex -> tokens -> parse.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/parser.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/parser.pw");
    // "1 + 2 * 3 - 4 % 3" = 1 + 6 - 1 = 6
    assert_eq!(build_and_run_stdin(&src, "selfhost_tokparse", "1 + 2 * 3 - 4 % 3\n"), "6\n");
}

#[test]
fn selfhost_emit_compiles_a_c_program() {
    // selfhost/emit.pw is a tiny COMPILER in Plew: it reads an arithmetic
    // expression and emits a complete C program (via write()) that prints the
    // value. Two-stage check: stage0 builds emit.pw -> run it to get C ->
    // clang compiles that C -> run -> result. Exercises the lex -> parse ->
    // emit-C pipeline end to end in Plew, plus write()-based output and
    // decimal integer formatting via per-digit string literals.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/emit.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/emit.pw");
    let emitted_c = build_and_run_stdin(&src, "selfhost_emit", "2 + 3 * (4 + 5) - 1\n");
    assert!(emitted_c.contains("printf"), "emitted C was:\n{emitted_c}");

    // Now compile the emitted C with clang and run it.
    let c_path = std::env::temp_dir().join(format!("plew_emit_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_emit_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang")
        .arg(&c_path)
        .arg("-o")
        .arg(&out_bin)
        .status()
        .expect("run clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    assert_eq!(String::from_utf8_lossy(&output.stdout), "28\n");
}

#[test]
fn builds_and_runs_stdin_io() {
    use std::io::Write;
    use std::process::Stdio;
    // Read stdin, count 'a' bytes, write a raw label then the count.
    let src = "fn main() {\n    val s: String = readStdin()\n    mut val n: I64 = 0\n    for val b in s.bytes {\n        if b == 97 {\n            n += 1\n        }\n    }\n    write(\"a=\")\n    print(n)\n}\n";
    let bin = std::env::temp_dir().join(format!("plewc_e2e_{}_stdin", std::process::id()));
    build_executable(src, &bin).expect("build executable");
    let mut child = Command::new(&bin)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("spawn");
    child.stdin.take().unwrap().write_all(b"banana apple").unwrap();
    let out = child.wait_with_output().expect("wait");
    let _ = std::fs::remove_file(&bin);
    let _ = std::fs::remove_file(bin.with_extension("c"));
    assert_eq!(String::from_utf8_lossy(&out.stdout), "a=4\n");
}

#[test]
fn selfhost_plewc_compiles_a_plew_program() {
    // selfhost/plewc.pw is the stage1 compiler skeleton, written in Plew: it
    // reads a Plew program from stdin (a single top-level fn's body), parses
    // declarations / statements / expressions into an arena AST, and emits a C
    // program (identifiers echoed from source spans via writeByte). Three-stage
    // check: stage0 builds plewc.pw -> run it on a Plew program to get C ->
    // clang compiles that C -> run -> result. A real compiler-in-Plew end to end.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "fn main() {\n    mut val i: I64 = 0\n    mut val sum: I64 = 0\n    while i < 5 {\n        sum += i\n        i += 1\n    }\n    if sum > 5 {\n        print(sum)\n    } else {\n        print(0)\n    }\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc", program);
    assert!(emitted_c.contains("int main("), "emitted C was:\n{emitted_c}");

    let c_path = std::env::temp_dir().join(format!("plew_plewc_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewc_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // 0+1+2+3+4 = 10, which is > 5, so it prints 10.
    assert_eq!(String::from_utf8_lossy(&output.stdout), "10\n");
}

#[test]
fn selfhost_plewc_compiles_functions_and_calls() {
    // plewc.pw v2: multiple top-level functions, by-value parameters, user
    // function calls (labels dropped), return values, recursion, and forward
    // prototypes. Same three-stage check as above.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "fn add(a: I64, b: I64) -> I64 {\n    return a + b\n}\nfn fib(n: I64) -> I64 {\n    if n < 2 {\n        return n\n    }\n    return add(a: fib(n: n - 1), b: fib(n: n - 2))\n}\nfn main() {\n    print(add(a: 3, b: 4))\n    print(fib(n: 10))\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_fn", program);
    assert!(emitted_c.contains("long long fib(long long n)"), "emitted C was:\n{emitted_c}");

    let c_path = std::env::temp_dir().join(format!("plew_plewcfn_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcfn_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // add(3,4)=7, fib(10)=55
    assert_eq!(String::from_utf8_lossy(&output.stdout), "7\n55\n");
}

#[test]
fn selfhost_plewc_compiles_structs() {
    // plewc.pw v3: struct declarations (incl. nested by-value struct fields),
    // JSX construction `<Type field=expr />` -> C compound literal, chained
    // field access, and type annotations reflected into C types (named structs
    // echoed; scalars -> long long). Same three-stage check.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "struct Point {\n    val x: I64\n    val y: I64\n}\nstruct Line {\n    val a: Point\n    val b: Point\n}\nfn main() {\n    val p: Point = <Point x=3 y=4 />\n    val q: Point = <Point x=10 y=20 />\n    val ln: Line = <Line a=p b=q />\n    print(p.x + p.y)\n    print(ln.b.x + ln.a.y)\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_struct", program);
    assert!(emitted_c.contains("struct Line {"), "emitted C was:\n{emitted_c}");
    assert!(emitted_c.contains("(Point){"), "emitted C was:\n{emitted_c}");

    let c_path = std::env::temp_dir().join(format!("plew_plewcst_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcst_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // p.x+p.y = 7; ln.b.x + ln.a.y = 10 + 4 = 14
    assert_eq!(String::from_utf8_lossy(&output.stdout), "7\n14\n");
}

#[test]
fn selfhost_plewc_compiles_enums_and_match() {
    // plewc.pw v4: enum declarations -> C tagged union, JSX variant
    // construction `<E.V f=e />` -> designated init with tag, and match ->
    // if-chain on tag with field bindings (the pattern names the enum/variant,
    // so tag index and field types are resolved without type inference).
    // Function parameter/return types now use the declared types too.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "enum Shape {\n    Circle { r: I64 }\n    Rect { w: I64, h: I64 }\n}\nfn area(s: Shape) -> I64 {\n    match s {\n        Shape.Circle { val r } => {\n            return r * r * 3\n        }\n        Shape.Rect { val w, val h } => {\n            return w * h\n        }\n    }\n    return 0\n}\nfn main() {\n    val c: Shape = <Shape.Circle r=5 />\n    val r: Shape = <Shape.Rect w=4 h=6 />\n    print(area(s: c))\n    print(area(s: r))\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_enum", program);
    assert!(emitted_c.contains("union {"), "emitted C was:\n{emitted_c}");
    assert!(emitted_c.contains(".tag == "), "emitted C was:\n{emitted_c}");

    let c_path = std::env::temp_dir().join(format!("plew_plewcen_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcen_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // Circle r=5 -> 5*5*3 = 75; Rect 4x6 -> 24
    assert_eq!(String::from_utf8_lossy(&output.stdout), "75\n24\n");
}

/// Run an existing binary feeding `stdin`, return stdout (asserts success).
fn run_bin_stdin(bin: &std::path::Path, stdin: &str) -> String {
    use std::io::Write;
    use std::process::Stdio;
    let mut child = Command::new(bin)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .expect("spawn");
    child.stdin.take().unwrap().write_all(stdin.as_bytes()).unwrap();
    let out = child.wait_with_output().expect("wait");
    assert!(out.status.success(), "binary exited with {}", out.status);
    String::from_utf8_lossy(&out.stdout).into_owned()
}

#[test]
fn selfhost_plewc_reaches_fixpoint() {
    // THE self-host test. plewc.pw is a Plew compiler. Pipeline:
    //   stage0 (Rust) builds plewc.pw -> `plewc` binary
    //   plewc compiles plewc.pw      -> c1   (clang -> plewc1 binary)
    //   plewc1 compiles plewc.pw     -> c2
    // c1 == c2 is the fixpoint: the Plew-written compiler reproduces itself
    // exactly, so it no longer depends on stage0. We also confirm plewc1 is a
    // real working compiler by having it build and run a sample program.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");

    // stage0 -> plewc binary
    let plewc = std::env::temp_dir().join(format!("plew_sh_plewc_{}", std::process::id()));
    build_executable(&src, &plewc).expect("stage0 builds plewc.pw");

    // plewc compiles itself -> c1 -> plewc1
    let c1 = run_bin_stdin(&plewc, &src);
    assert!(c1.contains("int main("), "c1 was not C:\n{}", &c1[..c1.len().min(400)]);
    let c1_path = std::env::temp_dir().join(format!("plew_sh_c1_{}.c", std::process::id()));
    let plewc1 = std::env::temp_dir().join(format!("plew_sh_plewc1_{}", std::process::id()));
    std::fs::write(&c1_path, &c1).unwrap();
    // -Werror also guards that plewc's generated C stays warning-clean.
    assert!(Command::new("clang").arg("-Wall").arg("-Wextra").arg("-Werror").arg(&c1_path).arg("-o").arg(&plewc1).status().expect("clang c1").success(), "clang failed (or warned) on c1");

    // plewc1 compiles plewc.pw -> c2; fixpoint: c1 == c2
    let c2 = run_bin_stdin(&plewc1, &src);
    assert_eq!(c1, c2, "self-host fixpoint broken: plewc and plewc1 disagree");

    // plewc1 is a real working compiler: build and run a sample program.
    let sample = "fn add(a: I64, b: I64) -> I64 {\n    return a + b\n}\nfn main() {\n    print(add(a: 19, b: 23))\n}\n";
    let sample_c = run_bin_stdin(&plewc1, sample);
    let sc_path = std::env::temp_dir().join(format!("plew_sh_sample_{}.c", std::process::id()));
    let sbin = std::env::temp_dir().join(format!("plew_sh_sample_{}", std::process::id()));
    std::fs::write(&sc_path, &sample_c).unwrap();
    assert!(Command::new("clang").arg("-w").arg(&sc_path).arg("-o").arg(&sbin).status().expect("clang sample").success());
    let out = Command::new(&sbin).output().expect("run sample");
    assert_eq!(String::from_utf8_lossy(&out.stdout), "42\n");

    for p in [&plewc, &c1_path, &plewc1, &sc_path, &sbin] {
        let _ = std::fs::remove_file(p);
    }
    let _ = std::fs::remove_file(plewc.with_extension("c"));
}

#[test]
fn selfhost_plewc_compiles_for_loops() {
    // plewc.pw post-self-host language growth: `for val i in a..<b` / `a..=b`
    // and `for val x in arr` (lowered to C for-loops). plewc.pw also dogfoods
    // the feature in its own driver, so the fixpoint test already exercises it.
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "fn main() {\n    mut val a: I64 = 0\n    for val i in 0..<5 {\n        a += i\n    }\n    print(a)\n    mut val b: I64 = 0\n    for val i in 1..=4 {\n        b += i\n    }\n    print(b)\n    val xs: Array[I64] = [10, 20, 30]\n    mut val c: I64 = 0\n    for val x in xs {\n        c += x\n    }\n    print(c)\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_for", program);
    let c_path = std::env::temp_dir().join(format!("plew_plewcfor_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcfor_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg("-w").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // 0+1+2+3+4=10; 1+2+3+4=10; 10+20+30=60
    assert_eq!(String::from_utf8_lossy(&output.stdout), "10\n10\n60\n");
}

#[test]
fn selfhost_plewc_compiles_string_eq_and_index_set() {
    // More post-self-host growth in plewc.pw: String ==/!= (lowered to
    // PlewString_eq, type-directed) and array element assignment a[i] = v /
    // a[i] OP= v (lowered to PlewArray_E_set).
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "fn main() {\n    val s: String = \"fn\"\n    if s == \"fn\" {\n        print(1)\n    } else {\n        print(0)\n    }\n    if s != \"x\" {\n        print(1)\n    } else {\n        print(0)\n    }\n    mut val xs: Array[I64] = [1, 2, 3]\n    xs[0] = 40\n    xs[2] += 10\n    print(xs[0])\n    print(xs[2])\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_streq", program);
    let c_path = std::env::temp_dir().join(format!("plew_plewcseq_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcseq_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg("-w").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // s=="fn" -> 1; s!="x" -> 1; xs[0]=40; xs[2]=3+10=13
    assert_eq!(String::from_utf8_lossy(&output.stdout), "1\n1\n40\n13\n");
}

#[test]
fn selfhost_plewc_compiles_arrays_and_strings() {
    // plewc.pw v5: monomorphized arrays (PlewArray_<E> + runtime), [] literal,
    // append, index, .count, struct array fields, String literals, String.bytes
    // (aliasing PlewArray_U8), and the write/writeByte/readStdin builtins lowered
    // to the C runtime that plewc.pw emits itself (self-contained output).
    let path = concat!(env!("CARGO_MANIFEST_DIR"), "/../selfhost/plewc.pw");
    let src = std::fs::read_to_string(path).expect("read selfhost/plewc.pw");
    let program = "struct Box {\n    val xs: Array[I64]\n}\nfn sum(b: Box) -> I64 {\n    mut val s: I64 = 0\n    mut val i: U64 = 0\n    while i < b.xs.count {\n        s += b.xs[i]\n        i += 1\n    }\n    return s\n}\nfn countA(s: String) -> I64 {\n    val bs: Array[U8] = s.bytes\n    mut val n: I64 = 0\n    mut val i: U64 = 0\n    while i < bs.count {\n        if bs[i] == 97 {\n            n += 1\n        }\n        i += 1\n    }\n    return n\n}\nfn main() {\n    mut val xs: Array[I64] = []\n    xs.append(10)\n    xs.append(20)\n    xs.append(12)\n    val b: Box = <Box xs=xs />\n    print(sum(b: b))\n    val msg: String = \"banana\"\n    print(countA(s: msg))\n}\n";
    let emitted_c = build_and_run_stdin(&src, "selfhost_plewc_arr", program);
    assert!(emitted_c.contains("PlewArray_I64"), "emitted C was:\n{emitted_c}");
    assert!(emitted_c.contains("PlewString"), "emitted C was:\n{emitted_c}");

    let c_path = std::env::temp_dir().join(format!("plew_plewcarr_{}.c", std::process::id()));
    let out_bin = std::env::temp_dir().join(format!("plew_plewcarr_{}", std::process::id()));
    std::fs::write(&c_path, &emitted_c).expect("write emitted C");
    let status = Command::new("clang").arg(&c_path).arg("-o").arg(&out_bin).status().expect("clang");
    assert!(status.success(), "clang failed on emitted C:\n{emitted_c}");
    let output = Command::new(&out_bin).output().expect("run emitted binary");
    let _ = std::fs::remove_file(&c_path);
    let _ = std::fs::remove_file(&out_bin);
    // 10+20+12 = 42; 'a' count in "banana" = 3
    assert_eq!(String::from_utf8_lossy(&output.stdout), "42\n3\n");
}

#[test]
fn builds_and_runs_write_byte() {
    // writeByte emits a single raw byte (putchar). The self-hosted compiler
    // uses it to echo identifier text out of source spans (no substring).
    let src = "fn main() {\n    val s: String = \"Hi!\"\n    val bs: Array[U8] = s.bytes\n    mut val i: U64 = 0\n    while i < bs.count {\n        writeByte(bs[i])\n        i += 1\n    }\n    writeByte(10)\n}\n";
    assert_eq!(build_and_run(src, "writebyte"), "Hi!\n");
}

#[test]
fn reports_unsupported_construct() {
    // `??` has no stage0 C lowering yet → a codegen error, not a panic.
    let errs = compile_to_c("fn main() {\n    print(a ?? b)\n}\n").unwrap_err();
    assert!(errs.iter().any(|e| e.contains("not supported")), "errors: {errs:?}");
}
