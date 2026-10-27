---
id: met-4slo
status: open
deps: []
links: []
created: 2026-10-27T20:37:09Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Clarify repeated memberwise factory publication in selected fixtures


## Finite Question

Source-only audit at compiler9665094d/spec5bd65a5 found two repeated bare publication markers, not two custom factory bodies: tests/fixtures/part/crossmut/State.pw for Counter, and tests/fixtures/part/importalias/src/Models/User.pw for User. Each has `pub impl Type { factory }` plus another public impl containing bare `factory`. Spec05 describes the marker as exposing the already synthesized memberwise factory, but does not explicitly settle repeated exposure. Do not classify it as an ordinary duplicate free function from current parser behavior.

## Deliverables and Scope

Recover the original public-factory migration intent (2aee8ff4 added standalone markers while existing ones remained); trace publication metadata to candidate identity and visibility, and find whether a prior adopted rule already settles idempotence or rejection. If no canonical decision exists, present these two minimal forms for user surface judgment before changing acceptance. Check single marker, repeated marker, custom-body duplicate and memberwise/custom overload contrast. Preserve cross-module inout mutation, associated construction and imported nominal alias controls.

com-owb3 owns generic impl binder shapes, not these nongeneric repeated markers. No all-factory migration, parser repair or fixture change is part of this audit investigation. Unread source-admission units remain in com-e713.

## Completion

Finite source-admission disposition with canonical grounds or explicit unresolved decision and owned correction. No test repair or source rule is adopted by the audit; subsequent repairs require TDD and scoped review. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-part-0003.json and prior part-batch-0085.json.

## Explicit Newtype Factory-Inheritance Control

Batch0021 adds exactly run/newtype_factory_inherit.pw/.out: two pub impl Rgb blocks both contain bare factory publication markers. Preserve five memberwise/named/fallible inherited-factory outputs and Self re-tagging while resolving the same repeated-publication question. The control is qualified, not evidence of adopted idempotence or a primary source-admission completion. No new generic-publication scope is transferred here.
