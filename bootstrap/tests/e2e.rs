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

#[test]
fn builds_and_runs_skeleton() {
    let bin = std::env::temp_dir().join(format!("plewc_e2e_{}", std::process::id()));
    build_executable(SKELETON, &bin).expect("build executable");

    let output = Command::new(&bin).output().expect("run built binary");
    let stdout = String::from_utf8_lossy(&output.stdout);

    let _ = std::fs::remove_file(&bin);
    let _ = std::fs::remove_file(bin.with_extension("c"));

    assert!(output.status.success(), "binary exited with {}", output.status);
    assert_eq!(stdout, "42\n");
}

#[test]
fn reports_unsupported_construct() {
    // `??` has no stage0 C lowering yet → a codegen error, not a panic.
    let errs = compile_to_c("fn main() {\n    print(a ?? b)\n}\n").unwrap_err();
    assert!(errs.iter().any(|e| e.contains("not supported")), "errors: {errs:?}");
}
