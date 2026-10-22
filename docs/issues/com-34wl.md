---
id: com-34wl
status: closed
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

PlewLlvmJit now retains the ExecutionSession::getSymbolStringPool() shared owner until calls has been destroyed. Declaring that owner before calls preserves engine-before-trampoline teardown while keeping the referenced storage alive. LLVM20 SymbolStringPtr::decRef writes the pool entry's reference count; its handle does not retain the pool owner. LazyCallThroughManager retains such handles in pending Reexports entries, establishing the missing lifetime dependency.

With only that production ownership change and the regression unchanged, normal LLVM20 and LLVM22 bridge/host ASan/LSan pass. Three standalone repetitions of the previously failing normal binary lifecycle now exit zero. Native first-call, reuse, recursion and terminal-failure controls also pass in both configurations. Fresh product entry checks and formal fixed-point/performance validation also pass; see the outcome below.

## Completion Boundary

Demonstrate why the old lifetime is invalid and close it through final destruction. Run the strengthened signature-only registration/lookup controls with absent/matching/incompatible layouts on normal LLVM20 and LLVM22 ASan/LSan, preserving no-preparation-on-lookup and terminal/error ownership checks. Keep the unexecuted lookup teardown case as a regression. LLVM22 bridge/host ASan success alone is insufficient: libLLVM itself is not instrumented, and allocator behavior differs.

After a production change, perform affected product AOT/JIT checks and fixed-point/performance validation under the existing below-seven-second goal. Reuse unrelated evidence with explicit input/scope limits; do not suppress the failing positive input or call it an expected rejection. Final main-candidate full gates remain the integration parent's work.

## Resolution and Verification

Production commit `87b382d2` retains the symbol pool explicitly and documents the destruction dependency. This preserves engine/generator-before-manager cleanup and closes the pool-entry lifetime through final destruction. It adds one shared pool owner per native session, not per generated function. No language semantics or admission policy changed.

[Repair evidence](../../../evidence/existing-feature-conformance/orc-lifetime/README.md) confirms that the regression test hash is identical to the failing review input. All three normal LLVM20 standalone runs now succeed. Absent/matching/incompatible signature-only declaration controls, object ownership/output preservation, consuming admission and terminal failures pass normally and under LLVM22 bridge/host ASan/LSan. Both first-call checker configurations also pass reuse, recursion and callback failure. The old later allocator trap is not represented as an instrumented trace of the precise invalid write.

The fresh measured compiler reaches generation-2 LLVM/runtime fixed point; three runs are 6.761472 / 6.211262 / 6.208176 seconds, median 6.211262, under seven seconds. The standard gate exits zero with immutable inputs unchanged. The same compiler passes all 43 lazy CLI checks and seven direct-object checks, including AOT/JIT agreement and signals. It is saved as `bin/plewc-orc-lifetime`, SHA256 `c36716d9f95e123f2b62158e44e2287476757eaf52b6bd93e41bc1a2a47d18b3`.

This closes the bounded repair and the prerequisite for com-6ygf. Whole-corpus ASan/LSan and final-candidate integration remain in com-604k; neither main nor seed is promoted. The previous independent review's finding has been addressed. Fresh independent re-review [com-io5f](com-io5f.md) also recognizes the repair, including scratch single-line mutation and mixed terminal-session controls.
