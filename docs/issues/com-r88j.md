---
id: com-r88j
status: in_progress
deps: []
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Select lexical call binding before visibility checks

## Contract and audit evidence

met-tfbl explicitly investigation with four not-yet-registered repair units; propose precise unit1 rather than claim investigation owns implementation.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `CALL-LEXICAL`.

## Scope and guarantee

- met-tfbl V1/V2 normal source Record/Expr/visibility eager/lazy route; retain nearest absent/noncallable/pending/selected kind

## Scenarios

- Local/parameter vs same-named private/unimported/module/imported function; noncallable shadow and pending global.
- Full free-function frontier, aliases/defaults/provided bodies, valid omission and genuine visibility refusals.

## Excluded

- No pow precedence decision, broad diagnostic hint rewrite or reopening com-cwu1/com-qb05.

Existing met-tfbl executed rejecting/correct-dispatch controls reused only within saved source/carrier; this assignment executes nothing.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Current candidate recheck

Compiler source c07a4ce0 / candidate `tmp/phase3-nested-closure-limits/build/bin/plewc` still rejects a function-typed parameter named `print` without using @Std/Io: `fn apply(print: fn(value: I64) -> I64) -> I64 { return print(value: 7I64) }`. Check/AOT/ORC all return the unrelated non-ambient Std diagnostic (Unclassified); the selected lexical parameter must not require a Std import. Evidence: meta `evidence/rejection-domains/diagnostic-domain-implementation/phase3-visibility-precheck-recheck.json`. Source inspection confirms normal Record calls checkExpressionVisibility before its Call arm reaches recordDynamicLocalCall / complete free-function selection. Continue this existing repair before com-yeua promotes these visibility refusals. Preserve the original full unit1 scope and separate pending-global/name-kind handling from com-za4f's final receiver consumption.
