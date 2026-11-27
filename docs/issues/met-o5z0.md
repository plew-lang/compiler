---
id: met-o5z0
status: in_progress
deps: [met-ldvd, met-oxch]
links: []
created: 2026-11-27T13:29:11Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Carry missing projection-member refusals through type-use admission

## Contract and finite scope

Carry the existing missing associated-member decision through shared type-use
admission, raw failure retention and owned eager/session consumers. A source
projection T#Parser.Missing with an admitted Parser declaration that has no
Missing member is a source rejection. Do not infer ownership from text, TypeRef
identity, a cursor or the caller stage. Reuse internally captured type-use
occurrence/root/frontier/path evidence; preserve real original locations.

Current baseline149aacd25456 whole20261127T121111-test-c32d9f has Unclassified
reject/{assoc_type_projection_unknown_assoc,unused_assoc_type_projection_unknown_assoc}.
The same wording also comes from Codegen/Mono/Resolve missing conformance/binding
for extern_signature_{unrelated_conformance,wrong_trait_instance}; those are a
separate decision and excluded, not evidence that one message has one owner.

## Decision and path

Inspect checkProjectionMember and canonical projection/declaration readers;
retain one semantic refusal at that decision before checkedTypeUses publication.
Keep the raw compatibility entry non-Source. Common type-use admission passes
its internally established occurrence origin; owned services interpret only the
matching stored refusal. Do not replay membership to classify or grant Source
for downstream missing binding. Remove duplicate acceptance/provenance authority
introduced by the repair. API inputs contain only actual query dependencies.

## Scenarios and completion

Freeze old check/AOT/ORC controls before product changes: local/imported,
used/unused declaration signatures, a demanded versus unrequested body type,
valid member/generic projection, lexical owner boundaries and original positions.
Native controls cover raw/coherent versus owned inputs, forged/foreign event and
occurrence/payload, failure retry/cache/drain, eager/whole/session conversion,
failed-builder provenance and no success-cache insertion. Preserve downstream
missing-binding diagnostic/domain as excluded controls. Setup failures are not RED.

TDD, independent plan and final review are mandatory. Focused fresh/regressions
and applicable gen first; owning parent com-yeua performs aggregate formal/whole
comparison at its bounded integration gate. Baseline is3314/248fail, not green.
No new language rule, main/seed/bin promotion, blanket Raw Comp validation or
all associated-type/conformance failure migration is included.



## Neutral plan review

Accepted finite slice. Add explicit-trait-offset and assocTraitStart fallback
controls with unrelated same-named module traits; unresolved trait or missing
assoc IDs must not gain Source. Preserve inherited associated names and valid
parameterized trait projections by consuming the existing flattened assocTypes
view, not a second inheritance search. Namespace selection and actual member
judgment precede retained owned interpretation. No source repair is claimed yet.

## WIP executed findings

Fixed149aac48controls yield14legal/deferred passes and34target exit1
Unclassified refusals, all exact missing-member message, no setup failures.
Nativev2 passes saved query/evidence boundaries. Review caught the old wrapper
was public; type:TypeRef Raw compatibility is preserved public alongside a new
canonical-ref adapter, with shared readonly query and private origin admission.

The same-name alias NamesMain native counterexample reports the alias use on
line1 rather than the authored projection on line4. Source interpretation now
uses the internally retained occurrence site; Raw legacy location behavior is
unchanged. This is a genuine original-location RED, not a source rule change.
New controls initially used U64 for I64 diagnostic lines, omitted required
TypeRef fields, and omitted the existing spec suffix: setup assertions corrected.
A blank golden in existing trait_args uses the normal harness trailing-newline
policy; the new diagnostic control adopts that same policy, not an existing-test
change. Native original v1/Core malformed whole-corpus checks are not claimed.

WIP source/native review accepts the public Raw API restoration and the
separation of canonical query snapshot from real occurrence diagnostic site.
Native original-location and public cross-module session controls now pass.
Intermediate fresh48/48 plus inherited/parameterized/distinct-producer15/15
pass; source query/location changes after that first build require v2 fresh
verification, which remains pending. No finite closure is claimed.

## Pending language boundary

met-oxch requires the user decision for T#Child.Output where Child inherits
Parent.Output. The original plan incorrectly described TraitDef.assocTypes as
flattened; it is declaration-local. Existing lexical lookup retains Parent as
the actual owner, and T#Parent.Output under a Child bound is valid. A new
Child-spelling control has never passed and is not counted as a specified RED.
The repair would otherwise classify that existing rejection as Source, so finite
closure is held rather than assuming either interpretation. Final v2 fresh48/48
and distinct-producer/valid15/15 passed; gen is being collected. WIP is not
adopted. Carrier149aac and the248fail whole baseline remain authoritative.

Final v2 build20261127T134254-build-07353d and fresh48/48, controls15/15,
gen20261127T135148-gen-5b6548 pass. Nativev8 exposed the new control
incorrectly assuming an inherited declaration namespace is flattened. Correct
normal control is T#Parent.Output under T:Child; old149aac accepts it.
T#Child.Output remains the pending met-oxch source decision, not a new RED or
an approved rejection. Do not certify this WIP until that dependency is decided.
