---
id: com-kd1s
status: in_progress
deps: []
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Retain and validate authored binding storage facts

## Guarantee and Scope

Carry declared binding identity/mutability from accepted SourceFacts through Mid freeze and instantiation to the production origin checker. Cover immutable/mutable/shadowed/reinitialized/capture/borrowed/synthetic roots, foreign/missing/forged facts, unchanged input snapshots. Unknown synthetic roots stay unproved. No snapshot elimination or ABI transport change in this unit.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.



## Storage Receipt Design Boundary

The source declaration target and mutability are published in the existing
owner-local SourceBindingFact, never re-inferred by LLVM. The next handoff must
reuse existing sealed readers rather than create a duplicate semantic fact table.
Fresh-context review first suggested one reader receipt per body, but actual
buildParametricMidGlobalInit combines nested lets from multiple global owners in
one canonical body. That alternative is rejected: global block expressions stay
in scope. A local raw origin of session/reader/binding-row identities is the
current implementation; it can reference the existing sealed
row without retaining the entire frontend payload in Mid. Owner checks should
be cached per reader within a body verification, not repeated per local.

Before implementing that handoff, fix the exact authenticity/absence contract:
valid numerical IDs and an origin tag alone do not establish trust. Preserve
binding identity across freeze/instance, reject another session/owner/binding,
and detect a required authored receipt removed from its accepted declaration.
Consider an indexed declarationTarget navigation to the same fact rows for
independent expected-origin checking; no second mutability authority is allowed.
Synthetic, borrowed pattern, parameter and capture-cell roots must not inherit
a source-local const guarantee. Raw hand-built unproved IR controls must remain
explicitly distinct from accepted authored source origins. The source-record
increment does not establish this downstream proof.

## Source-Record Increment

The accepted Let producer now saves declarationTarget and isMutable in its
existing SourceBindingFact. The new internal fixture checks distinct shadowed
declarations, immutable/mutable locals and globals, owner isolation and sealed
reader stability. Old-candidate missing-field structural RED, fresh standard
build and four raw-O0 runtime GREEN controls are recorded in the
[first increment](../../../evidence/performance-regression-history/value-passing-implementation/binding-facts-first-increment.json).
A fresh-context neutral source review found no contract violation in this
limited increment and independently matched build/candidate/input hashes, all
four actual compile/link/run paths and exact goldens there.
This does not close this task: receipt/origin retention, missing/foreign/forged
production checks and remaining root-family controls are still required.

## Origin Propagation Increment

SourceBindingOrigin is shared pure-IR raw data (the existing Frontend→Mid/Ir
dependency forbids placing the type in Frontend). Public record construction is
not authority: only current-session/source-owner/declaration validation can
establish it. The all-zero state is unproved; partial-zero/foreign/outside rows
are errors. Accepted Let rows reach Mid locals/freeze/instance, and the normal
verifier checks all present origins with one reader acquisition per distinct
reader in a body. Existing unproved hand-built IR retains its old contract.
[Evidence and neutral review](../../../evidence/performance-regression-history/value-passing-implementation/binding-origins-increment.json)
cover an actual authored body, a matching raw control, five malformed groups,
declaration indexing and unchanged synthetic/instance controls. This remains
WIP: the production request path must require the expected authored origins
before and after preparation, including mixed global-owner bodies; present-row
validation alone cannot detect removal or select the expected local. No reuse
optimization is enabled.

## Next Production Enforcement Contract

Neutral pre-implementation review at 5a0bbdad requires a two-step obligation.
First, use accepted source rows as an allowed-origin index to validate every
actually built local: if its declaration names an accepted binding, require the
corresponding origin rather than trusting a tag. Then retain the realized local
occurrences and compare them after instance/access/optimization/drop preparation.
Do not require every SourceFacts row to have a local or reject duplicate source
rows without proof: noncontinuing initialization and closed CFG paths can omit
locals, later globals may never be lowered, and repeated default evaluation can
have multiple occurrences. This verifies realized correspondence/retention, not
source AST lowering completeness.

Choose source owners in the same order as the production builder: closure
signature -> same preparedClosureSemanticFacts; global sentinel -> each global
reader (exclude the top-level global binding itself from local expectations);
registered environment-drop/witness and adapterTargetBodyId branches -> explicit
source-free expectation; otherwise -> preparedFunctionSemanticFacts(fnIdx), as
buildParametricMidBody does. Default generators have independent source owners
and must not be declared source-free just because they are synthesized. Provided
bodies normalize via semanticBodyOwner; generic instances reuse their parametric
source identity. Source lookup failure is an error, never an empty expectation.

Required controls additionally include noncontinuing let, closed paths/later
globals, repeated block-default evaluation, provided bodies, two instances,
mixed global readers and each registered synthetic family. The existing neutral
review located these boundaries in Build:2480,2754,3696,3766; Program:62–84; and
Resolve/Expr:777–790. This is a reviewed implementation plan, not executed proof.


## Production Increment and Fresh-Candidate Gap

The builder now publishes explicit source admission on every successful new/cache
path. Production requests validate realized locals against accepted origins and
retain their declaration/origin prefix through preparation. Runtime missing-origin
RED, seven executed owner/retention/closed-path controls, full source manifests
and neutral reviews are in the
[production increment](../../../evidence/performance-regression-history/value-passing-implementation/binding-production-enforcement.json).
The complete-source build also caught a missing diagnostic enum consumer; its
separate structural RED/GREEN and adapter repair are recorded there.

Standard fresh build `20261109T181351-build-866cc9` passed with unchanged inputs.
However, fresh candidate `535c4c602f8ccfeac91c744c5056741f36cccd1b8a406dd84e061b3662b199d7`
rejects the large imported program with conflicting source binding storage
origins. The small inner-source controls do not discharge this failure. Investigate
the declaration-target uniqueness assumption against actual source/lowered
statement identities; do not merely overwrite accepted origins or discard the
check. Resolve it and rerun fresh-candidate controls before closure. No stable-home
selection or ABI transport is enabled, and W1a remains in progress.
