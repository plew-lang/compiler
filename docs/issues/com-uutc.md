---
id: com-uutc
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Audit retained frontend acceptance combinations

This is the checklist specifically retained from provisional notes, to be integrated with the broader type-checking remediation issue when created; it does not authorize restarting the paused implementation. Design: [body checking](../design/body-checking.md), [types](../design/types-and-evidence.md), [generics](../design/generics.md), [lookup](../design/name-lookup.md).

- Nested generic argument inference; explicit type-argument free calls, including historical `first[I64](values: [42])` lacking context and ExprAst.Call not retaining type arguments; distinguish R7-T2 where an earlier typed argument fixes T. Associated-result inference, projection chains, multiple conformances with trait arguments, and array invariance with views.
- Abstract generic and generation-program checking scope; type-parameter name scope; public API closure, republication/name conflicts and part use ownership. Module gates are not assumed trustworthy boundaries.
- typeRefFromFactoryIdx From-proof obligations; function-type labels/suppression; builtin I/O signatures; temporary inout receivers; nested field-default expressions/contextual types.
- F32 semantic versus physical precision; generic Unit payloads; user unary operators/witnesses; nested destructuring bindings. Do not introduce a source prohibition on unconstructible recursive types.
- Seventh-review unconfirmed boundaries: pattern-derived type completion for match subjects with no normal result, index/field/arbitrary-expression direct callees, and generic inference from expected result alone. [Controls and evidence](https://github.com/plew-lang/meta/blob/main/evidence/block-expression-seventh-review/README.md).
- Former grammar unconfirmed implementation boundaries: trait-subject impl/extension active cycles and duplicate declarations within one extension; trait-type-argument projection source historically rejected as v1. Check current spec and implementation before deciding whether that last limit is specified or merely unimplemented. Historical discarded Plew.g4 status is not current evidence.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

For each combination record current source and minimal positive/reject controls, distinguish justified limitations from defects and already fixed cases, and route proven changes through the paused remediation design/restart conditions. Preserve saved decisions through final consumers; do not stop at adding checks.
