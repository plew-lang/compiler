---
id: com-kp0h
status: closed
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: bug
priority: 1
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Reject incomplete normal-suite dispatch results

## Contract and Evidence

Production run phase exits 0 with expected=1 pass=0 fail=0 when controlled xargs exits 1 before returning any case. Extracted unchanged phase and production progress helpers; not a full suite execution.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-1](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Preserve dispatcher status and reconcile expected versus returned case identities/counts for run/panic/reject/part/partreject. Test zero results, one missing result, worker interruption and complete positive/failing cases through the standard adapter. No fixture omission, timeout extension or summary-only workaround.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 1.

Row1: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Preserve actual normal dispatcher results/status/case identity before accepting normal run/panic/reject/part evidence. This validator repair precedes affected gate reliance, not all source investigations. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Repair Scenarios

Before implementation, test the actual production phase dispatch/aggregation
boundary for each run/panic/reject/part/partreject phase: dispatcher failure with
zero results; successful dispatch with zero or one missing result; duplicate or
foreign result identities (including equal total count); complete results followed
by dispatcher failure; worker interruption; out-of-order complete successes; and
complete results containing a legitimate case failure. Keep progress enabled and
quiet operation, existing labels, parallel budget (including an empty override
falling back to the standalone CPU default) and compiler/link/runtime/golden
checks. Results must correspond exactly once to the frozen discovered inputs.

Use controlled processes for intended failure causes and production adapters,
not a copied collector as proof. RED may pin the unchanged legacy phase while
its production adapter is extracted; final regression must invoke the actual
shared adapter and preserve the same observable scenarios. Keep existing worker
exit/output tests through the real worker entry. No fixture/golden omission,
timeout relaxation, gen/ASan classification change or compiler semantic repair.

Own the common dispatch status and identity reconciliation once, and have all
five standard phases consume it. Required verification is the scoped tooling
regression plus representative real compiler cases through that adapter and the
applicable normal consumer checks; whole-candidate gates/main admission remain
separate. Preserve pre-existing candidate/source failures with exact evidence,
not weaker expectations or a false full-suite GREEN.

## Intended RED

[Fixed legacy phase evidence](../../../evidence/test-runner-dispatch/red.json)
records100 controlled production-phase scenarios: all70 incomplete/invalid
result scenarios incorrectly exit0, while30 complete success/order/failure
controls behave as expected. Progress ON/OFF and all five phases are included.
The old harness is unchanged; this is real dispatch/result aggregation evidence,
not product semantics or a whole normal-suite success. Final regression will
use the shared production adapter after extraction, with no legacy fallback.

## Outcome

Resolved at compiler `94fb96db921c57ea9034f224325de895ab547ad2`.
All five actual normal phases now share dispatch status and exactly-once
expected/result identity reconciliation; the original worker checks and discovery
are preserved. Cancellation reclaims the owned group, and progress plus CPU/default,
empty-override and explicit worker budgets are retained.

The [completion record](../../../evidence/test-runner-dispatch/completion.json)
links original RED, final160 controls and56 existing status controls (exit0),
five detected mutation kinds, actual compiler adapter smoke10/10, baseline worker
comparison and [independent acceptance](../../../evidence/test-runner-dispatch/final-review.json).
No required in-scope defect, concern or specification decision remains.

The complete standard normal consumer at6d9cac0f/jobs8 covered all2,834 fixture
identities with unchanged inputs, no omission/duplicate and skip0, but exited1 on
five source failures also reproduced by the old worker with the same candidate.
The final94fb production delta only restores empty-override fallback; final
controls/smoke are separate, not a false final-revision full-suite GREEN.
[Exact limits and failures](../../../evidence/test-runner-dispatch/README.md)
remain mandatory inputs to com-2hx2/com-lbnc/com-x7r3 and open final gate com-9l3b.
No compiler source, fixtures, expected values, timeout, seed or carrier was changed
or promoted. This closure does not certify phase three, performance or main.

## Neutral Completion Recheck

A fresh reviewer without conversation history independently derived requirements
from the original `ef4ba494` task and project contracts before checking compiler
`37614034` (product `94fb96db`). The [neutral review](../../../evidence/test-runner-dispatch/neutral-review.json)
accepts closure with no required in-scope defect, unresolved concern or specification
decision. Fresh160 tooling and56 existing status controls both exit0; source hashes
match the reviewed product. The full-normal revision/five source failures and the
initial RED command/whole-process receipt documentation limits are explicit;
no full-candidate GREEN, new source validity or gate waiver is inferred.
