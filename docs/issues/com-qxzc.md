---
id: com-qxzc
status: in_progress
deps: []
links: []
created: 2026-10-24T18:51:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, frontend, mid]
---
# Project source call identity and result recipe without full templates


## Boundary and Evidence

Current bd2ed7dc production sample shows callTemplateAt65/readSourceOperationTemplate41
top samples; diagnostic only, not formal. Machine code retains272B CallTemplate
and280B Optional copies/variant ARC. See meta/evidence/performance-six-seconds/minimal-query-profile.json.

Project existing siteKey/resultTypeRecipe/mayHaveStorageArguments from the same
owner-local row. No additional semantic store or memo; no kind reconstruction.
Keep active/building/succeeded/failure directory routing, cached reader session
and owner checks, exact sameKey panic, absent site defaults and error order.
Only scalar consumers change; kind users keep full readers. Do not extend Mid
copy optimization or alter ARC/drop rules.

Build from saved fixed-pointd0654cb3; compare fresh with bd2 on the same source.
Require sourcecheck, affected source/result/storage/Mid controls, dedicated
active/sealed/missing/foreign-cache projection contrasts and independent review.
If a material improvement appears, run standard formal self-host alone. Preserve
all three times and fixed-point evidence; latest6.051333 is not below6.
