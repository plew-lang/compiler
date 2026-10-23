---
id: com-nplw
status: open
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Propagate a committed earlier array element type to later elements

## Boundary

Phase 3C / C1. **Known local implementation gap.** Parent criteria: 1, 2, 3, 5, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Resolve/Expr.pw`.

At Record.recordExpr Expr.Array, retain an incoming valid element expectation; otherwise use a successfully recorded, committed earlier element type as context for subsequent children, including a known type containing rigid lexical generic parameters. Do not read later elements to repair an earlier unknown, use an argument-less generic head as a completed type, or overwrite explicit/committed child types. Save the same Array[E] aggregate result and let ordinary compatibility reject conflicts.

## Exit and Evidence

Add or consolidate controls: inferred Some then None succeeds; None first without incoming context rejects; annotated array permits None first; conflicting explicit element type rejects; direct versus block-wrapped elements agree under the same context; a generic payload T still propagates Optional[T] without treating rigid T as an unresolved inference hole. Verify actual multiple-element native values/layout and the saved aggregate path. A need to change the approved forward inference rule is a stop, not permission to broaden inference.

Existing starting controls: `generic_enum_field_inference`, `generic_enum_array`, `generic_enum_field_inference_unresolved`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
