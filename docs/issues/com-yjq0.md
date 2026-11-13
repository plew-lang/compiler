---
id: com-yjq0
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit requested body and closure type views through saved final facts

## Guarantee and Finite Work

Attach local type annotations and value-view occurrences to the actual requested lexical body/closure owner, including ordinary, method/provided and deinit bodies. Apply common exact-instance admission at that owner's source check, then retain proof/type facts into instantiated body operations and final consumers.

An unused enclosing signature is not permission to eagerly check its body. Do not use a shared synthetic body, ambient caller cursor, another closure's readiness or type-term identity as source authority. Globals and default generators have separate siblings; no new closure/unique feature is included.

## Required Scenarios

- Valid and missing/unrelated/wrong-instance premises for local annotation and value view, with nested constructors and actual use.
- Same-spelled foreign binders, sibling closures/provided bodies, caller-callee environment separation and failure/retry restoration.
- Lazy unrequested body versus whole-check/requested body, supported build/lazy/gen entry paths, and real final saved type/proof consumption.
- Declaration-only acceptance must not be confused with successful body admission; missing saved facts cannot trigger a new source lookup.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First reproduction and work boundary

Candidate `plewc-com-ab7u-final` (`381d515a`, product `428ce8ca`)
rejects the following before starting `main` in both `--check` and
`--run`:

```plew
use @Std/Io only { print }
trait Marker {}
fn unused() {
    val number = 42I64
    val value: I64#Marker = number
}
fn main() {
    print("main")
}
```

Replacing the annotation with `val value = number#Marker` preserves the
whole-target rejection and allows lazy `main` to print `main`. The
annotation failure comes from `verifyProgram(includeBodies: false)`
calling `checkTypeViewSources`, which scans every interned TypeRef.
Lowering records an authored type use under a body role but both local
statement adapters keep only its TypeRef in the statement. Interned
type identity cannot distinguish a declaration from an unrequested
local or closure occurrence.

The new `local-view-unused` case in `tests/tooling/test-lazy-cli.py`
fails on the frozen baseline with the diagnostic above. The preceding
whole-target check and build controls both reject for conformance.

Start with a paired local annotation fixture for declaration-only,
whole-target and requested-body checking. Trace which remaining
consumers require the exact local annotation and remove their
dependence on the global scan as that authority moves to lexical body
preparation. Then trace the closure, provided/deinit and concrete
consumers against the same owner contract. Keep type-view source
formation distinct from discovering or publishing executable bodies.

## Request timing increment

Lowering now retains authored occurrence IDs in the existing block and
expression type-use lists. Declaration verification reads its own list;
body recording checks only the block and expression lists reached by its
request. This removes the scan across interned type terms and avoids
resolving a selected view head twice within a single check.

Build `20261113T031508-build-6c50d3` passed with immutable inputs.
Candidate `plewc-com-yjq0-request-timing` (`5590955d`) passed the lazy
CLI suite, including the new unused/requested/check/build controls, and
checked the compiler's own source. A valid locally annotated generic
view with a matching bound also printed `42` under JIT.

Generation `20261113T032010-gen-986660` passed. In a same-source
alternating comparison, the medians were 6.902333 s before and
6.821464 s after the timing change (three measured runs per carrier).

## Exact instance for body annotations without projections

The frozen baseline and request-timing
candidate both accept `val values: Array[I64#Marker[I64]] = []` when
the sole conformance is `I64 as Marker[Bool]`. The current head check
compares trait owner and arity without checking positional arguments.
The new rejection fixture confirmed this RED.

Requested non-projection annotations now require the same exact
instance query as authored signatures, with assumptions from the
lexical declaration. Build `20261113T032208-build-d6ed26` passed.
Candidate `plewc-com-yjq0-exact-local` (`f540d3b5`) rejects the RED
input in check, build and run. The lazy CLI suite passes, and both a
concrete and a generic view with a matching bound print `42`.
The compiler source passed check. On that same source, alternating
measurements gave medians of 6.928772 s for the timing candidate and
6.912429 s for the exact-instance candidate (three runs each).

Projection recipes, value views, owner-scoped proof publication and
final readers still need migration. Mid already reads sealed local
binding types. Mono's `scanLocalDeclarationType` grounds that binding
through the general term reader, and its statement walk also scans the
raw annotation. Both consumers need to take their input from the
admitted occurrence under the same body owner. The common formation
audit outside this body lifecycle remains under [com-3jtd](com-3jtd.md).

The next RED is `local_value_wrong_trait_instance`. A standalone
`number#Marker[I64]` passes both check and run on `f540d3b5` even
though only `Marker[Bool]` is implemented. Record attaches a view to
the operand's semantic type before Verify checks the older head lookup.
Use the exact instance and the lexical owner when recording the
admitted value view, then transfer its evidence to sealed body facts.

