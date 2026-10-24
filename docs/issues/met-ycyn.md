---
id: met-ycyn
status: closed
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
measurement when a material improvement is supported. An identity fast path is not permission to weaken type equality.
No change to source acceptance, ownership or code generation output is intended.

## Outcome

Production d461ba2c/4e716165, standard build20261024T183532-build-642634
from fixed-pointd0654cb3; freshbd2ed7dc sourcecheck and native18/panic2/reject8
all pass with unchanged inputs. Matching source old6.072105/new6.067694s,
all six LLVM outputs identical; difference is noise-sized, no speedup claim.
Independent b2 review accepted scope and rechecked referenced hashes/inputs.
Durable receipt: meta/evidence/performance-six-seconds/minimal-query-inputs.json.
Formal latest remains6.051333s, target unmet. No new formal run merely to select
a favorable fluctuation. No main/seed/adopted-carrier promotion.
