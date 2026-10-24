---
id: com-vkw3
status: closed
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Verify closure global default and provided source-domain ownership

## Boundary

Phase 3D / D2. **Bounded source-owner verification.** Parent criteria: 2, 3, 7, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Global.pw`; `src/Codegen/Resolve/Record.pw`; `src/CheckedProgram.pw`; `src/DeclarationProgram.pw`.

Construct a five-row owner map: closure body versus creation, per-global initializer versus synthetic all-global body, default declaration/slot, provided lexical body, generated/synthetic body origin. Trace reused ExprIds to successful readers and source signatures without using active Cursor/global sentinels as identity.

## Exit and Evidence

For each row give actual key/producer/reader and existing or minimal distinguishing control. Cover shared ExprId across owners, foreign/missing/failed owner, retained reader and construction-time callable registration without demanding a prepared body. Keep closure runtime environment/copy/drop and startup effect/SCC planning with their phase-four owners.

Existing starting controls: `source_typing_owner_requests`, `default_argument_call_templates`, `global_call_constraint_evidence`, `prepared_binding_source_owner`, `retained_provided_body_constraints`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Producer-to-consumer Reconciliation

Audited production: `c1b731bd` (D1 source-state admission). This map describes
existing authority rather than a new source-domain implementation.

| Domain | Key / producer | Published reader and final use | Distinguishing controls |
|---|---|---|---|
| Closure creation / body | `Resolve/Record.recordExpr` saves creation in its parent, calls `publishSemanticClosure` and `registerClosureFactOwner`; body facts use `Closure(exprId)` with the registered lexical parent. The source request checks nested obligations and `finishSourceFacts` propagates its success/failure to children. | `preparedSemanticClosureAt` reads the successful creation owner; `preparedClosureSemanticFacts` reads the distinct body payload. `ensureParametricMidClosureBody` admits that payload; Mono's `requirePreparedClosureInstance` validates the frozen body/environment against the creation descriptor. | `source_closure_publication`, `source_typing_owner_requests`, `global_closure_call_constraints`, C6 descriptor controls. |
| Individual global / composite | `prepareGlobalInitializer(target)` owns `Global(target)` and restores the request Cursor. `prepareGlobalInitializerUncached` checks that declaration alone. | `preparedGlobalSemanticFacts` / `preparedBodyFacts(..., globalInitializerTarget)` require that target. `DeclarationBodyRequests.globalInitializer` first admits every individual result; Mid's composite builder re-admits each actual global payload. The all-global executable sentinel alone grants no source authority. | `global_call_constraint_evidence`, `prepared_binding_source_owner`, `prepared_body_expression_owner`, `mid_global_initialization_ownership`, D1 `mid_source_owner_admission`. |
| Parameter / field default | `prepareDefaultArgumentGenerators` and `prepareFieldDefaultGenerators` allocate independent function owners, retaining `DefaultGeneratorOrigin.Parameter(function, slot)` / `.Field(structure, slot)`. Reused authored ExprIds are navigation, not an all-owner type table. Provided aliases share the canonical parameter generator; binder projection uses ParamIds. | Ordinary `prepareLexicalBody(generator)` publishes its signature/facts. `recordDefaultArgumentCall` saves the selected generator and environment; ordinary Mid/Mono callable preparation consumes them. The lexical namespace is retained without aliasing generator source facts to the parent. | `default_generator_source_publication`, `default_argument_call_templates`, `default_generator_shared_owner`, `default_generator_environment`, `record_literal_default_owner`, `mid_default_enum_owner_return`. |
| Authored provided body / placed callable | `semanticBodyOwner` validates explicit `lexicalOwnerFnId` and shared body; `prepareLexicalBody` canonicalizes the source request. Placed receiver/method binder environments remain distinct. | `preparedFunctionSemanticFacts` and source call keys read the authored payload. Instance preparation retains the selected callable, bound evidence and lexical receiver. No new source owner is inferred from equal spelling or active Cursor. | `retained_provided_body_constraints`, `trait_provided_private_owner_helper`, `default_generator_shared_owner`, B3/C3 environment and receiver controls. |
| Generated executable body | `BodyOrigin.Callable`, `.ExistentialWitness(resolution, member)` and `.ClosureEnvironmentDrop(closureBodyId)` distinguish executable origins. Defaults remain ordinary source functions with explicit declaration/slot provenance. | `CheckedProgram.declarationRootsForBody` uses the retained witness member target or capture destruction roots. Generated code does not acquire arbitrary source facts through the current Cursor; ordinary source-backed paths still require admitted facts. | C6 descriptor/environment origin controls; global/default/provided controls above. Runtime environment destruction and startup effect/SCC planning remain phase four. |

Signature registration is not source preparation success: `lowerDeclarations`
registers callable roots, `prepareFinalCallableSignature` can publish a callable
signature without requesting its invalid body, and `preparedSemanticFacts`
rejects absent/failed owners and bodyless registrations without a payload.
`callable_signature_demand` and `source_typing_owner_requests` distinguish these
states. Retained reader/session and foreign-owner controls belong to D1 and are
reused only with their recorded scope, not as new whole-candidate gate results.

## Outcome

Closed after independent completion review of `f6039d8a` plus the new internal
fixture's public import correction. No runtime logic changed: only the stale
global source-owner comment was corrected. The existing
`default_generator_environment` fixture now constructs real primitive/Unit,
trait Self/receiver and bound identities; its original nine-line output is
unchanged. Its earlier setup failure is retained separately.

Saved receipt: meta
`evidence/existing-feature-conformance/source-owner-facts/phase3d-source-domains.json`.
Fixed carrier `bin/plewc-phase3d-owner-admission-fixed`, SHA256
`434e711ea2eddeaa5cb4070bce88d69f84b9b2e3a421f9056fd48d2374c27f5f`,
compiled/linked/ran the existing 15 controls successfully. The new default source
publication control passed after correcting its import to `/Mid/Build`. Its
first import failure remains a failed run; no unexecuted test is counted.
Input fingerprints were unchanged for every run. Sessions 20625/18927/14206/57159
were recovered through their actual exit codes.

Independent reviewer `/root/body_receiver_completion_review` verified the five
rows, current fixture fingerprints and all nine receipt-file hashes, and accepted
bounded completion without remaining blockers. The only difference between the
accepted existing15 run and the new-control success was that new fixture's
public import correction. `/root/associated_context_completion_review` separately
traced the environment fixture's original purpose and repaired its invalid setup.

D1 retained-reader/foreign-session and C6 descriptor controls keep their recorded
scopes. No new performance claim: latest runtime production remains `c1b731bd`,
whose saved generation2 fixed-point median is 6.830579 seconds. D3/D4, runtime
closure/startup planning and final G2a/G2b gates remain separately owned.
