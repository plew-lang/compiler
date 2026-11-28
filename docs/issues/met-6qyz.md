---
id: met-6qyz
status: closed
deps: []
links: []
created: 2026-11-28T10:19:27Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [performance, diagnostics]
---
# Measure current self-compilation hotspots and rank recovery candidates

Measure the current noninstrumented compiler on one fixed compiler-source corpus. Identify absolute expensive phases and sampled function costs, inspect actual operations for repeated work/search/copies, and separate confirmed observations from unmeasured optimization hypotheses. This is a finite investigation, not an implementation or formal performance gate. Preserve source behavior, all verifier checks, user manifest/bin and existing stage3 WIP.

## Acceptance Criteria

Fresh repeated phase measurements, CPU windows covering front/middle/tail with exact symbol provenance; carrier/source/input/output hashes; bounded source-backed candidate assessment with next verification and ownership; independent review; retained evidence and owned follow-ups. Do not infer whole-run percentages from partial CPU windows, claim raw equality from symbol-normalized comparison, or prescribe large changes from unresolved costs.


## Findings and ownership

Evidence: meta projection-members/performance-recovery/current-costs/README.md
and provenance/phase/CPU/count records. First supported next experiment is
met-b775 (same original canonical ownership-analysis reuse). met-hw4n owns
publication/reread cost investigation. Existing com-xc6h owns builder API
closure; no parallel authority or size-based API redesign is prescribed.
Predecessor and flag-prefix candidates execute0 times and are discarded for
this corpus. Investigation completion does not claim either optimization,
whole-suite green, formal fixed point or <=7.5 recovery.

Independent reviewer absolute_cost_review confirmed measurement limits, revised
candidate ranking after counts, and approved finite investigation closure.
The initial predecessor/flag candidates were rejected by zero counts; CPU-window
and LLVM/O0 limits are preserved. Closure reason: investigated. Final saved evidence revision: meta6ff870a7; issue/follow-up checkpoint:
compilerc976411f. Source being investigated: b669e60e candidate behavior
with only the documented comment difference. Reproducibility helper was run
and reproduced the exact CPU summary; all complete sample trees conserve
exclusive self counts. Successful duplicate outputs are deduplicated and
regenerable compiler IR retired per current-costs/retirement.json; necessary
inputs, raw samples, carriers/std and shared backend remain for follow-ups.
