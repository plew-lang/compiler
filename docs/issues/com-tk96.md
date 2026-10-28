---
id: com-tk96
status: open
deps: []
links: []
created: 2026-10-28T00:12:51Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification, runtime]
---
# Reconcile C string conversion fixture with the fallible API


## Finite Audit Question

At compiler source9665094d/spec5bd65a5, inspect exactly tests/fixtures/run/ffi_extern_c.pw/.c/.out and the public stringFromCString declaration in std/Ffi.pw. The current positional helper assumes valid UTF-8 and returns String. Spec15's C-to-Plew contract instead names String.fromCString(ptr:) -> Result[String,Utf8Error] with validation, alongside bytesFromCString for raw bytes. No existing exact test-audit owner was found; com-qnyl covers separate unresolved FFI surface work, not this decided conversion contract.

## Guarantees and Limits

The ASCII companion library currently returns valid bytes; its opaque-handle ABI, explicitly suppressed C labels, copied CString lifetime and output plew_hello remain meaningful. Merely using the currently exposed helper does not prove the fixture is forbidden by adopted source rules, and the golden does not claim invalid-UTF8 handling. Preserve that finite purpose while distinguishing current implementation coverage from the adopted fallible API. CString's struct-body deinit placement is separately met-2t3l.

Recover the original introducing test/helper intent and relevant canonical decisions. Decide whether to retain a clearly bounded current-API fixture or migrate it when the adopted API becomes available; identify exact test/API follow-up owners and required positive/invalid-byte controls for that migration. Do not infer a new unsafe exception, declare the fallible contract implemented, or enlarge this task into all FFI/Unicode/C pointer safety work. No language-surface choice is delegated by this issue.

## Completion

Record exact source/contract differences, original intent, justified finite disposition, independent review and owned follow-ups. This investigation may close without implementing UTF-8 validation or changing tests. Any subsequent repair follows TDD and its applicable gates. Audit makes no compiler/std/test/runner change and runs no real compiler/native/sanitizer program. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0046.json and its independent receipt (on completion of that finite batch); this issue is not a prerequisite for audit completion.
