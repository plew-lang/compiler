---
id: com-zgk9
status: open
deps: [com-4vr8, com-9hyu, com-j0a9, met-k62r]
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime, verification]
---
# Audit collection place and reentrant ownership coverage

Retained uninspected boundaries: place reads; Buffer and Dictionary/Set reentrant commit order; iteration-value ownership; inout calls through pub(get) arrays. Design: [collection and Buffer contracts](../design/collections-and-buffer.md), [ownership](../design/ownership-and-access.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Check minimal executable/reject cases against current specification, preserve independent owners and commit-before-user-code safety, and distinguish current evidence from whole-API/combination coverage.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Current Buffer/Array/Dictionary/Set operations, CoW/iteration ownership, nested inout and callback/deinit reentry. Trace commit-before-user-code, retired ranges and multi-buffer updates; test mutation/final-release/alias controls. Capacity failure is independently com-p10m; no new collection APIs.

## Test Admission Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) installs required finite repair/investigation prerequisites at this actual admission: com-9hyu (row21), com-4vr8 (row27), com-j0a9 (row29). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.

## Test Admission Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) installs required finite repair/investigation prerequisites at this actual admission: met-k62r (row87). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
