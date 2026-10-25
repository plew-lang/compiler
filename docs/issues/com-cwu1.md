---
id: com-cwu1
status: closed
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

## Selected Implementation Slice

Project an already selected dynamic existential requirement through the existing
SourceCallParameterState.Selected/SourceCallSignature.Trait boundary. Consume
the retained interface source proof root and canonical requirement slot, not
fresh overload/witness lookup. Existing Record argument-context completion and
Verify shared literal/type/access-mode/mutable-place checks then consume the
same signature as ordinary calls. Source template closure also validates full
parameter compatibility and access modes from that projection before seal;
final dynamic descriptor and Mid consume the existing frozen argument plan.
No new call-family-specific type checker or per-syntax exception is planned.
Closure call controls and selected dynamic type/conversion/instance controls
remain part of validation; overload candidate selection itself is com-ra96.

## Independently Accepted Repair

Resolved at production/fixtures1cff794a; bin/plewc-dynamic-argument-admission
SHA25623f7d582501b394f3390fbd9e2ebd577cc9892cf6c7de4d5129b70ae5f14b583.
The canonical selected interface root and requirement slot now project through
SourceCallParameterState.Selected with the existing Trait signature. Record
context completion and shared Verify argument checks consume that projection;
source closure uses the same complete types/access modes instead of counts
alone. Descriptor and Mid readers retain the already selected identity and
argument plan. No separate dynamic checker, witness search or ABI is added.

Standard build20261025T114310-build-47b3d6 exits0 with6054 unchanged inputs.
Native11/reject17,check-run14 and associated-input check/AOT/JIT3 pass,
including immutable/missing/unexpected inout, wrong type/range, contextual
literals/blocks, generic and associated-type input, closure controls, failed
publication/cache/cursor and real interface descriptor consumers. Old candidate
7f4d accepted5 of6 new rejects; inout temporary was already rejected elsewhere.
Independent dynamic_argument_completion_review accepted this finite task after
source-to-consumer trace and actual output/diagnostic/hash checks, with no new
required findings. Same-source medians old7f4d5.945622s/new23f7 5.901033s;8
actual LLVM outputs identical,6054 inputs unchanged, no slowdown evidence.
This is diagnostic, not formal G2a or a speedup claim.

Durable receipt: meta/evidence/existing-feature-conformance/source-owner-facts/
dynamic-argument-admission-repair.json. Overload selection com-ra96, area
re-admission and new G1/G2a/G2b/G3 remain separately open.
