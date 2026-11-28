---
id: met-fp1z
status: open
deps: []
links: []
created: 2026-11-28T00:58:13Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Investigate zero-argument result inference in projected record fields

## Question and boundary

Classify the missing result context in the finite Source family recorded in meta
`tmp/phase3-forward-frontier/mixed-setup-followups-v47/results.json`. This is a
phase-three investigation, not an implicit new inference feature or a closure/
dynamic descriptor task. Its relationship to met-y2ec is discovery only.

RecursiveMixedProjection.pw passes with `item: Array[Wrap[R]#Parent.Item]` and
`item: []`. With only that field changed to `Wrap[R]#Parent.Item` and its value to
`opaque()` (`fn opaque[T]() -> T { panic("unused") }`), the fixed native compiler
refuses the call's record field. Diagnostic instrumentation shows expected caller
U and inferred unrelated callee T; retain these input hashes and the fixed probe
hash. This is not the same RED as receiver replacement re-inference. Earlier
Self-projection header setup failures belong to met-k93s.

## Required actions and completion

Compare typed local/return, plain record field and associated-projection field;
compare an argument-free generic result with an argument-inferred counterpart.
Consult spec/design and existing accepted tests to determine the supported result
inference contract. Trace context production, saved call descriptor, type-argument
completion and final read. If an existing-contract defect is confirmed, create a
bounded required repair task with decisive tests and the correct area owner; if
unsupported, record that classification and a future feature owner without
broadening phase three. Any new language-surface decision needs the user.

Completion requires these finite comparisons, evidence-backed classification,
owned follow-up and independent review. Merely recording "needs investigation"
is not completion. No whole-frontend or main readiness is claimed.
