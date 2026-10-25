---
id: com-zy6r
status: in_progress
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

## Selected Implementation Slice

Compare complete canonical Array terms, including nested child arguments, in
ordinary free-call and grounded method argument applicability. Contextual
literals retain the existing contextual candidate path; do not reinterpret an
already typed argument from its element spelling. Reuse canonical typeRefEq
and preserve saved selection through concrete final calls.

Validate each finite task separately, including declaration-order contrasts,
negative/ambiguous cases, retained selected identity and actual AOT/JIT results.
Each task needs its own independent completion judgment; grouping the build
does not merge or weaken the three issue contracts.

## WIP Checkpoint and Planning Stop

Production source WIP a22670c5, initial candidate
bin/plewc-overload-identity-wip SHA256
b0f8cccb49deb0dc3fb271c62b1e044f8a4201b3f0216f6958987ddd6a9429a5.
Build20261025T115647-build-2eb137 passed with before/after input identity;
one new never-green positive fixture was corrected after build to separate
FirstWorker/ReversedWorker instead of defining overlapping impl signatures
on one type. Compiler source was not edited during/after that build. The
current eight bounded --check contrasts pass expected source acceptance or
rejection, but no target native/JIT/milestone/formal performance gate was run.
Do not treat source acceptance as actual dispatch or complete evidence.

Independent overload_identity_completion_review finds the direction consistent
with design but cannot certify this task before its final-consumer/mode gates.
It confirms a separate existing generic selector-group admission violation,
[met-g53w](met-g53w.md), on old/new candidates with6 check-only contrasts.
That new required task is connected to met-ucze and G1; it is related to
com-y8l4 without a false ordering dependency. The user-requested task-omission
stop applies. This task stays in_progress; no new group-contract fix was made.
Durable checkpoint: meta/evidence/existing-feature-conformance/source-owner-facts/
overload-identity-checkpoint.json. Earlier independently closed return-owner
and dynamic-argument tasks remain complete at their exact scope.
