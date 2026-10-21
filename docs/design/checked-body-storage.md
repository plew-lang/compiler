# Checked-body Storage and Implementation Restart

**Status: adopted physical design; implementation is not certified by this reference.**
This supplement owns the physical storage/API contract and the gate before the
paused type-checking remediation resumes. [Compiler State](compiler-state.md),
[Body Checking](body-checking.md), [Generics](generics.md), [Types and Evidence](types-and-evidence.md)
and [Frontend Handoffs](frontend-handoffs.md) own the logical guarantees. The
[parent issue](../issues/met-si6j.md) retains scope, eleven completion criteria
and stopping conditions. Describing this design does not certify implementation.

## Adopted Choice and Decision Boundary

Use **owner-local immutable payloads for checked source bodies**, with shared
session-owned immutable type/evidence rows referenced by identity. Keep a separate instance registry for concrete substitutions and discharged
obligations. CheckedBody lowers to frozen parametric Mid first; instance preparation
then produces the existing Concrete Mid/body-instance result, not another typed tree. A session directory owns the source/instance request states; consumers
acquire one body's published payload once and reuse it. CheckedBody is a small read-only handle backed by a private Ref to the sealed
payload, using existing reference ownership; no MutableRef or writer alias escapes
publication. The payload is ordinary compiler data, not a new language IR or
application runtime value.

| Alternative | Benefit | Cost and decision |
|---|---|---|
| Owner-local payload | Completeness, failure isolation and read lifetime align with one body; another body's construction does not write the retained payload | More small arrays/indexes and per-body allocation overhead. Adopted as the simplest enforcement of the owner boundary |
| Shared fact store plus prepared owner handle | Can pack many small bodies and reduce allocations | Requires owner-local sealing, stable append storage, range/index isolation and a reader protocol that never snapshots the growing whole store. Retained as an alternative if measurement shows a material cost of owner-local storage; a private live store with scalar handles need not incur whole-store CoW |

Both can satisfy the logical contract. The choice is not a measured speed claim or a conclusion forced by Rust/Swift.
It is adopted under the delegated internal-design policy because it aligns the
existing owner boundary with fewer mutable-storage invariants, without changing
language acceptance, public ABI, backend or bootstrap strategy. A shared store
remains replaceable behind the same successful-owner reader contract; two valid
layouts do not require leaving the simpler choice undecided. Micro-layout choices
follow the cost/verification criteria below without reopening semantic authority.

## Identity and Stored Fields

The names below specify internal records and operation contracts, not proposed
Plew syntax or a requirement for one source file per record. All IDs are private
to their owning session; zero and an empty range never stand for successful
preparation.

| Record | Required fields and key |
|---|---|
| SourceBodyKey | Session identity, source domain/version and tagged origin: function declaration; closure node plus lexical parent; one global declaration; default generator's declaring member and parameter/field slot; authored provided body |
| SourceBodyHeader | Key, provenance, lexical module and binders/bounds, authored Self/receiver, parameter bindings/types/modes, logical result and completion contract; public async Promise signature is distinct |
| CheckedBodyPayload | Header; owner-local expression, statement/region, binding, operation, conversion, pattern, aggregate, try and closure-construction tables; required-row manifest; immutable local indexes; explicit deferred instance/effect obligations and dependencies |
| ExpressionFact | Source node identity, complete semantic term or typed result recipe, Value/Unit/NoNormalValue tag, shape/place/literal information and projection references. Pending/Unrecorded are builder-only states |
| OperationFact | CallSiteKey, selected declaration or abstract requirement, source signature, receiver/view, binder substitution and evidence, operand/default sources and evaluation order, parameter labels/modes/order, result recipe/projection, completion and obligations |
| UseConversionFact | Source use key (node, role and slot), source/result terms and saved conversion/evidence. A destination use is not another expression type writer |
| Pattern/Aggregate/TryFact | Selected type/variant/field identity, child and binding mappings, payload/boxing/conversion plans, coverage/completion or try carrier/success/error operations as applicable |
| ClosureConstructionFact | Separate closure-body key, authored signature, lexical parent/bounds and binding-identity capture/transfer plan. Construction success does not certify closure-body success |
| CheckedBody | Private strong handle to the sealed payload plus session/source key. Its constructor accepts only successful sealing; copying it retains the same read-only owner-local backing |
| InstanceKey | Tagged origin Authored(CheckedBody identity) or Synthesized(sealed SynthesizedBodyPlan identity), normalized parameter/binder substitution, receiver/view and selected evidence environment, plus preparation configuration that changes the result. Equal layouts are not key equality |
| SynthesizedBodyPlan | Tagged synthetic origin, selected target/signature and boundary conversion/evidence plan; constructs mechanical adapters without fabricating authored source facts |
| PreparedInstance | A read-only publication view of the existing BodyInstance/Concrete Mid: exact InstanceKey, grounded signature/operands/calls and concrete evidence/descriptors with residual execution dependencies. It is neither an independently mutable typed tree nor a whole-program executable token |

