---
id: met-nm2t
status: closed
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

## Measurements and bounded disposition

Count-only LLVM22/O0 on fixed self-source: template queries85164, argument rows115852; cache queries85164, comparisons111906 (~1.31/query), hits0. Native0/probe-construction inputs unchanged (native-target pre/post fingerprints were not collected), LLVM exactly equals prior counter-free-equivalent target. No dominant long linear scan was found; do not add a hash index from these counts. This corpus does not prove cache hits are unnecessary for other programs. [counts](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/call-metadata/counts.json).

Both private query signatures still carry complete Comp (and cache helper complete MidBuildState), but need only published argument/operand pools, or current callValues plus exact CallSiteKey.sameKey. Each has one actual caller, buildMidCallEvaluation/materializeMidCallValue. CoW snapshots must be per-call and not retained across later publication. Frozen pool reader construction stays with Comp; no raw callback or writer. The admission query experiment is measured first before selecting another input-only repair; counts alone do not certify elapsed benefit. Independent disposition review completed; investigated closure, with input-only repair still owned by com-i86w and no product-performance claim.

Independent review supports rejecting a dominant-long-scan/indexing claim, with no product changes. Recorded counter-input scope is construction-only, not whole native target; peer path/hash added and future runner extended. No retroactive guarantee. Counts omit maximum/distribution; zero hits cannot justify cache removal.
