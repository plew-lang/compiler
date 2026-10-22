---
id: met-ucze
status: open
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
