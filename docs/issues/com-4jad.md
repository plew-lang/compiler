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

