---
id: com-ksl8
status: in_progress
deps: []
links: []
created: 2026-10-24T17:10:41Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, mid, verification]
---
# Measure common Mid costs and select a bounded optimization

## Finite Investigation

Read current Mid Verify/Instantiate/Drop/DataflowState and matching no-codegen
samples, correlate body symbols to source, and recheck the unchanged baseline
with diagnostic phase/sample measurements. Select concrete repeated computation,
CoW copies or scans with an input-validity argument; estimate contribution only
where measured. Do not add global caches across owner/environment/stage boundaries.

Deliver a ranked finite list, the chosen first producer/consumer repair, negative
controls needed to retain strict verification and an independently reviewed
implementation task. This investigation is not success at the below6s goal.
