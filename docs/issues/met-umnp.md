---
id: met-umnp
status: open
deps: []
links: []
created: 2026-10-27T21:20:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Fix labeled-callback setup in two contextual block controls


## Finite Control Setup

Source-only supplemental control review during batch0010 at compiler9665094d/spec5bd65a5 reads exactly tests/fixtures/run/standalone_block_context.pw and .out. It intends contextual block/leading-dot construction through annotated/nested/return/argument/enum/closure/array/generic positions. Its callback is declared fn(point:Point)->I64 but called callback({ ... }) without the point label. Spec04 requires function-value labels too; lack of label is not repaired by propagating a Point context.

## Guarantees and Completion

Recover the original context-propagation test and retain all seven outputs/scenarios under a correctly labeled call, plus the existing unlabeled/wrong-label rejection contrasts. Do not weaken function-value label admission or remove the useful closure/block context. Check other root setup before treating this as an adopted positive. If current compiler accepts the invalid call, assign actual admission repair to its responsible existing source-boundary work; do not silently reopen or expand phase-three implementation while fixing this fixture.

Audit does not modify or execute this test. This exact control finding is separate from its still-unread primary audit obligations, which remain in the plan. Later test/compiler repairs require TDD and independent review. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0010.json and review-frontend-batch-0010.json.

## Explicit Second Contextual-If Control

Batch0012 adds exactly run/contextual_construction_if.pw and .out. Its closure fn(point:Point) is called as closure(if ...), missing required point:. Path-fixed introducing e36371c2 contains the same setup, so this is not a recently lost label. Preserve all seven outputs and contextual return/annotated/free/method/closure/interpolation/assignment positions under a correctly labeled call, with missing/wrong-label rejection contrasts. This supplements the original standalone_block_context pair and does not count either unread primary admission/outcome as audited.
