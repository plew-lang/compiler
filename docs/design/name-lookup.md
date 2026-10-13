# Declarations, Scopes, and Name Lookup

**Status:** Reviewed draft. This chapter defines decision boundaries and required information, not a completed audit of the current resolution passes.

## 1. Responsibility

Declaration registration establishes identities and declared interfaces. Scope construction determines which bindings are available at a source position. Lookup returns the applicable binding or candidate set with its provenance. Semantic checking determines call applicability and selects the source operation; concrete instantiation may later select the first concrete witness for an already chosen abstract requirement.

The purpose is to prevent a name index, visibility helper, or downstream pass from becoming a competing selector. A contributor changing imports, overloads, or generic member access should be able to identify the owner of each decision and the result that later stages consume.

Module membership and package reachability are inputs from [Sources, Packages, and Modules](sources-and-modules.md). This chapter does not select dependency revisions, type-check bodies, choose ABI layouts, or authorize execution.

## 2. Registration and Identity

Registration associates each declaration with its kind, lexical/module owner, source origin, declared signature, public status, and relevant binder identities. Bodies can be requested separately; registering a callable signature is not successful body checking. Mutually recursive calls can use registered signatures without recursively preparing their callees while checking one source body.

Aliases and re-publication preserve the original declaration identity. An imported local name is a binding to that identity or overload set, not a copied declaration with new visibility rights. A generated callable also needs an explicit semantic owner and origin; appended synthetic text cannot determine its privileges.

Name indices accelerate candidate discovery. They must remain consistent with their owning declaration store through its registration API. A global spelling-presence query does not prove lexical binding, visibility, arity, conformance, or unique applicability. An index's iteration order is not a semantic priority.

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

Shadowing creates a new lexical binding rather than changing the old binding's type or mutability. Its uses, captures, and cleanup remain associated with the correct identity. Pattern and condition bindings have their language-defined scope; entering a closure creates a separate body/control boundary while capture analysis records the enclosing binding identities it uses. Scope traversal must not be independently reconstructed by LLVM from source names.

The initializer of a shadowing declaration is checked in the old binding environment. Only after its evaluation and temporary cleanup does the new binding become available. This commit boundary must be retained for ownership analysis: hiding a unique binding is an accessibility cliff, whereas a hidden copyable binding retains its ordinary scope lifetime. Lookup establishes the identities and visibility transition; ownership analysis determines the corresponding cleanup edges.

Qualified expressions must distinguish a namespace from a same-spelled local value using lexical bindings. Once that distinction is established, later passes must not reinterpret the expression as a module path merely because a module with the spelling exists.

## 4. Free Functions and Public Surfaces

The [module specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md) defines file-local use bindings, module-private declarations, and individual public declarations. Free-function lookup combines visible local declarations and explicitly imported public declarations into one candidate set, deduplicated by declaration identity. It does not prefer a local declaration merely because it is local, or prefer the first import encountered.

Selective use of a function name transfers all public overloads under that name. An alias changes the local binding name of the set. Non-public overloads do not become public because another overload shares their spelling. Namespace-qualified calls read that namespace's reachable public surface; they do not fall back to unrelated same-named declarations.

Lookup must retain enough exclusion information for an accurate diagnostic. Finding a private candidate can explain an error but cannot hide an applicable visible overload or authorize the private call. Non-function binding collisions follow their own specification rules, not overload-set union.

For example, importing an unlabeled `print(String)` and declaring `print(value: String)` locally produces candidates distinguished by their argument labels. A labeled call selects the local function; an unlabeled call can select the imported function. The same candidate/applicability rules apply if both declarations originated in the same module.

## 5. Members, Views, and Generic Requirements

Member lookup is driven by the receiver's semantic type and explicit view/trait qualification, not by which trait names happen to be imported at the call site. Language syntax operations such as `+` use fixed protocol mappings; writing the trait name explicitly in a bound, impl, projection, or `#Trait` still requires ordinary name visibility.

