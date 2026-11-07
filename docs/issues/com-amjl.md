---
id: com-amjl
status: in_progress
deps: [com-x95z, com-zdod]
links: [com-oir7, com-8egj, met-c1pg, com-16j0, com-0w38, com-wka4, com-9hde]
created: 2026-11-06T09:51:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Establish trait-view evidence before admitting associated projections

Validate authored trait-view applicability under the exact lexical receiver and trait instance before source declaration success; preserve evidence through associated projection and final consumption. Repair the two com-x95z success setups without weakening their original graph/equality coverage.

## Contract and Confirmed Defect

[Spec09](../../../spec/spec/02-type-system/09-extensions.md#拡張ビューと-トレイトビューの非対称混同しやすい)
requires an existing conformance before forming a trait view: `#P` selects a
source and never creates conformance. This applies to type and value views.
[Spec08](../../../spec/spec/02-type-system/08-traits.md) makes
`T#P[Args].Item` an exact source/instance selection; `T.Item` is a shorthand only
when the lexical bounds uniquely determine that complete instance and member.
The declaration's own bounds, inherited premises or other specification-valid
evidence can justify a symbolic receiver; concrete resolution is not required.
Follow [Types and Evidence](../design/types-and-evidence.md#4-substitution-and-projection),
[source handoffs](../design/frontend-handoffs.md) and
[name lookup](../design/name-lookup.md). No new language rule is adopted.

[Investigation](../../../evidence/rejection-domains/projection-admission-investigation/README.md)
and [executed controls](../../../evidence/rejection-domains/projection-admission-investigation/cause-controls.json)
record current ordinary generic signature acceptance with no bound, unrelated
`T: Q`, and `T: P[I64]` for a requested `T#P[String].Item`. All pass the fixed
candidate. Correctly bounded input also passes; missing-member, unknown-trait
and concrete-no-conformance controls reject. The demonstrated cause is missing
generic justification, not a demonstrated unrelated-evidence leak.
Standalone `T#P` behavior and other entry paths require execution before claims.

`resolveAssocProjection` preserves ParamId receivers without querying evidence;
`checkProjectionMember` checks member existence but not receiver conformance.
Both responsibilities are individually useful, but neither establishes source
view validity. Deferral of concrete evaluation must not mean deferred proof
that a declaration is legal. Fix the common view-formation responsibility,
not an Item-specific missing-bound check or removal of symbolic deferral.

## Finite Repair and Final Consumer

Trace authored type/view construction -> lexical declaration environment ->
exact trait-view admission -> successful source publication -> associated term
and retained proof -> generic substitution/concrete output or dynamic consumer.
Include unused signatures, body annotations and value views on the supported
surface, and applicable check/build/lazy-run/gen declaration paths. Record actual
callers and applicability rather than asserting all modes share an entry.

- Establish receiver + canonical trait owner + full positional arguments under
  the originating ParamId/bound environment. Reuse the common conformance/source
  selection query; do not invent a second view-only solver or use an existence
  query as unique source admission. Preserve inherited and selected-extension
  evidence and existing ambiguity rules.
- Preserve established justification until projection/final use. Symbolic
  validity and concrete normalization remain separate. Do not recover proof from
  an unrelated ambient cursor, same-spelled binder or another trait instance.
  Retained facts/cache identity must include the necessary environment and
  source selection; remove competing unchecked source-success paths.
- A missing premise on valid authored input is a source diagnostic at the view
  selection, before member/output use; malformed raw input remains a typed
  non-Source failure under the shared input contract. Never tag arbitrary
  unresolved requests Source merely to satisfy a rejection consumer.
- Keep projection member existence, exact positional arity and short-form
  uniqueness checks. No implicit bounds, concrete witness lookup for every
  abstract declaration, or expectation inferred from current compiler success.

## Existing Test Corrections Authorized by the User

Preserve the introducing purposes documented by com-x95z:

- `tests/fixtures/run/trait_subject_cycle_parameterized_projection_distinct_allowed.pw`:
  distinct trait-instance projection arguments must not manufacture a cycle.
  Correct the whole-source success setup; if a valid source setup cannot express
  that structural case, retain it at the proper internal graph boundary and
  provide a valid source companion. Do not silently discard the comparison.
- `tests/fixtures/run/inherited_projection_identity.pw`: preserve inherited
  diamond equalities, foreign receiver distinction, symbolic missing-query
  behavior, Conflict versus known Unit term0, and no body discovery. Separate
  the internal unavailable Parent[String] query from successful admission of
  an embedded signature requiring that unavailable premise.

No conditional trait-to-trait `where` workaround is authorized (spec08,
com-wfq2). The two projection growth/binder rejection oracles remain owned by
the structural graph boundary and must not become unrelated missing-bound tests.
If stronger source admission changes their setup, preserve their exact graph
assertions and independently validate source diagnostics/order.

## Scenarios and Completion

Begin with meaningful REDs and valid GREEN controls from the saved candidate:
standalone `T#P` and projected `T#P.Item`; no bound, unrelated bound and wrong
trait instance; correct direct/inherited bound; same-spelled foreign binder or
unrelated declaration; unknown owner/member and arity; ambiguous/unique short
projection; supported selected-extension and nested type contexts; unused
signature and actual instantiated use. Test distinct semantic boundaries, not
all Cartesian combinations. Existing passing cases are controls, not defect REDs.

Complete only after source construction through final use is closed, retained
facts and alternate entry paths are structurally checked, corrected fixtures
retain meaningful assertions, and fresh targeted execution plus independent
neutral review accept the guarantees. Coordinate Source diagnostics with
com-yeua/com-fsuq without treating their whole tasks as prerequisites.
Final fixed-point/performance/full-suite gates remain G2a/G2b under met-si6j.

## Dependencies and Exclusions

com-x95z supplies the finite contract/oracle investigation and owned follow-ups,
not this product's GREEN. met-ia09 and met-6e6k must admit this repair before
closing their affected evidence/final-consumer boundaries; com-604k retains it
at integration. met-c1pg remains a separate raw graph-admission repair and does
not wait for this entire product repair: structural cycle checking does not
solve receiver applicability/where satisfiability before comparing terms.

com-oir7 owns view-check API authority narrowing. Closed investigations
com-16j0/com-8egj retain the projection/grounding input maps and their assigned
product repair owners; they did not complete those product repairs. Consult
their outcome sections and share this corrected semantic contract with the
actual affected repair owners, without duplicating their entire repairs or
adding unrelated full-task prerequisites. This task does not certify those APIs
already satisfy design.

Those existing product owners are com-p5q2/com-4vvt/com-be0m/com-4oor/com-hnm8
(com-16j0 outcome), and com-d4m2/com-9nbx/com-nei5 (com-8egj outcome). At
implementation, record which changed API is responsible for semantic evidence
admission here versus authority narrowing there; a shared API name alone is not
a new whole-task dependency or authorization to duplicate its implementation.

Excluded: new projection syntax or meaning, implicit conformance, conditional
trait-to-trait support, general solver/SCC redesign, unrelated API narrowing,
new unique/opening features, main/seed promotion, and claiming scope-wide
completion from helper comparisons alone.


## Complete-Instance View Coordination

The approved type/value view rule and executed state investigation are assigned
to com-zdod (shared complete selector terms), com-9hde (Syntax/Lower) and
com-4k31 (final call selection). This repair depends on com-zdod's term contract
and retains common exact receiver/instance source-proof admission, including
its original projection controls and authorized test corrections. com-4k31
consumes that shared proof instead of implementing another solver. No dependency
on com-4k31 or whole Syntax migration is introduced here; coordinate the shared
API with its actual producer/consumer without duplicating their task bodies.

## Complete View Reader Handoff

com-zdod's neutral completion review identifies proofSourceIsActive
(src/Codegen/Mono/Resolve.pw) as still reading only viewIds/viewExtId. Its
source-proof callers must consume retained complete sources, distinguish
extension kind from same-spelled trait selectors, and preserve the selected
instance/evidence. This is a finite investigation item within the existing
view/projection proof repair, not a reproduced source-level wrong witness or
new inference rule. Structural runtime erasure and existential equality are
repaired/tested in com-zdod; those do not certify this proof activation.

## Array Receiver Admission Increment

The com-9hde preservation probes expose an existing common source-query defect,
not an ambiguity of bracket parsing. Array TypeInfo intentionally carries an
I64 element-name adapter together with a complete Array[I64] term. The authored
value-view checker passes both to resolveViewSourceKey; its conformance filter
and extAppliesToType's extension filter compare the element-name head before
matching the structured receiver. A parenthesized extension view fails too.

[Executed diagnosis](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-investigation.json)
retains noninstrumented rejection, successful plain indexing, scratch-only output
at the actual query boundary, and a canonical-head counterfactual. Neutral review
assigns this repair to this existing common receiver/source-admission scope;
com-79k3 remains responsible for API authority narrowing, not these algorithms.
No new whole-task dependency or language rule is introduced.

Finite guarantee: when the query has a complete receiver term, candidate head
filtering and structured matching consume that same receiver. Legacy name input
is only an adapter fallback when no term is available. This is not an Array
exception, a proof of selected-instance arguments, or completion of this task.
Cover extension, parenthesized extension, zero-argument trait and view-free array
indexing, nominal receiver preservation, and rejection of a mismatched extension
or missing trait conformance. Remove the competing element-head interpretation
from both common source-query filters; do not merely patch one verifier call.
Run fresh focused native tests and shared source-query controls, inspect the
actual consumers, and obtain neutral review of this increment before returning
to com-9hde's parser work. Task-wide retained evidence/projection/final-consumer
requirements remain open.

[Finite repair verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-repair.json):
standard build `20261107T104002-build-ff7b35` passed. The common read-only arena
projection supplies the complete term's head to both filters, with a ref0-only
legacy fallback. Nine Frontend scenarios plus an actual ref0 source-query
control pass with exact golden/empty stderr. Seven old/new native programs match
goldens and three rejection controls retain their diagnostics. An additional
old-candidate RED accepts `Array[Meter]#E` for an I64 extension; the fresh candidate
rejects it, while Meter's own inherited extension remains valid. Neutral review
independently reran the final native probe and reconciled all 198 target/210
control input hashes without mismatch; no additional finite required repair.

The existing newtype-underlying extension recursion still omits the underlying
full term ref. This increment does not establish generic newtype inheritance or
repair that erasure. Full exact-instance evidence, retained source facts,
projection/final-consumer work and task-wide gates remain open; do not close this
task or infer that parser preservation alone supplies these guarantees.

## Short-form Instance Controls from Source-path Preservation

The existing complete-bound-instance requirement has concrete manual controls:
MaterializedTypePathControls mode shorthand preserves accepted short-form
admission/name/ParamId receiver only; shorthandInstance requires canonical trait
owner plus the bound I64 argument and currently prints0 against golden1. A
focused raw-shape diagnostic found the written bound span rather than canonical
declaration owner and an empty positional-argument list; this is not proof of a valid
complete instance. Preserve this RED when closing this task rather than counting
short-form acceptance as full evidence retention.

The unchanged old candidate487138f4 also rejects
fixtures/ImplTraitInstances/QualifiedShorthandInstance.pw (`where T: Types.P[I64]`)
with no unique short source, while accepting BareShorthandInstance.pw
(`where T: P[I64]`). Both belong to this task's lexical complete-instance and
short-form uniqueness contract. The com-9hde qualified explicit-path repair
does not certify or replace them. Original results live under the saved
qualified-type repair evidence; no new specification or task scope is adopted.
