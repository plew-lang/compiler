---
id: com-d607
status: open
deps: []
links: [com-m4kt, com-08i0]
created: 2026-11-19T00:08:30Z
type: bug
priority: 2
assignee: Koji Murata
parent: com-an0b
tags: [mid, backend, verification]
---
# Validate canonical enum fields and preserve payload destination mapping

## Contract and observed failure

Canonical enum construction must agree with its same-session finalized variant field layout. It must initialize each required field exactly once with the admitted type and boxing, and preserve child evaluation order separately from destination field placement. Mid verification and LLVM applicability/emission consume this contract rather than guessing from self-reported aggregate metadata.

An independently reviewed native raw-Mid probe establishes a ready, two-field I64/Bool enum contract, then calls verifyExecutableCanonicalMidBody. Missing/all-absent/extra fields, a wrong declared field type, duplicate fieldIndex and out-of-range fieldIndex all return None. Complete and reordered-by-fieldIndex inputs are positive controls. Mid/Types.pw checks operand -> element.targetTerm conversion and result/destination equality, but not declaration-field correspondence. LLVM preflight compares fieldCount with elements.len, not with the finalized variant. The enum emitter currently appends element values in vector order, discarding fieldIndex.

## Guarantee and covered boundary

- Validate variant identity, required field count, fieldIndex range/uniqueness/complete coverage, selected field type and boxing against immutable finalized metadata at the appropriate admitted stage.
- Preserve semantic evaluation order. A reordered element vector is not inherently invalid: arrange already evaluated values at their destination fieldIndex in LLVM payload layout. Do not require declaration-order source evaluation as a workaround.
- Carry the validated aggregate mapping to final LLVM construction; avoid duplicate independently reconstructed semantic decisions. Raw malformed input must fail closed before incomplete or ill-typed payload construction.
- Resolve helper active-field initialization preconditions explicitly. Do not rely on whole-enum zero initialization to repair malformed active fields.

## Scope and exclusions

Finite enum aggregate construction only, from canonical verification/applicability through payload emission, including existing raw callers and valid conversion/boxing paths. No new language feature, struct/array-wide rewrite, arbitrary source acceptance change or optional padding optimization is required. This is phase-four Mid/backend conformance, not a prerequisite added to com-yeua or phase three. The inactive-padding prototype remains unadopted. If that optional optimization is revived, it must consume a proven complete active payload.

## Scenarios and completion

Start with the saved raw RED and normal complete/reordered controls. Add duplicate-index-only same-typed fields, wrong variant/enum identity, wrong field type and boxing, empty variants, mixed-width and ARC-owning fields, generic finalized substitution, and typed enum repack/try controls where the helper is reached. Verify rejection at the intended actual admission, not a later LLVM assertion; demonstrate final field values and evaluation order for the reordered positive case. Keep source and raw origins distinct.

Repair the owning validation and field-mapping boundary, remove the competing positional assumption, retain exact accepted/failed stage identity, then run relevant normal/native/ORC and ownership sanitizer gates and obtain independent completion review. Do not close on a new check without final lowering evidence.

## Evidence and limits

Meta evidence/rejection-domains/enum-aggregate-admission contains the exact probe and recorded outcome. Existing e2360a6d compiler built it; LLVM20 clang -O0 linked its native executable. The probe asserts same enum identity, ready final layout, [0,2] field range, I64/Bool field types and no boxing; structural well-formedness is asserted for every case. All eight modes returned None. Abort termination means no constructed-value read/drop was executed. Source reachability, whole normal-preparation bypass, actual misexecution and zero->undef-specific regression are not established. Mode5 is a valid mapping control, not a seventh erroneous-acceptance claim.

Independent reviewer enum_aggregate_admission_review confirmed the observed boundary, setup checks and phase-four classification. Related API authority tasks com-m4kt/com-08i0 do not already repair this semantic completeness defect.


