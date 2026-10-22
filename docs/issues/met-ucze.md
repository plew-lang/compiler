---
id: met-ucze
status: in_progress
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

The historical 2983c47f review found Resolve/Preparation trying Record(false), Generic, Declaration and Record(true), with Record/Generic staticMemberResolution paths and different bound/trait candidate inputs. This was a structural read-only finding, not a newly reproduced current miscompile. Recheck the cumulative candidate before deciding which paths remain.

Make one source construction/selection owner authoritative and preserve the selected declaration, requirement, lexical owner and evidence through publication and final consumption. A shared selector repeatedly run by downstream readers is not completion. Preserve candidate order, visibility, labels, full signature, ownership and bounds; do not make a candidate-exists predicate final acceptance. Distinguish constructing a first concrete witness for a source-selected abstract requirement from selecting an already fixed witness again.

Acceptance: trace ordinary, generic-bound, provided, trait-subject, operator and implicit calls; remove competing source selectors/fallback accept paths, retain ambiguity/reject controls, and record remaining paths and removal conditions. The storage restart gate of met-si6j applies.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current written, generic-bound, provided, operator and implicit-call selection. Eliminate competing source selectors while preserving source-selected abstract requirements and legitimate first concrete witness formation. Sequence after the owner-reader core; this is implementation order, not a fabricated dependency on every other frontend ticket.

## Next Closed Increment: Source Operations

Rechecked at production `85aa9a96`, while com-kp3y is finishing its gates.
The owner-local expression/header/binding/completion component does not yet own
`Comp.callTemplates`, `callTemplateIndexSlots`, `callTemplateSourceOwners` or
`selectedCallConstraints`. Preserve their existing site keys and final descriptor
identity while migrating their semantic rows through the same owner boundary.
Coordinate with met-acfl and met-ia09; do not call storage alone completion.

The construction frontier is Resolve/Record's direct/static/dynamic/operator/
protocol producers and the type queries they call. Preparation currently visits
Record(false), Generic, Declaration and Record(true). Generic's symbolic method
checks can consume a recorded template, but several branches still call
staticMemberResolution or bound/member-existence queries again. ExprType also
constructs method results when no completed expression fact is available.
The migration must identify permitted tentative inference separately from an
already committed source choice; routing all repeated selections through the
same algorithm is insufficient.

Close one source-operation contract from construction to consumers:

- Give the source checker one operation-construction boundary. Private candidate
  probes may refine permitted unknowns; only the admitted candidate commits its
  declaration/requirement, receiver/evaluation sources, complete signature,
  substitution, result recipe, conversion and evidence. Preserve explicit
  uncomputed/no-static-selection/selected states where applicable.
- Generic/declaration compatibility reads the committed operation instead of
  selecting another member. Remove redundant construction walks only after
  their distinct checks have real owning producers/readers; do not simply omit
  Generic or Declaration diagnostics to obtain a single walk.
- Store successful operation and constraint rows in the owner payload, retaining
  immutable shared argument/type/proof ranges as session IDs. Any remaining
  global navigation index contains identities, not a second semantic store.
  Body/call-site readers reject missing/foreign/unprepared facts and cannot
  snapshot every owner's calls.
- Instantiate those saved operations and exact declaration-bound evidence into
  the callee environment and real Mid/final call consumers. The existing
  InstanceEnvironment.constraints and final CallSiteKey identities are inputs
  to preserve, not new mechanisms to recreate. Legitimate first concrete witness
  formation stays within the source-selected requirement.

Additional physical boundary to resolve: closeProgramCallTemplates currently
rewrites CallTemplate.mayHaveStorageArguments after source preparation. This is
an auxiliary access-demand classification, not permission to mutate a sealed
operation. Compute its source-stable part before sealing or give later analysis
its own result. The public requireCallTemplateStorage writer has no production
caller in this revision; audit tests/references and remove or place it under the
actual analysis authority instead of retaining an unrestricted payload writer.
`tests/compiler/mid/DeclarationLocalAccess.pw` does use it to force an eager
reference analysis beside the demand-filtered analysis. Preserve that comparison,
including equal diagnostics and absence of executable-body/destructor discovery;
move the eager root selection to the analysis request rather than mutating the
source payload or deleting the negative control.

Verify direct, requirement/provided, dynamic, operator and implicit calls through
actual callee bodies, with positive and wrong/missing owner/site/clause/proof
controls, AOT/JIT/gen and removal of competing decisions. Include a matching-source
old/new cost comparison whenever the new increment appears slower; fix easy
extra copies/searches rather than relying only on the seven-second ceiling.

