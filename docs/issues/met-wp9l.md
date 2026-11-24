---
id: met-wp9l
status: open
deps: []
links: []
created: 2026-11-24T05:14:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-eqw2
tags: [frontend, diagnostics]
---
# Classify qualified declaration members before value admission


## Contract and boundary

Establish argument-independent qualified member category and canonical declaration-set identity before rejecting callable declarations as values. Reuse receiver/view/module/visibility discovery, not empty-argument callable applicability or typeHasAssocFn Bool. Preserve structural fields, namespace-qualified globals, lexical value precedence, normal assoc invocation and instance/static distinction. Missing/private members and dependency failures stay distinct. Retain real source operation/owner and negative category through cache and owning consumer.

## Scenarios and completion

Existing assoc_fn_value_arg check/AOT/reachable ORC RED-to-GREEN, methods as values, overloads/aliases/views, real closure fields/static globals/type qualifiers/missing/private controls, Raw/synthetic/foreign owner/session and failed builder retries/drain. Producer through final consumers, shared lookup responsibility, fresh candidate and independent review required. Named declaration transport is met-5vgp; successful binding readers remain com-tr3a.