A CallSiteKey retains the original source span, origin serial and implicit-call
slot. A result recipe referencing an earlier call retains that exact key; a same-
typed result from another call cannot supply it. Source-independent Mid temporary
places use their own evaluated-place authority, not invented AST rows.

Local table rows use dense local IDs with owner-local indexes from source/use
keys. Nested operand/field/proof lists use ranges into that body's immutable
lists or session type/evidence pools, rather than recursive copied trees. The
index is constructed with its rows and published with them. No reader scans all
owners to find a row, and a global ExprId does not allocate a session-sized sparse
array inside every body. A hash index versus a compact sorted index is a physical
measurement choice; neither may use name spelling as semantic identity.

Shared term/evidence rows are stable immutable values, including their child
ranges. Appending new rows cannot rewrite an existing term or proof. The session
owns these pools and the directory, which never escape as a mutable arena.
CheckedBody/PreparedInstance are usable only while that session remains alive;
external consumers receive owned results/resources, not unsupported borrowed IDs.
Do not copy a whole pool into each payload merely to extend its lifetime. A payload
must not strongly own the session/directory that owns it; use scalar session/pool
identities and explicitly scoped pool readers to avoid an ownership cycle.

## Construction, Publication and Reader API

The source registry is keyed by SourceBodyKey and contains NotRequested,
Building, Succeeded(CheckedBody), or Failed(diagnostic). The instance registry
has its own InstanceKey and the same scoped states. These are implementation
states, not source-language types or one shared ready Boolean.

| Operation | Inputs and result | Authority and failure |
|---|---|---|
| registeredSignature | Declaration/closure signature key and declaration environment → registered callable contract | Declaration construction query, available before callee body success; not an execution grant |
| beginBody | SourceBodyKey and admitted declaration context → private body builder | Source-check owner only; active reentry follows its cycle contract, never returns partial success |
| record/check | Builder plus explicit source/use/binding key → new fact or diagnostic | One source checker constructs permitted unknowns and validates complete compatibility. Candidate probes use private scratch, committing only the winner |
| sealBody | Builder and required-fact/obligation closure → Result[CheckedBody, diagnostic] | Checks all required rows and unresolved source obligations; atomically publishes success or stable failure. No public success factory |
| acquireBody | Matching session and SourceBodyKey → Result[CheckedBody, diagnostic] | Requests/reuses the owner once, without cloning directory/Comp or all fact tables |
| required fact reader | CheckedBody plus local source/use key → required fact or invariant failure | Reads only; wrong owner/session, missing row or missing required dependency is never a source-selection fallback |
| optional fact reader | CheckedBody and a contractually optional key → explicit NotApplicable or fact | Optional absence is not Unrecorded, Failed, Unit or unknown completion |
| constructParametricMid | CheckedBody and explicit immutable pool access → frozen Parametric Mid | Consumes saved values/calls/conversions/completion under source binders. Syntax supplies structure/provenance, not another interpretation |
| constructSyntheticMid | Sealed SynthesizedBodyPlan → frozen Parametric Mid with synthetic origin | Realizes its selected target and boundary plan without fabricated source facts |
| prepareInstance | Frozen Parametric Mid and complete InstanceEnvironment → Result[PreparedInstance, diagnostic] | Grounds retained meaning into existing Concrete Mid and constructs first concrete evidence for its selected abstract requirement; never selects unrelated members |
| executable preparation | Concrete Mid/body instance → prepared executable Mid | Existing access/drop/verification stages discharge their guarantees; LLVM receives this result and the required dependency/publication context |

