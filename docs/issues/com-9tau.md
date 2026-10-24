---
id: com-9tau
status: in_progress
deps: [com-fbqh, com-px0e, com-o7ul]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Verify diverging callable types survive value storage and invocation

## Boundary

Phase 3E / E3. **Bounded callable-contract verification.** Parent criteria: 2, 4, 6, 8.
This is a bounded child of [com-fuo8](com-fuo8.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Lower/Types.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Return.pw`; `src/Mid/Types.pw`; `src/Ir/Types.pw`.

Trace isDiverging through function/closure type construction, generic/field/associated storage and invocation completion. Distinguish a callable value from invoking it. Verify both directions of forbidden normal/diverging function conversion and the adopted async/FFI boundaries without adding unsupported captures.

## Exit and Evidence

Representative generic/field/associated callable storage controls preserve divergence, invocation is source-nonvalue, taking/storing a diverging callable value is not itself divergence, and incompatible conversions reject. Record exact source term and Mid consumer; no Unit/normal-function fallback.

Existing starting controls: `diverging_callable_declarations`, `diverging_call_flow`, `diverging_function_return`, `diverging_function_fallthrough`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
