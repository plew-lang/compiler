---
id: com-nudy
status: open
deps: []
links: [com-cuoy]
created: 2026-11-17T09:13:25Z
type: bug
priority: 2
assignee: Koji Murata
tags: [syntax, diagnostics]
---
# Validate names in dotted type paths before semantic resolution


## Contract and observed gap

The shared Syntax layer owns the grammar for qualified type segments. A member segment after a dot must be a name before the type is handed to name or conformance resolution. See [Syntax and Semantic Input](../design/syntax.md#3-information-preserved-at-the-handoff).

With compiler 86a5c87c and Syntax e8aee7c, the following input to `plewc --check` exits 1, but reports “associated-type short projection has no unique trait source” at line 2.

```plew
struct Item {}
fn inspect(value: Item.#) {}
fn main() {}
```

The direct nominal-type parser consumes the post-dot token into the segment span without first checking its name shape. com-cuoy covers tokens left at the parameter boundary and does not correct this path.

## Guarantees and completion

- Reproduce the syntax acceptance and assert the earliest error at the offending token. Cover missing and non-name segments in reachable direct, materialized and legacy entry points.
- Keep valid qualified module types, qualified projections, and generic member paths. The parser should preserve written names without making lookup decisions.
- Confirm source failure and the original syntax diagnostic through the compiler, with independent review. Limit the change to dotted type segment admission.
