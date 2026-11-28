---
id: met-5e48
status: in_progress
deps: []
links: []
created: 2026-11-28T15:39:46Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [mid, performance]
---
# Measure and eliminate repeated draft statement prefix copies


## Guarantee and sequence

Measure midAppendStatement's draft mutation protocol before repair. Current code retains a MidBlock, copies its statements Array, appends while the old array remains held, then replaces the block. Post-Array native assembly gf7393 retains the old statement buffer before Array.append and drops the retained old MidBlock afterwards. MidBlock destructor pwdrop894 is present in the sampled Mid-building window. Confirm physical CoW copy count/elements/bytes with a private scoped runtime probe; do not infer time from O0 counts.

If confirmed, append through the existing draft place rather than retaining/replacing its whole prefix. Preserve out-of-range no-op, closed-block no-op, statement order and payload, terminator identity, other blocks, and external CoW snapshots. No change to canonical storage, ownership semantics, Array runtime/LLVM product code, checks or source admission. Behavior-fixed before/after controls must explicitly retain outer and inner snapshots. Enumerate actual helper callers; verify targeted statement/CFG controls and same-source LLVM/time. Independent boundary/source/test/performance review, final related whole gate shared with pending performance changes. Do not close stage3/parent/whole gate from this finite repair.

Design: mid.md Draft Construction permits owned temporary arrays; it does not require repeated prefix replacement. Excludes pooled canonical transforms, branch algorithms, deinit timing changes and generic Array/ARC redesign.
