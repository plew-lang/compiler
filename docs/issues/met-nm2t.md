---
id: met-nm2t
status: in_progress
deps: []
links: []
created: 2026-11-28T15:29:25Z
type: task
priority: 1
assignee: Koji Murata
parent: com-i86w
tags: [mid, performance]
---
# Measure Mid call metadata snapshots and cached-result scans


## Finite investigation

Measure midTemplateArguments and midCallValueForSite on the fixed self-source after selected Array/admission boundaries. Questions: actual calls and selected template argument count, cached-result query hits/misses and exact comparison iterations; whole Comp/state snapshot traffic versus necessary pool/key data. Inspect all direct/delegated reads and actual callers. Preserve all semantics, no product implementation in this investigation. Existing com-i86w owns both APIs; a justified finite repair is assigned before any code change. If traffic is negligible, close investigated, not optimized. No source inference/selection/ownership/cache validity weakening.

Evidence delivery: private count overlay+inputs/results, generated LLVM equality against uninstrumented-equivalent fixed corpus, bounded interpretation and independent review. Counts do not imply time; expensive-looking source is not proof of dominant elapsed cost. Candidate repairs need targeted controls plus same-source non-instrumented comparison. Parent/evaluator closure is excluded.
