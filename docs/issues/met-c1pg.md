---
id: met-c1pg
status: open
deps: [com-x95z]
links: [com-xh2h]
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
com-x95z's follow-up assignment remains pending. No product or fixture edit,
executed RED/GREEN, task start/closure or independent completion is claimed.
