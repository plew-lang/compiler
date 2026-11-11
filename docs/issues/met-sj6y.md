---
id: met-sj6y
status: in_progress
deps: []
links: []
created: 2026-11-11T02:38:30Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, performance]
---
# Restore read-only contracts changed solely to avoid value copies


## Scope

Restore independently measurable API units whose history shows a writable
receiver or argument was introduced only to avoid physical copying. Keep
ownership/lookup improvements that have independent design reasons. Preserve
actual mutations, semantic checking and later source-owner behavior. Work from
historical diffs and today's transitive call graph; do not revert whole commits.

First unit: `Comp.semanticClosureCount`, changed by ab1e958e. It reads a single
count and does not call another mutable reader. `semanticClosureAt` now also
routes through owner-local construction metadata; verify that dependency before
restoring it. The removed Snapshot API is not reintroduced.

Use the saved current carrier as the fixed input for builds. Compare prior and
restored compiler on the same final source, alternate order after warmup, check
exact LLVM output and existing closure or source-fact AOT controls. Accept
small/no regression; leave clearly slower or unvalidated units unadopted.
Record each scope, verdict and revision. No main/seed promotion.

## Sequential restoration

- `Comp.semanticClosureCount`: restored. Standard build
  `20261111T023910-build-9e5089` produced the same executable SHA-256 as
  the baseline. Same-source medians 8.107381 and 8.111118 seconds, eight
  identical raw LLVM outputs, two existing closure AOT controls passed.
  The independent review covered the receiver contract, fixed-input receipts
  and the targeted controls.
- `Comp.callTemplateIndex`: restoration tested and reverted. Standard build
  `20261111T025329-build-aedfd2` and two AOT controls passed. Same-source
  medians 8.093618 and 8.489046 seconds; all three matched pairs slower,
  eight equal LLVM outputs. Raw LLVM and ARM64 prove a Comp snapshot is
  inserted and survives optimization at a representative call. Resume
  restoration after generalized safe read-home forwarding covers this path.
- `Comp.currentSourceOwner`: restoration tested and reverted. Standard
  build `20261111T030227-build-5d8f16` and two AOT controls passed.
  Same-source medians 8.096866 and 10.213079 seconds, all three pairs
  slower, eight equal LLVM outputs. Raw LLVM and ARM64 again show a Comp
  snapshot surviving optimization.
- `SourceFactDirectory.matchOwner`: restored. Standard build
  `20261111T031131-build-c6ab26` and two AOT controls passed.
  Same-source medians 8.117086 and 8.129869 seconds, mixed pair direction,
  eight equal LLVM outputs. No clear regression.
- `SourceFactDirectory.state`: restoration tested and reverted. Standard
  build `20261111T031956-build-264c4e` and same-source comparison passed.
  Medians 8.141385 and 8.573201 seconds, all three pairs slower, eight equal
  LLVM outputs. A whole-directory temporary survives optimization. This
  blocks the dependent readers below. No AOT control was run for the
  rejected trial.
- `SourceFactDirectory.inactiveBuilder`: restored to the c390b418
  read-only receiver. Standard build `20261111T032603-build-4e100a`
  and two AOT controls passed. Same-source medians 8.154263 and
  8.149342 seconds, mixed pair direction and eight equal LLVM outputs.
- Next independently measurable unit: the `Comp` argument of
  `declarationCallHasStorageArguments`.
- Restore callers after their read-only prerequisites. Check the source owner
  state/outcome/prepared path, expression/statement/parent and closure
  construction path, and operation/call-template constraint path. Keep the
  current owner-local routes and their explicit cache mutations. Preserve
  mutable receivers that change the constraint graph or active builder.
