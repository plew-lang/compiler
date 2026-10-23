---
id: com-4kti
status: open
deps: [com-nucu]
links: [com-nucu]
created: 2026-10-23T13:23:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, generics, verification]
---
# Enumerate projected trait input instances and admit the selected full proof

Planned mandatory repair outcome of C2/com-nucu. projectedMemberResolution currently consumes the first Existence/open-input proof as its selected requirement. Replace that handoff with finite distinct positional-instance enumeration, normal callable applicability, and SourceAdmission of the chosen complete trait instance. Preserve source precedence, exact duplicate premise deduplication, ambiguity and associated-output checks.

## Acceptance Criteria

Bool and I64 arguments choose their unique matching instances regardless of bound order; indistinguishable no-operand instances and independent source paths reject; exact duplicate premises do not create ambiguity; associated-output mismatch still rejects. Save the admitted full proof through CallTemplate, both worklists and actual native/Mid calls. No name/order fallback; fresh scoped controls and independent completion review required.


## Boundary and Entry

Planned C2 repair disposition; parent criteria 3, 4, 8. Keep this to the existing
projected receiver member path. Entry: Check/Bounds.projectedMemberResolution,
Mono/Resolve.queryTraitPatternProof/projectedTraitPatternProof/
traitPatternProofFromFacts and the selected call constraint publication boundary.
Return distinct complete positional trait-instance candidates before normal
applicability; do not use discovery order or associated outputs to choose an
input instance. Reuse the common source-proof/path workers rather than creating
a second conformance solver. Query the selected full instance with SourceAdmission
before publishing its requirement/proof. Preserve exact authored premise priority,
explicit source views, ambiguity and existing conditional/projection children.

## Closure Evidence

Turn the watched C2 counterexamples into positive/reject regression controls;
add a concrete conformer with distinct results to exercise the selected call
through native/Mid. The two-input Bool call must work in either declaration
order; no-input ambiguity and independent source-path ambiguity must reject.
Recheck existing associated_projection_constraint_identity and
source_selected_witness_owner_evidence. Record actual removed first-hit paths,
fresh source/candidate/input hashes, and independent completion review here.
Final normal/gen/deps/sanitizer/fixed-point/performance gates remain G2a/G2b.