The builder owns only this body's mutable rows and tentative indexes. On failure,
its semantic rows are not published and its first failure remains stable under
unchanged inputs; later diagnostic collection cannot turn it into success. Valid
interned immutable rows created during a failed probe may remain in shared pools
if they carry no success authority. No global rewind may invalidate other owners.
On success, the builder's storage transfers to the payload and has no remaining
writer. Later analyses append their own result, not rewrite the checked payload.

Expected compatibility, lookup and first concrete witness construction remain
separate named operations of the existing checking/type/evidence boundaries.
Directory lookup or an array's presence cannot certify either. Extern/bodyless
callables use registered foreign/intrinsic contracts without manufacturing an
empty successful source body.

An all-global synthetic verification/request root aggregates per-global results;
it is not a SourceBodyKey and cannot stamp every initializer successful. Runtime
initialization publication remains separate from checking. Mechanical adapters
consume a sealed SynthesizedBodyPlan with exact selected targets/conversions;
this separate producer contract does not fabricate a checked source body. Provided body instances
retain their authored owner and binders; they do not overwrite it with the adopting
type. Default expressions retain their authored source IDs under distinct generator
keys. Captured lexical contexts and instance environments must not be recovered
from a mutable ambient cursor.

## Worked Producer-to-Consumer Paths

1. **Ordinary calls and prior results.** Source checking registers signatures,
   commits operation A and its result, then checks B's argument using that result.
   It saves B's operand recipe with A's exact CallSiteKey, complete signature and
   use conversion. Parametric Mid construction preserves that operation/recipe
   under source binders. Instance preparation grounds it and its evidence into
   Concrete Mid, followed by ordinary executable preparation; no typeOf/name lookup remains in
   the final reader. Missing A or a mismatched key fails preparation.
2. **Generic/provided/implicit calls.** An authored generic body saves its selected
   requirement and binder-owned evidence. Each instance binds caller evidence to
   the callee declaration's binders and constructs the first concrete witness only
   for that requirement. Operators, iteration and try are distinct operation slots
   under the same record contract. Mid consumes the concrete target and saved
   result projection, including Ord-to-Bool and Ne negation, without another selector.
3. **Closures.** Construction saves captures and signature under the enclosing
   CheckedBody. The closure-body request uses its own key and inherited lexical
   bounds; local/global binding use reads the saved binding/descriptor identity.
   Requesting a closure's signature does not require its body already Succeeded.
   Instantiation prepares environment/call/destruction entries from those records.
4. **Globals and defaults.** Each initializer/default generator seals independently
   under its explicit declaration/slot key, including field default expressions
   reused from authored syntax. Synthetic whole-global analysis combines the
   outcomes. Global readers consume registered-and-validated binding terms; the
   Driver's startup plan consumes initializer effects and successful publication,
   rather than using one synthetic-function sentinel as proof for every global.
5. **Aggregates and conversions.** Array/record/enum source checking records the
   complete type (including phantom parameters), children/default order and each
   use conversion. A return/give/argument consumes its recorded use, not a type
   reconstructed from its destination. Pattern payloads and lexical Self layouts
   follow the saved mappings into concrete Mid places and cleanup.
