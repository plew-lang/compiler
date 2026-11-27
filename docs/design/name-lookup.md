# Declarations, Scopes, and Name Lookup

**Status:** Reviewed draft. This chapter defines decision boundaries and required information, not a completed audit of the current resolution passes.

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## 1. Responsibility

Declaration registration establishes identities and declared interfaces. Scope construction determines which bindings are available at a source position. Lookup returns the applicable binding or candidate set with its provenance. Semantic checking determines call applicability and selects the source operation; concrete instantiation may later determine the concrete witness for an already chosen abstract requirement for the first time.

The purpose is to prevent a name index, visibility helper, or downstream pass from becoming a competing selector. A contributor changing imports, overloads, or generic member access should be able to identify the owner of each decision and the result that later stages consume.

Module membership and package reachability are inputs from [Sources, Packages, and Modules](sources-and-modules.md). This chapter does not select dependency revisions, type-check bodies, choose ABI layouts, or authorize execution.

## 2. Registration and Identity

Registration associates each declaration with its kind, lexical/module owner, source origin, declared signature, public status, and relevant binder identities. Bodies can be requested separately; registering a callable signature is not successful body checking. Mutually recursive calls can use registered signatures without recursively preparing their callees while checking one source body.

Aliases and re-publication preserve the original declaration identity. An imported local name is a binding to that identity or overload set, not a copied declaration with new visibility rights. A generated callable also needs an explicit semantic owner and origin; appended synthetic text cannot determine its privileges.

### Shared Module Binding Admission

Module scope construction admits one binding per name across nominal types
(struct, enum and newtype), traits, named extensions, free functions, globals
and imported namespace/selected/alias bindings. The sole multi-declaration
binding is a valid free-function overload set. Registration and use/public-surface
construction share this conflict authority; separate per-kind name indices
must not create separate language namespaces. Reject conflicting bindings even
when no body references them, retaining both origins for diagnostics.

