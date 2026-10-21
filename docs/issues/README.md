# Local Compiler Issues

Issue files are the canonical record of implementation gaps, unresolved design
work, and optional improvements. [Design](../design/README.md) owns adopted
contracts; issues link to those contracts instead of duplicating them. Current
work selection belongs in the meta worklog. This directory has no manual index.

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

Each body states the current problem/question, related design contract,
evidence (revision and inspected/verified scope), and completion conditions.
Distinguish a known violation from an unverified boundary. Do not turn every
uninspected combination into a mandatory bug. Record dependencies only when
one issue actually prevents completion of another. Assignees, dates, and
estimates are not mandatory.

For implementation work, completion requires the contract to hold from producer
to final consumer, removal of replaced paths and duplicated authorities,
applicable correctness/performance gates, and synchronized documentation. A
new check or saved table alone does not close the issue. Investigation can close
with findings and linked follow-up work without claiming the fix is complete.

Before closing, update the body with the reason (resolved, investigated,
duplicate, unnecessary, or deferred), revision/scope, and decisive evidence.
Use standard `closed` for all these outcomes; do not invent status variants.
Keep the issue and links after closure. Update the body for current truth;
Git retains the discussion/history, and existing evidence stores retain logs.

## Integrity Limits

The CLI is a convenience, not a schema validator or concurrency protocol.
The pinned version accepts an out-of-range create priority such as 9 despite
its documented 0–4 range; it rejects an unknown status and a missing dependency
target in the focused probe. Review metadata values, dependency targets, links, and the Git diff before
committing. Use stable full IDs for dependencies. Concurrent edits to one file
can overwrite each other; reconcile the file before publishing changes.
Independent file creation does not prove same-file updates are safe. Do not
assume successful CLI exit validates all fields or references.
