---
id: com-p10m
status: open
deps: []
links: []
created: 2026-10-21T13:05:07Z
type: bug
priority: 1
assignee: Koji Murata
tags: [runtime, backend, verification]
---
# Enforce checked Buffer capacity arithmetic and allocation failure

## Contract and Source Evidence

Static audit at compiler `78bd9691`, spec `1e0c4d0`; no compiler execution or
runtime reproduction. [Buffer capacity semantics](../../../spec/spec/01-basics/02-basic-types.md#生成観測容量)
require checked element-count/addition/element-size/allocator-range arithmetic,
panic on allocation failure and no receiver mutation before a failing request.
[The safe floor](../design/collections-and-buffer.md#conditional-safety-argument)
owns these guarantees for every user collection.

The inspected path is `std/Core.pw::Buffer.withCapacity/reserve` -> the registered
Buffer Reserve intrinsic -> `src/Backend/Llvm/Mid.pw` BufferIntrinsic.Reserve ->
`src/Backend/Llvm/Arrays.pw::rawbufReserve` -> emitted C
`src/Backend.pw::emitLlvmRuntime` (`plew_arr_reserve`, `plew_rawbuf_alloc`).

The LLVM reserve case uses plain LLVMBuildAdd(count, additional), without a
checked addition. Emitted allocation computes header bytes plus elemSize*cap in
signed long long arithmetic, calls malloc, then writes the header without testing
for null. Growth also computes cap*2 unchecked. The forwarding wrappers contain
no missing downstream check that repairs these operations. For example the
mathematical allocation for I64 capacity 2^61 already exceeds the 64-bit byte
range; it cannot be treated as a successful small allocation. No observed crash
or specific optimizer manifestation is claimed.

This is a confirmed missing correctness boundary, distinct from the reentry
investigation in [com-zgk9](com-zgk9.md). It also covers current non-concurrent
programs and does not depend on implementing spawn, new generics or a new ABI.

## Completion Conditions

Centralize checked arithmetic/allocation failure in the storage floor and preserve
valid ownership/state before publishing or replacing backing. Cover capacity
addition, growth, element multiplication, header/allocator range, zero-sized
elements and allocation failure. Exercise the common AOT/JIT runtime and both
private/shared backing. Do not fix only the public reserve wrapper or rely on
LLVM optimization, sanitizer detection or OS termination as the language panic.
Verify normal growth/CoW values and panic controls without enormous real allocations;
record sanitizer and fixed-input parent gates applicable to the eventual repair.
