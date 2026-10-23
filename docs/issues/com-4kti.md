---
id: com-4kti
status: open
deps: [com-nucu]
links: [com-nucu]
created: 2026-10-23T13:23:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, generics, verification]
---
# Enumerate projected trait input instances and admit the selected full proof

Planned mandatory repair outcome of C2/com-nucu. projectedMemberResolution currently consumes the first Existence/open-input proof as its selected requirement. Replace that handoff with finite distinct positional-instance enumeration, normal callable applicability, and SourceAdmission of the chosen complete trait instance. Preserve source precedence, exact duplicate premise deduplication, ambiguity and associated-output checks.

## Acceptance Criteria

Bool and I64 arguments choose their unique matching instances regardless of bound order; indistinguishable no-operand instances and independent source paths reject; exact duplicate premises do not create ambiguity; associated-output mismatch still rejects. Save the admitted full proof through CallTemplate, both worklists and actual native/Mid calls. No name/order fallback; fresh scoped controls and independent completion review required.


## Boundary and Entry

Planned C2 repair disposition; parent criteria 3, 4, 8. Keep this to the existing
projected receiver member path. Entry: Check/Bounds.projectedMemberResolution,
Mono/Resolve.queryTraitPatternProof/projectedTraitPatternProof/
traitPatternProofFromFacts and the selected call constraint publication boundary.
Return distinct complete positional trait-instance candidates before normal
applicability; do not use discovery order or associated outputs to choose an
input instance. Reuse the common source-proof/path workers rather than creating
a second conformance solver. Query the selected full instance with SourceAdmission
before publishing its requirement/proof. Preserve exact authored premise priority,
explicit source views, ambiguity and existing conditional/projection children.

## Closure Evidence

Turn the watched C2 counterexamples into positive/reject regression controls;
add a concrete conformer with distinct results to exercise the selected call
through native/Mid. The two-input Bool call must work in either declaration
order; no-input ambiguity and independent source-path ambiguity must reject.
Recheck existing associated_projection_constraint_identity and
source_selected_witness_owner_evidence. Record actual removed first-hit paths,
fresh source/candidate/input hashes, and independent completion review here.
Final normal/gen/deps/sanitizer/fixed-point/performance gates remain G2a/G2b.

## Proposed Scope Correction — Awaiting User Decision

**Do not implement the projected-only fix before this allocation is resolved.**
C2's independent review found the same first-candidate source bug on ordinary
opaque generic receivers in staticMemberResolution. That frontier was omitted
from the current bounded task ownership; this is the user's task-plan stop
condition. Existing projected-only scope above is not silently expanded.

Recommended correction: one bounded repair owns the shared source-candidate
frontier for ordinary and associated-projection receivers:

1. Form the finite set of distinct complete positional trait instances available
   for receiver/member under the explicit lexical premises, selected sources and
   retained associated/supertrait prerequisites. An Existence probe cannot choose
   the one instance that supplies all later call meaning.
2. Apply common callable applicability to the candidates using available argument
   types/labels/modes; reject indistinguishable input-instance alternatives. Do
   not filter independent source ambiguity away by associated output expectations.
3. Admit the selected complete instance through the common SourceAdmission path,
   preserving exact opaque premises, duplicate-premise equivalence, selected
   views and independent-path ambiguity. Publish that declaration/instance/proof
   once; both worklists and final Mid/backend use it.
4. Replace both first-return source frontiers. Verify both receiver families with
   bound-order inversions, unique typed operands, no-operand ambiguity, duplicate
   premises, independent trait-subject paths, output mismatch and an actual
   concrete native result. Retain fresh input/candidate fingerprints and an
   independent completion review.

No language-specification or ABI change is proposed. The change is to execution
task ownership and shared implementation scope. Before resuming, approve/update
this task's entry/action/acceptance and connect it to reopened met-ucze as well as
met-6e6k/G1; leave B1/B3/B4's valid narrower evidence intact. If implementation
analysis cannot keep this as one finite shared-frontier repair, stop to split
concrete independently closable changes rather than turn it into a new solver
redesign. Current compiler production remains 51e19101.

## Independent Review of the Proposed Task Revision

User-requested reviews examined compiler 402e2238 (production 51e19101), the
proposed shared frontier, current design contracts and the retained nine source
contrasts. All reviewers were read-only; none changed code or ran build/tests.
This section records recommendations, not adoption of the scope correction.

| Reviewer | Scope | Verdict |
| --- | --- | --- |
| /root/candidate_repair_design_plan_review | Responsibility, source selection, proof admission and implementation feasibility | Sound shared boundary; concrete acceptance refinements below required before implementation |
| /root/candidate_repair_size_review | Finite actions, deliverables, size and possible splitting | Keep one bounded repair with three checkpoints; medium implementation scope, near the upper end of the 1–2-day target, not a guaranteed estimate |
| /root/candidate_repair_dependencies_review | Ownership, real dependencies, closure order and evidence reuse | Keep primary parent met-6e6k; add selection and D3 dependencies; no whole-plan reorganization or duplicate repair ticket |

