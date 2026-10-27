---
id: com-wfq2
status: open
deps: []
links: []
created: 2026-10-27T21:28:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Reconcile the selected conditional trait-edge test oracles


## Finite Audit Question

At source baseline9665094d/spec5bd65a5, inspect exactly tests/fixtures/reject/conditional_conformance_edge_path.pw with .err and run/conditional_conformance_edge_path.pw with .out. Both declare impl[T] Source[T] as Target where T:Required, conditioning a trait-to-trait edge on selected Source instances. Spec08 explicitly excludes separate conditional trait-to-trait conformance and requires the full declared source range. Original4bfa4247 tests condition discharge along such an edge; current accepted implementation behavior is not an adopted language oracle.

## Deliverables and Completion

Recover that exact introducing body/diff and canonical decisions, distinguishing a deliberately retained current unsupported-feature lane from adopted-valid source. Under the adopted prohibition, identify the meaningful declaration rejection and preserve conditional-proof propagation through legitimate nominal conformances/unconditional trait edges in neighboring controls. Decide deletion, movement, or rewritten test purpose from original intent rather than blessing current acceptance. A contrary semantic change needs user approval; ordinary application of the explicit prohibition does not. Assign exact test/consumer corrections and applicable RED/GREEN/independent review before closing this investigation.

The positive additionally uses foreign I64 as Required; com-z4ns explicitly owns that setup separately. No broad trait redesign, compiler/test/expectation change or real execution occurs during audit. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0011.json and its independent receipt. Unread primary/control obligations remain audit work; this is not a whole-corpus handoff.
