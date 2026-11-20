---
id: met-bu94
status: closed
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

Implementation and evidence: revisions1bdccf70,8702289f,ea0bce38,c68d80ec,06a3392f,59803500; parent com-u22d keeps the original RED and repair account. Canonical evidence: ../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-provisional-call-context.json. Final fixed snapshot context-guard-build/source59803500 passed all gates below. Earlier c68 Raw NumericCandidateContexts regression is not adoption; final598 passes that unchanged test. Raw fault old RED/new normal and malformed controls are retained.

Acceptance: reconcile every parent scenario owned here with final-snapshot normal/reject/Raw/cache/retry/nonpublication assertions, actual native/ORC output, source structure, gen and applicable isolated same-source performance/fixed-point gates; independent neutral final review. Preserve detailed wrong-type/literal/mode diagnostics and genuine Selected authority. Existing whole324 failures remain the parent's required gate, not a green result here. No main/seed/carrier promotion. Excluded: method/associated role propagation (sibling), Source expected-context admission com-b0e6/com-8uik, gen authority, Float/default semantic changes and unrelated nested-Array identity.


## Final guard candidate gates

Source59803500 fixed build20261120T112517-build-60a5cf passed immutable. Focused51modes, numeric75modes, Array/closure54old-new pairs (8exact LLVM,1verified internal-name bijection), representative96old-new modes and Float16old-new modes pass. All8internal natives pass including unchanged NumericCandidateContexts and raw ContextualCallResultCompletion. Standard gen20261120T113644-gen-574570 passes. New partial_member_argument_context adds6old-new check/AOT/ORC controls and native outputs for method/associated construction and already-selected nested member results through a free parent. The companion baseline method-parent failures belong to met-qo60 and are not positives here. Formal repeat20261120T122551-self-host-ff7f11 passed unchanged inputs, generation2 LLVM/runtime/successor binary exact match. All5times7.512016,6.932653,6.931184,6.935289,6.936192 give median6.935289seconds. Prior formal7.218727 is preserved, not reclassified as passed performance. No implementation change or definitive environment cause claimed. Fresh no-history final reviewer met_bu94_final_review found no concrete blocker in A and reconciled exact formal/input results. Finite A may close; no whole-green, parent closure, main or carrier promotion.
