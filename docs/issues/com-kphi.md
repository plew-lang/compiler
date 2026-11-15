---
id: com-kphi
status: in_progress
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

## Implementation entry

The canonical call terminator contains the full template key. Use that key to
associate reached operations with the existing checked template registry.
`DeclarationAccessAnalysis.obligations` cannot supply the complete demand view:
`analyzeDeclarationGlobalAccessRoots` can return an empty analysis when the
program has no mutable globals. Read the cached parametric body's CFG instead.
Build this view once per authored function in the session as bodies are
requested, including when declaration effect collection did not walk that CFG.

The AOT root/frontier loop currently lives in the Frontend compatibility
entry, which cannot read Mid. Factor the common root/frontier operations so
the session can select the per-body checked view without importing Mid into
Frontend. Keep the direct Frontend entry's compatibility behavior. Integrate
the view at the written direct call's demand point so lexical locals,
dependencies of result recipes, descriptor validation, and Access writeback
still run at their existing scope points. Synthetic sites and other operation
families keep their current demand path.

The common finalization entry now exposes root preparation and final
publication separately, with the existing compatibility loop between them.
The previous candidate accepted the changed sources in check and LLVM output
modes. The session loop and Mid demand view still need to be connected.

The AOT session now owns its dependency loop, using the shared Frontend root
and publication phases. It preserves dependency interleaving and collection
context restoration. The direct Frontend entry keeps the existing loop.
Finalization traces share the same counters and markers. The fixed candidate
accepted the changed compiler source in check mode. Reachability is not yet
connected to requests in this checkpoint.

AOT and lazy sessions now supply a per-authored-function view of reached
parametric Mid template sites. Written free direct calls use this view for
executable demand and retain descriptor preparation at the existing scan
point. Compatibility callers use the default policy. The fixed previous
candidate accepted the changed sources and emitted LLVM. Native candidate
execution, targeted demand assertions, and performance comparison remain
pending. The residual scanner still traverses authored operands.

Independent review at f7598453 found that an early Mid build error lost its
normal diagnostic mapping. Use `programPreparationDiagnostic` with the
existing Mid build error and instance identity. The candidate accepted the
fixed source in check mode. Eight native fixtures passed on f7598453.
On `mid_call_reached_completion`, final body scans fell from 46 to 42.
Same-source compiler medians were 8.402 s to 8.370 s, with identical LLVM
in all ten runs. This is a diagnostic comparison. Verify per-callee demand
in both modes and re-review the diagnostic fix before closure.

Per-callee AOT diagnostic on `mid_call_reached_completion`: the baseline
declares frozen bodies for identity, sink, update and stop. The f7598453
candidate declares stop and omits the other three. The instance summary still
records all four identities, as expected for descriptor retention.
The [session demand fixture](../../tests/fixtures/run/mid_direct_executable_demand.pw)
also passed when built against the current sources. It observes the actual
lazy worklist, requires the reached diverging callee, excludes the blocked
outer call, and checks repeated requests preserve body identity and count.

Independent re-review at 77d6cf59 confirmed the original diagnostic mapping.
The native candidate for that revision passed eleven targeted AOT tests, the
lazy operand-exit fixture, both source rejection controls with identical
baseline diagnostics, and generation (20261115T074340-gen-5bec66).
The AOT trace again declared stop and omitted identity, sink and update.
[Fixed-source comparison](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-receiver-admission/phase3-parametric-mid-demand-final.json)
gave 8.018 s to 7.885 s and all ten LLVM digests matched. This is not a
formal fixed-point run. Missing-descriptor and combined diverging indexed
writeback controls are still outstanding.
