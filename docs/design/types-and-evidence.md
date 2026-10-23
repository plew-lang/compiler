# Types and Semantic Evidence

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## 1. Responsibility and Boundaries

The semantic type subsystem represents what a type means, applies explicit substitutions, and answers structural relations. Conformance resolution establishes why an operation or conversion is permitted. These responsibilities share type terms but do not collapse into one equality predicate.

[Name lookup](name-lookup.md) resolves declaration identities and candidate provenance. Body checking owns source applicability and publishes the selected operation, its types, and its evidence. Instantiation substitutes that result and discharges retained obligations. Mid and the backend consume the result; neither repairs missing evidence by searching for another implementation. Physical layout and calling convention are downstream concerns, not semantic type identity.

The language specification owns [generic abstraction](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/06-generics.md), [traits and associated types](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/08-traits.md), and [extension views](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/09-extensions.md). This chapter specifies representation and decision ownership, not additional inference or specialization rules.

## 2. Semantic Terms and Identity

A source type annotation has a location and spelling. A semantic type term has resolved meaning. Diagnostic locations remain attached to uses and results; they are not part of type equality or canonical keys.

| Meaning | Information that must survive |
|---|---|
| Nominal type | Declaration owner and recursively represented type arguments; package/module identity comes from the owner |
| Generic parameter | Lexical binder identity, not its spelling or its position in an ambient list |
| Associated-type projection | Receiver, trait owner, complete positional arguments, and associated-member identity |
| Anonymous record | Field labels and their semantic child types; physical slot order is separate |
| Function type | Parameter/result types and the language's labels, passing modes, and callable properties, including invocation divergence |
| Existential type | Trait constraint and retained capability guarantees; it is not a generic parameter or a nominal conformer |
| View-qualified type | Underlying term and resolved view provenance, preserving extension sources separately from a trait selector |

These are semantic categories, not a requirement to introduce another IR or one new class per row. Existing carriers are acceptable only if all operations preserve the same information. A function value whose invocation diverges can still be constructed and stored; its invocation property does not make construction diverge. Control-flow completion is not a fabricated value type.

Two declarations named `T` introduce different parameters. A nominal type with the same printed name in another module is also different. Conversely, two source occurrences of the same resolved type need not create two semantic identities. Interning can make repeated structural comparisons cheap, but an interned ID is meaningful only in its owning compilation domain.

Traversal, folding, equality, substitution, occurrence checks, and canonical-key construction must cover the same semantic children. A cached structural property must be derived from those children and remain valid after publication. Comparing only a head name or omitting projection/view children is not a permitted fast path. Recursive newtype children, unresolved terms, and repeated view sources in an input representation must also remain visible to structural queries. A reader optimization cannot infer closedness, uniqueness, or identity by skipping them. Deduplication and canonicalization must follow the explicit normalization contract; they are not incidental consequences of an index or traversal shortcut.

## 3. Relations Are Explicit

Keep the following questions distinct:

- **Exact identity:** are these canonical terms structurally identical in the same identity domain?
- **Contextual compatibility:** does the language allow this already determined source type at this destination, with which conversion?
- **Inference matching:** which explicitly designated inference binders can be bound by these inputs?
- **Conformance:** does this subject satisfy this trait constraint in this resolution environment?
- **Grounding:** what does this saved term or proof become under this explicit instance environment?

An expected type can guide an unresolved literal or child expression; it cannot overwrite an incompatible completed type. Compatibility must inspect the completed aggregate or function type and retain required conversion evidence. A block wrapper does not authorize a second interpretation of its result. The body-checking chapter owns the order and publication of contextual inference.

Directional matching binds only the declared pattern/inference binders. Query-side generic parameters remain rigid. A failed candidate's tentative substitutions must not escape into another candidate or become a successful proof. Structural mismatch, conflicting bindings, and a valid obligation deferred until instantiation are different outcomes.

## 4. Substitution and Projection

Substitution takes a term and an explicit mapping from lexical parameter identities to replacement terms. Receiver `Self`, associated-type evidence, and the source declaration's binder environment are explicit inputs where required; the current code-generation cursor is not a substitute for them.

