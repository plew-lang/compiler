---
id: com-za4f
status: open
deps: []
links: []
created: 2026-11-02T21:46:44Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Preserve global storage identity of callable values

## Contract and audit evidence

Exact met-tfbl proposed unit3; source storage result is producer fix, not backend arbitrary recovery.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `CALL-GLOBAL-RECEIVER`.

## Scope and guarantee

- met-tfbl V4 Local.isGlobal→ClosureLocal loss→final Mid receiver, simple noncapturing global only

## Scenarios

- Simple global/local counterpart check/native/JIT; exact declaration/storage identity retained to required receiver preflight.

## Excluded

- No new capture support or weakening preflight/string-ID recovery.

Existing global fn passes check but native/JIT fails; no repaired output claim.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "met-acfl", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.
