---
id: met-m7wx
status: open
deps: []
links: []
created: 2026-10-21T11:49:55Z
type: chore
priority: 3
assignee: Koji Murata
tags: [design, documentation]
---
# Improve canonical contract navigation and remove stale descriptions

## Scope

Editorial improvements from the design-only [met-ukm5](met-ukm5.md) review,
design `1d83231e` and spec `16f2f139`. These are not new source semantics or
evidence of a compiler defect.

- Frontend Handoffs retains stable contracts beside legacy row/count sentinels,
  concrete migration mapping and stale "reconciliation pending" prose. Preserve
  necessary invariants and rationale, but move changeable migration/current-state
  details to their owning issues and link them. Checked-body Storage remains the
  physical storage authority; do not create another status ledger.
- Link Syntax's string-literal handoff directly to the common decoder contract.
  Make lexical validity/selected value versus later physical representation easy
  to locate. Existing contracts already prohibit LLVM-only semantic validation;
  no new decoder framework or authority is needed.
- Spec15's opaque-handle paragraph still describes generated C/header typedefs,
  while its FFI section adopts Plew-owned declarations lowered through LLVM.
  Correct that mechanism-only wording, preserving one-word ABI, distinct nominal
  handles and the user's responsibility for foreign ABI/lifetime correctness.

Completion: one home for each current contract/status, working local links and
no changed acceptance or runtime guarantee. Keep prior decisions and migration
evidence reachable through issues/Git rather than deleting necessary information.
