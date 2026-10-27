---
id: com-7u8z
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Resolve selected package fixture manifest admission against the canonical schema

## Finite Question

Source-only test audit at9665094d/spec5bd65a5, not a fresh execution. Selected part projects namespace-related batch0086 and tail0087 include twelve manifests: nsimport, ownershipalias, pathdep plus greet, publicapi_namespace, publicapiclosure_external_dep plus dep, publicnewtype, rootimport, transdep plus mid and leaf. The exact twelve paths are listed below.

Spec17 minimum example and several headings use [dependencies], while the detailed dependency section requires a dependencies array. Selected fixtures omit plew version and path dependencies use old name-keyed tables. Correct program arithmetic does not certify current manifest admission. Do not silently choose a new schema or invalidate existing path-resolution controls during audit.

## Deliverables

Recover original manifest intent and adopted schema decision, reconcile the canonical contradiction or obtain user surface judgment when no decision exists. Inventory exact selected manifest paths and required fields, distinguish metadata syntax from source graph/package-root/transitive binding behavior. Define valid positive and bad-schema/missing-version controls under an explicitly chosen supported version. Preserve each current path/outcome scenario through migration; do not merely update golden outputs or use current parser as oracle.

com-9ttw owns dependency graph/constraint resolution, not this schema decision; link actual prerequisites only if proved. Evidence: meta/evidence/test-audit/scoped-reviews/part-batch-0086.json and part-tail-0087.json.

## Completion

A bounded schema/admission disposition and owned concrete repair work; actual repairs use TDD and scoped independent review. No network dependency, native package executor or all-5790-file migration is included. Unread manifest/source-admission obligations are not transferred from the audit by this finding.


## Exact Manifest Inputs

- `tests/fixtures/part/nsimport/Plew.toml`
- `tests/fixtures/part/ownershipalias/Plew.toml`
- `tests/fixtures/part/pathdep/Plew.toml`
- `tests/fixtures/part/pathdep/greet/Plew.toml`
- `tests/fixtures/part/publicapi_namespace/Plew.toml`
- `tests/fixtures/part/publicapiclosure_external_dep/Plew.toml`
- `tests/fixtures/part/publicapiclosure_external_dep/dep/Plew.toml`
- `tests/fixtures/part/publicnewtype/Plew.toml`
- `tests/fixtures/part/rootimport/Plew.toml`
- `tests/fixtures/part/transdep/Plew.toml`
- `tests/fixtures/part/transdep/leaf/Plew.toml`
- `tests/fixtures/part/transdep/mid/Plew.toml`
