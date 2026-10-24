---
id: com-fuo8
status: in_progress
deps: [com-2suv, com-0ssn, com-9tau, com-gnj9]
links: []
created: 2026-10-21T15:16:01Z
type: epic
priority: 1
assignee: Koji Murata
parent: com-tijs
tags: [design, verification]
---
# Close saved completion and divergence for admitted expression forms

## Bounded Execution and Gate Ownership

This is an area epic, not one executable multi-week task. Its current bounded
work and real prerequisites are tk dependencies under the
[parent policy](met-si6j.md#bounded-task-policy):

- [E1](com-2suv.md): normal-result and exit composition.
- [E2](com-0ssn.md): transfer errors versus loop warnings.
- [E3](com-9tau.md): diverging callable type/value/invocation.
- [E4](com-gnj9.md): saved exits through Mid cleanup/final use.

Close this area's exact existing contract after required children/repairs and
their scoped fresh verification. The final frozen candidate normal/gen/deps/full
sanitizer/fixed-point/performance obligation is explicitly owned by
[G2a](com-p5um.md)/[G2b](com-9l3b.md) and cannot be waived when this
area closes. Historical checkpoint gates are not current-candidate certification.
Earlier current/next/WIP observations refer to their named revisions; the bounded
children reconcile what actually remains before any repair. No new meaning or
unsupported feature is authorized by this allocation.

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-tijs](com-tijs.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Existing block/if/match/short-circuit/while/for/return/give/break/continue and admitted diverging function types/calls. New loop/value-bearing break syntax or other absent constructs are excluded. Approved value-position rejection and following-code errors versus analytical-loop warnings remain in scope.

## Producer to Final Consumer and Removal

SourceCompletion shared semantic/execution completion and exit targets -> successful owner facts and explicit instance readers -> Mid CFG/ownership cleanup -> LLVM and JIT. Preserve existing isDiverging carriers and source/execution distinction. Remove old last-statement and AST/name-based duplicate decisions without introducing Never/Unit fallbacks.

## Completion and Verification

Direct and wrapped values, empty match, nested valid exits, diverging function type conversion rejection, explicit transfer following-code errors, analytical unreachable warning/static checking and positive loop-exit ownership controls. Reassess historic fixtures against adopted semantics; current-source continuation joins are owned with com-gyup. No missing syntax is silently added.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
