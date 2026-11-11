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

Compare the dependent read-only contracts individually. The outcome
trial regressed in all nine matched pairs and was reverted. The
six-pair confirmation medians were 7.070159 and 7.214105 seconds.
Seven of nine emitted calls used a snapshot of the Comp.sourceFacts
field and representative copies survived in ARM64. The trial kept
identical emitted LLVM across candidates.
[Outcome evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/source-body-outcome-restoration/README.md).
The independent prepared trial was adopted. The same-source medians
are 7.094541 and 7.095004 seconds, all eight LLVM outputs agree, and the
two owner/payload AOT controls pass. Both projected call sites retain
a field snapshot in raw LLVM and ARM64.
[Prepared evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/source-body-prepared-restoration/README.md).

The outcome-dependent restorations remain pending. A forwarding
extension needs a verified access proof for a nonboxed field of the
live inout formal. Other readers can be evaluated in dependency order.

The exact prepareLexicalBody call retains a verified read borrow of the
inline sourceFacts field under inout self. LLVM Ready only admits the
whole incoming inout home, and its final receipt and native check require
that exact unprojected argument. A projected proof needs exact incoming
root provenance, nonboxed field layout and leaf alignment. The separate
overlapping-write rejection still passes. Independent review checked the
raw LLVM, representative ARM64 and ABI boundaries at 461f3eb4.
[Investigation and probe](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/source-body-outcome-restoration/field-forwarding-investigation.md).

## Forward verified inline field receivers

Extend normal direct synchronous receiver forwarding from the whole
copyable inout formal to its statically laid out inline fields. Match
the emitted field chain and alignment to the exact physical formal.
Preserve read timing after explicit/default argument evaluation and
existing rejection of conflicting inout or move arguments. Unsupported
places keep the snapshot fallback. Cover whole-formal controls, a
nested field of a non-first physical formal, and projected receiver
evaluation after a write in an earlier argument expression. Inspect
raw LLVM and execute the fixture. Compare outcome restoration against
the same final source only after verifying forwarding.

The forwarding change passed the fixed-carrier development build
`20261111T115237-build-f121f1`. The final raw LLVM fixture fails on
the old compiler's stack temporary and passes on the new compiler
with exact incoming argument and both GEPs verified. The effect case
verifies the mutation call before both GEPs, alignment 8 and raw AOT
output. JIT, existing overlap rejections and the Ready/physical ABI
controls passed. Independent review confirmed the borrowed interval
and exact root/leaf validation, and prompted stronger order and
alignment assertions. A scratch read-only outcome trial has seven
field forwards and two whole forwards with no snapshots. Measure
the read-only signature independently before adopting it.

The self-applied comparison used the same forwarding-enabled builder
for writable and read-only outcome. Six balanced rounds on the same
read-only trial source give 7.120595 seconds for the original compiler,
6.849405 for forwarding with writable outcome, and 6.890875 for
forwarding with read-only outcome. The two forwarding variants emitted
identical LLVM in all 14 runs. The read-only trial was slower in all
six pairs. Its outer projected calls are forwarded, but its calls to
isActive and state both stage the incoming read-only receiver into an
aggregate temporary. The writable outcome forwards both of these
receivers, and ARM64 confirms the read-only state call uses the stack.
Keep the generic field optimization and retain the writable outcome
until verified read borrows can forward a guaranteed-indirect input.
This follow-up needs to preserve the typed formal, its lifetime and
its read-access proof. No claim is made about the time attributable
to individual copies.
[Forwarding and measurement evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/projected-inout/README.md).

## Forward a read borrow from an incoming read-only argument

Reuse the whole guaranteed-indirect formal in a normal body when a
synchronous direct read-only receiver retains a verified read borrow.
Check exact argument identity and typed byref alignment at consumption.
Preserve ordinary value snapshots, overlap rejection, earlier argument
evaluation, and the existing field/inout controls. Exercise a read-only
method and an ordinary read-only argument as forwarding sources. The
previous carrier fails the raw receiver-address assertion for the method.

