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

## Placement decision

Spec/15's standard-library ownership section assigns `Hash` and `Hasher` to
`@Std/Hash`, and specifies that Hash depends on Core. Core must be able to name
these traits to own its conformances. Importing the public Hash module in Core
would close a cycle, while exporting the traits from Core would change Core's
surface.

Preferred decision: put the two protocol declarations in a lower-level source
module, import them privately in Core, and re-export them from `@Std/Hash`.
Keep `SipHasher` in `@Std/Hash`; keep all ten Core-owned witnesses with Core.
The lower-level module requires the ambient scalar `U64` in a signature, so
verify that the existing fixed language-item registration handles this without
an explicit back-edge. Confirm the canonical ownership change in spec/15 and
review whether direct imports from the new module expose a new supported path.

Fixed-point carrier `110e1fc7`, SHA-256
`a959c1b668883a9aee60e9a94c9d1a24ff38115d43c3bb88f2101f95f18f70e9`:
`--check` accepts an explicitly imported `@Std/Hash` bound called with I64,
and rejects the same input with `@Std/Core` as an unexported import.
`hash_siphasher.pw` and `dict_bool_key.pw` both pass `--check`.
