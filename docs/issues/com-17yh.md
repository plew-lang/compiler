---
id: com-17yh
status: in_progress
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Verify operator protocol iteration and try calls keep selected requirements

## Boundary

Phase 3B / B2. **Bounded closure verification.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ucze](met-ucze.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Verify/Ops.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Use B0 operator/protocol/try rows. Follow selectedProtocolTemplateCall/groundedProtocolTemplateReceiver and saved operation slots to actual final calls; verify Iterator/next, Eq/Add and try extraction use the selected requirement and same evidence. Confirm retired ProtocolSelection.Direct and structural next-only acceptance have no migrated source/consumer path.

## Exit and Evidence

Each named operation family has its exact producer/slot/final callee, applicable signature/bound controls and no fallback acceptance. Preserve Ord-to-Bool/Ne result projections and existing ambiguity/structural rejection controls. Any discovered repair is limited to that family and keeps parent/gate dependencies; no new protocol surface.

Existing starting controls: `source_operation_owner_storage`, `prepared_try_source_owner`, `generic_closure_iteration_bound`, `generic_closure_operator_bound`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Current Increment

At fd4bf676, the selected operator finalizer still synthesized a missing result
from a parent expectation, Bool for ordering, or the left operand. It now
instantiates the prepared source expression result, as Direct calls do. Its
operand-range error also replaces a silent success for a corrupt range; the
new `operator_invalid_operand_range` control covers overflowing start/length.

The static branch of `selectedProtocolTemplateCall` discarded
`selectStaticMethodTemplateCall`'s resultRef and published zero to its caller.
It now retains that result. The static helper receives the expected result
explicitly from every source template; zero means no expectation. It cannot
look up expression context by a protocol statement's numerical ID. The new
`protocol_selected_result_authority` control checks the retained result and
statement slot before the actual caller/Mid/LLVM controls below.

These are instance handoff/removal changes, not new source inference or a
language rule. Operator result projections remain explicit. Fresh validation
of operator/protocol/try families and full compiler source succeeded. C4
still owns the general recipe/result audit and B3 the real callee environments.

## Outcome

Closed at source/test revision a0e04c49. Evidence is
`meta/evidence/existing-feature-conformance/source-owner-facts/phase3b-implicit-call-closure.json`.
The fresh candidate `bin/plewc-phase3b-implicit` has SHA256
`f9ee3c792d47d2fb302e2254e1030ab54ee4be5375523de1cb2d26aa3262615b`.
Standard build 20261023T122609-build-f6ff5b and fresh full compiler `--check`
passed. All 31 native golden and 26 expected-rejection controls passed; reject
controls emitted no internal errors. All 290 scoped and 5,764 build input
fingerprints still matched after execution. Build/source-check/focused sessions
74165/70853/29318 were recovered through exit zero.

| Family | Producer and final readers | Decisive controls |
| --- | --- | --- |
| Operators | Resolve/Expr recordOperatorTemplate and prepared source expression; Check/Infer saved operator signature; Mono recordBodyOperatorCallee; Mid canonical call target; LLVM explicit result projection | distinct/nested Output and heterogeneous Rhs, generic bound/trait identity, ambiguity/range rejection, custom Ord/Ne, corrupt operand pool range |
| Iteration | Resolve/Record For recipes and protocol slots 1/2; Check/Bounds closed nominal requirement; Mono selectedProtocolTemplateCall and saved receiver dependency; Mid For recipe/target | saved concrete result and statement slot, generic/associated Item, conditional bounds, existential iteration; structural next-only/unbound/mismatched Item rejection |
| try | Resolve/Expr recordTryExpression saves Result decomposition and optional From slot 1; Verify consumes saved fact; Mono registerTryConversion; Mid materializeMidTry/canonical target | identity, overload selection, generic From and error argument; missing/wrong obligation and error type rejection |

The source audit confirms no ProtocolSelection.Direct path remains. No candidate
name search is introduced by these implicit finalizers. Statement-key identity
and result projections are retained. General result-recipe audit belongs to C4,
actual callee/provided environments to B3, universal dynamic evidence to B4.
No formal timing, fixed point, whole-suite or sanitizer completion is claimed.