Apply a parameter map simultaneously: a replacement belongs to the caller's environment and is not recursively subjected to the same map. For a recursive generic call whose replacement is `T -> Box[T]`, substituting one occurrence of the callee parameter produces `Box[T]`, not an unbounded sequence of nested boxes. Resolving a remaining projection inside that replacement is a separate evidence-driven operation; it does not reapply the original parameter map.

A projection such as `T#Iterator.Item` retains its receiver and exact trait instance while abstract. A bound may justify it without a concrete conformer. Instantiation can produce its concrete associated output from the retained evidence. It must not resolve the printed word `Item` as a new nominal name or choose a different trait because another implementation happens to return the requested output.

Symbolic but justified terms are valid abstract results. Missing evidence and unfinished inference are not. A consumer requiring a concrete result must reject or defer that request explicitly, rather than treating an unresolved projection as an arbitrary layout-compatible type.

## 5. Conformance Evidence

A trait instance is identified by its trait owner and positional type arguments. Associated-output predicates constrain the selected instance's outputs; they are not additional inputs that select an implementation. The subject and resolution environment are also necessary to ask a conformance question.

Static evidence records the derivation, not merely `true`. Relevant derivations include a concrete witness and its impl-binder substitution; an authored bound; a path from a bound through declared supertraits or trait-subject edges; the implicit `Self` constraint of a trait-provided body; and a concrete trait path with its terminal witness. A path retains each edge's instance, conditions, and substitution, including the edge that owns associated outputs. These categories describe evidence obligations; they are not a stable serialized enum specification.

Existence, source conformance admission, and executable selection have different completion criteria. One valid derivation can answer an internal existence query, but cannot admit a source bound, selector, or existential conversion on its own. Source admission requires the specification-valid unique path, even for an unused or empty bound. Distinct trait-subject branches remain ambiguous when they share a terminal witness. Repeated discovery of the same declaration path is deduplicated; distinct paths are not merged by endpoint or machine layout. An abstract member call records its selected requirement and justified obligations; it does not need a concrete witness during source checking. For static dispatch, before executable publication instantiation must establish the unique terminal witness for that selected source, rejecting conflicting terminal implementations. Dynamic existential calls instead retain the selected requirement and runtime dispatch slot; their runtime conformer need not be known statically. A unique executable endpoint is an additional requirement for static dispatch, not a replacement for source path admission. Canonicalization of a path preserves its edge owners, substitutions, source/view selection, and declaration environment. A shared provided body checks its own requirement calls in its declaration environment; its caller's path does not implicitly prioritize unrelated requirements inside that body.

Query completion distinguishes missing, found, and ambiguous answers as data. A conditional implementation whose required conformance is missing or ambiguous is inapplicable; this must not emit an admission-site diagnostic that prevents selecting another implementation. Malformed or foreign evidence remains an error. Boolean eligibility and proof-requiring admission are explicit projections of the same query, with an explicit demand at every call site. No default presence check may silently authorize a source bound.

Normalize query input completeness against the selected declaration. In particular, omitted inputs of a zero-arity trait already identify its exact empty positional instance; they must not suppress exact-premise handling as an open-input search. Openness is a query facility, not an extra component of source-path identity.

For an exact abstract subject and trait instance, an authored premise is opaque authority. An alternative derived path does not compete with, replace, or supply missing associated outputs for that premise. Equivalent premises for the same subject and instance can retain a stronger compatible output fact without becoming different source paths; ordinary retained proof identity is unchanged. For concrete and derived paths, collect the applicable source paths before checking requested associated-output equalities. A matching output cannot select one of several paths, and an incompatible explicitly preferred path cannot fall back to another path.

View-dependent queries preserve the normalized extension source set and separate trait selector described in [name lookup](name-lookup.md). For a subject and exact trait instance, applicable explicit extension sources shadow the bare source; competing sources at the same priority are ambiguous. Applicability conditions are established before checking associated-output equality. An output mismatch must not revive a shadowed bare implementation. Existence, projection, member selection, and existential boxing must use the same source-selection rule.

