---
id: met-6e6k
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Audit saved conversions, descriptors and first-concrete consumer boundaries

Complete the consumer audit adjacent to source publication and callee proof transfer. Saved source result/signature/conversion/projection facts and descriptor dependencies must be interpreted with explicit source and instance identity; declaration dependency scope is not runtime descriptor reachability. Construction of first concrete evidence is permitted only within the source-selected requirement; final readers must not return to AST/type-name/ambient-cursor selection.

Audit dynamic/closure descriptors, optional payloads, result/parameter signatures, nominal registration/binder stamping, final conversion proof endpoints, structural/path/Box admission and projection normalization input/output/proof identity. Do not erase semantic/phantom arguments merely because machine payload layout ignores them. Existential inherited-interface collection is a separate feature from correct supertrait projection normalization; broader unsupported shape work is com-uutc/com-b1ro.

Acceptance: record demanded dependency paths, typed endpoint/scope/owner validation and final consumer for each family; preserve declaration checks without incorrectly demanding execution readiness. Show removal of duplicate decisions and missing-result fallbacks through AOT/JIT, including prior-call-dependent results and generated bodies. This is unfinished audit/migration, not proof of a current source-level defect.

Retained representation audit: CallTemplateReceiver.Opaque descriptions that compiler-internal types need no semantic term, and Verify/Call comments that C handles are interchangeable, must not authorize erasing semantic type identity. Inspect actual uses before changing them; machine handle/layout equality is not source compatibility. Check/Literal associated-function inference, groundedTypeOf/typeOf and construction fallback entry points remain classified producer/reader audit targets, not blanket deletion requests. Preserve operator result projection (Ord -> Bool, Ne negation) from saved operation identity.

Dependency identity rechecked at `2983c47ff7ba0b1d693d656094e9fd0dbeca63dc`: Check/Obligations.sourceCallArgumentType passes PriorCallResult.siteKey to Check/Bounds.sourceSelectedCallResult, which finds the selected template and compares the result recipe's callSite. The historical ignored-siteKey observation is not current for this path. Preserve matching/wrong-key tests during migration; other recipe variants and final-consumer closure still require their own evidence. The finite [restart reconciliation](met-j9mv.md#cumulative-restart-reconciliation) identifies current entry points and consumers; it is not a full correctness audit.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Existing conversion/projection/descriptor/result-recipe and first-concrete consumers, including PriorCallResult.siteKey controls. Preserve implemented checks; remove legacy unstamped/name/cursor decisions only with matching producer migration. No new existential/interface feature is inferred from this task.


## Nominal Body-Receiver Identity Increment

The registered-carrier repair of mid_type_recipe_instances adds a same-spelled
carrier with a different declaration identity. It exposed sameBodyRuntimeRef
comparing only names/arguments when interning body environments, which merged
that foreign receiver with the intended carrier and attempted to publish a
second different call at one body/site. Prefer canonical declaration identity
when both terms have it, including aliases whose authored spellings differ.
Keep the existing bootstrap legacy fallback only where a producer lacks it; its
remaining removal is still part of the producer audit, not proof of completeness.

The internal recipe fixture uses the normal binder and Arena.registerEnum APIs
to supply a real nominal generic payload carrier. It remains a Mid-only test,
without requiring frontend initialization, a source body or executing a callable.
Its instance-specific results, cross-instance cursor, missing publication,
known Unit, forged Unit and absent-result controls are preserved. Added controls
reject a foreign nominal payload and require distinct body identities. A duplicate
statement-owned final publication reports through CallSiteKey rather than reading
a nonexistent source expression for its diagnostic. Current-source imported AOT
passes; fresh compiler/full gates remain separate.

## Canonical Grounded-Argument Read Increment

A new ordinary source control reproduces an incorrect rejection of
keep(value: <Box value=42I64 />) when keep's unrelated generic parameter is also
named Box. The final descriptor contains a canonical closed Box[I64] nominal term,
but finalStaticCalleeIsComplete called fnArgsAllGround/tyRefIsGround, whose legacy
global parameter-name query classified the generic nominal head as symbolic.
A virtual Iterator control reproduced the same issue with Cursor[Item]. Its
canonical typeIsClosed result is true, while the name-based query returns false.

Final descriptor validation now reads canonical argument closedness directly,
rejecting zero/missing and genuinely open terms without resolveTy or global name
queries. Construction tyRefIsGround also defers to canonical closedness when the
nominal declaration is already known. The legacy unstamped construction path
remains separately auditable; this does not certify every type producer.
The new nominal/binder source fixture preserves the old failure as a negative
carrier control. Current-source imported implicit-call and owner-request controls
pass after the canonical repair; fresh/full gates remain required.
