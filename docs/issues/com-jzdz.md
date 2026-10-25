---
id: com-jzdz
status: closed
deps: [com-wrjh]
links: []
created: 2026-10-25T10:39:41Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Preserve forbidden function returns through loop completion


## Confirmed Review Finding

P1 finding F1 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/04 diverge functions cannot return; spec/11 analytical loop continuation remains separate; body-checking section4.

**Actual:** Loop-bodied return is accepted by check and AOT. LLVM emits ret void in the callee and unreachable after its invocation. Direct/if return rejects. No undefined-behavior application execution was attempted.

**Source chain:** `src/SourceCompletion.pw:76-81; Codegen/Check/Return.pw:257-265`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `flow/diverge-loop-return.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Preserve invocation-level source return facts through loops without changing analytical warning/continuation semantics. Reject all forbidden returns in diverging named/closure bodies before successful publication; retain valid loops, warned source returns and closure target isolation through final Mid/LLVM.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.

## Implementation Boundary

The shared completionLoop now retains invocation-level source Return/Diverge
edges while always keeping source Normal after a loop. Execution edges and
loop-local Break/Continue consumption are unchanged. Source-normal is the
continuation/diagnostic criterion; a possible Return is independently available
to the existing diverging-body contract. Both the syntax walker and saved source
recording use this composition; no extra AST walk or special consumer is added.

The original internal source_completion_channels fixture (a31af25a) asserted
absence of source Return to represent continued source typing. Its actual intent
is to avoid turning loop noncontinuation into source divergence. Correct that
internal expectation to Normal+Return and retain the continuation assertions;
this is permitted internal fixture maintenance, not a language change.
New controls include nested/may-skip/warned source returns, diverging closure
and closure-construction isolation, plus native ordinary loop return semantics.
Loop-producer scoped validation and independent review are complete below;
the task's full forbidden-return contract remains incomplete.

## Scoped Verification and Remaining Required Dependency

Production/fixtures7ac54779, candidate bin/plewc-loop-source-exits SHA256
09d1dfc76d61eab22b00d30d5807c2b375eba543b3b68876b116a7f728bdec2f.
Standard build20261025T105937-build-4a5ddd exits0 with6020 fixed inputs.
Old073f incorrectly accepts all6 new check-only rejects; new candidate passes
native11/reject20 plus14 check/run contrasts. The actual closure-boundary,
loop-return values, source/execution fields, saved completion and Mid target
readers retain their expected results. Independent
loop_exit_repair_completion_review accepts this loop-producer repair scope.

Same-source alternating diagnostic medians old073f5.900369s/new09d1 5.921351s,
all8 actual LLVM outputs match,6020 inputs fixed. The 0.021-second difference
is diagnostic observation, not a formal regression/speedup or G2a certification.
The implementation adds only a fixed-size source exit mask/union per loop,
with no new walk, payload field, copy, allocation or downstream selector.

The covered-arm dependency com-wrjh is now resolved by the independently
accepted source-owner admission below. The loop-producer evidence remains
valid for its finite scope; the full prohibition no longer relies on that
aggregate summary.

## Independently Accepted Repair

Resolved at production/fixtures a9556c25, candidate
bin/plewc-return-owner-admission SHA256
7f4dbc4f8b4930baf09eea79c07367888577abcb10b2c87a102845dbe8be33fb.
The sole direct-transfer recording boundary now selects a return target using
its actual source owner and declared invocation contract. Global owners reject;
diverging function/closure owners reject independently of arm coverage.
checkDivergingBody no longer infers forbidden returns from live completion joins;
it retains execution fallthrough checking. Valid target facts and immutable
publication still authorize the actual Mid return and cleanup consumers.

Standard build20261025T112941-build-ac44b7 exits0;6038 inputs fixed.
Native9/reject27 and check/run18 pass, including cached owner failure, failed
reader admission, valid global closure execution, ordinary covered returns,
closure isolation, loop completion and actual saved-target Mid consumers.
The first never-green mode diagnostic driver incorrectly expected --run to
check an unused body; its failure is retained. The corrected control preserves
that lazy success and separately requests the invalid body, which rejects.
No maintained fixture expectation or source rule was weakened.

Independent source_return_owner_completion_review accepted com-wrjh, com-nr7y
and com-jzdz individually at their finite scope, tracing producer to final
consumer/failure and checking actual outputs and source hashes. Same-source
alternating diagnostic medians old09d1 5.948563s/new7f4d 5.947388s,8 LLVM
outputs identical,6038 inputs unchanged: no slowdown evidence, not a formal
G2a or speedup claim. Full E3/G1/G2/G3 and phase three remain open.
Durable report, sources, raw results, initial driver failure and coverage:
meta/evidence/existing-feature-conformance/source-owner-facts/
return-owner-admission-repair.json.
