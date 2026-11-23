---
id: met-bu94
status: open
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

## Reopened contextual-operand regression

See [com-u22d current boundary](com-u22d.md#reopened-current-boundary). Existing contextual literal/noninterference acceptance regressed in both free and member/associated paths; preserve the existing scope and Selected/DiagnosticCandidate guarantees. Previously recorded bounded successes remain historical evidence, not current full acceptance.


Contract: design/name-lookup.md applicability/publication and body-checking.md contextual commitment. Close the implemented common numeric/prepared-argument matcher and free DiagnosticCandidate/Selected boundary end to end. Covered: direct/block/if/match integer shapes and both declaration orders; known field and phantom constraints; partial nominal and already-selected nested results; rigid caller versus callee holes; Raw versus prepared facts; free lookup/cache/Record/ExprType/final publication and diagnostic precedence. Do not publish a diagnostic candidate, reopen a closed block, retype a determined operand, or infer an outer binder from a foreign unresolved callee binder.

Implementation and evidence: revisions1bdccf70,8702289f,ea0bce38,c68d80ec,06a3392f,59803500; parent com-u22d keeps the original RED and repair account. Canonical evidence: ../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-provisional-call-context.json. Final fixed snapshot context-guard-build/source59803500 passed all gates below. Earlier c68 Raw NumericCandidateContexts regression is not adoption; final598 passes that unchanged test. Raw fault old RED/new normal and malformed controls are retained.

Acceptance: reconcile every parent scenario owned here with final-snapshot normal/reject/Raw/cache/retry/nonpublication assertions, actual native/ORC output, source structure, gen and applicable isolated same-source performance/fixed-point gates; independent neutral final review. Preserve detailed wrong-type/literal/mode diagnostics and genuine Selected authority. Existing whole324 failures remain the com-yeua / 工程3 whole-candidate gate, not a green result here or a new finite com-u22d closure condition. No main/seed/carrier promotion. Excluded: method/associated role propagation (sibling), Source expected-context admission com-b0e6/com-8uik, gen authority, Float/default semantic changes and unrelated nested-Array identity.


## Final guard candidate gates

Source59803500 fixed build20261120T112517-build-60a5cf passed immutable. Focused51modes, numeric75modes, Array/closure54old-new pairs (8exact LLVM,1verified internal-name bijection), representative96old-new modes and Float16old-new modes pass. All8internal natives pass including unchanged NumericCandidateContexts and raw ContextualCallResultCompletion. Standard gen20261120T113644-gen-574570 passes. New partial_member_argument_context adds6old-new check/AOT/ORC controls and native outputs for method/associated construction and already-selected nested member results through a free parent. The companion baseline method-parent failures belong to met-qo60 and are not positives here. Formal repeat20261120T122551-self-host-ff7f11 passed unchanged inputs, generation2 LLVM/runtime/successor binary exact match. All5times7.512016,6.932653,6.931184,6.935289,6.936192 give median6.935289seconds. Prior formal7.218727 is preserved, not reclassified as passed performance. No implementation change or definitive environment cause claimed. Fresh no-history final reviewer met_bu94_final_review found no concrete blocker in A and reconciled exact formal/input results. Finite A may close; no whole-green, parent closure, main or carrier promotion.

## Current whole-suite forward-frontier repair

The immutable whole run `20261122T152131-test-9ce06a` exposes false acceptance of unchanged `closure_overload_later_if` and `closure_overload_later_match`. The public raw-ranking probe at `compiler/tmp/current-whole-regressions/ClosureFrontierProbe.pw` shows both candidates rank2 for the first untyped closure, but the complete conditional ranks2/1 after a later typed branch. No semantic operand fact is published. Therefore the defect is speculative backward candidate filtering, not stale-cache publication. Existing `closure_overload_forward_context` is the positive control; do not change either rejection expectation.

Repair boundary: separate candidate compatibility from whether the first normally completing branch needs the selected expected context. Later branches must not select a candidate that the first normal branch cannot distinguish. Preserve explicit outer context, first-branch partial explicit signatures, source divergence, callee-only deferred bindings, independent argument completion, typed operands and shared free/member matching. A Deferred-only early exit is insufficient: contextual numeric literals currently report Matched. Do not use `argumentRequiresResultContext` as independent-source readiness: raw known operands also have semantic term0. Do not infer a new array-order specification from these conditional failures.

Before editing: independently review a finite common-frontier plan against body-checking and spec01. Add missing numeric if/match order controls and raw nonpublication assertions, reuse existing closure cases, reproduce RED with fixed f94 carrier, then implement and run affected modes plus fresh candidate/performance gates. This is within the existing guarantee, not a new task or closure. Source-domain transport of seven new numeric rejections remains com-yeua/com-8uik.

Independent forward_frontier_plan_review supports the finite matcher-result plan, with numeric Matched/readiness separation, source-normal filtering and no parallel AST classifier. New tracked numeric later-if/match both falsely accept on fixed f94; existing late-closure two also accept; existing forward-closure succeeds. Exact RED receipt and review disposition are in canonical phase3-contextual-operand-regression.json current_whole_regression_followthrough. Source implementation pending.
