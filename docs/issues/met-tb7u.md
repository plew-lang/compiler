---
id: met-tb7u
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
# Carry numeric overload ambiguity through owned call selection

Five whole-suite controls: numeric_block_overload_ambiguous, numeric_if_diverging_branch_overload_ambiguous, numeric_if_overload_ambiguous, numeric_match_overload_ambiguous and generic_numeric_candidate_substitutions_ambiguous. The latter requires exact producer confirmation on the final candidate, not inference from its name. checkOverloadAmbiguity currently returns a raw report before selectFreeFunction can deliver its typed outcome. Preserve the precise original numeric/general kind, message and location through a finite selected outcome and existing retained ambiguity boundary; extend shared free/member/associated paths without repeating ranking. Raw APIs remain non-authoritative. Scope confirmed by independent numeric_refusal_intake_review; existing com-8uik/met-bu94/met-qo60 finite closures remain intact. Plan only: final a76 reproduction pending while formal0633ed executes.

## Acceptance Criteria

Exact final candidate RED first, then direct/block/if/match, both declaration orders, diverging-first and generic ambiguity controls; free/member/associated and existing general ambiguity. Raw active-owner versus owned, synthetic/copied-span and session/owner/kind/selector/arguments/location mutation, retry/drain/cache and no successful result/template/closure publication. Preserve normal frontier/typed controls. Fresh gates, independent acceptance and parent whole remain required.

## Exact final-candidate RED

A76f2f9c fixed associated-candidate carrier reproduces all7fixtures/check-AOT-ORC21modes: status1/stdout empty/intended primary diagnostic/Unclassified, with unchanged source/expectation/carrier fingerprints. Full receipt is canonical meta phase3-contextual-operand-regression.json numeric_refusal_intake.red and scratch tmp/phase3-forward-frontier/numeric-refusal-red/results.json. Generic candidate substitutions ambiguity actually reports the unsuffixed numeric overload message, confirming assignment to met-tb7u. No product implementation or GREEN for these tasks yet.
