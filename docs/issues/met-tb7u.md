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

## Finite reviewed implementation

Numeric_refusal_intake_review accepted the concrete plan: one optional-offset query, typed free negative outcome consumed by exactly Raw findFunc and owned resolvedFreeFunctionCall, existing member origin adapter at unchanged call positions, exact kind/location in private retained maps. Keep general/same-source/cross-source and bare-associated priorities. Raw single-source extension and synthetic anonymous factory wrappers remain Raw. Dependency query Err passes unchanged via try.

Expanded free native confirms original4lines then custom flattened-cause RED on old source; WIP free source has10line GREEN. New numeric method/view3mode each reproduce Unclassified domain RED; bare associated numeric control already Source and preserves associated message. Expanded member native preserves original3inputs plus method/view numeric and actual operand-line7 (free line6), including kind/location/synthetic/owner/operation guards. Never-passed test setup corrections and private API-closure setup failure are recorded separately, not counted as target RED. Exact final native/current candidate/formal gates remain pending.

Final current-source native gates pass10free/20member-view golden lines with empty stderr; sessions21688/53062/34227 are reaped. Numeric source positions are asserted (free line6, member/view line7), with changed location tag/path/line and kind rejected. Actual malformed-cast dependency Report passes through the numeric query/raw wrapper unchanged in message/location/Unclassified domain. It is not claimed as an injected FailureDomain.Internal dependency; equal-text Internal observer control and direct try source inspection are distinct evidence. Fresh candidate/source saving and affected modes remain pending.
