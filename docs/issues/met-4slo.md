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

## Explicit Shared-Pointee From-Place Publication Markers

Batch0067 adds exactly run/ref_pointee_from_place_arc.pw/.out: repeated pub impl Holder {factory} markers, not duplicate custom bodies. Preserve shared copyable Holder/inner-cell ownership and made/31/done sequence through existing canonical publication question; no idempotence decision made.

## Explicit Returned Shared Holder Publication Markers

Batch0068 adds exactly run/return_owned_local_move_arc.pw/.out: two bare public Holder factory publication markers. Actual2aee8ff4 added standalone marker while original e5c30d0b existing marker remained. Same finite publication-idempotence question, not two custom callable bodies or automatic source ban. Preserve bound/21 shared owner return and caller lifetime purpose.

## Explicit Nested Place Store Repeated Publication Marker

Batch0072 adds exactly run/store_to_place_arc.pw/.out. Original5406437d has one Slot bare factory marker;2aee8ff4 adds a standalone marker leaving the first. Apply the existing finite canonical idempotence/publication question, not duplicate custom-function-body error. Preserve enum reassignment/nested Array reference displacement and cleanup11/12/13 order; no immediate removal chosen during audit.
