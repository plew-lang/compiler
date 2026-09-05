# Frontend implementation regressions

These are internal tests, separate from the language fixture suite. Each entry
imports the real `src/Frontend` module, including its parts. Never compile an
individual `src/Codegen/...` part as a substitute: it lacks the owning `Comp`
definition and does not test the implementation in context.

`TypeTermPublication.pw` checks projection publication outside Lower, receiver
argument substitution, structural inequality, and allocation-free equality.
Compile it with the selected carrier, link its LLVM with that carrier's runtime,
then compare program stdout with `TypeTermPublication.out`. A failure while
compiling the harness is not an executed assertion failure; no-main is not a
passing internal test. This directory is not picked up by `test.sh`.

The imported compiler implementation currently makes even this harness an
expensive compile. Apply the normal 60-second meaningful-progress rule, retain
the command session and final exit code, and do not overwrite the canonical
compiler or seed with diagnostic artifacts.