## Standalone and call-receiver value views

The pre-change candidate accepted a wrong instance in
`viewed_method_wrong_trait_instance` and two instances of the same
trait in `value_view_two_instances_of_same_trait`. It also rejected
the second closure in `trait_value_views_in_generic_closures` because
the old verifier did not read the enclosing generic's premises.

Record now requires the complete instance when building a value
view or recording a viewed value receiver. It stores the selected
proof on the exact expression's source-body builder. The final
instance scanner reads the sealed body, checks the expression and
selector identities, and replays the proof before visiting the
viewed layout or finalizing the call. Verify retains extension
applicability and cycle checks. Generic declaration annotations
already admitted with lexical premises bypass the compatibility
sweep that has no such premises. This restores four positive
associated-type/extension controls that the timing change had
regressed.

Fixed-input build `20261113T033415-build-7786fe` produced candidate
`plewc-com-yjq0-value-views-checked` (`263a7415`). The three value
rejects and existing missing-conformance diagnostic match, both
closures print `42`, and the four restored controls pass check and
JIT with the original expected output. A fault test at the final
body reader and full annotation-recipe publication remain open.

Same-source comparison against the preceding exact-local candidate
gave 6.878221 s and 7.086465 s on the first three measured pairs.
An isolated repeat with four pairs gave 6.848379 s and 6.844556 s.
The slowdown did not reproduce. These are throughput comparisons;
the whole-program fixed-point gate remains with met-si6j.

## Retain projection proofs on local bindings

Both lowerers attach the authored occurrence of a projected local
annotation to its binding statement, including the binding made for a
typed loop. Record checks the canonical type recipe with the lexical
function's premises and publishes the recipe and proofs with the
binding in the exact source body. Mono's local type reader requires
that receipt, replays the admitted recipe under the concrete instance,
and publishes the result used by Mid. The local layout scan uses the
resulting type instead of scanning the raw annotation again.

Fixed-input build `20261113T034412-build-5f7ced` produced
`plewc-com-yjq0-local-projection` (`227c12d9`). The compiler source and
the lazy CLI suite pass. A generic closure binding and typed loop
binding pass check, JIT and native with outputs `42` and `43`.
An invalid projection remains deferred in an unrequested function and
fails whole-target check.
On the same compiler source, alternating medians were 6.946345 s
before and 6.944309 s after this increment (three samples per carrier).

Isolated deletion probes leave the production final readers unchanged.
The standalone value view, viewed call and projected local binding all
fail Internal when their proof is withheld, and intact fresh compiler
states succeed. See the meta evidence under
`evidence/rejection-domains/diagnostic-domain-implementation/value-view-proof-replay/`.

## Bind deinit annotations to their source body

The two source adapters for impl deinit and the two legacy struct-body
adapters now open a deinit body scope and bind it to the registered
destructor. A projected annotation uses that scope at admission and its
saved receipt at finalization. The destructor keeps its existing
instantiation path, with no authored callable signature. The
trait-provided method already uses authored method registration.

The same native owner fixture fails on the archived pre-change source
with `deinit has no authored body scope` and passes on the changed source
for both declaration forms. Fixed-input build
`20261113T040320-build-f4da04` produced `fd67b3c2`. Lazy CLI, generic
deinit and six other runtime fixtures passed. An isolated deletion of
the deinit annotation receipt fails Internal with
`final local has no saved annotation proof`; the intact controls pass.

Conditional generic deinit selection is tracked by [met-b2la](met-b2la.md).
Removal of legacy struct-body deinit is tracked by [met-2t3l](met-2t3l.md).

Alternating three measured compilations per carrier on the same source
gave 7.004045 s before and 6.989182 s after the destructor increment.
All eight runs (including warm-up) emitted identical LLVM
(72,485,130 bytes, SHA-256
`4a72df6c326a959f2f77b5dbe24bcf1610215f62802baacaf7c29fc5c4f2335c`).

## Retain annotations without an associated projection

Every explicitly annotated local lowered within a body now gets the
same source-occurrence handoff as a projected annotation. This includes
the ordinary statement generated for a typed loop binding.

In the isolated deletion probe, `val number: Number#Project =
<Number />#Project` previously completed with the annotation receipt
removed. With fixed-input build `20261113T041123-build-a535ad`
(`5c8e3231`), the same probe reports Internal from the final local
reader, and both intact controls pass. The compiler source check,
lazy CLI and seven existing runtime fixtures passed. On the same
source, alternating medians were 6.991954 s and 7.009900 s, with
identical nonempty LLVM output (72,484,293 bytes, SHA-256
`ac628e6b8a967afe435990a225b1fda427cf9b78b48764932051bdf9eb303991`).
This is a three-sample comparison, separate from the fixed-point gate.

