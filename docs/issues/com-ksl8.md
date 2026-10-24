---
id: com-ksl8
status: closed
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
## Outcome

Measured unchanged carrier090240dd... with existing monitored diagnostic
measure-self-compile: compiler/tmp/perf-six-baseline, exit0, sample intervals1s
and duration1s, wall7.400218s (instrumented diagnostic, not a formal median).
The3 samples again show shared Mid verification/instantiation/drop and ARC/array
floor. Existing formal baseline remains7.072914s, not replaced by this sample.

Ranked finite candidates: (1) com-9t8k's O(locals*statements) repeated result
scan, (2) flag initialization's full changed-loop/linear slot searches in Verify,
(3) repeated term instantiation under one immutable body/environment.
Closedness already has saved registration state and grounding has empty-
substitution fast paths; do not claim those as new improvements. Node-ID memo
is lower priority because freeze emits new IDs per occurrence.

Both independent read-only investigations agree on concrete repetition;
/root/body_receiver_completion_review accepts the first repair's boundary and
correctness controls. Select com-9t8k, preserving other candidates as measured-
contribution-unknown follow-ups. No performance target or implementation is
claimed complete by this investigation.
