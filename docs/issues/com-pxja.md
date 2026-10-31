---
id: com-pxja
status: open
deps: []
links: []
created: 2026-10-27T19:59:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Clarify constructor sibling inference under forward type resolution

## Finite Question and Original Intent

Source-only test audit at compiler9665094d/spec5bd65a5. `tests/fixtures/run/aggregate_infer_recorded_fields.pw` uses `<Measurement low=0 high=values.count() />` and reversed attribute order. Golden0/3/1/3 is arithmetically correct if admitted. spec02:47 resolves types forward from already available information; body-checking permits provisional inference but does not expressly establish this later-sibling rule. Do not label either backward inference or rejection as adopted merely from current source success.

Original f752b89f91341fe1511b561100005657b293441f added exactly this positive and `tests/fixtures/reject/aggregate_infer_literal_range.pw` with low256 preceding high=limit()->U8, plus a range-error companion. Both intentionally use all recorded field terms, so a future migration must preserve legitimate field mapping/range coverage without treating a different type mismatch as the same rejection. The original commit predates the current explicit forward-resolution contract.

## Deliverable and Guarantees

Derive whether a selected constructor signature may defer an earlier unresolved literal while collecting later sibling argument types. Distinguish available expected type/explicit Measurement[U64], later concrete count input, and ambiguous overload rescue. Determine same rule for ordinary calls and factory attributes; do not invent a block- or constructor-only exception. If current spec/design do not decide this source acceptance, obtain user judgment before changing it. Preserve source-order evaluation and one-time effects regardless of typing strategy.

Exact positive and paired rejection above only; bare generic-owner factory shorthand is separately com-owb3 and must not obscure the inference question. Produce agreed positive/reject scenarios and finite repair ownership, then TDD/independent review for actual implementation. Evidence: meta/evidence/test-audit/scoped-reviews/run-head-0087.json. No source/test edits or actual compiler execution occurred in audit; other source-admission units remain audit work.


## Explicit Ordinary Call Later-Sibling Empty Array Context

Batch0049 adds exactly run/generic_empty_array_arg.pw/.out to the existing same-rule ordinary-call/factory-attribute question. Original515a625f intentionally lets later seed determine an earlier xs:[] T. Forward available expectations and provisional body terms do not by themselves establish this acceptance. Derive or request the canonical same-call inference rule; preserve source-order evaluation and no overload rescue. Bare loop and nonunique float contexts remain separate exact owners; suffixing seed does not discharge this question.

## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 25.

Row25: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Constructor sibling inference needs finite canonical forward-resolution oracle reconciliation before current type acceptance/control changes. No new backward inference or expectation rule is adopted by assignment. Required admission: met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
