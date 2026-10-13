# Generics and Body Instantiation

## 1. Responsibility and Boundaries

Generic source checking establishes a body's meaning under its declared parameters and bounds. Instantiation applies a particular environment to that saved meaning and closes the obligations required for the requested concrete operation. Monomorphization discovers and prepares concrete bodies for execution. These are distinct responsibilities even when existing code places them in the same module.

A non-generic declaration follows the same pipeline with no explicit type arguments. It is not exempt from source checking, instance identity, conversion evidence, or execution preparation. Methods without method-owned type parameters can still depend on receiver, impl, and trait environments.

The [generic specification](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/06-generics.md) owns invariant type arguments, parameter capabilities, and declaration-time abstract checking. [Body checking](body-checking.md) owns source choices. [Types and evidence](types-and-evidence.md) owns structural substitution and conformance derivations. This chapter owns the instance environment, instance-specific discharge, and transport to final consumers. It does not define new specialization or fallback lookup rules.

## 2. Abstract Checking Is Not Template Acceptance

Treat each declared parameter as an opaque semantic type with a lexical binder identity. Operations must be justified by declared bounds, including their valid entailments. An eventual concrete argument having an extra method or operator does not justify that operation in the source body. Trait-provided bodies use their own abstract `Self` and requirements even when no concrete conformer is currently used.

`check` and `build` request abstract checking of unused generic bodies too. `run` can defer an unneeded body, but checks a demanded body's whole source under the same abstract rules before execution. “Declaration-time” describes the typing environment, not a promise that every command checks every declaration before startup.

The saved result identifies selected declarations or requirements, parametric expression/signature terms, source evidence and explicit obligations. A valid abstract projection can remain symbolic. An unchosen overload, unknown lexical binding, or absent proof cannot be relabeled as a deferred instance obligation. Source success and concrete execution success are different guarantees.

## 3. Constructing an Instance Environment

An instance environment contains an explicit mapping from lexical `ParamId` to semantic type term, the selected receiver, and the evidence required to interpret the source body. Its constructor validates binder membership, mapping consistency, and the provenance of receiver/proof inputs. Function/method binders, nominal receiver binders, impl pattern binders, and proof substitutions contribute through their own identities; parallel positional arrays must not become independent authorities.

When two contributions bind the same parameter, accept them only if the semantic types agree. Do not resolve a conflict by last-write wins. Trait lexical `Self` is bound explicitly to the selected receiver. When projecting the callable's type arguments for a signature or call record, use that declaration's parameter identities and order; do not include incidental derived bindings or index a different owner's shorter parameter vector.

Receiver-pattern matching is directional. For an impl pattern `Packed[Array[T]]` matched against `Packed[Array[Yes]]`, the impl binder `T` maps to `Yes`, not `Array[Yes]`. Method-owned arguments remain separate contributions. Query-side parameters are rigid, even if they share the printed name `T` with an impl parameter. The simultaneous-substitution rule and proof-driven projection handling are defined in [types and evidence](types-and-evidence.md).

A provided copy retains two relevant provenances: the conformance placing the body on its concrete receiver determines body `Self` and nested requirements; the source witness identifies the original impl binders to substitute. One conformance index cannot silently stand for both. The lexical source owner remains the authority for source types and visibility, while concrete placement belongs to this instance.

### Shared Type-Argument Constraint Matching

Call arguments, expected-result refinement, and construction fields use one structural constraint-matching contract. The input explicitly identifies which binders may be inferred: only the selected callee or construction binders are variables; caller binders remain rigid even with identical spelling. Read canonical type heads, children, and labels, and do not invert associated projections to invent bindings.

Matching distinguishes success, deferred obligations, structural mismatch, and conflicting bindings. Every occurrence of a binder must agree. Build tentative mappings separately so a failing candidate cannot partially modify published state. Independent candidates discovered while other constraints remain deferred may be retained, but are not conformance proof; signature checking must still close the obligations. Expected-result refinement commits only successful matches. Matching alone does not establish passing modes, bounds, views, conversions, or whole-call validity.

## 4. Instance Identity and Registration

An executable body identity includes its selected declaration/body origin and complete semantic environment. Different receiver terms, lexical mappings, or selected static evidence cannot collapse merely because their machine layouts or ABI signatures match. Closure, global-initializer, default-generator, and adapter origins must remain distinct where their bodies or obligations differ. A registry may represent them using synthetic function keys, provided those keys have explicit ownership and stable provenance.

Within an instance, ordinary and synthetic call results are keyed by the caller body identity and occurrence identity. A final call retains the selected callee body identity as well. The caller's environment cannot be substituted for the callee's environment when reading parameter/result types or projection evidence.

