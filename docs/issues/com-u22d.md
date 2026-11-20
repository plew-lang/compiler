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

## Numeric increment verification and next RED

Product1bdccf70 fresh build20261120T084013-build-5df910 passed immutable. Focused75modes and normal native execution passed; associated rejections stop at an existing receiver-pattern ambiguity and are NOT proof of the new observer. Array/closure54old/new controls preserve results, with8exact LLVM and1internal-name bijection. Float direct/block/if/match status/output remain unchanged. Return-branch tests prove old wrong acceptance becomes rejection, old wrong rejection becomes native/ORC64,0, while the existing all-divergent argument stays rejected (18old/new modes). Five isolated same-source pairs give6.912715/6.882600seconds; all10LLVM byte-identical, no demonstrated regression or claim of definitive speedup. Independent review accepts this numeric increment, not the whole task.

Next boundary RED: ProvisionalCallAuthority loads the real File/Std typed-mismatch fixture, proves one selector-only rank1 candidate, then asserts failed source preparation does not leave CachedCallee.Selected. Current1bd source-native test deliberately fails its assertion with `diagnostic-only candidate published selected callee authority` (native -6). This is the test detecting the compiler's authority violation, not a crash in compilation of the source program. The original source program rejects with its existing Source type-mismatch diagnostic. No lookup role or cache repair has been implemented yet. Preserve detailed diagnostics, literal/mode checks, negative frontier identity and the genuine Selected path; do not call publication helpers merely to validate a diagnostic candidate.

## Free-call role implementation (not final adoption)

The source path now carries DiagnosticCandidate separately from Selected through lookup and Record; only rank2 enters CachedCallee.Selected. ExprType returns unknown immediately for DiagnosticCandidate, and resolvedCallee does not export it as a final target. The Raw findFunc compatibility observation remains explicitly documented and has no compiler-source consumer. Record keeps the role in its private context helper, shares nonpublication literal/mode/value validation with the existing selected-call checker, and never publishes a parent template/result/access plan for a diagnostic-only outcome. Only NoCandidate performs visibility-hint lookup. The private failed-frontier helper requires a real failed outcome. Child failure provenance is preserved rather than promoted merely from a candidate hint. Expected-context Source admission itself remains the b0e6/8uik boundary.

Role separation exposed a real applicability deficiency: same[T](first:5,second:6I64) was accepted via rank1 fallback. The fixed matcher collects independent already-typed argument substitutions in its existing pass, retaining only unmet numeric signature constraints locally and checking them after that pass. Literals do not choose T or a default width. Known arguments are not queried again. Vector length and resolution are both required before diagnostic generic validation. Source-native tests verify both numeric orders, Array/closure/default controls, real failed cache ownership and successful generic Selected entries. A distinct-substitution generic overload fixture adds an old false acceptance and an old order-sensitive normal wrapper control; tests for fixed Bool, contradictory widths, opaque caller T and no width constrain the delayed checks. Fresh compiler/CLI/gen/performance gates and final independent review remain required. Method/associated fallback role separation is still open; this is not full com-u22d completion.

The generic numeric constraint remains possible only while a callee-owned variable/projection really depends on an unfilled inference slot, so an available result annotation may complete identity(value:5). A rigid caller parameter and fixed nonnumeric head are not holes. The ordinary Source incomplete-substitution checks still reject missing context and later-use repair. Diagnostic known-slot validation precedes unrelated generic-result inference, preserving the old fixed-Bool and opaque-caller literal errors; the full parameter array is no longer copied. Additional independent source review found no confirmed must-fix. Latest source-native role/cache, generic/substitution, result-context and rejection harnesses pass; fresh adoption still pending.

An exploratory positive oracle using two separate closures (one omitted result annotation, one explicit) already failed the fixed baseline with inconsistent generic types. It was not used as a valid positive: the retained closure control passes the same already-typed closure binding. The exploratory input/result is kept in scratch for future legality/inference investigation and is not claimed repaired or used to close this boundary.
