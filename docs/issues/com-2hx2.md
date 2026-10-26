---
id: com-2hx2
status: open
deps: []
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [frontend, verification]
---
# Map phase three semantic decision APIs and their actual authority

## Question and Boundary

Produce a bounded map of the actual phase-three semantic decision APIs, not a
claim that current responsibilities are correct. Read [phase-three criteria](met-si6j.md#completion-criteria),
[name lookup](../design/name-lookup.md), [body checking](../design/body-checking.md),
[handoffs](../design/frontend-handoffs.md) and the lexical audit met-tfbl.
Existing completed maps remain evidence only for their actual revisions/scope.

## Actions

Trace current source entries for declaration admission, lexical/candidate lookup,
visibility, callable classification/applicability, inference/conversion/proof,
completion, publication/instantiation and final Mid/backend consumers. Include
ordinary, default/provided, synthetic/gen, global and closure owners where these
same responsibilities execute. Start with the functions/files in met-tfbl and
follow callers/readers beyond its four repair proposals.

For each decision boundary record: contract owner, concrete API/constructor,
inputs and retained capabilities (including fields/captures/globals/Comp),
produced identity/fact/failure, downstream readers and competing entry paths.
Distinguish source acceptance from independent representation verification.
Index iteration and diagnostics are not violations merely because they use names.

Compare the map to existing area/task claims. Enumerate inspected versus missing
entries and assign finite audit batches for com-sn9w. Bound batches before
execution; split oversized ones instead of one unbounded whole-compiler audit.
Use current evidence when applicable, not an automatic rerun of all old probes.

## Exit and Evidence

A revision-pinned entry-to-final-use map and finite audit scopes cover the
semantic phase-three criteria; gate-only obligations retain their existing
G2/G3 evidence owners. Exclusions have contract grounds. Missing knowledge is
explicit, not marked compliant. Independent review checks the inventory against
real entry points rather than the original eight-family checklist. No compiler
repair, task closure re-admission, new feature or new architecture is included.
