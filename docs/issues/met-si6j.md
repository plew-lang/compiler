---
id: met-si6j
status: in_progress
deps: [met-ucze, met-ia09, met-acfl, met-6e6k, com-gyup, met-rzt4, com-fuo8]
links: []
created: 2026-10-13T01:29:29Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Complete checked frontend authority from source to final consumers

This is the parent for the active phase-three type-resolution/type-checking remediation. The target is one body-checking authority for committed meaning and read-only downstream consumption under explicit environments, not one AST walk. Two mandatory rules apply to every increment: **close storage through final use** and **do not stop at adding checks**. Remove the replaced decision path and structurally close write authority.

## Scope and Restart

Scope is the compiler's currently provided type-checking surface and the already approved divergence/flow changes. This is not a requirement to implement every unsupported feature, broaden inference or implicit conversions, redesign runtime/backend, or add persistent incremental compilation. Declaration worklists interpret saved obligations; they must not become another AST-driven type checker.

Implementation has resumed as phase three of existing-feature conformance. The initial [com-kp3y](com-kp3y.md) owner-storage increment and subsequent source-selection/evidence increments are implemented in part; their remaining closure follows the execution plan below. Completing a component does not complete this parent. [com-nsxb](com-nsxb.md) retains the detailed static findings and repair boundaries. [Checked-body storage and the restart design](../design/checked-body-storage.md) are adopted and reviewed; [met-j9mv](met-j9mv.md) retains the reconciled cumulative candidate and fresh baseline. Preserve these successful increments/evidence; do not repeat an unchanged baseline solely because this issue previously described the gate as pending. Worklog owns the selected candidate/carrier, active handles, verification and next step. Historical candidates and measurements in [migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) do not establish current-tree readiness.

Design authorities: [Body Checking](../design/body-checking.md), [Types and Evidence](../design/types-and-evidence.md), [Generics](../design/generics.md), [Compiler State](../design/compiler-state.md), [Frontend Handoffs](../design/frontend-handoffs.md). The storage supplement owns the adopted physical design and restart details; these chapters own logical contracts.

## Completion Criteria

Each item requires implementation locations and scoped verification records, not checkbox completion from wrappers or green tests alone.

1. [ ] Expected types only fill permitted unknown information or check compatibility; they never overwrite expression shape, explicit or committed semantic type.
2. [ ] Distinguish unrecorded facts, local inference variables, deferred obligations, incompatibility, Unit, rigid parameters and no normal value. No unresolved source typing obligation survives successful publication.
3. [ ] One authority for types, calls, proofs and conversions connects source recording/success through explicit instantiation to final Mid/backend consumers; no AST reinference or name reselection by final readers.
4. [ ] Functions, factories, adapters, operators and implicit calls check complete signature, labels, ownership modes and bounds; candidate existence is not final validity.
5. [ ] Under the same available context, expression wrapping changes acceptance only where the adopted value/divergence rules require it. Block/if/match/short-circuit share normal results and exit targets; checked dead code cannot contaminate live joins.
6. [ ] Integrate approved divergence: value-position rejection, following-code errors versus analytical-loop warnings, loop-following give, empty match, diverging function values versus invocation and forbidden normal-function conversion. Centralize semantic completion; keep diagnostic reachability distinct from execution/ownership flow.
7. [ ] check/build/run/gen use the same semantics for requested bodies. Lazy run may omit unused bodies; it may not defer invalidity in a requested body.
8. [ ] Remove migrated reinference fallbacks, partial acceptance and duplicate semantic state; structurally separate constructing writers from immutable readers. Retained adapters are one-way representation transforms. Demonstrate final consumers, removed decisions and post-completion write rejection.
9. [ ] Close historical D1/D4/D5 controls and classify/address D2/D3/D6 risks. Uninspected coverage is not completion; preserve representative positive/reject combinations.
10. [ ] Complete normal, generation, dependency, ASan/LSan, fixed-point and formal performance gates with matching source/carrier/artifacts. Satisfy the user-approved formal median below 7 seconds or obtain an explicit approved change; focused and old-driver checks do not substitute.
11. [ ] Synchronize design contracts, issue state and worklog. Unresolved in-scope items preclude completion; main integration follows the normal integration criteria.

## Work Units

- [met-j9mv](met-j9mv.md)
- [met-ucze](met-ucze.md)
- [met-ia09](met-ia09.md)
- [met-acfl](met-acfl.md)
- [met-6e6k](met-6e6k.md)
- [met-rzt4](met-rzt4.md)

Completion-flow work also uses [com-tijs](com-tijs.md) and the existing control-flow audit [com-gyup](com-gyup.md). [com-uutc](com-uutc.md) is a retained adjacent acceptance audit, not an automatic expansion of this parent's required scope. Unsupported unique/capture shapes keep their separate tasks.

## Phase Three Execution Plan

