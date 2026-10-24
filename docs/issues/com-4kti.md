---
id: com-4kti
status: in_progress
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

## Implementation Checkpoint

Implementation is in progress; no closure or final gate is claimed. The shared
proof traversal now supports enumeration separately from existence/admission,
and exact and enumerating projection queries share associated-clause evidence
construction. Both source receiver families feed one member selector, with
candidate-local receiver substitutions and exact-instance SourceAdmission.
Original trait-subject witness bodies are represented by the target requirement,
not counted again as independent provided declarations. The remaining operator
supertrait route has an explicit grammar/arity-only entry; its former written-
call/provided shortcuts are removed.

The first fresh candidate passed full compiler-source check and changed the
original ordinary/projected order-dependent examples to acceptance, rejecting
no-operand ambiguity. Additional new controls exposed the provided impl-binder
substitution and duplicate witness surfaces; their in-scope corrections await a
fresh candidate and controls. Preserve the failed and successful scoped receipts
under compiler scratch until the final revision and evidence are pinned.
