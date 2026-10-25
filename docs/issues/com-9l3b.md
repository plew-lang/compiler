---
id: com-9l3b
status: open
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

## Current Candidate Refresh

Reopened for the source repair e73a8476 in [com-ugee](com-ugee.md). The prior
043e2402/3c532ce1 gate remains valid only for its recorded inputs/binary; it does
not certify the new source or candidate073f0375. G1 current admission and the
actual final measured compiler must determine which checks can apply. The
current ordinary suite on candidate073f0375 is a repair milestone, not evidence
that an as-yet unmeasured successor passed the gate. Do not weaken any final
fixed-point, performance, gen/deps or LLVM22 sanitizer requirement.

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

## Current Frozen-Candidate Gate Progress

Measured compiler3c532ce1 from G2a20261025T061121-self-host-f849e0
passes normal20261025T062041-test-509a3f: run1524, panic50, reject1029,
part93, partreject84, midcoverage1 and midborrowedread1; skip0/fail0,
exit0 and inputs unchanged. Receipt
meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-normal.json.
Full gen20261025T065138-gen-d05081 passes25 positive/5 reject, skip0/
fail0 and gen-input-ast; deps20261025T065242-deps-1bd648 passes all10
dependency checks. Both exit0 with unchanged inputs. Corresponding tracked
receipts phase3g-gen.json / phase3g-deps.json retain exact compiler and result
hashes. LLVM22 full ASan-LSan20261025T065258-asan-3d0f5a exits0 with unchanged
5,990 inputs: A1/B2603/C1524/D50/E80, all levels clean,76.38 minutes.
Receipt phase3g-asan.json. Independent c2_classification_review accepts all final gates/identities/inputs;
G3 and the parent remain unaccepted until final synchronization.

All four profiles use exact measured compiler3c532ce1 from refreshed G2a.
A byte-identical convenience copy is saved as bin/plewc-phase3-final; this
is a candidate, not adoption, seed promotion or a replacement of tracked bin/plewc.

The earlier gen failure is retained at
meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-gen-initial-failure.json.
com-v1wa/com-tkz7 independently close the synthetic owner/span producer and
common named-Make recovery; their scoped gen25/5 does not replace this final
measured-candidate gen gate. No valid old fixture expectation was changed.

## Outcome

Independent c2_classification_review accepts this bounded gate task. All four
receipt/raw/config/log hashes and each5,990-input before/after/current map
match the frozen source and G1. G2a shared inputs match except profile-specific
tools/carrier. Actual measured compiler3c532ce1 is common to all profiles.
LLVM22.1.8 tools, every A-E final marker, E80 exact manifest/3A registration,
raw compiler instrumentation and actual UAF detector controls are confirmed.
No skips/failures or missing final markers.

Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-final-gates.json
links the four tracked gates. G3 now owns final eleven-criterion synchronization.
This does not close phase4/com-604k or promote main/seeds/adopted carrier.
