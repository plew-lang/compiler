---
id: com-0w38
status: open
deps: []
links: [com-z4ns, com-wka4, com-amjl, com-bvc8, com-cuoy]
created: 2026-11-06T17:52:14Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Reject record impls in bare and named extension scopes

## Contract and Evidence

Spec02's labelled anonymous records are pure data: impls, conformance and methods
are forbidden. The user reaffirmed that boundary, including named extensions;
there is no new record-extension language feature. [Executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json) proves bare record
conformance and generic-bound use are accepted. Extension acceptance, empty
impls and other member forms have not yet been executed; classify them by tests,
not by assumption.

## Actions and Guarantees

Admit impl subjects using semantic type category before registration/source
success. Reject anonymous record subjects in bare and named extension scopes,
including generic record patterns and empty impls; inspect both actual Syntax
and value-AST/generated declaration routes. A layout StructDef must never turn a
structural record into a user-declared nominal subject. Cover all supported impl
member forms without relying on whether a method is emitted or called.

Preserve ordinary record construction, fields, structural identity and records
nested inside named nominal type arguments. Preserve legal impls on eligible
named declarations. Unit/empty-record treatment follows the same semantic rule;
do not ban compiler-internal record layout construction.

## TDD and Completion

Establish REDs for bare and extension record impls (ordinary methods and
associated-type-only conformance), empty impls and generic record subjects.
Cover record label permutations, unit if accepted by impl grammar, nominal
wrappers and record-as-field/type-argument controls. Where syntax already
rejects, retain that correct control and trace remaining registration routes.
Require returning Source refusal and actual CLI rejection; no skip/golden
weakening. Close declaration creation through source-success and downstream
registration exclusion, with applicable gates and independent neutral review.

## Boundaries and Intake

com-wka4 independently owns bare declared-subject ownership; fixing it does not
reject extension record impls. com-cuoy owns malformed syntax, com-bvc8 owns
structural projection identity. Links coordinate shared admission APIs but do
not force a serial prerequisite before investigation. Required phase-three
acceptance is connected to met-si6j and met-ia09. No new record methods,
conformance, factory semantics or broader unsupported-feature implementation.
