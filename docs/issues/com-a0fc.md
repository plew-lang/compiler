---
id: com-a0fc
status: open
deps: []
links: []
created: 2026-11-02T21:46:44Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification, syntax]
---
# Accept already-specified single-scalar Unicode character escapes

## Contract and audit evidence

Bounded missing existing language literal support separated from parser failure robustness; not a new source G1/type inference algorithm requirement merely sharing Syntax file.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `SYNTAX-CHAR-UNICODE`.

## Scope and guarantee

- charValueAst valid single scalar Unicode escape currently scalar-count error; exact existing spec forms and compiler Syntax pin uptake

## Scenarios

- Defined character Unicode scalar examples vs raw scalar; invalid surrogate/overflow/empty/multiscalar refusal; simple named escapes preserve.

## Excluded

- No new Grapheme or independent escape grammar/policy; consume the adopted shared spec and coordinate com-9d4c.

Static defined-feature refusal, not invalid source or invariant. Local spec already defines form; no successful new execution claimed.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "4-existing-feature", "receivers": ["com-604k"], "reason": "Existing input/runtime/diagnostic/gen contract outside source checker algorithm; integration admission, not automatically all phase3 gates."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Adopted Shared Character Semantics

Consume the [shared escape contract](../../../spec/spec/01-basics/02-basic-types.md#文字文字列リテラル共通のエスケープ).
Character value decoding must agree with string decoding for the seven simple
escapes and valid Unicode scalars, including carriage return and NUL. Add exact
scalar controls for every simple escape, raw-versus-escaped Unicode, leading
zeros and invalid scalar/overflow refusal. Invalid source must not reach an
unchecked internal read or compiler panic. Grammar/refusal/cache authority is
coordinated with com-9d4c; this task owns character scalar-value completion and
exact dependency uptake, not a competing grammar. Implementation remains open.
