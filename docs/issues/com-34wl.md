---
id: com-34wl
status: open
deps: []
links: []
created: 2026-10-22T01:17:27Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [backend, ownership, verification]
---
# Fix heap corruption when destroying an unexecuted lazy JIT entry


## Contract and Observed Failure

Destroying a native lazy JIT session after registering and looking up an entry, without executing it, must release owners without accessing freed resources. This is an existing native API lifetime boundary, not a new language feature or a target addition. It blocks the strengthened positive declaration controls in com-6ygf and phase-two completion.

The phase-two review com-i5vp found an invalid negative control, replaced it with signature-only declarations carrying valid plew.body metadata, and added absent/matching layout success/lookup controls. Normal LLVM20.1.1 crashes after the first unexecuted lookup/session destruction. Three standalone repeats terminate with SIGTRAP. The OS crash report detects memory corruption of a free malloc block at the next LLVMContextCreate. [Saved evidence](../../../evidence/existing-feature-conformance/phase-two-review/README.md) includes exit codes, stderr, hashes and technical crash frames. The production source is 9fd85bb6/ce65512a and remains unmodified by the review.

## Leading Hypothesis and Design Direction

The production PlewLlvmJit member order destroys engine, then stubs, then calls. LLVM20 LazyCallThroughManager::Reexports stores SymbolStringPtr values; an unexecuted trampoline can retain these after the engine's ExecutionSession/SymbolStringPool is gone. Refcount release into a freed pool entry is consistent with the heap corruption, but source inspection plus a later allocator trap does not prove the exact write.

Investigate retaining the ExecutionSession::getSymbolStringPool() shared owner in PlewLlvmJit until calls has been destroyed. Declaring such an owner before calls would preserve engine-before-trampoline teardown while keeping the referenced storage alive. Confirm the whole lifetime graph rather than blindly reordering owners. No production patch has yet been made.

## Completion Boundary

Demonstrate why the old lifetime is invalid and close it through final destruction. Run the strengthened signature-only registration/lookup controls with absent/matching/incompatible layouts on normal LLVM20 and LLVM22 ASan/LSan, preserving no-preparation-on-lookup and terminal/error ownership checks. Keep the unexecuted lookup teardown case as a regression. LLVM22 bridge/host ASan success alone is insufficient: libLLVM itself is not instrumented, and allocator behavior differs.

After a production change, perform affected product AOT/JIT checks and fixed-point/performance validation under the existing below-seven-second goal. Reuse unrelated evidence with explicit input/scope limits; do not suppress the failing positive input or call it an expected rejection. Final main-candidate full gates remain the integration parent's work.
