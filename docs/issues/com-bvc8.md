---
id: com-bvc8
status: in_progress
deps: [com-f18l, com-fgck]
links: [com-vh0x, com-j2i7, met-c1pg, com-cuoy, com-0w38, com-zdod]
created: 2026-11-06T17:52:14Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Separate projection identity from receiver mirror metadata

## Contract and Evidence

Design types-and-evidence sections2-4 distinguish projection, record and nominal
identity and require a shared semantic child interpretation. [Executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json) shows
common typeRefEq equates different associated members when the projection
contains a record receiver mirror. Real rebuildProjectionTerm and explicit
groundTermInEnvironment also create the shape, so it is not limited to manually
stamping TypeRef flags. The exercised substitution does not satisfy T:Projection;
legal-source reachability and a source miscompile remain unproven. Normal bound
generic, nested record-field and concrete nominal controls compare correctly.

## API/Representation Investigation and Repair

Before choosing a patch, map the exact data required by construction, structural
comparison, substitution and actual consumers. Determine whether receiver
isRecord/fields/nominal/view/layout metadata must be copied onto the projection
itself, and which consumers still require compatibility mirrors. This is a
possible responsibility leak through an overbroad data/API input, not merely a
branch-order bug. Do not claim input misuse or needless payload without tracing
actual reads and required contracts.

The endpoint is one consistent semantic category/head/child interpretation:
projection identity reads its owner/member and treats the receiver as a child;
record identity reads fields; ABI materialization has an explicit separate
adapter. Remove redundant competing interpretation paths or confine unavoidable
compatibility mirrors behind a documented boundary with removal conditions.
A conditional-order change alone is not sufficient if the same ambiguity remains
in other affected semantic readers. This finite repair need not replace every
TypeRef or perform all future API narrowing.

Within the affected APIs and their direct caller paths, remove information or
capabilities proven unnecessary even when they do not cross a responsibility
boundary or cause the observed bug. Change the actual signatures/payloads and
callers; do not merely document unused inputs or hide them in a wrapper.
An unused field in a coherent semantic record alone does not require splitting
that record. Establish necessity from the operation's contract as well as its
actual reads; do not duplicate validation/selection to eliminate an argument.
If cleanup requires a wider shared-API redesign, assign the remaining work to a
finite linked issue with its boundary and completion conditions. Do not silently
expand this repair or describe deferred cleanup as completed.

Keep source conformance admission separate. Do not make equality search for
conformance or use absence of a valid record conformance to ignore a confirmed
structural error. Comparisons should consume established semantic identity;
malformed input handling and preconditions must be explicit, not accidental
success from unrelated mirror flags.

## TDD and Completion

Preserve raw and production-builder/substitution REDs. Cover same/different
member and canonical trait owner, receiver and positional arguments, view identity,
normal records with different ABI layout names, valid generic/nested-record /
concrete nominal controls. Do not require a legal record conformance control:
the specification forbids it. Trace shared head/child APIs through equality and
actual affected consumers (including caller guards) and through any adjusted
constructor/substitution paths; retain semantic fields through final use.

Complete API/data responsibility findings and scoped unnecessary-input removal,
record the justified coherent payloads and any explicitly assigned wider work,
remove competing decisions, run
applicable behavior/structural checks and independent neutral review. Performance
checks follow the parent goal; no unproved performance claim or verifier weakening.

The unnecessary-input scope clarification (baseline f32be228 plus this
document-only amendment) received independent read-only review by
record_issue_assignment_review: accepted without corrections. This does not
certify implementation or task completion.

## Boundaries and Intake

com-vh0x/com-j2i7 own broader input-authority narrowing, not this product equality
repair; link and coordinate rather than duplicating their whole scope. met-c1pg
owns cycle graph admission/private comparisons, not non-cycle equality. No new
projection policy, conformance solver, record extension feature or main/seed
promotion. Required area intake is met-6e6k and met-ia09, plus met-si6j directly.

## Reproduction on the Pinned Compiler

The fixed-point carrier built with Syntax 0.1.11-dev.32 compiled and ran
[projection_member_identity](../../tests/fixtures/run/projection_member_identity.pw)
natively. The builder and environment substitution each reported equality for
distinct members (expected 0, observed 1). The generic, nested record and
concrete controls matched their goldens. The mapped receiver was preserved.

