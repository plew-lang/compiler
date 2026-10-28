---
id: met-k62r
status: open
deps: []
links: []
created: 2026-10-28T04:07:48Z
type: task
priority: 2
assignee: Koji Murata
tags: [runtime, verification]
---
# Add a discriminating Dictionary missing-key subscript control


## Finite Coverage Boundary

At source baseline9665094d/spec5bd65a5, spec02:348 requires Dictionary subscript Index to panic for an absent key, while get/getOr handle absence normally. Current std/Lang.pw:419–442 implements that distinction correctly; this audit did not reproduce a compiler/runtime defect.

Batch0095's dictionary_subscript/literal/get and related primary values observe present subscripts and missing safe lookups. They cannot distinguish replacing the missing-key Index panic by a successful ordinary value. Contract-first reviewer and parent bounded filename/text/registration searches of the audited panic family, compiler/tooling cases and existing issues found no dedicated key-not-found trap control. This is not a claim that every uninspected generated test has been proven absent.

## Scope and Scenarios

First reconcile this exact branch with existing normal/panic/generated registration and reuse an equivalent discriminating control if it exists. Otherwise add the smallest registered missing-key Dictionary subscript panic case, with the dictionary-specific failure reason and a correct present-key and absent get/getOr contrast. Distinguish a true absent-key access from a type/setup failure or Array bounds panic. Preserve source/API qualification and the harness's known signal-classification limitations under their existing owners; do not count a compiler failure or arbitrary exit as the intended trap.

Show the chosen oracle rejects a normal-result replacement of this specific missing-key branch, while correct Dictionary behavior and nonpanicking safe absence pass. TDD may retain already-correct GREEN controls; no compiler implementation repair, whole collection matrix, new source rule or general panic-harness rewrite is assigned. Record actual candidate/input/mode/registration and independent review before repair closure.

## Audit Disposition

Finite test-coverage follow-up only; actual fixture/compiler/expectation/runner changes and native/sanitizer execution were not performed in the audit. This is not a prerequisite of audit closure. Its scoped searches and confirmation limits live in the batch0095 receipt; all remaining planned audit units remain their audit owners' work.
