---
id: com-0k37
status: open
deps: []
links: []
created: 2026-10-13T01:03:55Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, driver]
---
# Reassess historical deep-expression compiler stall

Historical evidence: [deep input](../../../evidence/2026-10-01/compiler/orc-restart/restart-100/App.pw) and [watchdog record](../../../evidence/2026-10-01/compiler/orc-restart/restart-100/abort.json). The 2026-10-01 restart probe stalled before producing LLVM for a deep sum of 100 helper calls and watchdog terminated it after 60 seconds (exit 124); flat calls succeeded. Responsible parser/checker/backend stage was not isolated. Current reproducibility is unverified; do not classify this as an ORC failure or current demonstrated defect.

Reproduce with the recorded input and current compiler using standard bounded diagnostics. If reproduced, isolate the dominant stage and correct the responsible algorithm without weakening checking; if not, record revisions and decisive evidence. Link follow-up work and document input-shape scope before making general restart scaling claims. Related design: [Hot Restart decision](../design/decisions/hot-restart.md).

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Recheck the exact old deep-sum workload and flat control with the current compiler and standard watchdog. A reproduced stall is localized to its responsible current phase; a non-reproduction closes this historical investigation with evidence. It is not a reusable Hot Restart milestone.
