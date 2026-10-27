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

## Scoped Audit Checkpoint

Discovery/routing com-ouh2 is complete at source/test baseline `9665094d`.
The [finite plan](../../../evidence/test-audit/audit-plan.json) assigns exact
obligation IDs and batches; every assigned bundle still requires reconciliation.
[Independent partial review](../../../evidence/test-audit/scoped-reviews/review-runtime.json)
names inspected scopes, normative grounds and unconfirmed boundaries.
[Finding dispositions](../../../evidence/test-audit/scoped-reviews/disposition.json)
route finite repairs separately. No compiler, expectation, test or runner changed;
no real compiler/full suite was executed. This is not a full batch/domain closure.
Reuse only the named assertions with matching hashes; uninspected inputs remain
in this audit rather than being converted to an external coverage task.

## First Exact Runtime Batch

[batch0084 source audit](../../../evidence/test-audit/scoped-reviews/runtime-batch-0084.json)
and [parent disposition](../../../evidence/test-audit/scoped-reviews/batch-0084-disposition.json)
reconcile exact forty panic-outcome IDs, source+companion hashes and normative
conditions. Parent read all forty inputs/companions and key shared contracts;
independent reviewer corrected five return-arrow/projection metadata errors and
reconciled existing positive controls. Source-level audit only: no compiler,
generated body or actual program execution is certified. Shared stdout/signal
limits and selected path gaps have separate finite owners com-uiwg/com-sp65/
com-l92e; ordinary panic admission com-bfvd, deinit met-2t3l, projections met-op15.
Other batches and whole-domain closure remain open; fixture admission remains
frontend primary work. No test/expectation/runner/compiler repair was performed.

Independent completion reviewer review_audit_inventory_partition matched exact
forty IDs, eighty file hashes, 461 lines, plan/review identities, actual projection
caveats and finite findings; no required correction. Accepted source-level batch
closure only, with no candidate/domain certification or omitted audit work.
