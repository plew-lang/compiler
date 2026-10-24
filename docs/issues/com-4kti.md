---
id: com-4kti
status: closed
deps: [com-nucu]
links: [com-nucu]
created: 2026-10-23T13:23:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, generics, verification]
---
# Unify generic and projected member candidate selection before source admission

Mandatory repair identified by [C2](com-nucu.md), covering the shared source
candidate frontier for ordinary generic and associated-projection receivers.
At production 51e19101, both frontiers can publish the first trait input instance
instead of considering all applicable instances. Scope and dependencies were
approved on 2026-10-24 following the independent reviews below. This is a task
allocation correction, not a language-specification or ABI change.

## Boundary and Entry

Parent criteria: 3, 4, 8. Primary parent remains [met-6e6k](met-6e6k.md);
[met-ucze](met-ucze.md), [D3](com-wqa0.md) and [G1](com-61jt.md) require this
repair. Classification [com-nucu](com-nucu.md) is its prerequisite, not a
consumer waiting for implementation.

Entry: `Check/Bounds.pw::staticMemberResolution`, `projectedMemberResolution`,
`selectStaticRequirement`, `staticMemberInSupertraits`; the common proof workers
`Mono/Resolve.pw::queryTraitPatternProof`, `projectedTraitPatternProof` and
`traitPatternProofFromFacts`; selected call constraint publication and its
CallTemplate/worklist/Mid/backend consumers. Include ordinary direct-bound,
supertrait, trait-subject and existing Provided routes, not just projected
requirements. Preserve the existing supported surface and source precedence.

Use the existing [source lookup contract](../design/name-lookup.md),
[body checking](../design/body-checking.md) and
[handoffs](../design/frontend-handoffs.md). Reuse common applicability and
source-proof/path workers; do not introduce a second conformance solver.

## Actions and Checkpoints

1. **Finite candidate query.** Connect both receiver families to shared finite
   enumeration of distinct complete positional trait-instance/member candidates.
   Candidate identity retains receiver, trait owner, full positional arguments
   and member declaration, with source provenance and associated/supertrait
   prerequisites. An exact explicit premise has priority for its exact instance;
   it cannot hide different schema-derived instances during open enumeration.
   Preserve explicit source views and exact duplicate-premise equivalence.
2. **Shared source selection and admission.** Apply common callable applicability
   using available argument types, labels and modes. Isolate each candidate's
   trait/method substitutions and tentative inference/context. The diagnostic
   rank-1 type-mismatch fallback is not a successful candidate; the first probe
   cannot type a literal or leak bindings that discard another candidate. Replace
   the two source frontiers and relevant direct/supertrait/provided/trait-subject
   first-return shortcuts, including Provided's labels-only shortcut. Admit the
   chosen complete instance through SourceAdmission before publication. Different
   proof paths for one instance are not overload alternatives that argument or
   associated-output filtering can discard: the common SourceAdmission worker
   determines path uniqueness. Neither switching the open query to SourceAdmission
   nor publishing Existence's first proof satisfies this boundary.
3. **Saved selection through final use.** Publish the selected declaration,
   complete instance, method arguments and admitted proof once. Carry that fact
   through existing CallTemplate and constraint admission, declaration and
   executable worklists, and actual concrete Mid/backend calls. Remove superseded
   selection paths; downstream readers must not search or choose again. Reuse B3's
   saved evidence environments rather than redesigning them.

## Acceptance Criteria and Closure Evidence

Verify both receiver families with these scoped controls:

- Bool/I64 typed operands select their unique matching instances in either bound
  order; candidate-local inference does not change another candidate's result.
- Indistinguishable no-operand input instances reject as ambiguous. Independent
  source paths to one selected instance reject unless existing exact-premise
  priority/equivalence rules resolve them; exact duplicate premises stay valid.
- Associated-output mismatch still rejects and cannot select an input instance
  or erase source-path ambiguity.
- A provided or supertrait route and coexisting explicit/schema-derived different
  input instances exercise the shared enumeration boundary.
- Concrete conformers with distinct results prove the saved instance/proof reaches
  native execution and Mid through both worklists. Recheck existing
  `associated_projection_constraint_identity`,
  `source_selected_witness_owner_evidence`, saved-proof/callee/output/source-path
  controls and operator arity controls affected by the shared supertrait helper.

The nine C2 source contrasts and their hashes are retained in
`meta/evidence/existing-feature-conformance/source-owner-facts/phase3c-projected-member-audit.json`.
Turn the applicable counterexamples into normal/reject regression controls.
Record actual removed functions/paths, fresh source/candidate/input hashes,
decisive scoped receipts and an independent completion review here. These
checkpoints are within one medium-sized task, near the upper end of the rough
1–2 active working-day target, not a guaranteed estimate. No implementation or
fresh repaired-candidate success is claimed by this plan update.

## Limits and Closure Relationships

Non-goals: general conformance/call solver replacement, existential opening/new
inference rules, B3 environment redesign, C4 result-recipe migration, or D3's full
write-authority audit. If existing applicability cannot be reused without a
general engine redesign, stop and revise granularity. The contingent split is
shared enumeration/query controls, then both producer migrations and final use;
do not split by receiver and duplicate solvers.

