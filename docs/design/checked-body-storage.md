# Checked-body Storage and Implementation Restart

**Status: unresolved physical design; implementation restart gate.** This is a
bounded design worksheet, not a newly adopted representation or a guarantee that
the existing compiler meets the target. [Compiler State](compiler-state.md) owns
session/request guarantees; [Body Checking](body-checking.md),
[Generics](generics.md), [Types and Evidence](types-and-evidence.md) and
[Frontend Handoffs](frontend-handoffs.md) own semantic contracts. This supplement
owns the still-missing concrete storage/API decision and how to establish it.
[The remediation parent](../issues/met-si6j.md) owns scope, stop conditions and
all eleven completion criteria. Worklog owns active execution state.

## Decision to Make Before Implementation

Compare an immutable owner-local checked-body payload against a shared immutable
store with prepared handles. Existing private arrays, append-only stores and
CoW snapshots are bounded progress, not a decision between these alternatives.
Do not assume that adopting Rust's THIR requires a new Plew IR, a whole-program
solver, or another representation of the same meaning. The reference is the
separation of source judgment from its downstream consumption.

Before adding wrappers/private stores, building another candidate, or resuming
paused compiler changes, document concrete fields, identities, transitions,
permissions and failure behavior. A list of attractive type names is insufficient.
The physical choice needs normal architecture approval if not derivable from the
adopted contracts; this document does not silently choose one.

| Question | Required concrete answer |
|---|---|
| Judgment authority | Which producer determines expression meaning, call selection, full compatibility and evidence? Which operation merely constructs a first concrete witness within an already selected abstract requirement? |
| Body ownership | Which session/source domain/body/initializer/closure key owns each row? How do default generators, provided bodies and shared all-global synthetic bodies refer to that source? |
| Stage and API | Actual Building/Prepared/Failed states; allowed readers/writers; success publication and stable failure; legitimate empty payload versus missing/unprepared; inaccessible constructors/rollback policy. |
| Instantiation | Parameter/bound identities, explicit substitutions, receiver and selected evidence bindings; body equality and environment rebuilding preserve all semantic evidence. |
| Consumer inputs | Exact type/result/signature/conversion/completion/pattern/try/aggregate/descriptor inputs, including call recipes and source-independent synthetic places; no missing-fact fallback. |
| Cost | Acquisition, append, retain/copy, lookup, owner indexing, failure cache and publication costs. Avoid per-expression whole-owner/Comp copying and per-body scans of all source tables. |
| Migration and verification | Every old producer/API/reader and replacement, removal conditions, fixture intent, representative final consumer and required correctness/performance evidence. |

## Finite Inventory and Worked Paths

Inventory actual entry points, not just modules. For each record, state its fields,
key, writer, construction reader, final reader, guarantee, remaining obligations,
source owner, instance environment and failure behavior. Classify monotonic
auxiliary classification separately from semantic changes. A private storage
writer alone is not semantic admission or owner success.

Cover expression and statement facts, saved body receiver/parameters/logical
return, source-call membership/templates/signatures, callable constraints,
static/conversion/conditional/associated proofs, projection equations,
closures/dynamic descriptors, local/global bindings, pattern/try/aggregate facts
and final-call publication. Source checking may need registered declaration
signatures before body success; requiring a Prepared body for that construction
query would create a cycle. Async logical return and public Promise result,
extern/bodyless callable admission and source-body preparation are distinct.

Work through these examples using the proposed fields and APIs from producer to
final consumer:

1. Ordinary call, including an argument whose type depends on a preceding call.
   Retain the dependency CallSiteKey: equal result types from different sites
   cannot substitute for the saved dependency identity.
2. Generic requirement/provided call: public obligations -> selected implementation
   derivation -> callee declaration-bound identities -> actual nested body use.
3. Operator and iteration/protocol/try implicit calls with saved complete signatures,
   conversions, lexical owner and unique-dispatch demands.
4. Closure creation versus body request, captured lexical bounds, source signature
   construction versus completed descriptor, local and global closure calls.
5. Single global initializer versus all-global synthetic declaration verification;
   explicit initializer target and independent failure/success caching.
6. Record/enum/array construction and defaults, whole/phantom type arguments,
   aggregate layout, pattern payload/boxing and original lexical Self layout.

Failures must include ambiguity, unresolved source obligations, unprepared and
foreign owners, missing required facts, failed request repeated in the same
session, source/domain mismatch, mismatched evidence/clause/path, and illegal
post-success/post-failure writes. Test empty but valid plans separately. Neither
later lookup nor another owner's success can repair a missing fact.

## Restart Checklist

All five conditions must be satisfied before compiler implementation resumes:

1. Map the parent completion criteria and retained review findings to a finite set
   of responsibilities, concrete fields and final consumers, with one authority.
2. Specify actual types/states/API inputs and outputs, writer/reader permissions,
   failure isolation and how required missing facts cannot masquerade as success.
3. Trace the representative paths above with the same general rules, rather than
   adding call-kind or expression-specific success exceptions.
4. Identify retained/replaced/transient APIs and their removal conditions. Define
   vertical increments that close producer -> publication -> final use and delete
   the superseded decision path; no permanent dual semantic authority.
5. Record specific slice/full-gate/performance plans and resolve outstanding design
   judgments. Review the design before implementation; checks or private arrays
   alone cannot satisfy the checklist.

Then build and validate the **fresh cumulative candidate first**. Do not combine
scoped successes from different old candidates into an all-green claim. Continue
source-selector consolidation, first-concrete preparation versus final-reader
closure, and implicit paths in dependency order; storage cost is part of the same
plan. The parent retains full integration gates and its performance stop rule.

## Verification Matrix

Choose representative invariants across let/assignment/argument/return/give/
field/default/global/closure consumers and numeric literal/array/record/function/
nominal/view/existential/parameter/projection terms. Compare `e` and `{ give e }`
under identical available context; an unannotated temporary can lose context, and
adopted divergence intentionally differs from producing a value. Forward inference
can legitimately differ with source order; committed-type destruction cannot.

Include positive and incompatible-expected/label/ownership/bound controls,
instance-order changes, generated bodies, closure captures, unique cleanup and
AOT/JIT. Malformed internal fixtures must preserve their original test purpose
without restoring public success writers or inventing checked AST rows. Keep
missing authority failure distinct from diagnostic rendering/recovery.

Use input-fixed standard validation in stages. Review-only evidence, an old driver
importing candidate source, a fresh compiler slice, a full normal suite, formal
fixed-point/performance and sanitizers have different scopes. Performance compares
the same source/carrier conditions without concurrent CPU-intensive builds/tests;
historical timings do not redefine the adopted baseline or stop condition.

## Follow-up Ownership

The design gate is [met-j9mv](../issues/met-j9mv.md). Source selection is
[met-ucze](../issues/met-ucze.md); proof/environment closure
[met-ia09](../issues/met-ia09.md); source publication/final facts
[met-acfl](../issues/met-acfl.md); conversion/descriptor consumers
[met-6e6k](../issues/met-6e6k.md). Separate historical stalls are
[met-rzt4](../issues/met-rzt4.md). Broader acceptance combinations in
[com-uutc](../issues/com-uutc.md) are adjacent investigations, not automatic scope.
