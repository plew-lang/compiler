---
id: met-sj6y
status: in_progress
deps: []
links: [com-nkoa]
created: 2026-11-11T02:38:30Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, performance]
---
# Restore read-only contracts changed solely to avoid value copies


## Scope

Restore independently measurable API units whose history shows a writable
receiver or argument was introduced only to avoid physical copying. Keep
ownership/lookup improvements that have independent design reasons. Preserve
actual mutations, semantic checking and later source-owner behavior. Work from
historical diffs and today's transitive call graph; do not revert whole commits.

First unit: `Comp.semanticClosureCount`, changed by ab1e958e. It reads a single
count and does not call another mutable reader. `semanticClosureAt` now also
routes through owner-local construction metadata; verify that dependency before
restoring it. The removed Snapshot API is not reintroduced.

Use the saved current carrier as the fixed input for builds. Compare prior and
restored compiler on the same final source, alternate order after warmup, check
exact LLVM output and existing closure or source-fact AOT controls. Accept
small/no regression; leave clearly slower or unvalidated units unadopted.
Record each scope, verdict and revision. No main/seed promotion.

## Sequential restoration

- `Comp.semanticClosureCount`: restored. Standard build
  `20261111T023910-build-9e5089` produced the same executable SHA-256 as
  the baseline. Same-source medians 8.107381 and 8.111118 seconds, eight
  identical raw LLVM outputs, two existing closure AOT controls passed.
  The independent review covered the receiver contract, fixed-input receipts
  and the targeted controls.
- `Comp.callTemplateIndex`: restoration tested and reverted. Standard build
  `20261111T025329-build-aedfd2` and two AOT controls passed. Same-source
  medians 8.093618 and 8.489046 seconds; all three matched pairs slower,
  eight equal LLVM outputs. Raw LLVM and ARM64 prove a Comp snapshot is
  inserted and survives optimization at a representative call. Resume
  restoration after generalized safe read-home forwarding covers this path.
- `Comp.currentSourceOwner`: restoration tested and reverted. Standard
  build `20261111T030227-build-5d8f16` and two AOT controls passed.
  Same-source medians 8.096866 and 10.213079 seconds, all three pairs
  slower, eight equal LLVM outputs. Raw LLVM and ARM64 again show a Comp
  snapshot surviving optimization.
- `SourceFactDirectory.matchOwner`: restored. Standard build
  `20261111T031131-build-c6ab26` and two AOT controls passed.
  Same-source medians 8.117086 and 8.129869 seconds, mixed pair direction,
  eight equal LLVM outputs. No clear regression.
- `SourceFactDirectory.state`: restoration tested and reverted. Standard
  build `20261111T031956-build-264c4e` and same-source comparison passed.
  Medians 8.141385 and 8.573201 seconds, all three pairs slower, eight equal
  LLVM outputs. A whole-directory temporary survives optimization. This
  blocks the dependent readers below. No AOT control was run for the
  rejected trial.
- `SourceFactDirectory.inactiveBuilder`: restored to the c390b418
  read-only receiver. Standard build `20261111T032603-build-4e100a`
  and two AOT controls passed. Same-source medians 8.154263 and
  8.149342 seconds, mixed pair direction and eight equal LLVM outputs.
- `declarationCallHasStorageArguments`: restored its read-only `Comp`
  argument. Standard build `20261111T033439-build-57c515`, two AOT
  controls and independent review passed. Same-source medians 8.109880
  and 8.149894 seconds, mixed pair direction and eight equal LLVM outputs.

The initial compiler and all four restorations compared on the same final
source give medians of 8.159039 and 8.167258 seconds. The eight LLVM outputs
agree and the input gate passed. This is a diagnostic source-to-LLVM
comparison with alternating runs. See the
[measurement index](../../../evidence/performance-regression-history/readonly-restoration/README.md).

## Remaining restorations

- `state` gates `outcome` / `prepared`, the global and owner closure checks,
  and owner-local expression, statement, parent, closure and operation queries.
  This also gates `semanticClosureAt` and the call template / constraint readers
  that use those operations. Keep their current owner-local routes.
- `currentSourceOwner` also gates construction expression queries and
  `sourceRecordingOwner`. The operation query still gates
  restoring the read-only `Comp` argument of `scanBody`. Its receiver writes the
  graph and obligations. `selectedCallHasDeferredConstraints` additionally
  requires checking its diagnostic reader before dropping mutable authority.
