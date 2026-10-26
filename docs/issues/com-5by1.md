---
id: com-5by1
status: in_progress
deps: []
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Integrate TDD scope and independent review rules into development entry points

## Contract and Actions

Operationalize the approved method using existing entry points. Read the
[execution plan](https://github.com/plew-lang/meta/blob/7893c820/agents/llm-development-workflow-proposal.md), [verification design](../design/verification.md) and
[local issue rules](README.md); reconcile existing instructions before adding any.

1. Keep meta AGENTS short: mandatory principles and links, not a second manual.
2. Mark task-start TDD rules as required reading at every task start in meta
   AGENTS and its document index. Update agents/development-workflow.md to derive
   a scenario list from the complete task guarantee and preserved behavior before
   taking one scenario through actual RED, GREEN and responsibility-level cleanup.
   Reconcile guarantee coverage and assertion effectiveness before closure.
   Pure behavior-preserving refactors use characterization and structural
   acceptance, not artificial RED. Documentation-only changes need no fake test.
3. Update this directory's README with action-oriented titles and body contracts:
   guarantee, covered/excluded shapes, producer/final consumer, replaced paths,
   tests, review, applicable gates and actual prerequisites.
4. Update tests/README.md with oracle grounds, discriminating failure, actual
   entry/mode and audit expectations. Preserve existing discovery responsibilities.
5. Document spec-first independent review: first contracts/revision/limits, then
   implementation narrative; classify confirmed violations, hypotheses, optional
   improvements and unresolved semantics. Verify findings before accepting or
   rejecting them. Re-review affected conclusions, not an endless full restart.

Do not change language semantics, source code, test expectations, tk behavior,
standard gate thresholds or the task graph as part of this rule edit. Do not
claim a review happened merely because a record exists. User per-task chores
must not increase.

## Exit and Evidence

One owner per rule with working links; no stale contradictory TDD/review advice.
Record document revisions and a fresh-context walkthrough from a normal work
entry to the correct contract, RED/refactor exception and closing evidence.
Obtain independent completion review of these operations before closing. Actual
compiler execution under the method is the separate process trial com-bv1s.

## Documentation-change Validation Plan

This task changes operating documents only; use the documented non-behavioral
exception rather than manufacturing a compiler RED. Required checks are:

- Every-task required-reading wording is discoverable from AGENTS and the index,
  including the exception to the general avoid-mechanical-rereading advice.
- Guarantees and preserved behavior produce a scenario list before coding;
  scenarios are incrementally automated and updated, not all coded up front.
- Intended RED is distinguished from setup/wrong-reason failure; already-correct
  controls and pure refactors need no artificial failure. Compiler build/gate
  guidance cannot silently bypass RED or require all final gates per iteration.
- Each guarantee maps to meaningful assertions at completion, with important
  boundary/interference/path controls and valid oracle grounds. No all-combination
  or numerical code-coverage quota is substituted for semantic sufficiency.
- Task and test guidance link to their responsible rules, independent review
  verifies findings instead of accepting every objection, and no semantics,
  expectations, tool behavior, validation threshold or dependency graph changes.
- Check document links/headings and obtain the required fresh-context walkthrough
  and independent completion review. Actual workflow effectiveness remains the
  separate real-repair trial com-bv1s, not a claim made by this document edit.
