---
id: met-ukm5
status: open
deps: []
links: []
created: 2026-10-21T11:40:54Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Re-review compiler architecture against the adopted language specification

## Review Input and Scope

User-requested renewed review of the architecture itself, before a detailed
implementation/design conformance audit. Input: compiler design
`1d83231ed5a282f69bcd1579875d62d8eb940fa1`, language specification
`16f2f13970dbe2789214b2206c48af3df21b68c8`. Implementation, current support and
performance are excluded as evidence of the design's correctness.

Three independent reviewers cover (1) source semantics/types/generics/storage,
(2) Mid/ownership/ABI/runtime/lazy execution, and (3) architecture/input/tooling/
maintenance. Each compares the assigned documents against relevant complete
specification topics and current primary reference-language documents. The parent
checks cross-domain cases and challenges candidate findings before saving results.

Review standards:
- Preserve Plew's specified meaning; do not substitute another language's rules.
- Identify one decision owner, explicit inputs/output guarantees, remaining
  legitimate decisions and final consumers, including failure/cleanup/cycles.
- Show concrete contradictions or missing handoffs rather than asking for detail
  or another general framework by default.
- Test whether a small new change can be located and finished from the reference.
- Consider runtime/compile costs and individual LLM-project maintenance; distinguish
  genuine design changes, existing accepted boundaries and optional elaboration.
- Record coverage/limits and accepted/rejected findings. Prior chapter approval or
  met-ukm5 completion does not certify implementation or first-edition acceptance.

## Findings

Review in progress. No specification/design change is adopted by this record.
