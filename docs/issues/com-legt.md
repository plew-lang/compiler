---
id: com-legt
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 1
assignee: Koji Murata
parent: met-op15
tags: [design, verification]
---
# Use registered identity for existing standard reference operations

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [met-op15](met-op15.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Existing Ref/MutableRef/WeakRef/WeakMutableRef and their current construction, copy/drop, projection, weak restoration and registered intrinsic handoffs. Existing compiler-known operation ownership/signature admission must remain exact. FrozenRef/MutexRef/Guard/Weakable, new .*, WeakRef[R] public API migration and user projection traits are excluded.

## Producer to Final Consumer and Removal

Standard declaration registration -> semantic term and selected intrinsic identity -> Mono/Helpers reference predicates and current weak/projection consumers -> shared runtime copy/drop/upgrade. Replace spelling-plus-arity authority with exact registered declarations without bypassing ordinary visibility or accepting forged trusted signatures. Preserve the useful owner-qualified runtimeIntrinsicDeclaration enum lane.

## Completion and Verification

Same-named unrelated user types versus exact standard declarations, qualified/re-exported standard uses, known intrinsic valid/invalid signatures, strong/weak expiration and restoration, alias mutation and cell pin during current inout projection. Verify AOT/JIT and ownership failure/cleanup; no new public pointer API is required.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 46.

Row46: FrozenRef/MutexRef/Guard/Weakable, new .* and WeakRef[R] remain outside. Current I64/I32 negative/alias/lifetime controls remain useful; API difference alone does not make fixture wrong. Source type/place and selected method admissions must consume exact identity. met-op15 exact broad contexts preserve current arrow field/method type checks, root/cell lifetime/writeback and weak operations. The real current repair owner is com-legt (registered identity through semantic terms, selected intrinsic/projection and runtime copy/drop/upgrade), not the full new-reference migration parent. Required admission: com-604k, met-6e6k, met-ucze.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
