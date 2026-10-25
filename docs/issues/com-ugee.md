---
id: com-ugee
status: in_progress
deps: []
links: [com-bkqq]
created: 2026-10-25T08:52:16Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Require an actual value producer in analytically nonterminating value blocks

## Contract and Scope

Required phase-three repair under [E1](com-2suv.md), [completion](com-fuo8.md)
and [met-si6j](met-si6j.md), found by [independent completion re-review](com-bkqq.md).
Parent criteria 1, 2, 5, 6 and 8 are affected. Existing block, if and match forms
only; no new loop-expression syntax, Never type or change to the adopted rules.

[spec/11](../../../spec/spec/03-expressions/11-control-flow.md#値利用と発散) and
[Body Checking section 4](../design/body-checking.md#4-blocks-branches-patterns-and-completion)
separate source completion from analytical execution reachability. An expected
type is context, not a value producer. Analytical nontermination does not supply
a required region's static result or excuse its missing give. Ordinary function
return completeness is a separate contract: a declared I64-returning function
whose body never reaches its end remains valid.

## Reproduction and Responsibility

At production043e2402, reviewed compiler dab97d52/meta58c9713d, exact candidate
bin/plewc-phase3-final SHA256
3c532ce1c7d1e2b0be6bc1c24b8c215a92be87625c65f531a0d83dc1719830b1:

```plew
fn body() {
    val x: I64 = { while true {} }
}
fn main() {}
```

--check incorrectly exits0. Removing the annotation rejects with cannot-infer.
The if and match value-region equivalents also incorrectly exit0. while is
already supported; this does not rely on absent loop-expression syntax.

Source path: Resolve/Record.pw::recordValueBlock (1176-1189) initializes
resultTerm from expectedTerm and saves it even without a give producer.
Verify/Expr.pw::verifyExpr (488) and checkBranchYieldsValue (827-833) use
Check/Return.pw::blockCompletesNormally (75-77), which reads execution.normal().
Thus a loop keeps source.normal=true but execution.normal=false, and the
required-give check is skipped. The declared expectation becomes a purported
result instead of remaining construction context.

## Required End State

Close actual result production, publication and all final readers at one shared
value-region boundary. Source completion, an admitted give/result producer and
its complete compatible term must justify a published normal value; an expected
type alone must not. Single blocks and block-bodied if/match arms consume that
same result. Remove the competing execution-reachability decision for this
source obligation, rather than add three syntax-specific guards or a later
verifier-only patch. Preserve the separate execution-based function-return and
Mid cleanup/ownership analyses.

## Exit and Controls

- Reproduce annotated/unannotated plain-block, if and match missing-give cases,
  then reject each for the missing source result, including dynamic conditions.
- Preserve loop followed by give (warning plus ordinary static typing), normal
  function declared-return nontermination, valid return/break/continue branches,
  source-diverging value rejection and incompatible warned-about give rejection.
- Show producer -> sealed fact -> explicit instance -> Mid/LLVM readers, removed
  competing decisions and missing/foreign/published-result controls.
- Preserve existing expectations and verifier strength; perform affected fresh
  checks, independent task/area review, readmit G1, and run the necessary final
  candidate G2 gates before G3/parent closure. Existing3c gate success remains
  valid evidence for that binary only, not for the repaired candidate.

The review receipt retains all11 check-only controls and hashes. No infinite
loop was executed. The two absent loop-expression controls are classified as
unsupported, not proof of this defect. Implementation is in progress: source result admission and result-term production move to the common Record value-region boundary; Verify's independent missing-give decision is removed. New source rejects and producer/publication controls are being verified.
