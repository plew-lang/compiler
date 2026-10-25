---
id: com-sby0
status: open
deps: []
links: []
created: 2026-10-25T10:39:43Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Normalize Unit return contracts across source checking and lowering


## Confirmed Review Finding

P2 finding F3, F4 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/04 omitted result equals explicit -> (), ordinary Unit values and permitted Unit fallthrough. Body-checking uses canonical result types, not syntax-shaped tests.

**Actual:** Implicit Unit return of a call/local/block is rejected while named explicit result permits it; closure Unit return also depends on literal shape. Conversely explicit -> () {} named function rejects fallthrough while omitted and closure forms succeed. check/build/run contrasts reproduce both failures.

**Source chain:** `src/Codegen/Verify/Stmt.pw:127-129; Codegen/Verify/Func.pw:76-81; Codegen/Verify/Expr.pw:97-120; Codegen/Check/Return.pw:272-278; Codegen/Resolve/Record.pw:2639; Mid/Build.pw:3501-3515`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `flow/unit-return-call-implicit.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Use one logical callable result contract for named/closure omitted/explicit Unit. Perform value compatibility by saved semantic types, normalize body signature and Mid return destination/fallthrough accordingly. Close F3 and F4 together; adding an AST exemption or only suppressing the first verifier error is insufficient.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
