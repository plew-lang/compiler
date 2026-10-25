---
id: com-wrjh
status: open
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

## Planning Stop

The user requires stopping when task omissions/errors are discovered. The loop
producer repair has scoped evidence, but com-jzdz's broad forbidden-return exit
is not complete. This newly required dependency is recorded; implementation is
stopped pending confirmation of the revised work scope. The new bug is open,
com-jzdz stays in_progress and E3/phase three remain unadmitted.
