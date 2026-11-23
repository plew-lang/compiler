---
id: met-9ym8
status: in_progress
deps: []
links: []
created: 2026-11-23T06:42:31Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain opaque generic numeric expectation refusal ownership

Existing generic_numeric_rigid_caller rejects but remains Unclassified. Check/Generic checkGenericTypeMatch directly reports that an unsuffixed numeric value cannot inhabit opaque caller T or provided Self. Reuse the existing raw versus private expected-check origin distinction from com-8uik, while keeping a distinct cause for this actual check. Retain exact expected ParamId/type, operand and owner/session at failure. No new inference, no Array-cause mixing, no retyping committed operands. Scope confirmed by independent numeric_refusal_intake_review; existing com-8uik/met-bu94/met-qo60 finite closures remain intact. This task remains open; the sibling ambiguity task met-tb7u is closed. Reproduce this task on the next fixed candidate before implementation.

## Acceptance Criteria

Exact final candidate RED; caller rigid T, provided Self, Int and Float, real nested Array/block transit where reachable, and valid concrete expectations. Raw active-owner checks versus source-owned lazy/whole/eager, foreign session/owner, changed expected/operand/kind/location, synthetic with copied span, equal-text Internal, retry/drain/cache. No success publication. Fresh candidate targeted controls and independent acceptance; parent whole gate remains separate.

## Exact final-candidate RED

A76f2f9c fixed associated-candidate carrier reproduces all7fixtures/check-AOT-ORC21modes: status1/stdout empty/intended primary diagnostic/Unclassified, with unchanged source/expectation/carrier fingerprints. Full receipt is canonical meta phase3-contextual-operand-regression.json numeric_refusal_intake.red and scratch tmp/phase3-forward-frontier/numeric-refusal-red/results.json. Generic candidate substitutions ambiguity actually reports the unsuffixed numeric overload message, confirming assignment to met-tb7u. No product implementation or GREEN for these tasks yet.

## Implementation boundary and scenarios

The fixed-point carrier from `20261123T101114-self-host-b3272b` (SHA256
`53ebd3f00c8c156b7199b1881a83739643ecc81f54e1c4b003bd6c6eb17458e4`)
reproduces caller argument, annotated local Int/Float and provided Self Int/Float
refusals. `opaque-intake/results.json` records 24 mode observations: 13 actual
opaque Unclassified refusals, two unrequested provided-body ORC successes,
six earlier block/Array inference refusals and three concrete successes. The
latter six are not RED for this producer and their diagnostic order must remain.

Implement a narrow private checking request through Preparation, bounds
condition/block/statement/expression traversal, closure, Make fields and Array
recursion, plus the two Record adapters. Public wrappers and Mono stay Raw.
Preserve dependency Err unchanged. Only the original Int/Float refusal branches
may construct the dedicated negative cause; retain ParamId versus provided Self
identity distinctly, expected term, literal metadata, location and recorded owner.
Observe expression owner separately from its lexical request root. No retyping,
message matching, successful parent publication or Array-specific authority.

Independent plan review found that expressionOwners, sourceExpressionLimit and
exprOriginSerial alone do not prove authorship: all can include synthetic nodes.
Use minimal Lower-owned numeric-origin receipts from both Lower entry points,
including folded negative integers. Ordinary pushExpr and Record cannot publish
this origin. This is syntax provenance, not a second type-success database.
Require request + retained owner + exact Lower provenance for owned attribution.
Test recorded synthetic copied-span nodes as well as unrecorded clones, different
IDs, changed serial/kind/location/expected identity, foreign session/root, Raw
with an active owner, same-text Internal, retry/drain and failure retention.
Keep the existing Float rejection condition, including suffixed Float, unchanged.

`tests/compiler/frontend/OpaqueNumericFailureDomains.pw` and its exact ten-line
`.out` start the whole/eager consumer regression. Extend with Raw/lazy/private
controls rather than treating this initial consumer test as complete coverage.
Final candidate controls, retained-input checks, independent acceptance and the
parent whole-suite gate remain required. Review is a plan review, not closure.

