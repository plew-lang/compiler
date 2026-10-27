---
id: com-e713
status: open
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
