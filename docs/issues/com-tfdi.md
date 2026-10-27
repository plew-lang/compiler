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