## Reject a receipt from a sibling binding

Under carrier `5c8e3231`, a scratch-only writer substitute copied the
previous local's annotation receipt into a second binding with the
same semantic type and a different occurrence. Finalization returned
Internal with `final local has a foreign annotation proof`. Both
intact controls passed. Two requests for the same corrupted body in
the same session retained the diagnostic and restored the caller
cursor. The test replays unchanged inputs; the request state remains
failed per the compiler-state contract.


## Supply the initializer with its admitted annotation type

The authored recipe admission supplies the lexical receiver substitution
and proven projection equations. Record replays those equations once
and uses the resulting source term as both the initializer expectation
and local binding type. Abstract outputs stay symbolic until
instantiation. The compatibility walks still consume the written term
and require migration to the saved binding type.

Fixed-input build `20261113T042234-build-1c960f` produced `76bf830b`.
The compiler source check, lazy CLI and seven runtime fixtures passed.
A projected U8 expectation reaches an unsuffixed literal through a
value block and produces 255 on both carriers. Alternating same-source
medians were 7.142997 s and 7.126682 s. Each carrier emitted the same
nonempty LLVM in all eight runs. This compares the change against a
baseline also above 7 s, with no increase attributable to this change.

## Read the admitted local type during compatibility checking

The ordinary and generic compatibility walks now acquire the
owner-scoped binding and use its admitted source term for initializer
compatibility. The occurrence map identifies the expected source use.
A missing or foreign receipt is rejected instead of recovering a
type from syntax. Existing global and synthesized bindings without
an authored local occurrence retain their own paths.

Fixed-input build `20261113T042841-build-73473e` produced `e692879e`.
Compiler source check, seven existing runtime fixtures, projected
literal control, lazy CLI and standard gen
(`20261113T043203-gen-cfbe40`) passed. Six existing rejects matched the
previous carrier's diagnostics. Alternating same-source medians were
7.324725 s and 7.261029 s. LLVM was identical in all eight runs.
This is a same-source comparison, not the formal fixed-point gate.

## Independent review and local annotation admission

Independent review at `b8250653` found that the block-level sweep
re-selected the trait instance for each local annotation before the
binding's authored recipe could normalize its children. A projected
trait argument was rejected on both check and JIT despite passing on
the pre-task carrier. The sweep now retains extension and cycle
checks and defers trait admission for the exact local annotation
recipe occurrences to the binding's source check. Candidate
`1c68b4d0` (fixed-input build `20261113T043852-build-2fad76`)
passes the regression fixture in check, JIT and native. Invalid direct
and nested instances still reject. Compiler source check and lazy CLI
also pass.

The review did not approve closure. Parameterized local shorthand
`T.Item` and provided-method `Item` still need the declaration
recipe provenance from their where clause and parent impl,
respectively. Value-view arguments containing a projection require an
ordered authored-argument handoff. A view of a value whose type is a
projection also needs the selected receiver normalization at final
instantiation. The independent controls and failure diagnostics are in
the meta `value-view-proof-replay` evidence directory. The old and
new carriers both reject the review's extension-only witness and
viewed assignment-place examples. General view formation remains with
[com-3jtd](com-3jtd.md).

## Reuse admitted declaration recipes in local shorthand

The body root must still be a Body-role occurrence of the registered
lexical function. A descendant can reuse a recipe already admitted by
that function's signature, including the exact argument recipe from a
where clause or the parent implementation's receiver. Body validation
inherits the frozen proofs and equations from that signature. The
compatibility sweep marks only Body-role uses as local-owned.

Carrier `1c68b4d0` rejects the two new shorthand fixtures during
check. Fixed-input build `20261113T044402-build-a7bfcc` produced
`8f8d0bb7`, which checks both fixtures and prints 42 in JIT and
native execution. The compiler source check, four additional runtime
fixtures and the lazy CLI suite passed.

The first candidate increased the three-pair same-source median from
7.023867 s to 7.136208 s. Declaration-recipe state was being acquired
for every local annotation. Limit that lookup to terms containing a
projection, where a declaration-origin recipe can occur. Fixed-input
build `20261113T044855-build-e79797` produced `14fc222b`; the same six
check/JIT controls pass. Comparing the optimized candidate to the
same pre-fix carrier gave 7.026079 s and 7.008201 s with identical
nonempty LLVM across all eight runs.

## Replay a value view's projected receiver

The prior candidate accepted the projected-receiver fixture during
check and failed JIT with `saved signature view is not instantiated`.
Record now retains the receiver's source projection equations with
the selected view proof. Finalization instantiates and replays those
equations before consuming the proof, including when the source
receiver remains abstract until the body is instantiated.

