---
id: com-qt11
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:28:42Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, diagnostics, verification]
---
# Narrow syntax parser and part-admission service inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/package-host-and-context.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-package-host-and-context.json), audited source 9665094dcec8aa63ed20573b1306a0015058f595. Parent: [com-mmk9](com-mmk9.md). This finite repair owner is independent of com-jno0/phase 3; creating it does not complete the repair.

## Guarantee and Scope
Narrow parseFileSyntax, checkPartSyntaxOnly, rejectNonImplSyntaxItem and partItemDiagnostic. Parsing needs mutable SyntaxFile plus fixed source bytes/base; structural part admission needs immutable syntax/root/item navigation. Supply only limited source path/range/bytes diagnostic provenance, without retaining whole mutable Comp behind a view or callback. Remove unrelated declaration/type/proof, Mid, cursor, Mono and source-admission authority.

## Actions and Completion
Characterize normal root parsing, impl-only part rejection, recursive Published items and parse failures that retain an appended syntax prefix. Preserve base offsets, original path/line/message, error prefix and Result propagation; retained syntax must not imply success. Narrow actual signatures and update real consumers, removing broad alternatives. Apply task-start TDD/refactor rules and independent review, including source checks that no full Comp survives indirectly; run gates appropriate to the future change.

## Excluded
Changes to language visibility/use/part/macro semantics, source acquisition, parser algorithms and unrelated compiler refactoring. No compiler execution, repair or performance improvement was performed by this audit.


## Adopted Implementation Intake

[com-k35g](com-k35g.md) classifies this exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-604k; actual tk prerequisites retain the open repair.

[Scoped intake outcome](../../../evidence/existing-feature-conformance/audit-intake/api-session-and-inputs.json) preserves every main/mixed role and the normative reason. Existing parser and structural impl-only part admission need mutable syntax construction or readonly graph/source provenance, not semantic/Mid/native authority. No grammar, visibility, use or macro change.

The original audit-time independence does not waive this implementation admission. Keep the original finite guarantee, caller/delegate/control and excluded optional scopes. This is assignment only, not product repair/GREEN.
