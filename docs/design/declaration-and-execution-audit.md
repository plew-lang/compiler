# Declaration Checking and Demand Execution Audit

## Scope and Authority

This supplement preserves the integration obligations and audit map behind the
run/check/build implementation. [Driver and Execution](driver-and-execution.md)
owns command coverage, fixed inputs, session/ID ownership, publication, termination,
and the distinction from reusable Hot Restart. [Body Checking](body-checking.md),
[Types and Evidence](types-and-evidence.md), and [Generics](generics.md) own semantic
selection and abstract checking. [Ownership and Access](ownership-and-access.md)
owns safety analysis; [LLVM Backend](llvm-backend.md) owns physical emission.
The names below locate implementation responsibilities, rather than freeze an API
or certify that every present path implements the intended contract.

The migrated plan mixed adopted rules, incremental source inspection, probes,
and completion reports. Its [evidence index](../../../evidence/2026-10-01/compiler/lazy-build/README.md)
keeps those scopes separate. No compiler, performance, or sanitizer test was run
for this documentation migration. Historical missing features are not renewed
language restrictions or newly confirmed current defects.

## Abstract Checking and Concrete Obligations

Declaration checking must validate a generic body in its declaration environment.
It cannot replace that task by enumerating concrete executable instances, clearing
an effect queue, or successfully emitting LLVM. Conversely, justified symbolic
operations need not have a concrete witness, layout, or destruction body yet.

| Operation | Required declaration facts | Work retained for concrete execution |
|---|---|---|
| Call | Selected declaration/requirement, signature, visibility, bounds, receiver and explicit-borrow rules | Substitute the retained selection; establish witness, body identity, and ABI |
| Iteration protocol | Iterable/Iterator evidence, Item term, iterable and loop-binding compatibility | Finalize the selected iterator/next operations and their physical layouts |
| Try conversion | Result operand/return compatibility; identical error type or eligible conversion factory | Register concrete variants and the already justified conversion call |
| Value | Each construction, return, cast, closure, and other source operation's own semantic rules | Produce that operation's grounded facts and layout |
| Storage | Initialization/assignment compatibility, movement, mutability, and access rules | Ground source/target terms and retain the conversion proof |
| Destruction | Unique/borrow rules, deinit declaration checking, and statically knowable global conflicts | Prepare required concrete glue; enforce symbolic/dynamic shared-identity accesses |

`Value` is a broad grouping, not one boolean proving every opcode checked.
`DeclarationAccessAnalysis.obligations` describes unresolved global-effect work,
not the universal semantic-check queue. The historical global-access analyzer
could return empty when no mutable global existed; local-access preparation could
skip ordinary owners without storage arguments. Those are domain-specific omission
conditions, never proof that all source bodies were checked. Zero obligations does
not grant whole-target success. Symbolic/dynamic destruction obligations alone do
not make an otherwise valid generic body erroneous.

Effect closure and executable publication follow the Driver contract. In
particular, a conflict-free partial graph is not a closed graph. Required static
callee/destruction dependencies must be accounted for before an omission is
justified; unknown dynamic effects remain conservative. Closure construction is
not execution of its body. A graph node, source declaration, semantic body, and
physical entry are distinct identities. Later discovery cannot weaken an already
published caller; the current design does not adopt a replacement protocol that
could repair its stale assumptions merely by preparing the new callee.

Concrete global-access closure reports detected conflicts separately from
additional required body IDs. It requests only unprepared bodies reachable from
the demanded roots through selected synchronous calls and concrete destruction
contracts. Body-ID deduplication closes recursive dependencies to a fixed point;
unused destruction contracts are not all enumerated. Dynamic dispatch and FFI
remain governed by their ambient/boundary enforcement, rather than being turned
into unresolved static-body requests. Machine-code demand is a separate worklist.

## Body Request and Cache Integration

The retained integration map identifies these boundaries:

- `prepareLexicalBody` performs type recording, generic/ordinary source checks,
  call recording, default completion, template closure, and recorded-body call
  constraints for the semantic source owner. Registering a callee signature does
  not recursively request its body.
