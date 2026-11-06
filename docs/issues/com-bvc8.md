---
id: com-bvc8
status: open
deps: []
links: [com-vh0x, com-j2i7, met-c1pg, com-cuoy, com-0w38]
created: 2026-11-06T17:52:14Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Separate projection identity from receiver mirror metadata

## Contract and Evidence

Design types-and-evidence sections2-4 distinguish projection, record and nominal
identity and require a shared semantic child interpretation. [Executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json) shows
common typeRefEq equates different associated members when the projection
contains a record receiver mirror. Real rebuildProjectionTerm and explicit
groundTermInEnvironment also create the shape, so it is not limited to manually
stamping TypeRef flags. The exercised substitution does not satisfy T:Projection;
legal-source reachability and a source miscompile remain unproven. Normal bound
generic, nested record-field and concrete nominal controls compare correctly.

## API/Representation Investigation and Repair

Before choosing a patch, map the exact data required by construction, structural
comparison, substitution and actual consumers. Determine whether receiver
isRecord/fields/nominal/view/layout metadata must be copied onto the projection
itself, and which consumers still require compatibility mirrors. This is a
possible responsibility leak through an overbroad data/API input, not merely a
branch-order bug. Do not claim input misuse or needless payload without tracing
actual reads and required contracts.

The endpoint is one consistent semantic category/head/child interpretation:
projection identity reads its owner/member and treats the receiver as a child;
record identity reads fields; ABI materialization has an explicit separate
adapter. Remove redundant competing interpretation paths or confine unavoidable
compatibility mirrors behind a documented boundary with removal conditions.
A conditional-order change alone is not sufficient if the same ambiguity remains
in other affected semantic readers. This finite repair need not replace every
TypeRef or perform all future API narrowing.

Keep source conformance admission separate. Do not make equality search for
conformance or use absence of a valid record conformance to ignore a confirmed
structural error. Comparisons should consume established semantic identity;
malformed input handling and preconditions must be explicit, not accidental
success from unrelated mirror flags.

## TDD and Completion

Preserve raw and production-builder/substitution REDs. Cover same/different
member and canonical trait owner, receiver and positional arguments, view identity,
normal records with different ABI layout names, valid generic/nested-record /
concrete nominal controls. Do not require a legal record conformance control:
the specification forbids it. Trace shared head/child APIs through equality and
actual affected consumers (including caller guards) and through any adjusted
constructor/substitution paths; retain semantic fields through final use.

Complete API/data responsibility findings, remove competing decisions, run
applicable behavior/structural checks and independent neutral review. Performance
checks follow the parent goal; no unproved performance claim or verifier weakening.

## Boundaries and Intake

com-vh0x/com-j2i7 own broader input-authority narrowing, not this product equality
repair; link and coordinate rather than duplicating their whole scope. met-c1pg
owns cycle graph admission/private comparisons, not non-cycle equality. No new
projection policy, conformance solver, record extension feature or main/seed
promotion. Required area intake is met-6e6k and met-ia09, plus met-si6j directly.
