---
id: com-tn1m
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [mid, runtime, verification]
---
# Audit async expression and composite payload coverage

Retained uninspected combinations: await in for and nested expressions, method/generic async, composite Promise payloads, frame ownership and result transfer. Explicit borrow/inout parameters cannot carry synchronous borrows over suspension and must be rejected; this is a semantic restriction rather than missing support. Design: [async Mid details](../design/mid-entry-audit.md#async-and-machine-boundaries), [runtime](../design/runtime.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Establish each currently supported/rejected combination with source and minimal controls; close selected payload/frame/result consumers without weakening synchronous borrow restrictions or inventing cancellation semantics.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

Codegen/Verify/Func.pw::verifyFunc explicitly rejects non-integer/non-Bool
async results because the Promise payload is one i64 slot. Backend.pw::emitLlvmRuntime
and Backend/Llvm/MidAsync.pw::midAsyncComplete/midAsyncSuspend confirm the scalar
layout and conversion path. This is an explicit implementation restriction versus
the general spec14 Promise[T] contract, not a newly reproduced crash. Lang.pw's
Promise[T] also lacks the adopted autounique/consuming unique-result protocol
([met-b2la](met-b2la.md)). Verify/Func still recognizes an explicitly non-Promise
async return as the inner payload; compare with spec14's explicit Promise syntax
when closing the source surface, rather than treating historical syntax as policy.

Countercheck: midAsyncSuspend tests the done flag and branches directly to its
completion block when already complete. Do not report unconditional yielding from
the runtime registration helper's queued fast path; generated await bypasses that
helper for an already-complete Promise. Scalar suspension and frame preparation
exist. Remaining composite ownership, async-self and consuming-result combinations
need their own verification, not blanket claims of missing all async support.