Both a direct rebuild and substitution publish through Comp.pushType and
Arena.registerType, which currently copy the receiver-derived classification
and pools into the scalar term. The shared child reader handles these rows as
projections. The shared head compare returns from its record branch before it
checks either the trait or the associated member. The immediate shape key and
the body/destructor nominal-key guards also read those legacy fields. Track
their compatibility with structural equality before changing the key or head.

## Semantic Reader Increment

The initial implementation gives pooled type readers an explicit projection
classification. Projection heads compare associated members and trait owners,
and their children carry the receiver and positional arguments. The coarse
candidate key uses the member for projection children and leaves full identity
to equality. Body/destruction nominal-index eligibility and grounding's
structural-record branches no longer derive the projection's category from
the receiver mirror.

The extended native RED builds the same fixture with the same exact-pin compiler
against archived source at b679f553. Member comparison fails through rebuilding
and substitution; the distinct trait-owner assertion also fails. Same-member,
receiver and trait-argument controls match. Compiling and running the fixture
with that carrier against the changed source matches the full golden.

Remaining work includes auditing data passed by construction paths, testing
selector identity and record layout-name independence, tracing any qualified
comparison and materialization consumers that still interpret mirrors,
fresh-candidate gates, and independent review. The migration TypeRef payload
still contains compatibility fields.

## Published Receiver Reads

The primary Arena registration caller publishes a projection's explicit
receiver before inserting the row. The only other production caller
registers the non-projection sentinel. Environment substitution, reification
and runtime-side projection resolution now read that stored receiver directly.
The removed witness branch duplicated the earlier projection traversal and
could never handle a projection. Syntax/legacy formation still adapts
flattened input at publication. Existing TypeRef readers outside these paths
remain part of the compatibility audit.

The expanded native regression also verifies record layout-name independence
both directly and through a projection, plus distinct output-view identity.
The exact-pin carrier compiles current compiler source and the expanded
fixture, whose output matches the golden. Six nearby fixtures passed check
on the previous diagnostic binary built from f26bb1a5.

## Independent Review and Follow-up

Read-only review of 2ea64ae0 found a spelling fallback could bridge an
ownerless projection to two distinct, same-spelled owners. It also found
that record layout lookup accepted a projection by reading the receiver's
mirror fields. Native RED reproduced both on 2ea64ae0 (owner assertion false;
record layout assertion diagnosed “projection matched its receiver layout”).
Both fixtures pass after comparison uses the saved canonical owner or the
lowered owner offset, and both ABI lookup entry points require a structural
record per the shared semantic category.

The review also identified separate projection matching in declaration alpha
equality and unification, possible owner overwrites during declaration sealing,
unchecked receiver and member inputs in reconstruction, and remaining layout
callers that branch on compatibility mirrors. Those paths still require audit,
regression cases and a follow-up independent review.

## Declaration Comparison and Constructor Inputs

The native regression fails before repair when an extension view exists only
on one projection output: both alpha equality and directional unification
accept it. Alpha equality now uses the common head reader. Directional
unification uses the same projection owner and member comparison and checks
output selector heads and argument terms, except when its caller explicitly
requests receiver dispatch without the outer view. The previous competing
projection head matcher was removed.

A second native RED shows rebuilding can publish rows for missing receivers
or members. Rebuilding now rejects a missing or out-of-range receiver and
a missing member before publication. Tests assert that invalid input cannot
change the arena. Both native REDs pass with their respective changes, and
the exact-pin carrier accepts the revised compiler source in check mode.

The next boundary is declaration sealing: trace an owner selected by both
lowering inputs through later declaration registration, including same-spelled
foreign owners, before deciding whether the existing canonical stamp is
sufficient. Recheck remaining ABI entry and construction payload reads.

## Preserve Lowered Trait Owners Through Declaration Sealing

Extending the existing imported-trait alias fixture with a local homonym
reproduced a public type mismatch on the exact-pin fixed-point carrier. The
source selected the imported owner correctly, then declaration sealing used
the canonical name's spelling to look up the trait again in the use module.
Sealing now preserves an existing stamp or validates the selected declaration
span by indexed offset. It does not perform trait-name lookup.

An isolated diagnostic compiler passed check, JIT and native execution for the
extended fixture, printing the distinct values from both imported owners and
the local owner. Both lowering implementations produce the selected declaration
span; the isolated CLI check exercises the ordinary file path. After skipping
owner lookup for rows without a trait span, compiler source also passed the
exact-pin carrier's check. Fresh optimized gates and independent completion
review remain open.

## Narrow Reconstruction Inputs

