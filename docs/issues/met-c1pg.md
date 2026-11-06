---
id: met-c1pg
status: in_progress
deps: [com-x95z]
links: [com-xh2h, com-amjl, com-bvc8]
created: 2026-11-06T07:58:54Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, diagnostics, verification]
---
# Validate trait-cycle inputs and prevent unresolved identity matches

Repair the confirmed trait-cycle request admission and unresolved-identity defects before assigning Source to cycle/growth refusals. Preserve the current language rules and distinguish malformed internal inputs from actual source cycles.


## Contract and Evidence

Follow [Types and Evidence](../design/types-and-evidence.md),
[Diagnostics](../design/diagnostics.md#input-failures-and-internal-invariants),
and spec09's trait-to-trait structural cycle rules. The executable raw probe,
fixed candidate and neutral review are retained in
[trait-cycle-admission-blocker.json](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-admission-blocker.json).
Current source baseline is 3f66f7dc; the fixed observed carrier is
bin/plewc-visibility-failure-domains (exact hash in evidence).

Two coupled defects are covered, not merely diagnostic wording:

1. Input admission: registered raw conformance rows are not proof that their
   trait owners, argument ranges/arity, binders and symbolic terms are valid.
   A missing owner can become canonical sentinel0 and pass 0==0 comparisons.
2. Identity consumed by cycle detection: identical invalid refs and unresolved
   nominal spellings can be treated as matching semantic terms, manufacturing
   the self-edge or instance equality used as a cycle proof. Normal-input SCC
   algorithm failure has not been demonstrated; do not claim or presume it.

Executed raw cases: arbitrary subjectTraitOwner with absent subject/target,
existing generic trait with identical out-of-range positional refs, and the
same with an undeclared nominal. Each currently returns the cycle diagnostic
with Source=false. Unconditional Source annotation is deliberately absent.
This is not a newly observed ordinary-source compiler crash.

## Finite Actions and Authority

Trace registered conformance producer -> active bare/bundle/view graph request
-> scoped symbolic relation/ranking/search -> typed diagnostic and final
consumer. Start with Ir/Conformances.pw registerConform and
Codegen/Check/Conformance.pw traitCycleEdgeActive, buildTraitCycleGraph,
traitCycleTermRelation, traitCycleTermsAlphaEqual, unifyTraitCycleTerms,
traitCycleConstructorCount, checkTraitSubjectCycles and their actual callers.
Enumerate the affected comparison and graph entry paths before changing them.

- Establish input validity in one appropriate graph/request admission owner;
  reuse existing canonical type/binder/scope contracts where applicable. Carry
  the established facts into comparison/search rather than rechecking source
  spelling or inventing a cycle-only parallel type checker.
- Check actual owner existence/canonical identity and subjectTraitOwner
  consistency, argument range/arity, scoped binder identity and participating
  symbolic children (record/projection children included). An existing numeric
  ID alone is not an admission receipt. Respect each ID domain's valid zero
  index; missing sentinel0 must not be confused with a valid first row.
- Raw malformed/unresolved requests must fail through a typed non-Source
  result identifying the missing/invalid prerequisite, before cycle/growth
  conclusions. Do not silently drop bad edges and return success, panic on
  caller-supplied malformed input, or only adjust the final failure domain.
- Equality/unification/canonical-owner comparisons must operate on established
  identities/terms: the same missing sentinel, invalid ref or unknown spelling
  is never semantic identity. Remove or constrain the offending raw equality
  paths; a new entry check with the old unsafe callers intact is insufficient.
- Once admitted, preserve current source-cycle and SCC growth rejection,
  fresh traversal binders, source-set/bundle scope and permitted shrinking /
  distinct-instance / acyclic paths. Preserve eager declaration checking and
  existing source provenance/order. No concrete where-satisfiability search
  is authorized as a replacement for structural comparison.

com-x95z owns the existing symbolic-projection well-formedness question, including
its inherited-signature context. Consume that conclusion before finalizing the
projection admission predicate; do not resolve it by inventing implicit proof
or by rejecting every symbolic projection. A clarified test is not itself a
product admission implementation. Wait for the bounded contract conclusion, valid
oracles and explicit follow-up assignment, not completion of every product
repair that com-x95z may assign. Keep normal type/binder authority shared.

## Guarantees, TDD and Completion

Create meaningful defect REDs for invalid-input diagnostics and unsafe identity,
not just Source=false (which already passes on the three raw probes). Preserve
those fail-closed GREEN controls. Cover missing/foreign owner, out-of-range and
unresolved nominal arguments, arity/range errors and foreign binders; verify that
invalid data cannot yield a successful equality or cycle proof through another
exposed path. Pair with established same/different owner and scoped-term cases.

Use tests/compiler/frontend/TraitCycleFailureDomains.pw/.out for existing source
cycle/growth and shrink/diamond controls. Its current failure asserts the pending
Source domain; do not report that as RED for malformed graph admission. Retain
valid source-set extensions, generic freshening/edge reuse and symbolic record /
projection contrasts relevant to modified paths, using com-x95z's valid oracle.
Do not mutate tests during live validation. Test intent and exact input/hash /
compiler/mode must be retained. Only add combinations that exercise distinct
responsibility boundaries, not a new full solver matrix.

Completion requires producer-to-comparison closure, removal of unsafe alternate
identity paths, typed non-Source refusals for malformed raw input, preserved
valid cycle semantics, applicable targeted actual-compiler/consumer checks and
independent neutral review. Record the precise admitted artifact/API, all actual
callers, results and remaining limits. Code changes and applicable gates remain
open; this issue is not completed by creating a verifier or writing this plan.

## Ownership and Exclusions

This phase-three repair is a prerequisite for com-yeua's sound cycle/growth
producer classification; com-yeua retains the domain/channel/cache/terminal
integration and actual negative-consumer completion. Coordinate the boundary
so admitted cycles become Source only with this contract; malformed inputs never
do. com-fsuq remains transitively downstream and owns classifier assertions.

com-xh2h owns the broader phase-four API-authority/signature narrowing, not this
semantic defect. Share the corrected contract/caller map with it; do not move
that whole phase-four work into phase three or preserve the malformed-input
behavior as an intended refactor invariant. com-oir7 remains the separate view
validation input-narrowing task; merely calling this checker creates no new
whole-task prerequisite.

Excluded: new source semantics, projection policy chosen without com-x95z,
conformance solver redesign, new SCC algorithm without a demonstrated defect,
new type system/evidence authority, graph optimization, general API narrowing,
public status/callback ABI changes, main/seed promotion and claims that scoped
checks certify phase-three/final gates.

## Read-only Implementation Checkpoint

The [caller map and next defect tests](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-caller-map.md)
trace registration through bare/bundle/view entries, graph construction,
ranking, unification and search deduplication at c63ffc07. Two raw invalid-ref
equality paths remain; current helper accessibility also permits bypassing an
entry-only repair. This inspection changes neither scope nor dependencies.
com-x95z's source/oracle follow-up is assigned to com-amjl; the bounded
investigation is closed as investigated after independent assignment review. No product or fixture edit,
executed RED/GREEN, task start/closure or independent product completion is claimed.

## Implementation WIP: First Three Malformed Requests

`TraitCycleInputAdmission.pw` executes the missing-owner, out-of-range-ref and
unknown-nominal cases. [Initial RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-input-red.json)
and [fresh checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-input-first-checkpoint.json)
retain exact assertions, hashes and actual results. Standard build
20261106T102721-build-35b44d passed with unchanged inputs; candidate
bin/plewc-trait-cycle-input-first passes these three native assertions.

This is not completion. Independent WIP review confirms graph Result/error
transport and private raw helper boundaries, but requires retained canonical
identity through relation/search, lexical membership separate from free-variable
eligibility, complete binder/arity/constructor inputs and preserved ordinary
source diagnostic domains. The new pattern-input code currently drops resolved
nominal identity after validating existence; do not leave that as the endpoint.
The ordinary unknown-type source probe also currently returns Input and needs
correction within this producer-to-input boundary. Source-cycle domains,
preserved graph/source controls and final independent completion remain pending.

## Second Increment and Shared Child Regression

Canonical nominal/projection owners are now retained in private admission facts
and consumed by graph relation, alpha comparison and search. Binder membership
uses lexical ParamId separately from free-variable eligibility. Exact authored
lowering-use receipts distinguish an invalid source type from an artificial raw
request; nominal unknown/arity refusals do not bless unproven raw input as Source.

[Incremental executed assertions](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-input-second-increment.json)
retain the scoped RED/GREEN and unresolved cases. Earlier native runs compile
imported compiler source and are not final fresh-CLI verification.

A real representation defect was reproduced: rebuildProjectionTerm retains a
record receiver mirror, while common child count/ref/label formerly selected
record fields before the projection receiver/trait arguments. A raw invalid
receiver was admitted (executed RED); valid record projection and known extension
view controls passed. Both TypeRef and scalar child APIs now prioritize the
projection discriminator. Independent read-only review confirms that the explicit
receiver, not duplicate record mirror fields, is the semantic authority. [Fresh build and native checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-input-second-checkpoint.json)
records standard build 20261106T111547-build-728482, unchanged inputs and exit 0.
The saved bin/plewc-trait-cycle-input-second candidate passes all 17 native
assertions across the four current internal fixtures.

Remaining finite admission work includes view-source identity/selector validity,
record ABI-name independence in graph heads, preserved source-domain cases and
source-set/freshening controls. The common non-cycle typeTermRefSameHead also
retains a record-first shortcut: independently track its actual equality defect
and repair ownership rather than claiming the child change repairs all equality.
No task/area/phase completion, full suite, formal performance or fixed point is
claimed by this increment.

[Additional authored controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-source-shape-probes.json)
confirm that source I64[I64] and T#P.NoSuch currently return Input rather than
Source; these are required remaining corrections, not accepted behavior. A
wrong projection positional arity is rejected earlier as Unclassified and is
retained for com-yeua's actual producer classification.

The [non-cycle common-head probe](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-head-probe.json)
compiles/links successfully, then fails its structural inequality assertion:
two record-receiver projections selecting different associated members compare
equal through typeRefEq. This probe establishes an internal structural equality
defect, not a demonstrated ordinary-source miscompile. The common head still
short-circuits on isRecord before inspecting projection identity. com-vh0x
explicitly excludes algorithm/acceptance changes, so it cannot silently absorb
this product repair. Confirm separate finite repair ownership before extending
implementation scope.

[Independent scope review](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-input-second-review.json)
confirms a separate finite bug is needed for the non-cycle head shortcut. The
raw probe has no receiver conformance evidence; do not call it a valid-source
miscompile. Include a justified receiver/associated-output control in that
repair's acceptance. Proposed actual area intake: met-6e6k and met-ia09, not an
automatic met-c1pg prerequisite. Task addition is awaiting user decision under
the active task-gap stop condition. Current met-c1pg remains in_progress with
the explicitly retained admission/source-domain work.

## User-Requested Projection Reachability Investigation

[Bounded investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json)
separates three findings; no product repair or expanded completion is claimed.

- Production rebuilding and explicit substitution can construct the record-mirror
  projection pair that common typeRefEq incorrectly equates. That substitution
  does not satisfy T:Projection; it is not a legal source-instantiation proof.
  Authored bound generic, nested-record-field and concrete nominal controls
  compare correctly. Source conformance and structural identity are distinct
  responsibilities; equality must not query conformance to repair its head.
- Spec02 explicitly forbids anonymous record impl/trait conformance. CLI --check
  nevertheless accepts a record conformance and its generic-bound use. This
  source refusal defect must not be treated as a valid conformance control.
- The apparent direct source projection case is another path: the parser reads
  one authored parameter as five (value, #, Projection, ., First) without error.
  File frontend parameter0 is a plain record. No associated projection was
  parsed, so this does not reach the projection-head defect. The first owner is
  Syntax's record-type return plus permissive parameter token/separator parsing,
  not demonstrated loss by lowering. The corresponding newtype parse does error.

An independent fresh reviewer confirms these limits and the corrected parser
cause. Earlier advice to use a justified record conformance as a legal source
control is withdrawn: the specification forbids it. Use valid nominal/nested
record controls separately from malformed internal projection relations.

Keep finite structural-head repair, forbidden record conformance admission, and
malformed parameter parsing ownership distinct. Existing com-amjl still owns
source trait-view evidence; this investigation does not silently expand that
issue, com-vh0x's API scope, or met-c1pg into all three repairs. Task assignment
remains pending after the requested investigation.

## Adopted Follow-up Assignment

The user authorized the four finite follow-ups after clarification:
[com-wka4](com-wka4.md) owns bare declared-subject/owner admission;
[com-0w38](com-0w38.md) owns record impl prohibition including named extensions;
[com-cuoy](com-cuoy.md) owns unsupported suffix conversion into fake parameters;
[com-bvc8](com-bvc8.md) owns projection head identity and the API/data
responsibility investigation around receiver mirrors. The latter must examine
necessary inputs and competing category interpretation, not just reorder a
conditional. These are open product repairs, not completion of this issue.

[Assignment reconciliation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-issue-adoption.json)
retains actual phase-three/area intake; none is automatically a met-c1pg
prerequisite. Earlier awaiting-decision observations above are historical
checkpoints now superseded by this authorized assignment. met-c1pg's remaining
input/source-domain/identity controls remain in_progress.

## Authored Provenance Increment

[Fixed-input checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-authored-sites-checkpoint.json)
records standard build 20261106T181802-build-4c77d5, fresh candidate
plewc-trait-cycle-authored-sites, 22 internal assertions and two CLI Source
refusals. Unknown nominal, primitive arity and missing projection member retain
source diagnostics; equivalent malformed raw requests retain Input failures.
Lower records authored sites privately, independently of legacy binder visibility
suppression and the public temporary use list. A reconstructed first-attempt
baseline with all source hashes matched demonstrates the forged-use-list RED.

Independent read-only review by trait_cycle_admission_wip_review accepted this
increment's provenance boundary and reconciled all 22 native/2 CLI results,
exact causes/domains and fixture/candidate hashes. No task completion, full
suite, fixedpoint or performance certification is claimed. Canonical view
selector admission/identity, record ABI-name independence in the private graph,
remaining source-domain controls and whole-task review remain unfinished.

## Private Record Identity Increment

[RED/GREEN checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-record-identity-checkpoint.json)
records a same-field/different-ABI-name cycle missed by baseline 96ea5682.
The private graph head now recognizes records structurally after checking
qualifiers; shared child traversal retains field labels and types. Fresh build
20261106T183012-build-43ebc7 passed unchanged inputs and 25 internal assertions,
including changed-label and changed-type controls. Independent source review
accepted the finite change and required those fresh controls, now satisfied.
Common non-cycle comparison remains com-bvc8; view/source-domain controls,
whole-task review and parent gates remain open.

## View Admission and Identity Increment

[Fixed-input checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-view-identity-checkpoint.json)
records build 20261106T184825-build-20e0c1, 37 internal assertions and 15
source checks. Shared semantic view readers supply validated, deduplicated
selector sets retained in private graph facts. Trait selectors retain actual
owners, including same-spelled declarations from two real modules; extension
existence reuses the current registered bundle query without receiver
applicability or conformance search. Unknown/mismatched owners and multiple
trait selectors fail typed admission. Projection parents' compatibility mirrors
are not a second identity: their receiver children own view semantics.

Independent review found and corrected premature parent-mirror comparison and
missing multiple-trait rejection; executed intermediate REDs and the reconstructed
intermediate source hash are preserved. Final source/result review accepted the
37 native cases and 15 source check controls. Successful source checks retain
existing warnings; they are not all stderr-empty. No whole-task, Source cycle
producer, full-suite, runtime source-fixture or performance certification is
claimed. The existing absence of empty-bundle source identity was observed, not
reinterpreted as a new acceptance policy. Source cycle/growth classification and
the whole-task guarantee reconciliation remain pending.
