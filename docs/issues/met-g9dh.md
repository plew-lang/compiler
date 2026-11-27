---
id: met-g9dh
status: closed
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

## Focused results awaiting final review

WIP 7771bb48 built successfully in frozen parameter-group-build-v1
(validate 20261127T094357-build-13df65). Fresh CLI114/114 pass with unchanged
inputs and explicit binding-name cause. Native v2 and retained-session v1
compile/link/run pass, empty stdout/stderr and input-invariance receipts.
Existing9 default/provided/via/generic/async forwarding fixtures pass both
old and fresh carriers (18 actual ORC runs, unchanged inputs). See meta
evidence declaration-parameters/{declaration-green,native,session,forwarding}.json.
Native v1 had a new test's DiagnosticNote field mistakenly called as a method;
it failed test compilation, was corrected without product/expectation changes,
and is not counted as an executed assertion.

Neutral source review found no established Source leakage, pre-publication
omission or accidental public API visibility change. createCallableFormWitness
currently constructs a fresh Raw adapter group and uses the public registration
validator; that subset is rechecked rather than treating a Func index as an
admission proof. This finite additional comparison is retained because that
public entry also accepts caller-constructed Raw rows. Plain provided copies
preserve the source group and default generators have no parameters. No new
capability flag or guessed Source authority is added to avoid this comparison.
Final focused/gen/review closure is pending; whole/fixed-point/performance gates
remain owned by met-auj6 after B/C integration.

## Finite certification

Neutral independent reviewer /root/qualified_member_plan reviewed product
7771bb48, tests fd021904 and meta3ad07188 against this task. No established
pre-publication bypass, Source escalation, unintended API visibility change or
focused contract/test gap remained. Selected gen passed. The native driver had
been expanded after execution for session mode; its exact executed bytes are
archived as run-private-native-v1.py, SHA matches native.json, with mapping in
driver-revisions.json. Reviewer independently rechecked this correction and
certified finite A closure. Reproducible successful native outputs are retired
per retirement.json; results/manifests/driver, setup-error logs, source and frozen
carrier/std remain. B/C and the parent's whole/fixed-point/performance gates
are not covered by this child certification.
