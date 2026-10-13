---
id: met-rzt4
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [frontend, jit, diagnostics]
---
# Recheck historical parser recovery and compiler-session JIT stalls

Retained independent investigation from type-checking remediation. Historical reserved-identifier/match/trait recovery could stall until the 60-second watchdog; a compiler InternalSession JIT execution aborted after the selected-body/final-call authority migration. Neither is established as a current-tree defect by the documentation migration.

Recheck exact historical inputs/revisions and watchdog output in [migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) and the [final-call-authority record](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/final-call-authority/README.md) (compiler 1a2ed6b6); separate parser recovery/progress from JIT dependency/abort ownership. Do not infer the _memcpy issue (com-8w4c) is the same failure.

Acceptance: minimal current controls, bounded termination or actionable error, failure-state propagation, and specific implementation/evidence if still reproducible. Do not weaken watchdogs or turn unfinished investigations into source restrictions. Route discovered responsibility changes to separate tickets if necessary.