Projection reconstruction now receives ProjectionRebuildSource, which owns
member and trait identity, positional argument labels, output-view metadata
and diagnostic location. The replacement receiver and positional arguments
are explicit inputs. Existing-row callers project the owned metadata; the
inherited-equation synthetic caller constructs it directly. The replacement
receiver remains the sole source of fields used to write the compatibility
mirror on TypeRef. Its old contents cannot be passed as reconstruction input.

The exact-pin carrier passed compiler check, checks of all eleven adjusted
internal fixtures and native execution of projection_member_identity.

## Ownership Materialization Guard

The shared ARC classifier previously accepted an unresolved projection over
String and returned its receiver's ARC class. The expanded record-layout
fixture reproduces this as a native RED. The ARC boundary now requires a
resolved associated output. Record layout search and matching consume the
pooled semantic row directly, without fetching the legacy row as well.

The expanded layout fixture passes natively. The existing materialized
TypeAst controls execute successfully in legacy, foreign and malformed-input
modes, and the extended same-spelled owner fixture passes JIT with a fresh
diagnostic compiler. The materialized control verifies foreign owner
selection itself; the same-spelled alias sealing regression uses the ordinary
file path.

## Type Collection and Remaining Reader Review

The independent follow-up found that scanType can ground an input to a
still-abstract projection, then enqueue its receiver's function layout. The
native record-layout fixture demonstrated that publication on 337560b8.
Collection now defers an unresolved projection before reading its ABI
metadata. The fixture verifies the projection adds no layout and the actual
function type adds one. The native fixture passes. A reified bound-associated
term also uses the shared projection constructor instead of copying the
receiver's mirror in a second constructor.

The follow-up found two further paths to verify: alpha equality and
directional unification can compare a record receiver's ABI name instead of
fields, and the authored-recipe reader appears to group output-view arguments
with the projection trait arguments. Reproduce both paths before closing.

## Structural Record Receivers in Declaration Matching

The expanded native projection fixture reproduced divergent declaration
equality and unification on records that differ only by ABI layout name.
Both comparators now visit record fields using the same head, child and
label readers as exact equality. The fixture verifies equality for equal
fields with distinct layout names, and inequality for distinct fields with
the same name. Top-level receiver-dispatch relaxation still excludes only
outer view children; the recursive receiver and all nested views stay exact.
Native RED and GREEN were observed with the same fixed carrier.

## Source RED for a Parameterized Output View

The following source reproduces a child-coverage failure on the exact-pin
fixed-point carrier and on the diagnostic compiler built from 337560b8.
Removing both `#Mark[I64]` qualifiers makes check and JIT succeed; JIT
prints 42. The visible error on the authored argument type is
“source recipe does not cover canonical type children”.

```plew
use @Std/Io only { print }
trait Mark[K] { fn number() -> I64 }
struct Value {}
impl Value as Mark[I64] { fn number() -> I64 { return 42I64 } }
trait Source { type Item: Mark[I64] }
pub impl Source {
    fn read(value: Item#Mark[I64]) -> I64 { return value.number() }
}
struct Provider {}
pub impl Provider { factory }
impl Provider as Source { type Item = Value }
fn main() { print(<Provider />.read(value: <Value />#Mark[I64])) }
```

The lowering path adds Mark[I64] to the lexical projection's output, then
builds its argument recipe against the receiver's view set, so the canonical
output-view child has no recipe. The signature reader has a related gap: it
takes every child after the receiver as a projection trait argument and
reconsumes only the receiver's view evidence. Fix the producer and the
reader through the existing projection/selector ownership rules. A recipe
count-only repair would leave the projection's own argument range and the
output-view proof unverified. Cover distinct projection and output selector
arguments, selector proof evaluated on the associated output, and ordinary
receiver views.

## Output View Partition Experiment

A scratch implementation added the output-view argument to the lowering
recipe, then limited the reader's projection argument range and preserved
the rebuilt output-view argument metadata. It built successfully. The
positive source advanced from recipe coverage to argument type mismatch at
the call site. A negative control removed the associated-type bound and
made the provided method and its argument unused. The scratch compiler
accepted that declaration, demonstrating that child partition alone
does not enforce the output-view prerequisite.

The experiment was reverted from source and its diff retained in scratch.
The next implementation must save the output selector's proof separately
from receiver selectors and the associated member's own proof, even if
their trait instance keys match. After normalizing the associated output,
the reader must consume that proof against the output and retain the
instantiated view on it. The unused/no-premise declaration must reject
at admission, with a source diagnostic. The existing receiver proof
paths remain preservation controls.

