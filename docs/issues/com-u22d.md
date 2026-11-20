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


## Reversed-order execution RED

Fixed b6461fdd fresh carrier confirms both declaration orders: direct choose(5) rejects, while block-give and if-give wrappers are accepted and execute32 or64 according to the first declaration. Check/ORC twelve-mode evidence: meta tmp/phase3-provisional-call-context/numeric-controls.json. This proves actual chosen execution, not merely acceptance. The context-demand query currently does not cover numeric wrappers, while selectFreeFunction returns firstLabel as Selected and lookupFreeCall caches that as CachedCallee.Selected. Investigate the shared producer and all final readers before changing it; planning review in progress.

## Numeric value-shape increment

Read-only File/Std native probe confirms direct5 has rank2/2, whereas block/if wrappers have rank1/1 with no operand term and no preselection cache; the fallback subsequently publishes Selected and executes32/64 by order. No prior width commitment was established. Typed suffix/local and mixed typed-first if controls choose64 in both orders; match wrappers reproduce the order defect. The independent plan review accepts observing prepared unfinished numeric values rather than deferring entire wrappers.

New reject fixtures numeric_block/if/match_overload_ambiguous are all wrongly accepted on fixed b646 (RED). The normal numeric_wrapper_overload_context fixture is rejected at array-first/I64 block discrimination (RED). Current increment shares one numeric value-shape observer between common applicability and integer ambiguity, reading retained terms/block results/completion and delegating leaf rules to the existing numeric syntax helper. It does not resolve locals, infer branch types, change source recording or introduce a Float default. The NumericCandidateContexts manual checks repeated rank probes/nonpublication, failed retry/cache and normal typed/mixed preparation. Initial source-native passed; refreshed native, final fresh compiler/modes, method/associated contrasts and performance are pending. This does not complete DiagnosticCandidate/failed-frontier/authority separation; task remains in_progress.
