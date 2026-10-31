---
id: met-py42
status: closed
deps: []
links: [com-mt7l]
created: 2026-10-28T10:09:57Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Reject missing required project output goldens

## Disposition

Closed as duplicate of [com-mt7l](com-mt7l.md), which already owns both exact predicates from initial driver-review2. Parent and reviewer overlooked that existing owner during batch0131. All repair authority stays with com-mt7l; no implementation was performed. The scoped description below is retained as the duplicate record. Meta runtime-batch-0131-golden-owner-correction.json and its independent receipt supersede the new-owner attribution while preserving the original audit snapshots.

## Contract and Evidence

Exactly tests/harness/test.sh part Main.out and tests/harness/test-gen.sh generated App.out comparisons must distinguish an intentionally empty expectation from an unavailable file. Current cat failure yields empty substitution; an empty-output exit0 application can therefore PASS. All current93part/25gen goldens are present; this is a runner detection defect, not an individual missing fixture or compiler fault.

Meta evidence/test-audit/scoped-reviews/missing-goldens-probe.json uses actual extracted worker predicates and compiler/linker/application shell doubles, with production supervisors where used. Both modes pass present-empty, reject present-nonempty mismatch, and wrongly pass missing+empty output. No Plew compiler/native/JIT/sanitizer program or full suite was run; original inputs were not removed. Static outer validate/run_gate inspection finds existing-file snapshots, no mandatory-part/gen companion assertion, and no cat-error failure pattern. No whole-suite PASS is claimed.

## Finite Repair Scope

- Preserve successful present-empty expectations, nonempty comparisons, existing trailing-newline policy, application exit checks and normal/gen staging.
- Missing/unreadable required expectation or failed expectation read must fail before claiming output equality. Exercise actual production predicates with controlled RED/GREEN inputs, not a copied replacement oracle.
- Verify actual part and gen dispatch/aggregation plus standard adapter propagation. Keep existing valid project and generated-source behavior.

Do not repair fixtures/compiler semantics, introduce byte-exact comparison for all projects, alter watchdogs, require all possible filesystem failures, or combine this with general result-count completeness. com-kp0h already owns selected-versus-terminal-result closure for five normal phases. These two named expectation-read predicates only; no new framework or test matrix.

## Completion and Limits

Recover original comparison purpose, independently review expectation/read failure controls and final consumer classification, retain exact commands/inputs/results, and pass applicable gates. Audit discovered/assigned the defect only; repair is separate and has no dependency on audit closure or com-jno0. No actual source/generated program success is inferred from doubles.

## Qualified Test Intake com-5azh Row95

[Exact scope and retained roles](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) route only the current required subset to com-mt7l. The original status and qualified future/optional/historical/duplicate disposition remain unchanged. This subset neither closes a mixed parent nor reopens a closed duplicate; follow the canonical repair above.
