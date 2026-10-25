---
id: com-cwu1
status: open
deps: []
links: []
created: 2026-10-25T10:39:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, verification]
---
# Check complete dynamic call arguments before source publication


## Confirmed Review Finding

P1 finding CALL-3 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/03 immutable val and inout mutable-place rules, spec/02 literal ranges, spec/04 complete callable parameters; frontend-handoffs full source signature.

**Actual:** Existential inout call accepts immutable val, AOT succeeds and changes 4 to5. Missing inout, String for I8 and out-of-range300 pass check then fail later; unsuffixed valid4 lacks context, while4I8 succeeds. Concrete and mutable controls distinguish the defect.

**Source chain:** `src/Codegen/Resolve/Expr.pw:1218-1236; Codegen/Check/Call.pw:349; Codegen/Check/Obligations.pw dynamic selection`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `calls/dynamic-inout-immutable.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Apply shared full signature/context/type-range/passing/mutable-place admission to the selected dynamic requirement before sealing. Retain complete checked parameter and result evidence through descriptors, Mid and AOT/JIT; keep invalid dynamic calls out of successful source artifacts.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
