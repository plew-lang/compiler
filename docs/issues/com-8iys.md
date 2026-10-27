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
now covers195 exact primary outcome units here: all43 runtime-owned panic,
all93 part and first59 run outcomes. Five complete outcome batches0084–0088
and seven scattered internal outcomes across owners are source/oracle/runner
reviews, not actual compiler/program execution or source-admission certification.
All selected project inputs were read; part output arithmetic matches authored
goldens, conditional on explicitly recorded admission qualifications.

Six new finite follow-ups distinguish five historical existential success
admissions (com-vp0o), Dictionary replacement observability (com-9hyu), explicit
versus bare impl binders (com-owb3), unresolved omitted trait inputs (com-yhap),
constructor sibling inference (com-pxja), and selected manifest schema consistency
(com-7u8z). Original useful coverage is retained in the required repair contracts;
no test or runner was repaired. com-ntm8 explicitly extends four named reason
controls. Other plan units remain audit work, not transferred as vague findings.

The earlier87-unit independent acceptance retains its exact scope. Added80-unit
independent reconciliation review accepted exact scope, hashes, oracles and
finite finding owners with no required audit correction. This task remains
in_progress; added35 independent reconciliation accepted the limited source
audit (initial partial report exposure explicitly retained) and batch0089 is
being inspected. Batch0088 explicitly extends com-vp0o to nine roots and
com-bfvd to seven representatives, with no repair/execution claim.
