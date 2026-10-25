---
id: com-wrjh
status: closed
deps: []
links: [com-nr7y]
created: 2026-10-25T11:09:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Validate diverging return contracts in unreachable match arms


## Confirmed Contract and Reproduction

Found during independent completion review of [com-jzdz](com-jzdz.md).
The previous073f and loop-repair09d1 candidates both incorrectly accept:

```plew
diverge fn stop(flag: Bool) {
    match flag {
        _ => { while true {} }
        true => { return }
    }
}
fn main() { stop(flag: true) }
```

All probes used --check only; no application or infinite loop was executed.
Covered return: old/new exit0. Reachable-return contrast: both exit1 with
cannot-return diagnostic. Covered nonreturning-loop contrast: both exit0.
Exact source, hashes and diagnostics are in meta/tmp/phase3-loop-return-repair/
dead-match/results.json and the durable loop-source-exit-repair.json receipt.
This is an existing gap, not a loop-repair regression.

Spec/04 forbids returns from a diverging invocation. Body Checking sections2/4/6
requires source contract validation in statically checked dead arms. The
unreachable-match warning cannot suppress that validation. Return.pw::armsCompletion
excludes unreachableMatchArms from both summaries; checkDivergingBody relies on
source.returns() for the forbidden-return contract. Static source validity is
therefore being inferred from a reachability-filtered aggregate.

## Required Finite End State

Close the owning return-contract check at source admission, preserving function
versus closure identity and the declared invocation contract independently from
live-result/flow joins. Keep dead-arm exclusion for executable joins and ordinary
result typing; simply unioning dead normal/result exits into the live summary
is not a correct repair. Reject forbidden named/closure returns even in covered
arms, preserve legal returns from nested independent closures and valid ordinary
function dead-arm diagnostics, and publish no successful source artifact for an
invalid return. Trace the retained source target/contract into final readers;
remove any superseded competing validation after adopting the common owner.

This boundary is adjacent to global-owner return legality in [com-nr7y](com-nr7y.md),
linked for coordination without an invented ordering dependency. Add positive,
rejection and requested-mode controls, then independently review the finite
repair and affected E3 closure. G1/G2/G3 and formal performance/full sanitizer
gates remain mandatory. No specification change, verifier weakening or new
inference feature is authorized.

## Selected Implementation Slice

Work resumed by explicit user instruction. Close this issue and com-nr7y at the
shared direct-return target admission in Resolve/Control.pw, driven by the
already explicit SemanticCompletionOwner and the owner's declared invocation
contract. Reject a global owner or a diverging function/closure before storing
its direct transfer. Body recording already checks every match arm independently
of reachable completion aggregation. Remove checkDivergingBody's superseded
source-return aggregation test; keep its execution-fallthrough obligation.
No extra AST walk, per-syntax exception or dead-arm live-join widening is needed.
Saved valid owner/target facts and successful publication continue to authorize
Mid return/cleanup consumers. Verify both finite issue contracts independently,
including invalid-owner failed-publication and nested valid closure controls.

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