Deduplicate paths to the same original declaration before conflict checking.
Declaration fragments belonging to one resolved extension identity remain one
binding; this does not permit an independent trait or type of the same name.
Owner-scoped members and lexical shadowing retain their separate scope rules.
The [module specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md#同一スコープの名前衝突)
owns the accepted language surface.

Binding establishes the declaration kind before interpreting a use. Neither
expected type, value/type position, receiver applicability nor a successful
alternative parse can rescue a binding collision. In particular, a source
selector does not search for an applicable same-named trait or extension after
another interpretation fails. Checking validates the already bound source and
its complete application, then retains the resulting evidence.

### Parameter Group and Signature Admission

The parameter-definition introduction owner admits a complete binding group
before signature publication or installing its locals. Its declared binding names are distinct even when argument labels are
suppressed. This applies to named and anonymous callable declarations and
requirements; it is not sequential local re-declaration. Outer bindings may be
shadowed, and later explicit local declarations retain their normal shadowing
rules. A low-level local append operation cannot decide all these cases from
name equality alone. Group admission needs the introduced parameter names,
not the surrounding local environment. Generic local storage receives admitted
bindings; do not pass a shadowing-policy flag into it or independently rerun
parameter checks at each storage caller.

Every callable signature and function type also has distinct non-absent
argument labels. Unlabelled positions are not repeated labels; a function type
does not introduce local parameter bindings. The signature/binding-group owner
establishes these two guarantees before successful publication. Derived,
provided and default-forwarding forms preserve the admitted group's guarantees
instead of introducing independent acceptance rules. Module number, body
demand and whether a signature is attached to a named Func row do not change
its well-formedness rules.
The [function specification](../../../spec/spec/01-basics/04-functions.md#引数ラベル)
owns label and binding-name uniqueness; this boundary does not replace the
separate module binding conflict rules.

### Extension Declaration and Member Publication

Module binding/public-surface construction consumes the extension declaration's
own publication status. Member admission consumes the selected impl's separate
visibility under its defining module. The accepted combinations and source
syntax are owned by [the extension specification](../../../spec/spec/02-type-system/09-extensions.md#拡張名とメンバの公開).

An extension's public members do not publish its name. A public extension does
not publish its private impls, and a private extension containing public impls
is valid. Do not infer declaration publication by scanning members or reject a
public impl merely because its containing extension is private. Apply the usual
package/public-API reachability rules at their existing boundary.

Selective, namespace and alias use, including re-publication, retain the original
extension identity and declaration publication. A published alias cannot widen
member visibility. Bind the source before receiver applicability; member checks
consume that bound source and the member's retained owner/publication facts,
without recovering privileges or choosing a different source by spelling.

### Shared Overload Declaration Admission

Declaration admission owns the complete overload acceptance decision, before a
declaration group is reported successfully admitted. Free functions, methods,
associated functions, custom and default/memberwise factories, and trait
requirements all use this authority. Sharing type equality or overlap helpers
while leaving additional acceptance predicates in individual callers is not this
contract: the same semantic declarations must not pass or fail according to the
entry point that registered them.

Inputs are the declaration-conflict domain and origin policy, receiver domain,
name and ordered labels, complete normalized parameter terms, lexical binders
and retained equalities, omitted-default callable forms, and the applicable
capability conditions. Each entry constructs those inputs from its declaration
kind. A default memberwise signature is available from fields/defaults even
without an executable function. Traversal and diagnostic rendering may remain
entry-specific; semantic acceptance may not.

The [specification's overload rule](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/07-methods-impl.md)
requires a distinguishing argument position for every pair of common ordinary
callable forms in one conflict domain and selector. Different pairs can use
different positions. Fixed unequal concrete types are sufficient, but the
bounded structural relation can also prove dependent terms distinct.

Compare under the common receiver domain: receiver-derived parameters describe
one shared environment, while method-owned binders from different declarations
remain independent. Derive sharing from canonical receiver/trait identity and
its parameter mapping, never spelling or binder-list position. A common receiver
parameter T can coincide with I64; two receiver parameters A/B can coincide too.
For the same shared T, T and fn() -> T cannot coincide in a finite structural
type. Independent method parameters T and U can satisfy T = fn() -> U.

The relation uses canonical nominal/function/record structure, consistent
substitutions, finite occurs checks and previously established type equalities.
Array[T] and Box[U] have different nominal constructors; Array[T] and Array[I64]
can coincide. Normalize concrete Self and retained projection equalities, but do
not search general trait bounds to manufacture a discriminator. Unresolved
projections preserve unknown; recursive nominal fields are not unfolded. A
cyclic substitution is not a legal recursive structural type. The existing
bounded analysis policy applies; distinguish a proved mismatch, a possible
match and unknown/AnalysisLimit. Only proved mismatch supplies a discriminator.

Each position is queried under the same receiver-domain constraints, but a
substitution introduced to test one argument position is not evidence for
another: the specification requires an individually distinguishing position,
not solely an inconsistent conjunction of otherwise overlapping positions.
Generic arity and use positions need not match, and neither is a discriminator.

Receiver/origin domains, independently provided trait-member coexistence and
inherent preference, and the adopted capability-conditioned groups retain their
explicit contracts. They are not caller-specific exceptions to the ordinary
structural-discriminator test. Different selectors are distinct operations. Apply the
rule to common default-omitted forms without requiring eager enumeration of
every omission combination.

The result establishes successful admission of the checked group or rejection
with the conflicting declaration/form and provenance. Reserved registration
identities or a passing overlap query alone do not establish admission. Changes
to a declaration domain must pass the same authority before reporting its new
state admitted. This result does not prove a body checked or a call uniquely
applicable: conversions, literals and contextual expressions can make a call
ambiguous even when its declarations are valid.

Verification maps every supported declaration entry to this authority and its
success boundary, records removed independent predicates and legitimate domain
checks, and compares valid/reject cases including unused declarations and
default forms. A copied trait check or an assertion comparing two independent
acceptance decisions is not the completed architecture. The implementation gap
is tracked by [met-g53w](../issues/met-g53w.md).

Candidate identity includes the original callable declaration and its applied
source/receiver instance. Equal source or trait heads do not make different
overload declarations or different proof instances one callable. Reuse canonical
witness identities and member-proof endpoint equality; a shared lexical body is
not a substitute. Collapse actual duplicate paths while collecting candidates,
before retaining a bounded pair of distinct matches. Two copies followed by a
different candidate must still expose the ambiguity. Apply inherent preference
to its eligible family without making registration order resolve remaining
multiple matches.

Name indices accelerate candidate discovery. They must remain consistent with their owning declaration store through its registration API. A global spelling-presence query does not prove lexical binding, visibility, arity, conformance, or unique applicability. An index's iteration order is not a semantic priority.

### Index and Query Cost Boundaries

Name indices retain the owning store's registration order and all same-named
candidates without turning that order into selection priority. Callable-only
indices and all-function indices serve different queries: generated functions
must remain visible to queries requiring the latter. Reading a narrow declaration
store should not require retaining unrelated mutable compiler state or creating
a new long-lived snapshot across later registration.

Not every declaration loop is a name lookup. Registration, whole-declaration
validation, and receiver/source-witness identity enumeration may need the entire
domain. A spelling-based query must not mutate source/name storage solely to
obtain an index key. Indexing is a cost improvement only when it preserves the
query domain, identity, provenance and ambiguity rules.

## 3. Scope Inputs and Binding Results

Each lookup is interpreted under explicit source context: module and file, lexical scope and source position, binder environment, and any explicit receiver/view qualification. A mutable cursor may be an implementation convenience but cannot be the hidden authority of a published result.

| Lookup class | Result | Required distinction |
|---|---|---|
| Local value or parameter | Lexical binding identity | Nearest legal binding versus equal spelling in another scope |
| Type parameter | Lexical binder identity | Method, nominal, trait, and witness binders even when all are named `T` |
| Type or namespace | Binding kind and original declaration/module identity | Namespace qualification versus value-member access |
| Free callable | Visible declaration candidates | Candidate collection versus call applicability |
| Member | Receiver/qualification-scoped member candidates or abstract requirements | Concrete member existence versus capability available under generic bounds |
| Diagnostic-only name search | Inaccessible or otherwise excluded suggestions | Explanation of failure versus permission to call |

A cached answer that no static callee exists can describe a successful value
call. It is an observation, not evidence that the query's callable candidates were
searched and rejected. Keep these outcomes distinct through the query boundary:
readers may consume the nonstatic answer, while source-refusal publication
requires the actual failed search and its source owner. Invalid cached indices
are malformed implementation input, not source rejection. Table growth must not
reinterpret a nonstatic answer as a declaration identity. A nonstatic cache
observation does not authorize a new concrete-member search; independent
abstract-requirement or value-call evidence remains a separate valid route.

Shadowing creates a new lexical binding rather than changing the old binding's type or mutability. Its uses, captures, and cleanup remain associated with the correct identity. Pattern and condition bindings have their language-defined scope; entering a closure creates a separate body/control boundary while capture analysis records the enclosing binding identities it uses. Scope traversal must not be independently reconstructed by LLVM from source names.

The initializer of a shadowing declaration is checked in the old binding environment. Only after its evaluation and temporary cleanup does the new binding become available. This commit boundary must be retained for ownership analysis: replacement in the same lexical scope can end unique ownership. Hiding an enclosing binding leaves its lifetime unchanged. Lookup retains the new and old binding identities and their lexical scopes; ownership analysis determines the corresponding cleanup edges.

Qualified expressions must distinguish a namespace from a same-spelled local value using lexical bindings. Once that distinction is established, later passes must not reinterpret the expression as a module path merely because a module with the spelling exists.

Namespace-call normalization retains the authored operation at the actual
Method-to-free-call transition, together with the resolved module use, selector
and argument range. Only a recorded authored Method can transfer that origin;
synthetic or unregistered nodes cannot acquire it from matching spans. Failure
interpretation consumes this retained identity rather than guessing from the
qualified spelling after normalization.

## 4. Free Functions and Public Surfaces

The [module specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md) defines root-owned use bindings shared across the root and all parts, module-private declarations, and individual public declarations. Directive-placement validation rejects use in handwritten and generated parts before lookup; there is no separate part-file import environment. The [root-owned binding contract](sources-and-modules.md#root-owned-use-bindings) owns this boundary and its reconsideration conditions. Free-function lookup combines visible local declarations and explicitly imported public declarations into one candidate set, deduplicated by declaration identity. It does not prefer a local declaration merely because it is local, or prefer the first import encountered.

Selective use of a function name transfers all public overloads under that name. An alias changes the local binding name of the set. Non-public overloads do not become public because another overload shares their spelling. Namespace-qualified calls read that namespace's reachable public surface; they do not fall back to unrelated same-named declarations.

Lookup must retain enough exclusion information for an accurate diagnostic. Finding a private candidate can explain an error but cannot hide an applicable visible overload or authorize the private call. Cross-kind module binding collisions are rejected by shared module binding admission, not resolved through overload-set union.

For example, importing an unlabeled `print(String)` and declaring `print(value: String)` locally produces candidates distinguished by their argument labels. A labeled call selects the local function; an unlabeled call can select the imported function. The same candidate/applicability rules apply if both declarations originated in the same module.

## 5. Members, Views, and Generic Requirements

Member lookup is driven by the receiver's semantic type and explicit view/trait qualification, not by which trait names happen to be imported at the call site. Language syntax operations such as `+` use fixed protocol mappings; writing the trait name explicitly in a bound, impl, projection, or `#Trait` still requires ordinary name visibility.

The [method](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/07-methods-impl.md) and [extension](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/09-extensions.md) specifications define which surfaces participate. Extension members require their explicit view. Bare surfaces include the type's own methods and applicable public trait-provided methods. The specification's inherent-method preference and explicit trait selection are semantic rules; they are not precedent for inventing origin priorities among free functions. Distinct trait-provided collisions may remain candidates until an ambiguous call is rejected or explicitly qualified.

For a generic receiver, lookup is limited by its declared capabilities. It may identify a trait requirement without selecting a concrete impl body. Checking publishes that requirement, its signature, and the obligations/evidence context. An instance then resolves the concrete witness for that same requirement; it must not discover an unrelated concrete member that retrospectively makes the generic source valid.

Associated-type name lookup uses the shared [associated-member selection
contract](types-and-evidence.md#associated-member-selection). An explicit child
trait instance limits the search roots but includes its inherited instances;
`T.Item` starts from the available constraints. Neither spelling has an independent
membership or ambiguity rule. Resolution retains the actual declaring instance
rather than treating the selected child as the declaration owner.

Member existence, proof that a conformance exists, and proof that a member selection is unique are different results. None can be represented soundly by a shared “found name” Boolean. The types/evidence and generics chapters own proof representation and projection; lookup preserves the identities on which they operate.

A callable declaration read in a value position is a declaration group, not an
applicable call. Establish its category from the real binding or receiver-scoped
name reader after preserving storage fields and static values. Retain canonical
declarations or requirements, receiver patterns, complete instance/path evidence,
and source families with their priority. Without written arguments, neither an
expected function type nor a preferred basename may select one overload or erase
fallback families. Coalesce only repeated discovery of the same declaration and
proof path. Complete trait selectors constrain candidate instances and the keys
on intervening proof edges, not merely their owner or arity.

The receiver's bounds and views retain their own admission checks. Establishing
a non-value category does not repeat unique member-dispatch or executable-witness
selection: it publishes only a refusal, never a call or conformance capability.
An existential contributes its already-admitted interface graph and original
member identities; it does not acquire self-conformance by this operation.
The recording producer binds these observations to the authored operation and
request owner in a private admission record. Diagnostics and failed-request
consumers retain that record rather than accepting a supplied candidate group or
repeating lookup in a later cursor context.

View qualification does not discard unrelated base members. Extension tags add participating sources and can shadow same-named base members; the single trait-source selector disambiguates an existing conformance path without creating a conformance or hiding unrelated inherent members. A trait selector identifies a complete trait instance: canonical declaration owner and every positional type argument, not owner or arity alone. Value and type syntax require all positional arguments even when only one conformance is available; an argument-free selector is complete only for a trait with no positional parameters. Lookup consumes this retained instance through candidate selection and final call evidence rather than reconstructing arguments from receiver spelling or a projection-only field. Extension source sets and trait selection therefore remain distinct lookup inputs: `A#Ext#P` and `A#P#Ext` have the same meaning, rather than sequential filtering semantics. Private trait-provided helpers may participate within their owning module but do not accompany conforming types into an external public surface.

## 6. Applicability and Publication

Lookup may filter by facts intrinsic to its domain, such as binding kind, visibility, explicit qualification, and member surface. Call checking owns label matching, concrete argument-type applicability, generic inference, and the specification's selection order. Bounds validate the selected generic operation; they must not become an unadvertised specialization ranking.

Preliminary context for an omitted type may use candidate information only under the same visible candidate rules. A contextual hint is not a selected callable.

Applicability reads prepared argument facts, including unfinished construction fields and the result recipe of an already-selected nested call. A nonzero TypeTerm or a nominal head alone does not prove that the value is complete. Candidate-local completion preserves known type arguments, field constraints and rigid caller binders; it cannot turn an unselected nested call into a selected one. Only the selected operation's context is subsequently applied by the existing expression producers. Invalid saved substitution ranges or type identities are not inference holes. An absent field fact alone is not evidence of a partial construction; fully written raw arguments retain their structural type-matching path.

A label-only diagnostic candidate remains a distinct lookup outcome: it cannot populate a selected-callee cache, supply a call result, or publish a call descriptor. Its tentative argument context exists only for diagnostics and is not admitted expected-type evidence. Passing a diagnostic check does not promote that outcome; normal applicability must establish the operation. A diagnostic outcome terminates its selected surface and must not be collapsed into an absent candidate that authorizes another surface search.

If type overloads remain ambiguous, lowering must not guess one to make a child expression type-check. Once checking selects an operation, it publishes its declaration/requirement identity, signature, environment, and evidence for instantiation and Mid consumers.

Downstream readers cannot recover a missing required selection by rerunning name lookup with a different environment. Legitimate initial concrete witness determination remains separate from source reselection. The [publication contract](compiler-state.md) distinguishes a missing required fact, an optional absent binding, a failed request, and a complete abstract result.

Declaration-time conflict checking and use-site ambiguity are also separate. Some duplicate definitions are invalid immediately; some independently qualified trait members may coexist and only a bare call is ambiguous. Neither registration order nor removing a candidate as a performance shortcut may change that distinction.

### Shared Callable Applicability

Ordinary calls, trait satisfaction, and `via` delegation use the same callable applicability rules. Lookup supplies candidates; semantic applicability determines the operation each candidate can provide. Its retained plan identifies the declaration, explicit-argument mapping, omitted defaults and their declaration environment, substitutions and evidence, and any delegation path. Conformance checking proves that the entire required operation is available, rather than testing one favorable concrete argument value.

Receiver normalization shared with candidate ranking interprets lexical `Self`
only. A bare nominal qualifier supplies the candidate's receiver recipe, not a
completed call substitution. Candidate-local matching owns tentative holes and
conflicts and must consider the other candidates before source-call failure is
authoritative. Strict receiver/argument inference runs after selection at the
owning source call. Ranking must not invoke that strict inference merely to
obtain its initial receiver or catch its errors as an alternative ranking rule.
Dependency failures still propagate from the ordinary candidate matcher.

An implementation `factory(count: I64 = 5)` can satisfy declared requirements for both `factory()` and `factory(count: I64)`, subject to the ordinary conformance declaration and compatibility rules. Trait requirements do not declare defaults. Concrete and generic calls use the selected implementation's defaults; there is no competing trait-default authority. Visibility, callable kind, result/failure types, ownership, and async compatibility remain mandatory.

Body checking retains the selected plan. Lowering realizes it as ordinary expression evaluation and a complete argument call; witness or delegation entries are ordinary forwarding bodies derived from the same plan. Explicit arguments are evaluated in source order, then omitted defaults in parameter declaration order, before operands are arranged in parameter order. Plans may be shared; evaluated default values are not cached. This does not require enumerating every omission combination or adding default-specific Mid execution semantics. [Body checking](body-checking.md) owns the evaluation plan; Mid and ownership preparation realize its evaluation order, access completion, and temporary lifetime contracts. [Generics](generics.md) owns concrete evidence and adapters.

## 7. Change Impact and Verification

Changing an import form affects binding construction and public-surface lookup before it affects applicability. Adding an overload affects declaration conflict checks, candidate-set construction, contextual hints, and selected-call publication. Adding a new member surface requires an explicit participation rule and evidence path; a new spelling scan in a later pass is insufficient.

Verification should compare local/imported/re-published overloads, aliases and duplicate paths, public/private overload pairs, labeled and type-distinguished calls, namespace/local-value shadowing, same-spelled lexical binders, and generic requirements versus concrete extra members. Capture tests must show that shadowed pattern variables retain the intended binding identity through execution. A lookup-reader unit test does not prove that Mid or LLVM uses the published selection.

When migrating an old selector, identify its callers and remove independent selection after producer-to-final-consumer closure. Keeping both selectors and adding a consistency assertion may help diagnose migration, but is not the final architecture.

## 8. Comparisons

[Rust's name-resolution guide](https://rustc-dev-guide.rust-lang.org/name-resolution.html) describes scope stacks, distinct name categories, and published links to declarations. These support explicit lexical context and identity here. Its expansion/import stages and namespace rules are Rust-specific, and the guide notes its own incompleteness. Plew does not adopt Rust's trait-import method participation or macro expansion order by analogy.

[Swift's lookup interfaces](https://github.com/swiftlang/swift/blob/main/include/swift/AST/NameLookup.h) represent result sets with declaration/context information and distinguish visibility filtering. That is a useful model for preserving candidate provenance separately from call selection. Plew's forward contextual inference, explicit extension views, and free-function import union remain governed by Plew's specification rather than Swift's overload solver or shadowing policies.

## 9. Implementation Mapping and Limits

[Module/visibility helpers](../../src/Codegen/Resolve/Module.pw),
[lexical qualification](../../src/Codegen/Resolve/Lexical.pw), and registered
candidate indexes implement lookup inputs. Their broad `Resolve` naming does not
grant each caller authority to select or replace a source operation.

The [eight-path source-selection reconciliation](../issues/met-ucze.md#reconciled-area-completion)
and [exact callee environments](../issues/met-ia09.md) record the supported
frontend handoff from selected declarations/proofs to actual final calls. The
[phase-three parent](../issues/met-si6j.md) owns whole-candidate gate status.
Preserved source/view placement and lexical body ownership are distinct; a
gated diagnostic candidate is never an admitted callable.

These closures do not establish arbitrary synthetic provenance through
`moduleOf`'s unmatched-offset behavior or certify every caller of legacy
module-membership helpers. Those uses require their explicit source-domain
contracts and assigned [existing-feature conformance work](../issues/com-604k.md).
Do not infer complete scope reconstruction or generated-path coverage from
lookup-index presence, helper names or absence of an issue link.