Development build `20261111T150737-build-4066d2` passed from the
projected-inout carrier. The read-only method and the ordinary relay
forward their exact incoming addresses in raw LLVM, including the
second of two equal-type physical arguments after an omitted marker.
The raw AOT and JIT fixtures, existing field and inout controls, and
overlap rejections pass. Independent review confirmed the exact
physical argument, typed alignment and access checks. The header
declarations and non-first-argument control were added after review.

## Remaining candidate inventory

The owner-closure family starts with outcome, then globalInitializerPrepared,
globalInitializerConstructionClosed, sourceOwnerConstructionClosed,
semanticCompletionOwnerPrepared, semanticExprConstructionClosed, and
semanticStmtConstructionClosed. The independent owner selector is
sourceRecordingOwner. Preserve the mutable body preparation paths.

The owner-table families are expression and constructionExpression
(including sourceSemanticExprTypeAt), expressionHead and its expression
head/term consumers (constructionExpressionHead, recordedSourceExpressionTerm,
invocationDiverges, hasSemanticExprTypeFact, recordedExpressionHasUnitResult,
and recordedGlobalAddress), statement, parent and lexicalSourceFactOwner,
constructionClosure and semanticClosureAt, constructionAggregate,
constructionMatch, and the directly related valueBlock/constructionValueBlock
and contextCommitted readers. Preserve owner activation and reader-cache writes.

The operation families are operation/callTemplateAt/callTemplateSnapshot
and the read-only Comp input of scanBody, operationHead/callTemplateHeadAt,
and operationConstraints/sourceOperationConstraints/selectedCallConstraintPlan/
preparedCallConstraints/selectedCallHasDeferredConstraints. Preserve scanBody's
writable analysis receiver. Check the diagnostic path before restoring the
last reader. The diagnostic entry itself is an enabling dependency only.
Original signature changes are visible in 0c7ee3c9, 7943e499, ab1e958e,
24192d1f and 2b241be3. Later pure readers are listed where they share the
same owner paths. No redesign of construction, caching or diagnostics is
required to complete this restoration assessment.

The self-applied trials built with the same forwarding-enabled carrier
(`20261111T151134-build-36e00e` and `20261111T151408-build-c03ad9`)
measure 6.588481 seconds for writable outcome and 6.585388 for read-only.
The build receipts record distinct source inputs and byte-identical
executables. The timing spread reflects repetitions of the same binary.
All 14 LLVM outputs agree, and the two source-owner AOT controls pass. Outer call sites and both inner calls
forward their exact addresses. Restore the read-only outcome.
The closure trial exposes a separate guaranteed-parameter field
projection gap on its state/inactiveBuilder calls.
[Read-only outcome evidence](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/readonly-parameter-relay/README.md).

## Forward inline fields of guaranteed-indirect formals

The closure trial shows two snapshots from the read-only Comp passed
to constructionClosure, at SourceFactDirectory.state and inactiveBuilder.
Extend the existing field path to typed byref roots while checking the
exact physical formal, nonboxed static field path, native root and leaf
types and derived leaf alignment. A nested byref fixture fails with the
previous compiler and passes after build `20261111T152249-build-6ac346`.
Raw AOT and JIT pass, including previous whole/inout, argument order and
overlap rejection controls. Independent review found no ABI or ownership
blocker.

## Dependent reader trials

The first closure trial was slower in five of six pairs (6.544138 to
6.566213 seconds), and in a second run was slower in all six pairs
(6.529359 to 6.550633 seconds). The all-candidate compiler in that
second run was slower still (6.564534 seconds). The closure methods
forward the intended addresses, but their machine code differs. The
scanBody trial still snapshots the full Comp passed as an ordinary
value. Exclude those three declarations from the next adoption.

The narrowed trial from build `20261111T154109-build-f7dc04` restores
35 declarations across owner checks, expression and operation readers,
and constraint queries including their diagnostic dependency. The same
builder and final source give medians 6.552373 / 6.546278 seconds for
baseline / narrowed and 6.577821 seconds for the all-candidate trial.
All 21 LLVM outputs agree. Five AOT controls, one JIT receiver control,
and three check rejection controls pass. valueBlock,
constructionValueBlock and contextCommitted were introduced as inout
and are independent of the historical restoration. They are outside
this adoption.
[Reader comparisons and controls](../../../evidence/performance-regression-history/readonly-restoration/inout-read-forwarding/dependent-readers/README.md).
