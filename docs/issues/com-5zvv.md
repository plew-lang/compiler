---
id: com-5zvv
status: closed
deps: [com-5by1, com-ouh2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 2
assignee: Koji Murata
parent: com-jno0
tags: [driver, verification, tooling]
---
# Audit driver generation dependency and harness test contracts

## Scope

Audit the driver/gen/dependency/tooling/harness assertions
assigned by com-ouh2: check/build/run/gen requests, package/module and
root/part handling, AST generation registration, native/session/ORC/CLI boundaries,
bootstrap/build/measurement/watchdog scripts and sanitizer orchestration.
Separate supported product behavior from manual embedding diagnostics and native
bridge probes. Name the exact requests a lazy test makes; unrequested bodies are
not proof of their validity.

Inspect runner success/failure classification itself: expected rejection versus
unrelated exit1/internal failure, panic text/signal, stdout comparison, missing
companions, timeout/child cleanup and instrumentation scope. Verify intentional
negative controls are noticed. Tooling correctness follows its own design/entry
contract and must not reuse the helper under test as the sole expected oracle.
Do not change watchdog, gate strength or profile semantics within this audit.

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

Investigated: all 404 assigned obligations: seven observed outcomes, 25 generation contracts, three meta operational controls, 29 checker contracts, 31 diagnostic roles and 309 role intakes are reconciled. Exact IDs, inputs,
reports, independent receipts, accepted corrections and finite finding owners
are canonical in the four
[reconciliation indices](../../../evidence/test-audit/scoped-reviews/README.md#canonical-reconciliation).
No assigned unread obligations or unowned required audit findings remain here.

Independent [area closure](../../../evidence/test-audit/scoped-reviews/review-driver-area-closure.json)
SHA 1c63111ad7c67862387e39cdbcde39cb4fb74464a9350716024c29e1d61b8bfe accepts this finite audit after
contract-first partition and scoped intent/oracle/path/control/owner review.
Prior input-matched evidence reuse and reviewer exposure remain disclosed;
counts and review receipts alone are not a semantic correctness proof.

Generated, manual, native/ORC and standard-dispatch inputs retain their actual request and registration boundaries. Batch131 preserves its original snapshots and redirects the missing-golden finding to existing com-mt7l; met-py42 is a closed duplicate. Source acceptance and shared runtime obligations are not counted twice.

Source/API migration, concrete masking errors, weak oracles, unsupported lanes
and unresolved semantics remain distinct under finite responsible owners.
This investigation does not repair or decide those items. No actual Plew
compiler, generated/native/JIT program, sanitizer or performance run occurred;
controlled checker/reader/worker observations remain narrow evidence only.
Production source baseline 9665094d, spec 5bd65a5 and exact Syntax 8c892042 are
unchanged. No implementation, phase-three, main/seed or carrier acceptance
follows. Whole-corpus closure belongs separately to com-tqzw.
