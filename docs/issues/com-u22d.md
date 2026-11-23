---
id: com-u22d
status: in_progress
deps: [met-bu94, met-qo60]
links: []
created: 2026-11-20T06:58:04Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification, diagnostics]
---
# Preserve provisional call context without publishing a selected callable

## Reopened current boundary

Fresh whole test071429-test-d6c2d4 exposed formerly passing array_nested, call_arg_literal, default_arg_array, associated_literal_context, closure_contextual_generic, cow_gw_inout_elem and cow_gw_nested_index rejected by exact carrier eadf4cb9. Same frozen input bisection: pre-u22d accepts array_nested/call_arg_literal/closure_contextual_generic; u22d fixedpoint db40e37c and subsequent carriers reject all3. This is a regression within the existing single-target contextual literal/Array/function noninterference guarantee, not a new language feature or permission to weaken tests. The whole run later ended1 on ENOSPC and cannot certify a completed suite; retain that environmental failure separately from already reproduced compiler refusals.

Restore candidate-local matching of genuinely contextual prepared aggregate/function recipes while fixed typed operands stay fixed. Preserve forward generic constraints, numeric overload ambiguity, source effect order and Selected/DiagnosticCandidate/cache nonpublication. Before editing, map the actual failed rank and saved operand facts, derive a finite repair plan and independently review it. Do not special-case fixture names, reopen unrelated AST checking or treat every operand as unknown.

Required RED/GREEN: free/member/associated calls; structural records and nested arrays with unsuffixed versus typed elements; block/if/match wrappers; contextual closures and generic constraints; conflicting typed operands and both overload orders. Reuse existing successful fixtures and compare their actual outputs. Parent whole remains open. Meta scratch `phase3-normal-array-context-regression/reproduction.json` and `carrier-bisection.json` retain exact carrier/input hashes and diagnostics; canonical current evidence is added there after recovery. Previous closure below is superseded for this uncovered implementation regression.

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

## Fresh role-split adoption blocker

Revision8702289f fresh build and finite numeric/generic/Array/closure/Float/representative positives, gen and two manual natives pass (details in the linked evidence). Existing FreeCallVisibilityFailureDomains compilation nevertheless fails at Mid/Build.pw:2619. Fixed old1bd accepts `accept(value:<Optional.None />)` for Optional[I64] and `accept(value:make())` for make[T] returning Optional[T]; fixed new870 rejects both as NoMatch. These are legitimate contextual argument regressions, not bad test oracles. Do not adopt or measure the broken candidate as final. The partial constructor has a recorded nominal head with zero arguments despite one declared binder; expressionNeedsTypeContext is false. The nested generic result establishes that a constructor-only exception is insufficient.

Next finite boundary: inventory common argument applicability and selected-context refinement, then preserve prepared context-dependent argument shape and independent constraints in candidate-local matching. Candidate probes must not publish selected cache, mutate expression/result facts, treat a foreign callee hole as a rigid caller variable, reopen a closed block, or promote DiagnosticCandidate. Complete determined arguments retain their types. Cover None/Some/struct/nested field, wrapped values, same-head ambiguity, explicit/inferred arguments and nested generic result completion before final adoption. Independent plan review requested; no product repair yet.

## Prepared argument repair plan and RED

Independent neutral plan review accepts one common prepared-argument matcher, candidate-local constraints, and a nonpublication projection of the existing selected-result completion. Constructor readiness and late result refinement are distinct from expression entry deferral; closed block scopes are never re-recorded. Selected inner calls keep their declaration and complete only unfilled binders from an outer expectation. Completed explicit/inferred operands stay rigid. No new source-domain admission is part of this increment.

