---
id: com-tfdi
status: open
deps: []
links: []
created: 2026-10-27T22:34:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Clarify local type declarations using ambient language-item names

Source-only batch0024 audit at compiler9665094d/spec5bd65a5: exact reject/redefine_langitem.pw expects any user enum Optional to reject as reserved. Original c7fe39ad added this gate; current Verify/Decl391-429 checks nonextern entry-module struct/enum names. Adopted spec15:105 explicitly permits local shadowing of ambient language-item names and distinguishes local/use/ambient resolution; its linked spec03 shadowing section describes val/mut val. These clauses do not clearly settle whether a module-local nominal type declaration is the same allowed shadowing or a separately forbidden canonical-name replacement. Current entry-only rejection and the fixture comment are not independent normative grounds.

Bounded question: reconcile exactly module-local struct/enum declarations using a canonical ambient name with lexical value shadowing, ordinary imported same-spelled names, canonical syntax/desugaring declaration identity and entry versus other-module declarations. Recover adopted decisions from source history only where necessary. Compare the minimal Optional declaration, one local val shadow and noncanonical-name controls. Determine whether existing spec already settles rejection/acceptance or requires one explicit surface decision; do not silently reserve all names or permit redefining the canonical language-item registry.

Deliver a canonical oracle or finite unresolved source question and a concrete fixture/implementation correction owner if needed, with independent review. No all-name-lookup redesign, runtime feature implementation, compiler execution or fixture/runner repair occurs in this audit. This separate follow-up is not a child/prerequisite of com-jno0 or its audits. Unread obligations remain audit work. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0024.json and independent receipt (pending final reconciliation).


## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 50.

Row50: Spec15 local shadowing plus spec03 value shadowing does not decide this nominal case. No automatic universal reserved-name ban or new source permission; no body selection repair inferred. com-tfdi finite module nominal declaration/ambient language-item shadowing question belongs to declaration/input identity admission. Registry identity must stay distinct from lexical names and entry/other-module policy. Required admission: com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
