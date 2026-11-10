---
id: met-c9m8
status: in_progress
deps: []
links: []
created: 2026-11-10T23:21:43Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Measure removal of redundant O1 before final O2 optimization


## Finite trial contract

On frozen identical compiler LLVM, compare the current shared SCC preprocessing
plus default<O1> then final O2 against SCC preprocessing alone then the same
final O2. This removes only the O1 suffix; native machine O2/CPU/PIC, verifier,
progress, sanitizer order and shared SCC sroa/early-cse/instcombine/argpromotion
remain unchanged. Start with scratch copies; production defaults stay unchanged
until a positive, validated adoption decision. No LLVM/language/backend switch.

Questions and scenarios:
- Compare baseline/candidate object-worker wall/stage times and object sizes,
  using the same copied source/toolchain and raw module, one exploratory run each.
- Link both generated compiler objects with the same existing production native
  archive/runtime. Warm both, then initially three alternating source-to-LLVM
  trials each; require exact raw LLVM/runtime agreement. If a meaningful runtime
  regression or failure appears, reject the trial rather than hide the tradeoff.
- Check candidate quiet/progress/verbose/sanitizer-symbol and failure behavior,
  and execute existing native-object fixture controls/reference outputs. Check
  corresponding external opt-prefix→clang O2 flow before any production adoption.
- Retain actual commands/hashes/gates and independent neutral review. If useful,
  synchronize the single shared header and consumers/tests/design, then perform
  a fresh standard development build/smoke. Do not infer full-suite, sanitizer
  runtime, new formal fixed point, seed/carrier/main promotion from this trial.

Investigation first: no artificial RED for changing an optimization setting.
A performance result is a measured tradeoff, not proof that O1 was semantically
unnecessary. One-run builder data is not a formal median or exact additive cost.
