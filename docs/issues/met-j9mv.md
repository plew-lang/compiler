---
id: met-j9mv
status: closed
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, architecture]
---
# Decide checked-body storage and implementation restart boundary

Design-only prerequisite for the paused type-checking remediation. The [adopted physical design](../design/checked-body-storage.md) selects owner-local sealed payloads with private read-only strong handles and shared session term/proof IDs, compared against a live shared-store alternative. The seven-family reconciliation and fresh cumulative baseline are recorded below; this is not an implemented or measured representation. Private arrays and snapshots already present do not implement the adopted owner boundary. Do not add another implementation layer instead of reconciling the existing producers/readers.

Acceptance: provide actual field/key/state/API and writer/reader permissions, failure isolation, acquisition/append/copy-retain/index cost, worked end-to-end examples and finite old-to-new removal map. Resolve open architecture decisions with the user where required. Obtain design review, then establish one fresh cumulative baseline before implementation. An interned handle, CoW snapshot or new IR is not prescribed by this ticket.

## Current Design Boundary

The supplement now specifies the source/instance keys, payload fields, Building/Succeeded/Failed publication, registered-signature queries, required/optional readers, synthetic plans, worked paths and finite migration families. Read-only comparison against the retained 2983c47f candidate identified all-owner semantic snapshots in preparedSemanticFacts. That source inspection is separate from the fresh baseline below. Independent design comparison supports the owner-local direction without claiming shared stores inherently require whole-table CoW.

The cumulative reconciliation below identifies the producers and final consumers; the same candidate now has a fresh fixed-point/performance and normal-suite baseline. The independent comparison and corrective design review are complete; adoption falls within delegated internal decisions because it preserves the existing public/semantic contracts and replaceable reader boundary. Source/instance authority, failure isolation and missing-fact rejection are fixed; index shape, packing and allocation refinements follow the recorded correctness/cost measurements. Implementation gates and the current parent performance condition still apply.

## Cumulative Restart Reconciliation

Inspected input: compiler `2983c47ff7ba0b1d693d656094e9fd0dbeca63dc`
(`codex/source-aggregate-facts`), clean source tree. This is read-only reconciliation
of the migration families, not proof of complete language coverage or a repair.
The design checkout and the candidate remain separate. The implementation must
preserve the successful increments already in this candidate.

| Family | Actual producers/state in this input | Actual consumers and retained boundary | Required migration |
|---|---|---|---|
| Owner facts and publication | Frontend `storeBuildingSemanticExprType`, `storeBuildingSemanticBinding`, `storeBuildingSemanticStmtCompletion`; Resolve/Record `recordSemanticAggregate`, `recordSemanticMatch`, `recordSourceBodySignature`; `prepareLexicalBody` and `prepareGlobalInitializer` cache Result by owner | Frontend `preparedSemanticFacts` validates owner success but returns snapshots of all-owner arrays; Mid/Build `buildParametricMidBody`, `buildParametricMidClosureBody`, `buildParametricMidGlobalInit`; Mono/Call `preparedBodyMatch/Aggregate/Try`, `preparedAccessUseFacts` acquire that result | Seal the complete owner payload once; pass its reader through these actual entry points. Remove each moved global table/index and per-use snapshot acquisition when its final consumer switches; retain required absence rejection and lawful optional absence |
| Source selection and signature validation | Resolve/Preparation `prepareLexicalBodyUncached`: Record(false) → checkGenericFunction → verifyFunctionDeclaration → Record(true), then default/template/constraint/conversion closure. Global preparation has a corresponding record/verify/record sequence. Resolve/Record and Check/Generic contain source selectors | Source templates feed Mono/Call `resolveBodyCallee`, `completeStaticBodyCallee`, `instantiateSelectedCallConstraints`; DeclarationProgram and Mid/DeclarationAccess request lexical preparation | Unify the authority that commits source selection and full compatibility. Keep separate ownership/declaration obligations; do not delete a verifier merely because it participates in the current sequence. Completed consumers take the saved selection, not another selector run |
| Call identity, constraints and evidence | Frontend `findSourceCallTemplateIndex` and private call-constraint state; Check/Obligations `prepareCallTemplateConstraints`, `checkSelectedCallConstraintPlan`, `checkSourceCallArgumentType` | Mono/Call `instantiateSelectedCallConstraints`, `instantiateStaticMemberProof`, final callable preparation; Ir/FinalResolutions `publishFinalCallee` keys by bodyId plus CallSiteKey; Mid/Instantiate `canonicalCallResolution` and LLVM Mid consume that result | Move source operations/constraint ownership into the payload and pass explicit instance/callee evidence. Preserve the existing site identity and final-call uniqueness rather than rebuilding either |
| Body headers, bindings and completion | Resolve/Record `recordSourceBodySignature`; Frontend `sourceBodySignatures` and binding/completion stores | Mid/Build uses `facts.functionSignature`; Mono/Call `preparedBodyReturnTerm` uses `preparedFunctionBodySignature` or a prepared closure signature; Check/Return `checkedSemanticStmtCompletionOwner`; Mono/Call `scanBlockInsts` | Use the payload header and region/binding facts in these readers. Retain construction-time registered signature queries separately. Remove global-table result acquisition, not legitimate declaration queries |
| Globals, closures, defaults and provided origins | Resolve/Global `prepareGlobalInitializer` already keys outcomes by declaration target; Resolve/Record `prepareLexicalBody` resolves authored owner; default construction includes `normalizeMemberwiseDefaultsAt`/`appendOmittedMakeDefaults`; Mono/Call `publishSemanticClosure` retains a source owner | Frontend `preparedGlobalSemanticFacts` and `preparedClosureSemanticFacts`; Mono/Call `sourceFunctionOwner`, `bodySourceOwner`, `preparedDeclarationMatch`; CheckedProgram `initializerResult` aggregates declaration work; Mid global builder uses individual declaration targets | Preserve existing per-global isolation. Give closures/default generators explicit origin keys and retain authored provided-body identity. Replace encoded/sentinel owner routing without using one synthetic aggregate result as success for every child; keep aggregate requests distinct |
| Concrete facts and final emission | Mono/Call `requestFinalBody`, `prepareFinalCallableSignatureInContext`, `scanFinalBodyInstance`, `finalizeCurrentBodyAggregate/Match/Return`, `instantiateValueConversion`, `publishFinalCallables`; Ir final-call/aggregate/try storage | Mid/Instantiate `instantiateCanonicalMidBody` and `materializeCanonicalMidCall`; Backend/Llvm/Mid reads `finalCalleeAt(target.resolution)` and selected parameter/result/conversion records | Preserve the existing source → parametric Mid → concrete Mid pipeline and final selected call representation. The proposed PreparedInstance is its read-only result view, not a parallel typed tree. Descriptor/conversion origin and dependencies remain mandatory |
| Internal fixtures | `prepared_aggregate_source_owner` parses and prepares real function/global/closure owners, tests foreign-owner rejection and prior-reader stability. `recorded_binding_value_compatibility` constructs/registers syntax, records a local, shadows its spelling, then checks saved meaning. Source-owner private reject and Mid CFG fixtures cover different boundaries | Normal suite discovers these fixtures and their output/rejection companions | Migrate each with its assertion intact: normal successful source setup followed by corruption for owner/fact checks; genuine Mid construction for Mid-only controls; builder-level inference tests may use private construction APIs in an appropriate internal module, never public success factories |

