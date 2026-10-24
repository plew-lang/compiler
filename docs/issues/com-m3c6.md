---
id: com-m3c6
status: open
deps: [com-m0bf, com-nqjd, com-6paa]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Verify nominal facet batch publication remains one-way

## Boundary

Phase 3D / D4. **Bounded API/removal verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Ir/Types.pw`; `src/Codegen/Resolve/Record.pw`; `src/Frontend.pw`.

Reconcile finishTypeDeclarationResolution and its private mutation against C3 source nominal producers. Check the all-or-nothing validation of ordered unique row identities, permanent phase closure and legal later appends. Trace the completed declaration dependency into successful source-owner admission.

## Exit and Evidence

Existing type_declaration_publication plus focused invalid/duplicate batch, post-publication row/append and branch controls establish the current API boundary. No production per-row overwrite writer remains. Do not conflate semantic term publication with runtime nominal layout or reimplement the already adopted batch.

Existing starting controls: `type_declaration_publication`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
