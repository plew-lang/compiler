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

To measure the existing full source-to-LLVM path on a generated benchmark:

```sh
/usr/bin/python3 -B scripts/support/watch-command.py -- /usr/bin/python3 -B scripts/diagnostics/orc-restart/source-baseline.py --source tmp/orc-restart/delta/cow-3.pw --out tmp/orc-restart/source-cow
```

Run `bench.py` first to generate that input. The outer watchdog supervises the
worker and its compiler children. Each sample launches the adopted compiler;
startup, source loading/checking, LLVM emission, output-file writes and process
exit are included. JIT and application restart are excluded. The first sample
is reported separately; subsequent samples are warm-filesystem but fresh-process
measurements. Identical output hashes are checked. This is neither a pure
frontend timing nor a prediction of a persistent incremental compiler's speed.

Managed execution-region lifecycle probe:

```sh
/usr/bin/python3 -B scripts/diagnostics/orc-restart/region-check.py --runs 101 --out tmp/orc-restart/region
```

`Region.pw` owns a mutable global counter, global Array, captured Array closure,
and suspended async frame/timer. Normal AOT must print the continuation; the
region host must print only the initial values on every generation. An empty
process argument exercises the runtime's immortal empty-string cache.

This diagnostic wraps allocation calls in the generated C runtime with a
single-threaded allocation ledger. At a quiescent host boundary it disables
further dispatch, clears the known runtime roots, frees remaining region
allocations without running application cleanup, and removes the generation's
JITDylib. The standard allocator/ARC behavior during execution is retained;
region disposal is a separate development-environment termination operation.
The normal event-loop drain is exposed as `probe_drain`, while generated main's
automatic drain is held by the host. The empty-string cache is epoch-invalidated
using an exact, checked source adaptation. Dictionary random seed stays host-lived.

macOS can retain a dylib after `dlclose` (observed here with this runtime), so
explicit runtime state reset is required. Unloading is not used as proof of reset.
The counter and app globals belong to the newly generated application module.
The ledger deliberately rejects unknown/double frees; its linear searches are
for lifecycle diagnosis, not the chosen production allocator design.

This tests one active environment with no live native stack and a simulated
host event transport. It does not implement general FFI teardown, isolated
concurrent runtimes, source-to-restart timing, or a final
runtime ABI. No sanitizer claim is made. The normal compiler/runtime/seed are
unchanged; adaptations are confined to this diagnostic build.

The lifecycle host also models an external event transport with generation IDs
and scalar payloads only. It looks up a marked Plew event function (exported for
this diagnostic) and verifies that current events execute, while old events are
rejected during shutdown, after code removal, and after the next generation
starts. No old function pointer is retained by the simulated transport. This
covers that host boundary, not arbitrary native callback APIs or concurrent
arrival from other threads.

An intentionally unresolved candidate JITDylib is materialized while the old
application is still suspended. Its lookup must fail, its resources are removed,
and the old application's event handler and pending work must remain usable.
The expected missing-symbol diagnostic is saved in the lifecycle stderr log.
This covers link failure before publication; source rejection and initialization
failure are separate remaining end-to-end cases.

Source-to-ready restart probe:

```sh
/usr/bin/python3 -B scripts/support/watch-command.py -- /usr/bin/python3 -B scripts/diagnostics/orc-restart/restart-check.py --runs 21 --out tmp/orc-restart/restart
```

A persistent ORC host keeps the old app while Python saves a changed source.
Timing starts at the explicit request, before invoking the compiler. It includes
compiler/watchdog launch, full source processing, LLVM file output, host command
transport, parsing/verifying/materializing the complete candidate, old region
termination, new main/global initialization, and a successful current-generation
Plew event call. No compile runs on save. Initial host/runtime setup is outside
this already-running-app measurement; the first app load is reported separately.
There is no lazy compile deferred beyond READY. Normal source checks and the LLVM
verifier remain enabled. The current configuration uses no explicit LLVM IR
optimization pipeline and LLJIT's default native codegen.

Every revision changes the event function's result, and every revision's LLVM is
also linked and checked with normal AOT outside the timed path. Full recompilation
avoids an unproven dependency cache; this is not a completed incremental frontend.
READY requires an actual successful event dispatch, not just a published pointer.
The report retains all timings and hashes, with warm median/p95/max and counts
over 500 ms; first load is separate. The deadline is evaluated from that report,
not encoded as a correctness assertion.

A source type error and invalid LLVM leave the old event handler usable. An
injected host readiness failure after main returns disposes the new region and
leaves no active application; the next valid request recovers. This is not
catching a Plew panic, an OS fault, or an arbitrary constructor failure. Candidate
link-failure preservation remains covered by `region-check.py`. Native LLVM
constructors are explicitly unsupported in this diagnostic. Protocol paths must
not contain whitespace. The same managed-region and FFI limitations apply.

`--scenario mixed` alternates record layout, helper signature, generic record
layout/instantiation, and imported module body changes. `--functions 100` adds
100 live helper calls in separate statements; `--expression-shape deep` instead
puts them into one nested addition expression. Preserve the distinction: the
deep form stalled before LLVM output under the 60-second watchdog, while the
flat form completed. The harness records the generated module texts and case
kind per revision. Full source compilation covers these dependency changes;
these results do not establish a correct incremental invalidation algorithm.
Commands emit phase progress and checkpoint the report before child execution.
