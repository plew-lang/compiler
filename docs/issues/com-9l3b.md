---
id: com-9l3b
status: in_progress
deps: [com-p5um, com-o3vw, com-rtki, com-9d1o, com-0uw9, com-16gs, com-cev5, com-072n, com-3qne, com-uuya, com-vuv9]
links: []
created: 2026-10-23T10:41:59Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Run all final correctness and sanitizer gates on the measured compiler

## Boundary

Phase 3G / G2b. **Final standard gates.** Parent criteria: 10.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `tests/harness/test.sh`; `tests/harness/test-gen.sh`; `tests/harness/test-deps.sh`; `tests/harness/asan-gate.sh`; `tests/sanitizer/asan-ownership-cases.txt`.

Use G2a measured compiler and the same frozen source/inputs for meta ./validate test, gen, deps and asan. The sanitizer profile uses LLVM22 and its required A–E coverage, including 3A ownership registration and detector controls. Reuse evidence only when exact inputs/compiler/conditions and required scope match.

## Exit and Evidence

All standard profiles terminate successfully, no skips/failures, required final markers and artifact/input hashes are recorded. Generated-program sanitizer checks never substitute for compiler-instrumented E. Any gate failure returns to a named source/test/tool owner and invalidated receipts are refreshed; do not accumulate anonymous repairs inside this task.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
