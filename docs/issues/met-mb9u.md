---
id: met-mb9u
status: in_progress
deps: []
links: []
created: 2026-11-25T17:20:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, control-flow]
---
# Retain loop-transfer target refusals through owned diagnostics

## Contract and scope

The source checker owns break/continue target selection. Preserve the actual
no-loop or while-condition barrier refusal from its producer through failed-body
cache and owning compiler/CLI consumer. Correct check/AOT/reachable ORC rejection
must be Source; Raw/synthetic/foreign/malformed queries remain non-Source.
No spelling/message/offset-only classification or fabricated successful target.

References: spec/11 while-condition transfer rules; design/body-checking source
exit contract; design/diagnostics producer ownership. Current Source-only negative
failure evidence is [residual survey](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-after-member-admission-survey.json).

## Finite implementation plan

1. Trace actual sourceTransferLoopTarget and Verify/Stmt paths, statement origin,
   request/owner acquisition and failed-body retention using real source inputs.
   Identify Raw verification separately. pushStmt currently has no Lower origin
   receipt; do not infer authored identity from statement shape or offset alone.
2. Before product repair, establish RED on the fixed dde345e4da6d carrier for
   actual target refusals and GREEN on valid targets. A private producer test
   must assert actual traversal and source/Raw boundaries, not rendered text.
3. Bind a real Lower statement identity/request/owner to the actual control-region
   selection result. Keep successful SourceTransferFact and failed receipt
   distinct; do not mint Source in offset/isContinue helper or publish dummy target.
4. Retain typed failure to final consumer/cache/retry. Prepared Verify consumes
   saved success/failure instead of independently selecting by depth/condition;
   missing/foreign/damaged facts stay non-Source. Preserve legal target identity,
   source completion and Mid cleanup semantics. Reassess scope/dependencies only
   if investigation finds a separately owned consumer not covered by this plan.

## Scenarios and completion

- Existing eight while_condition_{plain,binding,chain,nested_if}_{break,continue}
  cases: source rejection in check/AOT/reachable ORC; unrequested ORC remains lazy.
- Ordinary no-loop break and continue, closure transfer unable to escape to an
  enclosing loop, function/closure ownership and owner-boundary reset.
- Valid body break/continue and condition-local new loop, nearest nested target,
  ordinary/conditional loops and retained success SourceTransferFact unchanged.
- Raw queries, synthetic statement, mutated identity/operation/span, foreign
  session/root/owner, failed builder/retry/cache and final owned Source adapter.
- Confirm RED is actual target defect, no weakening of existing valid controls;
  fresh candidate, applicable regression/performance<=7.5s and independent review.
  Consult workflow gate granularity; do not rerun unrelated whole gates per probe.

## Excluded and task relationships

No new source semantics, give/return rejection migration, result typing,
unreachable policy, analytical loop warning, unique cleanup or Mid redesign.
com-fuo8 owns broader completion/success exits; com-0ssn owns following-statement
versus loop-warning policy. Preserve their guarantees, without making their
entire epics prerequisites. This is a finite child of com-yeua, not parent closure.

## Plan review

qualified_member_plan independently accepts the slice and size. The plan includes
its requested statement provenance boundary, separate success/failure, fail-closed
Verify consumption, no-loop RED and closure-target contrasts. Implementation has
not started; investigate reachability/provenance before choosing storage details.
