---
id: com-e713
status: closed
deps: [com-5by1, com-ouh2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 2
assignee: Koji Murata
parent: com-jno0
tags: [frontend, verification]
---
# Audit frontend language test expectations and coverage

## Scope

Audit all frontend assertions assigned by com-ouh2:
lexing/parsing, names/visibility, declarations, overloads/generics, type behavior,
expressions/control flow, diagnostics and other currently provided language
surface. The assignment follows assertion contracts, not fixture directory or
prefix. Reuse existing evidence only when scope and inputs match. Unknown claims of unsupported behavior need
contract/implementation evidence, not current rejection alone.

Read relevant spec chapters and frontend design independently of current expected
outputs. Target wrong-reason rejection, weak diagnostic assertions and untested
feature interactions, while preserving the adopted forward-only inference,
ownership and explicit divergence rules. Syntax/standard-library tests can be
language or implementation tests according to what they actually assert.

## Method and Exit

Use the exact batches assigned by com-ouh2 and the rules in com-5by1.
Before starting, split oversized batches under current planning rules; this is
not an open-ended promise to inspect every conceivable combination. Previously
reviewed assertions can be reused only with matching scope and inputs.

For every assigned assertion establish original intent, spec/design oracle,
actual path/mode, registration and a failure that discriminates the intended
contract. Independently derive missing positive/reject and interaction controls
from the contracts rather than filenames. Use known faults or selective isolated
controls for important boundaries, not a blanket mutation-testing framework.
Classify expectation errors, weak/incorrect paths, unregistered tests, missing
controls, unresolved semantics and separately unsupported features. Check the
original intent before recommending deletion, movement or expectation changes.

Route findings and test/runner corrections to concrete finite owners before
closing; follow existing stopping rules and keep this audit separate from actual
repairs. Required follow-ups stay open under their responsible area. Save exact
inventory revision, assertion dispositions, grounds and scoped independent review.
Completion means the assigned finite audit is reconciled, not zero unknown bugs,
all future features implemented or all resulting defects already fixed.

## Outcome

Investigated: all3132 assigned obligations are reconciled, comprising1707
source admissions,1157 source rejections,251 observed outcomes,9checker
contracts and8role intakes. Exact IDs, immutable inputs, reports/receipts,
accepted corrections and finite finding owners are canonical in the four
[reconciliation indices](../../../evidence/test-audit/scoped-reviews/README.md#canonical-reconciliation).

Independent [frontend area closure](../../../evidence/test-audit/scoped-reviews/review-frontend-area-closure.json)
SHA74ad3328b4ae59f4567ff92619779ce98f7bc5d2dba6cba371111b5bd05bb56b
accepts this finite audit after contract-first partition, scoped evidence,
original-intent and consumer/control reconciliation. Four internal fail-fast
inputs received additional finite source/history/positive-control review;
metadata corrections and temporal snapshots are retained rather than rewritten.
No assigned unread obligations or unowned required audit findings remain here.

Source/API migrations, concrete rejection masks, weak oracles, unsupported
features and unresolved language rules remain distinguished under their finite
owners. Missing .err alone is not a mandatory defect; current compiler behavior
cannot settle adopted semantics. Investigation closure does not close repairs
or decide those questions. No real compiler/program/sanitizer/performance run,
production input change, frontend implementation acceptance, phase-three
completion or main/seed readiness is certified. Source baseline9665094d,
spec5bd65a5 and exact Syntax8c892042 remain unchanged.
