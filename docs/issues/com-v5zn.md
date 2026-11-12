---
id: com-v5zn
status: in_progress
deps: []
links: []
created: 2026-11-12T09:35:59Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Compare short-projection types by original declarations

## Guarantee and Finite Work

Use the admitted declaration identity when comparing source type terms during
short-projection selection, including before the late nominal-resolution pass.
Both prepared clause receiver matching and complete trait instance deduplication
must compare original nominal declarations, lexical ParamIds and structural
children. A qualified use and a selective alias of the same declaration are
equal. Identical spellings from different modules are distinct. Use the
admitted module table and shared semantic type traversal.

Evidence and original inputs are in [com-erlx](com-erlx.md#checkpoint-exact-identity-at-short-projection-selection).
This issue owns the shared comparison and its short-projection consumers.
Original owner lifecycle, pending-clause preparation and failed-prefix
publication remain with com-erlx. Remaining view admission and evidence
transport remain with com-3jtd. Preserve existing specifications.

## Required Scenarios

- The prepared receiver matches its original nominal declaration, including
  a qualified use and an alias. It rejects an identically named declaration
  from another module.
- Two trait instances whose positional arguments contain different nominal
  declarations remain ambiguous. Two aliases of the same complete instance
  collapse to one candidate. Preserve nested argument and binder identity.
- Preserve later-clause/nonmember/legacy and associated-type controls where
  the old carrier supports them. The pending qualified subject case remains
  in com-erlx and is not certified by the ready-clause fixtures.

## Completion

Record RED on the pre-fix candidate with exact rejection reasons or observed
false acceptance. Execute the new fixtures through the compiler and existing
controls, follow [TDD and independent review](../../../agents/development-workflow.md#独立レビューと完了認定),
check the performance baseline, and record the exact candidate and remaining
scope. The product path must consume the shared comparison in both places.
