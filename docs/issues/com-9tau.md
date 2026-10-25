---
id: com-9tau
status: open
deps: [com-fbqh, com-px0e, com-o7ul, com-jzdz]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Verify diverging callable types survive value storage and invocation

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-jzdz](com-jzdz.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

## Boundary

Phase 3E / E3. **Bounded callable-contract verification.** Parent criteria: 2, 4, 6, 8.
This is a bounded child of [com-fuo8](com-fuo8.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Lower/Types.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Return.pw`; `src/Mid/Types.pw`; `src/Ir/Types.pw`.

Trace isDiverging through function/closure type construction, generic/field/associated storage and invocation completion. Distinguish a callable value from invoking it. Verify both directions of forbidden normal/diverging function conversion and the adopted async/FFI boundaries without adding unsupported captures.

## Exit and Evidence

Representative generic/field/associated callable storage controls preserve divergence, invocation is source-nonvalue, taking/storing a diverging callable value is not itself divergence, and incompatible conversions reject. Record exact source term and Mid consumer; no Unit/normal-function fallback.

Existing starting controls: `diverging_callable_declarations`, `diverging_call_flow`, `diverging_function_return`, `diverging_function_fallthrough`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Outcome

Lower/Types and TypeTerm identity preserve isDiverging through closure/generic/associated storage. Record saves normalized field/binding callable signature and invocation completion; Mono stores exact final call/result recipe. Mid commits result metadata at actual Call emission, then consumes saved divergence as Unreachable. LLVM uses those selected descriptors. Both forbidden function-contract conversion directions and adopted async/FFI boundaries remain rejected.

Independent completion admission by /root/body_receiver_completion_review:
production771150e1, contracts6e119a73. Meta evidence source-owner-facts/
phase3e-callable-authority.json records fresh35 normal/4 panic/21 reject, two
DestructionShape inputs, whole sourcecheck and standard build success. Inputs
305/190 match current source. phase3e-callable-authority-self-host.json records
generation2 LLVM/runtime fixed point;7.467912/6.978049/6.943662s, median6.978049s
(<7), exit0,5926 unchanged formal inputs and matching measured/saved compiler
SHA b2f2c229f04b738de42541b31ef440921043d92efde8c3baeca0bdd991e35168.
The functional compiler's separate identity remains explicit in the receipt.
E4's missing saved source exit identities are separately required work; no E4,
G2, main, seed or adopted-carrier completion follows from this admission.