- Explicit reader-cache updates, owner activation, save/remove and other
  writes keep their existing writable contracts. The deleted
  `semanticClosureSnapshot` is outside the restoration.
- Recheck the remaining regressions as verified Mid facts can prove
  exact synchronous call-interval stability of eligible mutable places.
  Start with a demonstrated copying call and a competing-write/alias control.
  Keep the snapshot where stability, initialization, access or lifetime
  is unproved. Extend the existing storage admission and typed byref
  transport without frontend-specific exceptions. See [com-nkoa](com-nkoa.md)
  for related effect-precision work. This task remains open for the blocked
  APIs and their dependent restorations.

## Receiver forwarding investigation

The standard CLI reproduces a whole-Comp temporary in the exact
sourceForItemTerm call. The production Mid preparation probe confirms
that the selected call retains a whole inout formal as a semantic read
borrow. StableHomes and the incoming guaranteed-parameter route both
exclude this shape. The current plain inout pointer also lacks the
referent type/alignment evidence used by the native home validator.
The existing overlapping inout/receiver rejection passed.

A bounded prototype is feasible if it establishes the original inout
lane's referent alignment, reuses verified call-interval access facts
and forwards the exact input pointer into the current byref ABI.
Shared, projected, indexed, async and foreign/indirect paths require
separate proof.
See [evidence and scope](../../../evidence/performance-regression-history/readonly-restoration/call-template-index/forwarding-investigation.md).

### Forwarding increment validation

- The private synchronous body forwards the exact native argument for a
  read receiver rooted in a whole copyable inout formal. Cover both self
  and an ordinary formal, including a different same-typed argument and
  an omitted logical parameter before it.
- Preserve receiver evaluation at the call and ordinary value evaluation
  before later sibling effects. Retain existing move/inout overlap rejection,
  ambient checks, and copy fallback for other shapes.
- Confirm pre-change structural failure, fresh candidate IR/behavior, and
  a same-source throughput comparison. Check the original Comp call
  separately from the synthetic structural fixture.

The forwarding implementation passed the structural RED/GREEN and
the value ABI, Ready, physical signature, AOT, lazy run and overlapping
inout/move rejection controls. The original sourceForItemTerm call in
the read-only trial forwards its incoming address, with two whole-Comp
loads gone from that caller. Same-source compile-to-LLVM medians are
8.098441 and 8.080239 seconds for the preceding compiler and the first
forwarding candidate. Measure the API restoration separately with the
same forwarding-capable build carrier on both sides.
[Increment evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/README.md).

### Applied optimization and lookup restoration

Rebuilding the exact same compiler source with the new forwarding-capable
carrier reduces the same-source compile-to-LLVM median from 8.075335 to
7.132823 seconds. This is a diagnostic comparison, not a formal fixed point.

With that same build carrier on both sides, restoring callTemplateIndex
to a read-only receiver gives medians of 7.097031 and 7.154932 seconds.
All eight LLVM outputs match, the original ARM64 call forwards the Comp
pointer, and two existing AOT controls pass. Adopt this restoration.
Restore currentSourceOwner in its own increment. Standard build
`20261111T095834-build-fbe934` differs from the preceding baseline build
only in Expr.pw and uses the same carrier. Same-source medians are
7.064874 and 7.045373 seconds; all eight LLVM outputs agree. All 24 calls
forward their incoming Comp pointer in raw LLVM, and the representative
ARM64 call retains that forwarding. Two targeted AOT controls pass.
[Evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/current-source-owner-restoration/README.md).

Restore state in its own increment. Standard build
`20261111T100823-build-eab7be` uses the same carrier as the preceding
baseline and differs only in SourceFacts.pw. Same-source medians are
7.133965 and 7.061837 seconds with eight equal LLVM outputs. Eleven of
14 generated calls forward the incoming directory; the three Comp field
receivers retain a snapshot in raw LLVM, also observed for
constructionClosure in ARM64. The two owner/payload AOT controls pass.
[Evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/source-body-state-restoration/README.md).

Next, compare dependent read-only contracts, beginning with outcome and
prepared. The remaining field snapshots need an access proof if an
independent measurement justifies a forwarding extension.
