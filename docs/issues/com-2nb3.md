---
id: com-2nb3
status: open
deps: []
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reject discovered import cycles before recursive surface queries

## Contract and audit evidence

Closed com-d57o historical parser spellings/F2 and com-vrvl JIT F3 are not this defect; new finite source-admission task.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `IMPORT-CYCLE-ADMISSION`.

## Scope and guarantee

- Frontend discover imports/reexports→first recursive Lower/trait/type surface lookup and checkImports→detectImportCycles order

## Scenarios

- Reciprocal same-selector public reexport cycle/source refusal; bare cycle without selector recursion.
- Acyclic chain/diamond/repeated import/alias and missing public selector controls.

## Excluded

- No import/cache subsystem rewrite or timeout extension.

Static discoverable cyclic selector path can recurse before cycle diagnostic; no executed current source hang claimed.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "source-admission-before-G1-and-integration", "receivers": ["com-61jt", "com-604k"], "reason": "Actual source use DAG admission; new defect outside closed historical F2 controls. Direct source G1 prerequisite, not reopen com-d57o or expand JIT F3."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.
