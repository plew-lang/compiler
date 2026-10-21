---
id: com-7g6i
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime]
---
# Investigate stack use when destroying deep owned value trees

Deep recursive owned-value destruction has an unmeasured stack-use boundary. This differs from shared-reference cycle reporting/reclamation in com-2z5l. Design: [runtime](../design/runtime.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Retained Lifecycle Prerequisite

Spec03 at spec revision `a6f2384` retained an older implementation note claiming recursive field heap-cell ARC release was not wired, with a dead link to claude/provisional.md. The specification synchronization removed that implementation-status statement from the language contract, not the underlying audit obligation. Its claim has not been reverified against the current compiler. Check recursive-box copy/drop/release wiring before interpreting depth/stack measurements; missing destruction would not demonstrate bounded stack use. This records a potentially related unverified lifecycle gap, not evidence of a newly reproduced leak or permission to omit normal destruction.

## Acceptance Criteria

Measure representative depth and destruction order, identify any actual resource limitation, and document or implement a semantics-preserving remedy without asserting an unmeasured stack defect.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

First verify current recursive-box copy/drop/release and destruction order; then measure a small finite depth series for owned trees. Missing lifecycle is an in-scope repair. Constant-stack arbitrary-depth destruction is not a new promised feature, and a measured resource limit alone is not a demonstrated memory-safety bug.
