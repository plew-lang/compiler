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

## Current Reconciled Subset

Primary audit count:1529 of1529 assigned obligations, by exact role{'observed-behavior': 1424, 'llvm-literal': 66, 'role-intake': 2, 'instrumentation-contract': 5, 'checker-contract': 32}. Exact role IDs, report/receipt hashes and all finite qualifications are indexed by meta/evidence/test-audit/scoped-reviews/{outcome-reconciliation,support-reconciliation}.json. Source-admission/rejection work has its separate frontend owner and is not counted here.

Reconciled units and exact completed batch membership are recorded in the canonical reconciliation files above; each retains its finite source/contract scope. Every selected input/companion, original purpose, canonical oracle, real runner mode and finite detection boundary was inspected. No actual compiler, generated program, native sanitizer or performance execution occurred; accepted static evidence does not certify runtime repair or all memory safety.

Source/API migrations remain qualified under their existing exact/broad owners. Fixed module-wide LLVM predicates reuse com-pshx; they are not target-specific lowering certificates. Existing com-4vr8 owns the exact array/Buffer/Dictionary and discarded-place immortal-String assertion gaps; met-6zp3 owns indistinguishable argument-destruction/result markers in the exact via and closure temporary cases. com-l5l9 retains the named destructure golden mismatch; met-k62r owns the bounded missing-key Dictionary Index trap control. Useful value/size/CoW/default-order checks remain preserved; neither source-backed gap is a reproduced compiler memory fault. Other finite owners are canonical in disposition.json, not a second manual progress list.

All remaining assigned units stay this audit's work. Next is batch0130 onward, followed by area/final reconciliation; this task remains in_progress. No repair, phase-three completion, main/seed or whole-corpus certification follows from these checkpoints.
