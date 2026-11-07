---
id: com-9hde
status: in_progress
deps: [com-zdod, com-scq5]
links: [com-amjl]
created: 2026-11-06T23:54:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Parse and lower complete trait-instance views in type and value syntax

Contract: [spec09](../../../spec/spec/02-type-system/09-extensions.md) method-source selection and complete trait-instance views; [Types and Evidence](../design/types-and-evidence.md) sections2-4 and [Name Lookup](../design/name-lookup.md) section5. A selector means canonical trait owner plus every positional argument; no argument omission even with one conformance. Memberless views and associated projections are distinct. Extension sets remain separate from the single complete trait selector; unrelated base members remain visible under the existing rules.

Evidence: [executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-instance-state.json), source8a2ab6c6, exact Syntax8c89204230c3d865ea95a03382c3fd213731e1de. Sixteen check inputs and five JIT/five AOT executions were independently reviewed. The carrier has experimental cycle Source annotations unrelated to selection; it is not an adopted final candidate. Initial direct-requirement declaration overlap is excluded as a view control; wrong-instance refusal is not validated by failures that also reject matching calls.

## Scope and Endpoint

After the shared term artifact exists, support a#P[I64] and A#P[I64] through exact shared @Plew/Syntax nodes, legacy AST adapter, immutable Syntax lowering and authored provenance. Value parsing currently treats the brackets as indexing (Syntax3348); type parsing5008 drops P without a following member and leaves projection arguments, which Lower/Types742 copies into assocTraitArgs. Resolve the selector declaration in lexical scope before validating positional arity; do not infer omitted arguments or recover an absent owner from global spelling.

Both source forms must lower to the same complete selector contract, with T#P[I64].Item preserving its existing receiver/trait/member identity. Require all positional arguments even for one available conformance; preserve argument-free traits and distinguish wrong arity from unknown trait. Preserve refusal of impl A as P when P has parameters; when using the shared trait arity admission, diagnose the known declaration's missing arguments rather than an unknown trait. Update Syntax exact dependency revision/lock consistently; no local override as completion.

## Guarantees and TDD

Turn the saved explicit value-view and matching annotated-view failures into producer-boundary regressions. Cover value/type/projection syntax, zero/one/multiple positional args, missing/extra args, nested type applications, aliases/qualified owners and two instances of one trait. Inspect actual lowered selector and children/provenance; parse success or byte spelling alone does not prove valid formation. Pair malformed syntax/error recovery with ordinary indexing: a#P[Args] must not become an index operation, and existing legitimate indexing after views and parenthesized expressions must not silently change. Include valid setups for array#Ext[index], array#NoArgTrait[index] and (array#Ext)[index], alongside parameterized trait arguments; these are preservation test requirements, not a new ambiguity rule. Do not guess type versus value from identifier spelling; if an actual grammar/meaning conflict cannot be resolved under the approved rules, stop for a decision rather than silently add a new precedence/whitespace rule.

## Completion and Boundaries

Close the Syntax->Lower->shared published selector path with meaningful RED/GREEN, exact Syntax pin uptake and neutral review. A successfully formed term is not proof of receiver conformance or correct method dispatch. Associated projection and memberless view arguments must not share phantom storage. com-amjl owns common source-conformance evidence admission; the call-selection task owns actual exact-instance dispatch/final consumers. Existing extension bindings, ordinary indexing, block/interpolation syntax and projection rules are preserved; no parser-wide cleanup, new surface feature, blanket undeclared-type recovery or verifier weakening.



## Initial Producer Scenarios

Start with the existing-API producer regression in Syntax/tests/TraitViewSelectors:
memberless A#P[I64] must retain its selector through direct parsing, materialization
and freezing; zero-argument A#P and A#P[I64].Item are preserved controls. Extend
this to complete child arguments, aliases/qualified paths and ordinary indexing
before final uptake. A parser setup failure is not semantic RED. Product source
remains unchanged until the executed regression is established.

## Grammar Handoff Contract

