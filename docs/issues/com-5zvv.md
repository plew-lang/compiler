---
id: com-5zvv
status: in_progress
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

## Reconciled Audit Subset

The four [canonical reconciliation indices](../../../evidence/test-audit/scoped-reviews/README.md#canonical-reconciliation)
contain exactly404 of404 driver-primary obligations, by exact role
{'observed-behavior': 7, 'generation': 25, 'meta-operational-control': 3, 'checker-contract': 29, 'diagnostic-role': 31, 'role-intake': 309}. Shared runtime-primary
roles do not increase this task's count. Exact ID/role/owner partition is canonical
in those indices, not inferred from report count or execution results.

Batches0128/0129/0132 independently reconcile actual generation/provider and manual
callback/global/ORC paths, helper source setup, exact prior range reuse,
and synthetic meta supervision controls. Existing finite owners preserve scope;
no real compiler/program/sanitizer execution or production repair. Remaining
checker/diagnostic/intake obligations and area closure remain this audit's work.