The [method](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/07-methods-impl.md) and [extension](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/09-extensions.md) specifications define which surfaces participate. Extension members require their explicit view. Bare surfaces include the type's own methods and applicable public trait-provided methods. The specification's inherent-method preference and explicit trait selection are semantic rules; they are not precedent for inventing origin priorities among free functions. Distinct trait-provided collisions may remain candidates until an ambiguous call is rejected or explicitly qualified.

For a generic receiver, lookup is limited by its declared capabilities. It may identify a trait requirement without selecting a concrete impl body. Checking publishes that requirement, its signature, and the obligations/evidence context. An instance then resolves the concrete witness for that same requirement; it must not discover an unrelated concrete member that retrospectively makes the generic source valid.

Member existence, proof that a conformance exists, and proof that a member selection is unique are different results. None can be represented soundly by a shared “found name” Boolean. The types/evidence and generics chapters own proof representation and projection; lookup preserves the identities on which they operate.

View qualification does not discard unrelated base members. Extension tags add participating sources and can shadow same-named base members; the single trait-source selector disambiguates an existing conformance path without creating a conformance or hiding unrelated inherent members. Extension source sets and trait selection therefore remain distinct lookup inputs: `A#Ext#P` and `A#P#Ext` have the same meaning, rather than sequential filtering semantics. Private trait-provided helpers may participate within their owning module but do not accompany conforming types into an external public surface.

## 6. Applicability and Publication

Lookup may filter by facts intrinsic to its domain, such as binding kind, visibility, explicit qualification, and member surface. Call checking owns label matching, concrete argument-type applicability, generic inference, and the specification's selection order. Bounds validate the selected generic operation; they must not become an unadvertised specialization ranking.

Preliminary context for an omitted type may use candidate information only under the same visible candidate rules. A contextual hint is not a selected callable. If type overloads remain ambiguous, lowering must not guess one to make a child expression type-check. Once checking selects an operation, it publishes its declaration/requirement identity, signature, environment, and evidence for instantiation and Mid consumers.

Downstream readers cannot recover a missing required selection by rerunning name lookup with a different environment. Legitimate first concrete witness selection remains separate from source reselection. The [publication contract](compiler-state.md) distinguishes a missing required fact, an optional absent binding, a failed request, and a complete abstract result.

Declaration-time conflict checking and use-site ambiguity are also separate. Some duplicate definitions are invalid immediately; some independently qualified trait members may coexist and only a bare call is ambiguous. Neither registration order nor removing a candidate as a performance shortcut may change that distinction.

### Shared Callable Applicability

Ordinary calls, trait satisfaction, and `via` delegation use the same callable applicability rules. Lookup supplies candidates; semantic applicability determines the operation each candidate can provide. Its retained plan identifies the declaration, explicit-argument mapping, omitted defaults and their declaration environment, substitutions and evidence, and any delegation path. Conformance checking proves that the entire required operation is available, rather than testing one favorable concrete argument value.

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

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. Focused reading covered [module/visibility helpers](../../src/Codegen/Resolve/Module.pw), [lexical module qualification](../../src/Codegen/Resolve/Lexical.pw), and existing candidate-index contracts. These files locate current entry points; their broad “Resolve” naming does not define the intended decision ownership.

Current `moduleOf` returns the entry module for unmatched offsets, and `methodInEntryModule` derives membership from body statements. Those mechanisms cannot establish arbitrary synthetic or empty-body ownership and must not be treated as the intended provenance contract. Their complete caller impact remains unaudited. The paused type-checking review also identifies independent source member selection across checking passes; this chapter specifies its replacement boundary, not its completed removal.

No new compiler execution or performance measurement was performed. Complete scope reconstruction, conflict checking, all generated paths, and final-consumer closure remain unverified. Gap migration into [local issues](../issues/README.md) is in progress, so absence of linked issues is not evidence that these gaps have been resolved.

Chapter review checked the lookup/selection boundary against the module, method, extension, and binding specifications. Clarifications for additive views and module-private trait helpers were incorporated and re-reviewed; no required correction remains within that review scope.