## Storage Summary Publication Increment

First remove the remaining post-success template rewrite before moving operation
rows into owner payloads. `mayHaveStorageArguments` is a conservative source-stable
summary of the selected signature and operand passing forms. Compute it at the
private successful lexical/global preparation tail, including nested closure
rows, after default/selection/obligation closure and before source publication.
Whole-program closure and Mid analysis only read the result. Preserve the
conservative true default for unknown forms and subsequent sites once an owner
is already known to require access analysis.

Remove requireCallTemplateStorage entirely. DeclarationLocalAccess's existing
eager comparison must request eager analysis explicitly instead of mutating source
calls; preserve diagnostic equivalence, demand-versus-eager body counts and absence
of executable/destructor discovery. New controls check precision immediately after
a lazy function/global request, post-success writer rejection and stability across
whole-program closure. This bounded publication repair does not complete source
operation storage/selection/evidence migration.

## Source Selection Construction Increment (WIP)

After the storage-summary repair, construct function operation rows in the first
Record walk, disable call construction for Generic/Declaration compatibility, and
remove the second Record walk. Keep default-generator restriction and result
validation at the same construction boundary; do not lose checks that were gated
on the old false/true pass flag. Source-call closure still checks complete selected
Direct/Static signatures, labels, ownership modes, substitutions, operand/conversion
plans and admitted bounds/evidence.

Generic method validation reads the selected declaration for qualifier category
and retains its existing contextual argument checks. Remove its independent
staticMemberResolution, boundProvidesMethod and traitProvidesMember call paths.
The old traitProvidesMember helper has an internal owner-identity fixture; migrate
that control before removing the now test-only helper. Operators/iteration and
Verify's concrete method queries still require their own saved-operation reader
migration. Removing a walk alone is not completion of this task.

New generic_call_selected_authority poisons only the method's diagnostic AST name
after construction while retaining its CallSiteKey: compatibility must use the
selected requirement, add no operation, and reject a deliberately missing saved
selection. Ordinary/generic/provided/default/closure/global AOT/JIT/gen and full
signature rejection controls remain required. Fresh builds and whole compiler-source checks now succeed at `699a9c59`;
normal verification of the preceding 0793cf02 snapshot is independent.

## Construction-Order Findings and Validation Boundary

Enabling the first operation-construction walk exposes dependencies on the old
second walk. Repair the owning producer rather than restore a global repair walk:

- An untyped numeric receiver such as `0 - typedValue` obtains only its permitted
  integer literal context before selection. A typed receiver's selected signature
  still owns Rhs context; heterogeneous operators are not forced homogeneous.
  Retain source result projections, particularly Ord's Ordering -> Bool.
- The second nominal-field visit must use the same constructionFieldContext as
  the first. Diagnostic inspection of SourceFacts.setState found a spurious
  conversion from SourceBodyState to Optional's unbound `T@39`; the completed
  expression still had SourceBodyState. Do not treat omitted declaration binders
  as rigid lexical context.
- Synthetic nominal Make nodes may have a selected name and no annotation term.
  Resolve that nominal term before field context and aggregate publication. The
  existing generation directiveargs control exposed the missing aggregate in its
  synthesized main; no gen-specific bypass or fabricated aggregate is introduced.
- A conversion requested while its source term is zero is an explicit builder
  dependency (pendingSource), not failed final evidence. Complete it from the
  recorded expression fact after default/type refinement and before call closure
  and owner publication. Never re-infer source syntax in the final reader. Both
  evidence admission and Mono reject pending requests; post-outcome conversion
  construction is rejected. Known incompatible evidence remains rejected.

New controls: generic_call_selected_authority, source_operator_literal_context,
inferred_enum_argument_source_owner and pending_source_conversion_completion.
The pending-request control and unchanged declaration_conversion_closure reject
control pass when current compiler source is compiled into the fixture with the
stable storage-publication carrier. This source-probe evidence is distinct from
testing the fresh compiler executable.

The `95bd11cb` fresh compiler source check passed. Its AOT slice passed the three
initial new controls plus retained call-result/substitution/proof/private-provided
controls before stopping on operator_literal_nested's stale zero-source conversion.
Its generation gate passed 23 positives and five rejects, failing directiveargs.
The above pending/nominal fixes address those findings; their fresh product
rechecks are pending. Full operation storage, callee-evidence and remaining
Verify/operator/iteration selector migration are still open.