The [executed producer RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-syntax-producer-red.json)
shows the lost type-position selector. Value-position brackets may be positional
trait arguments or existing indexing. Shared Syntax must preserve sufficient
syntax to classify that application after lexical source binding. Parameterized
traits require a complete application; extension and zero-arity trait views are
already complete before the preserved index. No name-spelling guesses, semantic
fallback between meanings, or compiler-owned reparser is permitted.

A prior implementation note incorrectly made this internal direction contingent
on user approval. [Neutral contract review](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-alias-controls.json)
confirmed it follows from spec09, this task's preservation requirements and the
adopted syntax handoff design. No approval was inferred from a continuation;
the unnecessary confirmation request is withdrawn. The concrete representation
still requires design and meaningful producer/consumer tests. Consult the user
only if meaning remains undecidable under existing rules, or a proposed solution
changes the surface/precedence/parenthesis requirement. Qualified namespace vs
trait/projection interpretation follows the same existing ownership boundary.

## Type-position increment (in progress)

Shared Syntax ae70dd4ef7ee67aa12d9449f909a356cb0c84989 / 0.1.11-dev.31
retains rich view-source rows separately from associated projections, including
arguments, labels and original spans through direct parsing/materialize/freeze.
[Producer increment](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-syntax-increment.json)
records 15 golden fixtures / 34 distinct reconciled cases and neutral review.
This is not package-wide or task-wide completion. Exact manifest and lock uptake
uses the normal resolver, without a local override.

[Executed Lower RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-lowering-red.json)
uses actual Frontend analysis plus an AST adapter control. Annotation, AST,
nested and multiple arguments lose the complete selector. Missing/extra/named
arguments and extension arguments are accepted. Plain and projection controls
pass. Unknown source is already rejected; retain its existing message rather
than treating wording alone as an acceptance defect. Its missing Source
classification remains an actual failure of the new domain assertion. The new never-green test's
expectation was corrected accordingly.

Current repair passes the rich rows to a shared finalizer, keeps legacy mirrors
as fallback only, and preserves rows through type-path/projection normalization.
Known-owner arity and positional-only checks do not establish conformance.
Standard build and focused native verification succeeded; see the finite increment below. Value
bracket handoff, qualified selector production, impl known-owner arity admission,
alias/module controls and task-wide completion remain open.

Neutral incremental review found legacy viewNames/extView bypassed the shared
finalizer. Added two compatibility AST cases; both executed RED after the first
build. All four rich retention cases and plain/projection controls passed.
The invalid forms now reject, but their Unclassified domain failed the new
Source assertions. The second repair routes both carriers' compatibility fields
through the same finalizer and marks authored rejection producers as Source.
Second standard build: 20261107T093420-build-5cbd97 succeeded. No blanket
adapter conversion and no conformance-evidence admission change.


[Type Lower increment verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-lowering-increment.json):
13 new cases and 43 existing consumer/matching/projection controls pass through
fresh compile/link/native, exact goldens and empty runtime stderr. Both input
inventories remain unchanged and match current files. The standard build passed.
Neutral review confirmed the compatibility fix and producer-only classification;
final review independently reran all 56 saved native cases and verified all
187/191 recorded input hashes against current files. No additional required fix
was found for this finite increment. This finite increment does not close
the whole task or certify a full suite/performance gate. The remaining boundaries
listed above stay open.


## Known-owner impl arity increment (in progress)

This existing task requirement is independent of the still-open value-bracket
implementation. [Executed RED and scope](../../../evidence/rejection-domains/diagnostic-domain-implementation/impl-trait-arity-increment.json):
valid one-argument and zero-argument conformances pass; missing/extra arguments
incorrectly diagnose an unknown trait. Unknown trait is already rejected, not an
acceptance defect. New AST/spanless controls additionally exercise the adapter.

