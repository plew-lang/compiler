---
id: com-9l3b
status: in_progress
deps: [com-p5um, com-o3vw, com-rtki, com-9d1o, com-0uw9, com-16gs, com-cev5, com-072n, com-3qne, com-uuya, com-vuv9, com-6cw6, com-v1wa, com-tkz7]
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

## First Frozen-Candidate Gate Failure

20261025T034939-test-9cc5f8 on measured 73078e5d exits 1 with unchanged
inputs: run 1520, panic 50, reject 1011, part 93 and partreject 84 success;
skip 0 / fail 15. All fifteen are diagnostic mismatches in the existing
trait_subject_chain_conflict family and try_from_body_obligation. Eleven now
report internal multiple receiver copies; four report no matching method.
Same-input old 6ddf8f75 produces all fifteen expected ambiguous bare refusals,
while fresh c50d2a04 and measured 73078e5d reproduce all regressions.
Do not change these valid language-test expectations or count this normal green.

Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-normal-initial-failure.json
retains gate totals and comparison hashes. Required source-copy placement repair [com-6cw6](com-6cw6.md) has an independently
reviewed finite scope and explicit dependencies. Affected area/G1
admission must reopen; G2b remains incomplete. Gen/deps/ASan were not started.

## Refreshed Candidate Gate Progress

Measured compiler2d7c785b from refreshed G2a passes full normal
20261025T051128-test-ed8f9a: run1523, panic50, reject1028, part93,
partreject84, midcoverage1, midborrowedread1; skip0/fail0, exit0, inputs
unchanged. Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-normal.json.
The original fifteen regressions remain fixed without expectation edits.
Gen20261025T054226-gen-36c9dc fails directiveargs harness compilation,
23 positive/5 reject/1 failure, exit1 and unchanged inputs. Receipt
meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-gen-initial-failure.json.
Independent scoped repairs com-v1wa/com-tkz7 retain selected derive type and
close common untyped Make admission separately. Affected areas/G1/G2a reopen
for changed inputs. Deps/LLVM22 ASan-LSan were not started.
