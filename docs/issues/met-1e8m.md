---
id: met-1e8m
status: open
deps: []
links: []
created: 2026-10-27T21:17:01Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Clarify result-carrier inference for the selected non-generic Chain negative


## Finite Source-Rule Question

Source-only batch0010 audit at compiler9665094d/spec5bd65a5: tests/fixtures/reject/chain_value_type_mismatch.pw assumes a non-generic Maybe:Chain with Value=Box must reconstruct Maybe after projecting Box.n:I64, so fromValue(Box) rejects. This is a current implementation-lane assumption, not yet a derived normative output-carrier rule. Spec12 describes a result O:Chain and its fromValue/empty expansion but does not explicitly select O from R when no incoming result context exists. Current Core509-510 says receiver constructor reapplied to member type. Design's retained carrier identity/source result boundary does not by itself define that source inference rule.

## Deliverables and Completion

Recover any prior adopted decision and compare exactly this nongeneric case with known generic Optional/custom-Chain and multi-parameter nominal/binder-position controls (including part/namespace_chain_identity). Explain the no-context result, any effect of explicit incoming result-carrier context, same-Value versus changed-Value continuation, and short-circuit behavior. If canonical decisions already settle O, record their grounds; otherwise seek user surface judgment before changing source acceptance or assigning a normative error reason. Do not infer language meaning from the current chainStageResultRef implementation alone.

A finite canonical disposition and concrete owned correction close this investigation. com-i62n's closed producer-to-reader/complete-carrier repair remains valid in its exact scope and is not reopened; it preserved an existing result path, not this missing public inference choice. com-ntm8 owns the selected test's actual diagnostic/source-anchor and missing bare Chain binding; met-2wca owns Some label setup. Fixing those setups does not independently decide O. Audit executes/changes no compiler, source or expectations and does not implement broader Chain/unique/generic features. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0010.json.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 38.

Row38: Do not reopen closed com-i62n carrier implementation; no arbitrary Optional fallback. No-context/context/same-vs-changed Value/short-circuit contrasts and independent setup owners survive. met-1e8m must recover O:Chain result-carrier inference for nongeneric Maybe/ValueBox and its selected fromValue/empty calls before chain result recipe/type and protocol-call admission. Retaining a carrier internally does not decide public no-context O inference. Required admission: met-6e6k, met-ucze.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