- `callTemplatesClosedForBody` means that selection recording is closed. It is
  neither ownership/access success nor executable readiness. A single-template
  bound check may retain legitimate instance obligations; it is likewise not a
  whole-body success token.
- Unrequested, active checking, success, and diagnostic failure belong to the
  unchanged input session and owner. Both success and failure restore the caller's
  lexical cursor. A partially closed template cannot become cached success;
  repeated failure returns the retained diagnostic.
- Declaration signatures/conformances are registered before body work. Expression
  storage exists before lexical bindings are recorded and is not reset afterward.
  Body type registration follows the body's lexical environment, not an ambient
  caller cursor. Generation has its separate target coverage.
- Bound/protocol checks consume owner-indexed recorded occurrences and the shared
  proof machinery. They must not scan every program call template for each body.
  A derived index includes nested closure owners and synthetic/default calls,
  preserves occurrence identity and append order, and is maintained when rows
  are appended or reindexed.
- Default completion uses a fixed input frontier: generated calls must not be
  completed repeatedly. A default's call belongs to its saved declaration/lexical
  environment. An unrelated invalid body must not be absorbed into a successful
  demanded request.
- Declaration ownership preparation and final executable dependency preparation
  have separate results. Invalid identities are not cached as prepared. A direct
  declaration analysis need not manufacture concrete Drop rewrites for every
  body; concrete destruction preparation occurs when the effect/execution
  dependency actually requires it.
- Global initializer roots are registered once. Partially requested preparation
  can extend to whole-target checking using the same valid caches and failures.
  Closure capture/signature facts precede its concrete body descriptor; instance
  lexical environments and witness adapters retain their selected provenance.

These are integration constraints on the [session request protocol](compiler-state.md),
not a proposal for a second generic request framework. The historical named
functions and state layouts require fresh source inspection before modification.

Type collection owns a narrow lexical scope. `scanGenInstFields` /
`collectGenericMemberTypes` save and restore caller `typeParams`, `typeArgs`,
`selfRef`, and `itemRef` on both success and diagnostic failure; an inner early
return must not bypass restoration. Nominal fields use that nominal's Self and
no caller/method Item. Only method-signature collection installs the applicable
Iterator Item bridge. `collectRecordedType` enables layout registration only
around its `scanType` request and restores `inCollection` on both exits, including
when its previous value was already true. Neither the whole Record pass nor
unrelated inference/backend work gains incidental layout-registration permission.
Restored scratch does not certify that a partially registered failed Comp is reusable.

## Semantic Audit Boundaries

The original probes exercised the following easily conflated cases. Their
contracts derive from the linked domain chapters; the list is an audit map,
not a declaration of exhaustive test coverage.

- **Iteration:** iterator acquisition and next are distinct synthetic call sites.
  Identity iteration has an explicit no-callable meaning; it is not an accidental
  reuse of a numeric dynamic-call sentinel. A prior call's result comes from its
  selected result term and receiver/evidence, including views, projections,
  existential bindings, and closure signatures. An async call's Promise result
  differs from its logical body return.
- **Associated evidence:** a projection must refer to a member actually declared
  by the chosen trait, even without an ordinary source offset. Missing associated
  equality retains a projection rather than inventing a scalar result. Formation
  of an existential, its usable runtime interface, and a static generic proof are
  different checks. Annotation alone is not an executable method use.
- **Proof provenance:** associated declaration constraints, impl subject bounds,
  authored assumptions, inherited trait paths, and implicit Self retain their
  owners and substitutions. Supertrait edges preserve their instances; a child
  impl does not implicitly manufacture a parent impl or prove its own obligations.
  Shared associated-bound evidence preserves the projection, clause, receiver
  prerequisites, and substituted bound. Active recursion is not proof success.
  Exact proof representation is owned by Types and Evidence, not this inventory.
- **Types and values:** established floating widths cannot be made compatible by
  a contextual-literal shortcut. Declared return terms preserve semantic views,
  projections, binders, and containers. Ordinary array fields use ordinary member
  checking; no bare field-name exception proves their existence. Required aggregate
  fields and enum payload presence are checked separately from symbolic type
  substitution. Try requires a suitable Result operand and return/error contract.
