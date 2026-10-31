---
id: com-fkzm
status: open
deps: []
links: []
created: 2026-10-27T18:38:52Z
type: chore
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Correct returning-diagnostic probe execution instructions

Correct the contradictory manual procedure for TemplateDependencyUnfinalized without changing its intended returning-diagnostic contract.

Audit evidence: tests/compiler/frontend/README.md says exit 0 plus the .out marker near line 22 but exit 1 near line 42. The fixture handles Result.Err, calls returning Diag.emitDiagnostic, then prints returned. src/Diag.pw emitDiagnostic reports without exit; terminal compileErrorAt adapters call exit separately. The .out contains returned. Source inspected at compiler 7f64172e (production unchanged from 9665094d); no fresh execution claimed.

Guarantee: the documented manual command verifies successful harness compile/link, normal probe exit, expected stderr diagnostic and stdout marker, distinguishing an executed failure from setup error. Confirm original intent from history before editing. Preserve TypeTermPublication and other manual procedures. Correct inaccurate status/marker instructions; add no public API or compiler special case.

Excluded: compiler semantic changes, suite registration, test corpus repair, new features. If a fresh probe contradicts the source contract, report it as a separate compiler investigation rather than changing expectations.

Acceptance: independently review the intended contract and final procedure, verify all related references/companions, and collect suitable scoped execution evidence if practical under standard monitored execution. Do not claim full-suite or audit completion. This repair is independent of the audit closure and is not an audit dependency.

Found by com-ouh2; evidence/test-audit/README.md retains source-discovery limits.


## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 77.

Row77: Manual frontend diagnostic, not standard discovered gate. No suite registration, semantics/com-bfvd expansion or G2/standard-ASan prerequisite. Returning TemplateDependencyUnfinalized emits diagnostic, continues to returned stdout and normal exit; exact manual README exit0/exit1 contradiction and setup/execution separation need correction. Required admission: com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
