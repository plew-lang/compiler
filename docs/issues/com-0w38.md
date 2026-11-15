---
id: com-0w38
status: closed
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
conformance and generic-bound use are accepted. [Fixed-point REDs](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-record-subject-red.json) also cover named extensions, methods, empty impls, generic record subjects and unit.

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


## Verified implementation increment

Both declaration lowering routes call the same record subject check immediately
after type lowering, before registering members, conformance or the impl owner.
It reads the top-level semantic TypeTerm kind; nested record arguments and
synthetic record layouts remain valid data.

The f20fc36c fixed-point carrier accepted the seven source rejection fixtures.
A native value-AST fixture linked against f20fc36c source failed with
`record impl was accepted` (134), and the same fixture linked against the fixed
source passed, checking the Source diagnostic, message and unchanged function
count. The rebuilt candidate rejects all seven cases in check, run, LLVM text
and gen modes. It also rejects an actual auto-parted generated record impl
previously accepted. The nominal wrapper test passes lazy execution and observes
the record field under permuted initialization labels.

Independent review found no contract violation or unchecked entry route.
It requested distinguishing the intended Source diagnostic from any other
rejection in the value-AST fixture; the final fixture checks both and the
reviewer rechecked it. Same-source alternating six pairs produced identical
LLVM in all twelve runs (median 7.275s to 7.285s).


## Closure

Resolved in a086ac26. Normal suite 20261115T224510-test-d61556 finished with
immutable inputs, exit 1 and 784 failures. Both new success fixtures and all
seven new rejection fixtures passed in the suite. The 778 failures shared with
the previous archived suite plus six separately reproduced against the fixed
f20fc36c carrier account for all failures. The latter include one native
runtime panic reproduced with the exact old source, and one expected-diagnostic
mismatch on an inapplicable extension view. Those original failures remain
visible. This closure applies to the record-subject guarantee. Phase three
retains the whole-suite and performance requirements.

[Normal suite and targeted results](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-record-subject-green.json)
