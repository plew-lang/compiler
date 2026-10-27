---
id: com-yhap
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Clarify the source contract of an omitted positional trait bound

## Finite Question

tests/fixtures/part/namespace_trait_open: Models declares Read[T]; Local explicitly conforms to Read[I64]; accept[T](item:T) where T: Models.Read returns42 without invoking read(). Source-only audit9665094d/spec5bd65a5. Original5ae85b08 expressly intended qualified open-bound acceptance. Runtime42 follows if admitted, but does not observe requirement result41 or complete selected trait arguments.

Current spec08 explicitly requires complete type arguments for existential formation/projections, while this source is a non-projecting bound. Do not apply that rule by analogy without grounds. Design types-and-evidence distinguishes open internal queries from exact source-path admission; it does not itself decide this omitted-input public syntax.

## Deliverables and Completion

Recover adopted source-bound decision, compare same-scope/qualified form and exact/ambiguous multiple Read instances. State whether omission has a canonical meaning and what evidence persists to admission/final call; request surface judgment if undecided. Preserve old qualified-owner regression through an explicit Read[I64] control if omission is rejected. Own finite specification/test/compiler follow-ups; no blanket banning of zero-arity bounds or new trait inference solver. Evidence part-batch-0086.json; independent contract-first review required. Audit outcome inspection is complete only for this exact assertion; source-admission unit remains separately tracked.

