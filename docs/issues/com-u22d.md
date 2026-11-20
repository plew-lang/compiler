---
id: com-u22d
status: in_progress
deps: []
links: []
created: 2026-11-20T06:58:04Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification, diagnostics]
---
# Preserve provisional call context without publishing a selected callable

Contract: spec/02 forward local expectations and ambiguous calls reject; body-checking.md contextual construction versus committed compatibility; name-lookup.md a contextual hint is not a selected callable. Do not grant source authority merely from a selected-looking cache row.

Confirmed fixed33d1011d File controls (meta tmp/phase3-empty-array-overloads/numeric/old.json): choose(I32)/choose(I64) rejects choose(5), but accepts choose({ give 5 }) and choose(if true { give 5 } else { give 6 }). Both overload declarations are valid; a value wrapper cannot silently choose an integer width by declaration order. Current com-5n0l fixes empty-array demand/shape, not this numeric-wrapper contract. Source case text, hashes, actual check/AOT/ORC statuses are retained. Reversed numeric declaration order and actual selected result must also be measured before selecting the finite repair.

Also resolve the related authority boundary: selectFreeFunction returns firstLabel as Selected when no rank2 candidate exists. This is a diagnostic-context fallback, not proof of applicable callable selection. Source expected-context admission must distinguish those outcomes through lookup/cache/Record/retention/final readers without using the current cursor or redoing overload resolution. Preserve diagnostic precedence and useful diagnostics for bad arguments; do not simply delete the fallback, declare an unknown argument matched, or publish a successful call from it. An owned failed-frontier/diagnostic context may carry a source refusal only from its actual retained negative selection evidence, not an arbitrary first candidate type.

Investigate the actual numeric-wrapper demand and selection path, then implement the finite common applicability/context/selection distinction across relevant free/method/associated callers, canonical cache consumers and final call publication. No new numeric default, backward inference or Float semantics. Separate unresolved Float/default rules remain com-s922/com-pxja; declared nested Array identity remains com-zy6r. General API grant narrowing remains existing owners. This is existing-feature phase3 repair; not an optional new feature.

## Acceptance Criteria

TDD direct/block/if/match integer forms and both declaration orders, unique versus genuinely ambiguous destinations, typed widths/Bool/function/Array noninterference, single-target contextual literal success, unknown/incomplete environments, Raw/cache/retry/provisional-versus-selected invariants and final actual call execution. Preserve source effect order and one-time evaluation. No diagnostic fallback can pass final call publication as applicable. Retain useful owned source failure without text classification, fake successful parent facts or replayed resolution. Cover all actual consumers, remove superseded competing authority, applicable gates and independent review. Investigation must establish a finite role/API plan before repair; not an open-ended numeric inference redesign.

