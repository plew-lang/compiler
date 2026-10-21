# Contract Navigation Cleanup

**Status: Under discussion.** Editorial review item E1; tracked by
[met-m7wx](../../issues/met-m7wx.md). This is a bounded cleanup plan, not a new
architecture. Current progress is in the meta
[progress document](../../../../agents/compiler-design-progress.md#再レビュー指摘の具体化).

## Scope and Preservation Rules

The reference must make a change's owner and consumers easy to locate, without
requiring reconstruction of legacy implementation details. Preserve stable
contracts, necessary rationale, rejected alternatives and decisive evidence.
Move current-state details to their owning issues; Git preserves obsolete text.
No source acceptance, runtime guarantee, public ABI or standard-library API changes
are part of this work.

## Work Items

| Item | Current location | Proposed destination/boundary |
|---|---|---|
| Legacy row/count/sentinel and migration-state prose | Frontend Handoffs, especially current representation and migration sections | Keep logical invariants there; link physical storage to Checked-body Storage and put changeable migration details in existing implementation issues |
| Stale reconciliation status | Frontend Handoffs and other references to pending reconciliation | Reconcile with met-j9mv and worklog; replace duplicated status with a link, not another synchronized status field |
| String decoding discoverability | Syntax, Declaration and Execution Audit, Mid Entry Audit | Add direct links to the existing common decoder contract and distinguish lexical/semantic validation from physical representation |
| Generated-C explanation of opaque handles | Spec15 opaque-handle paragraph | Describe the adopted LLVM mechanism while preserving nominal distinctions, one-word ABI and external lifetime/ABI responsibility |

## Checks Before Editing and Completion

1. Classify each passage as adopted contract, rationale, implementation evidence,
   current status or obsolete mechanism. Identify the authoritative destination
   before deleting or moving it.
2. Preserve source paths/revisions and actual evidence limits where still needed.
   Do not relabel an unimplemented guarantee as implemented or close an issue
   because its paragraph moved.
3. If literal-decoder ownership reveals an actual semantic disagreement, stop
   calling it editorial and record the decision separately.
4. Re-run the change-location exercises for a string escape and a checked-body
   reader; confirm that decision owner, final consumer and validation are findable.
5. Check local paths/anchors, references from source/operations and stale wording.
   Language-surface behavior changes require a separate decision, not a prose fix.

Finish by retaining the corrected stable material in its authoritative home and
recording evidence in the issue. Remove this active plan after incorporation.
This cleanup alone does not close R1/R2/R3, adopt the first edition or certify
implementation conformance.
