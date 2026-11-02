---
id: com-sh7q
status: open
deps: []
links: []
created: 2026-11-02T22:01:08Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, diagnostics, verification]
---
# Preserve resolver lock output failure before artifact publication

## Contract and evidence

[com-6lza](com-6lza.md) whole assignment review W3 identifies a finite required-artifact boundary, not a general logging defect. Resolver.runResolver writes writeLock output through the void @Std/Io.write channel. The current output runtime ignores fwrite completion/flush failure. A worker can therefore return zero after incomplete required lock output; native/tool.cpp resolve then commits PendingFile because checked sees only zero, and development plew do_resolve similarly moves the redirected temporary output. Atomic staging alone is not evidence of complete producer output.

Evidence: [B105 corrective entry review](../../../evidence/compiler-failure-audit/batches/B105.json), Resolver.pw154, std/Io.pw15, Backend.pw1386, native/tool.cpp154-160, plew75-83; [whole assignment review](../../../evidence/compiler-failure-audit/whole-assignment-review.json). Source-confirmed conditional path, not an executed disk-error or corrupt-lock reproduction.

## Guarantee and finite scope

The resolver's required lock artifact must report write/final flush failure as a non-source failure before publishing Plew.lock. Carry that result through standalone resolve-worker and the development resolver entry to both actual publication adapters. Preserve an existing lock on producer failure, and do not admit an empty/partial prefix as complete merely from worker zero. Keep normal empty-dependency lock output valid. Do not re-solve dependencies in the output consumer or substitute text heuristics for completion.

## Scenarios

- Successful nonempty and valid zero-dependency lock, using the actual worker and both adapters.
- Write failure before bytes, after a prefix, and final flush failure; no new committed lock and a non-success result retaining the output/tool origin.
- Partial bytes plus nonzero worker result, normal resolver source/input/tool refusal, and valid output versus malformed query output.
- Existing target preservation and absence of target at start; publication operation failure stays failure.
- needs-resolve-worker is a separate Bool query: native resolveIfNeeded accepts exact0/1 and rejects empty/invalid output. Do not label that path an already-proven publication defect.

## Excluded and completion

No all-print API migration, generic logging reliability, new resolver/dependency semantics, stable public CLI taxonomy, panic/recovery policy, arbitrary unsafe-pointer recovery or filesystem power-loss durability guarantee. com-x386 remains LLVM/runtime compiler text output only. Follow TDD with actual producer/consumer controls, preserve original error and ownership, run affected resolver/distribution/development entry checks and obtain independent review. Saved source evidence and this assignment are not product GREEN.
