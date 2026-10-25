---
id: com-nr7y
status: closed
deps: []
links: [com-wrjh]
created: 2026-10-25T10:39:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Reject function returns from global initializer source owners


## Confirmed Review Finding

P1 finding F2 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/11 return exits the enclosing source function; body-checking section4 and compiler-state owner identity. An implementation startup helper is not a user source function.

**Actual:** Global initializer return passes check/AOT. Emitted startup helper returns before storing the global, while main still continues. A closure-local return in a global initializer is valid and passes. No incomplete-startup native execution was attempted.

**Source chain:** `src/Codegen/Resolve/Control.pw:64-69; SourceFacts.pw:581-588; Mid/Build.pw:2608-2645`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `flow/global-return-branch.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Represent absence of an enclosing source function for global owners at transfer admission and refuse that return before publication. Preserve legitimate closure returns and actual saved target/cleanup mappings; do not solve this by changing global dependency planning.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.

## Selected Implementation Slice

Coordinate with com-wrjh at the existing direct-transfer admission boundary.
SemanticCompletionOwner.Global has no enclosing source-function return target;
reject it rather than use the synthetic startup helper. Closure owners keep
their independent invocation target even under a global initializer. Retain
normal global initialization, legal closure returns and final Mid/cleanup
consumers; verify failure prevents publication and check/AOT/JIT mode agreement.

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
