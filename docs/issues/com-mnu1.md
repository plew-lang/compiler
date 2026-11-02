---
id: com-mnu1
status: open
deps: []
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Resolve default self-containment against lexical bindings

## Contract and audit evidence

com-ru19 preserves existing traversal/errors and excludes source algorithm redesign; new finite behavior owner needed.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `DEFAULT-LEXICAL`.

## Scope and guarantee

- Unique.exprMentionsAny/checkParamDefaultRestrictions/checkFieldDefaultRestrictions→zeroarg generator ordinary lexical admission

## Scenarios

- Same-spelled module declaration vs forbidden argument value access; parameter/field default controls and nested lexical shadow.
- No argument/self capture, suspend restriction and generator failure retention preserved.

## Excluded

- No changing default evaluation order/ABI or adding unavailable captures.

Static conditional false rejection: module global shares forbidden parameter spelling before Record resolves binding. Skipped block/if/match alone does not prove invalid source accepted.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-acfl", "met-ia09", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.
