---
id: com-s5k5
status: in_progress
deps: []
links: []
created: 2026-10-24T10:42:22Z
type: task
priority: 1
assignee: Koji Murata
parent: com-m3c6
tags: [frontend, ir, verification]
---
# Privatize canonical type rows and child pools without changing scalar reads


## Boundary

Finite D4 repair, parent criteria2/3/8, about1–2 active human working days.
Independent allocation reviewer `/root/body_receiver_completion_review` approved
this split at `0c1a680c`: hiding the9 canonical type storage arrays closes a
concrete bypass without widening into unrelated Arena/global storage.

## Evidence and Target

`Arena.typeTerms` and8 type child pools are `pub mut`; an external internal
client can replace a published scalar row or child slice and diverge from the
private TypeRef mirror despite the permanently closed declaration batch.
`type_term_rows_private` is the minimal compile-admission control. D4's dedicated
private apply writer alone cannot prove this stronger backing invariant.

## Entry and Action

- `src/Ir.pw` / `src/Ir/Types.pw`: privatize typeTerms and typeArgumentPool,
  typeRecordLabelPool, typeRecordFieldPool, typeViewIdPool, typeViewSourcePool,
  typeArgumentLabelPool, typeAssocArgumentPool, typeAssocArgumentLabelPool.
- Add scalar TypeTerm/count and element readers, without returning whole arrays
  or owning TypeRef snapshots. Preserve zero sentinel, array bounds and range
  indexing; existing register/batch APIs remain the only writes.
- Migrate external source and internal-test reads (initial search approximately
  306 references). Search all actual writers and retained raw public aliases.
- Preserve private initial batch mutation, both representations, normal late
  appends and C3's selected nominal source identity. Do not rerun candidate
  selection or add compiler-specific ownership suppressions.

## Exit

- Raw scalar and8pool mutation/access are rejected through API privacy controls;
  each family has a distinct rejecting fixture so one error cannot mask another.
- No external raw storage reads/writes remain; new readers return scalar/element
  values and no growing pool snapshots.
- D4 invalid/duplicate/reverse batch, post-publication/post-append, metadata,
  branch and source-dependency controls plus relevant C3 source/receiver controls
  pass with a freshly built compiler. Record before/after/carrier/input hashes.
- Fresh full compiler sourcecheck and formal fixed-point/performance below7s;
  investigate any measured overhead and stop if difficult to fix. Final full
  suites remain G2a/G2b.
- Independent completion review; synchronize design, D4 map and worklog.

D4 and G1 require this repair. This child does not depend on its parent and
creates no graph cycle. Surface language/spec semantics are unchanged.