Fixed-input build `20261113T045410-build-b3daa3` produced `4635ba84`.
The projected receiver fixture passes check, JIT and native with
output 42. Four related check/JIT fixtures also pass. An explicit
trait argument containing a projection still needs its authored
argument handoff.

## Retain ordered arguments of body-owned value views

Both syntax adapters preserve the exact authored occurrences of the
positional arguments. Record admits the argument recipes in order and
uses the resulting trait instance for the view term and for proof
selection. Finalization checks the written selector identity, then
instantiates and replays the saved equations for its receiver and
arguments. Declaration/global/default paths keep their existing
ownership boundaries.

The projected-argument fixture reproduces a false Source rejection
on `4635ba84`. Fixed-input build `20261113T050412-build-ea199e`
produced `811d0918`, which passes check, JIT and native for both a
stored view and a directly viewed call. Two projected positional
arguments pass in the written order and reject in reverse order when
that instance is absent. Generic argument and global controls also
pass. Compiler source check and lazy CLI passed. Same-source medians
were 7.022430 s and 7.045990 s in three measured pairs. All eight
nonempty LLVM outputs matched. This is a throughput comparison.

## Remove the raw initializer expectation from Mono

The local instance scanner no longer installs an ambient expectation
from the written annotation. Its sole reader constructed an unused
operator result hint. Source-selected call templates and saved local
types still supply the final scanner's inputs. Fixed-input build
`20261113T050954-build-ed0c9e` produced `9cf01e79`. Four projection
runtime fixtures, compiler source check and the lazy CLI suite passed.

## Independent recheck and remaining admission boundaries

The independent review of `d57c7510` reproduced two source regressions.
A provided method's explicit `Self: Projection[Item=I64]` premise
must supply the equality for a view selecting
`Project[Self#Projection.Item]`. The implicit receiver premise
establishes conformance but has no associated equation. A generic
function's bound `T: Marker[U#Projection.Item]` must also match the
same selector after the lexical `U: Projection[Item=V]` equation is
applied. The raw bound currently fails to match the normalized key.
The meta replay directory preserves both inputs and carrier results.

Make ordered argument occurrences mandatory at authored value-view
sites. Bind each root to the actual view expression and slot before
Record. Retain the argument receipts with the selected view and
validate them at the final consumer. Distinguish source sites from
global/default and static qualifier paths explicitly. Add deletion
and same-type foreign-slot controls. Route the replayed type to the
layout/call consumer where the current generic grounding path can
search for projection evidence again.

The independent recheck did not approve closure. Existing check/JIT
successes for the earlier four regressions, ordered argument cases,
provided-body separation and sibling closure timing remain valid
controls for the next candidate.

## Keep the equation from an equivalent lexical premise

The source recipe now selects a member equation among equivalent
roots for the already-selected abstract trait instance. An opaque
premise supplies no equation and cannot overwrite one. Conflicting
outputs fail rather than choosing the first or last value.

Fixed-input build `20261113T051557-build-fadbac` produced `8720f079`.
The provided method fixture passes check, JIT and native with output
42. The two orders of the equivalent free-function clauses both pass
check and JIT. Compiler source check and the covered shorthand,
view and concrete supertrait controls pass. Matching a normalized
selector against the raw lexical premise remains open.

The pre-existing nested provided receiver signature fixture also
fails on the archived pre-task carrier. Its separate declaration
formation boundary and last known passing carrier are recorded in
[com-3jtd](com-3jtd.md#nested-projection-in-a-provided-receiver).

## Match a selector under its retained equations

The complete-instance query compares candidates' ordered argument terms
under the equations already admitted at the selector. Proof paths keep
their original declaration identities. Build
`20261113T052203-build-109a51` produced `4fac5791`. The lexical-bound
regression passes check, JIT and native with output 42. The older
nested provided receiver signature fixture also passes check and JIT
again, as do six additional target fixtures. Compiler source check and
lazy CLI passed. Same-source medians were 7.028838 s and 7.030233 s
with identical nonempty LLVM in all eight runs.

## Validate ordered argument receipts during finalization

The originating source expression serial identifies the ordered roots
in the source-use store. Record publishes the admitted per-argument
occurrences, recipes and proofs alongside the selected value view.
Mono checks the presence, length and identity of each slot against the
source-use store and reads the retained recipe in the instance.

Fixed-input build `20261113T052912-build-735838` produced `723fdb18`.
Eight targeted check/JIT fixtures passed, as did two native controls,
compiler source check and lazy CLI. The isolated publication probe
rejects a missing receipt list and swapped receipts for identical
written types with Internal. Both intact controls pass. Same-source
medians were 7.173830 s and 7.040047 s with identical nonempty LLVM.
The proof replay still needs to hand off the concrete view type to
layout and later consumers.
