---
id: met-rzt4
status: open
deps: [com-d57o, com-vrvl, com-auvx, com-v1wa]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [frontend, jit, diagnostics]
---
# Recheck historical parser recovery and compiler-session JIT stalls

## Bounded Execution and Gate Ownership

This is an area epic, not one executable multi-week task. Its current bounded
work and real prerequisites are tk dependencies under the
[parent policy](met-si6j.md#bounded-task-policy):

- [F2](com-d57o.md): finite historical parser observations.
- [F3](com-vrvl.md): current isolated normal-CLI session progress disposition.

Close this area's exact existing contract after required children/repairs and
their scoped fresh verification. The final frozen candidate normal/gen/deps/full
sanitizer/fixed-point/performance obligation is explicitly owned by
[G2a](com-p5um.md)/[G2b](com-9l3b.md) and cannot be waived when this
area closes. Historical checkpoint gates are not current-candidate certification.
Earlier current/next/WIP observations refer to their named revisions; the bounded
children reconcile what actually remains before any repair. No new meaning or
unsupported feature is authorized by this allocation.

[F1](com-4bib.md) separately owns requested-body mode parity, and
[F4](com-s248.md) owns six historical/risk dispositions. They are direct
parent tasks, not missing acceptance work silently added to this parser/CLI area.

Retained independent investigation from type-checking remediation. Historical reserved-identifier/match/trait recovery could stall until the 60-second watchdog; a compiler InternalSession JIT execution aborted after the selected-body/final-call authority migration. Neither is established as a current-tree defect by the documentation migration.

Recheck exact historical inputs/revisions and watchdog output in [migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) and the [final-call-authority record](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/final-call-authority/README.md) (compiler 1a2ed6b6); separate parser recovery/progress from JIT dependency/abort ownership. Do not infer the _memcpy issue (com-8w4c) is the same failure.

Acceptance: minimal current controls, bounded termination or actionable error, failure-state propagation, and specific implementation/evidence if still reproducible. Do not weaken watchdogs or turn unfinished investigations into source restrictions. Route discovered responsibility changes to separate tickets if necessary.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Current bounded parser recovery for the retained malformed input and the distinct InternalSession JIT abort. Use exact old inputs/revisions, current error/exit controls and stage evidence. Keep the libcall issue separate. Do not weaken watchdogs or introduce unsupported syntax to restore old acceptance.

## Reconciled Area Completion

Independent b2_completion_review accepts this finite investigation/repair area
with F2/com-d57o, F3/com-vrvl and its required repair com-auvx closed.

| Contract | Current decisive evidence |
| --- | --- |
| Retained parser recovery | Four maintained inputs terminate with success or positioned rejection. The exact historical scratch was not retained; this is not an invented exact replay or general keyword certification. |
| Normal CLI compiler-session execution | com-auvx runs all four original CLI --run fixtures with opt-in PLEW_TRACE_RUN=1 progress observation and exact golden output. Quiet/traced equivalence and quiet stderr are a separate smaller CLI control. |
| Genuine progress vs liveness | Seven newly requested bodies produce fourteen monotonic completion events; repeated/unused work produces none. A stalled callback remains interrupted by the unchanged watchdog after 61.126 seconds, exit 124/events 0. |
| Shared execution and failure ownership | Progress options are transported explicitly through CompilerSession/LlvmJit; reusable execution and backend do not consult ambient environment. Native source/module completion events retain their real boundary. |

The task Outcomes and cli-lazy-progress-repair.json retain source/candidate/input
hashes, commands and independent checks. Traced embedding diagnostics and JIT
optimization policy experiments are historical bounded observations, not new
runtime semantics or proof that the entire old stall class had a single cause.
No deadline/heartbeat relaxation or mandatory noisy application stderr was added.
The area has no remaining in-scope implementation obligation; final frozen
candidate G2a/G2b, phase three and main/seed/carrier promotion remain uncertified.
