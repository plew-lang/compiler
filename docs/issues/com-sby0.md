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

## F3: Unit Return Values Must Use Semantic Compatibility

An omitted result and explicit `-> ()` denote the same logical result contract.
This valid call-result form currently rejects when the wrapper omits its result:

```plew
fn action() {}
fn wrapper() { return action() }
fn main() { wrapper() }
```

Unit local values and `return { give () }` show the same annotation-dependent
failure. Unit closures reject nonliteral Unit returns too. Literal `return ()`
and an explicitly annotated named wrapper are positive contrasts. Full sources,
check/build/run results and candidate hashes are in the review receipt under
`unit-results.json`, `unit-followup-results.json` and `mode-results.json`.

- [ ] F3: omitted/explicit named and closure Unit returns accept compatible
  literal/call/local/block values using saved semantic types, while non-Unit
  returns still reject. Remove the syntax-shaped `exprIsUnit` admission decision.

## F4: Explicit Unit Functions Must Permit Fallthrough

This explicitly Unit-returning function currently rejects with missing return:

```plew
fn action() -> () {}
fn main() { action() }
```

The omitted-result version, an explicit Unit closure and explicit Unit with a
bare return are positive contrasts. Spec/04 expressly permits Unit fallthrough.
The source signature's `hasReturnValue=f.hasRet` and final Mid result/terminator
handling must be normalized too; suppressing only the first error is not enough.
The separate F4 source and real mode outcomes are retained in the same receipt.

- [ ] F4: omitted/explicit Unit bodies have equivalent fallthrough behavior and
  valid saved signatures, Mid result destinations/terminators and AOT/JIT output.
  Non-Unit completeness and diverging-body restrictions remain enforced.

Both obligations belong to one canonical callable-result repair. This issue
cannot close with only F3 or F4 fixed; no artificial ordering dependency between
the two is introduced.

## Required Finite End State

Use one logical callable result contract for named/closure omitted/explicit Unit. Perform value compatibility by saved semantic types, normalize body signature and Mid return destination/fallthrough accordingly. Close F3 and F4 together; adding an AST exemption or only suppressing the first verifier error is insufficient.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.

## Shared Candidate Matching Interaction

The met-g53w intermediate independent review identified a related Unit argument
boundary during extraction of the shared candidate-local matcher. Canonical Unit
may be term0, while typeCompatibility(0,0) reports Unresolved. A Bool/Unit same-label
overload group with choose(value: ()) (and a Unit local) can therefore leave the
Unit candidate selector-only instead of fully applicable. Check free, method and
trait entries and both declaration orders with this repair. The previous method
matcher skipped expected0; preserve neither that blind acceptance nor a matcher-only
literal exception. Distinguish known Unit from absent type information at the
semantic compatibility boundary, and verify final argument/return use. This is a
reviewed affected boundary, not yet a newly reproduced independent issue or a
claim that met-g53w/this task is complete.

The first direct contrast (Bool/Unit method overload, literal Unit argument) passes
--check on old23f7 and newe6ff. It does not confirm the review hypothesis as a real
regression. The source/outcomes are retained in the structural-overload checkpoint;
local/call-derived Unit and final native/JIT remain separate required coverage.
