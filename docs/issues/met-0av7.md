---
id: met-0av7
status: closed
deps: [met-6hrd, met-zcig]
links: []
created: 2026-11-23T19:21:47Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ajht
tags: [frontend, generics, verification]
---
# Realize inherited existential witnesses from retained interface slots

## Guarantee and responsibility

Consume the declaration-owned effective interface and selected ancestor proof at concrete existential boxing. Preserve original declaration identity, parent instance bindings, modes and ordered slots through implementation selection, callee environment, Prepared/Final/Ready descriptors and LLVM vtables. Keep the existing fat-any layout and every effective slot, including explicit unavailable entries; do not compact indices or pass effective slots into raw TraitDef.reqs. Static requirement declaration readers remain raw.

Prepare ancestor proofs once in retained topological order from the root box evidence, replaying every exact declaration edge and checking converging instances/witness identity. Propagate failed admission before warm cache hits. Canonical candidate aliases do not certify proof equality. Concrete selection and its environment consume the same selected parent proof; root box evidence remains separate for Self re-erasure. No source overload/conformance reselection belongs in backend emission.

Logical existentialWitnessPlan and checkAbstractExistentialPlans interpret retained Interface evidence without requiring a closed payload or publishing executable bodies. Concrete prepareExistentialMember consumes its already selected parent Static proof at the canonical body receiver. Both interpret the same result recipe, preserving Unit normalization, ownership modes and recursive Self conversion. No closedness-based fallback joins these stages.

Final interface calls retain the full validated signature plus source/instance roots, caller, receiver, trait, slot and source interface token. Mid consumes this saved signature instead of re-reading root requirements. Physical endpoint checks preserve range, mode/count, storage/lane/result and malformed-evidence rejection; missing preparation cannot emit an undersized vtable or invalid IR.

## RED and repairs

Initial native RED showed direct Index success but an inherited prepared box with zero members; a second showed failed admission bypassed by a warm box cache. Actual Mid later retained the old direct-only signature lookup. Whole integration then exposed an abstract/concrete planning regression: unchanged existential_declaration_plan must plan generic assumed evidence without materializing a concrete witness. Child [met-zcig](met-zcig.md) restores that boundary and adds inherited generic/Self coverage rather than replacing the original fixture with concrete input.

Sibling [met-8dme](met-8dme.md) distinguishes retained slot identity from missing canonical authored occurrences; [met-27bt](met-27bt.md) updates private Ready setup with genuine source receipts and keeps synthetic ABI-only cases at their own layer. Their old failures are not silently removed from whole integration results.

## Accepted finite boundary

Productb8c69b69/teste2d7e969, fresh build20261124T003907-build-59c66a: exit0, invariant inputs,194 frozen/current source files equal. Optimized candidate e2fd62b5b78e144a560a3d88c72892267e51c240c80948d001ca2ffe43a2f32b passes CLI45, symbolic API native3, native15 and LLVM22 ASan/LSan15. Current private witnesses pass ASan with24030 actual function checks; standard optimized Ready runner preserves all21modes and physical declaration/call negatives.

Independent reviewer typing_obligation_plan_review recomputed source/candidate/input/artifact hashes, checked all30 native/memory artifacts and actual hooks, and certified this repaired finite boundary plus met-zcig/met-8dme/met-27bt with no mandatory gap. Review was artifact/source verification, not an independent rerun. Exact reports and guarantees are in [canonical integration repairs](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-inherited-existential-interface.json).

Parent [met-lrep](met-lrep.md) still owns new formal fixed point/performance<=7.5s, measured-candidate controls, full normal reconciliation and final integration review. No main/seed/carrier promotion or whole-green claim follows from this finite closure.
