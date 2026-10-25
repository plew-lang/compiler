---
id: com-l8m1
status: open
deps: []
links: []
created: 2026-10-25T10:39:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve shared value region result conversions through final Mid


## Confirmed Review Finding

P2 finding T1 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/08 heterogeneous concrete injection into any; spec/11 common value-region rules; body-checking section4 compatible normal results and saved per-use conversions.

**Actual:** An explicit any Metric if/match with Small/Large gives passes check but fails AOT/JIT Mid type verification (Large into Small). Direct/block/homogeneous controls succeed. Later context refinement overwrites the common target with raw give type, then first branch wins; give assignment has no branch conversion.

**Source chain:** `src/Codegen/Resolve/Expr.pw:2346-2351,2389-2403; Mid/Build.pw:1758-1777,2719-2736; Codegen/Mono/Call.pw:6370`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `types/any-if-heterogeneous.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Close the shared result-use producer, immutable conversion/result facts, concrete conversion interpretation and Mid assignment. Preserve each branch actual type and common checked destination; do not retag a value or weaken Mid verification. Cover if/match/direct/block with heterogeneous layouts and equivalent context.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
