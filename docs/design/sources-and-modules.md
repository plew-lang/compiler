# Sources, Packages, and Modules

**Status:** Reviewed draft. Language rules come from the module and package specifications. Implementation coverage is limited to the inspection described below.

## 1. Responsibility and Boundaries

This chapter owns the transition from selected package inputs to a source/module graph with explicit membership and provenance. It separates dependency resolution, source access, module discovery, and semantic scope construction. The [module specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md) and [package specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md) remain authoritative for source acceptance.

The resolver selects dependency revisions and local bindings from manifests and the applicable lockfile. Source access obtains the selected bytes. The loader discovers files and structural edges from parsed syntax. Semantic lookup constructs visible declaration candidates from that graph. None of these operations substitutes for overload selection or body checking.

Consumer dependency discovery is entry/use-reachable, not an instruction to resolve every dependency listed in every manifest. Loader discovery can demand a package binding from the resolver, which returns the selected source before discovery continues. This feedback does not merge their authorities: the loader identifies a dependency demand; the resolver validates the direct binding and selects its version under the applicable constraints and lock. Admitted inputs must be fixed before they influence checking; body-level lazy requests cannot later introduce edited sources.

| Boundary | Published information | Consumer responsibility |
|---|---|---|
| Dependency resolution | Selected package sources, revisions, dependency-name bindings, and configuration inputs | Load the selected sources; do not independently select a newer revision |
| Source access | Bytes and logical source identity, or a load failure | Parse those bytes and preserve their provenance |
| Module discovery | Module roots, part membership, file-local use directives, and dependency edges | Register declarations and construct visibility under the published membership |
| Semantic scope construction | Candidate identities and provenance under the module/file environment | Select meaning using ordinary checking rules |

## 2. Packages Are Not Modules or Directories

A package is a distribution/dependency unit described by `Plew.toml`. Its name is a consumer-facing binding, not a globally unique semantic identity. The selected source/revision and binding context must remain available to the loader. An external package's public API is reached through its root `_.pw`; callers cannot bypass that gate by interpreting a suffix of its package name as an internal file path.

A module is a root file plus its transitive part files. A directory is only a source organization mechanism. Resolving a directory path to `_.pw` does not include every neighboring file in the module.

Path categories must remain distinct through resolution:

| Source form | Resolution context |
|---|---|
| `@Name` | Dependency binding in the referring package; `Std` is reserved for standard packages |
| `/Path` | The current package's source root |
| `./Path` or `../Path` | The referring file's location within the applicable source namespace |

For example, `@Acme/Http` names one external package; the slash is part of that package name. `/Models/User` identifies a source path in the current package. Normalizing both into an unqualified string and later guessing their category would erase required provenance.

The package layer owns manifest/version/lock semantics, native dependencies, and tool declarations. The compiler consumes their selected inputs. It must not treat dependency membership as proof that every dependency contributes machine code: source checking, generation-time execution, and final executable reachability have distinct purposes. The driver and metaprogramming chapters own those demands.

Resolution follows the specification's newest-compatible policy, with the top-level lock fixing git commits and explicit update changing selected versions. Dependency libraries' own locks do not override that selection. Compatible same-major requests unify; different major versions may coexist and their types retain distinct identities. Standard packages, language items, and core traits require a single version. These are resolver constraints, not spelling-based exceptions in type equality.

The resolver publishes direct dependency bindings per package. A transitive package's presence in the compilation does not grant a source-level `@Name` binding to its consumer. Explicit re-publication exposes the original declaration through the publishing package's API; it does not grant direct access to that dependency's package namespace.

### Standard Library Ownership

[Standard Library Boundaries](standard-library.md) fixes the defining owner and public routes of the foundation, shared references and synchronization APIs. Existing Lang/Core/Hash/Async/Set/Random routes remain; Sync is an explicit standard package above the admitted foundation, not a new implicit namespace. The startup language-item closure registers identities before contract validation and body checking, so ambient references do not introduce reverse use edges or permit source cycles. Source package dependencies are distinct from private generated/native operation dependencies. A standard package has no general permission to call another module's private factories; the exact registered typed operations own that handoff.

### Compiler-Known Declaration Contracts

