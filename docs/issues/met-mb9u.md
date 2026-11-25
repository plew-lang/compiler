---
id: met-mb9u
status: closed
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
Verify consumption, no-loop RED and closure-target contrasts. The initial plan precedes implementation; implementation evidence follows.

## Investigation and fixed-candidate RED

Fixed dde345e4da6d: CLI75 modes,60 expected Source-ownership REDs with the
correct exact target diagnostic and Unclassified domain;12 unused ORC and3
valid-condition-local-loop controls pass. Private direct Record entry reaches
the real while-condition refusal but sourceFailureHasOwner is false. It aborts
at that first assertion; the other private cases are not yet exercised.
[Saved RED and runner](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/red.json).

Lower has no statement receipt. A receipt plus the current builder does not prove
that the statement belongs to that invocation or that the active control stack
represents its position. Establish actual membership/ancestry on the refusal
path only; retain that structural path in the private event so final consumers
validate saved identities without another whole-body walk or target selection.
Exclude nested closures when locating a statement under a function/global root.
Use common control-edge metadata where Record and ancestry traversal need the
same while-condition/loop-body boundary, rather than duplicate target semantics.
Successful target selection remains source-owned and unchanged.

Verify is not uniformly post-publication: ordinary/global uncached preparation
runs Verify while the owner is Active/Building. A narrow transfer consumer reads
that existing builder, reads the retained reader for Succeeded, propagates Failed,
and treats missing/foreign transfer under a recorded owner as internal handoff
failure. Only a genuinely absent owner lifecycle uses non-Source Raw verification.
Do not use missing statementOwners or a new mode Bool as the Raw discriminator.
Independent source review confirms this is within the task, not a Verify-wide
API redesign. The helper stage below precedes the completed integration described afterward.

## Helper evidence and retained-path contract

Direct Syntax/legacy break/continue lowering now retains an append-only private
receipt. Its serial identifies the receipt, not arbitrary Stmt mutation history;
kind/offset/span/current receipt are checked. Synthetic pushStmt cannot mint it.
Refusal-only structural ancestry finds the unique invocation path without crossing
nested closures. Record and ancestry share while/for control-edge metadata.

Independent review found that selected-child equality alone missed a changed
parent range. A real native RED extends the root range while preserving its
selected child. Path links now retain a narrow variant/child/range descriptor,
and validate owner/root binding plus saved descriptors/edges without another
body walk or target selection. The RED is GREEN. Whole parent AST values and
pool contents are not copied into the proof.

Native controls cover real functions, closure and global roots; foreign body,
synthetic/mutated transfer, body replacement, duplicate/range/cycle and parent
variant/condition-body changes. Normal condition-local loops still prepare
successfully. [Helper evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/helper.json).
The consumer verifies the retained path, not global uniqueness/cycle absence
after unrelated off-path edits. The admission walk establishes those properties;
normal processing must not rewrite a failed owner body afterward.
## Producer and lifecycle integration

Typed target refusal now retains the verified Lower receipt, owner/root and path
in a private event. Successful targets do not allocate failure diagnostics or walk
the body. Verify consumes Active/Building/Succeeded facts, propagates Failed and
rejects damaged handoff; only absent lifecycle uses Raw depth verification.

Actual REDs exposed binding-condition metadata omitted by Record and failed
closure parent lookup after builder disposal. Shared condition-edge metadata and
producer-sealed owner correspondence repair these causes. Native GREEN covers
all eight condition refusals, no-loop cases, cache/retry, foreign/synthetic input,
retained targets under contradictory Verify cursor, malformed lifecycle readers,
finished closure/global failure and preparation of another owner afterward.
Independent source review reports no further confirmed in-scope violation.
[Integration evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/integration.json).

The expanded fixed-carrier CLI111 modes establish91 ownership failures and20
controls. Fresh candidate0663011b builds successfully and passes all111 target
controls plus108 qualified/45 named-declaration regression controls with unchanged
inputs. Formal run20261125T184249-self-host-d731c8 reaches generation2 fixed point;
median7.447430s is within7.5s. Tool and successor hashes were independently read
and compared. [Candidate](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/candidate.json),
[formal](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/formal.json).
Independent guarantee/test review found no remaining mandatory gap apart from
whole-suite reconciliation and its final review at that stage.

## Completion

Whole run20261125T185842-test-f4334c completed with invariant inputs, no worker
failure and3313 identical-source cases. No new failures; thirteen loop-refusal
cases resolve. The effective baseline277 falls to264 (physical prior278 also
includes the already-reconciled Array.count golden). [Whole evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/whole.json).
The formal measured carrier f329fa419735, retained with frozen std, passes111
additional target controls. Independent final review certifies this finite repair
at0663011b; no in-scope unresolved violation or mandatory guarantee gap remains.
No main/seed promotion or parent/phase3 completion is implied.

Superseded helper/initial producer payloads totaling569121277 bytes were removed
after evidence preservation. Snapshots/results/diagnostic traces and decisive
final probes remain; latest264 unresolved whole cases, fresh build, formal,
carriers and backend archive are retained for follow-up/reproduction. [Retention](../../../evidence/rejection-domains/diagnostic-domain-implementation/loop-transfer-refusals/retirement.json).
