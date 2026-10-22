# Generics and Body Instantiation

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

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

### Declaration-bound Evidence Transport

Callee environments retain evidence by declaration-bound identity, not only type
arguments and one receiver/provided proof. Environment rebuilding and equality
must preserve those bindings; a legitimate empty set differs from missing or
unprepared evidence. Function, requirement, conformance and associated-clause
identities cannot be interchanged merely because their bound arrays have the same
length or order.

Public requirement evidence and implementation-body assumptions have different
owners. Conformance preparation retains the derivation from original requirement
clauses, selected conformance and implementation declaration to each implementation
bound. Instantiation applies that saved derivation in the explicit environment,
including weaker/reordered implementation bounds and supertrait/where entailment.
The final body receives implementation-bound identities; intermediate requirement
bindings are not themselves proof that the body environment is complete.

Source-bound admission first requires the unique path described in [conformance evidence](types-and-evidence.md#5-conformance-evidence), even if no member is used. A weaker internal existence obligation cannot stand in for that admission. Presence obligations do not automatically demand unique member dispatch. A saved
existence proof cannot silently choose a caller path as a shared callee's dispatch
priority. Prepare the evidence actually demanded by saved member/conversion/
protocol operations, preserve required uniqueness, and keep first concrete
preparation distinct from reselection of an already committed witness. Declaration
worklists and execution preparation use the same explicit evidence contract,
without making ambient monomorphization cursor state authoritative.

Scheduling a source-selected static callee requires its retained operation as
well as the concrete selection. Written calls, operators, iteration and implicit
error conversions use this same entry; an omitted evidence argument cannot
silently request declaration-based proof construction. Declaration worklists use
the same evidence reader with their explicit caller environment. Root and sealed
synthetic plans remain separate first-evidence producers. Extern/bodyless calls
admit their substituted signature and evidence without inventing a checked body.

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

### Capability Discharge and Witness Admission

Instantiate the [saved capability/selection contract](types-and-evidence.md#capability-and-conditional-selection-contracts) with the instance's explicit binder and evidence environment. Do not rewalk nominal fields to invent a different unique condition. An allowunique body's justified borrow/move modes adapt to by-value copy semantics for a copyable instance; this is one substitution of its checked contract, not a second source diagnostic or permission to insert a copy for a unique instance.

Recursive capability instances consume the completed
[structural summary](types-and-evidence.md#structural-recursion-and-shared-capability-decisions)
under that same environment. Visiting an active instance is not a copyability
proof. A symbolic component's completion is distinct from discharging a concrete
copy/drop request. Conditional call/via/deinit paths use the common relation's
results and evidence rather than implementing separate overlap or coverage tests.
The [fixed expansion-depth limit](types-and-evidence.md#bounded-capability-reasoning-and-analysis-limit)
can stop a finite deep request as AnalysisLimit. It never permits selecting a
different candidate or publishing an undisclosed residual classification.

A conditional candidate family is one checked source operation. Evaluate its saved predicates to select exactly one recorded branch for the admitted environment. Retain the branch's declaration/body identity, conversions, modes and evidence. Default adapters, provided methods and `via` witnesses use the same applicability contract. An uncovered or conflicting environment is a preparation failure; concrete-name lookup or a more-specific-implementation fallback cannot repair it.

Destruction selection consumes its own saved selection contract, explicitly representing the absence of a user deinit as well as selected deinit branches. This valid absence is not an uncovered callable candidate family. Instantiate the recorded conditional deinit and child destruction relationships into the final type destruction contract. Copyable instances retain ordinary child cleanup; a missing user deinit does not mean release-free storage. Drop elaboration, effect closure and physical glue consume this result rather than each selecting deinit again.

At existential injection, conformance preparation fixes the concrete witness and associated bindings under the admitted source path. Runtime dispatch retains the requirement/slot, logical modes and capability guarantees established at the call. A stored copyability class or fully bound associated type can discharge the corresponding condition, but does not authorize runtime overload search. Field requirements retain a selected storage projection rather than becoming owning getters. An owned Self result uses its checked re-erasure plan; a storage address cannot be reinterpreted as writable existential storage of another concrete type.

This closes the semantic producer-to-consumer handoff. Runtime-only opened Self additionally requires the [prepared execution bridge](#runtime-opened-self-execution-bridge); semantic evidence alone is not executable code.

## 6. Signatures, Adapters, and Returns

Instance body construction reads the saved source-body receiver, parameters and logical result contract under the instance environment. The declaration's callable interface remains a separate input for call-boundary checking. A dispatch receiver pattern is not automatically the body receiver type, and a logical source result need not equal a carrier's ABI result.

Final calls retain parameter types, conversions, passing modes, evaluation sources, source-visible result adapters, and the exact callee body identity. Backend lowering reads these instance results instead of reconstructing an environment from a function index and receiver arguments. For extern declarations with no source body, signature preparation has an explicit declaration-based constructor; this is not a fallback for missing ordinary-body facts.

An inherited or forwarding surface can require an adapter around the original body: execute the original body with its original type and apply checked boundary conversions. The adapter has explicit origin, target instance and selected conversion/call evidence. It does not reinterpret the original AST under the wrapper receiver. Its registration also does not imply its target is ready. Physical ABI and adapter realization belong to the representation chapter; this chapter requires preservation of their semantic inputs.

A return reads the saved source result and destination contract, then its instance conversion. It does not derive a new source type from an ABI return slot. Provided bodies, closures, globals and ordinary functions all obey the same distinction.

A library's use of Self is intentional: I64 same-kind operations describe their
applicable parameters, results, associated outputs and trait arguments with
Self; heterogeneous operands and quantities such as U64 distances retain their
concrete types. The compiler must not treat a concrete type name as implicit
Self. [Newtype inheritance](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/10-newtype.md)
therefore changes only the positions the declaration actually marked. The
original body remains typed for its original type behind the boundary adapter.

## 7. Discovery, Recursion, and Execution Readiness

The preparation worklist starts from the command's requested roots and follows selected executable dependencies, including calls, closures when required, destruction, adapters, and runtime/protocol operations. Demand-driven execution may prepare a later target on demand through the common checked boundary; it does not authorize executing an unchecked target or bypassing its instance obligations.

For a repeated instance key, reuse the registered identity and its computation state. A recursive call can refer to a registered signature without recursively rebuilding the same body. Processing an active graph node is not successful completion. Analyses needing a whole recursive component use an explicit graph/worklist or fixed-point protocol and publish only their scoped result, as described in [compiler state](compiler-state.md).

Recursion that generates endlessly different type instances is not eliminated by same-key deduplication. The compiler needs a bounded resource/depth diagnostic with source provenance. Such an implementation limit can prevent `build` or `run` after successful abstract checking; it must not be presented as a new source typing rule or silently truncate the executable graph.

Execution publication requires the concrete body's needed local and interprocedural analyses and its callable dependencies to be satisfied under the execution model. A successfully grounded type, an interned body ID, or source-only checks are each insufficient. Lazy target readiness is handled at the common call-entry boundary, not by a second runtime semantics for generic bodies.

### Runtime-Opened Self Execution Bridge

Retain Plew's checked-body and concrete-instance execution model. An implicitly opened existential chooses a concrete instantiation through a prepared private bridge; it does not turn the existential box into a conforming nominal type or introduce an unspecialized generic interpreter. This is an internal realization of the adopted opening rules, not a wider member-availability or conversion rule.

The saved opening plan identifies the source-selected callable/body, its abstract bindings and admitted conformance relationships, logical ownership modes, and the result's permitted re-erasure. Each existential value retains private concrete type and selected witness identities from injection. They are executable metadata, not public type values, downcasts, or a request to search declarations at runtime. Independent boxes do not gain a same-type proof from this mechanism.

| Stage | Required work |
|---|---|
| Source checking | Commit the operation and opening/re-erasure plan using ordinary applicability. Reject unrepresentable escaping results or unjustified same-type relationships here |
| Concrete existential injection | Register the payload type, exact conformance provenance, associated bindings and typed value operations |
| Execution preparation | Combine a checked opening plan with admitted concrete descriptor identities; instantiate its recorded environment and prepare a typed adapter plus ordinary concrete callee instance |
| Runtime call | Select that prepared bridge by operation/descriptor identity; preserve evaluated arguments, owners and access dependencies; do no overload, trait-path or associated-output search |
| Adapter result | Perform the saved owned-result re-erasure or inout writeback exactly once and retain the original type/guarantees |

A bridge's execution key includes the opening operation's contract, all opened concrete type/witness identities, remaining substitutions, ownership/conversion plan, and required RC/target/ABI specialization. Distinct source provenance cannot collapse merely because the payload layout matches. The callee's concrete body uses the ordinary instance registry and can be reused across equivalent bridge requests. Diagnostics retain the requesting occurrence even when executable adapters are shared.

For AOT, collect concrete existential injections and compatible opening operations along the executable dependency worklist. Close dependencies over their instantiated bodies, adapters, value/destruction operations and further injections before emitting the target. Conservative compatible combinations are allowed; reachability precision is an optimization. With multiple independently opened parameters, required combinations can grow; do not silently omit combinations or substitute an unprepared fallback. A repeated key reuses work, while indefinitely growing type instances receive the existing resource-limit diagnostic. The binary contains every bridge admitted by that closure and requires no compiler service to execute it.

For demand execution, a concrete descriptor is registered before the value is exposed as an existential. An opening operation can request its concrete bridge on first use through the ordinary preparation/publication entry, using the saved descriptor identities and evidence. Prepare the source body under its declared abstract bounds and instantiate that checked meaning; do not type-check it as a new concrete template. Registration or a cached address alone is not readiness. Compilation preserves existing argument evaluation and ownership across the pause, and publication closes effects, typed operations and RC-mode requirements. An existing caller of an unprepared bridge treats unknown effects conservatively under the common enforcement contract; it cannot assume a pure target until first use. Publishing a new bridge must not invalidate an existing caller's omitted-check justification. Further injections or demands can extend the prepared set without changing a previously committed operation's meaning.

The private adapter boundary passes hidden payload storage under the saved copy/borrow/inout/move contract and returns a representable erased result. Representation lowering may use indirect lanes or private descriptor-indexed tables; it must emit a typed adapter under a concrete environment rather than reinterpret unrelated storage with a raw cast. Inout keeps the opened concrete type fixed through writeback. A new owned Self result is repacked using its retained witness; no invariant generic container is mapped elementwise to an existential container.

This chooses concrete preparation plus private dispatch over adopting a general metadata-parameterized generic ABI. [Rust monomorphization collection](https://rustc-dev-guide.rust-lang.org/backend/monomorph.html) supplies a precedent for closing concrete code dependencies, but Rust does not supply Plew's implicit opening rule. [Swift generic signatures](https://github.com/swiftlang/swift/blob/main/docs/ABI/GenericSignature.md) and [type metadata](https://github.com/swiftlang/swift/blob/main/docs/ABI/TypeMetadata.rst) show the alternative of passing metadata and witnesses into generic execution. Plew uses their separation of type and conformance evidence without requiring that alternative execution ABI. Compile-time/code-size growth is acknowledged; specialization, dispatch-table organization and cache precision can be optimized without changing source ownership or introducing a second runtime.

The whole-worker pause protocol remains a separate [R3 design boundary](../issues/com-7knz.md). This bridge must consume that protocol in concurrent demand execution; its descriptor registry does not solve application quiescence. No implementation or performance verification of this bridge is claimed.

## 8. Examples and Change Impact

Consider a source body calling a requirement on `T: Iterator`. Its saved call selects that requirement and its result projection. Instances for two concrete iterators retain their own receiver, witness and associated output. Even if both produce the same physical result type, a backend cache cannot merge their calls solely by that result's layout. Conversely, an identical source/body/environment request reuses the same instance rather than cloning it at every call site.

For a provided copy reached through a trait-subject conformance, preserve the placement proof and source impl substitution independently. Nested calls use the body's justified requirements. The caller's path is not an implicit priority among unrelated requirements inside that shared body. A missing callee body or conversion halts preparation at the required reader; a declaration-name fallback would erase the distinction this example needs.

Adding a new bound or projection form affects source justification, environment construction, evidence substitution, instance keys where meaning changes, and final consumers. Adding a new synthetic body requires origin identity, signature preparation, dependency discovery and readiness. A new backend cache must state why its key preserves the instance distinctions above.

Verification should cover same-spelled binders, nested receiver patterns, method/impl parameter combinations, conflicting maps, provided placement versus source provenance, distinct proofs with equal ABI, recursive same-key reuse, expanding-instance limits, extern signatures, adapters, dynamic existentials, failed re-requests and required-fact deletion. Compare zero-argument and generic forms through the same pipeline. Check execution or expected rejection as well as registry counts; a correctly interned ID does not prove its final consumer uses the right environment.

Capability controls should contrast a copyable Optional with a unique-payload Optional even when its active variant is None, and follow consumption through exactly-once destruction. Nominal finalization needs all-variant, multiple-owned-field and phantom-parameter controls, including rejection of autounique declarations whose capability never varies. Abstract checking must distinguish a meaningless explicit move on a known copyable value from an admitted allowunique move whose copyable instance preserves the caller's binding. Exercise the same conditional family through ordinary calls and via, with missing, overlapping and unproved-disjoint branches. Finally, follow conditional deinit selection and valid absence through ordinary child cleanup and final destruction; preparation-only assertions do not establish these outcomes. The [capability producer contracts](types-and-evidence.md#capability-and-conditional-selection-contracts) and [ownership verification](ownership-and-access.md#targeted-verification-paths) own the corresponding boundaries. These are verification obligations, not executed coverage.

## 9. Comparisons

[Rust monomorphization](https://rustc-dev-guide.rust-lang.org/backend/monomorph.html) collects needed concrete items and generates specialized code, trading compile time and code size for concrete execution. This is a useful reference for Plew's concrete-body worklist. Rust's codegen-unit policy and exact collection staging are not Plew requirements; source checking and execution readiness remain distinct here.

[Swift's generics introduction](https://github.com/swiftlang/swift/blob/main/docs/Generics/chapters/introduction.tex) starts from independently checked generic declarations and requirements supplied by callers. Its runtime metadata convention supports unspecialized generic code, while specialization can remove that indirection. Plew shares the abstract contract but currently prepares concrete body instances rather than adopting Swift's resilient runtime-generic ABI. [Swift substitution maps](https://github.com/swiftlang/swift/blob/main/include/swift/AST/SubstitutionMap.h) retain replacements together with conformances, reinforcing the need to transport evidence rather than just type argument lists. These comparisons do not prescribe new metadata services or a second generic runtime for Plew.

[Swift SE-0309](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0309-unlock-existential-types-for-all-protocols.md) separates existential formation from individual member usability; [SE-0352](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0352-implicit-open-existentials.md) opens a contained type for generic calls and bounds result erasure. Plew adopts this usability direction without treating the existential box as automatically conforming to every requirement. Its copyable and unique existential types are separate and keep the box's capability aligned with hidden Self, avoiding a mixed-capability box and its extra candidate/mode cases. Opening only when a trait bound needs it is a stable semantic rule: an unconstrained generic still sees and returns the box. Plew deliberately does not erase inside nominal generic containers or function signatures, since that could introduce hidden element conversion, allocation, copying or ownership changes. A private concrete execution bridge realizes accepted opening without importing Swift's general runtime-generic ABI.

For allowunique bodies, adaptation to copyable instances neither invalidates the caller's copyable binding nor establishes a lasting borrow of its original storage. This is Plew's by-value contract, not a silent import of Swift's consuming/borrowing conventions. Conversely, unique-only explicit drop avoids destroying a mere copy while suggesting that the original owner's lifetime ended; ordinary scope cleanup remains available for all types.

[Swift SE-0427](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0427-noncopyable-generics.md) separates the default Copyable requirement from its relaxation; its relaxed range is not Plew's unique-only range. Plew also requires an explicit autounique declaration so ownership-derived capability remains visible, while a capability that never varies is declared directly. Rejecting silent range narrowing keeps the declared range truthful. Inherited associated-type redeclaration is rejected to preserve requirement identity and provenance; existing associated bindings express restrictions without introducing another identity or a special redeclaration rule. Bounded disjointness reasoning likewise favors predictable declarations and a simple compiler over accepting every mathematically disjoint family.

Splitting conformance declarations themselves by capability remains deferred: one conformance may select a checked implementation family without also multiplying associated-type and witness identities. Reconsider this only when a concrete use requires switching a whole conformance, including associated outputs or multiple requirements. Any extension must retain bounded proofs of disjointness, coverage and uniqueness, preserve one selected conformance's associated outputs and ownership contract, and never assemble a witness from unrelated conformances or add a more-specific-wins rule. Further unique-payload Optional/Result extraction APIs remain separate library decisions beyond the adopted replace and consuming enum match mechanisms; existing copyable read APIs keep their declared scope.

## 10. Implementation Mapping and Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. `InstanceEnvironment` and `BodyInstance` in [Ir.pw](../../src/Ir.pw) retain receiver, parameter mappings, proof and adapter links. [Mono/Call.pw](../../src/Codegen/Mono/Call.pw) contains environment comparison, `findBodyInstance`, `internBodyInstance`, and body-entry handling. [BodyInstances.pw](../../src/Ir/BodyInstances.pw) owns registry navigation and signatures/results.

The inspected implementation exposes [`matchTypeArgumentConstraints`](../../src/Codegen/Resolve/Expr.pw), with `PatternBindInput` declaring the inference-binder set (Function range for calls, Values for construction) and `TypeArgumentMatch` distinguishing outcomes. These names map the contract above to existing code; they are not a second semantic interface. The older bare-binder consistency scan was removed in the retained remediation work in favor of checking each argument against the selected substitution. Coverage of construction inference and the final consumers remains part of the paused remediation audit, not a completed guarantee of this chapter.

The registry currently reserves signature rows during registration and exposes separate setters; registration is therefore visibly not signature completion. Adapter metadata can also be set after registration. Those construction mechanisms are not proof of an immutable successful execution artifact. Declaration-check module gates and chained calls on associated-type or type-parameter results remain unaudited; module exclusion or unknown-type fallback is not the intended abstract-checking contract. Complete environment-constructor coverage, all worklist cycle/failure paths, and every backend/mangling consumer remain unaudited. Retained type-checking candidates add further source-artifact contracts not all present at this base. No compiler execution or performance measurement was performed, and retained follow-up work is recorded in [local issues](../issues/README.md).

Chapter review checked abstract/concrete selection, instance identity, recursion/readiness, existential dispatch, specification alignment, and the Rust/Swift comparisons. Concrete witness determination is explicitly unique, not selection of the first candidate encountered. No required correction remained in that scope; this was not a complete implementation audit.

## Retained Follow-up Investigations

[generic inference, projections and conformance audit](../issues/com-uutc.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.

## Representation and Restart Boundary

[Checked-body Storage](checked-body-storage.md) owns the adopted physical
representation and implementation restart checklist. [met-si6j](../issues/met-si6j.md)
owns remediation completion; [met-ia09](../issues/met-ia09.md) tracks saved evidence
through real callee environments. The contracts above do not certify that all
current consumers implement them.
