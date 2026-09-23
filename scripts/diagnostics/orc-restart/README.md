# ORC feasibility probes (manual)

These probes do not change the compiler, seed, language semantics, or standard
test gates. The plan is in the meta repository's `agents/hot-restart-validation.md`.

From the compiler repository:

```sh
/usr/bin/python3 -B scripts/diagnostics/orc-restart/check.py --out tmp/orc-restart/smoke
```

Requires a macOS LLVM distribution (`--llvm-prefix`, default Homebrew LLVM).
Output directories must be new. Each child is supervised by the existing
60-second progress watchdog. Commands, outputs, exits, toolchain/input hashes,
and comparison results are recorded in `results.json` and companion logs.

`runner.cpp` is a small C++ diagnostic host using ORC LLJIT. It loads the normal
Plew-generated runtime as a dylib, consumes compiler-generated IR, verifies it,
and executes `main`. It has no new interpreter or language implementation.
`check.py` reuses existing fixtures and compares ORC, AOT, and their goldens,
both without optimization and with the common Plew pipeline followed by O2.
The AOT path uses clang O2; ORC uses the explicit LLVM O2 pipeline and default
native codegen. These are recorded configurations, not a claim of identical
clang/JIT pass sequences. Runtime C is compiled at O2 in both paths.

This verifies selected normal executions only: it is not repeated application
restart, a memory-safety gate, source incremental compilation, mobile support,
or an end-to-end restart latency measurement. The diagnostic host deliberately
uses the current native target; cross-target use is outside its scope.