Runtime existential evidence supports dynamic dispatch. It is not static entailment for an arbitrary generic bound. Boxing a concrete value into `any P` retains the exact static conformance used to build its runtime evidence; backend witness construction must consume that selection rather than perform another source search.

An existential interface's hidden Self is a rigid, universally scoped subject.
Its exact interface premise, declared supertraits and associated constraints are
retained guarantees; caller-owned types and premises remain explicit and separate.
Erasing to any P is not a #P selector for other traits. A trait-subject edge
impl P as Q alone does not guarantee a unique Q conformance for every possible
hidden conformer: another subject path may compete. Such an edge cannot silently
satisfy a hidden-Self method condition. Declaring P:Q makes that Q promise part of
the interface contract and requires conformers to establish it. Unavailable
members do not prevent existential formation.

### Capability and Conditional-Selection Contracts

The [language capability rules](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/06-generics.md) for copyable / unique / allowunique extend the same evidence pipeline. They do not authorize a second source selector in Mid or the backend.

| Producer | Published semantic contract | Final consumers |
|---|---|---|
| Parameter/trait/associated-type declaration checking | Allowed capability range under lexical binder or requirement identity; complete associated bindings and source locations | Abstract body checks, shared applicability, and conformance admission |
| Nominal type finalization | Ownership edges and a normalized copyability condition over declared parameters; sendability and destruction obligations kept separately | Instantiation, value operations, destruction and sharing analysis |
| Conditional candidate-family checking | Source-selected candidates, applicability predicates, proof of disjointness and coverage, and one compatible call contract | Instance-specific selection and witness preparation |
| Source call/conversion checking | Exact admitted conformance path, source requirement, modes, conversions, and any opening/re-erasure plan | Instantiated calls, dynamic slots and explicit Mid conversions |

For example, an aggregate directly owning two parameters can have `Copy(T) AND Copy(U)` as its finalized condition. A shared handle owning a cell reference has its own copyable handle contract even when its referent is unique; it does not recursively acquire the referent's copy prohibition. Use declared ownership edges, not pointer layout or every type mentioned inside a field. A private owned field can change a public autounique type's copyability condition, so such a change affects its public capability contract despite field privacy. Recursive capability derivation and finite physical-layout validation are separate checks. Sendability additionally includes selected destruction/effect obligations; copyability is not a substitute for that proof.

Predicates reference canonical type/projection terms and binder identities, not spelling. Equality normalization must not discard conformance-path provenance. Keep recursive active, ready, failed and deferred states distinct. Use the common bounded capability/equality decision contract below and saved derivations; proving every arbitrary trait formula satisfiable is not required. Diagnostics distinguish a proved overlap from failure to prove disjointness within the supported reasoning. Both can reject a candidate family, but unknown is not proof of overlap. A condition that cannot yet be discharged is not `false` and cannot justify a copy, a missing destructor, or an arbitrary candidate.

Readers keep a reference to this contract plus an explicit substitution rather than independently reconstructing its conditions. Two equivalent normal forms may share storage; callers' explicitly selected sources do not become interchangeable. [Instantiation](generics.md#capability-discharge-and-witness-admission) owns concrete discharge and [ownership](ownership-and-access.md#standard-reference-projection-handoff) owns place/value use.

### Structural Recursion and Shared Capability Decisions

For a closed finite structural ownership component, capability derivation uses
the **least fixed point of may-be-unique**, equivalently the greatest fixed point
of copyability. For an autounique aggregate, may-be-unique is the disjunction of
its owned field/payload conditions over every variant. Fixed unique/copyable
declarations supply constants; binders and justified projections supply their
declared ranges or symbolic atoms. A fixed-kind summary does not excuse checking
that its owned fields and type arguments are permitted in that declaration.

For example, `U(List[T]) = U(T) OR U(List[T])` yields `U(List[T]) = U(T)`.
Starting from "not yet known to own unique" and propagating positive ownership
dependencies selects this solution. A cycle alone is not evidence of a unique
payload. The result does not depend on whether a finite inhabitant exists;
recursive layout legality and inhabitation are different questions. For shared
handles, follow their declared ownership contract rather than the referent's
copy prohibition. Sendability and destruction do not inherit this stopping rule.