## Output View Evidence Increment

Lowering records output selector argument recipes after the receiver and the
projection trait arguments. Admission saves output proofs with a distinct
subject role, backed by the projection's selected prerequisite, and places
a source diagnostic on failure. The reader uses the projection argument
range and replays the output proof against the instantiated output before
attaching its view.

The diagnostic candidate rejects an unused declaration without the required
associated-type premise with the expected spec/09 diagnostic. A provided
method with Source[I64] and Item#Mark[Bool] succeeds in check, JIT and native
execution and prints 42. The edited compiler source passes check; the final
extension-role hardening was source-checked after that diagnostic build.
Additional extension result-use coverage, broader preservation controls,
fresh optimized gates, and independent review remain required.

## Output View Normalization and Extension Controls

Independent follow-up of 2fe4bbc0 found an equation-key mismatch: the
projection equation was saved with its output view attached, but replay
matches the projection after removing that view. Admission and reading
now retain the bare projection as the equation source and handle the
output views separately. Extension applicability receives the output of
the saved normalization, when available.

The exact diagnostic compiler passed both parameterized output cases in
JIT, the extension case in native execution, two neighboring selected
projection/extension JIT cases, and both missing-premise diagnostics.
The extension test exercises the view as an argument and as a method
result used immediately for a second call.

Independent review also traced an evidence propagation gap to the
result-occurrence traversal, which skips output-view proofs attached to
a projection before following the associated binding's occurrence.
Structural type information alone allowed the new runtime case to pass;
this is not evidence that candidates consumed the retained view proof.
Follow and verify that consumer boundary before closing.

## Retained View Proofs at Method Candidate Collection

Result evidence now follows the associated-output occurrence chain without
discarding proofs attached to the output itself. Extension lookup keeps only
output-role proofs at projection nodes. The trait selector store publishes the
admitted output selector; consumers still require an exact match to the
result type. A direct inferred-binder substitution uses the original authored
occurrence before following the selected output's structural recipe.

An instrumented native compile of associated_output_extension_view observed
two consumptions of a projection-output extension proof at candidate
collection, then the generated program matched both expected lines. The
trait-view fixture now also invokes a method directly on the forwarded
output and succeeds in JIT. The two output-view fixtures and the existing
projected-conformance extension case passed JIT. Temporary instrumentation
was removed, and the final source passed compiler check.

The closure re-review of f226c1f3 caught a final traversal guard in the
wrong branch: reaching a non-projection authored output after accumulating
direct projection proofs incorrectly returned an empty array. Commit
fd53521e returns the accumulated and leaf proofs at that boundary and
retains fail-closed behavior for depth exhaustion. The earlier
instrumented execution is evidence for the abstract-output path only.
A direct concrete-origin proof-count control remains to be confirmed.

Formal self-host validation 20261117T101817-self-host-fd9ec5 started on
fd53521e in an isolated checkout using the exact pinned manifest and the
adopted exact-pin carrier. No result is claimed while that run is active.

Re-review of fd53521e confirmed the normal leaf merge, the fail-closed
traversal limit and the bare equation key on both sides. The reviewer
raised a verification concern about a generic output-view argument:
the declaration admission may save a symbolic selector while final lookup
requires exact instantiated arguments. The concrete Bool fixture cannot
answer it. A scratch generic Source[K] / Item#Mark[K] case and a direct
concrete-leaf proof-count probe are prepared for execution after the
isolated formal self-host run. The review was read-only.

## Fixed Point and Concrete Origin Control

The formal isolated run 20261117T101817-self-host-fd9ec5 reached the second
generation fixed point with identical LLVM, runtime and successor binaries.
Inputs remained unchanged. Its three measurements were 7.992284, 7.414190
and 7.495634 seconds (median 7.495634). The phase-three seven-second target
is outstanding.

A native scratch probe called the internal result-evidence reader with a
projection occurrence pointing at a non-projection leaf. The same probe
failed on f226c1f3 and passed on fd53521e. It verifies keeping the direct
output proof with and without a leaf proof, excluding receiver-role proofs,
and returning no result for a cyclic chain. The optimized fixed-point
compiler also accepted and executed the generic Source[K] / Item#Mark[K]
fixture, printing 42 twice. Runtime output does not by itself demonstrate
which selector path supplied the concrete proof.