The new partial_call_argument_context fixture first passed old1bd ORC with six exact outputs (None, Some numeric, generic struct numeric, closed local field, if, nested generic return), and failed new870 with NoMatch at the first call. Further controls include both outer-generic argument orders and an explicit extension method result. The separate partial_constructor_argument_ambiguous fixture rejects two legitimate Optional contexts rather than choosing declaration order. The scratch eleven-case matrix retains the old erroneous acceptance of None ambiguity and old outer-generic first-argument inference failure; neither is claimed as a passing oracle.

WIP extracts prepareCallTemplateResult from publication and returns a local ContextualCallResult proposal; only completeCallTemplateResult publishes expression terms, type-argument pool entries and provided-result selectors. Common matching reads prepared constructor declaration/field terms and saved normal block yields, or the exact selected inner template; deferred contextual operands are checked after independent substitutions. The selected-context tail recognizes nonzero partial terms. Source recording must not infer an outer binder from an inner unfilled binder. A malformed substitution range/term is not a legitimate inference hole; ContextualCallResultCompletion covers missing/oversized/out-of-pool/out-of-arena retained arguments without silently repairing them. The existing raw versus Source distinction is not replaced by a blanket source-only observation policy.

First source review found ExtMethod omission and malformed-state conflation; both are accepted for correction. Preserve provided receiver-zero behavior and recheck proposals depending on outer unfilled slots. Review agrees with independent saved-range validation rather than equating source:false with corruption. Fresh snapshots and raw fault/native results remain required; method/associated diagnostic fallback authority is still open. Current product is WIP, not adopted.

## Saved readiness and nested construction follow-through

The pre-review fresh snapshot passed build20261120T103734-build-0269dd and restored None/Some/struct/block/if/selected generic result contexts while rejecting None ambiguity. Revisionea0bce38 passed fresh build20261120T104521-build-878b49, but the expanded positive still exposed extension-result readiness and an old inference entry. File/Std diagnostic native proves freeCallParameterEnvironment's remaining inferFnArgs path produced a foreign T@46 environment; using inferRecordedFreeCallArgs yields I64 and successful preparation. The actual replacement is included in the next increment, not retroactively attributed to ea0.

An extension method's semantic fallback can be a closed-looking Optional head while its saved selected template retains zero generic slots. Readiness therefore comes from the selected declaration and validated saved substitution, not typeIsClosed or Source permission. This also removes the repeated signature/environment construction previously used by the readiness observer. Preserve raw legitimate zero slots; malformed lengths/ranges/terms must not complete. Old870 executes ContextualCallResultCompletion and fails its assertion with `malformed substitution was repaired from expectation` (-6), establishing the internal fault RED.

Nested construction requires preserving incomplete children under a nonempty parent argument list (Box[Optional]). Canonical matching protects known sibling and phantom arguments; authored type slots remain fixed. Ordinary source construction producers supply either zero omitted nominal arguments or the full declared arity with possibly unfinished children: partial nonzero arity is not a supported valid instance. Known-field source inference uses the same prepared-argument matcher rather than copying a foreign callee hole into an outer binder. New normal nested/phantom/match and reject known-field/explicit-argument controls cover this boundary. Independent source reviews accept the finite direction and saved-readiness correction, with final fresh/native/nonpublication/performance certification still required.

## Raw versus prepared construction observer

Freshc68 passes new51mode, numeric75mode, Array/closure54old-new controls (7exact LLVM,2verified internal-name-only), representative96old-new controls, Float16modes and the first6internal natives. NumericCandidateContexts then fails only its final generic Pair[I32,I64] raw candidate assertion. Diagnostic native identifies arguments0T@48 and1I32 as successful, with argument2Pair[T@48,I64] losing rank2. The observer treated absent, not-yet-prepared field facts as unfinished child recipes and supplied parent term0 to construction matching. This is a product regression, not an erroneous existing test.

The finite repair requires a retained parent term before treating field information as a prepared contextual construction. It does not reject the raw argument; fully written raw arguments continue through ordinary structural matching. Existing numeric assertions are unchanged. Instrumented source-native now passes all four ambiguity frontiers and the typed normal fixture; guard preparation and final fresh verification remain pending. The previous c68 fresh gates are not attributed to this additional guard.

