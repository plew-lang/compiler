---
id: com-tqzw
status: closed
deps: [com-ouh2, com-e713, com-8iys, com-5zvv]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 2
assignee: Koji Murata
parent: com-jno0
tags: [verification]
---
# Reconcile full corpus test audit coverage and route outstanding findings

## Actions and Boundary

Reconcile com-e713, com-8iys and com-5zvv
against the actual inventory from com-ouh2. Check exact revision and
coverage applicability, shared/secondary assertions, excluded/manual/generated
inputs and inventory changes since discovery. Do not infer completion from
closed task statuses or total test counts.

Every inventoried assertion has an audited primary owner and oracle/path
classification; each required contract has meaningful controls or a named gap.
Resolve unclassified omissions, including new tests added by the real repairs.
Each discovered necessary correction, defect and specification question has a
finite owner/dependency under its actual area. Unsupported new features remain
separate with grounds. If scope grew, reconcile affected inventory and owners
instead of silently keeping an obsolete denominator.

## Exit and Evidence

Produce a finite reconciliation and independent review showing no unowned audit
rows or unexplained required-contract holes. Auditing and assigning a repair is
not proof it is fixed; list open follow-up owners without certifying their
behavior. No implementation milestone is a prerequisite or certification target. Do not
require new features, execute anonymous repairs or replace standard final gates.

## Outcome

The [final reconciliation](../../../evidence/test-audit/final-reconciliation.json)
SHA 7928c320858654ed914908fbfc3cfef2da500f650c41db21acbdad763dfc25f9
reconciles all 5,065 distinct obligations / 143 batches with one primary owner:
frontend 3,132, Mid/runtime 1,529 and driver 404. All three area exits are
independently accepted; original local read/reuse limits remain attributable.
Current discovery 5,790 test files, three meta controls and 31 diagnostic/support
files match their immutable input snapshots; exact test re-enumeration finds no
added/missing input. Production source/std/tests/scripts/native/manifests remain
unchanged from baseline 9665094d; spec 5bd65a5 and Syntax 8c892042 are unchanged.

The four canonical indices connect each exact obligation to its source/intent,
oracle, actual consumer/mode, detection bounds and independent scoped evidence.
Corrections104 and131 retain original snapshots: actual retain-checker coverage
is acknowledged, and the missing-golden duplicate met-py42 is closed in favor of
existing com-mt7l. No unread work is reclassified as a finding to permit closure.
55 distinct separate finite repair/investigation subjects remain open; exact
existing migration/context owners are additionally reused, without duplicate
credit or new audit-time semantic rulings.

The [fresh-context final review](../../../evidence/test-audit/scoped-reviews/review-audit-final-reconciliation.json)
SHA 9fc84141db3cb78c284126167420d23de307b63781ce62208436a75bc32a6ae6
accepted this exact candidate after independently deriving closure conditions,
checking all three area exits, actual control examples, finite owner scopes and
completion documents. The parent adopts that evidence-backed comparison. This
investigation is complete; no required audit omission remains.
This task does not certify repairs, zero unknown bugs, unsupported features,
phase-three implementation, main/seed/carrier promotion or current GREEN. No
actual Plew compiler, generated/native/JIT program, sanitizer or performance run
occurred. Saved controlled observations exercise only named extracted predicates
with doubles/synthetic data. Preexisting dirty binary and caches are untouched.
