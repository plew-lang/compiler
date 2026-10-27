---
id: com-e713
status: in_progress
deps: [com-5by1, com-ouh2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 2
assignee: Koji Murata
parent: com-jno0
tags: [frontend, verification]
---
# Audit frontend language test expectations and coverage

## Scope

Audit all frontend assertions assigned by com-ouh2:
lexing/parsing, names/visibility, declarations, overloads/generics, type behavior,
expressions/control flow, diagnostics and other currently provided language
surface. The assignment follows assertion contracts, not fixture directory or
prefix. Reuse existing evidence only when scope and inputs match. Unknown claims of unsupported behavior need
contract/implementation evidence, not current rejection alone.

Read relevant spec chapters and frontend design independently of current expected
outputs. Target wrong-reason rejection, weak diagnostic assertions and untested
feature interactions, while preserving the adopted forward-only inference,
ownership and explicit divergence rules. Syntax/standard-library tests can be
language or implementation tests according to what they actually assert.

## Method and Exit

Use the exact batches assigned by com-ouh2 and the rules in com-5by1.
Before starting, split oversized batches under current planning rules; this is
not an open-ended promise to inspect every conceivable combination. Previously
reviewed assertions can be reused only with matching scope and inputs.

For every assigned assertion establish original intent, spec/design oracle,
actual path/mode, registration and a failure that discriminates the intended
contract. Independently derive missing positive/reject and interaction controls
from the contracts rather than filenames. Use known faults or selective isolated
controls for important boundaries, not a blanket mutation-testing framework.
Classify expectation errors, weak/incorrect paths, unregistered tests, missing
controls, unresolved semantics and separately unsupported features. Check the
original intent before recommending deletion, movement or expectation changes.

Route findings and test/runner corrections to concrete finite owners before
closing; follow existing stopping rules and keep this audit separate from actual
repairs. Required follow-ups stay open under their responsible area. Save exact
inventory revision, assertion dispositions, grounds and scoped independent review.
Completion means the assigned finite audit is reconciled, not zero unknown bugs,
all future features implemented or all resulting defects already fixed.

## Reconciled Outcome Subset

[Cross-owner outcome reconciliation](../../../evidence/test-audit/scoped-reviews/outcome-reconciliation.json)
now covers 4 exact primary outcome units here (four internal declaration/interner/span fail-fast outcome units). Normative conditions,
original intent, complete selected inputs and shared runner predicates were read
independently and by the parent. This is source-level audit, not executed compiler
or program correctness and not the separate source-admission units. Existing
finite findings and migration owners are retained; no repair or domain closure.
All other plan units remain this audit's work, with shared reports reused only
within exact matching scopes.

Independent reconciliation review review_audit_inventory_partition matched exact
IDs/owners/hash identities and scoped calculations, found no required correction,
and accepted these source-audit records only. No compiler/candidate/domain
certification, unread-work transfer or fixture/runner repair is implied.

The shared reconciliation also records80 additional runtime-primary outcomes;
these do not increase this task's audited primary count. The six finite new
follow-ups preserve explicit source-admission/package boundaries. Other assigned
units here remain audit work.

## First Source-Admission Batch

[Batch0002](../../../evidence/test-audit/scoped-reviews/frontend-batch-0002.json)
and its [independent review](../../../evidence/test-audit/scoped-reviews/review-frontend-0002.json)
add38 disjoint source-admission obligations. Two prior internal outcomes are
exactly reused, not counted twice. All76 selected source/companion files were
read. This brings this task's inspected primary units to42 (four outcomes plus
38 admissions); the task remains in_progress.

Twenty-two ordinary setups have source-level grounds, nine reference roots
retain current syntax and precision-sensitive dynamic-tier qualifications,
five root panic setups retain their existing ordinary-function migration, and
two Buffer roots exercise current public assoc APIs while factory migration is
planned separately. com-jbau owns the exact nine-root static-alias frontier and
dynamic control investigation; com-58zf owns two constructor operations/three
representatives. No new source rule, arbitrary reject-or-panic PASS, fresh
compiler execution, repair or whole-frontend closure is implied. The independent
review found no remaining required audit correction.

## Remaining Panic Source Admissions

The tail12 source-admission units and independent review are saved in meta/evidence/test-audit/scoped-reviews/frontend-panic-admission-tail.json and review-frontend-panic-tail.json. Together with batch0002, all50 panic source-admissions are reconciled separately from their50 outcome units; exact IDs and parent disposition are in source-admission-reconciliation.json. This task has54 inspected primary units (four outcomes plus50 admissions), remains in_progress, and closes no additional whole batch.

The explicit com-jbau extension adds eight ambient roots to the original nine, preserving the static-rejection versus current dynamic-tier distinction. Existing source migration, internal guard APIs, actual-signal and destructor-attribution owners remain separate. Review found no required correction. No Plew compiler/program execution or repair occurred.

## First Part Source Admissions

frontend-part-0003.json and review-frontend-part-0003.json add36 source-admission units (128 full project inputs/785 lines), with31 ordinary source-shape grounds and5 qualified current/historical roots. Optional.Some(v=...) versus adopted Some(value:T) was found during parent reconciliation, independently confirmed and assigned finite met-2wca; no whole-Std or capability migration was silently transferred. Repeated publication and two manifests retain explicit met-4slo/com-7u8z scopes, old deinit met-2t3l, supplemental partdiamond reason com-ntm8. Reviewer-required qualification wording was corrected and accepted.

Primary inspected count is90 (four outcomes plus86 admissions). Reconciliation of the36 plus three previously audited panic admissions and one span outcome completes exact batch0003. There are eight complete source-audit batches across owners; no new outcome count, execution, repair or frontend closure. Unread assigned units remain audit work.

## Remaining Part Admissions and First Rejection Batch

frontend-part-0004.json / review-frontend-part-0004.json reconcile40 more admissions (153 files/538 lines); frontend-batch-0005.json / review-frontend-batch-0005.json add17 admissions and23 source-rejection units (149 files/674 lines). These complete source-only admission inspection of all93 part fixtures, separate from their93 prior outcome units. Manifest setup and exact generic binder/omitted-bound questions retain finite owners.

New finite source-oracle questions are met-l1u5 (one internal-module versus package-public API closure rejection) and met-bejv (two extension identity/binding assumptions); two bad outer-print reason controls extend com-ntm8 and one enumaliaspartial manifest extends com-7u8z to15. Root-authored API checks do not certify all imported Std internals. Final independent review accepted both finite reports with no required correction. Contextual keyword reference is spec01-overview25, refining a broad report reference to spec04.

This task has170 inspected primary units:4 outcomes,143 admissions and23 rejections. Cross-owner total408/ten complete plan batches. No compiler execution, source repair, whole-frontend or final corpus closure. Remaining negative/batch units remain this audit's work.
