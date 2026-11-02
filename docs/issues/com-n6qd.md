---
id: com-n6qd
status: open
deps: []
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Retain full newtype underlying receiver in extension applicability

## Contract and audit evidence

Input-only newtype metadata/adapter tasks do not own extAppliesToType algorithm; closed scoped work remains valid.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `NEWTYPE-VIEW`.

## Scope and guarantee

- Decl.extAppliesToType633–636 newtype recursive fallback and actual view validity/source selection consumers

## Scenarios

- Underlying Box[I64] vs extension Box[String] wrong/right full instantiation, conformance-only extension, nongeneric and absent source controls.
- Required view gate and final method use consume same selected full semantic receiver.

## Excluded

- No new cast/view language policy or full newtype implementation rewrite.

Static conditional required applicability gate loses generic receiver precision; no executed whole-program wrong dispatch.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "met-6e6k", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.