- **Capture and storage:** closure captures belong to the closure owner; generic
  capture validity differs from a concrete environment representation limitation.
  Global receivers and zero-sized globals retain storage identity independent of
  source offsets. Conversion/return success must retain the selected source and
  target terms, not only the existence of a finalizer result.

Historic implementation records included `DeclarationBoundRef`, trait-associated
bound ranges, supertrait references, assumed paths, and shared associated-bound
evidence. Those names identify inspected producer/consumer paths; they do not
turn a historical serialized tag or pool layout into a permanent design API.
The independent type-checking redesign and its [tracked gaps](../issues/README.md)
remain relevant; this migration does not assert they are all closed.

Conditional conformance traversal evaluates conditions only on candidate paths
that reach the requested trait, under each source impl's own binder substitution.
It does not infer conditions from method presence or positional instance arguments,
or use flattened derived rows as independent proof authority. An active identical
conditional witness is not an assumption; failed queries and diagnostics restore
the query stack. Revisit detection preserves provenance and path distinctions and
rejects a repeated substituted witness, not every reuse of its declaration edge.
The same edge can therefore be reused with shrinking type arguments without
silently dropping an unchecked alternative conditional path.

## Native Integration Audit Map

The backend's Whole, Requested, and Declarations emission scopes share canonical
preparation. Declarations register identities/signatures without implying body
emission. Requested bodies reference execution-owned storage; success explicitly
observes the requested body emitted. Metadata/tables require session identity,
not just equal byte sizes. Async entry/resume share the semantic body and public
entry identity; frame planning belongs to the concrete body preparation needed
before frame allocation, not necessarily every initial declaration registration.

Historical ORC integration used `plew.body` and `plew.host` metadata for source
identity and explicit host permission. A native consumer must not recover missing
source contracts by decoding symbol spellings or searching arbitrary process
symbols. Restricted backend memory-service fallbacks (`memcpy`, `memmove`,
`memset`, and the applicable Darwin service) remain distinct from source imports;
explicit definitions take precedence. These implementation names are audit
locations, not a new portability promise.

Native names and numeric/text output buffers have explicit owned-copy/disposal
boundaries. Module/context handoff, including failure, follows the consuming
ownership contract in LLVM Backend. Empty diagnostic instruction text need not
allocate a new native buffer for every request, but optimization cannot weaken
that lifetime contract.

JIT-owned global storage is not automatically discovered like loader-owned
static globals by a leak detector. The retained sanitizer integration used finite
root-region registration/unregistration for those allocations, not blanket heap
exclusion. For a logically zero-byte payload, a physical one-byte allocation can
provide an in-allocation data pointer without changing logical length/capacity.
This is an implementation audit requirement, not proof of complete LSan coverage
on every platform or of reusable execution teardown.

### String Literal Decoding

String-literal decoding belongs to the common source/Mid preparation boundary,
not an LLVM-only validator. The recorded map uses `StringLiteral.decodeStringLiteral`
without LLVM or `CompResult`, successful decoded values in an append-only session
table, and operand-time recording so emission does not decode again. Current
source must be inspected before assuming this exact cache/API remains present.

## Evidence and Remaining Audit Scope

The [historical evidence index](../../../evidence/2026-10-01/compiler/lazy-build/README.md)
records early feasibility, declaration/body probes, product CLI tests, and final
completion reports separately. A whole-check corpus result does not establish
all Value opcodes, destruction paths, OSes, or future source versions. A historical
LLVM-lazy preloaded module is not evidence of lazy Plew source checking. Diagnostic
performance samples are not formal current self-compilation results.

The old enum-capture and explicit-free-call-type-argument limitations are historical
observations, not restrictions adopted here. The inline-identity/required-field
probe was subsequently explained and fixed in that record; it is not a new open
bug. Current implementation limitations require current reproduction and the
appropriate local issue. Existing Mid/type-checking and host-lifecycle issues
should be consulted before filing a duplicate. The absence of a fresh audit here
is an evidence limit, not itself a confirmed defect.
