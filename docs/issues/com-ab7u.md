---
id: com-ab7u
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit extern signature views before foreign-call publication

## Guarantee and Finite Work

Finish exact extern owner/slot/premise admission in both signature adapters, using the returned LoweredSourceSignature and actual registered extern Function identity. A lowered token alone is not source success.

Carry admitted parameter/result annotation evidence into the foreign-call signature and actual supported consumer, without source queries that repair absent saved facts. Preserve existing C ABI admissibility, calling convention, callback/expose and lifetime rules. No new FFI capability or ABI change is included.

## Required Scenarios

- Unused and called supported extern signatures, nested viewed/projection types when existing FFI rules permit them, both adapters.
- Missing/unrelated/wrong-instance/foreign-owner evidence and failed or duplicate owner binding retain the correct diagnostic domain.
- Existing unsupported FFI type shapes retain their intended ABI rejection rather than becoming false view-admission GREENs.
- Actual check/build and supported native/lazy foreign-call controls preserve final signature, with saved-proof deletion and recovery at the internal boundary.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Register the exact lowered signature

Both extern lowering adapters bound the function ID to its scope but
discarded the parameter and result slots from callable signature
registration. The native `authored_extern_signature_slots` fixture
aborted on `7719ee9f` with `extern function has no authored signature`.
Both adapters now bind the same exact parameter/result occurrences
through the shared callable registration helper. Completed extern
lowering is required, and the retained callable reader reports a
missing extern signature as Internal instead of falling back to raw
declaration types.

Candidate `4e635d8d` passes the native slot/owner fixture through
admission and the shared result reader. The positive C projection
control uses `Number#Carrier.Value` in both slots of `llabs`, prints
`42` in JIT and native, and emits an `i64 (i64)` C declaration and call.
It already executed on the baseline. An unused unsupported view with
no conformance is still rejected at the annotation with the common
source-admission diagnostic.

Build `20261113T023615-build-c6b420` and generation
`20261113T024113-gen-ffca49` passed. Same-source medians were 6.893268 s
and 6.891748 s. LLVM outputs match after normalizing only TypeTerm
numbers in generic body symbol names.

The existing C import of a managed `String` parameter passes
`--check` but fails native and lazy compilation on both candidates
with `main requires verified Mid lowering`. This is an existing C ABI
diagnostic gap in the scope of [com-2o4w](com-2o4w.md); it is not an
accepted ABI shape or a passing diagnostic control. Next verify absent
and foreign proof/owner cases at the actual foreign-call publication
boundary before independent review.
