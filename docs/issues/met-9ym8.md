---
id: met-9ym8
status: open
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

Existing generic_numeric_rigid_caller rejects but remains Unclassified. Check/Generic checkGenericTypeMatch directly reports that an unsuffixed numeric value cannot inhabit opaque caller T or provided Self. Reuse the existing raw versus private expected-check origin distinction from com-8uik, while keeping a distinct cause for this actual check. Retain exact expected ParamId/type, operand and owner/session at failure. No new inference, no Array-cause mixing, no retyping committed operands. Scope confirmed by independent numeric_refusal_intake_review; existing com-8uik/met-bu94/met-qo60 finite closures remain intact. Plan only: final a76 reproduction pending while formal0633ed executes.

## Acceptance Criteria

Exact final candidate RED; caller rigid T, provided Self, Int and Float, real nested Array/block transit where reachable, and valid concrete expectations. Raw active-owner checks versus source-owned lazy/whole/eager, foreign session/owner, changed expected/operand/kind/location, synthetic with copied span, equal-text Internal, retry/drain/cache. No success publication. Fresh candidate targeted controls and independent acceptance; parent whole gate remains separate.

## Exact final-candidate RED

A76f2f9c fixed associated-candidate carrier reproduces all7fixtures/check-AOT-ORC21modes: status1/stdout empty/intended primary diagnostic/Unclassified, with unchanged source/expectation/carrier fingerprints. Full receipt is canonical meta phase3-contextual-operand-regression.json numeric_refusal_intake.red and scratch tmp/phase3-forward-frontier/numeric-refusal-red/results.json. Generic candidate substitutions ambiguity actually reports the unsuffixed numeric overload message, confirming assignment to met-tb7u. No product implementation or GREEN for these tasks yet.
