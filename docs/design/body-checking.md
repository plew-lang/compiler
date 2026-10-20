# Expression and Body Checking

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## 1. Responsibility and Boundaries

Source body checking owns the meaning of expressions and statements under a declaration's lexical environment. It applies permitted contextual information, selects calls and members, checks complete type compatibility, and records source control transfer. Its successful result is the authority for instantiation and Mid construction. Neither a later verifier nor the backend is another source type checker.

[Lookup](name-lookup.md) supplies declarations and candidate provenance. [Types and evidence](types-and-evidence.md) supplies semantic terms, structural relations, and justified conformance operations. This chapter owns when those operations are requested and committed. Ownership/access analysis checks the resulting operations and places; it does not correct their source types or select alternative callees. The driver chooses which bodies to request, not a different set of typing rules for each command.

The specification owns [local inference](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md), [function and closure contracts](https://github.com/plew-lang/spec/blob/main/spec/01-basics/04-functions.md), and [value blocks and source completion](https://github.com/plew-lang/spec/blob/main/spec/03-expressions/11-control-flow.md). The design below does not broaden inference by adopting another language's solver.

## 2. Checking Context and Results

Checking receives the source owner, lexical binding environment, declaration binders and bounds, receiver/associated-type environment where applicable, expected value contract if available, and explicit enclosing function/block/loop targets. An expectation is input to construction, not permission to relabel an already typed result.

An expression result distinguishes:

- A produced value with its semantic term, value/place shape, literal constraints, selected projections or operations, and conversion evidence where required.
- Source completion without a value, retaining the transfer target or non-returning call contract.
- A failure with diagnostic provenance. Recovery placeholders are not successful values.

A statement or block can have several completion paths. Its summary preserves normal continuation, yielded values, and transfers to specific enclosing targets. It must not replace every non-continuing path with one Boolean called “diverges.” A `give` completing an inner block and a `return` exiting the function have different consumers.

These are logical result contracts, not mandated new class names. A semantic expression ID is interpreted with its source owner and, after substitution, its instance context. A syntactic navigation ID alone is not authority to read another owner's results.

## 3. Contextual Inference and Commitment

Plew resolves from earlier information and available expectations. Later statements or later branches do not repair an ambiguous earlier expression. Candidate-local inference can be tentative, but failed probes cannot mutate another candidate's bindings or publish partial success. A valid symbolic caller type is already meaningful; it is different from an unresolved inference variable owned by the callee candidate.

Use two conceptual operations: construct/check an unresolved expression under an allowed expectation, and require compatibility of a determined value with a destination. They share structural relations but have different write permissions. A later compatibility check reads the committed source term and produces evidence or an error; it cannot retype a numeric literal, reopen overload selection, or reinterpret a binding from current spelling.

For example, `val x = { give 1I64 }` commits `x` as `I64`. A later use requiring `U8` cannot reinterpret the literal or use that destination to infer the earlier binding; it must apply the ordinary compatibility rule and reject an unsupported conversion.

For arrays, pass an available array element expectation to elements, construct the array term, then check the entire array at the destination. A non-array expectation cannot become the array's type. Empty arrays still need a determinable element type and full compatibility. For records, labels distribute child expectations; checking children does not establish whole-record compatibility or an implicit nominal conversion. Named construction preserves nominal identity and all type arguments, including arguments not mentioned by any field.

For a closure, complete omitted parameter/result annotations from the permitted function expectation before checking its body and publishing its descriptor. Explicit types, labels, and passing modes remain constraints, not fields to overwrite. The resulting function type passes through ordinary compatibility checks regardless of whether the expression is a literal closure, identifier, block, or branch. Partial explicit signatures can inform candidate selection; partial signatures cannot be published as complete closures.

An operator's result expectation is not automatically an operand expectation: receiver `Self`, right-hand type, and associated `Output` can differ. Likewise, a block result's expectation belongs at its yields, not at the value of a nested `return` to another function contract. Optional-chain payload holes receive an explicit child term; they do not make one saved expression arbitrarily change type with each reader's context.

Fixed-width numeric literals are resolved from permitted local context, with
no default numeric type or later-use global inference. This keeps decisions
readable in source order and avoids turning an overload ambiguity into a costly
whole-body search. [Basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md)
owns literal ranges and inference rules. The [conversion
specification](https://github.com/plew-lang/spec/blob/main/spec/03-expressions/12-operators.md)
distinguishes total From conversions from fallible factory construction; cost
or physical representation cannot erase that distinction.

Function labels are part of the semantic signature, with argument names or
explicit suppression rather than separate external/internal aliases. Argument
reordering and implicit relabeling do not repair incompatibility; an explicit
closure can express the intended adaptation. Construction syntax likewise
makes creation visible instead of inferring a conversion from convenience.

## 4. Blocks, Branches, Patterns, and Completion

A shared value-region operation checks a sequence under an optional result expectation and explicit exit targets. A single block uses it directly; each block-bodied `if` branch and `match` arm uses it with the corresponding region. A bare match arm is an expression-result adapter into the same branch aggregation. Match adds scrutinee/pattern checking, binding construction, arm order, and coverage; it does not own another value-block type checker.

`give` evaluates a value, transfers that result out of its target block, and ends that path. `return` checks against the enclosing function's result contract and exits that function. `break` and `continue` retain their loop target; a value-bearing break checks the value-loop result contract. Mid owns cleanup realization, but the source checker must retain enough target and value information to request it correctly.

At a value join, every normally yielding branch contributes a compatible value. A branch that transfers elsewhere need not yield. A path that falls through a required value region is invalid. An expression whose paths all source-diverge cannot itself be supplied at an initializer, argument, operand, or `give` value position. A diverging branch is allowed at a branch-aggregation boundary. These rules do not introduce a bottom type or silently give a non-returning expression the expected type.

Source completion and analytical reachability remain separate. Code following `return`, `give`, `break`, `continue`, a declared diverging call, or an exhaustive empty match is rejected in the affected region. Non-continuation inferred through a loop produces a warning, while later source typing continues. A warned-about `give` after a nonterminating loop still participates in static result typing. The checker follows the specification's composition rules for branches and loops; it cannot derive source divergence from arbitrary CFG reachability.

For example, a value block containing `loop {}` followed by `give 1I64` has a statically checked `I64` result with an analytical reachability warning. If one `if` branch returns and the other contains a nonterminating loop, following code is analytically unreachable and warned about; the loop branch does not turn the join into source divergence. These classifications affect diagnostics and static value formation, not whether the optimizer emits an executable successor.

Completion classification and sequential/branch composition have one owning implementation boundary. Call invocation reads the selected callable's completion contract; it does not recognize a function named `panic`. Rejected or analytically unreachable code does not justify skipping ordinary static checks, but its state must not enter a normal reachable join. Diagnostic recovery after a decisive rejection does not establish a successful body artifact.

Pattern checking consumes the saved scrutinee term, creates stable lexical binding identities with mutability and ownership mode, and checks guards/arms in those scopes. Captures refer to those binding identities. Coverage includes diverging arms; dead-arm warnings are not permission to omit their source checks. Record/enum patterns and their payload projections must preserve types and binding ownership through Mid, rather than rediscover them from a variant name.

The [explicit-divergence decision](decisions/divergence.md) retains the motivation, rejected alternatives, function-value implications, and accepted development costs. It does not replace the specification or broaden this chapter's implementation audit.

## 5. Selected Operations and Evaluation

A source call occurrence records the selected declaration or abstract requirement, receiver/view provenance, type substitution, parameter/result terms, argument mapping, conversions, passing modes, completion, and any instance obligations. Explicit and synthetic occurrences need stable identities; a single source expression can contain several protocol calls. An expression offset alone cannot distinguish those sites.

Selection is not execution order. Explicit arguments are evaluated in their specified order; omitted defaults are then evaluated in declaration order under the default generator's environment. Retain the argument evaluation sources separately from declaration-ordered parameter slots. Forwarding/default adapters and `via` witness construction must preserve the selected operation and this order. A downstream pass must not manufacture a same-named call and resolve it again.

The default expression belongs to its declaring lexical environment, including its generic substitutions and evidence. Default memberwise fields follow the same evaluation contract. Moving an explicit effectful argument into a default can change its order relative to other explicit arguments; purity or optimization success must not switch that rule.

Call-owned temporary receiver and argument ownership ends after that call's access writeback and borrow completion, before enclosing evaluation resumes. This applies to explicit and default arguments through direct, generic, existential, and `via` calls. The result's ownership transfers to the parent evaluation. Named bindings, other shared owners, and ownership transferred into the callee or result retain their ordinary rules; a borrow cannot survive after its last owner disappears. [Mid](mid.md) realizes this with an enclosing result home and an ordinary child ownership scope, including accepted nonlocal exits. No default-specific lifetime container, hidden owner-extension ABI, or destruction suppression is introduced.

Subscript value reads, operators, iteration protocols, `try` conversions, interpolation operations, and implicit calls use the same publication contract as ordinary calls. Their adapters preserve the source-visible result, which can differ from a selected carrier's ABI result. Assignment/place construction also retains selected projections and evaluation-once operands; evaluating an index function is ordinary value evaluation, not an invitation to special-case its syntax.

Aggregate results retain resolved type identity, field/payload mappings, child conversions, and required default generators. A return of a record or constructed enum consumes the saved aggregate result and destination conversion. It cannot infer the value again from the enclosing return type.

## 6. Body Ownership and Publication

A function body belongs to its declaration. A provided-method copy retains the original semantic source owner while its concrete instance has separate placement and evidence. A global initializer and a default-value generator also have explicit owners. A closure has its own body identity and signature, while retaining its lexical parent and captured binding identities. Checking a closure expression's construction does not mean its body has executed or that all interprocedural effects are closed.

For implicit copy captures of a spawn body, source checking admits only immutable value bindings with copyable, sendable contents. Reading an outer mutable binding is rejected even if no write occurs in the spawn body; lowering must not silently replace that binding with a snapshot. An explicit immutable local created outside the spawn body can supply that snapshot. Captured borrow/inout bindings are also rejected. Binding immutability is distinct from freezing a referenced payload. Record capture origin and transfer obligations once for environment construction to consume; do not reclassify mutable bindings downstream. Explicit ownership transfer is a separate contract from implicit copy capture.

Construction is private and owner-scoped. Before successful publication, the owner checks that all required source facts and selected operations are complete for that result's scope. Published facts cannot be overwritten by a subsequent verification pass. A shared traversal or multiple internal passes are acceptable if they have explicit read/write phases; several independent selectors followed by a consistency assertion are not the final design.

| Saved content | Required consumer |
|---|---|
| Owner, source/binder environment, provenance, and source-body receiver/parameter terms and logical result contract | Instantiation, receiver/parameter-local construction, and return checking/lowering |
| Expression terms, shapes, literal constraints, projections, and destination conversions | Instance expression readers and Mid value/place construction |
| Completion and target identities for expressions, statements, and regions | Mid edges, result joins, and cleanup exits |
| Selected ordinary/synthetic operations and explicit instance obligations | Call instantiation, protocol/try lowering, final dispatch |
| Pattern bindings, aggregate field/payload mappings, and conversions | Pattern locals, construction, and return lowering |
| Closure signature, lexical owner, captures, and body identity | Environment construction, closure-body preparation, dispatch and destruction |
| Global binding terms and initializer/default-generator ownership | Global reads and initialization/adapter lowering |

A saved range's presence is not proof that its owner succeeded. Required readers accept a successful owner result and the correct context. Optional absence is allowed only where the result's contract makes that fact optional. Failure or a foreign owner must not fall back to AST inference, declaration lookup, or an old partially filled table.

Body success is scoped. Source semantic success does not imply Mid ownership/access success. Local declaration checks do not imply interprocedural effect closure or concrete execution readiness. The [request protocol](compiler-state.md) retains success/failure and diagnostics under unchanged inputs; requesting a callee signature does not recursively prepare its body. Recursive analyses use their own graph protocol rather than consume active construction as success.

## 7. Storage Decision Still Required Before Implementation

The saved contents above define one logical owner result. They do not yet decide between the physical alternatives retained in [compiler state](compiler-state.md). The comparison must use these fields and the following consumer path, not a preference for arena-style names:

| Alternative | Construction/publication and access | Cost to establish |
|---|---|---|
| Owner-scoped immutable payload with references to shared terms/evidence | Build the owner's expression/operation/binding arrays privately; publish one payload. Acquire that owner's reader once, and pass shared-pool access explicitly during consumption. | Per-owner arrays/allocations; retaining a selected payload must not retain/copy the outer mutable registry or all owners. Shared references must outlive the payload's use. |
| Shared store with prepared owner handles | Build owner-tagged rows and private indexes; publication seals the owner's membership/completeness. A prepared handle gives required readers access only to that published scope. | Appending another owner must preserve old IDs without cloning all retained fact tables. No mutable accessor or raw handle may bypass owner success. |

For either design, type/proof pools have session lifetime or another explicit retained lifetime; an owner handle alone cannot extend a destroyed session. During consumption, acquire a body context once and read many facts. Do not acquire a value snapshot of `Comp` or every semantic table for each expression. The comparison must specify retain/drop traffic, CoW when another owner is appended, index lookup, and failure rollback or isolation.

This remains an implementation-blocking internal design choice, not a language question and not permission to continue incremental cache guards indefinitely. Resolve it with a concrete API/storage sketch and representative acquisition/append costs before restarting the paused type-checking migration. Neither a new typed IR nor a universal global pool is adopted by this chapter.

## 8. Representative End-to-End Paths

A normal overloaded call begins with lookup candidates and available argument/context information. The checker commits one applicable declaration, mappings, types and conversions. Instantiation supplies its environment and discharges obligations. Mid consumes that instance; LLVM consumes its final call target and argument/result adapters. Ambiguity is a source failure, and an unchanged repeated request returns that failure rather than a partially selected candidate.

A generic requirement or provided body commits the abstract requirement and source evidence under its own bounds. Instance preparation performs the first legitimate concrete witness selection for that requirement, then grounds the saved types and operations. A different caller instance cannot overwrite the abstract result or reuse another instance's evidence merely because the ABI looks identical.

For a global initializer containing a closure and a constructed record, preparation records the global binding term, aggregate child conversions, closure descriptor and lexical captures under explicit owners. Closure-body demands use its own identity and inherited binder context. Mid initializer construction consumes the global artifact; closure environment construction consumes the descriptor; later global reads consume the saved binding term. Missing aggregate conversion or unpublished closure ownership stops preparation instead of reopening the source tree.

A `try` or iteration operation follows the same selected-site path, including protocol requirements, result projections, conversion proofs, and completion targets. An earlier call result used by a later operation is read under the caller's explicit instance environment. It is not recomputed from a callee declaration under an ambient cursor. This closes the dependency from saved source result through concrete use.

## 9. Change Impact and Verification

Adding an expression form requires explicit expectation propagation, produced value/completion behavior, selected synthetic operations, owner publication, and final-consumer support. Changing a block rule belongs in the shared region/completion operation and its Mid consumer, not three independent block/if/match implementations. Adding a verifier must declare which published facts it validates and which new analysis result it produces.

Verification should compare direct expressions with block/if/match wrappers; compatible and incompatible expectations; fixed numeric types; empty and nonempty aggregates; labeled function values; source divergence and loop warnings; pattern capture/mutability; ordinary and synthetic call sites; generic/provided instances; and globals/default generators. Include failed re-requests, foreign owners, required-fact deletion, and stability while a second owner is prepared. Source tests must reach final execution or the expected rejection; storage-reader tests cannot prove removal of downstream re-inference.

Default-call verification additionally covers multiple omissions, method/factory and trait/`via` routes, generic and associated substitutions, declaration-scoped side effects, ambiguity, and rejection of defaults on trait requirements. Lifetime probes cover explicit unique borrows, temporary receivers, nested calls, returned unique/Ref ownership, named bindings, inout writeback, conditional evaluation, and nonlocal exits. A successful adapter shape alone does not establish the final destruction order.

A migration slice replaces producer, saved result, instantiation reader, and final consumer together. Remove the old writer and fallback reader once that path is closed. Validation-only additions and privately wrapped legacy tables are useful intermediate steps, not completion. Whole-command static checks and performance gates remain separate from the design review performed for this document.

## 10. Comparisons

[Swift's type-checker design](https://github.com/swiftlang/swift/blob/main/docs/TypeChecker.md) separates contextual constraints, solving, and applying a solution to make selected overloads and conversions explicit. That last boundary is especially useful here. Plew retains forward, local inference and does not adopt Swift's alternative ranking, implicit conversion catalog, or whole-expression search behavior. Separating tentative work from committed results does not require implementing Swift's solver.

[Rust's inference context](https://rustc-dev-guide.rust-lang.org/type-inference.html) distinguishes tentative probes and rollback from committed constraints and retained obligations. Plew needs the same isolation property for candidates, but not Rust's later-use inference or lifetime machinery. [Rust THIR](https://rustc-dev-guide.rust-lang.org/thir.html) provides an example of typed, body-owned input making calls and adjustments explicit before MIR. This supports complete per-body semantic input; it does not establish that Plew needs a separate THIR or identical body-storage lifetime.

### Default Arguments and Temporary Lifetime

Plew combines implementation-side default expressions with trait-required callable forms through [shared applicability](name-lookup.md#shared-callable-applicability). This deliberately differs from Swift: a method with an optional parameter does not itself satisfy a protocol's parameterless requirement. Swift's [protocol declaration rules](https://docs.swift.org/latest/documentation/the-swift-programming-language/declarations/) and [SE-0411](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0411-isolated-default-values.md) are references for separating requirement contracts from default evaluation, not a mandate to copy its witness rules.

Plew ends call-owned temporary ownership at call completion so direct calls and synthesized witness forwarding can share ordinary scope cleanup. Requiring arbitrary implementation-side defaults, dynamic witness forwarding, and retention through the enclosing expression together would require transporting additional ownership beyond the forwarding call. That extension is not adopted. [Local Swift and C++ probes](https://github.com/plew-lang/meta/blob/main/evidence/string-formatting-interpolation/default-argument-survey/README.md) distinguish observations from language guarantees: Swift 6.2.3 released the tested class and noncopyable borrowing temporaries before outer output in both optimization modes. This does not establish exact destruction timing for all Swift values or named locals. C++ reference-argument temporaries lasted to the enclosing full expression for direct/virtual calls but ended within hand-written wrappers. Its [temporary rules](https://eel.is/c++draft/class.temporary) are distinct from value-parameter destruction.

Other comparisons isolate which parts transfer:

| Reference | Relevant difference or similarity |
|---|---|
| [C++ defaults](https://eel.is/c++draft/dcl.fct.default) | The declaration visible through the caller's static type supplies defaults, including virtual calls; this is not implementation-only default satisfaction of a shorter requirement. |
| [Kotlin evaluation](https://kotlinlang.org/spec/expressions.html#function-calls-and-property-access), [functions](https://kotlinlang.org/docs/functions.html) | Explicit arguments precede omitted defaults in declaration order, as in Plew. Overrides use base defaults. [GC lifetime](https://kotlinlang.org/docs/native-arc-integration.html) does not supply Plew's deterministic temporary cleanup. |
| [Julia optional arguments](https://docs.julialang.org/en/v1/manual/methods/#Note-on-Optional-and-keyword-Arguments) | Desugaring into methods of different arities resembles forwarding surfaces, but does not settle ARC/unique lifetime. |
| [Dart functions](https://dart.dev/language/functions), [C# parameters](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/language-specification/classes#1562-method-parameters) | Restricted constant/default forms do not model arbitrary resource-producing default expressions. |
| [ECMAScript parameter initialization](https://tc39.es/ecma262/#sec-functiondeclarationinstantiation) | Defaults run during parameter initialization for missing/undefined arguments; GC object lifetime is a different contract. |
| [Python defaults](https://docs.python.org/3/tutorial/controlflow.html#default-argument-values) | Definition-time evaluation and sharing differ from Plew's per-call evaluation. |
| [Rust functions](https://doc.rust-lang.org/reference/items/functions.html) | No ordinary default-parameter syntax, so no direct precedent for default-based trait satisfaction. |

## 11. Implementation Mapping and Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. [Record.pw](../../src/Codegen/Resolve/Record.pw) contains `prepareLexicalBodyUncached`, which runs recording, generic checking, declaration verification, and recording again. This locates the current source preparation boundary; it does not prove those passes share one selector. `SemanticExprType`, `SemanticClosure`, and `CallResolution` in [Ir.pw](../../src/Ir.pw) show existing storage for expression, closure, and final-call facts, including legacy carriers.

The paused type-checking review identifies incomplete producer-to-consumer closure, independent selectors, and expensive snapshot acquisition. Its retained implementation candidates are not all present in this inspected source base. This chapter describes the intended authority and publication contracts without claiming those candidates have completed them. Every expression form, synthetic path, storage cost, and final consumer has not been audited here. No compiler execution or performance measurement was performed; retained implementation follow-up work belongs in [local issues](../issues/README.md).

Chapter review checked source authority, inference/completion semantics, owner publication, final-consumer paths, and the primary-language comparisons. Receiver and logical result signature contents and forward-inference/completion examples were made explicit. No required semantic correction remained within that scope. The unresolved physical storage/API decision still blocks implementation restart; chapter review does not discharge it.

## Retained Follow-up Investigations

[retained acceptance-combination audit](../issues/com-uutc.md), [closure environment shapes](../issues/com-b1ro.md), [unique result and region boundaries](../issues/com-5n4i.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
