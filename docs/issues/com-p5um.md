---
id: com-p5um
status: open
deps: [com-61jt]
links: []
created: 2026-10-23T10:41:59Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Verify the frozen candidate fixed point and formal self compilation time

## Boundary

Phase 3G / G2a. **Final standard gate.** Parent criteria: 10.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `scripts/diagnostics/measure-self-host.sh`; `docs/issues/met-si6j.md`.

Use meta ./validate self-host with the explicitly recorded validated carrier and frozen G1 inputs. Preserve generation transition LLVM/runtime comparisons and all adopted-generation runs. Record the measured compiler/hash for G2b; no concurrent build/test or diagnostic instrumentation.

## Exit and Evidence

Standard gate exits0 with unchanged inputs, fixed point and formal median below 7 seconds. Investigate any observed regression with matching-source conditions, fix easy extra copies/searches and return repairs to their owning task; stop if the adopted limit cannot be repaired. Do not promote seed/carrier or merge main here.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
