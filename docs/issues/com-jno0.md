---
id: com-jno0
status: open
deps: [com-5by1, com-2hx2, com-ouh2, com-sn9w, com-lbnc, com-x7r3, com-bv1s, com-e713, com-8iys, com-5zvv, com-tqzw, com-3p7m]
links: [met-si6j, com-604k, met-tfbl]
created: 2026-10-26T12:48:12Z
type: epic
priority: 1
assignee: Koji Murata
tags: [verification, tooling]
---
# Establish evidence-based compiler development and audit existing tests

## Purpose and Authority

Make compiler development depend on scoped executable evidence and enforceable
responsibility boundaries, rather than task counts, repeated assurances or green
suites with unexamined oracles. The user authorized this separate epic and child
organization on 2026-10-26. The [adopted execution plan](https://github.com/plew-lang/meta/blob/7893c820/agents/llm-development-workflow-proposal.md) records the
research, alternatives and limitations. Rule integration is work owned by
[com-5by1](com-5by1.md), not already completed by creating this epic.

Evidence motivating the work is the [phase-three retrospective](met-si6j.md#closure-assurance-retrospective)
and [lexical/visibility investigation](met-tfbl.md). Existing spec and design
remain semantic authorities. This epic introduces no language change.

## Scope and Boundaries

- Integrate intended-RED TDD, scoped task contracts, evidence-based independent
  review and test validity checks into existing development entry points.
- Audit phase-three APIs for unnecessary decision authority, including arguments,
  retained fields, captures, globals and unrestricted access through Comp.
- Audit the actual existing test corpus for valid expectations, assertions,
  exercised paths, discovery and missing contract controls, prioritizing phase
  three. Discovery inventory and semantic coverage are separate evidence.
- Reconcile finite repairs with existing owners, try the method on one actual
  repair, and verify sustained use through phase-three re-admission.

Existing implementation repairs, G1/G2a/G2b/G3 and main/seed integration retain
their current owners. Do not reparent the phase-three tree here, duplicate its
final gates, or make all non-phase-three audits prerequisites of phase three.
Confirmed in-scope phase-three gaps cannot be deferred to close that phase.
Non-phase-three defects discovered by the corpus audit need owned follow-ups;
this epic does not silently require every unsupported feature or every unrelated
repair before the development-method work can close.

No mandatory new guard, validate-task DSL, receipt format, CI system, management
tool replacement or full mutation-testing platform is authorized by this epic.
Existing validate/watchdogs/input freezing and the formal median below seven
seconds remain applicable; no threshold or verifier/test weakening is allowed.

## Work Routing

| Responsibility | Child owner |
|---|---|
| Operational rules and entry points | [com-5by1](com-5by1.md) |
| Phase-three API/authority inventory | [com-2hx2](com-2hx2.md) |
| Actual test discovery and disjoint audit assignment | [com-ouh2](com-ouh2.md) |
| Phase-three API responsibility audit | [com-sn9w](com-sn9w.md) |
| Phase-three test validity and missing controls | [com-lbnc](com-lbnc.md) |
| Finite recovery repairs and admission dependency reconciliation | [com-x7r3](com-x7r3.md) |
| One real lexical-binding repair as a process trial | [com-bv1s](com-bv1s.md) |
| Remaining frontend tests | [com-e713](com-e713.md) |
| Remaining Mid/backend/ownership/runtime tests | [com-8iys](com-8iys.md) |
| Remaining driver/gen/deps/harness tests | [com-5zvv](com-5zvv.md) |
| Full-corpus audit reconciliation | [com-tqzw](com-tqzw.md) |
| Continuity, effectiveness and handoff | [com-3p7m](com-3p7m.md) |

This is routing, not a copied status list. Use tk for live state and dependencies.
Inventories must bound the audit batches before execution. If an assigned domain
exceeds roughly one or two active human working days, replace its executable
scope with finite child batches before starting the broad audit, preserving the
complete partition and required dependencies. Creating this plan is not evidence
that the inventory or any audit has already occurred.

## Completion

All required child outcomes have independently reviewed evidence. The actual
corpus is partitioned and audited without unclassified omissions; required repairs
and specification questions have concrete owners. Phase three is re-admitted by
its existing owners on current evidence, with all original gates and scope intact.
A fresh-context execution demonstrates use of the rules without the user having
to supply per-task paperwork or reminders. Record effectiveness and remove or
simplify ineffective process, without weakening correctness obligations.

Audit completion, repair completion and phase/whole-candidate admission are
separate claims. Unknown defects are not proved absent. The epic does not merge
main, promote a seed/carrier or close the whole conformance project.
