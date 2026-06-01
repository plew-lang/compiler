//! `plewc` CLI entry point.
//!
//! Currently a thin harness: reads a `.pw` file and dumps its tokens, so the
//! end-to-end pipeline can be exercised while later stages are built up.

use std::process::ExitCode;

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    let Some(path) = args.get(1) else {
        eprintln!("usage: plewc <file.pw>");
        return ExitCode::FAILURE;
    };

    let src = match std::fs::read_to_string(path) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("plewc: cannot read {path}: {e}");
            return ExitCode::FAILURE;
        }
    };

    let (tokens, errors) = plewc::lexer::lex(&src);
    for tok in &tokens {
        println!("{:?} {:?}", tok.span, tok.kind);
    }
    if !errors.is_empty() {
        for err in &errors {
            eprintln!("plewc: lex error at {:?}: {}", err.span, err.msg);
        }
        return ExitCode::FAILURE;
    }
    ExitCode::SUCCESS
}