## Bounded child work

Independent neutral planning review accepts a two-child partition without narrowing this parent. [met-bu94](met-bu94.md) owns common applicability/prepared values and the free role increment through final gates; [met-qo60](met-qo60.md) owns the remaining method/associated collectors, composed resolvers, caches and publication. The second depends on the first; this parent depends on both and remains in_progress. Existing com-8uik dependence on this parent is unchanged. These are the original required repairs, not optional follow-ups or justification to close the parent.


## Closure — provisional argument context and callable authority

Resolved on final source ba891bdf with met-bu94 and met-qo60 closed. Independent parent review derives the required numeric/context/role/cache/publication/priority/Raw/rigid/normal scenarios from this contract and finds no missing finite parent obligation or confirmed product must-fix. A's prepared argument/free selection boundary and B's member/associated boundary share applicability without promoting diagnostic candidates. The exact fixedpoint carrier's target gates and generator gates cover the final combined source. Source admission of expected-type failures remains com-b0e6/com-8uik, not a new grant inferred from an active cursor.

Formal run20261120T153146-self-host-32b720: generation3 fixedpoint, generation2/3 LLVM/runtime/successor equality, five samples median6.999988seconds (<7, no margin claim). Same-source alternating5pairs: oldA7.085223/newC6.950058, all reference LLVM hashes match. Canonical A/B evidence remains meta phase3-provisional-call-context.json and phase3-member-call-roles.json under evidence/rejection-domains/diagnostic-domain-implementation/.

Limits: the whole normal suite was not rerun for this combined candidate, so current-corpus noninterference beyond executed targets is unconfirmed. Last whole324 failures remains historical, not a successful current corpus. Per工程3 progress policy, each finite task closes by applicable target validation, while final fixed-candidate whole gates remain G2a/G2b and com-yeua / 工程3 owners. This is neither their closure nor main/seed/bin promotion. Next is com-b0e6's complete expected-context role plan, then com-8uik's implementation under it.

## Intermediate finite repair checkpoint

The normal run20261121T092032-test-b7974b processed all1817 run fixtures
but stopped later at an unobserved native ORC C++ build; it is not a whole
gate pass. Six acceptance regressions were compared on identical sources.
The current repair consumes pending block completion, retains callee-dependent
projection obligations until the existing retry, excludes provided copies with
missing conformance proof, and retains an omitted receiver equation only in
candidate ranking. The strict selected substitution is unchanged.

Retained native RED/GREEN controls cover late/early projection owner ordering,
wrong payload and rigid caller mismatch, raw return branches, valid/invalid
provided placements, and omitted/concrete/pattern associated receivers. Current
three native kernels pass (28 operand flags plus two boundary kernels).
The final finite certificate and limits below supersede this intermediate
pending checkpoint. The complete normal gate remains a separate parent
obligation. Follow
[the canonical current evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-contextual-operand-regression.json).

## Current parent acceptance boundary

Met-bu94/met-qo60 are resolved on the source31241607 finite certificate with exact target/native/gen receipts and formal5c9627 (G2, immutable, median7.145550s/5runs). Additional a76f2f9c associated refusal classification is separately resolved by com-yeua childmet-1yd7: freshbuild27d1db, all63public modes and12-line native guard/genaea48a pass. Former3Unclassified modes were not counted as successes on312. Neutral contextual_parent_final_review found no remaining mandatory finite product repair; closure remains conditional on currenta76 formal0633ed input stability/fixedpoint/<=7.5 and this checkpoint synchronization. Formal312 does not certifya76.

Current whole normal remains314fail and has not been rerun on this final combined source. Com-yeua/engineering3 and main/seed/carrier promotion remain open; broader unresolved producer-domain tasks are not silently removed from this boundary. Canonical current status/product and all original failed receipts are retained in phase3-contextual-operand-regression.json.
