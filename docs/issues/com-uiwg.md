---
id: com-uiwg
status: open
deps: []
links: []
created: 2026-10-27T19:16:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, runtime, tooling, verification]
---
# Observe pre-trap effects in shared-access panic tests

## Contract and Evidence

Shared overlapping access must be detected before the conflicting operation; nonoverlapping cells must remain usable (spec 03-values shared-world exclusivity). Normal panic worker and ASan D discard stdout and assert only abort status plus .panic substring. This does not observe source comments promising no body execution or distinguish an erroneous panic at an earlier legal call.

Four controlled production-worker observations are saved in meta evidence/test-audit/scoped-reviews/panic-output-observations.json. Expected trap and a program that first prints "must not run" and "999" both PASS; wrong reason and no-trap controls FAIL. Compiler/linker doubles only. Controlled executable exits134 rather than sending SIGABRT, so this proves stdout blindness, not real abort instrumentation or a compiler bug.

## Scope and Completion

For panic/overlapping_inout_ref, overlapping_inout_container, overlapping_inout_mixed and overlapping_inout_receiver_container, recover original intent and require observable pre-trap behavior: 6/17 legal-cell results where applicable and no conflicting callee-body execution. Use actual runner capture/optional companion or a focused checker, avoiding a blanket stdout requirement for unrelated panic tests. Derive needed stdout flush/side-effect controls so buffering cannot make "must not run" assertions vacuous. Preserve panic signal/text, source scope, nonaliasing positives, sanitizer status and watchdog cleanup.

Start with controlled RED cases exercising the real worker, including early erroneous trap, late trap after forbidden effect, correct trap and legal/no-trap counterpart. Independently review and validate affected normal/ASan paths. No compiler semantics change is implied by this detection gap. Separate repair, no audit epic parent/dependency; fixing this is not required to close the audit, but all assigned audit inputs remain its work.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 16.

Row16: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Pre-trap shared-access assertions must observe legal-cell effects and absence of conflicting callee-body effects on real normal/ASan-D paths, with flushing/buffering controls rather than source comments as proof. Required admission: com-an0b, com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
