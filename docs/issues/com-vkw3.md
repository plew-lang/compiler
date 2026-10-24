---
id: com-vkw3
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Verify closure global default and provided source-domain ownership

## Boundary

Phase 3D / D2. **Bounded source-owner verification.** Parent criteria: 2, 3, 7, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Global.pw`; `src/Codegen/Resolve/Record.pw`; `src/CheckedProgram.pw`; `src/DeclarationProgram.pw`.

Construct a five-row owner map: closure body versus creation, per-global initializer versus synthetic all-global body, default declaration/slot, provided lexical body, generated/synthetic body origin. Trace reused ExprIds to successful readers and source signatures without using active Cursor/global sentinels as identity.

## Exit and Evidence

For each row give actual key/producer/reader and existing or minimal distinguishing control. Cover shared ExprId across owners, foreign/missing/failed owner, retained reader and construction-time callable registration without demanding a prepared body. Keep closure runtime environment/copy/drop and startup effect/SCC planning with their phase-four owners.

Existing starting controls: `source_typing_owner_requests`, `default_argument_call_templates`, `global_call_constraint_evidence`, `prepared_binding_source_owner`, `retained_provided_body_constraints`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
