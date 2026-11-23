---
id: met-9ym8
status: in_progress
deps: []
links: []
created: 2026-11-23T06:42:31Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain opaque generic numeric expectation refusal ownership

Existing generic_numeric_rigid_caller rejects but remains Unclassified. Check/Generic checkGenericTypeMatch directly reports that an unsuffixed numeric value cannot inhabit opaque caller T or provided Self. Reuse the existing raw versus private expected-check origin distinction from com-8uik, while keeping a distinct cause for this actual check. Retain exact expected ParamId/type, operand and owner/session at failure. No new inference, no Array-cause mixing, no retyping committed operands. Scope confirmed by independent numeric_refusal_intake_review; existing com-8uik/met-bu94/met-qo60 finite closures remain intact. This task remains open; the sibling ambiguity task met-tb7u is closed. Reproduce this task on the next fixed candidate before implementation.

## Acceptance Criteria

Exact final candidate RED; caller rigid T, provided Self, Int and Float, real nested Array/block transit where reachable, and valid concrete expectations. Raw active-owner checks versus source-owned lazy/whole/eager, foreign session/owner, changed expected/operand/kind/location, synthetic with copied span, equal-text Internal, retry/drain/cache. No success publication. Fresh candidate targeted controls and independent acceptance; parent whole gate remains separate.

## Exact final-candidate RED

A76f2f9c fixed associated-candidate carrier reproduces all7fixtures/check-AOT-ORC21modes: status1/stdout empty/intended primary diagnostic/Unclassified, with unchanged source/expectation/carrier fingerprints. Full receipt is canonical meta phase3-contextual-operand-regression.json numeric_refusal_intake.red and scratch tmp/phase3-forward-frontier/numeric-refusal-red/results.json. Generic candidate substitutions ambiguity actually reports the unsuffixed numeric overload message, confirming assignment to met-tb7u. No product implementation or GREEN for these tasks yet.

## Implementation boundary and scenarios

The fixed-point carrier from `20261123T101114-self-host-b3272b` (SHA256
`53ebd3f00c8c156b7199b1881a83739643ecc81f54e1c4b003bd6c6eb17458e4`)
reproduces caller argument, annotated local Int/Float and provided Self Int/Float
refusals. `opaque-intake/results.json` records 24 mode observations: 13 actual
opaque Unclassified refusals, two unrequested provided-body ORC successes,
six earlier block/Array inference refusals and three concrete successes. The
latter six are not RED for this producer and their diagnostic order must remain.

Implement a narrow private checking request through Preparation, bounds
condition/block/statement/expression traversal, closure, Make fields and Array
recursion, plus the two Record adapters. Public wrappers and Mono stay Raw.
Preserve dependency Err unchanged. Only the original Int/Float refusal branches
may construct the dedicated negative cause; retain ParamId versus provided Self
identity distinctly, expected term, literal metadata, location and recorded owner.
Observe expression owner separately from its lexical request root. No retyping,
message matching, successful parent publication or Array-specific authority.

Independent plan review found that expressionOwners, sourceExpressionLimit and
exprOriginSerial alone do not prove authorship: all can include synthetic nodes.
Use minimal Lower-owned numeric-origin receipts from both Lower entry points,
including folded negative integers. Ordinary pushExpr and Record cannot publish
this origin. This is syntax provenance, not a second type-success database.
Require request + retained owner + exact Lower provenance for owned attribution.
Test recorded synthetic copied-span nodes as well as unrecorded clones, different
IDs, changed serial/kind/location/expected identity, foreign session/root, Raw
with an active owner, same-text Internal, retry/drain and failure retention.
Keep the existing Float rejection condition, including suffixed Float, unchanged.

`tests/compiler/frontend/OpaqueNumericFailureDomains.pw` and its exact ten-line
`.out` start the whole/eager consumer regression. Extend with Raw/lazy/private
controls rather than treating this initial consumer test as complete coverage.
Final candidate controls, retained-input checks, independent acceptance and the
parent whole-suite gate remain required. Review is a plan review, not closure.

The initial consumer RED is confirmed at native execution: compile/runtime and
corrected link exit0, then exit -6 with exactly `panic: opaque numeric rejection
lost its source owner`. All captured inputs remained unchanged. Initial test
setup errors, a60s ORC timeout and the first link's missing C filename suffix
are excluded from RED. Canonical `numeric_refusal_intake.opaque_checkpoint`
retains the input hashes, baseline24modes and exact outcome. This proves the
first consumer assertion; the remaining scenarios are not claimed executed.
