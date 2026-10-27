---
id: com-vp0o
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Reconcile five existential success fixtures with adopted erasure rules

## Boundary

Finite follow-up from com-8iys/com-e713 test audit; independent of audit completion and phase3. Audit makes no test/compiler repair and claims no fresh candidate execution. Source baseline9665094d, spec5bd65a5. Evidence: meta/evidence/test-audit/scoped-reviews/run-head-0087.json.

Exact run fixtures: any_array_covariant_erasure, any_array_self_member_return, any_direct_optional_match, any_heap_self_member_return, any_array_unique_concrete. spec06 generic invariance and spec08 existential copy classification/results disallow whole generic-container covariance, nominal Self-result re-erasure, and injecting unique Self into ordinary copyable any P respectively. Historical numeric outputs are internally consistent under old acceptance; changing numbers is not the remedy.

## Guarantees and Original Intent

Recover initial commits3c5d8254,40c2619b,2be38c92,9f074d9e,2f8dcebb and preserve useful direct boxing, heterogeneous dispatch, heap ownership, source independence and direct/typed match controls in admitted shapes. Add discriminating rejection controls for the now-forbidden forms. Source-admission rules must survive to actual conversion/Mid consumers; no test-name special cases or retained old successful bypass.

unique existential support is met-b2la, ordinary deinit placement met-2t3l; do not require implementing that whole future family just to stop asserting an invalid copyable box. Do not delete independent ARC/heap controls without a replacement. Related ordinary fixture reports remain separately audited.

## Completion

Contract-derived case map, fixed-candidate RED for the targeted admission mismatch, fresh relevant positive/reject checks and structural conversion evidence; scoped independent review. No whole type-checker rewrite, new covariance semantics, whole suite cleanup or audit-domain closure.

