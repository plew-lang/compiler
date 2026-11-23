---
id: met-1yd7
status: in_progress
deps: []
links: []
created: 2026-11-23T06:12:45Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain associated receiver-pattern ambiguity refusal ownership

The final31241607 candidate correctly rejects closure_associated_overload_later_match in check/AOT/ORC, but all three return Unclassified instead of Source. This is the existing com-yeua shared member ambiguity family, separate from met-bu94 first-normal inference and met-qo60 selected member roles. At Resolve/Module.pw findAssocWithOrigin the actual negative selection directly returns diagnosticAt and drops MethodLookupOrigin. Preserve the main diagnostic, exit status, ranking and ambiguity decision. Extend the existing retained member refusal family and exact owning observer; never infer Source from matching text, cursor or an active builder alone. Raw/public lookup has no authored authority.

## Acceptance Criteria

Retain fixed candidate domain RED for three public modes. Cover authored owned associated refusal and raw empty origin; wrong session/owner/kind/receiver/selector/arguments, synthetic/unregistered expression, retry/drain, cause lifetime and no successful parent/cache/template publication. Reuse existing member ambiguity controls plus successful associated calls. Remove the raw direct diagnostic competing producer, use one existing retained family/observer, independent source/evidence review, fresh candidate exact three modes plus affected gates. No new language semantics or whole-stage completion claim.


## Independent scope and RED

Neutral associated_ambiguity_intake_review confirms Module.pw1244 drops MethodLookupOrigin at the actual failed selection; existing Check/Bounds memberCallAmbiguityDiagnostic and SourceFacts observer already own the retained contract. No second classifier. This is com-yeua shared member ambiguity closure, explicitly outside met-qo60 Source admission. Source31241607 candidate5d9ee2bb check/AOT/ORC all reject with the intended ambiguity message and exit1 but Unclassified. Receipt: meta tmp/phase3-forward-frontier/argument-cli-complete/results.json, canonical phase3-contextual-operand-regression.json associated_ambiguity_followthrough. Guard-test expansion is pending; no product adoption.

## Implementation checkpoint

An explicit AssociatedReceiverPatterns kind preserves the original message and compares only with itself. The failed associated selection now passes exact MethodLookupOrigin/recvRef/selector/arguments to the existing memberCallAmbiguityDiagnostic; Raw empty-origin remains raw. StaticMemberAmbiguityFailureDomains adds a third real associated input while retaining both original inputs, and shares session/kind/owner/receiver/selector/argument, synthetic/unregistered, raw/retry/drain and owned whole/eager assertions. Neutral source review found no confirmed must-fix; receiver0 is intentionally retained as the actual negative query value, not replaced with a candidate type. Execution gates remain pending. Frozen old source/test kernel under meta tmp/phase3-forward-frontier/associated-red-kernel is for RED; current product is WIP, not adopted.
