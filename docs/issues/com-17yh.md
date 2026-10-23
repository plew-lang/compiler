---
id: com-17yh
status: open
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Verify operator protocol iteration and try calls keep selected requirements

## Boundary

Phase 3B / B2. **Bounded closure verification.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ucze](met-ucze.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Verify/Ops.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Use B0 operator/protocol/try rows. Follow selectedProtocolTemplateCall/groundedProtocolTemplateReceiver and saved operation slots to actual final calls; verify Iterator/next, Eq/Add and try extraction use the selected requirement and same evidence. Confirm retired ProtocolSelection.Direct and structural next-only acceptance have no migrated source/consumer path.

## Exit and Evidence

Each named operation family has its exact producer/slot/final callee, applicable signature/bound controls and no fallback acceptance. Preserve Ord-to-Bool/Ne result projections and existing ambiguity/structural rejection controls. Any discovered repair is limited to that family and keeps parent/gate dependencies; no new protocol surface.

Existing starting controls: `source_operation_owner_storage`, `prepared_try_source_owner`, `generic_closure_iteration_bound`, `generic_closure_operator_bound`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
