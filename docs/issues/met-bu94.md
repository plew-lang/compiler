---
id: met-bu94
status: in_progress
deps: []
links: []
created: 2026-11-20T11:30:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-u22d
tags: [frontend, diagnostics, verification]
---
# Finish prepared argument matching and free-call selection roles

Contract: design/name-lookup.md applicability/publication and body-checking.md contextual commitment. Close the implemented common numeric/prepared-argument matcher and free DiagnosticCandidate/Selected boundary end to end. Covered: direct/block/if/match integer shapes and both declaration orders; known field and phantom constraints; partial nominal and already-selected nested results; rigid caller versus callee holes; Raw versus prepared facts; free lookup/cache/Record/ExprType/final publication and diagnostic precedence. Do not publish a diagnostic candidate, reopen a closed block, retype a determined operand, or infer an outer binder from a foreign unresolved callee binder.

Implementation and evidence: revisions1bdccf70,8702289f,ea0bce38,c68d80ec,06a3392f,59803500; parent com-u22d keeps the original RED and repair account. Canonical evidence: ../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-provisional-call-context.json. Latest guard fixed snapshot context-guard-build/build20261120T112517-build-60a5cf is still running. Earlier c68 passes51+75modes,54Array/closure pairs,96positive modes,16Float modes,6internal natives; its raw NumericCandidateContexts regression is not adoption. Unchanged numeric test and initial/late record/default/format source-native pass with598 guard. Raw fault old RED/new normal+malformed controls are retained.

Acceptance: reconcile every parent scenario owned here with final-snapshot normal/reject/Raw/cache/retry/nonpublication assertions, actual native/ORC output, source structure, gen and applicable isolated same-source performance/fixed-point gates; independent neutral final review. Preserve detailed wrong-type/literal/mode diagnostics and genuine Selected authority. Existing whole324 failures remain the parent's required gate, not a green result here. No main/seed/carrier promotion. Excluded: method/associated role propagation (sibling), Source expected-context admission com-b0e6/com-8uik, gen authority, Float/default semantic changes and unrelated nested-Array identity.


## Final guard candidate gates

Source59803500 fixed build20261120T112517-build-60a5cf passed immutable. Focused51modes, numeric75modes, Array/closure54old-new pairs (8exact LLVM,1verified internal-name bijection), representative96old-new modes and Float16old-new modes pass. All8internal natives pass including unchanged NumericCandidateContexts and raw ContextualCallResultCompletion. Standard gen20261120T113644-gen-574570 passes. New partial_member_argument_context adds6old-new check/AOT/ORC controls and native outputs for method/associated construction and already-selected nested member results through a free parent. The companion baseline method-parent failures belong to met-qo60 and are not positives here. Isolated performance/fixed-point interpretation and independent final acceptance remain pending; no whole-green, parent closure, main or carrier promotion.
