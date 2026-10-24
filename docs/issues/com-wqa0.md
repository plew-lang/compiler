---
id: com-wqa0
status: in_progress
deps: [com-qb05, com-17yh, com-v2xk, com-4kti, com-fyxe]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Close operation and constraint API write authority after semantic selection

## Boundary

Phase 3D / D3. **Bounded API/removal verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Resolve/Expr.pw`; `src/Codegen/Check/CallConstraints.pw`; `src/Ir/InstanceConstraints.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`.

After [com-4kti](com-4kti.md) closes its shared generic/projected candidate
selection repair, use its revised source-selection/constraint-publication map
together with the finalized B1/B2/B3 maps. Enumerate operation/constraint constructors, navigation and sealed readers. Verify private owner payload mutation is possible only while Building and auxiliary storage-demand analysis cannot rewrite committed operations. Follow each saved operation/constraint range to admitted callee and final use.

## Exit and Evidence

Operation/constraint API table and privacy/post-outcome/foreign-owner controls close the remaining public writer boundary. Confirm source-local immutable range backing, no second semantic navigation store and no removed storage-summary rewrite. Preserve declaration construction queries and independent access-analysis results; no test-only writer exposure.

Existing starting controls: `source_operation_owner_storage`, `source_call_storage_publication`, `call_template_seal`, `source_call_constraint_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Operation and Constraint API Reconciliation

Runtime production remains `c1b731bd`; this audit reconciles the cumulative
B1/B2/B3, com-4kti and source owner implementation rather than adding another
selection mechanism.

| Boundary | Producer / authority | Saved record and consumer |
|---|---|---|
| Source operation construction | `appendCallTemplate` requires an open `currentSourceOwner`, the canonical source site owner and a new complete key. `replaceBuildingCallTemplate` explicitly selects a location and requires that exact site key and an open target owner. | `SourceBodyData.operations` is private owner-local backing. `SourceCallLocation` contains only owner/key/local-index navigation. `callTemplateAt` checks the retained key and cached reader owner/session; `PreparedSemanticFacts.operationAt` reads immutable local rows. |
| Nested operands / types / views | `directCallTemplateArgs` and `publishCallTemplateArguments/TypeArgs/Operands/Views` append to private session pools. No set/remove/clear path changes an issued slice. | Owner-local operation rows retain ranges into stable session-private immutable child pools, as permitted by `checked-body-storage`. Source selection validates range bounds, arity, types, labels, access modes and declaration scope. A slice allocated while another owner was active is not itself a foreign semantic owner. |
| Constraint selection | `prepareCallTemplateConstraints` computes a declaration-scoped selected plan and invokes private `recordBuildingCallConstraints` / `storeBuildingOperationConstraints`. | The plan resides alongside its operation in `SourceBodyData.operationConstraints`; no parallel semantic navigation store contains its meaning. `checkRecordedCallConstraintEvidence` validates the saved scope, subjects, clauses and proof boundaries. |
| Successful admission | Private `admitSelectedCallConstraints` retains the exact checked plan in private-constructor `AdmittedCallConstraints`. The lexical/global preparation tails finish all fallible typing/conversion/nested checks first. | `publishPreparedCallConstraints` stores an immutable `PreparedCallConstraints` snapshot before `finishSourceFacts` seals success. No callback or fallible user work intervenes. Failed owners expose no prepared constraints; completed owners cannot reacquire writers. |
| Instance / callee handoff | `instantiateSelectedCallConstraints` requires the actual location's successful source owner and prepared snapshot, grounds its saved obligations under explicit environments and preserves selected source paths. | `selectedCallConstraintEvidence` checks the retained target against the actual callee. `environmentWithCallableConstraints` / `instantiateRequirementCallConstraints` retain clause/ParamId mappings; Arena's `prepareCallableConstraints` / `prepareDeclarationConstraints` create append-only immutable bindings, not source admission authority. Ordinary final static-call preparation consumes this evidence. |
| Storage demand | Private `finalizeSourceCallStorage` and lexical/global loops execute only in the successful preparation tail. | They preserve site/selection/receiver/result/arguments and may refine only the conservative `mayHaveStorageArguments` bit before sealing. `closeProgramCallTemplates` cannot revise published operations; declaration access analysis remains independent. |

Replacement intentionally has an explicit target rather than a current-Cursor
authorization rule. Default completion restores its lexical Cursor before
updating the selected row, and whole-lexical finalization visits closure/provided
rows. Forcing cursor equality there would duplicate identities and break valid
construction. Foreign-owner replacement means mismatching the target location's
complete site key, not explicitly requesting another still-Building row.
Append remains tied to the current source recorder and rejects another site's
owner even when the key is new.

The independent static reviewer confirmed no required physical pool relocation:
the invariant is immutable owner-local operation/constraint meaning with stable
scoped session pool access, not a private copy of all child pools per payload.
Final Mid/LLVM contains no call to construction-time selected-plan preparation
or source candidate selection. B1/B2/B3 and C4/C5/C6 retain their separate exact
callee, recipe, conversion and descriptor evidence boundaries.
