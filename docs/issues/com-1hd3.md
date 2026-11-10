---
id: com-1hd3
status: in_progress
deps: []
links: [com-nkoa, com-rv7l]
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Connect retained free signatures to call and body descriptors

## Internal completion fixture consumer

The full normal run20261110T100035-test-cad4b5 rejects
function_completion_type_identity at its removed `sameFuncSelector` call.
Fixed W1b and lean both reproduce this obsolete internal API consumer on current
source. Preserve its finite function completion/parameter/result identity
assertions while migrating to the canonical comparison API; do not expose a
compatibility helper or replace the assertion with unconditional success.
com-lm8j mentions this fixture for optional prose only and does not repair its
executable consumer. This is an explicit original signature-work follow-up,
not a value-ABI optimization regression or a passing normal case.

## Guarantee and Finite Work

Registered free-function annotations must reach selected-call ABI types and BodySignature through exact saved parameter/result slots and the original constraints-bearing InstanceEnvironment. The original defect was that readAdmittedSignatureRoot had no production caller while groundedSelectedCalleeReturn/ParameterTypes and recordFinalCallableSignature independently grounded declaration terms. The implementation below replaces that competing path for registered free signatures.

Implement one shared signature-consumption endpoint, consume it at actual call/body publication, preserve body-type result recording/layout scans, and remove the competing source re-query for this registered free path. A missing admitted slot/recipe/proof is Err, never a fallback. Keep synthetic/default helpers and non-free signatures explicitly separate. Preserve async Promise versus logical body result and explicit/omitted Unit without re-substituting caller replacements or proof outputs.

## Required Scenarios

- Sync generic/nested projection parameter and result, repeated identical terms at different slots, actual final-call/BodySignature agreement and native value.
- Missing/foreign proof, constraints, owner/slot and wrong output reject even when a conformance remains searchable; valid recovery restores request state.
- Async annotated/omitted result, explicit/omitted Unit, default-argument helper and no-view free function remain valid in their existing representations.
- Both lowering adapters and check/AOT/lazy consumers use the same retained endpoint; supported gen applicability is recorded, not assumed.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Current Finite Implementation and Evidence

Compiler **f65fa24e** connects saved free signature slots to actual selected-call
and body signatures before caches or ambient grounding can confer authority.
Non-free/synthetic declarations keep their separate path. Actual publication
retains type-result mappings and layout scans; async Promise/body results and
omitted/explicit Unit retain their existing representation.

[Original consumer RED/GREEN](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-consumers.json),
[unchanged-child identity fold](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-identity-fold.json)
and [signature-wide reader](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-batch.json)
retain exact sources, candidates, scenarios and mode limits. The reader validates
one original declaration/environment, then interprets all requested slots with
one recipe-ID memo. Every slot still checks its authored occurrence and saved
proof; equal semantic terms do not confer authority. Empty slots also require
the exact environment. This added refusal has an actual old-source native RED,
followed by rejection and valid recovery in the final13 controls.

Build20261109T111958-build-a2b67a passed. Fresh13 internal,58 preservation,
public check/AOT/lazy and refusal, plus old/new actual helperboundary generator
execution and exact generated source passed. Independent review reconciled all
seven raw result hashes, input deltas,179source/build/candidate identities,
assertions and source responsibilities. A manual legacy adapter uses a primitive
projection; ordinary/public paths retain nested Box coverage. The wrongOutput
control also has witness Self/bind inconsistency, so output-only isolation is not
claimed. Unsupported generic/aggregate async setups are not passing coverage.

## Performance Stop and Resume Boundary

The final formal run **20261109T113003-self-host-195aa0** reaches generation2
fixed point. Samples8.307254/7.743194/7.720560s give median **7.743194s**.
Balanced final formal candidates on the same current source (five each) measure
old7.038477s/new7.716668s; all ten LLVM outputs match. The earlier exact restored
checkpoint is [preserved](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-restored-checkpoint.json).
The diagnostic comparison does not replace the formal median.

The shared identity fold removed redundant node allocation, but the introduced
performance regression remains.
Three grounder-side trials were [discarded with exact patches](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-discarded-trials.json).
Signature-wide batching measured7.846359s/7.810533s in the same development
pipeline (five each), insufficient recovery. Source/profile observations suggest
machine-code/inlining changes in an existing substitution hot path, but neither
the complete cause nor an unavoidable design cost is established.

No clearly low-effort recovery was identified in the local trials. This is not
proof that repair is difficult; the cause and recovery difficulty remain
unresolved. Continue performance investigation rather than deriving the stop
condition solely from failed local trials. A separate guaranteed-indirect ABI
work item is proposed, not implemented. Do not close this child or bypass its
unresolved acceptance by advancing a sibling.

[Final fixed-point, matched timing and fresh candidate controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-batch-final.json)
record the final candidate. This child remains in_progress; parent/goal, full
suites/ASan/G2 and main/seed/adopted-carrier promotion remain uncertified.

## Interruption Checkpoint and Return Procedure

This child can be set aside without discarding or completing it. The semantic
implementation is committed/pushed at **f65fa24e**; later compiler commits through
**e6323fe8** only change records. The saved final evidence identifies all179
product source hashes and candidate **bin/plewc-retained-free-signature-batch-fixed**
(SHA f4c81f5a0ca9a49d3c98ebc933566f76f63c0ec56b541518c11a391a7ccfb879).
Rechecked all179source hashes and the candidate hash on2026-11-09. All owned
validation handles have terminal results. No partially applied product trial
remains; discarded trial patches and reasons are in the linked evidence.

Return in this order:

1. Read this contract and the final checkpoint. Preserve the current retained
   signature implementation and all proof/occurrence refusal guarantees.
2. If source, dependencies, tests or execution inputs changed while set aside,
   run the13 internal signature controls,
   the58 preserved controls and public check/AOT/lazy/refusal/gen controls against
   the new candidate. Earlier results do not certify changed inputs. Test paths,
   scenario sets are retained in the durable checkpoint chain; use the
   [internal fixture execution procedure](../../tests/compiler/frontend/README.md)
   to compile/link/run them. Scratch runners are conveniences, not the sole
   restart authority.
3. Compare old/new compilers on the same latest source under the same pipeline,
   and perform the formal fixed-point/performance measurement. ABI improvement
   alone does not prove the original signature regression resolved. If the target
   remains unmet, investigate the residual cause; do not infer difficulty merely
   from the7-second threshold or count of unsuccessful trials.
4. Reconcile this child's complete scenario/consumer contract and obtain the
   independent completion review before closing it. Only then choose the next
   amjl child (currently com-erlx is the suggested next boundary).

The compiler's unstaged Plew.toml local Syntax path override, generated bin/plewc
and existing pycache directories are not uncommitted semantic implementation.
Do not stage or promote them. Recheck the actual manifest/dependency inputs on
return. Whole-suite/ASan/G2, parent closure and main/seed/adopted-carrier promotion
remain separate. No new ABI task or priority/dependency change is implied here.

The final checkpoint JSON retains the historical stop assessment. The current
difficulty assessment and return procedure in this task supersede that judgment;
the measurements and scoped test results themselves remain valid for their inputs.
