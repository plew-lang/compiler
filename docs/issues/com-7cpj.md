---
id: com-7cpj
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:53Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source call-storage summary finalization inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-owner-and-preparation-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-owner-and-preparation-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Three finalization APIs in Preparation.pw only; retain selected source call identity, owner-relative frontier/cursor read context, syntax storage shape query, conservative true and bounded row writer. Do not change call selection or summary algorithm.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-call-storage-summary-finalization: finalizeSourceCallStorage/finalizeLexicalCallStorage/finalizeGlobalCallStorage

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/algorithm/ABI/runtime changes, full compiler redesign, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-vr57](com-vr57.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-frontend-services.json) retains all main/mixed roles and normative grounds. Current source lexical/global call-storage summaries finalize already selected calls in owner-relative frames with bounded row writes. Source publication, not a second call-selection algorithm, owns this fact. Its selected CallTemplate storage-summary writer also belongs to selection-area publication/write-authority closure.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