### Required Task-text Refinements

On approval, replace the projected-only title, description, Boundary/Entry and
Acceptance consistently, instead of retaining contradictory instructions and
appending another accepted plan below them. The revised task must specify:

- Distinguish an input instance from its proof paths. Candidate identity retains
  receiver, trait owner, complete positional arguments and member declaration.
  Different paths for the same instance are not overload alternatives that
  argument/output filtering can discard. Existing SourceAdmission decides their
  uniqueness after that complete instance is selected. Exact duplicate premises
  retain the existing equivalence rule; explicit views and source priority stay
  intact rather than being flattened into an unordered pool.
- Separate open-input enumeration from exact-instance admission. Neither changing
  the open query to SourceAdmission nor publishing Existence's first proof fixes
  this boundary. An exact opaque premise has priority for its exact instance,
  not authority to hide different schema-derived input instances during open
  enumeration. Retain associated prerequisites and supertrait/trait-subject edges.
- Use successful callable applicability, not the rank-1 type-mismatch candidate
  currently retained for diagnostics. Isolate each candidate's trait/method
  substitution and tentative inference/context; the first candidate cannot type
  a literal or leak a binding that removes another candidate.
- Cover ordinary direct-bound, supertrait, trait-subject and existing Provided
  selection as well as the projected requirement path. Root enumeration followed
  by an old first-return helper leaves the same bug in place. Provided's existing
  labels-only shortcut must not stand in for complete applicability. Preserve the
  existing supported surface; no new opening or inference rule is implied.
- Publish the selected declaration, complete instance, method arguments and
  admitted proof once. Existing CallTemplate/constraint admission, both worklists
  and final Mid/backend consumers interpret that fact; they cannot search again.

### Three Implementation Checkpoints Within One Task

1. **Finite candidate query.** Connect both receiver inputs to the common proof
   workers; return distinct complete trait-instance/member candidates with source
   provenance and prerequisites, keeping enumeration distinct from admission.
2. **Shared source selection.** Replace the two producer frontiers and their
   relevant direct/supertrait/provided/trait-subject first-return shortcuts with
   common applicability, ambiguity and exact-instance SourceAdmission. Remove
   superseded paths rather than leaving receiver-specific alternate decisions.
3. **Saved selection through use.** Check declaration and executable worklists,
   actual concrete native/Mid results and selected proof/instance integrity on
   both receiver families. Add order inversions, typed operands, no-operand
   ambiguity, duplicate premises, independent paths and output mismatch controls;
   include a provided or supertrait route and coexisting explicit/schema-derived
   input instances. Recheck operator arity controls because its caller shares the
   supertrait helper. No newly discovered operator defect is asserted here.

Non-goals remain a general conformance/call solver replacement, existential
opening, B3 environment redesign, independent C4 result-recipe migration and
D3's whole write-authority audit. If existing applicability cannot be reused
without a general engine redesign, stop to revise the granularity. The preferred
contingent split is shared instance enumeration/query contrast first, then both
producer migrations and final use; do not split by receiver and duplicate solvers.

### Required Dependency and Closure Updates on Approval

- Add **met-ucze -> com-4kti** so the reopened selection area cannot close solely
  from previously closed B0/B1/B2 children.
- Add **com-wqa0 (D3) -> com-4kti** and update D3's Entry/Action to audit the
  revised source selection/constraint publication boundary after this repair.
  Auditing the old writer API and closing D3 first would certify stale inputs.
- Keep **com-4kti -> com-nucu**, existing met-6e6k/G1 dependencies and primary
  parent met-6e6k. Do not add com-nucu -> com-4kti: that creates a cycle.
- C2 can close as a classification once the revised responsibility, entry/exit
  and actual dependencies are approved and recorded; it need not wait for repair
  execution. met-ucze can reclose only after the repair's scoped fresh evidence
  and independent completion review. G2a/G2b still own final whole-candidate gates.
- No new dependency on every C3–C6 or D1/D2/D4 task is justified by this finding.
  B1/B3/B4 narrower results remain evidence for their recorded inputs, not proof
  that a changed compiler passes. Re-execute affected saved-proof/callee/output/
  source-path controls on the fresh repaired candidate.

**Review conclusion:** one shared-frontier repair is the recommended revision.
The plan change is localized, while implementation is medium-sized and needs
these explicit checkpoints and dependency edges. Scope/graph adoption and source
implementation still await the user's decision under the task-plan stop condition.
