//! Plew stage0 bootstrap compiler.
//!
//! Pipeline (built incrementally): source → lexer → parser → AST →
//! name/type resolution → C codegen → clang. This crate is the throwaway
//! bootstrap used to bring up self-hosting; it favours simplicity and
//! correct *semantics* over performance or completeness.

pub mod span;
pub mod token;
pub mod lexer;
pub mod ast;
pub mod parser;
pub mod typeck;
pub mod codegen;
pub mod driver;