This section owns phase-three ordering and exit boundaries. Child issues own
their detailed path inventories, implementation findings and closure evidence;
tk metadata owns issue status. The meta worklog owns the single selected next
action, current source/carrier and active validation handles. Do not maintain a
second status list in meta. The labels 3A–3G are local steps, not new tickets,
statuses or language-design decisions.

Step **3A is complete** at compiler/test revision `09e5a277`: its
[closure inventory](met-6e6k.md#current-increment-closure-inventory) and
[receipt](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3a-completion.json)
identify the exact fresh controls and remaining gate limits. Steps 3B–3G are not
certified complete. They already contain substantial implemented increments;
the remaining work is to discharge their finite boundaries with evidence, not
restart the migration or mark unchecked paths complete by inference. Next is 3B;
repair a discovered prerequisite in its owning issue without creating a parallel
authority. Completion of 3A does not close met-6e6k's remaining 3C scope.
The [independent completion review](com-h4pz.md#outcome) also accepts 3A's
closure; it does not discharge any later step.

| Step | Owning issues and existing progress | Remaining work and exit condition |
|---|---|---|
| 3A. Finish the current enum-construction increment | [met-6e6k](met-6e6k.md#field-driven-enum-construction-inference). Shared struct/enum field inference and focused native positive/reject controls exist. | Apply the approved test cleanup: consolidate ordinary array safety in runtime coverage, remove the redundant unused valid-input guard, retain genuinely invalid unused-body and uninferred-construction rejection. Register applicable sanitizer coverage. Build the latest source and verify inferred/explicit/conflicting/unresolved cases, multiple elements and String cleanup. Do not attribute the earlier fresh binary to subsequent source edits. |
| 3B. Close selection and evidence handoff | [met-ucze](met-ucze.md), [met-ia09](met-ia09.md). Saved selection, scoped proof interpretation, inherited receivers and final descriptors have implemented controls. | Reconcile ordinary/method/factory/operator/protocol/implicit/adapted/dynamic paths. Finish the stronger universal-nominal/source-certificate audit, exact requirement-to-implementation clause/parameter mapping and actual callee environments. Check differing proofs with equal ABI, missing/foreign/replaced evidence and unavailable versus malformed members. Remove migrated reselection; retain explicit concrete instantiation. Unresolved semantic/ABI choices require a user decision. |
| 3C. Close remaining type, conversion and descriptor producers/readers | [met-6e6k](met-6e6k.md). Canonical grounded-argument and nominal receiver fixes are retained. | Inventory raw/unstamped type construction, result recipes, projections, conversions, closure/dynamic descriptors and partial-input member enumeration. Trace selected identity and evidence through actual final use, replacing name/cursor fallbacks only with matching producer migration. Resolve/classify the recorded forward array-context gap under the adopted inference policy; preserve explicit/committed types and reject genuine conflicts. Verify direct/wrapped forms and prior-result identity controls. |
| 3D. Close publication and API write authority | [met-acfl](met-acfl.md), [com-kp3y](com-kp3y.md). Owner-local immutable payloads and declaration-facet batch publication exist. | Reconcile all remaining writer and final-reader families after 3B/3C: headers, expression/binding/completion, operations/constraints, globals/closures/default/generated domains, conversions/descriptors and nominal facets. Distinguish construction queries from successful-owner readers. Demonstrate failure/foreign-owner/missing-fact rejection, post-outcome write refusal, retained-reader stability and removal of replaced tables/readers. Close the storage component only when its final revision has the required scoped evidence. |
| 3E. Close completion and expression consistency | [com-fuo8](com-fuo8.md), supported by [com-gyup](com-gyup.md). SourceCompletion/isDiverging and continuation-ownership increments are retained. | Trace shared normal results/exit targets through block/if/match/short-circuit to Mid cleanup and LLVM. Cover direct/wrapped values, expected types, empty match, nested exits, diverging callable values/invocations/conversions, following-code errors and analytical-loop warnings. Reconcile affected historical tests with the approved semantics. Remove remaining last-statement/AST/name-based competing decisions. Preserve the bounded closed ownership investigation; new syntax is excluded. |
| 3F. Close requested-body mode and historical controls | [met-rzt4](met-rzt4.md), with the current-subset controls routed from [com-uutc](com-uutc.md) to the owners above. | Reconcile check/build/run/gen for equivalent requested bodies, including global/default/provided/generated and unused-body boundaries. Finish the bounded parser/normal-CLI InternalSession controls or record and repair an evidenced blocker; traced embedded execution does not establish normal CLI completion. Map every retained D1–D6 class to its current path/control and disposition. Do not turn missing features or every untested combination into new mandatory work. |
| 3G. Discharge the parent and final candidate gates | This parent, using the implementation/evidence from 3A–3F. Earlier matching gates remain scoped evidence. | Verify all eleven criteria above have explicit implementation/removal/control evidence; close remaining in-scope child obligations. Freeze one candidate and run normal/gen/deps/LLVM22 ASan-LSan, fixed point and formal median below 7 seconds. Reconcile evidence applicability after any edits, synchronize docs/issues/worklog, and meet normal integration requirements. Main integration belongs to the whole conformance plan, not a unilateral phase-three merge. |

The order expresses closure dependencies, not permission to leave existing
consumers broken until a later step. A scoped increment needs appropriate fresh
controls before proceeding. Heavy whole-candidate gates run at meaningful
milestones and in 3G; they are not required after every inventory row. New
failures or changed inputs determine which earlier evidence must be refreshed.

### Per-issue Closure Inventory

Before editing the next path in an owning issue, reconcile its existing records
into a finite inventory. Reuse existing evidence and source locations; do not
append another historical checkpoint for every attempt. Each row records:

- The admitted input/call/owner/mode family and the exact design contract.
- Producer -> saved/publication fact -> explicit instance environment -> final
  consumer, including failure or cleanup where relevant.
- The replaced writer/reselection/reinference/fallback and its removal location,
  or why a retained construction/instantiation query is legitimate.
- What current source actually implements, what is still uninspected or known
  broken, and the next bounded action. Investigation is not a proven defect.
- Implementation revision and decisive positive/reject/corruption controls,
  evidence path, tested compiler/source and any remaining gate limitation.

Inventory closure must account for every family already named in that issue's
scope. Do not require an exhaustive Cartesian product of language features.
Use representative controls at the actual boundary; split out an evidenced
independent defect only when the existing issue cannot own it coherently.
Newly discovered in-scope work must update the owning row, its effect on the
exit condition and any real dependency before changing the selected task.
Out-of-scope work needs a reason and owner, not silent deferral.

### Mapping to the Eleven Criteria

The numbered checklist above remains the only parent completion checklist.
These links identify where evidence must come from, not additional checkboxes.

| Criterion | Primary steps / decisive evidence |
|---|---|
| 1. Expected types preserve meaning | 3A/3C/3E: producer and direct/wrapped compatibility controls |
| 2. Distinct states; no unresolved publication | 3C/3D/3E: state/API audit and missing/deferred/value/Unit/completion controls |
| 3. One authority through final use | 3B/3C/3D: path inventory and actual Mid/backend evidence |
| 4. Complete callable validity | 3B/3C: signature, labels, ownership, bounds and implicit-call controls |
| 5. Expression wrapping and joins | 3C/3E: same-context direct/block/if/match controls |
| 6. Approved divergence | 3E: saved completion, diagnostics, cleanup and callable controls |
| 7. Requested-body semantics across modes | 3F, with the shared paths from 3B–3E |
| 8. Remove obsolete authorities | 3B/3C/3D/3E: removal/API audit and forbidden-write controls |
| 9. Historical D1–D6 | 3F: explicit disposition linked to current owning rows and controls |
| 10. Matching final gates/performance | 3G: frozen candidate, exact artifacts and gate receipts |
| 11. Synchronization and unresolved scope | 3G: child closure, criteria evidence and document reconciliation |

Historical identifiers retain the meaning in the
[migration record](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md):
D1 expected-array overwrite; D4 partial operator validity; D5 flow/ownership;
D2 downstream reinference, D3 state conflation and D6 partial duplicated checks
are risk classes. Their presence in this list is not a current reproduction.

### Updating Progress and Closing a Step

On each bounded increment, update the owning inventory row with the actual
result, remaining work and evidence, then update worklog only if the selected
action/candidate/handle changes. Use tk to start/close the actual issue; preserve
existing in-progress work without implying simultaneous executions. Before
moving to the next step, account for every exit item in the owning issues and
record the closure rationale and its evidence there; update the reconciliation
statement above when it no longer holds. A step finishes only its stated boundary; a
partial implementation or a green focused test is not issue/parent completion.

Report progress as the selected step, implemented boundaries, remaining exit
items, evidence scope and next action. Do not compute a percentage from issue
counts, checklist counts, commits or repeated validation runs. If a requirement
is already discharged, cite and reuse the matching record instead of restarting
it. If it is not, leave it explicitly uncompleted. This management reconciliation
adds no new implementation or validation success.

## Stop Conditions

Stop for an unapproved specification change; a language-specific design decision not derivable from adopted policy/Rust/Swift references; tooling/environment failure preventing necessary validation after diagnosis; or self-compilation at least 7 seconds when repair is judged difficult. A threshold crossing alone does not establish irreparable cost: investigate with matching-source comparisons. Do not weaken validators, checks, test expectations or performance conditions to continue.

Stop for erroneous tests except authorized cases: tests broken by an approved specification change, internal non-language-surface tests, or newly written tests that have never passed may be repaired after preserving their original purpose. An unrelated known limitation need not block a bounded required fix. Keep unresolved design issues explicit rather than calling a compromise the final design.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

The existing typed-source parent is the frontend workstream within com-604k, not the parent of every conformance task. Its 11 criteria remain mandatory on the admitted source surface, with the approved below-7-second target. Missing unique-generic/loop/new-reference facilities remain separate. Current acceptance controls from com-uutc are discharged here; unsupported forms are not enabled to close this parent.
