---
id: com-qbwg
status: in_progress
deps: [com-m0bf]
links: []
created: 2026-10-24T05:12:48Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve Core Buffer identity in early and late synthetic construction

## Boundary and Evidence

Required C3 producer/reader repair, parent criteria **2, 3, 8**. This is one
dual-stage synthetic constructor, not a general TypeInfo, body-key or inference
redesign. Contracts: [nominal identity](../design/types-and-evidence.md#2-semantic-terms-and-identity),
[construction and publication](../design/compiler-state.md#4-construction-publication-and-consumption),
and [frontend handoffs](../design/frontend-handoffs.md).

At source **39c3e27f**, Lower/Types::synthBufferNew always appends an ownerless
Buffer[elemRef]. Lower/String::beginStringInterpolation calls it before ordinary
declaration resolution; Resolve/Record::synthEmptyDict calls the same helper
after publication for keys, values, hashes and buckets. Recording a Core
namespace use does not resolve a term appended after the declaration batch.
The fresh compiler rejects associated_literal_signature_authority at Core.pw:797:
actual Buffer[U64] decl0 versus selected Core Buffer declaration53232.
The source check and four module controls pass; this mandatory native control
fails and the remaining focused cases are unexecuted. This is a missing producer
authority, not evidence that receiver identity checks should be relaxed.

Evidence and independent scope review:
[C3 finding](com-m0bf.md#scope-stop-unassigned-late-synthetic-buffer-producer),
meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-receiver-producer-scope-stop.json. The user approved task addition after
that stop; no producer code fix or successful repair validation is claimed here.

## Finite Actions

1. Classify the two call phases explicitly at Lower/Types::synthBufferNew,
   Lower/String::beginStringInterpolation and
   Resolve/Record::elaborateDictionaryValues -> synthEmptyDict. Preserve early
   selected Core-module provenance until ordinary declaration resolution. Do not
   treat absence during construction as a successfully published nominal term.
2. For post-publication construction, obtain the fixed Core Buffer declaration
   through existing declaration APIs (Codegen/Decl::declaredTypeRef or the
   applicable explicit-domain entry) and retain the complete elemRef, including
   its nominal owner, ParamId and views. Use the existing phase/publication
   authority; do not add an independently mutable second readiness flag. Missing
   Core identity after publication is failure, not a name-only success.
3. Pass the resulting receiver through SyntheticCallSite.receiverTerm and the
   saved complete signature into both declaration and executable worklists,
   body instance environment/key, BodySignature and final callee admission.
   Trace the actual CallResolution.calleeBodyId -> Mid -> LLVM direct-call/body
   consumer. Reuse the retained receiver/dependency work at 39c3e27f; do not
   require com-fyxe or com-6paa to close first, creating a dependency cycle.
4. Remove the late raw-TypeRef construction lane and any paired recovery that
   this repair replaces. Keep legitimate early construction and its ordinary
   one-time publication path. Do not mutate published declaration facets,
   globally stamp by spelling, recover owners in final readers, weaken equality
   or relax the failing fixture. D4 retains the separate whole-facet API audit.

## Exit and Controls

- Record exact producer/publication/reader changes and every synthBufferNew
  caller's phase/disposition. If the boundary requires a larger independent
  redesign, apply the bounded-task stop policy rather than silently expanding.
- Add internal early-before-resolution and late-after-publication controls:
  fixed Core owner, complete nested/ParamId/view element retention, same-owner
  reuse, unrelated same-spelled Buffer/element separation, and missing/foreign
  owner rejection. Verify ordinary early resolution supplies the expected owner
  without changing previously published facets.
- Execute native source controls for String interpolation and Dictionary
  construction (all four synthesized buffers), including shadowed Buffer names
  and generic/nested elements. Inspect the saved synthetic receiver/signature
  and both worklists, then execute their final native consumer. A standalone
  term-equality control or a new verifier alone is insufficient.
- Build a fresh compiler and run full compiler-source checking. Rerun the
  currently failing associated_literal_signature_authority, the scoped
  associated-context/body-receiver normal and reject controls, and the four
  module controls; retain exact source/carrier/input hashes and results. Keep
  internal corruption failures distinct from source-language rejects.
- Obtain independent completion review before closure. com-fyxe and com-6paa
  retain their own final evidence/review obligations; their previous partial
  success is not upgraded by this task. Formal fixed point/median below 7s and
  full normal/gen/deps/ASan-LSan gates remain mandatory under G2a/G2b. Investigate
  observed compile-time regressions under the active goal's rule.

## Dependencies and Scope Limits

C3 classification reconciliation (com-m0bf) precedes this repair. Its closure
does not require this implementation to pass. This repair is a required
prerequisite of com-fyxe and com-6paa completion, the met-6e6k area, D4 facet
verification and G1 final evidence admission. com-nqjd's already reviewed bounded
closure stays unchanged; this newly assigned entry is not retroactively folded
into that task. No new language semantics, runtime ABI, global nominal search,
new generic capability, main/seed promotion or adopted-carrier change is in scope.

## Task Addition Review

Independent read-only review by /root/body_receiver_completion_review inspected
the task-creation diff on compiler base **9945f97e**, the C3 inventory amendment,
all required dependency edges, phase-three routing and meta worklog.
Verdict: **task addition appropriate; no blocking findings**. The same-constructor
early/late boundary and producer-to-final-consumer exit are finite; there are no
missing dependency targets or cycles. nqjd's existing closure, C3 reconciliation,
the two in-progress repairs and final G2 gates remain distinct.
This certifies the task definition and allocation only. C3 classification
reconfirmation and this repair's implementation/validation/completion review
remain outstanding.

