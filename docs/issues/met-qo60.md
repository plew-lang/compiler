---
id: met-qo60
status: in_progress
deps: [met-bu94]
links: []
created: 2026-11-20T11:30:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-u22d
tags: [frontend, diagnostics, verification]
---
# Retain method and associated lookup roles through publication

Contract: design/name-lookup.md diagnostic context is not selected authority; body-checking.md retains the chosen operation. Propagate private Selected(function)/DiagnosticCandidate(function)/NoCandidate roles through the four remaining method/associated collectors, their composing resolvers, Expr/ExprType/Verify caches, Record diagnostic argument checking and final publication. Abstract requirement/dynamic result types remain distinct. Public Raw compatibility observations may retain their old representation, but compiler source/final consumers must not use them to manufacture selected authority.

Finite owner inventory: Resolve/Module.pw findMethodWithOrigin,findCallableInViewSetWithOrigin,findExtMethodBySource(no compiler caller),findAssocWithOrigin. Include resolveMethodForResolvedReceiverWithOrigin/resolveExtMethodFinalWithOrigin and associated Expr/ExprType routes; Record's associated/resolved/syntax/newtype fallback chain; Verify/Ops recordResolvedMethodCallee; method/static template publication. A Diagnostic role is not a NoCandidate sentinel that authorizes another surface search. Keep the selected surface/receiver/proof/signature context for nonpublication checks, retain detailed diagnostics, and refuse even if diagnostic-only argument checking passes. Cache, result and parent descriptors require Selected.

Preserve current priority: applicable inherent set before provided; inherent rank1 must not newly hide a provided rank2. View-set pass0 label-only still shadows later pass according to current source rules. Associated bare full, then provided typeMatchOnly full, then bare diagnostic. Preserve required-trait/newtype/explicit-source restrictions and duplicate/instance identity distinctions. Do not broaden ranking or overload semantics as part of role propagation.

TDD and acceptance: selector-only RED for each collector and cache/parent/final nonpublication; Raw compatibility, retry/malformed cache; inherent full/provided full and inherent rank1/provided full; view pass0rank1/pass1full shadow boundary; associated full/fallback combinations; same declaration duplicate/third distinct/different source instance; newtype,namespace,alias,generic receiver,provided signature,literal/mode/type diagnostic controls; actual normal method/associated callee output and one-time evaluation. Enumerate all source/final consumers, remove competing UInt-as-authority paths, run affected gates and independent final review. Independent neutral plan review confirms scope/dependencies and these rules in the parent. Excluded: Source admission com-b0e6/com-8uik, separate gen authority and new language rules.


## Existing selected-method context REDs

Add the existing argument-context formation boundary to the required TDD: run/generic_method_result_argument_context and generic_associated_result_argument_context both reject on old1bd and new598 in check/AOT/ORC with cannot-infer-all-type-arguments. The same nested member result succeeds with an Optional[I64] binding annotation or a free read(value:Optional[I64]) parent; its declaration is not inherently uninferable. run/method_if_construction_argument_context rejects on both with integer-literal-no-context despite a fixed Optional[I64] parameter. Expected outputs0,0,7 follow existing generic/expected-context rules; neutral review confirms method syntax does not remove that context. These are valid new RED tests for baseline defects, not regressions attributed to A or erroneous old test oracles.

Before repair, trace actual lookup role/rank, nested saved template and zero slots, the exact query demanding completion before supplying the fixed parameter context, and receiver/own-binder versus inner-binder obligations. recordSelectedMethodArguments currently invokes finalMethodEnvironment before applying context and before literal validation, but this is a hypothesis to prove, not an established root cause. Nonpublication diagnostic and genuine Selected argument paths must share appropriate prepared source signature information, not require finalized operands to obtain the signature that types those operands. If a shared-matcher deficiency is proven, reconcile A's boundary rather than silently assigning blame. Existing metadata and measured failures are in the parent's canonical evidence and scratch member-final-controls/result.json. No Source-domain admission rule or new language behavior is introduced.


## Active role increment

A closed after independent source review and standard five-sample generation2 fixed point median6.935289. B began with ProvisionalMemberAuthority: the unchanged598 candidate compiles the internal fixture, then native exits-6 with the intended assertion `diagnostic member became a final callable`. This probes the final resolvedCallee consumer before lexical body publication, not the compatible Raw findMethod observer. Bare, associated and explicit extension forms are included; per-surface detection and postfailure cache/template controls remain required.

Current WIP introduces private MemberCallLookup and propagates it through four collectors and composed semantic resolvers. Only NoCandidate permits fallback. Record consumes diagnostic arguments before refusing and never publishes a diagnostic parent; final wrappers and ExprType require Selected. Public raw find* compatibility observers retain scalar observations. Whole source --check passes on the unchanged598 carrier; fresh native and scenario gates pending. The three method-parent context defects remain open here; this increment does not claim their repair.


