---
id: com-atac
status: open
deps: []
links: []
created: 2026-11-18T13:46:02Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [backend, driver, verification]
---
# Route async instance methods to their entry ABI


## Reproduction

A fixed-point carrier from `76a15cb2` accepts this with `--check`.
AOT and demanded JIT both fail with
`private value ABI: normal body signature is incomplete or belongs to another entry convention`.

```plew
use @Std/Io only { print }
struct Worker { val code: I64 }
impl Worker {
    async fn perform() -> Promise[I64] { return self.code }
}
async fn main() {
    val answer: I64 = await <Worker code=42I64 />.perform()
    print(answer)
}
```

An ordinary method suffices. An explicit trait forwarding body and a `via`
declaration also fail when reached. An unused delegation passes declaration
checking on the current frontend candidate.

## Guarantee and Completion

Use the finalized async calling convention for a demanded instance method
in AOT and ORC; preserve the source receiver passing and frame acquisition
rules in [spec/07](../../../spec/spec/02-type-system/07-methods-impl.md)
and [Ownership and Access](../design/ownership-and-access.md). Inspect
`GenMethods.declareGenMethods` and `declareOneGenMethod`: the former
currently admits a receiver method based on `hasRecv` and `!isExtern`,
while the normal `bodyValueAbi` consumer explicitly rejects `isAsync`.
Trace actual registry publication, call targets and async frame preparation
before deciding the fix. The normal ABI verifier must retain its guard.

Reproduce the fixed failure, then require 42 for a direct method and a
conformance forwarding method in AOT native and JIT. Include existing sync
method and free async positive controls, receiver ownership preservation and
independent review. Check admission, entry registration and the final consumer
on the same candidate. Async syntax or scheduling policy changes are outside
scope. This is a runtime control prerequisite of [com-6esv](com-6esv.md).

## Receiver ABI Implementation Checkpoint

The candidate routes ordinary async methods through the finalized-body
entry table and uses a receiver lane before ordinary arguments. Copy-self
from a temporary aggregate with a heap String survives suspension, and the
moved unique receiver deinitializes once before the awaiting caller prints
the result. The two cases and the existing via path failed on the old
carrier with the recorded ABI diagnostic. The first prototype passed
check, JIT and native AOT for those cases and four positive controls.
The existing generic async feature limit is unchanged.

Independent review verified those paths and found that a second iteration
must check the supplied entry against the frozen receiver/ordinary modes
before admitting its frame (including the forged Move case in
ReadyAsyncPlanMain). The independent review also found that the successful
via output concealed an extra activation. [com-ceny](com-ceny.md) owns
that separate forwarding repair and blocks com-6esv. The existing unique
copy-self source-admission gap is recorded in [com-tn1m](com-tn1m.md).

The follow-up candidate checks receiver and ordinary lane type, role and
passing against the frozen signature before publishing a Ready activation.
The seven check/JIT/native controls passed again, as did the Ready and
completed-async architecture checks. The two receiver lifetime fixtures
are registered in the pre-optimization ASan ownership manifest. The
first full suite (20261118T135447-test-411f83) stopped via its watchdog;
a passing full suite, ASan and formal performance are still unverified.