The initial consumer RED is confirmed at native execution: compile/runtime and
corrected link exit0, then exit -6 with exactly `panic: opaque numeric rejection
lost its source owner`. All captured inputs remained unchanged. Initial test
setup errors, a60s ORC timeout and the first link's missing C filename suffix
are excluded from RED. Canonical `numeric_refusal_intake.opaque_checkpoint`
retains the input hashes, baseline24modes and exact outcome. This proves the
first consumer assertion; the remaining scenarios are not claimed executed.

## Implementation checkpoint

The first product candidate passes source checking, standard build
`20261123T105854-build-f6979c`, and24 baseline CLI modes with unchanged
acceptance/primary diagnostics: only the13 opaque failure domains become Source.
Negative integer, suffixed Float, nested statement scope and if-body add12
preserved Source refusals. Closure intake retains its existing earlier Source
literal-context rejection; the match intake syntax error is not product evidence.
Independent source review found two origin-dropping legacy helpers; both now have
Raw wrappers and private origin-bearing cores. Bool/suffixed Int need no stored
numeric provenance. Updated private guards (including both Lower contracts) and
Raw retry/drain/whole/eager consumer native runs pass with unchanged inputs.
The final correctness/lifetime receipts and independent acceptance are below.
Formal performance recovery remains required; these scoped gates are not closure.

## Final candidate correctness gates

Product source `8e3aefe5` is identical, file for file, to candidate-v2's source.
Build59247c and generationc4833e both exit0 with immutable inputs unchanged.
The final candidate passes24 opaque/concrete/unrequested modes,96 inherited
Conflict controls, and generic51 / CLI120 / numeric75 / Array54 / Float48
controls. The CLI protocol preserves com-9clj's known three mode failures;
these results are not a whole-suite green claim.

The current consumer has an exact18-line golden covering Raw repeated body
requests/drain, source-owned lazy prepareFunction retry followed by failed whole
checking, fresh whole checking and eager frontend checking. Initial body-only
lazy setup never requested the callee and is retained as a test setup failure.
Both consumer and private probe run under final-candidate LLVM22 ASan/LSan:
8554/10662 sanitized definitions,20638/28443 memory checks,5271/6583 checked
function bodies, all stages/native exit0, empty stderr and exact goldens.
Captured input hashes were independently recomputed without discrepancy.

Independent reviewer generic_conflict_source_review found no outstanding finite
contract violation or required evidence gap outside formal performance. The
finite scope explicitly preserves earlier block/Array/closure diagnoses rather
than relocating them to the opaque producer. Formal self-host0919bf is complete and independently artifact-checked, but its
5-run median exceeds7.5s. The recovery boundary below remains open.

## Formal fixed point and performance recovery

Formal0919bf completes at generation2 with immutable inputs unchanged and
matching LLVM/runtime/successor artifacts; all generation/measurement artifact
hashes were independently recomputed. Its5 times are8.061463,7.599326,
7.747968,7.359638,7.583590seconds: median7.599326 exceeds7.5.
Nonperformance acceptance does not close this task. Recovery is not judged
impractical.

Same latest source, old fixed-point53eb versus new fixed-point3d468, alternating
5pairs: medians7.525688 /7.540193seconds,10 identical LLVM outputs. This is
an uninstrumented diagnostic comparison, not formal acceptance. Old-source
cross-controls follow to separate input growth from compiler/runtime conditions;
do not attribute the earlier7.135-to7.599 cross-source difference to this
implementation without that evidence. Preserve the existing rejection/ownership
contracts while removing any demonstrated unnecessary cost.

Old-source3pairs also retain identical LLVM, including the prior formal
old-source output: before7.488072 /after7.558915seconds. The exact old compiler
and old source no longer reproduce the earlier7.135462 result under current
conditions. These samples do not establish a specific thermal cause or waive
the7.5 limit. No compiler/test processes remain live.

Next bounded recovery candidate: Lower already knows numeric kind, Boolean flag
and suffix length. Pass that syntax metadata to the private provenance issuer
instead of rereading/copying its newly appended Expr. Keep one central admission
predicate, both Lower entry contracts and failure ownership unchanged. Verify
unchanged behavior and measured benefit; do not alter the measurement protocol
or source acceptance to meet the bound.
