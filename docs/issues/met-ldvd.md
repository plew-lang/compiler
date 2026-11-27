---
id: met-ldvd
status: in_progress
deps: [met-g9dh]
links: []
created: 2026-11-27T09:01:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [frontend, types, verification]
---
# Validate labelled function types through type admission

Apply the adopted non-absent-label uniqueness rule to function type construction and source type-use admission without introducing local binders or rejecting repeated unlabelled positions.


## Contract and implementation boundary

A function type has unique non-absent labels but no local binding group.
`fn(value: I64, value: I64) -> ()` is invalid; `fn(I64, I64) -> ()` is valid.
Use the shared label comparison contract from met-g9dh through actual type
construction/admission and retained type-use consumers. Do not infer a binding
name from an absent label, type identity0 or a display string.

Trace Syntax/legacy builders, source type uses, callable/closure signature
function-type construction and canonical type interning. Reject malformed
authored labels before successful type-use publication. Raw/synthetic terms
cannot obtain Source authority from matching labels or spans. Do not reopen
source inference or reinterpret associated/view evidence to diagnose duplicates.
Preserve ordered labels, contextual compatibility and existing completion/mode
contracts. A valid admitted callable signature can carry its already proved
label uniqueness; avoid rechecking it through every derived type consumer.

RED/GREEN against the fixed carrier: direct/nested annotated function types,
fields/parameters/results and source wrappers/associated type uses as applicable,
labelled duplicates versus repeated unlabelled positions, distinct legal labels,
ordinary/diverging function types and omitted-annotation closure contexts.
Exercise real type-admission/retained consumers plus Raw/foreign/malformed
controls; no verification weakening or same-text Source classification.
Focused tests and neutral review precede parent aggregate whole/fixed-point/
performance validation. No new function type feature or local shadowing rule.
