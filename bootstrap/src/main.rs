//! `plewc` CLI entry point.
//!
//! Usage:
//!   plewc <file.pw>            build a native executable (stage0: via C + clang)
//!   plewc --emit-c <file.pw>   print the generated C to stdout
//!   plewc --tokens <file.pw>   dump the token stream (debugging)

use std::path::{Path, PathBuf};
use std::process::ExitCode;

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let (mode, path) = match args.as_slice() {
        [flag, path] if flag == "--emit-c" => (Mode::EmitC, path.clone()),
        [flag, path] if flag == "--tokens" => (Mode::Tokens, path.clone()),
        [path] if !path.starts_with('-') => (Mode::Build, path.clone()),
        _ => {
            eprintln!("usage: plewc [--emit-c | --tokens] <file.pw>");
            return ExitCode::FAILURE;
        }
    };

    let src = match std::fs::read_to_string(&path) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("plewc: cannot read {path}: {e}");
            return ExitCode::FAILURE;
        }
    };

    match mode {
        Mode::Tokens => {
            let (tokens, errors) = plewc::lexer::lex(&src);
            for tok in &tokens {
                println!("{:?} {:?}", tok.span, tok.kind);
            }
            report_lex(&errors)
        }
        Mode::EmitC => match plewc::driver::compile_to_c(&src) {
            Ok(c) => {
                print!("{c}");
                ExitCode::SUCCESS
            }
            Err(errs) => report(&errs),
        },
        Mode::Build => {
            let out = default_output_path(&path);
            match plewc::driver::build_executable(&src, &out) {
                Ok(()) => {
                    eprintln!("plewc: built {}", out.display());
                    ExitCode::SUCCESS
                }
                Err(msg) => {
                    eprintln!("plewc: {msg}");
                    ExitCode::FAILURE
                }
            }
        }
    }
}

enum Mode {
    Build,
    EmitC,
    Tokens,
}

/// `foo/bar.pw` -> `foo/bar`; a path with no extension gets `.out`.
fn default_output_path(path: &str) -> PathBuf {
    let p = Path::new(path);
    let stripped = p.with_extension("");
    if stripped == p {
        p.with_extension("out")
    } else {
        stripped
    }
}

fn report_lex(errors: &[plewc::lexer::LexError]) -> ExitCode {
    if errors.is_empty() {
        ExitCode::SUCCESS
    } else {
        for e in errors {
            eprintln!("plewc: lex error at {:?}: {}", e.span, e.msg);
        }
        ExitCode::FAILURE
    }
}

fn report(errs: &[String]) -> ExitCode {
    for e in errs {
        eprintln!("plewc: {e}");
    }
    ExitCode::FAILURE
}
