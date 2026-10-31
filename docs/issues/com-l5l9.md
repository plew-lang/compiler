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

## Named Destructure Binding Drop Order

Batch0094 adds exactly run/destructure_two_arc.pw/.out. Independent Cell roots become named x=1,y=2 then p=3,q=4. Spec03:114 ends hidden non-call record temporary holding at full-statement end;120 named locals then drop in reverse declaration order. The resulting q,p,y,x tail is4,3,2,1, while the current golden pins3,4,1,2. Original8ff2a2e expressly retained hidden __dtN record owners until scope and pinned grouped field order; that historical implementation does not override the adopted owner boundary. This is a source-backed oracle mismatch, not a fresh executed compiler failure.

Reconcile this exact named-field case alongside the original discarded-field case, tracing temporary creation, field copies/ownership transfer, aliases and cleanup to the final observer. Preserve two independent destructures, explicit renames/temp hygiene and exactly-once cleanup; do not fix only stdout or introduce a record-specific lifetime exception. Single-cell destructure_ref_bind_arc, independently retained destructure_assign_mixed and Dictionary unspecified current-layout order must not be mechanically reversed. Existing source ref/deinit migration stays separate and no audit-time fixture/expectation/compiler repair was made.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 65.

Row65: Keep String binding independent from discarded Cell; named4,3,2,1 versus historical3,4,1,2 and exactly-once aliases/renames. No stdout-only fix, record-specific exception, Dictionary mechanical reversal or optional com-zowv prerequisite. com-l5l9 reconciles initializer/projection/discard owner facts with full-statement temporary release and reverse named-local drop through actual common Mid cleanup/final observer. Historical hidden __dtN scope owners conflict with adopted boundaries; this is required current ownership evidence. Required admission: met-acfl, com-an0b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
