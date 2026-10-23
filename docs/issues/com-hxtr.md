---
id: com-hxtr
status: closed
deps: []
links: []
created: 2026-10-23T10:07:34Z
type: task
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification, design]
---
# Review phase three work breakdown for actionable bounded tasks

## Scope and Method

Review the actual phase-three work breakdown, not 3A completion or compiler
correctness. Three independent reviewers inspected
[met-si6j](met-si6j.md#phase-three-execution-plan), its actual tk dependencies,
owning issues, the meta progress/worklog and the relevant design boundaries.
They assessed actionable implementation scope, a few working days per human
implementer, and sufficiency of all task closures for the eleven parent criteria.

Review input is compiler 6a8cd25e / meta 3722a167. Read-only inspection and tk
queries only: no source changes, probes, build, suite or performance execution.
Time estimates are qualitative, not measured implementation durations. The
review is not a new comprehensive source audit or evidence of new compiler bugs.

## Outcome

**Investigated: current 3B–3F decomposition is insufficient as an executable,
few-day task plan.** All three reviewers agree. The overall scope and eleven
criteria remain sound, and 3A completion stands; the problem is task granularity,
current remaining-work reconciliation and explicit ownership of acceptance
evidence. Do not continue implementation from the broad 3B milestone row as if
it were an already bounded task.

The parent holds the unresolved replanning obligation. This review is complete;
the recommendations below are not already-created or completed implementation
tasks. Existing implemented increments must be reused, not restarted.

## Findings

### P1: Milestones are being used as executable tasks

Reviewers `phase3_task_action_review`, `phase3_task_size_review` and
`phase3_task_coverage_review` all found that the 3B–3F rows enumerate broad audit
families. The parent explicitly requires a finite inventory to be produced
before editing the next path, but those inventories are not yet present outside
the completed 3A slice. Worklog's next action, closing a remaining call/evidence
path, does not identify which path or its actual change/removal/test sites.

met-ucze has 458 lines of cumulative WIP: older next-operation/storage/iteration
instructions sit beside later implementation checkpoints. These are not all
current pending work; reconstructing that distinction is still necessary.
com-fuo8 has a broad completion/divergence contract without an inventory of the
specific current unclosed producers/consumers. Neither is a defensible few-day
implementation task just because its subject has a name.

Reconcile existing evidence into finite current rows first, then create
independently closable implementation tasks only for actual remaining gaps.
An investigation has an explicit finite deliverable and does not itself close
required repairs discovered by it. Unknown scope is not a promised few-day fix.

### P1: Mode parity and historical controls lack executable owners

The parent's 3F row includes requested-body parity across check/build/run/gen
and ordinary/global/default/provided/closure/generated owners. met-rzt4's actual
contract covers parser recovery and retained InternalSession JIT observations;
it does not define that broader parity matrix.

D1–D6 have definitions and a parent routing requirement, but no finite current
input -> fact/consumer -> responsible task -> evidence assignment. D2/D3/D6
remain risk classes, not six newly reproduced bugs. Create a bounded parity unit
and a finite historical disposition task/table, reusing existing controls rather
than inventing an exhaustive feature product.

### P1: Metadata does not expose the intended closure units

3A–3G are local labels, not tickets. A step can complete while its mixed owning
issue remains in_progress for other steps; met-6e6k after 3A is the immediate
example. That status is truthful, but repeating it for every increment hides
actual completed work in the CLI. Long-lived area issues should group short
children whose individual closure has implementation/removal/test evidence.

The intended sequence also is not a hard dependency graph. met-acfl depends only
on com-kp3y, while its 3D row follows 3B/3C and com-kp3y still describes a wait for
met-ucze work. The wide selection/evidence/conversion issues have empty deps and
are all reported ready. Do not fix this by adding whole-area mutual dependencies;
record only actual fact-family prerequisites between the bounded children.

### P2: Slice closure and final-candidate gates are mixed

com-kp3y and met-ia09 retain latest full-gate closure language while 3G owns the
final frozen candidate gates. This makes it unclear whether an increment may
close before the full phase ends. Define the bounded children's applicable fresh
controls and retain all final-candidate verification obligations explicitly at
the parent/integration boundary. Do not delete required gates or relabel a scope
limited success as whole-parent readiness. Existing area issues can remain open
for their full contract while their bounded implementation children close.

### P2: 3G can absorb undefined implementation work

With unenumerated 3B–3F work, 'close remaining in-scope child obligations' can turn
3G into another unbounded audit/fix stage. Require finite prior inventories to be
accounted for and no known unfinished in-scope implementation before entering
final verification. Failures found by a final gate reopen the identified owning
unit; they do not become anonymous residual implementation inside 3G.

### P2: State and source-owner coverage is not assigned at task level

Criterion 2's unrecorded/inference/deferred/incompatible/Unit/rigid/no-value states
and the function/closure/global/default/provided/generated ownership domains are
distributed across 3C/3D/3E. A general list of these words does not identify who
supplies each decisive control. Select representative boundaries such as shared
ExprId across distinct owners, failure, post-outcome writes and retained readers;
do not require the Cartesian product of every state and owner.

## Recommended Units to Define

These are proposals for reconciliation, not assertions that every named path is
broken or still needs implementation. Confirm current source and reuse scoped
successful evidence before issuing repair tasks.

| Area | Candidate independently closable units |
|---|---|
| 3B | First reconcile the finite ordinary/method/factory/operator/protocol/try/adapter/dynamic paths into producer, saved fact, environment, final consumer, retired path and existing control rows. Then separately close a demonstrated static-selection gap, clause/ParamId/callee-environment gap, or erased/inherited proof gap. Stronger universal nominal predicates need a bounded investigation before a semantic repair can be specified. |
| 3C | Forward array context; partial-input projected member enumeration; canonical nominal producers and their paired legacy readers; result recipes/projections; conversions; closure/dynamic descriptors. Split only genuinely independent remaining boundaries; do not delete all name fallbacks without their producer migration. |
| 3D | Owner publication/state/write API; operation/constraint and default/generated domains; nominal facet/API final closure; successful-owner final-reader/removal audit. Reuse implemented storage/facet closure and make dependencies per moved fact family. |
| 3E | Normal-result/exit composition; explicit transfer errors versus analytical-loop warnings; diverging callable type/value/call/conversion; saved completion through Mid cleanup/final use. Preserve one semantic authority and do not reopen the bounded closed com-gyup investigation without new evidence. |
| 3F | Requested-body parity table and controls; bounded retained parser check; normal-CLI InternalSession observability/materialization question; D1–D6 current disposition. Retained 2154af1b CLI observations are not a newly reproduced defect at the latest candidate. |
| 3G | Reconcile eleven criteria/child evidence; freeze candidate and run all required gates; reconcile artifacts/docs and any changed-input reruns. Source repairs return to their actual owning units. |

Each actual implementation task needs its entry function/API, committed fact,
final consumer, removed competing decision, positive/reject/corrupt control,
applicable gate scope and explicit exit. If these cannot yet be named, first cut
a bounded investigation with a finite result and a link to required follow-ups.

## Coverage and Next Action

No missing major parent criterion or unreachable existing owning issue was found.
The tk graph reaches met-ucze/ia09/acfl/6e6k/rzt4/fuo8, closed com-gyup and,
through met-acfl, com-kp3y. Existing closure source facts versus runtime capture/
drop work (com-j3pp), and initializer facts versus startup effect/SCC work
(com-fkxl), are legitimate phase-three/four boundaries. Missing unique generics,
new loop syntax and general opening remain excluded. Required final normal/gen/
deps/full sanitizer/fixed-point/formal performance gates are listed.

However, a conceptual mapping to eleven criteria is not proof that completing
the current unbounded tasks is a predictable sufficient execution plan. The
smallest next action is to reconcile **3B's current path inventory**, choose the
first actual remaining closure, and cut its bounded tk task. Subsequent 3C–3F
areas need the same finite assignment before implementation. Keep overall scope
and all acceptance obligations; no new management tool or status system is needed.

## Planning Follow-up

The task arrangement now materializes 28 bounded tickets in the
[parent execution plan](met-si6j.md#phase-three-execution-plan): the already
completed 3A unit, 23 remaining investigation/implementation/verification units
and four final admission/gate/closure units. The next task is
[B0](com-qehq.md), not an anonymous remaining 3B path.

Area issues are epics with required child dependencies. Current selection WIP
and owner-storage histories were replaced by current contracts and task routing;
other contracts retain their semantic obligations and explicit child routing.
Each bounded task has actual entry files, actions, exit evidence and starting
controls. Unknown repairs require a specifically owned blocking follow-up.
Final full-gate obligations are retained by G2a/G2b at the parent; bounded task
and area closure do not certify the final candidate. G1 waits for complete area
contracts and remaining mode/historical tasks before final verification.

This records implementation of the planning recommendations, not a new
independent acceptance of the revised breakdown. Compiler source/tests/candidate
and existing validation evidence were not changed by task arrangement.


Planning consistency checks: all 28 bounded IDs are reachable from the parent
dependency graph; completed 3A alone is closed, the other 27 remain open. The
original eleven acceptance criteria are byte-for-byte unchanged. tk reports no
dependency cycle; all changed/new issue links resolve. Entry files and starting
fixture names exist. Original focused compiler/source/test inputs still match
the saved 3A hashes. These are management/source-integrity checks, not new
compiler execution or independent review of the revised plan.