Fresh initial-role build20261120T124931-build-3dceaa passed immutable, but does not include later source/cache/context-order refinements. MemberCallCacheOutcomes adds a separate RED: a NoStatic observation is reopened as successful source selection (native-6 intended assertion). Repair retains CachedNonStatic separately from NoCandidate; independent abstract/dynamic evidence can still be checked, but the observation cannot authorize another static search or a Source failure. Out-of-range Selected is a raw error. ProvisionalMemberAuthority now also checks unknown result, failed-retry cache, parent-template and final-call nonpublication. These expanded GREEN gates remain pending.

The existing context RED's actual early-demand chain is recordSelectedMethodArguments -> checkLitSpanCtx -> checkLitCtx(Method) -> checkMethodArgs -> checkRecordedCallLiteralArguments -> Incomplete saved substitution. Normal expected-result completion was called only afterwards. If/generic-Make similarly loses full type arguments at the early scalar literal check. WIP applies saved child result context first; neither new inference semantics nor scope reopening. Whole-source --check succeeds; external GREEN not yet claimed. Canonical finite evidence: ../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-member-call-roles.json.


Independent role review found a remaining cache-to-lookup leak in ExprType's ChainHole continuation. The expanded MemberCallCacheOutcomes reaches a genuine optional-chain Method receiver and reproduced native-6 `chain continuation reopened an observation cache` on the pre-fix source. The continuation now falls back only for NoCandidate; associated type recovery reads the same role-aware cached query instead of calling findAssoc again. Cache tests cover bare, associated and explicit view observations, out-of-range Selected, type recovery and failed retries. Provisional test also checks parent-template/final nonpublication. MemberPreparedArgumentContexts checks completed saved substitutions for the three valid method-parent REDs. Fresh verification still pending.


## Late consumer closure and bounded gates

Source review plus concrete internal REDs found Array's direct type recovery bypassing the callee cache, and pow collapsing DiagnosticCandidate into a scalar sentinel before free fallback. Both now retain the original role: Array uses the same resolved member/ChainHole query; named-operation diagnostics terminate instead of choosing a free result. Source ExprType0dbeab21 reproduces the named-operation concrete-result assertion and the prepared File/Std Array NoStatic result leak. Initial Text/unprepared Array attempts did not reach this path and are not RED evidence. Internal fixtures use public callTemplateCount, authored module filters, and explicit recovery queries. File/Std is required for imported protocol/Array setup. Current-source four-native follow-through passes, exact expected stdout and empty runtime stderr. Array recovery is probed only after recording its real File/Std receiver operand; an unprepared raw Array cannot prove this query. Raw/prepared/Source grant distinctions are preserved. Fresh final CLI compiler build remains pending.

The intermediate0dbeab21 product passes all9check/AOT/ORC formerly failing method-parent modes (0,0,7), normal None/Some/free context and inherent-full/provided-full priority controls. Combined78 old/new comparisons preserve expected outcomes, with19 native executions, except6 explicitly retained baseline positive failures. trait_subject_associated_precedence is the already reopened [com-9clj](com-9clj.md#reopened-current-source-regression-controls) control, not a newly discovered or fixed issue here. Actual last cache repairs are not retroactively certified by this intermediate build. Final candidate, full targeted controls, gen, fixed-point/performance and neutral acceptance remain required. Parent/whole/main remain open.


## Associated Self applicability follow-through

Fresh5cd63 CLI exposed a regression in existing global_callable_named_pow; old598 succeeds, intermediate0dbe and5cd63 both reject at the named-operation global initializer. The bare associated collector alone still compared the declaration's ungrounded Self via callableArgMatchRank. The previous firstLabel-as-selected fallback masked the incomplete ranking. AssociatedReceiverApplicability proves the same typed literal operands have shared receiver-grounded rank2 while the composed associated resolver returns no selected function (native-6 exact assertion). This is not a cache-precedence specification change. Use the existing groundedMethodArgMatchRank with the receiver for this collector too, keeping all priorities and diagnostic roles. No Diagnostic is promoted after argument checks.

The repaired source kernel passes that exact selected-function assertion and opens the actual global named-pow File initializer successfully. Whole-source --check passes using5cd63 carrier. Independent review supports this shared-signature correction, requires generic namespace/ambiguous receiver/rigid binder controls, and keeps finite completion pending. Before this repair,5cd63 passed75numeric modes,54Array/closure old-new pairs,48Float old-new modes and12internal natives; its CLI regression remains explicitly failed, not an adopted candidate. Rebuild the new final source and repeat affected gates before formal performance or closure.
