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
