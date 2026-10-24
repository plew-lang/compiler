---
id: com-i62n
status: in_progress
deps: [com-m0bf]
links: []
created: 2026-10-24T06:22:08Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve complete source types before Optional-chain rewriting

## Boundary and Evidence

Required C3 producer/read repair, parent criteria **1, 2, 3, 8**. Entry:
Resolve/Locals::optChainResultRef;
Resolve/ExprType::constructExprTypeWithChainHole's OptChain arm;
Resolve/Record::recordExpr's pre-rewrite OptChain capture;
Mono/Call::chainStageResultRef / rewriteOptChainToChainMatch and their saved
ChainSite consumers. This closes one chain-expression source-result boundary,
not every result recipe or conversion family.

Contracts: [semantic identity](../design/types-and-evidence.md#2-semantic-terms-and-identity),
[context and commitment](../design/body-checking.md#3-contextual-inference-and-commitment),
and [frontend publication/consumption](../design/frontend-handoffs.md).

At **ce98f5f4**, fresh62a36bc4 passes sourcecheck, module native4 and focused
native19, then optional_chain fails with "source value does not satisfy the
required conversion". Pre-Buffer fresh5 fails on the identical source; nqjd's
fixed8e0f0329 succeeds. Independent review traces an earlier, separate source
producer: optChainResultRef appends an unowned Optional[U] and reconstructs a
missing continuation term from its head spelling; recordSemanticExprInfo saves
the nonzero ref before expected-type/conversion checking. The later canonical
stage/registration path cannot repair that already committed fact.

The [C3 finding](com-m0bf.md#scope-stop-unassigned-pre-rewrite-optional-chain-producer)
and meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-synthetic-buffer-partial.json own the trace, binary/input hashes,
same-source comparison and independent scope verdict. User approval authorizes
this task addition. No fix or successful validation of this producer is claimed.

## Finite Actions

1. Trace the pre-rewrite result through source recording and the existing chain
   rewrite. Preserve one complete selected carrier and continuation child before
   committing the expression result. Replace optChainResultRef's raw Optional
   head/child reconstruction with the appropriate existing canonical term/stage
   path. Keep nominal owner, all carrier arguments, lexical ParamId,
   projection/view provenance and the explicit ChainHole input. Do not decide
   Optional identity by spelling or create a second chain applicability solver.
2. Move or remove Record's provisional pre-rewrite TypeInfo capture as necessary
   so it cannot publish an unowned nonzero result as a committed source type.
   A genuinely unresolved dependency remains private/deferred until ordinary
   completion; it is not Unit, successful unknown, or a fabricated nominal.
   Share the semantic result authority across original OptChain and generated
   MatchExpr rather than fixing the two shapes independently. Preserve source
   evaluation order, short-circuiting, ownership and forward-only inference.
3. Follow the same saved result into recordDeclarationConversion / pending
   completion and checkDeclarationConversionEvidence, then saved ChainSite,
   selected generated calls, declaration/executable worklists, BodySignature /
   CallResolution and actual Mid/LLVM consumption. Retain existing canonical
   chainStageResultRef/registerChainSiteInsts behavior; final readers must not
   reopen syntax/name lookup or change a committed conversion endpoint.
4. Remove the paired raw append, pre-rewrite replay and duplicate result
   authority that the migration replaces. Record exact removals and retained
   representation-only adapters. Missing/foreign owner must remain rejected;
   do not weaken equality, evidence admission or the existing failing test.

## Exit and Controls

- Record producer -> committed source result/conversion -> rewrite -> explicit
  instance environment -> actual Mid/backend consumer and removed competing
  sites. A new checker, later correct stage or passing runtime alone is not
  completion; inspect the earlier saved source result and conversion endpoints.
- Reuse optional_chain, chain_generic, optchain_generic_method,
  optchain_multiparam_chain, projected_call_chain and trait_subject_chain.
  Cover direct/block/if results under the same available context, chained and
  nested nominal children, aliases/same-spelled foreign owners, rigid/projected
  children and missing identity/dependency controls. Do not broaden inference
  or unsupported Chain/unique behavior to make a test pass.
- Keep Some and None paths, continuation side-effect count/short-circuiting and
  owned-payload cleanup observable. Reuse optchain_place_arc and
  temp_optchain_deinit where applicable; register new ownership paths for the
  existing final sanitizer gate if the repair changes their implementation.
- Build a fresh compiler; run full compiler-source checking, decisive native /
  reject controls and the interrupted associated-context/body-receiver suite,
  including required module controls. Pin source/carrier/input hashes, actual
  execution and exact failure diagnostics. Independently review completion.
  Current partial native19/module4 evidence does not establish this repair.
- Observe the active goal's compile-time regression rule. Formal fixed-point /
  median below 7s and full normal/gen/deps/ASan-LSan gates remain under G2a/G2b;
  this bounded task cannot waive or claim those unexecuted final gates.

## Dependencies and Responsibilities

C3 classification/assignment precedes this repair and does not depend on its
implementation. The repair blocks qbwg, fyxe and 6paa's interrupted required
closure controls, the met-6e6k area and G1 evidence admission. Reuse their saved
WIP implementation without depending on those tasks closing first. D4 remains
transitively blocked through its existing 6paa/qbwg dependencies.

qbwg retains Buffer construction and its pending qualifiedConstruction sentinel
guard/control. nqjd's listed late nominal producer changes and historical
evidence remain closed within their reviewed scope; this missing source path is
not retroactively folded into them. C4 owns the complete recipe-variant audit;
C5 owns conversion-family endpoint/proof admission. This task fixes the chain
source endpoints they consume, not their general verification/API design.
No new language semantics, ABI, runtime, generic capability, adopted carrier,
main/seed promotion or global type-checker redesign is in scope. If a larger
independent repair or undecided semantic choice is necessary, apply the normal
bounded-task stop condition before expanding.

## Task Definition and Allocation Review

Independent read-only review by /root/body_receiver_completion_review inspected
this task-creation diff on compiler base **7af9781f**, the current source trace,
C3 inventory amendment, work routing and all issue dependency targets/edges.
Verdict: **task definition/allocation appropriate; C3 reclassification complete;
no blocking findings**. The source-result -> conversion/rewrite -> final-consumer
boundary is finite and distinct from nqjd/qbwg/6paa/C4/C5. There are no missing
targets or dependency cycles; D4's transitive prerequisite holds.
This certifies planning/classification only. The task remains open and
unimplemented; implementation, fresh controls, independent completion review
and final G2 gate obligations are not certified by this review.