Resolve the lexical owner before strict positional arity admission. Reuse the
trait instance arity check and carry the resulting canonical head to method
provenance, associated bindings and conformance registration instead of resolving
it again at each consumer. Remove raw-name fallback after a failed resolution.
Standard build 20261107T094608-build-12b01f succeeded. Neutral review found
a new-test positive Err loophole (corrected), and an existing open-owner helper
that did not follow reexports. The17-case native run confirmed14 successes and
3 barrel/alias/missing-through-barrel failures; the previous CLI accepts the
valid File graphs. Both open-helper import/reexport branches now use the existing
recursive surface resolver. Source follow-up found no additional required fix.
Second standard build 20261107T095229-build-77741a passed. All17 native cases
(source, AST/spanless, direct/barrel/alias and hidden-name controls),13 type-view
cases and5 existing generic/trait controls pass with unchanged recorded inputs.
Independent final review reran all35 native cases and checked194/197 input
hashes and6 preservation fixture goldens against current files; no additional
required fix for this finite increment. The full task remains open.


## Type alias preservation and qualified-path investigation

[Actual File alias controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-alias-controls.json)
pass direct import, barrel and alias type views, retaining canonical owner,
I64 argument and exact written selector coordinates. All17 executions (including
the13 existing cases and no-argument golden default) pass with197 recorded
inputs unchanged. Neutral review independently reran the cases and checked hashes.
These are preserved GREEN contracts, not a new product repair or task closure.

Namespace-qualified impl setup succeeds, but `S#Types.P[I64]`,
`S#Types.P[I64].Item` and `S#Types.Zero` fail with projection-arity diagnostics.
The parser currently converts the first dot after# into projection fields
before namespace resolution. Do not patch this by spelling guesses or a Lower
parser. The shared-path handoff must preserve segments until their ordinary
binding owner can distinguish namespace, trait and associated projection.
The scope remains in this existing task. Neutral review confirmed unresolved retention follows from the adopted
single-grammar/handoff contract; the earlier unnecessary user-confirmation
request is withdrawn. Concrete representation design is the next step.

## Next implementation unit: name-dependent source applications

**Consumer-stage point4 is provisional and must not be implemented as written.**
The source-kind collision review below found a concrete counterexample to its
lexical-only assumption. Producer retention remains independently valid; record
the necessary surface rule and corrected stage owner before consumer changes.

This is an internal encoding plan under the Grammar Handoff Contract, not a
change to the accepted source language. Review its concrete boundaries before
editing product code.

1. A shared source-selection syntax row retains receiver, complete dotted name
   segments, written spans, strip mode and an optional bracket application on
   the final segment. The parser can stop before an ordinary method-call suffix
   and preserve following postfix operations. The source path ends after its
   first bracket packet or before a `.name(` call suffix. Thus
   `value#Ns.P[T].field[index]` retains `Ns.P` plus `[T]`, then ordinary
   postfix syntax; `value#Ext.field[index]` retains `Ext.field` plus the packet
   until binding identifies `Ext`. Never move a field-attached packet to an
   earlier parameterized trait to repair a missing application. It does not bind namespaces,
   traits or value fields. Parentheses end this source-path construction scope;
   `(value#P)[index]` remains an ordinary index over the parenthesized view.
2. The bracket packet retains independently parsed type-list and index-expression
   alternatives plus each alternative's syntax-error receipt. Parsing uses the
   existing shared type/expression grammar, not a new parser or a later reparse.
   Append-only arena checkpoints roll back a failed alternative by pool length;
   checkpoint every mutable pool length and parser position/error state, not
   only expression rows. Preserve a successful first alternative before taking
   the second checkpoint, so rollback cannot invalidate its children. Existing
   pool prefixes remain unchanged. Do not copy the entire SyntaxFile or publish
   malformed speculative children.
   Successful alternatives refer to owned typed pools and retain original spans.
   Verify the successful branches consume the same bracket boundary; do not
   choose a new semantic priority if that invariant fails.
3. Materialization/freeze preserve every packet status, child, label and error
   location. A syntax error in an unselected alternative must not invalidate a
   valid interpretation. A selected invalid alternative remains a Source error;
   no semantic fallback to the other alternative is permitted. Existing legacy
   ExtView/ExtMethod AST payloads cannot carry these alternatives: add a rich
   carrier and converge direct and materialized input on the same classifier.