Source anchors for the inspection:
[owner snapshots](https://github.com/plew-lang/compiler/blob/2983c47ff7ba0b1d693d656094e9fd0dbeca63dc/src/Frontend.pw#L2478),
[preparation phases](https://github.com/plew-lang/compiler/blob/2983c47ff7ba0b1d693d656094e9fd0dbeca63dc/src/Codegen/Resolve/Preparation.pw#L11),
[Mid source entry](https://github.com/plew-lang/compiler/blob/2983c47ff7ba0b1d693d656094e9fd0dbeca63dc/src/Mid/Build.pw#L3360),
[final source readers](https://github.com/plew-lang/compiler/blob/2983c47ff7ba0b1d693d656094e9fd0dbeca63dc/src/Codegen/Mono/Call.pw#L6081),
[instance construction](https://github.com/plew-lang/compiler/blob/2983c47ff7ba0b1d693d656094e9fd0dbeca63dc/src/Mid/Instantiate.pw#L1341).

### Rechecked Historical Claims

- `sourceCallArgumentType` now passes PriorCallResult.siteKey to
  `sourceSelectedCallResult`; the latter looks up the template and verifies the
  recipe's callSite. The historical ignored-site-key claim does not describe this
  candidate. Preserve positive and wrong-key controls during migration; this
  read does not certify every other result-recipe path.
- `semanticBodyReturnTerm` is absent from the inspected source. The corresponding
  saved-header reader is `preparedBodyReturnTerm`; do not add another helper with
  the old responsibility merely to match a historical task name.
- Individual global declaration result caches and explicit initializer targets
  already exist. The remaining migration is encoded/source-owner routing and the
  stored reader contract, not starting per-global ownership from nothing.
- The global DFS in Resolve/Global examines initializer syntax. Its existence is
  not implementation of the newly adopted transitive async/worker/callback static
  startup plan. That execution work stays separate from this source-checking
  migration; a baseline pass cannot certify the new startup guarantee.

### First Closed Increment

After the fresh cumulative baseline, migrate source owner/header/expression/
binding/completion publication together with their parametric-Mid and final
Mono readers. Acquisition must remain per owner/consumer, with explicit shared
pool access. Preserve aggregate/try/pattern consumers via the same payload reader
in this increment, rather than keeping an all-owner snapshot behind the new handle.
Keep each increment's advertised guarantee exact: until the required operation/
constraint and origin families are also closed, a sealed component is not a
complete CheckedBody or execution token. Each moved component loses its old
authoritative writers/readers in the same increment. Update source-selection
construction as part of the owning call increment, then its explicit and implicit
concrete consumers. No store-only success milestone or permanent dual authority.

A complete removal audit is required in each implementation increment: follow all
references to the changed symbols and remove its old writers/readers. This finite
family inventory locates that work; it is not a claim that every call or negative
language combination has been examined. Baseline outcomes and artifact identity
are retained in meta evidence/worklog; main/seed/carrier promotion is separate.

## Resolution: Design and Restart Prerequisite

Resolved at the design/reconciliation scope. Owner-local storage/API is adopted
and independently reviewed; the cumulative migration matrix above identifies
actual producers, state owners and final readers, and corrects stale historical
claims. The input-fixed [restart baseline](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/restart-baseline/README.md)
uses unchanged compiler `2983c47f`: generation-3 fixed point, formal three-run
median 6.260879 seconds, and the same measured compiler passed the normal suite
(run1415, midcoverage1, midborrowedread1, panic45, reject977, part90, partreject80;
skip/fail0). Both execution handles ended with exit 0 and unchanged inputs.

This closes the prerequisite, not met-si6j or the source/storage implementation.
The recorded 6.260879-second baseline is below the currently user-approved
7-second target; this changes no implementation or validation completion claim.
Generation, dependency and sanitizer gates remain unrun for this baseline.
Next, follow the first closed increment above on the cumulative source, with
per-increment reference/removal audits and applicable validation. Main, seed and
the adopted carrier remain unchanged; the new measured binary is retained as
a baseline artifact, not promoted as the official carrier.
