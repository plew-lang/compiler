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
clang/JIT pass sequences. Runtime C uses O2 for ORC; AOT compiles it with the selected O0/O2 mode.

This verifies selected normal executions only: it is not repeated application
restart, a memory-safety gate, source incremental compilation, mobile support,
or an end-to-end restart latency measurement. The diagnostic host deliberately
uses the current native target; cross-target use is outside its scope.

Backend-only repeated updates:

```sh
/usr/bin/python3 -B scripts/diagnostics/orc-restart/bench.py --runs 101 --out tmp/orc-restart/delta
```

`bench.py` generates Plew arithmetic (1/10/100 functions) and Array CoW
(3 functions) programs and checks their initial results with AOT. `delta.cpp`
extracts functions identified by unique constants, retains a compiled Plew
caller, and changes those constants for every generation. Writable call slots
connect that unchanged caller to new native code. This is controlled IR
extraction, not automatic source dependency analysis or the proposed final ABI.
Backing helpers/constants remain in the base module. Function signatures and
data layouts never change. All updates occur with no old stack, frame, closure,
or callback alive; application teardown is not tested here.

Each update includes IR parsing/patching, verification/optimization, registration,
materializing lookup (code generation/linking), publication/first call, and old
resource removal with symbol-absence checks. Initial JIT/base preparation and
the first update are reported separately; median/p95 exclude the first update.
Every result is checked against the generation-specific expected value.
The real JITLink allocator is wrapped to verify successful frees: during updates
only base plus current generation may remain, and at completion only base remains.
RSS samples are supplementary and do not by themselves prove absence of leaks.
These timings exclude source reading, frontend work and application restart.

Samples are streamed to `.samples.jsonl` rather than retained in the JIT host.
Dead symbol-pool entries are reclaimed after resource removal (included in
removal timing), so neither measurement records nor old interned symbol names
intentionally accumulate in the measured process. Log output is outside the
reported update latency. Python summarizes results after the host exits.