Dependency resolution selects the admitted package versions, including Std; declaration registration binds compiler-known language operations, protocol mappings, and intrinsics to declarations from those admitted inputs. Registration owns validating their required signatures and ownership contracts before publishing consumable semantic identities. Equal spelling in an unrelated module is not such a binding, and registration of an identity alone is not proof that its required contract passed.

Checking uses these identities through ordinary applicability and conformance evidence. Syntax lowering, Mid, ABI, and runtime emission consume the validated operation contracts rather than rediscovering a privileged declaration by name or silently accepting a replacement signature. Changing a known operation therefore requires updating its registration contract and its consumers together. This assigns responsibility without adopting a new registry API or claiming that every existing intrinsic path already meets it.

## 3. Source Access and Admitted Inputs

Filesystem sources and embedded standard resources implement a common source-access boundary. Embedded resources occupy a distinct logical namespace. A missing embedded source must not silently fall back to a neighboring checkout, because that changes the admitted implementation while concealing its origin.

Source identity must retain the package/source namespace as well as the resolved location. The [session contract](compiler-state.md) fixes admitted source versions and configuration. Discovery may read a set of files before body checking becomes demand-driven; deferred body checking does not permit later file edits to enter that session.

Read failures and empty source are distinct outcomes at the loader boundary. If a low-level API uses an empty string to report absence, the admission layer must establish existence or return a diagnostic; downstream semantic checking must not infer successful loading merely from that string.

Source registration owns the mapping from stored bytes to file and module identity. Current storage uses ordered, disjoint ranges in a shared byte arena. This is a representation choice, not a rule that semantic identity is a byte offset. Gaps and synthetic suffixes must not be assigned to the preceding file by accident. Diagnostics and semantic ownership must use the same registered provenance rather than independently scanning paths or source text.

Source-file range registration maintains ordered, nonoverlapping intervals through
one update API. Membership lookup and diagnostic lookup share the containing-file
binary search rather than independently scanning files. Syntax-root attributes
needed for module identity are derived during registration and attached to the
module identity; readers do not rescan file paths or source text to reconstruct
them. These indexes accelerate explicit provenance, not replace it with spelling
or offset guesses for synthetic bodies.

## 4. Discovery, Membership, and Graph Closure

Discovery consumes the shared parser's structural directives. A second textual pre-scan for `use` or `part` would create a competing grammar and is not part of the design. Loading syntax and registering declarations are separate responsibilities: aliases and declaration identities must be interpreted after the relevant membership and dependency graph are known.

Two graphs must not be conflated:

- `part` edges form a forest: a file has at most one part parent and cannot participate in a part cycle. All descendants belong to the root's module.
- `use` edges connect modules and must form a DAG, including re-publication edges. A part file cannot also be admitted as an independent use target.

The loader must preserve enough edge provenance to diagnose a cycle or conflicting parent with the responsible directives. File deduplication cannot silently resolve conflicting membership by accepting whichever traversal reached the file first. A visited file and a completely discovered module are different states.

Within a module, definitions are shared across root and part files. External names introduced by `use` remain file-local: a part does not inherit the root's external bindings. Part contents are restricted to impl blocks and permitted structural directives; free functions, types, extern declarations, top-level values, and re-publication are rejected there. Membership does not excuse these restrictions.

The module DAG is a source dependency rule. It is not the runtime initialization dependency graph, nor does it forbid recursive calls within a module. Initialization order and cycles belong to runtime preparation under the specification; a DAG does not by itself prove initialization safety.

## 5. Visibility and Generated Membership

Module membership establishes the boundary for non-public declarations. `pub` exposes individual declarations; publishing one overload does not publish private overloads with the same name. `pub use` binds and re-publishes reachable public declarations while retaining their original identities and provenance.

Selective use of a function name imports its public overload set. Local and imported candidates use the same overload-selection rules; their origin does not create priority. Multiple paths to the same declaration do not create multiple distinct candidates. The detailed namespace/candidate algorithms belong in the name-lookup chapter; the loader must supply identities and scope edges that let those algorithms enforce this contract.

Generated sources must have explicit membership, input identity, and provenance before their declarations are used. Generated part files follow the same module restrictions. Generation must not invent a privilege to reach unrelated private declarations or require consumers to reverse-engineer a synthetic filename to find the originating module. The metaprogramming chapter owns generation ordering, host execution, and the precise synthetic provenance records.

