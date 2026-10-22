# Metaprogramming and Generated Code

## 1. Responsibility and Boundaries

Generation constructs and executes a host program that transforms annotated syntax into additional Plew source. Ordinary compilation consumes the resulting source; it does not secretly execute generators. The generator owns harness construction, host dependency selection, execution and output publication. The loader owns admitting the output as a part, and ordinary semantic checking owns its validity.

The [metaprogramming specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/16-metaprogramming.md) owns macro roles, directive forms, AST input, add-only output and auto-part behavior. [Syntax](syntax.md) owns the shared grammar and arena/value-AST boundary. [Sources and modules](sources-and-modules.md) owns membership and source snapshots. This chapter does not introduce general compile-time evaluation, expression macros, or another source type checker.

Generated output obeys the same [root-owned use contract](sources-and-modules.md#root-owned-use-bindings) as handwritten parts: it cannot contain `use`/`pub use`. Consumers explicitly supply required dependencies and binding names in the target module root; providers document that contract. Neither generation nor loading silently edits the root or hoists output imports. Provider/harness dependency selection for the host is independent of these consumer-root bindings. Import verbosity and generated-name collisions are recorded reconsideration conditions in that source contract, not current macro exceptions.

## 2. Macro Identity and Host Contracts

A directive names an existing declaration with a registered macro role. The provider's owner alone may attach that role. Cross-module use requires both the declaration's visibility and a public macro role; recognizing the spelling `Hash` is not sufficient. Directive-name resolution follows ordinary use/visibility rules before trusted harness synthesis.

`Derive` and `ParameterizedDerive` are host-only `macrointerface` contracts, not ordinary runtime traits. The generator recognizes their supported package-qualified identities. They do not imply runtime conformance, existential boxing, extension membership, or a generic `where T: Derive` capability. A known interface's role and invocation contract are checked explicitly.

Bare `@[X]` requests the associated `Derive` operation. Parenthesized `@[X(...)]`, including `@[X()]`, constructs the configuration value for `ParameterizedDerive` and invokes its instance operation. The presence of parentheses is semantic information and cannot be replaced by testing whether the argument list is empty. Configuration arguments follow the applicable construction/visibility rules; synthesis cannot bypass them merely because it creates the call internally.

Eq and Hash use their owners' regular macro roles and the same execution path as user providers. Ord has no derive. Library dependency problems do not justify a compiler-only same-named synthesizer or relaxing role ownership. Separate host syntax/macro dependencies from the target runtime surface instead.

## 3. Syntax Input and the Process Boundary

A derive receives a `TopItemAst` value and returns a String containing generated source. The input exposes annotated syntax, including bodies, defaults and directive arguments, without requiring those target bodies to type-check or execute. The target source must be parseable and its directive/provider resolvable; syntactic availability does not establish semantic validity.

The adopted runner boundary is String-to-String. The macro library's `deriveFromSource` adapter parses the supplied source/range with its selected Syntax version and delegates to `derive`. The runner does not marshal an internal compiler arena or depend on the macro AST's binary layout. [Syntax](syntax.md) defines materialization from the shared grammar into the macro-facing value tree.

Input spans retain original source coordinates. The source snapshot and range must refer to the same admitted input, including when the harness embeds an escaped source literal. Diagnostic provenance distinguishes the directive, annotated item, provider implementation, harness operation and generated output. Parsing the same input through the library must not shift spans into the synthetic harness by accident.

This boundary permits different providers to use different Syntax versions, but does not itself implement that isolation. Providers requiring incompatible package graphs must be compiled in isolated host units or an equivalent explicit arrangement; their nominal AST types cannot simply be linked into one unifying compilation. The generator owns the host-unit and aggregation protocol below; String compatibility does not establish package-graph compatibility.

## 4. Building the Generation Program

Generation follows these responsibilities:

1. Admit the requested source and its source dependencies, preserving directives and annotated syntax. Suppress automatic inclusion of the output being regenerated explicitly, rather than depending on whether an old file exists.
2. Resolve each requested directive's provider, role, configuration form and provenance. Generation of one source file does not recursively regenerate every annotation in its dependencies.
3. Replace the application's entry point with a harness invoking the selected adapters and collecting their returned source. Retain explicit identities for synthetic calls and their source origins.
4. Select the host executable closure rooted in those operations, including required function bodies, configuration construction, globals and initialization dependencies. Check and prepare that program through the normal semantic/ownership/instance boundaries.
5. Compile for the host, execute it, and publish the output for the requested source only after successful generation. Ordinary target compilation later parses and checks that output.

Loading declarations to resolve the provider is different from checking all application bodies. The generation program's complete checking requirement applies to its selected program, not every unused application body present in the source tree. Conversely, `genMode` cannot become a permissive acceptance rule for ordinary `run`, `check` or `build`. Macro code and selected helper bodies receive normal checks, including unexecuted branches of demanded bodies.

The annotated item is data. A macro generating an implementation that the item needs must not first require the missing implementation to exist merely to obtain that item's AST. A provider that itself calls the not-yet-generated implementation has a real dependency cycle and is rejected. Same-file or same-module providers are allowed when this dependency closure is valid; file colocation is neither a cycle nor permission to bypass checks.

### Host Units and One Output Publication

The generator resolves an ordered list of directive invocations for one target source snapshot. It partitions those invocations into compatible host units: every unit must admit one consistent host package/configuration graph, including provider Syntax versions. Conflicting graphs require separate units with independent source/instance identities. A String result crosses units; nominal AST values, arenas and witnesses do not. Logical host units and invocation membership are fixed by admitted dependency-graph compatibility for the requested generation, not by cache hits, job count or runner batching. Construct the plan in source/directive order: assign each invocation to the earliest existing unit whose complete merged resolved graph remains valid, or create a new unit if none qualifies. Preserve resolved revisions rather than re-resolving them to make a merge fit. Compatibility need not be transitive, so membership comes from this deterministic plan rather than an assumed equivalence class. Repeated invocations of the same provider under the same admitted graph share its logical unit. Each unit is one ordinary host program: its selected globals have one identity, initialize once and retain state across its invocations until that program ends. Execute its invocations in their original relative order. A physical split or batch must preserve that identity, initialization count, state visibility and cleanup; it cannot reset the provider between calls as an optimization. For example, two calls incrementing the same selected global counter must not change from 1,2 to 1,1 merely because the runner changes batching. Incompatible graphs have separate host-program state; isolation is not permission to split a compatible logical unit arbitrarily. The generator retains unit and invocation identities in its generation plan. This protocol does not require a new serialized AST or a process per directive.

Each unit returns a result associated with the generator's invocation identity, not an independently chosen output filename. The generator collects one successful String per invocation and assembles them in the original source/directive order. It owns framing and diagnostic output separately, so an incidental provider print cannot become generated code. Units must not append to or replace the shared final generated file themselves.

A failure in resolution, host preparation, execution or result collection fails generation for that target source. Keep returned fragments private until all invocations succeed; then stage and publish one combined artifact through the output/provenance boundary. An older complete artifact may remain after failure but must not be relabelled as the new success. Target source, provider or configuration changes during generation invalidate the attempted publication. Artifact staging, replacement and validity binding must make an interrupted publication unusable as a mismatched successful generation; the exact file/receipt encoding is an implementation detail of the freshness contract.

## 5. Globals, Host Dependencies, and Execution

The selected host program includes values referenced by the macro and its callees, plus values and functions transitively needed by their initializers. It applies ordinary eager initialization and ordering rules to that set before macro execution. An unreferenced registration initializer is not retained solely for its side effects. Necessary registration/setup must be an explicit dependency of the macro program.

This selection does not change ordinary application initialization: its eager global semantics remain in the modules/runtime contracts. Declaring a global's type and checking its initializer body are separate demands; scope preparation must not indirectly check an unselected application initializer.

Host execution uses host target configuration and native dependencies. Target SDKs, layouts and runtime values must not leak into the host artifact through a cache keyed only by package revision. Cross-compiling the final application does not mean the generator runs on the target. Host compilation uses the same language/runtime semantics, not a relaxed interpreter or a duplicated macro-only ownership system.

A separate execution process is a failure and ABI boundary, not automatically a sandbox or proof of determinism. A provider's host I/O and external inputs can affect its output. The compiler must not infer purity from the word macro or cache outputs as a pure source function without an explicit validity policy. Resource limits and command cancellation remain implementation details to establish before claiming coverage. The host-unit aggregation protocol above owns isolation and output framing; no inspected runner is certified by that design.

## 6. Output, Provenance, and Ordinary Checking

The source owner is unchanged. Generated `<Foo>.gen.pw` adds declarations to `<Foo>.pw` through ordinary part membership; it does not edit or remove the original item. “Add-only” describes language output, not perpetual byte appending to an old file. Regeneration replaces the generated artifact rather than accumulating stale duplicate declarations.

Generation execution, output publication and target acceptance are distinct successes. On execution failure, partial returned source must not be presented as a successful current artifact. The generator stages one complete combined result and publishes it with its matching validity identity; readers reject interrupted or mismatched publication. This design contract does not claim an existing atomic implementation. A successfully generated String can still contain invalid Plew source, which ordinary compilation diagnoses in the generated file.

Generated parts obey the ordinary allowed-item, visibility, ownership, coherence and public-API rules. There is no macro-specific “only impls for the annotated item” filter. Each part uses the target module root's shared bindings and cannot declare `use` itself. A generated Hash implementation requires the consumer root to supply Hash/Hasher; it does not inherit the provider module's imports or gain access to unrelated private modules.

The visible directive triggers auto-part admission. Required missing or stale output is an error directing the user to generation. Merely finding a neighboring `.gen.pw` is not a trigger. Ordinary `run`, `check` and `build` do not execute a provider or rebuild its host executable to validate generated source.

### Recorded-Input Validation

Plew adopts explicit generation, with generated source and its portable generation receipt retained as project/distribution inputs. The generator produces the receipt only after all logical host units succeed. The loader consumes it before admitting the generated part; ordinary semantic checking then checks that part as source. The receipt is an association with recorded inputs, not proof that arbitrary provider observations would still produce the same output.

| Recorded identity | Admission comparison |
|---|---|
| Generation-contract version and logical target source identity | Supported validation contract and the intended source/module association, independent of checkout location |
| Original input source content and ordered directive/provider/configuration identities | Current admitted source snapshot, resolved macro roles and project-declared generation configuration |
| Resolved provider and transitive host dependency identities | Selected source/manifest/lock identities, including content fingerprints for mutable local/path inputs; a version label alone is insufficient |
| Complete combined generated source | Content bound to that same receipt; neither file existence nor mtime establishes validity |

Use content identities and resolved graph membership, including relevant configuration and local input additions/removals, rather than absolute author-machine paths. Source fingerprinting may conservatively cover a whole admitted source file/package; it must not omit provider helper or configuration changes that the recorded contract covers. Exclude the output being regenerated from its own original-input fingerprint. Existing generated dependencies that genuinely belong to a provider's admitted input remain explicit dependencies. Do not execute or type-check arbitrary provider bodies merely to compute these identities.

A fresh checkout containing matching source, generated output and receipt is admissible without the author's generator binary, host SDK, execution cache or machine environment. Resolution/source access may obtain the selected source identities under the ordinary package rules; it does not run host generation. Record the actual generation host/tool/native provenance where needed, but do not require a consumer on another host to recreate it just to read committed Plew source. If required comparison evidence is unavailable, report that validation cannot establish current output and direct the user to resolution or explicit generation; do not silently certify it.

Missing output, a missing/invalid or unsupported receipt, changed recorded inputs, or an output/receipt mismatch rejects auto-part admission with an actionable generation diagnostic. A failed/interrupted generation must not publish a new successful receipt or relabel an old output as current. Stage a complete output and matching receipt before success; their encoding may be embedded metadata or a coupled record, but interrupted replacement must never admit a mismatched pair. Commit/distribute the receipt with the output. These checks detect accidental inconsistency, not maliciously forged metadata or semantic bugs in a generator.

### External Observations and Reproduction

Arbitrary provider reads of other files, environment variables, network services, time or randomness are outside recorded-input validation. Such I/O is not forbidden by this freshness policy; its permissions still follow the applicable host-execution contract. Changing `schema.json` read only through a provider's file I/O, for example, does not by itself make ordinary build reject an unchanged recorded input set. The author must explicitly regenerate when those inputs change. A project-declared generation setting or admitted source input is recorded even if a provider also observes other data; the distinction is managed input identity versus arbitrary runtime observation, not whether a file is inside the repository.

Do not automatically reuse generated output as a pure-function result of the recorded source key: an explicit generation request executes its logical invocations, preserving their state and effects. Compiled host artifacts may be reused under their own valid build/provenance contract. Automatic external-input discovery, an external dependency declaration API and hermetic output reproducibility are not first-edition requirements. They require separate adoption if later needed; a source fingerprint is not a claim to implement them.

Generated-source diagnostics retain the generated file's location and origin association. Macro input diagnostics retain original locations. Mapping every generated token back to an input token is not currently an adopted requirement; provenance must remain useful without pretending a String output carries an exact expansion map.

## 7. Bootstrap and Runtime Separation

Committed generated parts are bootstrap inputs. Bootstrapping or ordinary building does not need to execute every derive again. Generator changes and output regeneration have their own validation path; the normal build then checks the committed output as source.

Syntax models, parser implementation and host macro interfaces must not become mandatory runtime dependencies merely because Eq/Hash providers belong to core declaration owners. Preserve owner rules and separate host dependency surfaces. The exact package split is an implementation decision still requiring dependency verification; this chapter does not invent a new package name as an adopted API.

## 8. Examples, Change Impact, and Verification

For `@[Hash] struct Point`, lookup first resolves Hash and its visible macro role. The provider receives Point's syntax even if Point does not yet satisfy Hash. Its host dependencies are checked and executed, and the returned implementation becomes the generated part. Ordinary compilation checks that implementation using the target root's shared bindings, including its explicit Hash/Hasher imports. The compiler never treats the annotation's existence as proof that Point conforms.

For `@[Configured()]`, preserve the parenthesized form even with zero fields: it requests configuration construction, unlike bare `@[Configured]`. A runner selecting the interface by argument count would violate the source contract. For a same-file provider that invokes an implementation it is about to generate, reject the generation dependency cycle instead of enabling stale output or skipping the provider's checks.

Changing the AST model affects Syntax and providers, not a runner-owned AST ABI. Changing directive visibility affects declaration/role resolution and harness provenance. Changing global selection affects generation-program construction and initializer dependencies. Changing output freshness affects receipts and loader admission, not source type inference. Adding a new macro kind requires a specification decision; do not stretch derive into arbitrary token/DSL expansion.

Verification should cover bare versus empty-parenthesized directives, provider/declaration privacy, configuration access, same-file providers, valid generation-before-conformance, real provider cycles, selected versus side-effect-only globals, host/target separation, original spans, generated imports, invalid output, missing/stale parts, failed generation publication, and repeated regeneration without duplicates. Include a fresh checkout with portable receipt, helper/local dependency edits, invalid/missing receipts, output/receipt mismatch and interrupted publication. Contrast a recorded project setting change with an untracked external file/environment change: the latter requires author-triggered regeneration, not hidden provider execution. An explicit repeated generation must still invoke the provider even when recorded inputs match. Preserve separate evidence for generation success and ordinary target acceptance. No timing or successful harness execution proves that syntax versions are isolated or freshness is complete.

## 9. Comparisons

[Go generation](https://go.dev/blog/generate) is explicitly separate from ordinary build and encourages checked-in generated source. Plew adopts that visible workflow and author-managed external inputs. It additionally checks recorded source/provider/configuration identities before auto-part admission; unlike Go generation, this bounded stale-input rejection is part of Plew's contract. It does not add automatic dependency analysis of arbitrary provider I/O or arbitrary build commands as language semantics.

[Rust procedural macros](https://doc.rust-lang.org/reference/procedural-macros.html) operate on token streams, with derives adding items during compilation and host-resource access carrying build-tool risks. Plew instead supplies a shared parsed AST and writes source in a separate command. Rust's same-crate restriction, inline expansion and unhygienic expansion model are not imported into Plew.

[Swift expression macros](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0382-expression-macros.md) use separate implementations operating on SwiftSyntax and check expanded results. They also type-check expression arguments before expansion, which is appropriate to that macro kind. Plew's derive target is syntax data and need not pass target semantic checking before generation. The common lesson is the explicit syntax/implementation/result boundary, not Swift's expression-macro ordering or plugin API.

[Swift attached macros](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0389-attached-macros.md) are a closer comparison for declaration-based generation: roles describe additions such as peers or members, and implementations receive declaration syntax. Plew retains one derive output as an ordinary part rather than adopting role-specific inline expansion or declared generated-name sets.

## 10. Implementation Mapping and Open Decisions

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. [Gen.pw](../../src/Codegen/Gen.pw) synthesizes a harness and passes original source slices with offsets. Its inspected path directly synthesizes `parseItem` and `derive` calls, rather than using the adopted library-owned `deriveFromSource` boundary. It also branches on argument count, which does not establish correct preservation of empty parentheses. These are concrete boundaries to audit/migrate, not alternative adopted semantics.

Authoring templates/quote/unparser APIs and any future raw-token or DSL macro boundary are not adopted here; extending derive into those features requires their own specification.

Host-unit isolation and combined publication are design contracts above; their implementation, recorded-input receipts and host/runtime dependency splitting remain unverified as identified in the audit. External-observation freshness is excluded by the adopted scope, not an unresolved guarantee. Exact implementation coverage of macrointerface roles, selected-program checking, host dependency discovery and ordinary output rejection has not been fully audited. Retained frontend summaries describing a gen “whole-input check” must be read as selected generation-program checking; inspecting AST input must not require all application bodies to succeed. No compiler execution, generation gate or performance measurement was performed for this chapter. Retained implementation gaps are tracked in the [metaprogramming audit](../issues/com-vy62.md).

Chapter review checked macro-role identity, syntax versus host-program checking, initialization selection, source/runner boundaries, open protocols and the primary-language comparisons. No required correction remained in that scope. This is not certification of the inspected generation implementation or generation-gate success.

Retained follow-up work on provider-version isolation, host dependencies and
generated-source freshness is tracked in the [metaprogramming audit](../issues/com-vy62.md).
