---
id: met-o5z0
status: in_progress
deps: [met-ldvd]
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
