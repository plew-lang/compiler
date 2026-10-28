---
id: com-8iys
status: closed
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

## Outcome

Investigated: all 1,529 assigned obligations: 1,424 observed outcomes, 66 LLVM predicates, 32 checker contracts, five instrumentation contracts and two role intakes are reconciled. Exact IDs, inputs,
reports, independent receipts, accepted corrections and finite finding owners
are canonical in the four
[reconciliation indices](../../../evidence/test-audit/scoped-reviews/README.md#canonical-reconciliation).
No assigned unread obligations or unowned required audit findings remain here.

Independent [area closure](../../../evidence/test-audit/scoped-reviews/review-runtime-area.json)
SHA 4f57dde70d07c0337cfd91924db179fe1459b3ecbf5636da1d354e1646ce96c0 accepts this finite audit after
contract-first partition and scoped intent/oracle/path/control/owner review.
Prior input-matched evidence reuse and reviewer exposure remain disclosed;
counts and review receipts alone are not a semantic correctness proof.

The actual registered borrowed-receiver retain checker is acknowledged by the indexed batch104 correction; its earlier absence premise is withdrawn. Module-wide IR spelling checks, immortal payloads, raw compiler versus generated-program instrumentation and nested JIT exclusions retain their precise limits.

Source/API migration, concrete masking errors, weak oracles, unsupported lanes
and unresolved semantics remain distinct under finite responsible owners.
This investigation does not repair or decide those items. No actual Plew
compiler, generated/native/JIT program, sanitizer or performance run occurred;
controlled checker/reader/worker observations remain narrow evidence only.
Production source baseline 9665094d, spec 5bd65a5 and exact Syntax 8c892042 are
unchanged. No implementation, phase-three, main/seed or carrier acceptance
follows. Whole-corpus closure belongs separately to com-tqzw.
