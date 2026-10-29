---
id: com-8b4d
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:56:18Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Keep mutable executable compilation state private to its owner

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/session-and-preparation-boundaries.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-session-and-preparation-boundaries.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Make external mutable compiler access unavailable while retaining exact compiler/prepared ownership. Supply owner-controlled lowering and diagnostic/trace fronts; the same internal inout Comp may be forwarded to existing backend services, preserving their interner/cache effects. Do not return a wrapper exposing full mutable Comp.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- checked-program-and-executable-owner-result-construction: ExecutableCompilation.compiler public mutable escape only; private pair ownership, readonly prepared and private CheckedProgram/result enums preserved

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Backend service decomposition, proof representation, source semantics, native ownership or runtime behavior changes.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

