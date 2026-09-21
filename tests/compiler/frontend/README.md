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
passing internal test. This directory is not picked up by `tests/harness/test.sh`.

The imported compiler implementation currently makes even this harness an
expensive compile. Apply the normal 60-second meaningful-progress rule, retain
the command session and final exit code, and do not overwrite the canonical
compiler or seed with diagnostic artifacts.

`TemplateDependencyUnfinalized.pw` checks that a published implicit-call slot
cannot satisfy a different, unfinalized slot. Compile/link the harness normally;
its execution must exit 1 and report the diagnostic in the companion `.err`.
This is a compiler diagnostic test, not a panic (SIGABRT) test.

## Manual execution procedure

Run from the compiler repository root with the selected carrier. Keep all
outputs in a new directory under `tmp/`; these fixtures are not automatically
registered in the normal suite.

1. Compile the selected `.pw` with `--trace-phases`, using
   `python3 -B scripts/support/trace-command.py <compile-log> -- <carrier> ...`
   to supervise progress. Save stdout as LLVM and require compiler exit 0.
2. Export that same carrier's `--runtime` output to a C file. Link it with the
   generated LLVM using `clang -w`, adding the selected `llvm-config --ldflags`.
   Supervise runtime export and linking with `scripts/support/watch-command.py`;
   require exit 0 for each step. Do not execute an old binary after a failure.
3. Execute the new binary through `scripts/support/watch-command.py`, capturing
   stdout, stderr and the actual exit code separately.
4. For `TypeTermPublication`, require exit 0 and byte-compare stdout with its
   `.out`. For `TemplateDependencyUnfinalized`, require exit 1 and the literal
   diagnostic from its `.err` in stderr. A signal, timeout, compile/link failure,
   or another exit code is a failure, even if the diagnostic text appears.

Pass the fixture path under `tests/compiler/frontend/` to the carrier. Neither
procedure updates the canonical compiler or seed, nor replaces the standard
normal or sanitizer gates.
