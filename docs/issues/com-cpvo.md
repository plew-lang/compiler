---
id: com-cpvo
status: open
deps: []
links: []
created: 2026-11-15T21:43:51Z
type: task
priority: 1
assignee: Koji Murata
parent: com-wka4
tags: [std, frontend]
---
# Place standard Hash conformances with their declared subjects


## Contract and evidence

Spec/07 and spec/15 require the subject's defining module for a bare impl.
`std/Hash.pw` currently declares ten bare Hash conformances for Core-owned
subjects (eight integers, Bool and String). The Hash module also depends on
Core for `bitCastU64`; naively transferring just the impls and importing Hash
back into Core would introduce a use cycle.

## Guarantees and completion

- Inventory all std bare impl owners, including generated parts; reproduce the
  relevant placements using the fixed carrier and note any independent gaps.
- Establish an acyclic placement that lets Core own the affected conformances.
  Preserve public `@Std/Hash` use, explicit Hash name visibility, ordinary
  selection of standard witnesses, derive, and Dictionary/Set behavior.
- Cover fixed-carrier behavior of explicit Hash imports and standard witness
  selection before moving declarations; verify the same behavior after the move
  in affected check/build/run and generation gates. Confirm the owner-module
  placement structurally and obtain independent review before closure.
- No std exemption from ownership admission or change to the user-facing API.
  If the existing public surface cannot be preserved, obtain a design decision
  before changing it. Universal header admission remains with com-wka4.
