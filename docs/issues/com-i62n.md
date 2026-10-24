---
id: com-i62n
status: closed
deps: [com-m0bf, com-uruz]
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
this task addition. The allocation evidence precedes the implementation and partial validation below.

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
This certifies planning/classification only. This allocation review does not certify implementation, fresh controls,
independent completion review or final G2 gate obligations.



## Implementation Under Validation

Production **d05a153d** removes optChainResultRef and its raw Optional/child
construction, and removes Record's pre-child legacy result capture. ExprType's
uncommitted OptChain construction and Record share chainStageResultRef. Record
checks the base/continuation before saving the complete stage as the source
expression term and passing it to ChainSite/generated calls. The generated
MatchExpr uses ordinary source checking. **7aeda7d5** defers an unowned carrier
before legacy declaration-index readers; it does not admit a missing identity.

Fresh2 passes the new source-result/return/stage and Identity conversion checks,
including rigid generic and projected T#Source.Output children, direct/block/if,
nested terms, retained-owner aliases, missing carrier, registered foreign carrier
and same-spelled foreign child controls. Actual optional-chain execution covers
Some/None, continuation effects, two concrete projection results and existing
owned payload cleanup. Foreign checked-body reads are rejected. The unrelated
ordinary projected_call_chain and trait_subject_chain are supplementary controls,
not evidence of ?. projection handling. The saved source result goes through
conversion/rewrite and both existing worklists to BodySignature/CallResolution,
Mid match/call construction and midCanonicalEmitDirectCall; no final reader
performs owner recovery.

Independent review finds no remaining i62n-specific static or projection-control
blocker. The interrupted required closure suite still prevents final recognition,
as detailed below. New controls/corrections are **3b9a2f9c / 38b33f37**; source and
binary hashes plus actual successes/failures are in the linked durable receipt.

## Current Validation Hold: Custom-factory Source Receiver

Fresh2 on production **7aeda7d5**, fixture checkpoint **38b33f37**, passes full
compiler source checking and module4. The scoped runs retain their actual
successes but do not complete: string_interpolation exposes an ownerless Options
factory receiver already saved before body admission. The independent review
classifies a separate source/context producer, now assigned to
[com-uruz](com-uruz.md). This is not permission to widen this task or recover the
owner in final readers. See
[C3 scope stop and proposed allocation](com-m0bf.md#scope-stop-unassigned-custom-factory-source-receiver)
and meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-chain-factory-scope-stop.json. This task remains in_progress; final
completion review and G2 gates are still required.


## Bounded Completion

The original raw Optional source-result reconstruction and provisional pre-rewrite capture are removed. Checked child/stage results supply both committed source/conversion endpoints and the generated ChainSite/calls. Actual optional-chain projected and rigid children, Some/None, effects and existing ownership controls pass.

Production **dd393d54**, control update **956902ad**, fresh4 SHA256
**df71fc281246486b13f603d273bdede62a985a3d023964ed0f8669b7ea637839**.
Standard build **20261024T075946-build-c9e973** and fresh full compiler-source
checking pass. Combined native90/reject27/module9 controls pass. The prefix
run remains false after native89/reject23 success and a diagnostic-golden
mismatch; the one updated internal diagnostic and remaining three rejects
pass separately, as does the associated-owner positive. Production source,
std and carrier match; the only changed prefix expectation is that golden.

Canonical receipt and producer/consumer/removal mapping: meta
**e6210277**, evidence/existing-feature-conformance/source-owner-facts/
phase3c-source-receiver-closure.json. This preserves initial failures, exact
input/carrier hashes, individual outcomes, permitted diagnostic correction,
source check, and independent final reviews.

Independent completion review by **/root/body_receiver_completion_review**
recognizes this finite task as complete, with no blocking findings. E registers
optchain_projected_result; registration is not successful sanitizer execution.
The native String projection fixture uses a literal, not a separate dynamic
heap-allocation measurement. Final G2a fixed point/performance and G2b full
normal/gen/deps/LLVM22 ASan-LSan, C4 onward and parent phase-three completion
remain open. Main, seed and adopted carrier are unchanged. Earlier holds above
retain historical observations and are superseded by this bounded outcome.
