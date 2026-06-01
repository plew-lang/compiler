//! Compilation driver: ties the pipeline together and shells out to `clang`
//! to turn generated C into a native executable (macOS-first, stage0).

use std::path::Path;
use std::process::Command;

use crate::codegen::emit_c;
use crate::parser::parse_program;

/// Parse and generate C for `src`. Errors (parse or codegen) are returned as
/// human-readable strings.
pub fn compile_to_c(src: &str) -> Result<String, Vec<String>> {
    let (ast, items, perrs) = parse_program(src);
    if !perrs.is_empty() {
        return Err(perrs
            .into_iter()
            .map(|e| format!("{:?}: {}", e.span, e.msg))
            .collect());
    }
    let checked = crate::typeck::check(&ast, &items);
    if !checked.errors.is_empty() {
        return Err(checked
            .errors
            .into_iter()
            .map(|e| format!("{:?}: {}", e.span, e.msg))
            .collect());
    }
    emit_c(&ast, &items, &checked.expr_ty, &checked.table)
}

/// Compile `src` to a native executable at `out`, writing the intermediate C to
/// `out` with a `.c` extension and invoking `clang`.
pub fn build_executable(src: &str, out: &Path) -> Result<(), String> {
    let c = compile_to_c(src).map_err(|errs| errs.join("\n"))?;
    let c_path = out.with_extension("c");
    std::fs::write(&c_path, c).map_err(|e| format!("writing {}: {e}", c_path.display()))?;

    let status = Command::new("clang")
        .arg(&c_path)
        .arg("-o")
        .arg(out)
        .status()
        .map_err(|e| format!("failed to run clang (is it installed?): {e}"))?;

    if status.success() {
        Ok(())
    } else {
        Err(format!("clang exited with {status}"))
    }
}