Semantic identity, registry presence, and readiness are separate. Registration reserves a stable identity for graph edges. It does not prove that a signature, body, ownership result, or execution dependency is complete. A backend's read-only lookup must not register an instance that escaped preparation. Emission starts from the prepared executable set, not every row in the registry.

Indexes may narrow comparisons by declaration. Full environment equality remains authoritative. Stable internal IDs can key worklists and backend slots after interning, avoiding repeated deep proof/substitution comparison for each call. Symbol construction must preserve distinctions needed for execution; later machine-code deduplication needs a separate proof of equivalence and cannot redefine semantic identity.

## 5. Discharging Saved Obligations

Instantiation consumes a successful source artifact and explicit environment. It grounds saved terms, substitutes selected proof edges and conditions, and establishes the unique concrete terminal witness for an abstract requirement when static dispatch requires it. This is legitimate concrete selection within the source-selected requirement and provenance, not source overload resolution repeated with extra concrete capabilities.

| Source fact | Instance work | Final consumer |
|---|---|---|
| Selected direct call with symbolic types | Substitute its signature, arguments, conversions and obligations; identify the callee instance | Mid call construction and backend target |
| Bound/provided requirement and abstract proof | Instantiate retained paths/conditions; establish a unique concrete witness for static dispatch | Grounded requirement call and witness construction |
| Associated projection | Ground the receiver and exact trait instance; read the selected associated output | Expression, signature, and layout preparation |
| Selected aggregate/pattern/try protocol | Ground saved mappings, payload types and conversions | Construction, match, propagation and cleanup lowering |
| Closure signature and capture descriptor | Ground lexical types and instantiate the closure body under its own identity | Environment representation and closure dispatch |
| Existential operation | Preserve selected requirement and runtime evidence/slot contract | Dynamic dispatch; no statically known conformer is required |

Closed parent types alone do not discharge a symbolic child condition. Preserve deferred, failed/missing, and ready outcomes distinctly. A request requiring executable facts cannot publish unresolved obligations as if they were pure, identity conversions, or optional absent data. Failures carry the original source/call provenance and are stable under unchanged inputs.

Conditional conformance matching binds only impl-owned parameters and checks its conditions. Source priority and associated-output checking obey [the shared evidence rule](types-and-evidence.md): an output mismatch cannot reopen a shadowed implementation. Static evidence and runtime existential evidence remain separate. Generic abstraction does not turn an existential value into static proof of every requirement.

## 6. Signatures, Adapters, and Returns

Instance body construction reads the saved source-body receiver, parameters and logical result contract under the instance environment. The declaration's callable interface remains a separate input for call-boundary checking. A dispatch receiver pattern is not automatically the body receiver type, and a logical source result need not equal a carrier's ABI result.

Final calls retain parameter types, conversions, passing modes, evaluation sources, source-visible result adapters, and the exact callee body identity. Backend lowering reads these instance results instead of reconstructing an environment from a function index and receiver arguments. For extern declarations with no source body, signature preparation has an explicit declaration-based constructor; this is not a fallback for missing ordinary-body facts.

An inherited or forwarding surface can require an adapter around the original body: execute the original body with its original type and apply checked boundary conversions. The adapter has explicit origin, target instance and selected conversion/call evidence. It does not reinterpret the original AST under the wrapper receiver. Its registration also does not imply its target is ready. Physical ABI and adapter realization belong to the representation chapter; this chapter requires preservation of their semantic inputs.

A return reads the saved source result and destination contract, then its instance conversion. It does not derive a new source type from an ABI return slot. Provided bodies, closures, globals and ordinary functions all obey the same distinction.

## 7. Discovery, Recursion, and Execution Readiness

The preparation worklist starts from the command's requested roots and follows selected executable dependencies, including calls, closures when required, destruction, adapters, and runtime/protocol operations. Demand-driven execution may prepare a later target on demand through the common checked boundary; it does not authorize executing an unchecked target or bypassing its instance obligations.

For a repeated instance key, reuse the registered identity and its computation state. A recursive call can refer to a registered signature without recursively rebuilding the same body. Processing an active graph node is not successful completion. Analyses needing a whole recursive component use an explicit graph/worklist or fixed-point protocol and publish only their scoped result, as described in [compiler state](compiler-state.md).

Recursion that generates endlessly different type instances is not eliminated by same-key deduplication. The compiler needs a bounded resource/depth diagnostic with source provenance. Such an implementation limit can prevent `build` or `run` after successful abstract checking; it must not be presented as a new source typing rule or silently truncate the executable graph.

