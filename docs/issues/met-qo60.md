---
id: met-qo60
status: open
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

