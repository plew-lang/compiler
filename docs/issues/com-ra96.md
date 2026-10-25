---
id: com-ra96
status: open
deps: []
links: []
created: 2026-10-25T10:39:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Select existential overload requirements by full argument applicability


## Confirmed Review Finding

P2 finding CALL-1 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/07 overload labels and concrete types; spec/08 distinct requirements; name-lookup common applicability.

**Actual:** The first same-name/same-label requirement wins without checking types. I64/Bool requirement declaration order changes check/native acceptance; reversed valid order executes expected20. Concrete and bounded generic controls work.

**Source chain:** `src/Codegen/Resolve/Record.pw:498-506,540`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `calls/existential-overload.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Form and check the complete applicable requirement set using the common source-call contract; diagnose true ambiguity, preserve selected requirement identity/proof and do not rescan in Mono/LLVM. Validate both declaration orders, mismatches and final AOT/JIT dispatch.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