4. Lower resolves namespace prefixes and the source head once, retaining the
   binding result (canonical owner, kind, arity and provenance). Do not pass
   only its spelling to a second bare-name resolver. Only the selected branch
   is lowered; success of the other parser branch never proves source kind. A parameterized
   trait consumes the attached complete type application at that head. A
   zero-arity trait or extension completes the view without consuming the packet
   as type arguments; the packet is then an ordinary index. Dotted suffixes after
   a resolved source are ordinary member operations. Publish only the established
   canonical view / field / index / call operations; no unresolved choice escapes
   to Record, Verify, Mono, Mid or LLVM.
5. Type-position qualified source paths preserve the same name segments but have
   unambiguous type-argument syntax. Namespace/source/projection splitting uses
   the same lexical owner boundary and existing projection formation. Keep
   semantic view arguments and associated projection arguments distinct.

Start with actual Frontend File regressions for a complete value trait view and
preserved extension / zero-arity-trait / parenthesized indexing, with a plain
receiver control. Add producer packet/range/error tests through direct parse,
materialize and freeze, including nested applications, multiple arguments,
selected invalid syntax, later indexing, method suffixes and malformed brackets.
Then close namespace-qualified value/type paths, missing/extra arguments,
aliases/reexports, two instances and exact written coordinates. Update the exact
Syntax pin only after its producer increment passes neutral review. Focused gates
precede task-wide normal/fixed-point/performance acceptance. This plan does not
claim those remaining tests or implementation are complete.

### Concrete Producer Encoding

Use one new SourceSelection expression tag, retaining its receiver in child0,
qualified segments in the existing typePath name-segment range, strip in flag0,
source-only span in text and whole expression span in span. Add a typed optional
SourceApplicationId field (raw0 absent; allocated packet ids are pool index +1)
to SyntaxExpr and one private sourceApplications pool. A packet contains its
original bracket span and two closed alternatives: parsed type-id/label ranges
or a type-parse error receipt; parsed index ExprId or an index-parse error
receipt. No alternative stores a value AST in SyntaxFile.

The public value AST adds SourceSelection and corresponding application/type/
index alternatives using owned arrays/ExprAst only at that explicit boundary.
Materialization and freeze retain both branch outcomes and original coordinates;
freeze allocates packet identity after recursive children. Existing ExtView and
ExtMethod value constructors remain compatibility inputs to the same later
semantic classifier, not a second spelling-based resolver.

