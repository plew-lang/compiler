---
id: com-ra96
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

## Selected Implementation Slice

Use the existing static requirement argument-applicability algorithm with an
explicit canonical trait bound for existential candidates too. Select the full
name/label/type frontier, diagnose multiple complete matches, preserve one provisional
label-only representative for ordinary argument diagnostics, and retain the
chosen requirement/interface proof for existing final consumers. Extract the
bound-input matcher from static proof projection rather than duplicate a
dynamic matcher. Remove the redundant Mono-named selector wrapper: its only
caller is source protocol recording, which must use the same source selector.

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
