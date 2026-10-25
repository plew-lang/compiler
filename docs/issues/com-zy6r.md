---
id: com-zy6r
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
# Retain nested array element type identity in overload applicability


## Confirmed Review Finding

P2 finding CALL-2 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/06 invariant generic types and spec/07 complete concrete overload discriminators; types-and-evidence canonical term identity.

**Actual:** A fully typed Array[Box[Bool]] is rejected if Array[Box[I64]] overload is declared first; reversing order succeeds and executes20. Direct Box and simple Array controls pass.

**Source chain:** `src/Codegen/Resolve/TypeRecovery.pw:238-243; Codegen/Resolve/Module.pw:299`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `calls/array-nested-original.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Compare complete canonical array element terms in source applicability rather than element head spelling. Preserve explicit types and valid forward-context inference, use private candidate probes, and verify saved chosen call through both declaration orders and final execution.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
