# Local Compiler Issues

Issue files are the canonical record of implementation gaps, unresolved design
work, and optional improvements. [Design](../design/README.md) owns adopted
contracts; issues link to those contracts instead of duplicating them. Current
work selection belongs in the meta worklog. This directory has no manual index.

Before starting every task, read the meta repository's required
[task-start TDD rules](../../../agents/development-workflow.md#タスク開始時に必ず読むtdd規則),
including their investigation, documentation and pure-refactor applicability.
That section owns the execution procedure; this document owns ticket contracts.

## Tool and Store

Use `scripts/issues/tk` from the compiler root, or its absolute path from any
working directory. The entry always selects this checkout's `docs/issues/` and
uses the [pinned upstream tool](../../scripts/support/vendor/ticket/README.md).
Do not invoke an unrelated global tk or override the store for project work.

```sh
scripts/issues/tk create 'Close a selected implementation boundary' -t task -p 2 --tags frontend
scripts/issues/tk ls
scripts/issues/tk ls --status=open
scripts/issues/tk ls --status=in_progress
scripts/issues/tk ls --status=closed
scripts/issues/tk show <id>
scripts/issues/tk dep <id> <prerequisite-id>
scripts/issues/tk ready
scripts/issues/tk blocked
scripts/issues/tk start <id>
scripts/issues/tk close <id>
```

`ls` includes all statuses in this pinned release; filter explicitly for open
work. `closed` is a recent, limited view; use `ls --status=closed` for all closed
issues, or `rg` over the files for historical searches. The upstream ID prefix depends on the invoking working directory and has no
semantic or repository-identity meaning. Keep generated IDs and
filenames stable, including after closure. Do not move closed files elsewhere.

## Record and Classification

Use tk's standard YAML metadata and types (`bug`, `feature`, `task`, `epic`,
`chore`). Use `bug` for an evidenced violation, `task` for bounded investigation
or implementation/design work, and `feature` for optional new capability.
Use `epic` only when existing child work needs grouping. Tags name affected
areas, such as `frontend`, `generics`, `mid`, `ownership`, `backend`, `runtime`,
`driver`, `diagnostics`, `verification`, and `tooling`; they are filters, not a
second status or severity system.

Priority is work ordering, not a claim that every issue is a defect:

- 0: immediate safety/data-loss or widespread unusability with evidence.
- 1: blocks the selected goal or violates a required correctness boundary.
- 2: ordinary actionable work or investigation.
- 3: useful improvement without a current blocking dependency.
- 4: deferred option requiring further justification.

Use an action-oriented title. Keep guarantees and limits in the body:

- Contract, problem and covered/excluded behavior, input shapes and modes.
- Decision owner, producer-to-final-consumer path and competing paths to remove.
- Scenario list covering the guarantee and preserved behavior; links to tests,
  expected-result grounds, actual paths and RED/GREEN results.
- Structural checks, independent review, required gates and real prerequisites.
  Investigations instead name finite questions, deliverables and follow-up owners.

Short lists and evidence links suffice; do not create another status ledger.
Distinguish confirmed defects from unverified cases. Add dependencies only for
actual prerequisites. Assignees, dates and estimates are optional.

Completion requires the contract from producer to final consumer, removal of
competing authorities, applicable gates and synchronized documents. Adding a
check or table is not completion. Reconcile all required scenarios with meaningful
executed assertions and structural evidence; do not silently drop required cases.
Use the [independent review procedure](../../../agents/development-workflow.md#独立レビューと完了認定)
to check expectation validity, detection strength and actual paths. A green suite,
coverage number or review receipt alone cannot certify completion.

Investigations may close with evidence and owned follow-ups, without claiming
repairs passed. Before closure, record the reason (resolved, investigated,
duplicate, unnecessary or deferred), revision, scope, decisive evidence, review
findings and their reasoned disposition. Use `closed` for all outcomes. Keep the
issue and links; Git retains history and evidence stores retain results.

## Integrity Limits

The CLI is a convenience, not a schema validator or concurrency protocol.
The pinned version accepts an out-of-range create priority such as 9 despite
its documented 0–4 range; it rejects an unknown status and a missing dependency
target in the focused probe. Review metadata values, dependency targets, links, and the Git diff before
committing. Use stable full IDs for dependencies. Concurrent edits to one file
can overwrite each other; reconcile the file before publishing changes.
Independent file creation does not prove same-file updates are safe. Do not
assume successful CLI exit validates all fields or references.
