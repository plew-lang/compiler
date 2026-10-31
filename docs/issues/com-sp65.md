---
id: com-sp65
status: open
deps: []
links: []
created: 2026-10-27T19:19:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [runtime, tooling, verification]
---
# Distinguish program abort signals from ordinary exit status in panic assertions

## Contract, Evidence and Scope

Normal panic worker and ASan D require SIGABRT plus panic text, but process_watch.exit_status maps -6 to134 and leaves normal134 unchanged. A program that prints expected text and normally exits134 passes the same source predicate. probe_panic_output.py demonstrates normal134 acceptance with correct text; no real SIGABRT program executed in audit and no compiler bug claimed.

Bounded repair: retain subprocess-origin signal information through supervisor to normal/D panic classifiers, or an equivalently sound result contract. Add real SIGABRT versus ordinary134 with identical text, wrong signal/text, clean result, timeout and cleanup controls; preserve Unix CLI status normalization for external callers. Do not tighten arbitrary returncode regex or infer signal from text. No watchdog weakening or change to Plew panic semantics. TDD then affected runner/adapter gates and independent review. com-uiwg separately owns pre-trap stdout/side-effect assertions.

Scoped evidence: meta/evidence/test-audit/scoped-reviews/runtime-batch-0084.json and batch-0084-disposition.json (test/source baseline 9665094d). This is a separate finite follow-up, not a child/prerequisite of the audit epic or a claim repairs passed.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 18.

Row18: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Panic validators must preserve subprocess-origin signal identity and distinguish real SIGABRT from normal134 with equal text, before relying on normal/ASan-D assertions. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
