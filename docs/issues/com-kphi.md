---
id: com-kphi
status: open
deps: [com-jgy9]
links: []
created: 2026-11-15T06:29:15Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, generics, verification]
---
# Drive ordinary direct call body demand from parametric Mid

Move executable-body demand for authored direct calls from the per-instance source scan to reached checked operations in the cached parametric Mid body. Preserve descriptor producers for result recipes, access writeback, and any stored Mid rows that require them.

## Design

Use the session coordinator above Frontend and Mid or pass an explicitly owned operation view through that boundary. Reuse the checked template and full site identity. Keep reached calls distinct from closure preparation, generation-selected globals, implicit operations and concrete destruction on the residual scanner. Preserve descriptor-before-consumer scheduling across lexical locals, operator/trait/default producers and detached setters.

## Acceptance Criteria

In AOT and lazy preparation, verify actual body requests for ordinary calls, reached diverging callees and reused instances. Contrast a selected outer call whose argument exits before emission using legal source or scoped internal Mid and retain source rejection controls. Include call-result recipes, explicit/default argument order, nested inout writeback, unchanged missing-descriptor diagnostics, and generated/adapter non-interference. Show migrated source branches no longer request executable bodies. Compare fixed-source LLVM, targeted behavior, body-demand counts and compilation time, then obtain independent review.


## Entry policy and controls

Use parametric Mid demand for the AOT and lazy session entries. The direct
Frontend entries used by gen and runFrontend retain existing source demand until they have the
same checked operation view. Prove each entry selects only one demand path.
The residual scanner retains generation roots and unmigrated operations.

A reached diverging call keeps its own request but cannot execute post-call
writeback. Preserve any setter descriptor needed by Access publication and
verify no executed writeback or newly migrated setter-body demand follows the
diverging call. Detached setter demand itself stays on the existing path in this
slice and remains subject to a later reachability audit if it proves material.

Existing controls cover [default result context](../../tests/fixtures/run/mid_default_argument_result_context.pw),
[saved result arguments](../../tests/fixtures/run/call_template_result_arguments.pw),
[nested inout](../../tests/fixtures/run/nested_field_array_inout.pw),
[writeback lifetime](../../tests/fixtures/run/mid_inout_shared_writeback_pin.pw)
and [diverging calls](../../tests/fixtures/run/diverging_call_flow.pw).
Add a scoped assertion for actual body demand where these fixtures only observe
source or output behavior.
