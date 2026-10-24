---
id: com-nucu
status: closed
deps: []
links: [com-4kti]
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Close partial-input projected member enumeration before source admission

## Boundary

Phase 3C / C2. **Bounded investigation of one query boundary.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Bounds.pw`; `src/Codegen/Check/CallConstraints.pw`; `src/Codegen/Mono/Call.pw`.

Trace projectedMemberResolution positionalArgsOpen probes through queryViewedTraitConstraint to selected requirement admission. Enumerate only the distinct positional trait instances for one receiver/member, then track the chosen full instance and proof. Use one-instance, two-distinct-input-instance, duplicate-path and associated-output mismatch contrasts.

## Exit and Evidence

Publish the exact enumeration/selection/filter ordering and current controls. If the weak Existence result is being used as SourceAdmission, create a mandatory bounded query/result handoff repair with exact entry/result/control sites and make the area and G1 depend on it. This investigation closes classification, not an unperformed repair. Preserve source precedence and ambiguity; do not merge different input instances, choose discovery order, or introduce an unsupported projection/opening feature.

Existing starting controls: `associated_projection_constraint_identity`, `source_selected_witness_owner_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Investigated Boundary

At production 51e19101, projectedMemberResolution asks traitPatternProof for
Existence with open positional inputs. traitPatternProofFromFacts returns the
first matching assumption/path under that demand. selectStaticRequirement then
ranks only requirements within that one already-chosen trait input instance.
The stored operation retains that exact proof; integrity/scope checking and
later instantiation do not enumerate the discarded instances or establish
source uniqueness retroactively. Associated-output mismatch checking remains
active, but cannot repair this earlier loss.

Eight watched fresh-compiler source checks are retained in
`meta/evidence/existing-feature-conformance/source-owner-facts/phase3c-projected-member-audit.json`:

| Contrast | Current result | Disposition |
| --- | --- | --- |
| One Convert[I64] instance | accepts | valid control |
| Convert[I64], Convert[Bool], Bool operand | rejects mismatch | wrong first-instance selection |
| Same bounds, I64 operand | accepts | does not prove complete enumeration |
| Reverse bounds, Bool operand | accepts | order dependence confirms discarded candidate |
| Exact duplicate Convert[I64] premise | accepts | preserve source-premise deduplication |
| Two no-operand Convert input instances | accepts | missing instance ambiguity |
| Independent Left/Right trait-subject routes to Convert[I64] | accepts | weak Existence used without full source-path admission |
| Associated Output=I64 but Bool return | rejects | output checking still active |

This is the anticipated repair disposition in this investigation's Exit, not
completion of an unperformed fix. Required child [com-4kti](com-4kti.md) owns
finite instance enumeration, normal applicability and full selected proof
admission through final use. It depends on this classification; met-6e6k and
G1 explicitly depend on the repair. No area/parent closure or compiler rewrite
is inferred from the investigation. The independent classification review and
its disposition are recorded below.

## Independent Classification Review and Allocation

`/root/c2_classification_review` reviewed 80cebe44 disposition and the saved
checks, independently matching all eight input hashes, carrier and four source
files. Verdict: projected-path classification is valid; it does not certify the
unperformed repair. The planned projected repair child/dependencies are correct.

An additional ordinary generic receiver contrast found the same first-instance
selection without an associated projection:

```plew
trait Convert[Input] { fn convert(value: Input) -> I64 }
fn probe[T](value: T) -> I64 where T: Convert[I64], T: Convert[Bool] {
    return value.convert(value: true)
}
fn main() {}
```

The fresh compiler rejects this with a type mismatch. Bounds.staticMemberResolution
returns the first assumption's selectStaticRequirement result, even its fallback
rank, without reconciling later input instances. The reviewer confirms that B1's
saved-reader boundary, B3/B4 and the projected-only C2/repair allocation do not
own the complete ordinary source-candidate frontier. This is a newly evidenced
mandatory task-allocation omission, distinct from C2's anticipated projected
repair disposition. This triggered the user's explicit task-plan stop condition
before widening a task or introducing a second solver.

## Outcome

**Investigated and allocated; classification complete.** On 2026-10-24 the user
approved the independently reviewed task correction. [com-4kti](com-4kti.md)
now owns one shared finite candidate frontier for ordinary generic and
associated-projection receivers, exact-instance admission and saved final use.
Its accepted entry/actions/exit incorporate all three plan reviews. Actual tk
edges retain com-4kti -> com-nucu and met-6e6k/G1 -> com-4kti, and add met-ucze
and D3/com-wqa0 -> com-4kti. There is no reverse C2 -> repair dependency.

The nine retained source contrasts at production 51e19101 and the independent
classification review establish this investigation's findings. No source or
test changed to close classification; the known defect remains open in the
repair. Existing narrower evidence remains valid for its recorded inputs only.
Area/parent closure, repaired-candidate controls and final G2a/G2b gates remain
outstanding. The task-allocation stop is resolved; the next implementation is
com-4kti, not another unbounded C2 investigation.
