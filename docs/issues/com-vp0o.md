---
id: com-vp0o
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Reconcile selected existential fixtures with adopted erasure rules

## Boundary

Finite follow-up from com-8iys/com-e713 test audit; independent of audit completion and phase3. Audit makes no test/compiler repair and claims no fresh candidate execution. Source baseline9665094d, spec5bd65a5. Evidence: meta/evidence/test-audit/scoped-reviews/run-head-0087.json.

Exact run fixtures: any_array_covariant_erasure, any_array_self_member_return, any_direct_optional_match, any_heap_self_member_return, any_array_unique_concrete. spec06 generic invariance and spec08 existential copy classification/results disallow whole generic-container covariance, nominal Self-result re-erasure, and injecting unique Self into ordinary copyable any P respectively. Historical numeric outputs are internally consistent under old acceptance; changing numbers is not the remedy.

## Guarantees and Original Intent

Recover initial commits3c5d8254,40c2619b,2be38c92,9f074d9e,2f8dcebb and preserve useful direct boxing, heterogeneous dispatch, heap ownership, source independence and direct/typed match controls in admitted shapes. Add discriminating rejection controls for the now-forbidden forms. Source-admission rules must survive to actual conversion/Mid consumers; no test-name special cases or retained old successful bypass.

unique existential support is met-b2la, ordinary deinit placement met-2t3l; do not require implementing that whole future family just to stop asserting an invalid copyable box. Do not delete independent ARC/heap controls without a replacement. Related ordinary fixture reports remain separately audited.

## Completion

Contract-derived case map, fixed-candidate RED for the targeted admission mismatch, fresh relevant positive/reject checks and structural conversion evidence; scoped independent review. No whole type-checker rewrite, new covariance semantics, whole suite cleanup or audit-domain closure.


## Explicit Four-Input Extension From Batch0088

Add exactly these run inputs to the original five: any_optional_covariant_erasure,
any_optional_self_member_return, any_single_letter_trait_optional_self, and
any_sendable_erasure. The first converts Optional[Person] wholesale to
Optional[any Named]; the other three call nominal Optional[Self] results through
an existential. Current invariance/result rules differ from their historical
success assumptions. Preserve single-letter owner identity, Some/None handling,
String ownership, and legal direct Self/sendability-erasure controls. Original
intent: 3c5d8254/40c2619b/e57fb1e3/08156ab8, recorded in
meta/evidence/test-audit/scoped-reviews/runtime-batch-0088.json.

Within any_sendable_erasure, eraseArray/eraseOptional also lift sendability
guarantee erasure through nominal containers. The direct guarantee-erasure
arrows alone do not authorize that lift. Reconcile this separately against
invariance; obtain a surface decision if the adopted contract is insufficient,
rather than invent a conversion exception. Do not reject legal direct
any-sendable-to-any or direct-Self result erasure. No fixture/compiler repair or
actual execution occurred in audit; source-admission audit is still separate.

## Explicit Shared-Witness Existential Array Negative

Batch0028 adds exactly reject/trait_subject_chain_conflict_existential_array.pw/.err. Its intended shared self.b() witness-body ambiguity is explicitly adopted by spec09, independently of caller view. The input also converts inferred Array[S#C] wholesale to Array[any A], forbidden by generic invariance. Preserve the shared-body rejection with an admitted direct/element boxing contrast; its specific ambiguous-bare-call companion does not credit an unrelated container mismatch. This exact negative setup is not a new covariance exception or an all-chain audit. Neighboring direct/generic/closure/existential negatives remain separately audited, and no test was executed or edited.

## Explicit Shared-Witness Optional Negative

Batch0029 adds exactly reject/trait_subject_chain_conflict_existential_enum.pw/.err. It converts Optional[S#C] wholesale to Optional[any A], an unrelated invalid invariant-container setup. Preserve canonical shared self.b() ambiguity through legal direct/element erasure and retain the specific ambiguity companion; a generic mismatch is not a passing substitute. Optional.Some(v=...) migration is separately met-2wca. This extends the selected negative context by one exact root, not all Optional conversions.

## Explicit Loop-Binding Setup in Existing Self-Result Roots

Batch0034 source-admission audit confirms any_array_self_member_return has bare for x and for y without existing mutable bindings, and any_heap_self_member_return has one bare for x. In addition to forbidden nominal Self-result re-erasure, preserve meaningful dynamic dispatch/empty/ownership contrasts with legal loop binding forms (spec11:209) when reconciling these already exact roots. Keep label migration separately met-2wca; no duplicate general loop issue or extra unread fixture scope is added.

## Explicit Internal Existential Plan, Rebox and Payload Oracles

Batch0045 adds exactly run/{existential_declaration_plan,existential_rebox_evidence,existential_payload}.pw/.out. Declaration plan expects nominal Wrap[Self] result erasure success but rejects boxed()->(item:Self) with requirements1..<4: spec08 permits labeled-record element erasure and forbids nominal lift. Keep compare(other:Self) and assoc create nondispatchable while reconciling record/Wrap separately. Rebox helper expects direct T, Array[T], Wrap[T], nested Array[Wrap[T]] conversions from selected evidence; direct boxing remains valid, container success is not authorized by invariance. Embedded independent Array/Wrap type declarations themselves are legal; conflict is internal observed oracle, not automatically outer source admission. Payload injects unique Sq into ordinary any Shape and conforms to copyable-only Shape, violating both adopted Self capability and existential classification. Preserve useful heap/dispatch/independent ownership controls without requiring the whole future unique existential implementation or blindly altering goldens.

## Explicit Mid Call-Boundary Nominal Container Conversion Oracles

Batch0055 adds exactly run/{mid_any_array_call_repack,mid_any_nested_optional_call_repack,mid_any_optional_array_call_repack,mid_any_optional_call_repack}.pw/.out/.ll.expect. Existing Array[Sq] or nested Optional/Array/Optional[Item] values cannot implicitly become corresponding containers of existential elements under invariant generics. Retain source-selected evidence/physical payload/none-tag regression purposes in permitted structural/internal contexts or intentional source-rejection tests; do not license nominal covariance merely because Mid implements repacking. mid_any_array_literal_context is distinct valid per-element expected-type boxing contrast. No audit-time source or golden changes.
