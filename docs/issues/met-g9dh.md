---
id: met-g9dh
status: in_progress
deps: []
links: []
created: 2026-11-27T09:01:13Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [frontend, diagnostics, verification]
---
# Admit declaration parameter groups before signature publication

Implement shared binding-name and non-absent-label group admission for named callable and requirement signatures, preserving Raw ownership, generated forwarding and selected gen policy.


## Contract and implementation boundary

Implement the adopted spec04 rules as two guarantees: all declared parameter
binding names in one introduction group are distinct, including suppressed
positions; all non-absent signature labels are distinct. Reuse one minimal
comparison authority, not a separate per-kind checker. With Plew's labels
derived from binding names, a validated binding group may establish uniqueness
of its label subset without rescanning the same data. Function types use the
label-only guarantee and do not introduce binders.

Own source/legacy named declaration and trait-requirement admission before
successful signature/row publication. Trace existing registerAuthoredCallable,
registerDeclaredFunc and bindAuthoredRequirementScope paths. Free, method,
associated, factory, generic, provided authored definitions and named extern
parameter names must follow the same binding-group rule. Preserve C no-label
requirements and synth receiver handling. Authored groups are admitted once;
default/provided/via/generic copies retain their source group's contract.

Raw/public entry points cannot grant Source from scopes, nameIds, offsets or
caller-built rows. Compare actual coherent label/name data; unknown nameId0
is not a shared name. Keep gen selected-program policy separate from ordinary
compiled generated source. Never bless an AST-only harness as a checked program.

RED/GREEN: local/import unused declarations in check/AOT/ORC; labelled and
suppressed duplicate binding names, distinct/unlabelled legal pairs; named and
requirement signatures, default/generic/provided forwarding; original/duplicate
locations and retained failure; Raw/synthetic/foreign/malformed group input.
Retire module-zero/competing decisions, maintain actual success/failure
publication and coordinate only the com-9sa5 parameter leaf. Final whole/
performance integration belongs to met-auj6 after all its children, while
this child's focused admission controls and neutral review are mandatory.

The user confirmed introduction-side validation: the common parameter-definition
owner admits the group, while local storage only consumes it. Its uniqueness
comparison needs the group itself, not outer locals or an allowShadow policy.
Reuse an existing private/sealed signature construction path where it provides
the guarantee; do not mandate a new wrapper type or duplicate storage per rule.

## Current implementation checkpoint

The fixed da2c8c0a82e9 declaration matrix has 42 legal GREEN controls and
72 target RED failures (21 Unclassified duplicate-label failures, 51 accepts),
with unchanged inputs. Receipt: meta evidence declaration-parameters/declaration-red.json.
The manual matrix now requires the binding-name diagnostic specifically;
executed shadowing behavior is retained in binders.json, not inferred from an
unused BodyShadow declaration.

WIP admits completed pooled groups before registerDeclaredFunc publication and
requirement signature completion through the existing bytes/span comparator.
Private fresh Syntax forwarding retains Source origin; public and legacy entry
points retain Raw. Direct Raw shape verification reuses the same comparison
instead of module-zero/nameId policy. No storage-side shadowing changes.
Existing gen suppression stays a caller policy: skipped harness groups are not
ordinary checked signatures; ordinary compiled generated source is admitted.
Fresh/native/forwarding/retained-failure and independent review remain required;
this checkpoint is not completion.
