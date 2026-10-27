---
id: com-8iys
status: in_progress
deps: [com-5by1, com-ouh2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 2
assignee: Koji Murata
parent: com-jno0
tags: [mid, ownership, backend, runtime, verification]
---
# Audit Mid backend ownership and runtime test expectations

## Scope

Audit the Mid/backend/ownership/runtime assertions assigned by
com-ouh2: IR/ABI/codegen structure, value copying/CoW/ARC, access and
cleanup, closure/environment lifetime, async/event-loop behavior and sanitizer
controls. Read the corresponding design contracts and language spec where tests
claim public behavior. A stable LLVM spelling or an internal constructor's old
shape is not automatically a language requirement.

Distinguish compiler instrumentation, generated program instrumentation, nested
JIT instructions and native bridge checks. Detection controls must actually
exercise the memory accesses claimed; an ASan pass does not prove uninstrumented
paths safe. Include the existing raw ownership supplement according to its
assigned contract without requiring all ASan runs for each inspected fixture.
Use com-ouh2's primary ownership for shared assertions rather than copying
inputs or assigning the same assertion twice.

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
now covers 80 exact primary outcome units here (all43 runtime-owned panic outcomes and37 part outcome units). Normative conditions,
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
