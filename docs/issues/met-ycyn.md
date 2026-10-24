---
id: met-ycyn
status: in_progress
deps: [met-v1jg, met-7a8u]
links: []
created: 2026-10-24T18:32:09Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, mid, frontend]
---
# Minimize saved Mid query inputs and empty-view head comparisons


## Boundary

Formal navigation baseline generation2 compilerd0654cb3 reaches fixed point,
median6.051333s, no target claim. Two remaining measured local costs: unnecessary
168-byte MidBuildState arguments (optimized machine still forwards about120B,
not proven State-array ARC), and repeated empty-view head query work.

Private Mid SourceSemanticExpression/Type/Term consume only the same saved
facts/sourceFunction pair, not locals/blocks/return scratch state. Pass smallest
input directly at all44 callers. Keep admission/session/owner/global initializer
facts changes and Pending source call lookup; no cached projection/new store.
For type-head comparison, reuse both already loaded terms: only when all six
view metadata fields are empty may the existing view-set equality be elided.
Preserve bounds, nominal identity/binders/associated labels and nested views;
found-set membership can stop scanning, duplicate checks can be removed by proof.

Use the saved fixed point carrier bin/plewc-perf-navigation-fixed for build.
Separate commits per query family; same-source comparison against that carrier,
fresh source/type/Mid source controls, independent review, then standard formal
measurement. An identity fast path is not permission to weaken type equality.
No change to source acceptance, ownership or code generation output is intended.