The domain owner constructs equations over canonical nominal identities,
explicit substitutions and owned-edge relationships. It closes components over
that graph, retaining finite symbolic conditions instead of enumerating concrete
uses. A recursive summary graph/schema is permitted; flattening every condition
into a copied formula is not required. This rule applies when normalization and
saved summaries close over finitely many terms/atoms. It does not claim that an
unbounded chain of changing associated projections is the same finite problem.

Provisional component state is private. Publish a summary only when its equations,
chosen solution contract, binder identities and outgoing obligations are complete
for its advertised scope. Active visitation alone publishes no capability truth.
Recursive summary references belong to this typed component artifact; they do
not permit cycles or unfinished nodes in the ordinary conformance-proof DAG.
Readers retain a summary identity and explicit substitution. A symbolic summary
can be complete without an executable copy/drop classification being discharged.

Use dependency worklists and shared immutable conditions so that unchanged
components/atoms are reused. No runtime classifier or payload scan is introduced.
The contract does not promise linear cost for arbitrary symbolic formulas, and
resource exhaustion cannot be converted into a guessed capability. Changing
type arguments/projections use the bounded expansion rule below; discovering
that a sequence is infinite is not a prerequisite for stopping.

One capability relation owns applicability, pairwise overlap and domain coverage
queries for saved candidate families. Its inputs include the admitted capability
domain, canonical terms, selected family/summary identities, explicit substitution,
and retained equality/conformance evidence. It distinguishes positive proof,
counterevidence, unsupported/unproved requests, justified residual obligations,
resource exhaustion and invalid input. These distinctions need not be one enum.
Only evidence appropriate to the requested publication scope authorizes success.
In particular, family admission cannot defer required disjointness or coverage
merely because concrete instantiation will eventually pick a branch.

Ordinary calls, via and conditional deinit consume the same relation and saved
derivations. This is not another source selector. Proof of Boolean coverage alone
does not establish labels, modes, result compatibility or valid absence of deinit.
The following minimum fragment and fixed analysis limit implement the
specification's bounded reasoning rule.

### Bounded Capability Reasoning and Analysis Limit

The common relation supports capability atoms on canonical terms, constants,
and finite AND/OR/NOT combinations of those capability conditions. Copy(T) and
Unique(T) are complements within the admitted two-class domain. Parameter, Self
and associated-type declarations supply domain restrictions; completed nominal
summaries supply derived conditions. Equality uses exact semantic identity and
equations already justified by retained conformance/associated-binding evidence.
It does not search for a different conformance to obtain a convenient equation,
infer arbitrary negated trait requirements, or introduce new source predicate syntax.

Normalize through those saved summaries/equations, then answer finite capability
obligations through one shared propositional decision procedure. Representations
may share condition nodes; no particular SAT/decision-diagram library is required.
For admitted domain D and recorded branch predicates F_i, disjointness requires
proof that `D AND F_i AND F_j` is impossible for each distinct pair; coverage
requires proof that `D AND NOT(OR(F_i))` is impossible. Preserve the domain and
normalization derivation with the result. A model that disregards required type
relationships is not proof of a real overlap; unresolved relationships retain
their unproved outcome instead of authorizing a fabricated counterexample.

Use **one fixed semantic expansion-depth limit L** for this procedure initially.
A root request starts at depth zero. Following an unresolved normalization,
projection, summary substitution or decision branch adds one along that chain;
sequential rewriting also preserves that chain depth instead of resetting it.
Check before expanding past L and return a distinct AnalysisLimit outcome.
Sibling branches use the same parent depth. Ordinary worklist iteration within
an already discovered finite structural SCC is not repeated descent through its
self edge; it still must complete its fixed point before publishing a result.

L is an implementation constant, not a language-level numeric guarantee. Select
its initial value with the capability implementation and representative controls;
the design does not need that number to define the protocol. No user override,
infinity detector, extra rule-count/size budgets or elapsed-time acceptance rule
is part of this initial contract. A depth bound alone is not a bound on total
branching work; broader cost controls require a separately justified change.