Each speculative branch has a fresh P cursor sharing immutable bytes/tokens,
starting at the packet's '['. Original P errors remain outside speculation.
A private arena checkpoint contains every private pool length, including the
packet pool. Roll back failed branches without touching old row prefixes;
checkpoint branch B only after retaining branch A. Success must consume the
closing bracket. If both succeed their end positions must agree. If only one
succeeds it establishes the syntactic bracket extent, not semantic source kind.
If neither succeeds, publish no malformed child and report the syntax error;
there is no valid interpretation for binding to select. A selected failed branch
with another syntactically successful branch remains a later Source diagnostic.

The shared Hash parser gathers dotted identifiers only up to the first packet
or before `.name(`. Following operations stay in the ordinary postfix loop;
parentheses naturally terminate that collection invocation. The producer has
no namespace/trait/extension registry and makes no semantic choice. Lower later
requests the lookup-owned lexical binding result instead of owning a second
name-resolution algorithm. Qualified type/projection splitting and the concrete
extension-header binding authority still need consumer implementation; do not
claim the producer closes those semantic contracts.

### Producer Verification and Consumer Boundary

[Finite producer verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/value-view-syntax-producer-increment.json)
records initial executed RED (six failures/four controls), source application
rows, isolated grammar branches, complete pool checkpoints and value adapters.
Seventeen fixtures / 88 distinct cases pass; the latest 54 include exact
receiver/arguments/path/coordinates/error receipts and direct/materialize/freeze
assertions, recursive packet freeze and prefix retention. Neutral review reran
both focused sets, checked current hashes and accepted the finite producer after
four assertion gaps were fixed. All47 pool checkpoint fields/creation/rollback
were structurally reconciled; this is not a claim every pool was dynamically
exercised. Source files are unchanged across the successful focused runs.
Compiler pin/Lower/Record uptake, qualified type paths and task-wide gates remain
open. The producer deliberately selects neither semantic interpretation.

### Adopted Module Binding Rule and Consumer Plan

The user adopted one module binding namespace across types, traits, named
extensions, free functions, globals and use aliases/namespaces. Only admitted
free-function overloads share a name. See [module binding admission](../design/name-lookup.md#shared-module-binding-admission)
and the [normative collision rule](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md#同一スコープの名前衝突).
This removes the prior source-kind specification stop; it does not certify the
current implementation or the complete task.

[The preserved investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/source-kind-binding-boundary.json)
records the old intentional same-name trait/extension behavior and the value/type
arity discrepancy. The existing `run/view_source_kind_collision` positive
expectation is superseded by the adopted specification, not evidence to retain
an applicability-based source-kind selector. Update affected tests under the
changed-spec allowance while preserving non-collision view/index controls.

Before publishing an admitted module binding, reject cross-kind collisions in
local, imported, aliased and re-published bindings, including unused declarations.
Preserve valid free overloads, original-identity deduplication, separate-module
namespaces, owner-scoped members and ordinary lexical shadowing. Registration
and public-surface construction must share the binding-conflict decision rather
than copying per-kind predicates. Confirm actual implementation ownership before
splitting any cross-cutting repair; do not silently count it as already done.

The consumer requests the unique lexical declaration identity/kind, then selects
the retained syntax role and validates complete arity and receiver applicability
with the existing semantic owners. Neither syntax-branch success nor receiver
applicability chooses between colliding names. No receiver type checker is moved
into Lower, and no failed interpretation falls back to another meaning.

The producer remains Syntax `2b5811c` without a package tag; compiler dependency
remains exact dev31/ae70. Pin/consumer uptake, qualified type paths, source
admission and final-use gates remain open. Do not close com-9hde or claim
implementation GREEN from this documentation change.

Documentation-only independent review (`module_binding_docs_review`) checked
these spec/design changes and worklog handoff: no required repairs; the shared
binding authority, unchanged overload/shadowing rules and resolved-extension
fragment distinction are consistent. New local files/section anchors and saved
evidence links resolve. An optional extra explanation that equal spelling alone
is not extension identity was not duplicated: the general distinct-declaration
rule and resolved-identity condition already establish it. Diff whitespace and
new section/link checks pass. No product tests or performance measurement were
run for this documentation-only increment; implementation acceptance is open.

### Module Binding Producer Scenarios

Inspection before consumer uptake found that both shared parsers flatten an
extension into tagged impl items and lose an empty declaration entirely.
Preserve a distinct extension declaration item (name and original full/name
spans), independent from its existing impl items. No source rescan is allowed.
The finite producer guarantee covers empty/populated/multiple/same-spelled
extension declarations, top-level source order, direct/materialize/freeze,
nonzero source bases and appended-file prefix retention. Distinct parsed
occurrences remain distinct; semantic admission owns bundle identity.
Check existing top-item consumers for any assumed first-impl/count layout.
This is required input preservation, not module collision admission or task
completion. After this producer boundary, registration and use/public-surface
bindings must reach one admission authority before lexical kind consumers.

[Extension declaration producer verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/extension-declaration-producer.json)
is saved as Syntax `3e328b2` (signed and pushed, no release tag/pin uptake).
The executed two-case RED loses empty/populated declaration roots after a
successful compile/link. The final 15 executions inspect direct rows, macro AST
values without freezing, and a distinct freeze roundtrip. Seventeen preserved
Syntax fixtures / 88 cases pass with unchanged inputs. All 48 pool checkpoint
fields/captures/rollbacks reconcile structurally. Independent review reran all
15 final native cases and reconciled controls/current hashes; no required
repairs remain after fixing an obsolete comment and duplicated adapter modes.
The declaration marker preserves empty bundles, original name/full spans,
source order and tagged impl data; it does not itself admit any module binding.
Next: consume these declaration roots in common module binding admission and
connect the neutral source-application consumer. The exact compiler Syntax pin,
package-wide gates, collision rejection and com-9hde completion remain open.

### Shared Module Binding Admission (in progress)

Source-boundary RED now covers unused trait/extension (including empty),
type/function, function/global and type/trait declarations, imported type versus
local trait and namespace versus global. The old candidate accepts these
invalid programs. Different imported kinds and conflicting re-exports already
reject but lack the new shared Source-classified admission; distinguish those
classification/path controls from new acceptance RED. Valid overloads, separate
lexical/member scopes, two paths to one declaration, imported overload unions
and extension fragments are preserved controls. The first SeparateScopes input
incorrectly used a normally completing value block without give; corrected as
a never-green test, not counted as product RED.

Implement a source declaration/use graph independent of Comp/receiver/type
checking: preserve original identity through aliases/re-exports, validate all
module binding groups before lowering and retain an admitted read-only result.
Function-set admission remains the existing callable authority; it is not
replaced by this kind/identity merge. Remove the old struct/enum-only and
import/import-only collision decisions after the common authority is connected.
The temporary Syntax path override is WIP-only and must never be committed;
restore an exact released pin before increment closure.

### Integration Review and Publication Decision Stop

The first common-admission candidate rejects the seven newly accepted-invalid
source scenarios; the existing import/re-export rejection reasons are also
routed through the shared diagnostic in the initial CLI controls. Standard
builds `20261107T123207-build-c059bb` and
`20261107T123815-build-bcf801` passed with the temporary local Syntax override.
The latter uses a distinct admitted reader type; neither build proves the
current uncommitted follow-up source or a fixed point/performance gate.

Neutral integration review (`shared_module_binding_integration_review`) found:
(1) downstream trait-kind reselection through same-named extension applicability;
(2) extension owner module discarded before query; (3) legacy AST classifiers
not converged; (4) builder registration failure not latched before finish;
(5) first collision location discarded by the diagnostic adapter. These are
required, not optional. The pending source-selection/mapping checks and
private/public overload, namespace/alias, extern, packet/no-fallback and
interpolation controls remain open. Item4 has an executed unit RED/GREEN in the
saved evidence; item5 and source-selection closure are not claimed fixed.

A concrete cross-module alias probe could not yet test findings1/2: it is
rejected at extension-name import/publication, before source selection. Do not
call that rejection a source-owner RED. This recovers the existing unresolved
[met-bejv](met-bejv.md) publication/identity premise: spec15 requires an explicit
binding for #Ext and mentions published extensions, but does not spell out how
an extension declaration is made public; the grammar has no pub extension.
Inferring declaration publication from pub impl was a provisional WIP
assumption, not an adopted rule, and has been removed. The current collector
keeps unmodified extension declarations private rather than inventing that rule.

The user confirmed publication composition on 2026-11-08: explicit
`pub extension Name`, module-private unmodified extension declarations, and
independent impl visibility. A non-public extension may contain `pub impl`;
that neither publishes its name nor authorizes external access. No new warning
is part of this decision. [com-scq5](com-scq5.md) owns specification/design
clarification and is a real prerequisite of this task.

After that contract is synchronized, this task owns the product handoff:
accept the public extension declaration in shared Syntax and every supported
AST adapter, retain declaration publication independently of impl publication,
and consume it in admitted module/public-surface bindings. Remove any inferred
publication from members; do not add an extension-specific private-owner
rejection. Cover all four extension/impl visibility combinations, local access,
external public-member success/private-member rejection, selective/namespace/
alias/re-publication routes and package-root reachability, with intended reasons
and valid positive setups. Preserve empty declaration markers and exact package
pin uptake. Existing owner/kind/legacy-path review repairs remain mandatory;
this publication increment does not certify them. Test-purpose reconciliation
for the three existing fixtures remains met-bejv, which depends on this task
rather than blocking it in return. Do not weaken import existence checking to
make an owner probe run.

The local Syntax override has been restored to exact dev31/ae70 before WIP
commit. Current WIP source imports new Syntax APIs from revision3e328b2 and is
therefore not buildable with that old exact pin. Resume locally by reapplying
`{ path = "../syntax" }` only while finishing the paired consumer; release/pin
uptake and gates remain required before completion. No unsupported source is
promoted to main/seed/adopted carrier. WIP candidates
`bin/plewc-module-bindings-first` and `bin/plewc-module-bindings-sealed-first`
are evidence from their saved build inputs, not the latest source or accepted
publication policy. The tracked bin/plewc remains a generated WIP artifact.

[WIP evidence and review disposition](../../../evidence/rejection-domains/diagnostic-domain-implementation/module-binding-admission-wip.json)
preserves builds, focused acceptance observations, exact API RED/GREEN,
source-owner probe text and the required review findings/limits. The baseline
acceptance runners omitted compiler/src and fixture hash maps; tracked source
was76ea32e6 without in-flight edits, but this is not formal input/gate evidence.
The publication-blocked owner probes are scratch diagnostics, not normative test
fixtures. R4 final review checks declaration/import construction failures and
subsequent finish/declaration/import calls all retain the initial Collision and
both offsets. Other review requirements and implementation remain open; the adopted publication decision is recorded above.

## Extension Publication Increment

Specification b31ccfa and design45a46bc3 close com-scq5. Syntax5174ace adds
Published around the declaration marker only, independently of impl flags.
[Producer evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/extension-publication-producer.json): actual private/public RED contrasts, final18 and existing19fixture/121 control cases, independently reexecuted.

This consumer increment preserves the declaration flag in the admitted module
surface, removes import rechecking against a separate lowered export scan, and
checks authored qualified names against the same admitted public table. Explicit
synthesized qualified origins retain their defining-module authority. Published
extension names also reach the existing exports consumers through their original
name/module provenance, in both direct and value-AST adapters.
[Consumer evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/extension-publication-binding.json): two successive RED boundaries, native16 including direct exports/provenance and synthetic interpolation assertions,
fresh CLI8 including qualified/barrel-alias actual calls and private rejection,
standard build20261107T165331-build-1b06a1 passed with unchanged inputs. Neutral
review independently reexecuted native16 and CLI8, matched current220/216 input
hashes, and accepted only this finite publication consumer increment.

Exact Syntax tag/pin uptake remains pending. Automatic approval review rejected
publishing proposed tag0.1.11-dev.32 at5174ace because shared version publication
exceeds ordinary branch push while consumer/full gates remain unfinished; explicit
user approval was requested. Do not retry or publish through another route
without that approval. A local path override is still WIP-only, excluded from
commits; the other required kind/owner/legacy/diagnostic repairs remain open.

## Canonical Extension Identity Repair Plan

[Executed owner/kind controls and neutral plan review](../../../evidence/rejection-domains/diagnostic-domain-implementation/view-source-owner-increment.json)
now use valid published declarations: each source alone succeeds; combining
same-spelled trait/extension misrejects, and separately owned extension bundles
collide at declaration admission. R1 now excludes extension applicability when
a retained trait owner already fixes the kind; the native case becomes GREEN,
while the separate-owner case deliberately remains RED. No whole-task approval.

For R2, use a canonical bundle ID issued once from the merged admitted binding
(owner module plus original name); aliases, re-publication and same-owner
fragments preserve it. The merged original declaration offset+1 is an admissible
session-local representation, not a stable ABI. Migrate Func/Conform/view/callable
and cycle/proof activation together; resolve names for display from the sealed
ID metadata. Replace interner bounds/name-based existence and applicability,
connect type and legacy producers to the same binding authority, and remove
unused competing spelling-based view validators. Kind-erased compatibility IDs
must not let a trait source activate an unrelated extension with an equal numeric
ID. Retain empty declaration existence independently of receiver applicability.
This is existing R2/R3 scope, not a call-site-only module filter workaround.


## Canonical Identity WIP Verification

[Finite migration evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/canonical-extension-identity-increment.json)
records the canonical binding identity across impl/view/callable and cycle/proof
activation. Owner/kind native4 pass. A direct value/associated final-resolver
probe executes RED0→GREEN1 after removing the display-span roundtrip; a legacy
AST Conform probe executes RED0→GREEN1 after replacing spelling interning with
the same extension-only binding query. Both have successful compile/link/runtime
and unchanged per-run inputs; setup failures are excluded. Neutral followup
review verified the two missed paths are repaired and accepted those finite
contrasts. These are not full conformance dispatch or task completion evidence.

Before closing R2/R3, reconcile existing internal setup for canonical IDs in
TraitCycleCanonicalIdentity, TraitCyclePatternInputs and SemanticTraitViewConsumers;
preserve their original comparison/cycle/domain assertions, and replace the
newly invalid same-module trait/extension name collision with a valid independent
kind contrast. LoweredTraitViewSources keeps its unknown-name Source assertion
at the new shared admission diagnostic. Do not rewrite opaque numeric IDs in
pure structural comparison tests merely because semantic source IDs changed.
Expanded fragment/reexport/conformance-only/numeric-collision controls, fresh
compiler execution, exact Syntax pin and whole-task gates remain required.

## Collision Diagnostic Origins (R5)

[Returning and rendered collision context](../../../evidence/rejection-domains/diagnostic-domain-implementation/module-binding-collision-diagnostics.json)
records an actual successful-executable RED for the missing first location and
GREEN after retaining structured notes. Declaration/declaration, import/import
and import/declaration cases inspect Source classification, both file-local
locations and the exact supplementary message. A leaf renderer control covers
primary/context location variants, notes absence, warnings and domain independence.
The primary and note follow admission registration order; no source ordering or
semantic collision decision is changed. A neutral reviewer independently reran
all four final native cases and checked the whole diagnostic transport path;
no mandatory repair remains in this finite R5 scope.

The first standard build completed compilation/linking but its formal gate was
invalidated by an in-flight edit to tests/compiler/frontend/README.md only.
It must not be reported as a passed immutable-input gate. The resulting candidate
`bin/plewc-collision-diagnostic-notes` rejects the three actual CLI inputs with
both origins. The replacement standard build `20261107T175415-build-d1ceef` passed with all
inputs unchanged. Formal self-host `20261107T175932-self-host-7a0e4f` reached
generation3 LLVM/runtime equality and all3 samples produced identical outputs:
7.252218 / 6.729189 / 6.731090 seconds, median6.731090 (<7).
The saved fixed-point candidate `bin/plewc-source-binding-fixed-point` repeats
the owner/kind check/run8 and collision CLI3 controls. This is WIP evidence,
not full-suite acceptance, exact Syntax pin uptake, or adopted-carrier promotion.


## Remaining Legacy Adapter Controls

Before claiming R3 closure, exercise ImplAst.extName with and without its optional
name span at an explicit original impl site. Both forms must obtain the same
admitted bundle identity; neither may derive module authority from newly interned
text. Pair valid extension input with known trait/non-extension and unknown name
refusals, preserving the intended failure domain and preventing conformance
publication on failure. This is compatibility adapter coverage under the existing
scope, not new source syntax or global spelling inference. The representation's
required impl span supplies lexical provenance when the optional name span is
absent. Retain canonical ID checks for successful conformance registration.

## Legacy Adapter and Conformance-only Verification

[Finite evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/legacy-extension-adapter-closure.json)
records actual spanless compatibility RED and final12 successful legacy controls.
The optional name span and required original impl site converge through the same
sealed binding/kind query. Both Func and Conform retain canonical IDs and original
definition offsets; foreign-module controls exclude interner-position authority.
The unused competing alias spelling resolver is removed.

A conformance-only extension control checks two owners without extension methods,
registered Conform provenance, individual/composed views and exact proof-source
activation membership. Native1 and previous-candidate CLI check/run2 succeed; this
does not certify the full solver or final dispatch. Existing ArrayViewAdmission
keeps its nine scenarios and ref0 compatibility path, correcting only its obsolete
nameId setup to the sealed ID. Neutral review accepted all three finite scopes.
Source compatibility check succeeds; no fresh full build/performance is claimed
for this adapter repair. Parameterized value source-application consumer controls,
exact Syntax pin and whole-task gates remain open.