6. **Completion.** Region checking records normally yielding values and targeted
   source exits. Instance/Mid consumers preserve those tags and targets; they do
   not infer value presence from term zero, a final give, or LLVM reachability.
   Analytical loop warnings remain separate from source divergence.

These paths share the same publication protocol. None permits a missing source
fact merely because an internal function, closure, newtype or synthetic body is
involved. See [Frontend Handoffs](frontend-handoffs.md) for each record family's
logical detail; this supplement does not duplicate those rules into a new solver.

## Migration Units and Removal Conditions

This is a finite migration map, not permission to wrap all current tables in a
new success token and keep the old selectors. At implementation start, reconcile
actual symbols against the selected cumulative revision; remove each superseded
family in the increment that moves its final consumer.

| Current family / search anchor | Replacement and final consumer | Removal condition |
|---|---|---|
| Frontend Comp.semanticExprRecords, semanticAggregates/Tries/Matches, bindings/statements, preparedSemanticFacts | Owner-local builder/payload/indexes; Mid expression/pattern/try/aggregate readers | No successful payload retains all-owner mutable fact arrays; no completed consumer reads the old family |
| Record(false)/Generic/Declaration/Record(true) source selection routes and staticMemberResolution | One source-call construction operation and saved OperationFact; instance witness preparation | Completed-reader and declaration-worklist paths consume saved selection rather than rerun AST candidate selection |
| Source call templates/constraint plans, sourceCallArgumentType / PriorCallResult | Per-owner operations with complete CallSiteKey dependencies, constraints and callee evidence environment | Signature, prior-result and final-call readers consume matching saved records without type-only identity substitution |
| semanticBodyReturnTerm / typeOf / groundedTypeOf and receiver/local reconstruction | Saved source header plus instance grounding and binding facts | Remove final-reader reinterpretation; retain narrowly named declaration-construction queries where genuinely needed |
| Shared global synthetic sentinel / initializerResult and global closure assumptions | Per-declaration source outcome plus aggregate request result; global Mid/startup consumers | No global inherits success from another global or one all-global request |
| Concrete descriptor/conversion/Mono publication and fallback paths | PreparedInstance dependencies and explicit source/instance keys | Final concrete consumers reject missing evidence and preserve selected origin; adapters only transform representation |
| Internal fixture writers injecting source type/flow rows | Normal source preparation plus deliberate corruption, or genuine Mid-only input | Fixture intent and negative controls remain; no public payload factory or fabricated success for convenience |

The inspected candidate at `2983c47f` has a PreparedSemanticFacts value whose
acquisition snapshots the Comp's all-owner semantic arrays (Frontend.pw,
preparedSemanticFacts). This limited read explains the migration anchor; it is
neither a current miscompile reproduction nor measurement of its cost. Existing
successful call/proof/pattern/try/aggregate work must be preserved, not discarded
because its storage changes.

## Cost, Measurement and Reconsideration Criteria

The architectural invariant is body-local semantic backing, not a promised exact
allocator count. For B bodies and F total facts, retained source facts/indexes
must be O(B + F), excluding separately owned shared terms/proofs. Sealing visits
only that owner's rows/dependencies; it must not scan every session fact for each
body. Acquiring one handle retains the sealed owner once per consumer; fact readers
use its private backing without materializing a full payload/array snapshot; it must not add a whole-body/whole-Comp retain/copy on every expression.
Appending another body's facts must not CoW-clone published semantic backing.
Exact lookup complexity/index load factors and small-body packing can be refined
without changing the successful-owner reader interface.

Before replacing the adopted layout with a shared store, demonstrate a material
allocation/memory or same-source compile-time cost and a concrete append/seal/
reader design that preserves these invariants. Merely reducing the number of
record types is not evidence. If owner-local arrays need packing, compare packed
immutable slabs behind the same body boundary before introducing a second global
semantic store.