Ordinary compilation reads committed generated parts with the rest of the admitted sources. Explicit generation suppresses automatic inclusion of the output being regenerated, avoiding a dependency on stale output. The loader must receive that mode explicitly; it must not infer it from which generated files happen to exist.

The visible `@[...]` directive is the auto-part trigger for the corresponding `.gen.pw`, not merely that file's presence. Ordinary build must diagnose missing or stale required output and direct the user to generation. Freshness evidence and its checking mechanism belong to metaprogramming; silently ignoring the output or generating it as an undisclosed ordinary-load side effect would violate this boundary.

Host tools and target artifacts may need different target configuration and native dependencies. Their source universes and cache validity must be explicit even when they select the same package revision. A host-built generator's successful execution is not evidence that its output is valid for the target.

Construction inputs and post-construction field access are independent
permissions. Explicitly publishing a default memberwise factory does not require
public fields; its exposed argument types still satisfy public API closure.
Default factory visibility remains module-local. The [construction
specification](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/05-structs-enums.md)
owns these rules; lookup supplies their declaration/module provenance rather
than inferring access from a field's physical layout.

## 6. Example and Change Impact

Suppose `Models/_.pw` defines a type and includes `part ./Impl`, while `App.pw` writes `use ./Models only { Item }`. Discovery resolves `Models` to its root and assigns `Impl.pw` to that module. Lookup sees `Item` through the root's public surface. Code in `Impl.pw` can see module-owned definitions, but must write its own use directive for an external helper. Attempting `use ./Models/Impl` is rejected as a part target, even if those bytes were already loaded.

Adding another path that re-publishes `Item` preserves its declaration identity. Adding a private overload under an already public function name does not enlarge the importing module's candidate set. Editing `Impl.pw` after session admission affects a future session, not a pending lazy request in this session.

For a new source provider, change source access and provenance admission while preserving graph and lookup contracts. For a new dependency syntax, update the package resolver and path-category handoff rather than teaching body checking to fetch packages. For a visibility change, update semantic scope construction and affected public-surface consumers; do not solve it by loading fewer files.

Verification should exercise directory roots versus neighbors, nested parts, conflicting parents, part/use cycles, file-local external bindings, selective overload sets and duplicate re-publication paths, and missing embedded resources. Input-version tests must also request an unprepared body after editing its backing file and demonstrate that the old session retains its admitted inputs. These are required coverage categories, not claims that all current tests exist or pass.

## 7. Comparisons and Rationale

[Go's module reference](https://go.dev/ref/mod) distinguishes versioned distribution modules from packages of source files. Plew also separates dependency selection from source-language organization, but its word “module” denotes a root-plus-parts semantic unit rather than Go's distribution unit. Go's version-selection algorithm is not adopted by this analogy.

[Go's import specification](https://go.dev/ref/spec#Import_declarations) prohibits direct and indirect self-import. Plew's DAG rule serves a similar dependency-boundary purpose. Plew's part forest is a separate mechanism for keeping impls in a defining module; it is not a way to weaken the DAG.

[Rust's module reference](https://doc.rust-lang.org/reference/items/modules.html) distinguishes logical module structure from external source filenames. Plew likewise needs explicit logical membership rather than directory-based inference, but chooses a different source rule: part files share a root module rather than introducing nested named modules. These comparisons explain responsibility boundaries, not a proposal to import Rust privacy or Go package syntax.

## 8. Implementation Mapping and Audit Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f`. Focused inspection covered [SourceAccess](../../src/SourceAccess.pw), [SourceFiles](../../src/SourceFiles.pw), and [Loader](../../src/Loader.pw). SourceAccess distinguishes embedded resources from filesystem paths. SourceFiles owns ordered ranges and containing-file lookup. Loader uses shared syntax roots for discovery and rejects non-impl part contents.

This inspection does not certify the full resolver, every path normalization case, all membership/cycle checks, generation ordering, or consistent snapshot admission across every command. Package/bin/tool and native dependency implementation coverage must be audited against their own specification before being declared complete. No compiler execution or performance measurement was performed for this chapter. [Local issue management](../issues/README.md) is available, with gap migration in progress; missing issue links do not imply these areas are audited.

Chapter review checked the responsibility boundaries and module/package/generation rules against the specifications. Its two required clarifications—entry/use-driven resolver demands and directive-triggered generated-part admission—are incorporated. This is a design review, not an implementation certification.
