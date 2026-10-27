---
id: com-ntm8
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, diagnostics, verification]
---
# Strengthen scoped frontend rejection reasons and arity path controls

## Contract and Evidence

Scoped review F2 lists nine no-reason negatives; F3 generic_arity_construction also contains invalid annotation, so annotation rejection could mask construction handling; F4 test-check-command unused-type-error/global-conflict compare same generic errors across modes without intended reasons.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [F2,F3,F4](../../../evidence/test-audit/scoped-reviews/review-frontend.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

For exactly F2 nine inputs, F3 construction/annotation pair and F4 two generated cases, verify original intent and isolate intended source rule with meaningful reason and neighboring positives. Preserve driver check/build agreement and no-execution checks. Separate shared classification com-fsuq; no arbitrary rewrite of every absent .err or new unsupported feature.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.

## Explicit Part/Identity Control Extension

The later part outcome audit independently read four additional rejection
controls that have no diagnostic companion:

- `tests/fixtures/partreject/trait_view_unimported/Main.pw`
- `tests/fixtures/partreject/trait_owner_required_identity/Main.pw`
- `tests/fixtures/partreject/phantomdep/Main.pw`
- `tests/fixtures/reject/trait_subject_cycle_generic_edge_reuse.pw`

Include these exact four reason assertions alongside the original nine, not
the entire absent-.err corpus. They must distinguish missing explicit selector
binding, the actually selected trait's missing requirement, missing direct
dependency, and exact-instance cycle respectively. `phantomdep` also has legacy
manifest setup; com-7u8z must resolve the relevant canonical schema before using
that setup as a diagnostic oracle. A manifest parse/version failure is not its
intended rejection. Original intent and companion positive controls are recorded
in meta/evidence/test-audit/scoped-reviews/part-tail-0087.json. These were source
reads, not observed current-candidate reasons. Shared exit/internal-failure
classification remains com-fsuq, and audit repair remains separate.

## Explicit Part-Diamond Reason Control

Source-admission batch0003 independently reads exactly `tests/fixtures/partreject/partdiamond/{Main,A,B,C}.pw` as the paired root/part control. Main imports print but calls `print(1)` without a numeric type context and has no Main.err. The loader currently rejects the repeated part parent first; if that check regresses, forward-only numeric inference can still reject the bare literal, so generic rejection is insufficient evidence of diamond detection. Isolate the diamond reason and keep the single-parent positive. This adds one exact control to the existing finite diagnostic work, not the unread partreject corpus. No fixture was run or repaired.

## Explicit Two Visibility-Reason Controls

Batch0005 adds exactly `tests/fixtures/partreject/crossmoduleprivate/{Main,Pub,Priv}.pw` and `tests/fixtures/partreject/crossmoduleprivateglobal/{Main,Gl}.pw`. Both Main files use `print(value: ...)` while the selected Std print has an unlabeled parameter. Neither has Main.err. Even if visibility protection regresses, unrelated outer-call label rejection can still satisfy the generic rejection worker. Recover and preserve the original cross-module private callable/global isolation, isolate intended diagnostics, and use valid outer contexts with reachable public positives. No actual candidate or controlled execution is claimed. This exact five-file extension is separate from common failure classification and the unread no-reason corpus.

## Explicit Two Part-Structure Masking Controls

Batch0006 adds exactly partreject/partmissing/Main.pw and partreject/partcrossmodule/{Main,Other,Shared}.pw. partmissing has bare print(1) without numeric context, so rejection can persist if missing-part discovery is incorrectly skipped. partcrossmodule's Shared impl Z is also unbound in Other's module if shared membership is incorrectly allowed. Both lack Main.err. Isolate missing input and unique part membership reasons while preserving valid neighbor controls.

partfreefn was also read, but removing its intended part-only-impl restriction leaves a well-typed I64 triple. Missing diagnostic text alone is not a demonstrated competing-failure setup. Its reason coverage is optional, not a newly required fixture repair or a duplicate of shared com-fsuq classification.
