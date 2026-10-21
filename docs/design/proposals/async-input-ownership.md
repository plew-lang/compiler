# Async Input Ownership Handoff

**Status: Under discussion.** Review finding R3; tracked by
[met-6kzo](../../issues/met-6kzo.md). The
[progress document](../../../../agents/compiler-design-progress.md#再レビュー指摘の具体化)
owns scheduling and current status. This document does not adopt a new ABI.

## Question and Existing Constraints

Who establishes an async activation's input owners, how are they represented at
logical body entry, and who supplies exactly-once cleanup? Existing
[Frontend Handoffs](../frontend-handoffs.md#8-implicit-calls-and-reachability)
requires async entry to own accepted inputs, while the
[stored-value rule](../representation-and-abi.md#stored-values-and-ownership-glue)
requires a new share when a borrowed input becomes an independent owner. Thus
the intended meaning is already present; the missing part is the explicit handoff.

Preserve [caller-guaranteed ordinary inputs](../mid-entry-audit.md#evaluation-homes-and-call-materialization),
unique Move transfers, declaration borrow/inout restrictions, source cleanup in
Mid, and physical frame storage in LLVM. Frame/Promise bookkeeping is not another
source cleanup authority. AOT/JIT must use the same runtime semantics.

## Representative Trace

```plew
async fn keep(text: String) -> Promise[()] {
    await delayed()
    print(text)
}
val pending = keep(text: makeString())
```

This is an illustrative design trace with assumed helper declarations, not an
executed regression. A suspended activation needs its own String owner before
the entry call returns and the caller temporary's guarantee ends. Saving descriptor
bytes does not acquire that owner. Synchronous completion on first resume must
obey the same acquisition/transfer and cleanup contract.

## Alternatives

| Direction | Required connection | Tradeoff |
|---|---|---|
| Preserve +0 ordinary public inputs and establish activation owners in entry | Explicit Copy/acquisition or Move transfer feeds logical initial ownership and cleanup | Fits the present public call rule; must avoid hidden backend retain/drop |
| Use a consuming internal activation ABI behind public adapters | Callers/adapters transfer already established owners under one finalized signature | May simplify activation binding, but expands the set of ABI consumers to synchronize |

The first is the initial recommendation to investigate. Either direction must
preserve evaluation, copy/move semantics and cleanup; retaining an object earlier
or longer is not automatically observationally neutral when destruction is visible.
No new source lifetime feature or general coroutine framework is required.

## Decisions and Handoff to Specify

- Assign the semantic acquisition/transfer producer, likely an explicit generated
  Mid entry/prologue contract, and state its relation to the source logical body.
  Determine the exact stage rather than deferring the choice to backend emission.
- Define ordinary copyable input, copy-self, unique Move input and admitted closure
  environment cases. Do not clone a unique value to satisfy frame ownership.
- Connect every acquired/transferred owner to the initial ownership analysis state,
  suspension liveness and normal-exit cleanup. Specify the handoff point so no
  caller owner is destroyed twice and no guaranteed input is dropped as an owner.
- Separate logical owners from physical slots: liveness may choose frame storage,
  but cannot retroactively authorize acquisition or destruction.
- Explain synchronous first completion, genuine suspension, defaults/conversions,
  indirect/witness adapters and partially established input owners when preparation
  fails. Use existing failure/termination rules; do not invent unwind or cancellation.
- Account for ARC operations, aggregate snapshots and frame allocation. Any elision
  needs proof of preserved source meaning; optimizer success is not a safety premise.

## Controls, References and Completion

Trace a temporary String; an aggregate containing managed children; a receiver;
a unique Move input with visible deinit; an admitted closure environment; and an
indirect/generic entry. Contrast immediate completion with suspension/resume.
Follow each owner from caller guarantee through body entry to final cleanup and
separately follow Promise/frame lifetime. Include supported borrow/inout rejections.

[Rust async functions](https://doc.rust-lang.org/reference/items/functions.html#async-functions)
explicitly capture parameters into a state machine. Rust Future start/drop rules
are not Plew Promise rules. [Swift Ownership SSA](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md#guaranteed)
explains why guaranteed values require an enclosing lifetime; a slot is not an
independent owner. Use these as boundary references, not APIs to copy.

Completion requires one producer-to-initial-state-to-cleanup contract, all listed
consumers connected, rationale/cost and independent review. Incorporate it into
[Mid entry details](../mid-entry-audit.md#async-and-machine-boundaries) and
[Ownership](../ownership-and-access.md), with ABI/runtime links. Synchronize spec
only for a genuine semantic change. Then retain decisions and retire this proposal.
[com-tn1m](../../issues/com-tn1m.md) continues to own implementation coverage.