An AnalysisLimit may stop a finite request that would succeed with more work.
The diagnostic identifies the requested relation and its source and says the
analysis limit was exceeded, not that recursion was proved infinite. It is not
false, an overlapping family, a default capability or permission to omit drop.
The required proof cannot be deferred past source admission or executable
publication merely to avoid the limit. A justified abstract residual obligation
still has its ordinary scoped meaning; it is not failed analysis relabeled ready.

All consumers share this limit and outcome contract. Incidental helper calls do
not consume semantic depth, and wrappers may not reset it. Memoized proof/limit
results must respect their available-depth assumptions; an overflow result cannot
be cached as a context-free negative answer. Reuse of a completed source artifact
is distinct from pretending an unfinished request succeeded.

| Control | Required result within the shared rule |
|---|---|
| Complementary copyable/unique branches | Prove one applicable branch over the admitted domain, subject to the common call contract |
| Pair owning A/B; recursive List owning T/rest | Preserve Copy(Pair)=Copy(A) AND Copy(B), Copy(List[T])=Copy(T); do not unfold runtime list length |
| Established associated binding T#Link.Next=U | Use the retained identity/evidence and U's capability condition |
| Copy(T) alone used to assume Copy(T.Next) | Reject the unjustified implication; an allowunique associated type may be unique |
| Candidate overlap or missing coverage | Preserve a proved error separately from unproved/unsupported relations |
| Changing projection chain or finite deep query exceeding L | AnalysisLimit, with no infinite-recursion proof or capability guess |
| Cold/warm memoization and indirect call/via/deinit consumers | Preserve the same promised evidence, depth assumptions and outcome distinctions |

