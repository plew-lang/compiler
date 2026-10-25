---
id: com-y8l4
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
# Compare full canonical trait requirement signatures for duplicates


## Confirmed Review Finding

P2 finding CALL-4 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/07 concrete type overloads; spec/08 overloaded requirements; name-lookup semantic signature identity.

**Actual:** Unused trait requirements accepting Box[I64] versus Box[Bool] are falsely called duplicates. Array[I64]/Array[Bool] requirements and ordinary Box overloads pass.

**Source chain:** `src/Codegen/Check/Duplicate.pw:58-85`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `calls/trait-generic-overload.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Use the declared canonical parameter/signature contract, including nested generic identity and modes/labels where applicable, for duplicate requirements. Retain true duplicate rejection and ordinary trait conformance/dispatch validation; do not create a special exemption for Box.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
