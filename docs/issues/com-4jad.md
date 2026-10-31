---
id: com-4jad
status: open
deps: []
links: []
created: 2026-10-27T23:38:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Cover successful owner closure without global publication

Static audit batch0039 found a finite missing positive boundary in tests/fixtures/run/call_closure_owner_boundary.pw. Existing invalid-owner rejection and empty-program closure correctly detect original9634f6cf, but successful individual closure must publish only that owner, leaving globalCallTemplatesClosed false until explicit program closure. Inspected call_template_seal, call_template_result_arguments, frontend_body_demand and lexical_body_requests do not assert that sequence. Add a valid declared owner, successful individual close, local closed=true/global=false, then explicit program close/global=true control while preserving original failure checks. Recover original purpose and use existing public frontend/registration APIs; no blanket mutation framework, new source semantics, whole-pipeline certification or claim of a compiler defect. Contract: docs/design/frontend-handoffs.md source owner publication and Codegen/Resolve/Expr.pw closeCallTemplatesForBody/closeProgramCallTemplates. Deliver meaningful pre-fix detection against a focused counterfactual, production-path success and independent review. Audit itself does not edit tests or execute compiler.


## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 55.

Row55: Preserve invalid-owner9634f6cf, valid individual success/localclosed/globalfalse then explicit program closure/globaltrue. No product defect or blanket mutation framework is claimed. com-4jad must distinguish one valid successful source owner/local closure from whole-program closure. This detector is required before relying on source-owner and selected-call publication admission. Required admission: met-acfl, met-ucze.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
