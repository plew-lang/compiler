---
id: met-9luu
status: in_progress
deps: [met-g9dh]
links: []
created: 2026-11-27T09:01:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [frontend, ownership, verification]
---
# Install admitted parameter groups in body scopes

Make closure and named-body parameter installation consume the admitted binding group before publishing closure facts or introducing locals. Preserve explicit local shadowing and distinct outer scope bindings.


## Contract and confirmed failure

Current da2c8c0a82e9 executes duplicate labelled and duplicate suppressed-name
closures with arguments11/22 and returns22. A named fn with duplicate
suppressed parameter names does the same. Record appends each parameter via
addLocal, addLocalCn appends to cur.locals, and localIndexByName searches
backwards. The parameter group is never admitted before this makes an invalid
second binding shadow the first. resolveClosureFunctionType and descriptor
publication do not establish binding-name uniqueness.

Consume an admitted parameter group before publishing a closure descriptor/
SourceBodySignature or installing its locals. Use the same group rules as
named signatures; do not add a closure-only duplicate-name loop or make the
low-level addLocal reject every repeated name. Retain stable binding identities
and the original admitted signature through installation; do not re-infer
labels/types or construct a second local environment/duplicate parameter array.

Explicit sequential val/mut val shadowing and outer-variable/parameter
shadowing remain valid under spec03. Captures and implicit receiver data are
not additional user parameters in this group. Inventory the finite parameter
installation callers and distinguish raw storage append from semantic group
admission. If another simultaneous binder group has the same missing boundary,
record its evidence and assign a real owner rather than claiming all scopes
fixed here. Do not change unrelated pattern/capture semantics by assumption.

RED/GREEN: actual duplicate-labelled/suppressed closure invocation plus
unused-created closure signatures, same/different parameter types, inferred
contexts and wrappers; named body consumption of admitted groups, Raw/foreign
groups without Source promotion, no partial locals/facts on failure, stable
identity through captures/ownership. Preserve explicit sequential shadow and
outer-binding restoration; the executed positive controls are in binders.json.
Focused real Record/retention/consumer controls and neutral review are required;
parent met-auj6 owns aggregate compatibility/performance gates.

The user confirmed that semantic parameter introduction owns validation. Body
scope storage must consume the admitted result rather than revalidate it or
accept an allowShadow switch. Closure signature introduction invokes the shared
admission once before publication; its generic storage helper remains neutral
to the declaration category. No new local environment is needed for the check.
