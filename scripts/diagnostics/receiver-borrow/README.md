# Receiver borrowing lowering prototype (manual diagnostic)

This is a bounded **code generation model**, not an implementation of a general
borrow checker and not a normal/ASan test gate. It does not modify the language,
compiler sources, seed, or adopted binary.

`compare.py` generates paired Plew programs. `late` evaluates an opaque argument
before calling the reader. `early` first enters a method with borrowed `self`,
then evaluates that same argument and calls the same reader. The extra method
models the placement of an early borrow; inspect the optimized LLVM to assess
inlining. Both inputs include the same method declarations.

The controlled C argument function has no receiver pointer, no callbacks and
accesses only its own volatile scalar. The generated inputs contain no other
receiver alias mutation, escaping borrow, unique value or suspension. This
closed corpus is legal under both candidate semantics. It provides **no proof**
that arbitrary early borrows, ambient mutation or await are safe. No invalid
input is accepted as evidence for an unimplemented checker.

From the compiler repository:

```sh
python3 -B scripts/diagnostics/receiver-borrow/compare.py \
  --out tmp/receiver-borrow-measurement --iterations 200000000 --runs 7
```

Output directories must be new. Each subprocess uses the existing 60-second
watchdog; optimized linking uses the shared LLVM pipeline. Measurements alternate
order, exclude one warmup per executable and check a deterministic checksum.
Timing is inside the uninstrumented executable (loop only), separate from Python
startup/link time. Counts come from separate runtime-instrumented executables,
covering non-null retain and both release/drop decrements. They exclude setup,
printing and final teardown. Inspect `*.optimized.ll` and retain/drop placement;
counts alone do not prove balanced lifetime across all scopes.

Raw/optimized LLVM, generated sources, C support, logs, compiler/input hashes,
compile diagnostic times and runtime samples are retained. The compile times
include wrapper and tracing overhead and **do not measure the cost of either
candidate borrow/effect checker**. Do not use these data to choose a winner in
compiler speed, claim a fully implemented candidate, or weaken formal gates.
