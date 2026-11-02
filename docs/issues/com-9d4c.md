---
id: com-9d4c
status: open
deps: []
links: []
created: 2026-11-02T21:46:44Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification, syntax]
---
# Preserve lexical literal and delimiter failures in Syntax

## Contract and audit evidence

com-qt11 explicitly excludes parser algorithms and closed com-d57o only historical controls; new finite dependency+uptake task required.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `SYNTAX-ADMISSION`.

## Scope and guarantee

- Pinned Syntax comments/enum errors; char terminator/token bounds/final backslash; complete-file struct/trait/impl/extern/extension/import/call/array EOF, empty radix digits and unterminated char traces; compiler exact pin/lock uptake

## Scenarios

- Reuse executed comment/enum/character positive and existing-refusal controls only at their recorded hashes; make defect-specific future RED.
- Static complete-entry examples paired with well-formed and already rejected controls; original file/base/offset; bounded char spans.

## Excluded

- No allgrammar/Unicode/stack-safety proof; no unknown escape adoption, Grapheme or unsupported spawn/closure implementation.

Comment/enum and final-backslash abort executed lower APIs; named additional EOF/radix/unterminated char examples static only, final compiler misacceptance unproved.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "source-admission-before-G1-and-integration", "receivers": ["com-61jt", "com-604k"], "reason": "Canonical source parser failure precedes Loader hasErr admission; a later unrelated semantic refusal cannot repair missing syntax failure. Separate dependency implementation+compiler uptake finite task."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.
