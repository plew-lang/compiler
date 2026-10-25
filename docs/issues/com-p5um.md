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

## Outcome

Independent c2_classification_review accepts the refreshed standard gate
20261025T050217-self-host-8da5f2 at source8997fa7e (productionb16439fa,
fixture573ff620). Exit0 and5,982 unchanged inputs match G1 and actual files.
Generation1 ->2 changes LLVM; generation2 ->3 matches LLVM/runtime exactly.
All measured outputs match. Timings6.460528 /6.179747 /5.886134 seconds give
formal median6.179747 seconds, below7. No sampling or overlapping validation.

Measured compiler: meta/tmp/validation/20261025T050217-self-host-8da5f2/self-host/generation-2/next/plewc,
SHA256 2d7c785b55fa33ffc143b749a8f17986c437521140e2abf4d80687b59e5a3c49.
The generation3 successor has the same hash. G2b consumes this exact compiler.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-self-host.json
retains all timing/artifact references. Old gate5.954835 remains in Git/raw
history and is not a same-source comparison. Full suites, parent completion
and main/seed/adopted-carrier promotion remain uncertified.

The final generator gate exposed com-v1wa/com-tkz7 after this measurement.
Those production repairs reopen this task; the recorded6.179747 gate remains
historical input evidence, not new-candidate certification. Refresh after G1.
