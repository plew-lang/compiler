---
id: com-l5l9
status: open
deps: []
links: []
created: 2026-10-28T01:54:54Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, verification]
---
# Reconcile discarded record-field temporary lifetime oracle


## Finite Source-Oracle Boundary

Batch0066 source-admission audit at compiler9665094d/spec5bd65a5 reads exactly
run/record_destructure_discard.pw/.out. The initial record expression has a
String field bound to name and an unrelated sole MutableRef[Cell] field n
matched by _. Comment and golden retain a hidden destructure owner until scope
exit (7 after end). Spec03:114 ends non-call temporary holding at full-statement
end, and271 describes _ as discarding. The String binding does not retain the
Cell. Independent actual origin8978934c explicitly intended the older hidden
scope-owner lifetime; original intent alone does not override the adopted rule.

## Deliverable and Guarantees

Reconcile this exact destructor-timing oracle with canonical temporary/binding
ownership and preserve label-completeness, discard without creating local,
String binding and loop-pattern coverage. Contrast an unretained field with a
named or independently aliased shared owner, and keep statement-end versus
ordinary named-binding scope lifetime distinct. Follow original owner creation,
projection, discarded component and cleanup edge; do not fix only stdout or add a
record-specific lifetime exception. If canonical evidence remains insufficient,
obtain a focused semantic ruling before repair.

Current struct-body deinit/reference API migrations remain met-2t3l/met-op15;
resolving those does not settle this separate lifetime oracle. General optional
CFG propagation com-zowv is not a prerequisite. No corpus-wide lifetime rewrite,
unread outcome transfer or new language decision belongs here. Audit credit is
source-admission only; no executed failure or compiler bug is claimed. Repair
requires meaningful RED/GREEN and scoped independent review, outside the audit.

Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0066.json and
its independent receipt. No compiler/std/test/golden/runner changes or real
compiler/native/ASan execution during the audit.