C2 closes classification after ownership and dependencies are recorded; it does
not certify this repair. met-ucze closes only after this repair's fresh scoped
controls and independent completion review. D3 audits the revised publication
boundary afterwards. Keep valid B1/B3/B4 evidence for its recorded inputs;
re-execute affected controls on the repaired candidate. No blanket dependency
on C3–C6 or D1/D2/D4 is introduced. Final fixed-point/performance and full
normal/gen/deps/sanitizer gates remain G2a/G2b, including the median below seven
seconds; no gate is waived by this task's closure.

## Independent Review of the Proposed Task Revision

User-requested reviews examined compiler 402e2238 (production 51e19101), the
proposed shared frontier, current design contracts and the retained nine source
contrasts. All reviewers were read-only; none changed code or ran build/tests.
The user approved the task update on 2026-10-24. The accepted boundary,
checkpoints and dependencies above incorporate these recommendations; compiler
implementation remains open.

| Reviewer | Scope | Verdict |
| --- | --- | --- |
| /root/candidate_repair_design_plan_review | Responsibility, source selection, proof admission and implementation feasibility | Sound shared boundary; concrete acceptance refinements below required before implementation |
| /root/candidate_repair_size_review | Finite actions, deliverables, size and possible splitting | Keep one bounded repair with three checkpoints; medium implementation scope, near the upper end of the 1–2-day target, not a guaranteed estimate |
| /root/candidate_repair_dependencies_review | Ownership, real dependencies, closure order and evidence reuse | Keep primary parent met-6e6k; add selection and D3 dependencies; no whole-plan reorganization or duplicate repair ticket |

## Outcome

Completed at source/test revision **c056e658352362b2b915a7ffd5a6b3b4a2a72dcc**.
This closes this shared candidate boundary, not phase three or release gates.

- `Mono/Resolve::searchTraitPatternProofFromFacts` is the shared finite traversal
  for instance enumeration and exact queries. Projected and ordinary receivers
  retain authored, supertrait, trait-subject and associated-schema evidence.
  `projectedTraitAssumptions` constructs the same associated-clause evidence for
  discovery and exact queries. Exact opaque premises keep their priority.
- `Check/Bounds::staticMemberResolution` replaces the separate projected and
  first-bound/direct/supertrait/provided written-call choices. It deduplicates
  complete trait instances after provenance priority, uses the shared complete
  argument matcher with a candidate-local method map, and performs exact
  SourceAdmission only for the successful choice. Associated outputs never rank
  alternative sources. Original trait-subject bodies are represented by their
  target requirements rather than duplicate provided candidates.
- Candidate matching preserves nested records/functions/arrays and labels,
  legal boxing conversions, unresolved method slots and contextual closures.
  Conversion errors remain candidate-local; a type-mismatch rank cannot publish.
  `groundKnownCallTypeArguments` substitutes only bound slots. The existing
  `inferFnArgs` accepts the complete proof-grounded parameter vector for selected
  requirements, preserving method inference and result types.
- `recordStaticMethodTemplate` saves declaration, full instance, method arguments
  and admitted proof. Declaration obligations and executable worklists consume
  that same template through `instantiateStaticMemberProof`; Mid/declaration
  access and native lowering retain it. No separate concrete selection was added.
- The common exact proof worker now applies preferred-source cohorts to member
  dispatch too, preserving unrelated members when the explicit selector has no
  candidate. SourceAdmission compares paths; MemberDispatch compares executable
  endpoints. A preferred source with incompatible associated outputs cannot
  fall back. The remaining operator helper is explicitly grammar/arity-only;
  its written-call/provided selection shortcuts were removed.

### Verification and Independent Completion Review

Fresh candidate `bin/plewc-phase3c-member-selection-6`, SHA256
`0a7e4432d425c2052c24ac130b41406018a169e3951149752147c87ca8c57084`,
was built by standard run `20261024T021053-build-9f6d8f` (exit zero, immutable
inputs unchanged). Full compiler-source check passed. The watched scoped runner
`focused-10` passed **native 20 / reject 20**, with no exclusions, immutable
inputs unchanged and no internal errors in rejection controls. The standard
profile has no scoped fixture filter; each focused compile/link/run used the
existing watchdog rather than a weaker runner. Receipts and precise fixture
hashes are retained in
[the scoped evidence](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3c-member-selection.json).

New controls cover both ordinary/projected instance order and ambiguity, schema
plus explicit bounds, provided/supertrait routes, structural/method inference,
repeated method constraints, function labels, literals, boxing source ambiguity,
conversion-candidate isolation and output mismatch. `generic_member_source_selection`
executes all six explicit/inherited/unrelated-view calls;
`generic_member_contextual_closure` executes both contextual receiver families.
Existing saved-proof, declaration-owner, result-signature and operator controls
were rerun on the same candidate.

`/root/shared_member_completion_review` independently reviewed the implementation,
producer-to-final-consumer chain and fresh receipts. Earlier blocking findings
(partial structural inference, rank-1 publication, zero-slot substitution and
source/context propagation) were corrected and re-reviewed. Final verdict:
**bounded scope complete; no blocking findings** at c056e658, native 20/reject 20.

Standard formal checkpoint `20261024T021625-self-host-66ae62` reached generation-2
fixed point and median **6.717830 seconds** (7.309414 / 6.717830 / 6.707443), exit
zero and unchanged inputs. This meets the current seven-second checkpoint. The
changed-source comparison does not isolate the all-trait scan's cost. A later
frozen candidate still requires all G2a/G2b gates; this scoped closure does not
certify final normal/gen/deps/sanitizer success or main/seed/carrier promotion.
