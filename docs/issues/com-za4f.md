---
id: com-za4f
status: in_progress
deps: []
links: []
created: 2026-11-02T21:46:44Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Preserve global storage identity of callable values

## Contract and audit evidence

Exact met-tfbl proposed unit3; source storage result is producer fix, not backend arbitrary recovery.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `CALL-GLOBAL-RECEIVER`.

## Scope and guarantee

- met-tfbl V4 Local.isGlobal→ClosureLocal loss→final Mid receiver, simple noncapturing global only

## Scenarios

- Simple global/local counterpart check/native/JIT; exact declaration/storage identity retained to required receiver preflight.

## Excluded

- No new capture support or weakening preflight/string-ID recovery.

Existing global fn passes check but native/JIT fails; no repaired output claim.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "met-acfl", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Required predecessor for com-r88j

Use the source target publication already implemented in eab68d76; do not depend on closure of com-r88j. com-r88j now depends on this task (tk accepted, no cycle). The newer global target must not break legitimate existing global-initializer preparation. `prepared_access_source_owner` passes with the frozen c07a4ce0 source/carrier and aborts with eab68d76 because its initializer callback is categorically rejected as ClosureGlobal. Normal function global callable execution was already unsupported and remains this task's original scope.

TDD: `tests/fixtures/run/global_callable_storage.pw` checks global-initializer call, ordinary function global call and local shadow (expected 42/42/7). eab68d76 candidate accepts check but rejects AOT/ORC Internal; meta scratch `tmp/phase3-lexical-call-binding/global-storage-red.json`. Keep global declaration target distinct through CallResolution, validate against retained source template and canonical global storage, use existing global MidPlace/LLVM helpers. No name/string recovery, no preflight weakening, no capture support expansion. Additional controls: imported alias/module global, return/function ABI, malformed target/type and local/global confusion, existing initializer source-owner probe, standard local closure positives.

Completion requires actual native/ORC receiver execution, retained-owner negative probes, original initializer prefix and applicable gates plus independent review. Source preparation alone does not close this task.

## Canonical snapshot implementation checkpoint

The global source target now stays distinct in CallTarget, with a function-typed Borrow receiver. Mid construction copies the whole selected global into the normal owned evaluation temporary before arguments; call-scope cleanup owns its release. LLVM consumes that canonical receiver operand, never synthesizes a hidden global read/retain. `evaluationGlobalOrigin: Optional[U64]` preserves the source declaration (target 0 is valid); Assign, receiver and mutation checks verify the actual origin, instantiation/pass boundaries preserve it, and the two copy-transfer rewrites keep these homes intact.

New manual `GlobalCallableSnapshotOrigin` demonstrated native RED for same-type global Assign-source replacement; current source-native GREEN additionally rejects a same-type receiver swap. `GlobalCallableDependencyOrder` verifies genuine callable-value cycle rejection and failed-owner retry without publishing an initializer plan. Native temporary probes are in meta scratch `tmp/phase3-free-function-ambiguity/`. These are finite assertions, not full adoption.

Alias startup smoke exposed a missing callable-value dependency. A name-based draft also caused a genuine pow false-cycle RED, so it is not the final implementation. The common `prepareGlobalInitializers` now prepares all source owners before adding only saved Dynamic.ClosureGlobal edges through the existing per-owner CallTemplate index, then admits order before any initializer Mid publication. The registration-time preliminary sort is retained; the three ordinary consumers use the shared completed preparation, with repeated requests cached only after success. Late ordering keeps declaration-target keyed source/type/request state; LLVM global row lookup is deferred until after the order is fixed. General block/callee-effect startup summary closure remains com-fkxl.

Latest source check exits 0. Fixed snapshot build 20261120T013634-build-79ca57 is running, candidate location `tmp/phase3-global-call-storage/adoption-build/bin/plewc`; it is not yet an adopted carrier. Required next checks include fresh native/ORC global and alias outputs, named pow/non-named callable pow, existing initializer source-owner prefix and free-call cache fault, origin/mutation fault extensions, LLVM22 lifetime checking, same-source performance, full normal suite and independent acceptance.

The single-global self-call cycle also has native RED/GREEN: the former n<=1 ordering shortcut published a plan, and n==0 now leaves one-global inputs in DFS. Provenance tracking is requested only for global callee evaluation homes; ordinary snapshots keep their existing capabilities. Expanded native origin controls reject same-type receiver/source swaps, origin-only forgery, Overwrite and inout, while accepting the matching Read. The preceding cf0831 candidate passed five global/alias/pow fixtures in 15 modes and five native executions, but predates the last two corrections and is not final evidence. The unchanged free_call_failure_domain internal control now passes native with the corrected raw-cache handling.
