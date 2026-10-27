---
id: com-z5k3
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, runtime, verification]
---
# Reject sanitizer diagnostics on manual ORC lazy failure checks

## Contract and Evidence

test-orc-lazy.py failure path accepts exit1 plus lazy compilation failed while success/trace paths check sanitizer cleanliness. Native failure followed by ASan exit1 can satisfy same assertion. Source-backed unchecked conjunction, no native memory fault executed.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [RT-05](../../../evidence/test-audit/scoped-reviews/review-runtime.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Add controlled expected-domain-failure plus sanitizer-error stderr/exit collision and clean failure controls. Preserve terminal lazy failure text and native ASan/LSan checks; choose explicit failure policy consistently with native diagnostic contract. Do not claim nested JIT instructions instrumented.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.


