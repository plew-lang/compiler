---
id: com-p5um
status: open
deps: [com-61jt, com-auvx]
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

## Historical Gate and Current Refresh

Independent c2_classification_review accepts the standard gate
20261025T034133-self-host-290b80 at source 3aef0546 (production b6645ac1,
fixture 7e0648c1). Exit 0 and 5,972 unchanged inputs match G1, tools and fixed
Syntax. Generation 1 -> 2 changes LLVM; generation 2 -> 3 matches LLVM and
runtime exactly. All three fixed-point measurements emit identical outputs:
6.468564 / 5.954835 / 5.924573 seconds, formal median 5.954835 seconds.
No diagnostic sampling or overlapping build/test was used.

Measured compiler: meta/tmp/validation/20261025T034133-self-host-290b80/self-host/generation-2/next/plewc,
SHA256 73078e5da70d0c96647f30efd78cdf3f73aad462e01ae3d6fab92d3471980578.
The generation 3 successor has the same hash. G2b uses this exact measured
compiler, starting only after the formal gate completed.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-self-host.json
retains all measurements and raw references. G2b, phase three and main/seed/
adopted-carrier promotion remain uncertified.

Production com-6cw6 changed the frozen inputs after the recorded gate. This
task is reopened: the result above remains valid for its recorded input only.
After refreshed G1 admission, rerun standard self-host with the unchanged
adopted carrier and use its new measured compiler for G2b.