Execution publication requires the concrete body's needed local and interprocedural analyses and its callable dependencies to be satisfied under the execution model. A successfully grounded type, an interned body ID, or source-only checks are each insufficient. Lazy target readiness is handled at the common call-entry boundary, not by a second runtime semantics for generic bodies.

## 8. Examples and Change Impact

Consider a source body calling a requirement on `T: Iterator`. Its saved call selects that requirement and its result projection. Instances for two concrete iterators retain their own receiver, witness and associated output. Even if both produce the same physical result type, a backend cache cannot merge their calls solely by that result's layout. Conversely, an identical source/body/environment request reuses the same instance rather than cloning it at every call site.

For a provided copy reached through a trait-subject conformance, preserve the placement proof and source impl substitution independently. Nested calls use the body's justified requirements. The caller's path is not an implicit priority among unrelated requirements inside that shared body. A missing callee body or conversion halts preparation at the required reader; a declaration-name fallback would erase the distinction this example needs.

Adding a new bound or projection form affects source justification, environment construction, evidence substitution, instance keys where meaning changes, and final consumers. Adding a new synthetic body requires origin identity, signature preparation, dependency discovery and readiness. A new backend cache must state why its key preserves the instance distinctions above.

Verification should cover same-spelled binders, nested receiver patterns, method/impl parameter combinations, conflicting maps, provided placement versus source provenance, distinct proofs with equal ABI, recursive same-key reuse, expanding-instance limits, extern signatures, adapters, dynamic existentials, failed re-requests and required-fact deletion. Compare zero-argument and generic forms through the same pipeline. Check execution or expected rejection as well as registry counts; a correctly interned ID does not prove its final consumer uses the right environment.

## 9. Comparisons

[Rust monomorphization](https://rustc-dev-guide.rust-lang.org/backend/monomorph.html) collects needed concrete items and generates specialized code, trading compile time and code size for concrete execution. This is a useful reference for Plew's concrete-body worklist. Rust's codegen-unit policy and exact collection staging are not Plew requirements; source checking and execution readiness remain distinct here.

[Swift's generics introduction](https://github.com/swiftlang/swift/blob/main/docs/Generics/chapters/introduction.tex) starts from independently checked generic declarations and requirements supplied by callers. Its runtime metadata convention supports unspecialized generic code, while specialization can remove that indirection. Plew shares the abstract contract but currently prepares concrete body instances rather than adopting Swift's resilient runtime-generic ABI. [Swift substitution maps](https://github.com/swiftlang/swift/blob/main/include/swift/AST/SubstitutionMap.h) retain replacements together with conformances, reinforcing the need to transport evidence rather than just type argument lists. These comparisons do not prescribe new metadata services or a second generic runtime for Plew.

## 10. Implementation Mapping and Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. `InstanceEnvironment` and `BodyInstance` in [Ir.pw](../../src/Ir.pw) retain receiver, parameter mappings, proof and adapter links. [Mono/Call.pw](../../src/Codegen/Mono/Call.pw) contains environment comparison, `findBodyInstance`, `internBodyInstance`, and body-entry handling. [BodyInstances.pw](../../src/Ir/BodyInstances.pw) owns registry navigation and signatures/results.

The inspected implementation exposes [`matchTypeArgumentConstraints`](../../src/Codegen/Resolve/Expr.pw), with `PatternBindInput` declaring the inference-binder set (Function range for calls, Values for construction) and `TypeArgumentMatch` distinguishing outcomes. These names map the contract above to existing code; they are not a second semantic interface. The older bare-binder consistency scan was removed in the retained remediation work in favor of checking each argument against the selected substitution. Coverage of construction inference and the final consumers remains part of the paused remediation audit, not a completed guarantee of this chapter.

The registry currently reserves signature rows during registration and exposes separate setters; registration is therefore visibly not signature completion. Adapter metadata can also be set after registration. Those construction mechanisms are not proof of an immutable successful execution artifact. Declaration-check module gates and chained calls on associated-type or type-parameter results remain unaudited; module exclusion or unknown-type fallback is not the intended abstract-checking contract. Complete environment-constructor coverage, all worklist cycle/failure paths, and every backend/mangling consumer remain unaudited. Retained type-checking candidates add further source-artifact contracts not all present at this base. No compiler execution or performance measurement was performed, and migration into [local issues](../issues/README.md) is in progress.

Chapter review checked abstract/concrete selection, instance identity, recursion/readiness, existential dispatch, specification alignment, and the Rust/Swift comparisons. Concrete witness determination is explicitly unique, not selection of the first candidate encountered. No required correction remained in that scope; this was not a complete implementation audit.
