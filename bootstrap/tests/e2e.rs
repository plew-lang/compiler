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
fn reports_unsupported_construct() {
    // `??` has no stage0 C lowering yet → a codegen error, not a panic.
    let errs = compile_to_c("fn main() {\n    print(a ?? b)\n}\n").unwrap_err();
    assert!(errs.iter().any(|e| e.contains("not supported")), "errors: {errs:?}");
}
