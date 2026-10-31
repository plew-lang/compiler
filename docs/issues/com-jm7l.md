---
id: com-jm7l
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:03:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source access and aggregate fact storage inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-expression-and-recording-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-expression-and-recording-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Open-owner aggregate/try/match values and maps; access candidate navigation and selected use rows/owner-key checks, no setter/member reselection. Replace real full Comp grants at all actual named API callers with the closed domain reader/writer proposed per row. Keep coherent stores/topology together and retain all legitimate side effects, identity/lifetime/default/error/invariant behavior.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-building-source-aggregate-try-match-row-publication: ['putSemanticAggregate', 'putSemanticTry', 'putSemanticMatch']
- codegen-source-index-access-candidate-navigation: ['accessCandidateIndex']
- codegen-source-selected-access-use-provenance-publication: ['recordAccessUse']

## Actions and Completion
Change the actual APIs and every actual source/fixture consumer to the named closed services. Remove competing broad grants and raw Comp/unwrap/callback escapes. Preserve all listed direct/delegated effects, source/session/owner identity, ordering/defaults and error/restore/lifetime behavior with task-start TDD/refactor controls and independent structural review; run appropriate repair validation. A new interface proposal alone is not repair completion.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other API components/domains, passive record field decomposition, language acceptance/algorithm/performance/ABI changes or whole compiler correctness/GREEN. No product repair/execution occurs within the originating audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-7kzd](com-7kzd.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-recording.json) retains all main/mixed roles and normative grounds. Building aggregate/Try/match and selected access-use rows publish source-chosen identity and owner-local provenance. Keep candidate navigation distinct from selection and prohibit setter/member reselection or post-success writer access.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
