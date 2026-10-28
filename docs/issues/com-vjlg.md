---
id: com-vjlg
status: open
deps: []
links: []
created: 2026-10-28T01:10:20Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Reconcile copyable consuming-match source controls

## Finite Source-Oracle Question

Audit batch0057 reads exactly `tests/fixtures/run/mid_enum_destructure_runtime.pw`
and `.out`, without executing them. The unique Chain half tests declaration-order
discard/recursive cleanup; the copyable Tree half explicitly uses `match move
tree` while retaining another logical alias. Both are meaningful original
regression purposes, but current acceptance alone does not establish source
permission for the latter spelling.

Spec03's access-mode section rejects explicit borrow/move on copyable types and
introduces that rule through parameters, receivers and calls. Spec11 separately
defines consuming match and explicitly requires move for unique storage, without
an explicit copyable-match ruling. Its actual introducing/change diffs
`30dee3d66bfa81ace77016b292c8485384919fa5` and
`c8be4b29b0585e92aefb1e3e7a1ab6424ff4a453` were read; neither explicitly settles
this relation. `reject/copyable_move.pw` checks a move parameter declaration, not
this consuming-match shape. This is a bounded canonical-contract question, not
permission to introduce a copyable move exception or a confirmed compiler bug.

## Deliverables and Limits

Recover any decisive existing decision, reconcile the two canonical scopes, and
identify the valid source/internal test lane for the copyable recursive-cell
alias regression. If existing decisions do not settle it, ask for the focused
surface judgment before changing spec, compiler or expectations. Preserve the
unique Chain commit/drop order and the Tree alias/value results; do not discard
either purpose or redesign recursive representation. Include the exact normal
and rejection contrasts required by the settled rule, without auditing all
ownership features anew.

Evidence and independent receipt: meta `evidence/test-audit/scoped-reviews/`
`frontend-batch-0057.json` and `review-frontend-batch-0057.json`. No execution,
repair, performance or phase-three certification is claimed. This follow-up is
not a dependency of the audit; unread obligations remain with their audit owners.

