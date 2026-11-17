---
id: com-bvc8
status: in_progress
deps: []
links: [com-vh0x, com-j2i7, met-c1pg, com-cuoy, com-0w38, com-zdod]
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

Within the affected APIs and their direct caller paths, remove information or
capabilities proven unnecessary even when they do not cross a responsibility
boundary or cause the observed bug. Change the actual signatures/payloads and
callers; do not merely document unused inputs or hide them in a wrapper.
An unused field in a coherent semantic record alone does not require splitting
that record. Establish necessity from the operation's contract as well as its
actual reads; do not duplicate validation/selection to eliminate an argument.
If cleanup requires a wider shared-API redesign, assign the remaining work to a
finite linked issue with its boundary and completion conditions. Do not silently
expand this repair or describe deferred cleanup as completed.

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

Complete API/data responsibility findings and scoped unnecessary-input removal,
record the justified coherent payloads and any explicitly assigned wider work,
remove competing decisions, run
applicable behavior/structural checks and independent neutral review. Performance
checks follow the parent goal; no unproved performance claim or verifier weakening.

The unnecessary-input scope clarification (baseline f32be228 plus this
document-only amendment) received independent read-only review by
record_issue_assignment_review: accepted without corrections. This does not
certify implementation or task completion.

## Boundaries and Intake

com-vh0x/com-j2i7 own broader input-authority narrowing, not this product equality
repair; link and coordinate rather than duplicating their whole scope. met-c1pg
owns cycle graph admission/private comparisons, not non-cycle equality. No new
projection policy, conformance solver, record extension feature or main/seed
promotion. Required area intake is met-6e6k and met-ia09, plus met-si6j directly.

## Reproduction on the Pinned Compiler

The fixed-point carrier built with Syntax 0.1.11-dev.32 compiled and ran
[projection_member_identity](../../tests/fixtures/run/projection_member_identity.pw)
natively. The builder and environment substitution each reported equality for
distinct members (expected 0, observed 1). The generic, nested record and
concrete controls matched their goldens. The mapped receiver was preserved.

Both a direct rebuild and substitution publish through Comp.pushType and
Arena.registerType, which currently copy the receiver-derived classification
and pools into the scalar term. The shared child reader handles these rows as
projections. The shared head compare returns from its record branch before it
checks either the trait or the associated member. The immediate shape key and
the body/destructor nominal-key guards also read those legacy fields. Track
their compatibility with structural equality before changing the key or head.

## Semantic Reader Increment

The initial implementation gives pooled type readers an explicit projection
classification. Projection heads compare associated members and trait owners,
and their children carry the receiver and positional arguments. The coarse
candidate key uses the member for projection children and leaves full identity
to equality. Body/destruction nominal-index eligibility and grounding's
structural-record branches no longer derive the projection's category from
the receiver mirror.

The extended native RED builds the same fixture with the same exact-pin compiler
against archived source at b679f553. Member comparison fails through rebuilding
and substitution; the distinct trait-owner assertion also fails. Same-member,
receiver and trait-argument controls match. Compiling and running the fixture
with that carrier against the changed source matches the full golden.

Remaining work includes auditing data passed by construction paths, testing
selector identity and record layout-name independence, tracing any qualified
comparison and materialization consumers that still interpret mirrors,
fresh-candidate gates, and independent review. The migration TypeRef payload
still contains compatibility fields.
