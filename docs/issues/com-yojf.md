---
id: com-yojf
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, verification]
---
# Resolve the stronger universal nominal proof audit with bounded counterexamples

## Boundary

Phase 3B / B4. **Bounded investigation; no speculative semantic change.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ia09](met-ia09.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/InterfaceEvidence.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Codegen/Mono/Call.pw`.

Inspect replayConstraintProof/replaySelectedWitness and declaration dependency classification for four proof roots: interface assumption, nominal witness with hidden arguments, conditional witness, associated/supertrait projection. Construct a minimal promised member, unguaranteed unused member and malformed-proof contrast; follow boxing and final dynamic use. Reuse the saved f67c8fce availability controls.

## Exit and Evidence

Record which exact root/child conditions establish universal admission versus concrete readiness, with source locations and positive/counterexample results. Do not try to prove all possible predicates. If an unsound edge is reproduced, create a bounded mandatory repair child and block the area and G1 on it; this investigation may close only with that exact disposition. If meaning or ABI is undecidable from policy, stop for a user decision. An unavailable member and corrupt evidence remain distinct.

Existing starting controls: `interface_declared_guarantees`, `interface_final_evidence`, `interface_boxing_conditions`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
