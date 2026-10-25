---
id: com-jzdz
status: in_progress
deps: []
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
Validation and independent completion review are pending.
