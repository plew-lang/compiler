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