Implementation verification compares the fresh cumulative candidate on identical
source/std/dependencies/carrier/toolchain conditions. Establish its baseline first.
Use focused counters outside formal timing to observe payload acquisitions,
facts visited per seal, whole-table copies/CoW and peak memory across many tiny
bodies, one large body, many instances of one generic body and interleaved JIT
requests while earlier readers remain alive. Formal fixed-point/performance runs
exclude diagnostic counters and concurrent builds. The parent's current performance
condition applies; baseline failure requires investigation, not relaxed acceptance. Correctness/ownership/target eligibility cannot be selected by timing.

## Restart and Validation Gate

Before compiler implementation resumes, reconcile each reviewed migration row
with concrete producers,
registered-signature queries and final readers in the selected cumulative input.
Each increment closes producer → publication → final use and deletes its replaced
authority; do not schedule an isolated store-only or verifier-only increment.

The parent completion criteria map as follows: contextual/committed type rules
and completion (1/2/5/6) use saved expression/use/region facts; authoritative
selection/signature/evidence (3/4/8) use operations, headers, registries and explicit
instance environments; controls/mode parity (7/9) use the common producer and
worked paths; correctness/performance/documentation gates remain 10/11. This map
does not mark any implementation criterion complete.

After reconciliation, establish the cumulative baseline before extending it.
Reuse recorded success only when its input, compiler and execution conditions
match; a new session alone does not require repeating the same baseline. Changes
or unverified conditions require the affected validation gates. The owning issue
and meta worklog retain the selected input and evidence, not this contract.
Stage slice validation through (a) source owner/signature,
(b) calls and evidence through concrete final consumers, (c) remaining implicit,
closure/global/default/conversion paths, with each affected old path removed.
Run required full gates and formal fixed-point/performance at integration points;
scoped old-driver imports or successes from different candidates cannot replace
them. Normal/generation/dependency/ASan-LSan coverage remains required by the parent.

Positive/negative coverage includes matching versus incompatible expectations,
`e` versus `{ give e }` under the same available context, signature labels/modes,
instance-order changes, generators/provided bodies, source divergence/loop warnings,
unique cleanup and AOT/JIT. Corrupt required facts, owners, environment/binder
identities, prior-call keys and post-success/post-failure writes. Test legitimately
empty payloads separately from missing/unprepared results; keep failure stable on
repeat and old readers valid when another owner is appended. Verify final output
or source rejection, not only table-reader tests.

[met-j9mv](../issues/met-j9mv.md) owns design/adoption/restart reconciliation;
[met-ucze](../issues/met-ucze.md) source selection;
[met-ia09](../issues/met-ia09.md) callee proof/environment closure;
[met-acfl](../issues/met-acfl.md) source publication/final facts;
[met-6e6k](../issues/met-6e6k.md) conversion/descriptor consumers.
[Historical stalls](../issues/met-rzt4.md) and broader [acceptance investigations](../issues/com-uutc.md)
do not silently expand this implementation scope.

## Reference Comparisons

[Rust TypeckResults](https://doc.rust-lang.org/nightly/nightly-rustc/rustc_middle/ty/struct.TypeckResults.html)
retains owner-scoped node types, selected definitions and adjustments. Its
[THIR](https://rustc-dev-guide.rust-lang.org/thir.html) is body-oriented typed
lowering and can be discarded after its consumers; adopting that boundary does
not require copying THIR into Plew or retaining a second full typed tree.
[Swift's RequestEvaluator](https://github.com/swiftlang/swift/blob/main/docs/RequestEvaluator.md)
illustrates explicit request caching/dependencies/cycles, not a requirement for a
universal request framework. Plew's owner-local value backing specifically
addresses private publication and CoW costs; its actual performance is to be measured.

Independent comparison supported the simpler owner-local boundary while retaining
the shared-store alternative. Corrective review aligned parametric-Mid ordering
and authored/synthetic instance origins with the canonical pipeline. This review
is design evidence; it neither measures the layout nor completes implementation
acceptance or authorizes bypassing the restart baseline.
