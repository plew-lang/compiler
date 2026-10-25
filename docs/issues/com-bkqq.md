---
id: com-bkqq
status: closed
deps: []
links: [com-ugee]
created: 2026-10-25T08:52:16Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Re-review phase three completion against implementation and final evidence

## Scope and Reviewed State

User-requested fresh independent completion review of [met-si6j](met-si6j.md),
not an assumption that the preceding G3 approval is correct. Compiler
**dab97d524f5ad67db66ca7a17bcea98b13c10572**, meta
**58c9713d2cd89b7c75296a891b76b9e063929e26**, production043e2402,
fixture17537a40 and exact candidate3c532ce1. Original eleven criteria and adopted
scope are unchanged. Phase four, unsupported language features, main integration,
seed and adopted-carrier promotion remain outside this review.

## Independent Assignments and Findings

| Reviewer | Inspected scope | Result |
| --- | --- | --- |
| phase3_semantic_audit | Type/expected context, owner publication, call/proof/conversion storage, eight source call families, explicit instances and actual Mid/LLVM consumers; B0/B1 task-specific review | No additional confirmed implementation blocker in these paths. Newly accepts B0/B1 individually, with exact current fixture gate evidence independently confirmed by the evidence reviewer. |
| phase3_flow_modes_audit | Shared value-region and completion algebra, saved targets/cleanup, block/if/match/short-circuit, requested-body check/build/run/gen admission | Confirmed P2 [com-ugee](com-ugee.md): analytical loop noncontinuation suppresses missing-give rejection and expected type becomes the static result. Eleven watched check-only probes; no infinite loop execution. |
| phase3_evidence_scope_audit | Original criteria/scope, actual tk graph, raw input/config/log/LLVM/runtime/compiler hashes, ASan controls and manifest, task-review and document synchronization | Existing exact-candidate gates are valid. Independently agrees com-ugee violates the adopted specification without a new language decision. Found B0/B1 missing durable task-review records and stale pending descriptions; these record-only findings are addressed below. |

### P2: Expected Type Substitutes for a Missing Value Producer

The annotated block `{ while true {} }` is accepted by --check as I64, while
its unannotated form rejects. Block-bodied if/match reproduce the same issue.
Record.pw::recordValueBlock saves expectedTerm without a give; Verify's
checkBranchYieldsValue and single-block guard use execution.normal(), rather
than requiring source result production. A normal declared I64 function with
a nonterminating body is intentionally valid under its separate return contract.
This difference does not authorize inventing a value-region result.

[com-ugee](com-ugee.md) owns the exact producer/publication/consumer repair and
controls. Both flow and evidence reviewers independently classify it as an
existing in-scope defect. No new spec decision is needed. Criteria1/2/5/6/8
cannot currently be certified. G1/E1/completion/G3/parent are reopened, and
current progress is phase three rather than phase four. No production fix was
made during this review.

### Record Findings Addressed by This Review

B0/com-qehq and B1/com-qb05 did not retain a task-specific reviewer/revision/
disposition in their issue or receipt. This review does not infer that a prior
review occurred. phase3_semantic_audit newly inspected B0's eight rows and B1's
ordinary/method/factory producer -> saved authority -> instance -> final use,
removals and wrong/missing-selected controls, and accepted each bounded task.
phase3_evidence_scope_audit independently confirms all six cited current controls
PASS in final normal stderr.log: default_argument_call_templates:331,
dictionary_selected_method_signature:351, generic_call_selected_authority:553,
prepared_call_expression_source:1041, selected_call_verify_shadow:1135,
verify_call_selected_authority:1524. The standard harness compiles/links/runs and
compares golden output before PASS. Each task now retains its new recognition;
this does not substitute for closing com-ugee or the parent.

The stale body-checking section7 assertion that storage implementation remained
pending, and the unconditional unfinished assertion in meta's typechecking index,
are replaced by explicit scoped evidence/current-parent links. Current progress
and validation descriptions distinguish valid previous gate results from the
withdrawn overall completion claim. No normative specification is weakened.

## Evidence That Remains Valid

- Original11 criteria match17fb0e9d except checkboxes; no success-based narrowing.
- Pre-review68-node required graph matches its frozen receipt, no missing ID/cycle.
  The new required repair and review are explicitly added; that old snapshot is
  not a claim about the new live graph.
- All five standard profiles have5990 before/after/current matching inputs;
  current union5996 files matches. Raw result/config/log hashes and no-overlap
  conditions are independently verified.
- Generation2->3 actual LLVM/runtime match; measured/gen3/saved compiler all3c.
  Formal median independently recalculated5.954309s. Adopted carrierc367 unchanged;
  dirty bin/plewc is a different binary and was not used for these gates.
- Normal/gen/deps/LLVM22 ASan-LSan success is real; E manifest80 equals actual80
  success cases, raw pre-optimization ASan and actual UAF controls are present
  during the run. Failed intermediate gates remain failed. Harness differences
  add sanitizer controls rather than weakening checks.

## Outcome and Limits

Review complete, **phase-three completion is not re-certified**. Reopen the
owning value-result boundary, not every already verified source-selection task.
The recorded gates do not prove the newly found negative case was checked.
B0/B1 and stale records are addressed without production changes; com-ugee is
open and implementation is not authorized merely by this review's closure.

Durable machine evidence and all probe source/result text:
meta/evidence/existing-feature-conformance/source-owner-facts/phase3-completion-rereview.json.
Raw scratch is tmp/phase3-completion-rereview/flow. This review is not an
exhaustive proof over every program or phase-four runtime/ownership feature.
No full suite was redundantly rerun; exact candidate/source inputs are unchanged.

## Independent Record Acceptance

phase3_evidence_scope_audit independently accepts this review's documentation
and tracking update, based on the reviewed dab97d52/meta58c9713d state plus
the explicit review-only changes. It verifies the live70-node graph and receipt
states, reopened criteria/owners, all11 persisted source/output/hash controls,
unchanged candidate and target inputs, local links/anchors and the finite
com-ugee producer-to-final-consumer contract. This accepts the review task's
completion only; it explicitly does not re-certify phase-three completion.