For example, an owned recursive Chain[T] whose next payload is Chain[T#Link.Next]
may normalize back to a known node or finite summary. Its declaration is not
automatically forbidden. A particular required classification that keeps expanding
is stopped by L regardless of whether that expansion would eventually close.
Source capability proof and endlessly growing concrete code-instance generation
remain distinct requests and diagnostics.

This selects a small proof boundary plus a fixed cutoff instead of an analysis
whose job is to prove nontermination or accept every terminating query.
[Rust's recursion limits](https://doc.rust-lang.org/reference/attributes/limits.html)
and [Swift's bounded completion](https://forums.swift.org/t/the-requirement-machine-a-new-generics-implementation-based-on-term-rewriting/55601)
are precedents for stopping finite expensive work too. Plew does not import
Swift's several budgets, Rust's override syntax or either general trait solver.
The [R1/R2 resolution](../issues/met-yotl.md) records scope; implementation and
actual numeric tuning remain separate from this adopted design.

[Rust coinduction](https://rustc-dev-guide.rust-lang.org/solve/coinduction.html)
motivates an explicit solution for recursive structural properties, not universal
coinduction for Plew trait proofs. [Swift SE-0427](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0427-noncopyable-generics.md#recursive-copyable)
illustrates why growing associated-type conditions are a separate problem. A
field rescan per consumer or an Active-as-success shortcut would violate the
single derivation authority; a general trait solver is unnecessary for the finite
structural component covered here.

## 6. Publication and Consumption

A successful checked operation carries its source and destination terms, selected declaration/requirement, instance substitution, dispatch kind, and conformance/conversion evidence as applicable. Identity conversion is an explicit valid result; missing conversion evidence is not identity. Evidence retains the source owner and environment needed to interpret its binders.

For example, checking a generic iterator operation first records the requirement selected under `T: Iterator` and its abstract result `T#Iterator.Item`. A concrete call supplies a valid witness and substitution. Instantiation grounds both the result type and the selected requirement through that evidence. Mid receives the instantiated operation; LLVM realizes its chosen target or dynamic slot. A new search for an `Item` type or same-named method anywhere along this path breaks the contract.

The [computation lifecycle](compiler-state.md) applies to evidence requests. A valid symbolic proof can leave explicit instance obligations; failure, active recursion, absence, and ready evidence remain distinct. Cache identity includes all meaning-changing inputs: subject, constraint, extension sources, selector, visibility, bound environment, and static/runtime mode. A smaller key requires proof that omitted inputs cannot affect that query. Existence-only results cannot masquerade as uniquely selected executable witnesses.

Published terms and evidence are immutable. Recursive evidence is saved child-first, then the parent is published. Append-only pools must preserve old IDs and keep each parent's variable-length range contiguous even when constructing children appends to the same pool. Readers validate ownership, kind, range, and required completeness; validation does not become a second selector.

Sharing immutable terms and proof IDs avoids repeated recursive value copies. Indexes may exclude impossible candidates, but cannot discard semantic distinctions. The [checked-body storage contract](checked-body-storage.md) uses owner-local sealed payloads with shared session pool identities; it does not prescribe copied proof trees or another universal global pool. Its implementation remains separate.

## 7. Change Impact and Verification

A new type form changes every structural operation, canonicalization, diagnostic rendering, and affected instance/conversion consumers. A new projection or conformance path changes evidence production, substitution, publication, and final witness use. Changing source priority affects all conformance queries, not just method lookup. Adding a physical ABI representation normally changes downstream lowering without changing semantic identity.

Tests should distinguish same-spelled binders and nominal owners, nested function/record/array substitutions, recursive caller-owned replacements, abstract and concrete projections, output mismatches after source shadowing, competing paths, existential boxing, and missing conversion evidence. Freeze/read tests must include nested siblings and previously published IDs. Source tests must follow selected evidence through instantiation and execution; equal type IDs or a successful proof-reader test alone do not establish final-consumer closure.

## 8. Comparisons

[Rust's semantic type representation](https://rustc-dev-guide.rust-lang.org/ty.html) separates written type syntax from semantic types and uses interning for identity. Its discussion of inference and normalization also shows why interned equality cannot answer every compatibility question. Plew adopts that separation while retaining its own forward inference rules and labeled function types.

[Rust's trait-solving guide](https://rustc-dev-guide.rust-lang.org/traits/resolution.html) distinguishes obligations justified by generic bounds from concrete implementation selection and nested obligations. That distinction supports abstract checking here. The page describes an older solver architecture; it is not authority for Plew to repeat selection in later phases or adopt Rust's complete solver policy.

[Swift's substitution maps](https://github.com/swiftlang/swift/blob/main/include/swift/AST/SubstitutionMap.h) carry replacement types together with conformances used to derive nested types. Its [conformance representation](https://github.com/swiftlang/swift/blob/main/include/swift/AST/ProtocolConformance.h) exposes requirement witnesses and associated-type witnesses. These are useful precedents for preserving both substitutions and evidence. [Swift generic signatures](https://github.com/swiftlang/swift/blob/main/docs/ABI/GenericSignature.md) provide a further precedent for canonical constraint identity; Plew retains its own capability ranges and explicit conformance-path choices rather than merging proofs by endpoint. Plew's explicit extension source sets and separate trait selector require their own provenance, rather than a direct copy of Swift's lookup or conformance model.

## 9. Implementation Mapping and Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. Focused inspection covered `TypeTerm`, legacy `TypeRef`, and `StaticConformanceProof` in [Ir.pw](../../src/Ir.pw), and the append/read representation in [StaticProofs.pw](../../src/Ir/StaticProofs.pw). The current proof enum includes bound paths, supertrait paths, and trait `Self`, beyond the shorter historical three-category summary. Existing names and scalar IDs do not by themselves establish the complete ownership guarantees described above.

The retained frontend contracts identify the intended simultaneous substitution, source-selection, and conversion-evidence boundaries. This chapter has not audited every structural visitor, cache key, projection grounding path, or backend witness consumer. No compiler execution or performance measurement was performed. Complete replacement of legacy `TypeRef` interpretation and independent selection remains unverified; absence of a [local issue](../issues/README.md) link does not establish that an unverified path meets the adopted contract.

Chapter review checked responsibility boundaries, specification alignment, retained evidence, and the Rust/Swift comparisons. The clarification separating abstract requirement selection from concrete executable witness preparation was incorporated; no required correction remained in that scope. This review was not a complete implementation audit.

## Retained Follow-up Investigations

[semantic type and retained-evidence coverage](../issues/com-uutc.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
