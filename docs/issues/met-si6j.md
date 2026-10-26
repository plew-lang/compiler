---
id: met-si6j
status: in_progress
deps: [met-ucze, met-ia09, met-acfl, met-6e6k, com-gyup, met-rzt4, com-fuo8, com-4bib, com-s248, com-lzpe, com-bkqq]
links: [com-jno0]
created: 2026-10-13T01:29:29Z
type: epic
priority: 1
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Complete checked frontend authority from source to final consumers

This is the parent for the active phase-three type-resolution/type-checking remediation. The target is one body-checking authority for committed meaning and read-only downstream consumption under explicit environments, not one AST walk. Two mandatory rules apply to every increment: **close storage through final use** and **do not stop at adding checks**. Remove the replaced decision path and structurally close write authority.

## Scope and Restart

Scope is the compiler's currently provided type-checking surface and the already approved divergence/flow changes. This is not a requirement to implement every unsupported feature, broaden inference or implicit conversions, redesign runtime/backend, or add persistent incremental compilation. Declaration worklists interpret saved obligations; they must not become another AST-driven type checker.

The supported frontend surface is tracked through the finite area and child
contracts below. Completion is reopened by [com-bkqq](com-bkqq.md):
[com-ugee](com-ugee.md) repaired the confirmed missing-value producer defect;
its E1/completion scope is independently re-admitted at e73a8476/candidate073f.
The phase-three parent remains open pending fresh final admission and gates.
[G1 admission](com-61jt.md) reconciles source-to-final-use
authorities, removals, controls and remaining excluded boundaries. [G2a](com-p5um.md)
proves the frozen candidate's fixed point/performance; [G2b](com-9l3b.md) proves
its complete correctness/sanitizer gates. [G3](com-lzpe.md) owns the final
independent eleven-criterion synchronization; its prior final approval is superseded by the current re-review.
[The closure-assurance retrospective](#closure-assurance-retrospective) explains
why prior reviewed completion was premature and proposes the recovery boundary.
Do not equate completing the four lexical repairs with re-certifying this parent.
The separate [development-method and test-audit epic](com-jno0.md) groups
operational rules, API/test audits and a bounded process trial. It does not own
this implementation tree or replace G1/G2a/G2b/G3. G1 requires its phase-three
recovery assignment and real-repair trial; unrelated corpus audits do not block
phase three. Actual repair dependencies must still be attached to their areas
and G1 before admission.
[Existing-feature conformance](com-604k.md) remains open for phase four and final
integration. Worklog owns the current candidate and next action; scoped evidence
does not substitute for a final candidate's gates.


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
9. [x] Close historical D1/D4/D5 controls and classify/address D2/D3/D6 risks. Uninspected coverage is not completion; preserve representative positive/reject combinations.
10. [ ] Complete normal, generation, dependency, ASan/LSan, fixed-point and formal performance gates with matching source/carrier/artifacts. Satisfy the user-approved formal median below 7 seconds or obtain an explicit approved change; focused and old-driver checks do not substitute.
11. [ ] Synchronize design contracts, issue state and worklog. Unresolved in-scope items preclude completion; main integration follows the normal integration criteria.

## Work Units

The original area issues are epics for their exact existing contracts:
[selection](met-ucze.md), [callee/interface evidence](met-ia09.md),
[type/conversion/descriptor consumers](met-6e6k.md),
[source publication](met-acfl.md) with [owner storage](com-kp3y.md),
[completion](com-fuo8.md), and [retained parser/CLI observations](met-rzt4.md).
Their required work is expressed by actual tk dependencies. The bounded tasks
below own executable actions and scoped evidence; no second mutable status list
is kept in this document. [met-j9mv](met-j9mv.md) remains the closed adopted
restart design, and [com-gyup](com-gyup.md) the closed bounded ownership study.

## Phase Three Execution Plan

A–F area/child Outcomes retain their independently reviewed producer, saved
authority, final consumer and removed-path records. The [type/conversion area](met-6e6k.md#reconciled-area-completion)
and [eight-path selection area](met-ucze.md#reconciled-area-completion) provide
closure routing; actual states and prerequisites belong to tk. E1/completion and
com-ugee have scoped independent re-admission. G1, G2a,
G2b and G3 remain open for current-candidate reconciliation. Previous3c gates
remain evidence only for that unchanged candidate.

The [work-breakdown review](com-hxtr.md#outcome) is addressed by separating
milestones 3B–3F from their real child tickets. The tickets name actual entry
files/functions, finite deliverables, existing control inputs and exit criteria.
An uncertain mechanism is a bounded investigation, not a fictional specified
implementation. The table is routing, not a copied issue-state index; use tk for
open/in_progress/closed and real prerequisites.

| Unit | Action owner / deliverable | Work kind |
|---|---|---|
| A (3A) | [com-g2qg](com-g2qg.md): Close enum field inference and approved fixture cleanup | Completed implementation increment |
| B0 (3B) | [com-qehq](com-qehq.md): Reconcile the eight current callable paths and remaining closure sites | Bounded investigation |
| B1 (3B) | [com-qb05](com-qb05.md): Verify written static calls consume one saved source selection | Bounded closure verification |
| B2 (3B) | [com-17yh](com-17yh.md): Verify operator protocol iteration and try calls keep selected requirements | Bounded closure verification |
| B3 (3B) | [com-v2xk](com-v2xk.md): Verify requirement clauses and inherited receivers reach the real callee environment | Bounded closure verification |
| B4 (3B) | [com-yojf](com-yojf.md): Resolve the stronger universal nominal proof audit with bounded counterexamples | Bounded investigation |
| C1 (3C) | [com-nplw](com-nplw.md): Propagate a committed earlier array element type to later elements | Known local implementation gap |
| C2 (3C) | [com-nucu](com-nucu.md): Close partial-input projected member enumeration before source admission | Bounded investigation of one query boundary |
| C2 repair (3B/3C) | [com-4kti](com-4kti.md): Unify generic and projected member candidate selection before source admission | Bounded shared-frontier implementation |
| C3 (3C) | [com-m0bf](com-m0bf.md): Classify remaining unstamped nominal producers and paired legacy readers | Bounded producer inventory |
| C3 producer repair | [com-nqjd](com-nqjd.md): Stamp late source and synthetic nominal terms with their selected owner | Paired producer/read repair from planned inventory |
| C3 synthetic repair | [com-qbwg](com-qbwg.md): Preserve Core Buffer identity across early and late synthetic construction | Finite dual-stage producer/read repair from inventory reconciliation |
| C3 chain source repair | [com-i62n](com-i62n.md): Preserve complete source types before Optional-chain rewriting | Finite pre-rewrite source-result/consumer repair from inventory reconciliation |
| C3 factory source repair | [com-uruz](com-uruz.md): Preserve selected declaration identity through custom-factory source receivers | Finite source/context-to-rewrite and saved-call repair from inventory reconciliation |
| C3 context repair | [com-fyxe](com-fyxe.md): Use the selected complete associated-call parameter context | Paired signature/context repair from planned inventory |
| C3 body-key repair | [com-6paa](com-6paa.md): Preserve declared receiver identity through final body keys and retire paired recovery | Paired producer/final-key repair after other producers |
| C4 (3C) | [com-e9l2](com-e9l2.md): Verify saved result recipes and projection identity at final reads | Bounded closure verification |
| C5 (3C) | [com-loyb](com-loyb.md): Verify source conversion proofs retain exact endpoints and ownership | Bounded closure verification |
| C6 (3C) | [com-3q2n](com-3q2n.md): Verify closure and dynamic descriptors retain semantic dependencies | Bounded closure verification |
| D1 (3D) | [com-rv13](com-rv13.md): Reconcile owner payload publication and core final-reader closure | Bounded closure verification of implemented storage |
| D2 (3D) | [com-vkw3](com-vkw3.md): Verify closure global default and provided source-domain ownership | Bounded source-owner verification |
| D3 (3D) | [com-wqa0](com-wqa0.md): Close operation and constraint API write authority after semantic selection | Bounded API/removal verification |
| D4 (3D) | [com-m3c6](com-m3c6.md): Verify nominal facet batch publication remains one-way | Bounded API/removal verification |
| E1 (3E) | [com-2suv](com-2suv.md): Verify block branch and short-circuit completion use one result authority | Bounded semantic closure verification |
| E1 result-producer repair | [com-ugee](com-ugee.md): Require source value production despite analytical loop noncontinuation | Finite common value-region producer/publication/consumer repair from completion re-review |
| E2 (3E) | [com-0ssn](com-0ssn.md): Verify explicit transfer errors remain distinct from loop reachability warnings | Bounded diagnostic/flow verification |
| E3 (3E) | [com-9tau](com-9tau.md): Verify diverging callable types survive value storage and invocation | Bounded callable-contract verification |
| E4 (3E) | [com-gnj9](com-gnj9.md): Verify saved exit targets drive Mid cleanup and final lowering | Bounded final-consumer verification |
| E4 target repair | [com-tl9c](com-tl9c.md): Save source transfer targets and consume their active Mid mappings | Finite paired source publication/final-consumer repair |
| F1 (3F) | [com-4bib](com-4bib.md): Assign and verify requested-body semantics across command modes | Bounded mode-parity investigation and controls |
| F2 (3F) | [com-d57o](com-d57o.md): Close the finite retained parser recovery observations | Bounded historical investigation |
| F3 (3F) | [com-vrvl](com-vrvl.md): Isolate normal CLI InternalSession progress before changing JIT policy | Bounded isolated investigation |
| F4 (3F) | [com-s248](com-s248.md): Assign D1 through D6 to current controls and responsible closure tasks | Finite evidence-disposition task |
| G1 (3G) | [com-61jt](com-61jt.md): Reconcile all phase three closure evidence before freezing a candidate | Final evidence admission |
| G2a (3G) | [com-p5um](com-p5um.md): Verify the frozen candidate fixed point and formal self compilation time | Final standard gate |
| G2b (3G) | [com-9l3b](com-9l3b.md): Run all final correctness and sanitizer gates on the measured compiler | Final standard gates |
| G3 (3G) | [com-lzpe](com-lzpe.md): Synchronize phase three parents and discharge the eleven criteria | Final closure and handoff |

Recommended order is B0, then its actual residual callable paths, followed by the
remaining type/publication/completion/mode work. This is not an artificial
whole-area dependency: independent bounded tasks may be ready. Hard tk edges
are only required outputs (B0 -> its call-path closures, selected-call closure ->
operation API final closure, nominal-producer classification -> facet closure,
saved completion -> final cleanup). Current selection belongs in worklog.

### Bounded Task Policy

- Each bounded task requires an independent subagent completion review before
  closing. Record the reviewed revision, scope, evidence and disposition in that
  task; fix in-scope findings and re-review affected conclusions. Final parent
  review does not substitute for these task reviews.

- Aim for roughly one or two active human working days per bounded child. This
  is a granularity target, not a deadline or a promise about an unknown repair.
  If a task exposes a larger independent change, name it and create a child with
  exact entry/exit instead of silently widening the original scope.
- Investigations finish a finite disposition: every named row is supported by
  applicable existing evidence, a verified limitation, or a specifically owned
  required repair. An unresolved in-scope question is not classified away. Add
  every mandatory repair as a dependency of its area and G1; reopen a closed
  area when necessary. A closed investigation never implies its repairs passed.
- Implementation/closure verification records producer -> saved fact/publication
  -> explicit instance environment -> final consumer, removed competing decisions,
  revision, positive/reject/corruption controls and tested input/carrier. Existing
  correct code closes by evidence, not by inventing a rewrite. Conditional local
  repairs must preserve the same end-to-end contract; adding checks alone is not
  completion. Ambiguous language/ABI judgments retain the stop conditions below.
- Use actual tk statuses and dependencies. Area epics are not scheduled as one
  enormous executable task. A source-contract child and its area can close with
  applicable fresh scoped validation after all required repairs; their closure
  does not certify a whole-candidate release. Final normal/gen/deps/full ASan-LSan,
  fixed-point and formal-performance obligations remain mandatory here through
  G2a/G2b. This explicit allocation replaces repeated per-area final-gate waits;
  it removes no required check and attributes no old gate to a new binary.
- G1 joins the completed area contracts, F1/F4 and all required descendants. It
  checks finite coverage and absence of known unfinished implementation **before**
  final gates. G2a produces the measured/fixed-point compiler; G2b tests that
  artifact with matching frozen inputs. G3 synchronizes evidence and discharges
  this parent. Main/seed/carrier integration remains the whole conformance plan's
  later boundary, not an automatic action on phase-three closure.
- A new gate failure returns to a named owning task/area and invalidates affected
  admission/gate evidence. G1/G2/G3 cannot become anonymous residual source-fixing
  buckets. Preserve unchanged valid results, rerun affected gates and never weaken
  verifier, tests, watchdogs or the seven-second target.

### Mapping to the Eleven Criteria

The original checklist above is unchanged and remains the only parent acceptance
checklist. These task links assign evidence, not another set of checkboxes. G1
must confirm each row has current decisive proof/removal/control evidence; G2a/G2b
and G3 discharge final gate/synchronization obligations. Unclassified owner/state/
mode paths or unfinished mandatory descendants prevent closure even if every
initially issued investigation has finished.

| Criterion | Required evidence tasks | Acceptance evidence |
|---|---|---|
| 1 | [A](com-g2qg.md), [C1](com-nplw.md), [C3](com-m0bf.md), [E1](com-2suv.md), [G1](com-61jt.md) | Context may refine unknowns, never overwrite committed shape/type; direct and wrapped controls. |
| 2 | [C1](com-nplw.md), [C3](com-m0bf.md), [C4](com-e9l2.md), [C5](com-loyb.md), [C6](com-3q2n.md), [D1](com-rv13.md), [D2](com-vkw3.md), [D3](com-wqa0.md), [D4](com-m3c6.md), [E1](com-2suv.md), [E2](com-0ssn.md), [E3](com-9tau.md), [G1](com-61jt.md) | Explicit state/owner/recipe distinctions and successful publication without unresolved source obligations. |
| 3 | [A](com-g2qg.md), [B0](com-qehq.md), [B1](com-qb05.md), [B2](com-17yh.md), [B3](com-v2xk.md), [B4](com-yojf.md), [C1](com-nplw.md), [C2](com-nucu.md), [shared candidate repair](com-4kti.md), [C3](com-m0bf.md), [C4](com-e9l2.md), [C5](com-loyb.md), [C6](com-3q2n.md), [D1](com-rv13.md), [D2](com-vkw3.md), [D3](com-wqa0.md), [D4](com-m3c6.md), [E4](com-gnj9.md), [G1](com-61jt.md) | Exact producer, published fact, explicit environment and actual Mid/backend consumer. |
| 4 | [A](com-g2qg.md), [B0](com-qehq.md), [B1](com-qb05.md), [B2](com-17yh.md), [B3](com-v2xk.md), [B4](com-yojf.md), [C2](com-nucu.md), [shared candidate repair](com-4kti.md), [C5](com-loyb.md), [E3](com-9tau.md), [G1](com-61jt.md) | Full signature/labels/passing/bounds, including implicit calls; existence is not validity. |
| 5 | [C1](com-nplw.md), [E1](com-2suv.md), [E2](com-0ssn.md), [E4](com-gnj9.md), [G1](com-61jt.md) | Equivalent available context for direct/block/if/match/short-circuit and correct live joins. |
| 6 | [E1](com-2suv.md), [E2](com-0ssn.md), [E3](com-9tau.md), [E4](com-gnj9.md), [G1](com-61jt.md) | Approved value/divergence/diagnostic rules and final cleanup/targets. |
| 7 | [D2](com-vkw3.md), [F1](com-4bib.md), [F2](com-d57o.md), [F3](com-vrvl.md), [G1](com-61jt.md) | Equivalent requested bodies across modes; unused omission and separate gen program are intentional. |
| 8 | [A](com-g2qg.md), [B0](com-qehq.md), [B1](com-qb05.md), [B2](com-17yh.md), [B3](com-v2xk.md), [B4](com-yojf.md), [C1](com-nplw.md), [C2](com-nucu.md), [shared candidate repair](com-4kti.md), [C3](com-m0bf.md), [C4](com-e9l2.md), [C5](com-loyb.md), [C6](com-3q2n.md), [D1](com-rv13.md), [D2](com-vkw3.md), [D3](com-wqa0.md), [D4](com-m3c6.md), [E1](com-2suv.md), [E2](com-0ssn.md), [E3](com-9tau.md), [E4](com-gnj9.md), [G1](com-61jt.md) | Removed competing decision/writer/fallback sites and post-outcome/foreign-owner controls. |
| 9 | [F2](com-d57o.md), [F3](com-vrvl.md), [F4](com-s248.md), [G1](com-61jt.md) | Six concrete current historical/risk dispositions, linked to actual owners/controls. |
| 10 | [G2a](com-p5um.md), [G2b](com-9l3b.md) | Frozen candidate, complete standard gates, fixed point and formal median below seven seconds. |
| 11 | [F1](com-4bib.md), [F4](com-s248.md), [G1](com-61jt.md), [G3](com-lzpe.md) | Complete evidence assignment, current issue state and synchronized closure/handoff. |

Historical D1/D4/D5 are expected-array overwrite, partial operator validity and
flow/ownership controls; D2/D3/D6 are downstream reinference, state conflation and
partial duplicated checks as risk classes. [F4](com-s248.md) owns the finite
current-input/consumer/task/evidence mapping from the retained migration record.
No class is presumed to be a newly reproduced current defect.


### Historical and Risk Disposition (F4)

These are exactly the six migration classes, not six newly reproduced bugs.
Named controls are the current maintained inputs. The cited receipts certify
only their frozen scoped candidates; G2 must rerun the final candidate. A finite
class disposition does not close its mandatory open repair or the area/G1.

| Class | Current positive / negative controls | Authority from producer to final reader | Responsible closure and evidence |
| --- | --- | --- | --- |
| D1 — incompatible expected Array overwrite | `array_forward_element_context`, `block_array_literal_context`; `array_forward_context_explicit_conflict`, `array_forward_context_block_conflict`, direct/block/empty `type_context_array_as_Bool` and `type_context_array_as_I64` variants. `arrow_store_literal` now retains its 42/99 output after the canonical structural-index repair. | Record commits the source expression/binding type and admitted conversion; prepared aggregate/value-region readers consume it through Mid and LLVM. A later requested context cannot rewrite that commitment. | C1 [com-nplw](com-nplw.md), E1 [com-2suv](com-2suv.md) / [com-f0mq](com-f0mq.md): `phase3c-array-context.json` and `phase3e-result-authority.json`. [com-o3vw](com-o3vw.md) closes the structural index producer; current full-candidate replay remains G2. |
| D2 — downstream type/callee/evidence reinference | `source_typing_owner_requests`, `prepared_aggregate_source_owner`, `protocol_selected_result_authority`, `selected_copy_receiver_identity`; the last rejects swapped receiver/foreign proof and wrong lexical Self, and detects duplicate copies. | Owner-local saved terms, operation/constraint facts and complete environments feed instantiated callee descriptors, Parametric Mid and LLVM. Source selection must be valid before Direct is saved; consumers cannot rescue a bad saved callee by selecting again. | C4/C5/C6 and B3 contracts remain scoped evidence; fresh [com-9p68](com-9p68.md) / `selected-copy-receiver-repair.json` closes the newly exposed receiver selection family. [com-9clj](com-9clj.md) closes associated copy production and [com-3qne](com-3qne.md) closes original default forwarding authority; [com-6cw6](com-6cw6.md) retains root-birth placement, and [com-v1wa](com-v1wa.md)/[com-tkz7](com-tkz7.md) close synthetic named-construction producers and remove bare-head recovery. Full-candidate admission/gates remain separate. |
| D3 — absent/unprepared/failed/success state conflation | `source_owner_payload_stability`, `source_builder_branch_isolation`, `type_declaration_publication`, `type_term_closedness`, `source_completion_diagnostics`; missing/foreign/failed owner controls in the same internal fixtures. | Source preparation publishes an explicit owner outcome and sealed payload; successful empty evidence differs from missing preparation. Nominal facets publish once. Final expression, operation and signature readers require the matching successful owner. | D1/D4 [com-rv13](com-rv13.md), [com-m3c6](com-m3c6.md), E2 [com-0ssn](com-0ssn.md); exact receipts in those tickets, plus `phase3e-diagnostic-flow.json`. F1/F2 are scoped mode/recovery evidence; F3 [com-vrvl](com-vrvl.md) and [com-auvx](com-auvx.md) close CLI progress with opt-in observation, not general state certification. |
| D4 — partial operator validity mistaken for whole-call validity | `operator_invalid_operand_range`, `source_operator_literal_context`, `generic_closure_operator_bound`, `operator_output_type`; `operator_hetero_rhs_range`, `operator_hetero_nested_range`, `operator_diverging_witness`, `type_operator_same_type_without_requirement`. | Record selects the full operator requirement/signature and operand terms; complete source operand/range/passing/constraint checks precede source success. Saved result projections and proof feed both worklists and the actual Mid/LLVM call. | B2 [com-17yh](com-17yh.md), E3 [com-9tau](com-9tau.md): `phase3b-implicit-call-closure.json`, `phase3e-callable-authority.json`. No existence-only operator acceptance or late result-type repair is authorized. G2 retains final rerun. |
| D5 — flow / ownership continuation disagreement | `give_exits_block`, `prepared_value_block_source_owner`, `block_loop_completion`, `pattern_mutable_capture`, `block_abandoned_result`, `conditional_move_continuations`; saved transfer-target corruption and divergence/value-position rejects in E1–E4. | Shared completion distinguishes source-value/control transfer from analytical execution reachability; saved explicit source target identities and admitted bindings determine Mid CFG edges, cleanup and LLVM. Last-statement AST shape cannot reconstruct completion. | E1–E4 [com-2suv](com-2suv.md), [com-0ssn](com-0ssn.md), [com-9tau](com-9tau.md), [com-gnj9](com-gnj9.md), retained ownership [com-gyup](com-gyup.md): `phase3e-result-authority.json`, `phase3e-diagnostic-flow.json`, `phase3e-callable-authority.json`, `phase3e-transfer-targets.json`. Ownership ASan registration is retained; full final ASan remains G2. |
| D6 — partial / duplicated checks with competing write authority | `source_operation_owner_storage`, `source_call_storage_publication`, `call_template_seal`, `source_call_constraint_evidence`, `source_call_proof_boundary`; post-success/failure writes and missing/foreign operation/evidence corruption. | Source builder owns semantic selection and publication; compatibility/verifier walks may validate operands but cannot overwrite the selected operation. Both worklists consume admitted constraints and final descriptors. Foreign-owner evidence and post-outcome writes fail at actual readers. | D3 [com-wqa0](com-wqa0.md), B1/B2/B3/B4 and C6: `phase3d-operation-authority.json` and their scoped receipts. Current receiver wildcard/first-match paths were removed in [com-9p68](com-9p68.md), not merely hidden by another verifier. G1 audits remaining area exits before G2. |

Receipt paths above are under meta
`evidence/existing-feature-conformance/source-owner-facts/`. This table is the
single six-row mapping; tk owns live task status and dependencies.

### Updating Progress

Update the bounded ticket with actual implementation/removal/evidence and close
it only at its stated exit. An area closes after its required descendants and
scoped contract evidence; parent final gates are still independent obligations.
Use tk dep tree/ready/blocked for state, and worklog for the one selected next
action and current candidate/handles. Keep current findings, not cumulative WIP
attempts; Git and existing evidence retain past checkpoints. No progress percent
is computed from tickets, commits or repeated validation runs.

## Stop Conditions

Stop and report an evidenced task omission, erroneous allocation or other required
plan correction before continuing under a silently revised plan. An in-scope
implementation bug already covered by a task is not by itself a plan error.

Stop for an unapproved specification change; a language-specific design decision not derivable from adopted policy/Rust/Swift references; tooling/environment failure preventing necessary validation after diagnosis; or self-compilation at least 7 seconds when repair is judged difficult. A threshold crossing alone does not establish irreparable cost: investigate with matching-source comparisons. Do not weaken validators, checks, test expectations or performance conditions to continue.

Stop for erroneous tests except authorized cases: tests broken by an approved specification change, internal non-language-surface tests, or newly written tests that have never passed may be repaired after preserving their original purpose. An unrelated known limitation need not block a bounded required fix. Keep unresolved design issues explicit rather than calling a compromise the final design.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

The existing typed-source parent is the frontend workstream within com-604k, not the parent of every conformance task. Its 11 criteria remain mandatory on the admitted source surface, with the approved below-7-second target. Missing unique-generic/loop/new-reference facilities remain separate. Current acceptance controls from com-uutc are discharged here; unsupported forms are not enabled to close this parent.

## Current Reconciliation and Reopening

The return-owner repair a9556c25 and dynamic-argument repair1cff794a
independently close com-wrjh/com-nr7y/com-jzdz/com-cwu1 at finite scope.
The current inventory is13 findings in12 repair tasks (original F3/F4 share
one Unit task). Three canonical overload/duplicate repairs are WIP at
a22670c5; build and bounded check contrasts do not certify actual dispatch
or mode/full/performance gates. Their independent reviewer confirms new
[met-g53w](met-g53w.md), a separate existing trait selector-group generic-shape
admission gap. Required deps to met-ucze and G1 are recorded. Work stops under
the user's task-omission condition; the new group repair is not implemented.
Evidence is overload-identity-checkpoint.json. All area/G1/G2/G3 gates and
other required repairs remain open, without shrinking the parent contract.

Fresh specification-first [com-9hf7](com-9hf7.md) confirms11 in-scope findings
(3 P1/8 P2), assigned to10 finite required repair issues. The affected
selection, callee/evidence, type/conversion, publication and completion areas
are reopened with actual prerequisites. Criteria1-8,10 and11 remain pending;
criterion9 retains only its exact historical six-row disposition scope.
Review completion and green prior controls do not certify these new boundaries.

The common failures include lost invocation returns at loop boundaries,
nonexistent global return targets, incomplete dynamic call signatures and
shallow type comparisons, stale shared-result refinement, unsealed conversion
backing and noncanonical Unit/async return contracts. These are existing
feature contracts, not new inference, Never, capability generics or runtime
feature requirements. Detailed sources/actual outputs and ownership paths are
in meta/evidence/existing-feature-conformance/source-owner-facts/
phase3-specification-rereview.json and the linked repair issues.

The com-ugee missing-producer repair remains independently complete in its
finite scope. Earlier unrelated successful source/proof/storage paths remain
usable evidence when inputs and contract match. No full restart is authorized
merely by a new finding. New073f normal/gen/deps milestones remain valid; old3c
formal fixed-point/ASan gates apply only to old3c. New final G2a/G2b/G3 remain
required after source repair and G1 admission.

## Closure Assurance Retrospective

This is the user-requested investigation of the **completion method**, following
[met-tfbl](met-tfbl.md), not another implementation acceptance. Original eleven
criteria remain unchanged. The recovery below is a proposal for task-plan
reconciliation; it has not silently created tasks, changed dependencies, or
authorized source repair.

### Evidence and Failure of the Previous Inference

The original completion at dab97d52/production043e2402 was real and was withdrawn
after [com-bkqq](com-bkqq.md). Its exact saved compiler3c532ce1 reproduces the
representative V1/V2/V3/V4 defects, plus the gen-related unrelated-name rejection:
8 fixed-input projects,38 watched commands, check/native/JIT and selected gen
contrasts. The renamed positive controls pass. std/Plew.toml/Plew.lock are
unchanged from043e2402 through aaf7f134. These defects were present in the
accepted candidate; they are not explained solely by subsequent repairs.
The additional gen contrasts emit host LLVM, not actual host execution.

Sources, original-candidate commands/results, historical code/blame, exact old
fixture contents and selected prior review records are retained in meta/evidence/
existing-feature-conformance/source-owner-facts/phase3-assurance-retrospective.json.
Full previous reviews remain in their existing receipts; no duplicate review
transcripts or second task register is introduced.

| Recorded observation | Consequence for the assurance claim |
| --- | --- |
| B0/com-qehq defined exactly8 broad call families. Its58-source hash manifest omits Check/Visibility; negative source checks focus on removed final selectors. | A family name was treated as a closed path, although preselection vetoes and classification branches were not evidenced. A file hash is not read coverage, and an absent hash does not prove nobody read it; the saved evidence nevertheless cannot establish that boundary. |
| B1/com-qb05 removed a **Verify** free-name rescan after selection. Its shadowing fixture uses a same-module free function. | This useful repair and positive control do not establish absence of the analogous **preselection Visibility** decision against unrelated modules. Reviewing only the changed selector/removal tail leaves another authority outside the frame. |
| C6/com-3q2n verifies retained closure binding/field/type identity and final descriptors, including deliberately corrupted records. | A downstream reader can faithfully preserve an incorrectly classified or insufficiently admitted source operation. Corruption rejection cannot certify correctness of its source producer. |
| global_closure_invocation copies the global closure to a local before invoking it; global_closure_call_constraints checks global preparation internally. Existing closure_arg_label_mismatch fixtures check literal-to-function-type compatibility. | Those successful tests do not execute direct global invocation or wrong labels at a closure **call**. These tests are valid, but their names/categories cannot substitute for inspecting the exercised path. |
| F1/com-4bib's seven owner/mode rows use representative contrasts. Later specification-first review combines closure/interface into one dynamic row; its calls manifest does not establish Visibility/resolvedCallee coverage. | Owner, mode and call-family coverage does not automatically cover binding kind, type readiness, provenance and argument admission. Reading all chapters or listing all issues is not equivalent to tracing every relevant decision boundary. |
| G3's retained acceptance verifies11 criterion links,68 graph nodes, receipt/input/artifact identity and292 documentation links. | Evidence consistency was promoted into semantic sufficiency. Those checks and the green full gates remain valuable and genuine, but do not establish missing semantic coverage. |
| com-bkqq explicitly found no durable task-specific B0/B1 review record and supplied a **new** acceptance later. | The required per-task review discipline was not demonstrably complete at first closure. Do not retrospectively assume the original review happened. The later correction does not erase the original control failure. |

The primary root is **claim scope larger than demonstrated decision coverage**.
Task partitioning followed representations and familiar successful lanes more
closely than every place that can decide acceptance, binding, type, conversion
or control flow. Leaf evidence was finite, but its union was used to assert an
entire supported surface without independently establishing completeness of the
partition. Repeated reviewers starting from those same inventories/fixtures can
inherit the same blind spots; separate agents alone do not establish independent
coverage. This is an inference from recorded methods/results, not a claim about
reviewers' private reasoning or fabricated execution.

The design and execution plan already required source-to-final closure, removal
of competing authorities, full source admission and explicit unverified bounds.
More repetitions of those words would not fix this failure: **the plan was not
operationally demonstrated at its claimed scope**. The previous parent completion
was premature. Neither the presence of many bugs nor the current evidence proves
every implementation path is defective, but known tests plus another general
"thorough review" cannot currently justify another global completion claim.

### Proposed Recovery Before Further Completion Claims

1. **Freeze the investigation input and retain valid work.** Pin source/spec,
   candidate and current scope. Keep old scoped results as scoped evidence;
   withdraw aggregate conclusions whose coverage cannot be shown. No wholesale
   rewrite, rollback, seed promotion or phase-four expansion follows from this
   retrospective.
2. **Rebuild the phase-three decision inventory from executable entries and
   contracts, then reconcile the old tickets.** Inspect every relevant normal,
   lazy, global/default/provided/closure and generated request from admission
   onward. Include code that accepts/rejects before a saved fact exists, not just
   readers after publication. Search/index helpers, diagnostic failures, builtin
   intercepts, compatibility passes and mode privileges need explicit disposition.
   Search results are leads, not an exhaustive call-graph proof.
3. **Make each inventory row actionable.** Name input/owner/preconditions,
   decision and authority, actual callers/guards, retained fact and publication
   guarantee, final readers, legitimate remaining validation, replaced sites and
   corresponding source-level positive/negative controls. Distinguish local versus
   global, callable versus noncallable/pending, and ordinary versus synthetic
   provenance where code branches. A broad family is an organizing label, not a
   sufficient row. Untraced relevant decisions remain explicitly unverified.
4. **Close the inventory before claiming the repair set is sufficient.** Every
   relevant decision site must be classified as covered with evidence, needing a
   bounded repair, or outside scope with a normative reason. Four met-tfbl repair
   units remain valid findings, not proof they exhaust phase three. A first-pass
   reviewer derives boundaries/counterexamples from spec and actual entries before
   seeing the implementation's coverage verdict; reconciliation follows. Do not
   promise every program or a combinatorial product of all features.
5. **Reconcile finite tasks against that inventory.** Preserve already valid
   leaf repairs; reopen only invalidated claims and assign uncovered boundaries
   to named owners/dependencies. For example, complete existential argument
   admission in com-cwu1 does not certify fn-value arguments. Resolve required
   specification boundaries separately. Review revised scope sufficiency before
   resuming the repair sequence; do not silently amend the plan on each discovery.
6. **Pair structural closure with public semantic execution.** Verify source
   admission and saved identity through the actual final consumer. Deliberately
   corrupted-record tests supplement, not replace, valid/wrong-label/count/mode/
   type/ownership source cases. Confirm the expected rejection stage/category;
   an unrelated visibility failure or internal error is not a successful reject.
   Use finite contrasting classes and interaction pairs: unrelated declaration
   rename/addition, same versus other module, direct versus local alias, inferred
   versus explicit equivalent type, wrapped versus direct, cold versus prepared
   cache when relevant. Respect intentional lazy unused-body omission.
7. **Separate three review obligations.** Leaf review checks its bounded fix and
   removals. Area integration review checks inventory completeness and interactions
   between leaves. Final G3 reconciles already justified semantic evidence and
   exact-candidate gates. Integrity checks and large green suites cannot discharge
   the missing area review; a leaf review cannot certify its containing area.
8. **Re-certify once the evidence supports the original contract.** Require zero
   known unresolved in-scope defects and zero unclassified high-risk decisions in
   the agreed inventory, the actual structural removals and behavioral controls,
   independent area acceptance, then G1/new fixed-point and below7-second G2a/
   complete G2b/G3 on applicable fixed inputs. A newly found omitted authority
   invalidates the affected inventory/area claim and requires reconciliation,
   rather than merely adding one regression and repeating broad approval.

### Recurrence Prevention and Limits

Use the existing issue records for the decision rows and their coverage, with
real dependencies. Do not create another hand-maintained index or treat task/test/
agent/hash counts as confidence scores. A completion report must state the exact
claim, the branch/entry distinctions tested, remaining limits and why its evidence
is sufficient. An implementation or test name never establishes what ran.

When a bug exposes a duplicated authority, audit its finite sibling routes and
the containing contract's coverage before closing it; do not add a syntax-specific
exception. Changes to an authority, published fact or reader invalidate the
affected semantic evidence explicitly. Unchanged valid evidence need not be rerun.
Put recovered public-source regressions and essential isolation contrasts into
the maintained suites, not only scratch or manually invoked internal fixtures.
Where it preserves semantics and cost, encode the authority boundary in API/stage
construction and remove obsolete entry paths so later callers cannot bypass it.
This does not mean adding a second full type checker or weakening legitimate
independent readiness/integrity verification.

No finite review proves zero latent bugs. The completion claim sought is the
original, bounded design-conformance contract with inspectable coverage and no
known unresolved required boundary, not a promise that another reviewer can never
find a defect. Repeated new simple violations of that same contract are evidence
to question the inventory/completion method, rather than routine reasons to keep
extending an allegedly complete surface.

## Current Outcome

**Not complete.** The user-requested retrospective now questions sufficiency of
the previous coverage/closure method. Review the recovery proposal above before
resuming the repair sequence; no revised task graph has yet been adopted.
Retain the finite required repairs from com-9hf7 and the four met-tfbl proposals,
but do not assume that list exhausts required work. After scope reconciliation,
independently re-admit affected task/areas and G1, then run the necessary
new-candidate G2a/G2b and G3 reconciliation. Preserve valid unaffected work;
do not substitute checks at a final reader for complete source admission and
sealed producer-to-consumer authority. No new specification decision is needed
for the confirmed findings. Phase four, main, seeds and adopted-carrier promotion
remain outside this boundary.
