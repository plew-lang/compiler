---
id: com-za40
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T11:42:57Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, backend]
---
# Narrow finalized callable LLVM body registration and emission inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/prepared-body-pipeline-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-prepared-body-pipeline-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Only genLlvmFuncBody, declareGenMethods, declareOneGenMethod, emitOneGenMethod, emitGenMethods, ensureFinalGenMethodBody, declareGenFns, emitOneGenFn and their 12 actual call expressions in the pinned46-call table. Other groups own their own listed APIs. genMethSlotFor remains justified and outside repair; prepareMidExecutable mainC/com-e1ea, initializeProgramArguments mainC/com-9h5s and mainFunctionTypeJ stay with prior owners.

Per-entry finalized semantic/body/Mid/source-ready/type/layout/evidence readers plus only reached destruction-alias memo, runtime symbol interner/bytes and conditional prepared-facts acquisition services. The coherent LlvmCtx physical owner keeps matching module/context/builder/ABI/layout/local/global/ambient/async/registry/queue state; no field-count decomposition. No source checker, semantic preparation/publication, mutable whole Comp/Arena/MonoWork hidden through callback/facade/unwrap. Read hints are not writers and preflight-only providers do not acquire or intern runtime symbols.

## Completion
Task-start TDD/refactor controls, relevantbehavior/unsupported/failureprefix/nativecontext/queue/ABI/default/capture/global/async boundaries and independentstructuralreview ofreal signatures+allactualconsumers, nofullComp retainedviaunwrap/capture. Preservefixedpipeline/categoryorder, noASTfallback, exactsame-sessionfrozenidentities andtypedsourceinputs, runtimeinterner/alias/acquisition andnativeprefixes. Existingerror/nativefunction/ambient success-only restore facts areobserved; algorithm/allABI/native-safety changes requiretheirown scope ratherthan silently claimedcorrect here. Producttests/GREEN notrequired forinvestigationclosure andnotclaimed. Change only this group real signatures and all its exact consumers. Coordinate shared physical/prepared/typed ownership/input repair owners without duplicate API ownership. Preserve None/false/preflight-reason/Err distinctions, exact defaults and constant-false async provider branch, native prefix and emitted/requested admission markers, bounded traces/coverage, source hint versus successful measured acquisition, no native/source AST fallback, source/session/owner/BodyInstance/ABI/capture/proof and module/context lifetimes. Original null affected subsets mean the whole exact family source range, not zero APIs. Existing observed success-only physical ambient restoration is not certified as general safety; any alteration needs the owning confirmed issue and controls.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Product repair/execution/GREEN not performed in this audit; no language/source-selection/typechecking/worker/native-ABI algorithm redesign, source body/destruction producer queue or Mid passes introduced into prepared consumers. Read-only metadata and coherent native state need not be reduced to scalars. No deletion of existing helpers or stricter source acceptance based on an input audit.


