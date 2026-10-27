---
id: com-tqzw
status: open
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
