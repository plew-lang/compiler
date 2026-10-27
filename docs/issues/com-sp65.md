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


