---
id: met-c9m8
status: closed
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

## Outcome

Investigated; reject trial and keep production O1→O2 unchanged. The matched
object-worker trial improves224.617706→220.198212s, only4.419494s on one run each.
Later O2/codegen work grows and object size grows about1.471%. Generated compiler
same-source medians after warmup are8.019973→8.335548s (+about3.935%), with all3
alternating pairs slower. All8 LLVM outputs and both runtimes agree. This meets
the predeclared rejection criterion, so no production adoption/build was pursued.

Candidate native-worker mode/failure/sanitizer-symbol controls, native fixtures,
check/lazy outputs, external prefix→clang O2 executions and existing nested
byval-delegate promotion controls all pass with immutable inputs unchanged.
The linked compilers share the original production native archive; scratch
candidate worker directly validates the changed pipeline. No source defaults,
seed/adopted carrier or main were changed. No formal new fixed point/full suite,
LLVM22 performance or full sanitizer runtime success is inferred.

[Measured evidence, limits and reproduction](../../../evidence/ir-o2-trial/README.md).
[Independent neutral review](../../../evidence/ir-o2-trial/final-review.json)
confirms the source difference/artifacts/receipts/assertions and supports rejection
without additional trials. Closure reason: investigated (optional trial rejected).
The current-policy reason is also retained in the backend design; the precise
pass/code-quality cause was not profiled and is not a required follow-up repair.
