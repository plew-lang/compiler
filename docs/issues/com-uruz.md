---
id: com-uruz
status: in_progress
deps: [com-m0bf]
links: []
created: 2026-10-24T07:16:50Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve selected declaration identity through custom-factory source receivers

## Boundary and Evidence

Required C3 paired producer/read repair, parent criteria **1, 2, 3, 8**.
This is the finite custom-factory construction/context receiver boundary, not a
whole type-checker, conformance or body-key redesign. The bounded-task policy in
[met-si6j](met-si6j.md#bounded-task-policy) applies; active human implementation
and scoped verification are intended to fit about 1–2 working days.

Entry: Resolve/Global::resolveConstructionContext, prepareFactoryConstruction,
rewriteNamedFactoryConstructionAt and rewriteFactoryConstruction's cast lane;
their supplied expected context, SyntheticCallSite.receiverTerm, and the saved
Direct/Static receiver/signature. Inspect the context producer actually reached
by the failure before choosing the repair; a raw simpleTypeRef fallback's mere
existence does not prove that it produced the observed value.

Contracts: [semantic identity](../design/types-and-evidence.md#2-semantic-terms-and-identity),
[context and commitment](../design/body-checking.md#3-contextual-inference-and-commitment),
and [source facts and handoff](../design/frontend-handoffs.md#2-source-fact-identity-and-states).

At production **7aeda7d5**, fixture checkpoint **38b33f37**, the fresh compiler
passes full source checking and module4, but string_interpolation fails at
Options.factory with actual receiver owner0 versus selected declaration84.
The ordinary File-input probe prepares main and reads two saved Direct templates
whose receiver term14 already lacks identity before bodyInstanceEnvironment.
For contextual </>, resolveConstructionContext passes ty=context: the first loss
may be in supplied context or receiver construction and is not yet localized.
The final body-key check is correctly rejecting that incomplete input.

[C3's finding](com-m0bf.md#scope-stop-unassigned-custom-factory-source-receiver)
and meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-chain-factory-scope-stop.json preserve exact inputs, carrier/build receipts,
probe source/output, actual scoped results and independent classification review.
User approval authorizes this task allocation. No implementation repair or new
successful validation is implied by creating it.

## Finite Actions

1. Trace the two failing default/explicit Options constructions from their
   source/expected-type context through custom-factory preparation/rewrite to
   SyntheticCallSite and the committed CallTemplate receiver/signature. Identify
   the first loss with decisive intermediate facts. Classify each listed rewrite
   lane as pre-publication construction, source commitment, or retained reader.
   Preserve complete selected nominal owner/children, ParamId, projection and
   view provenance. Legitimate rigid/projected receivers need their existing
   abstract evidence, not an invented nominal declaration.
2. Repair that source construction/selection boundary with existing declaration
   and complete-term APIs in its explicit lexical/selected domain. An unresolved
   pre-publication construction stays private until the ordinary phase resolves
   it; a committed nominal receiver cannot be a name-only success. Keep the
   existing phase authority. Do not globally stamp by spelling, mutate published
   facets, add a parallel readiness flag, or choose an owner from the final body.
   Preserve existing custom/memberwise selection, visibility, default ordering,
   source evaluation, and forward-only inference.
3. Pass the same selected receiver/signature through source context completion,
   both declaration and executable worklists, explicit callable substitution,
   BodyInstance environment/key and ready BodySignature, then actual
   CallResolution.calleeBodyId -> Mid construction/instantiation -> LLVM direct
   call/body emission. Reuse the saved receiver/identity checks of com-6paa;
   a second inference/selection or later owner repair is not a valid consumer.
4. Remove each paired raw receiver/replay authority that the repaired lane
   replaces. Document legitimate early construction and representation-only
   adapters that remain. Do not indiscriminately delete simpleTypeRef or expand
   into another unrelated producer. An independently necessary broader repair
   or undecided semantics triggers the normal bounded-task stop condition.

## Exit and Controls

- Record the observed first-loss producer, source/context -> rewrite -> saved
  signature -> both worklists -> actual final consumer, removed competing
  sites and retained phase-specific adapters. A new verifier alone, successful
  body-key rejection, or a repaired final reader does not close the task.
- Execute string_interpolation and string_interpolation_lifetime unchanged,
  including default Options, explicit </>, and explicit field options; preserve
  the default factory's effect order and existing ownership behavior. Keep
  named/anonymous factory and custom/memberwise selection controls, generic and
  nested receiver children, aliases and homonymous declarations. Use actual
  source construction paths; unrelated similarly named tests are not coverage.
- Add source/internal saved-receiver controls at the repaired boundary: exact
  selected owner and children before body admission, matching receiver reuse,
  distinct same-spelled owner separation, and missing/foreign owner rejection.
  Cover contextual and explicitly typed forms without widening inference.
  Retain justified rigid/projection context where the existing surface supports
  it; do not add unsupported generic/unique facilities to make controls pass.
- Build a fresh compiler and run full compiler-source checking. Finish the
  interrupted Chain/Buffer/associated-context/body-receiver native/reject controls
  and all required module controls, retaining exact source/carrier/input hashes,
  actual exit codes, golden/diagnostic results and unchanged inputs. Prior
  partial results remain valid only within their measured scope; unexecuted
  cases are not successful. Obtain independent task-completion review.
- Observe compile-time regression policy. Formal fixed point/median below7s
  and full normal/gen/deps/ASan-LSan on the final frozen candidate remain G2a/G2b;
  task closure cannot waive or claim those unexecuted final gates. No main,
  seed, adopted-carrier, ABI, runtime or language-specification change is in scope.

## Dependencies and Responsibilities

C3 classification/assignment precedes this implementation and does not depend
on this repair completing. The repair blocks interrupted i62n/qbwg/fyxe/6paa
completion, met-6e6k and G1; D4 is transitively blocked through its existing
qbwg/6paa prerequisites. No reverse edge to those incomplete repairs is needed:
reuse their saved WIP changes and controls without requiring their closure first.

i62n owns pre-rewrite Optional-chain source results; qbwg owns early/late Core
Buffer generation; fyxe owns selected associated parameter context; 6paa owns
registered receivers/body keys and final admission. This task owns the separate
custom-factory source/context receiver producer exposed by their validation.
nqjd's reviewed bounded closure remains closed. C4/C5 and D4 retain their general
recipe, conversion and publication API audits.


## Task Definition and Allocation Review

Independent read-only review by /root/body_receiver_completion_review inspected
this task-creation diff on compiler base **072ece07**, the source/probe evidence,
C3 inventory and routing changes, existing repair responsibilities and every
issue dependency target/edge. Verdict: **definition/allocation appropriate;
C3 reclassification complete; no blocking findings**. The first-loss investigation
is explicit, the source/context-to-final-consumer repair is finite, and no
particular raw fallback is assumed to be the cause. There are no missing targets
or dependency cycles; required six prerequisite edges and D4's transitive
prerequisite hold. nqjd's closed scope and the four incomplete repairs are retained.
This certifies task planning/classification only. Implementation, fresh controls,
independent completion review and final G2 gates are not certified.


## Implementation Checkpoint (Not Completion)

**7b7ae4f6 / 6b92594e / e10009c4** repair the source context before factory
rewrite. The old File-input probe shows Options signature terms12/14 already
have siteOffset0/hasDecl=false immediately after declaration analysis, before
main is prepared. Lower/Impl::appendTraitAssocTypes inserts name-only entries
into the lowering skip scope; Lower/Types previously erased source sites merely
on a spelling match even when that entry had no ParamId. The three type and
construction entrances now reserve that behavior for real ParamIds. Trait
requirement lowering's two representations supply their selected owner, Self
ParamId and parameter terms to the existing lexical projection producer, as
provided bodies already do. Its scope is saved/restored; no anonymous nominal
stand-in or new proof solver is introduced.

Global's factoryConstructionReceiver replaces the three raw receiver fallbacks.
It keeps supplied terms, gives early missing terms a normal source-site
construction, and resolves late missing terms in the selected source domain
through declaredTypeRef. Structural record literals bypass nominal factory
processing and continue to ordinary structural checking. Missing late nominal
declarations fail instead of becoming successful raw receivers.

Canonical requirements also expose asymmetric conformance environment handling:
conformanceTraitBound already substitutes its subject into associated outputs,
but copied positional inputs containing Self verbatim. Inputs now use the same
existing groundTermInEnvironment(selfRef: subject). Exact instance/output
comparison is retained; ParamIds are not rebound by spelling.

Initial fresh candidates and failures remain evidence, not passes. Fresh1
(standard build 20261024T072728-build-001996) reproduces the structural-literal
regression and requirement Item visibility regression. Fresh2 (standard build
20261024T073423-build-eaf881) rejects I64 as Add[Self] due to the ungrounded
positional input. The first internal fixture compile stalls on an unescaped
empty interpolation in its test-source strings; the never-green fixture is
corrected to escaped braces without weakening its assertions. Existing-carrier
preflight then compiles and runs the new Comp code's source-owner/factory test
successfully with unchanged inputs. This diagnostic does not certify a fresh
compiler or final gates. Fresh3 standard build 20261024T074133-build-7c1463 is
in progress on source e10009c4 from the known chain-source-2 carrier.

Independent read-only implementation follow-ups by
/root/body_receiver_completion_review found the structural regression, confirmed
the subsequent source/structural separation and requirement projection fix, and
confirmed positional Self grounding is proper same-declaration normalization.
No remaining static blocker was reported; fresh target results and final
completion review remain required. New source/internal and existing generic,
projection, shadowing, structural and exact-instance rejection controls are
queued for those checks. Final G2 obligations remain unchanged.
