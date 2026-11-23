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

Independent forward_frontier_plan_review supports the finite matcher-result plan, with numeric Matched/readiness separation, source-normal filtering and no parallel AST classifier. New tracked numeric later-if/match both falsely accept on fixed f94; existing late-closure two also accept; existing forward-closure succeeds. Exact RED receipt and review disposition are in canonical phase3-contextual-operand-regression.json current_whole_regression_followthrough. Source frontier implementation and final31241607 certificate are recorded below.

## First-normal frontier implementation increment

The shared recursive matcher now returns compatibility, context dependence and source-normal value presence in one walk. Joins stop before later arms when the first normal value needs the selected expectation; explicit constraints still filter candidates, independent arguments/retries stay active. Array readiness comes from its first element; nominal field context comes from its independently recovered full type, while structural record fields contribute readiness. No second AST classifier or source-fact publication is added.

Standard isolated build20261123T042558-build-190b67 succeeded; its initial implementation passes42check/AOT/ORC controls. The later readiness refinements are not retroactively certified by that binary. New BranchCandidateFrontiers has16 raw scenarios and complete fact/template/closure/callee nonpublication assertions. Old-source native RED and new-source GREEN are verified; review caught a structural-record OR omission during refinement, separately reproduced as native RED and fixed. Final3 native kernels (branch16, existing prepared28, numeric) pass exit0/exact golden/empty stderr. Final31241607 candidate and formal gates are recorded below; parent/whole gates remain separate. Canonical evidence forward_frontier_implementation distinguishes every source stage.

## Member surface frontier controls

Added method later-if and associated later-match closure refusals plus a successful early-typed member/associated counterpart. Fixed f94 falsely accepts both negative inputs; final31241607 candidate rejects both and executes the positive42/42. The associated rejection currently has Unclassified instead of Source in all three CLI modes, explicitly owned by com-yeua child met-1yd7, not silently accepted here. RED/final receipts are in canonical phase3-contextual-operand-regression.json. No existing input or expectation changed.

## Final finite source certificate

Source31241607, fresh build20261123T060114-build-80c563 / carrier5d9ee2bb, has exact6native (branch frontier, prepared contexts, numeric contexts, member identities/admission/inference), provided private guards, public generic5-line and associated/identity/native/ORC controls, existing generic102/CLI120/numeric75/Array54/Float48 and standard genf3902a. Formal20261123T061202-self-host-5c9627 is immutable, generation2 fixedpoint, successor equality, five times7.846941/7.157484/7.081429/7.106972/7.145550; median7.145550 meets approved7.5seconds. Old7.525428 failure remains evidence. Neutral final source/evidence review finds no remaining finite obligation. Canonical phase3-contextual-operand-regression.json retains exact receipts.

Currenta76f2f9c adds only the separately owned associated ambiguity refusal kind/owner-helper route (met-1yd7), not matcher/proof/obligation changes. Fresh build27d1db and all63public modes pass, including previously Unclassified3 now Source with original main diagnostic/status. These failures were not counted as successes on31241607. Do not apply312 formal timings retroactively to a76. New associated guard/gen receipt and independent final review remain their owner. Parentcom-u22d/com-yeua, whole normal/ASan and main/seed/carrier promotion are not certified here.

Closure reason: resolved within the finite scope above. Fresh a76 guard12-line native and genaea48a have now also passed; no pending changed-path functional control remains. Neutral final reviews forward_frontier_plan_review/provided_identity_plan_review are reconciled against the source312 certificate and current63mode receipts. The a76 formal run is a separate parent-candidate gate, not a retroactive source312 result.
