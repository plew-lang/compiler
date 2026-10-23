---
id: com-qb05
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
# Verify written static calls consume one saved source selection

## Boundary

Phase 3B / B1. **Bounded closure verification; repair only an identified local gap.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ucze](met-ucze.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Generic.pw`; `src/Codegen/Verify/Call.pw`; `src/Codegen/Mono/Call.pw`; `src/Backend/Llvm/CallBasic.pw`.

Use B0 ordinary/method/factory rows. Trace recordParametricMethodCall and direct/static templates through selectDirectTemplateCall/selectStaticMethodTemplateCall, completeStaticBodyCallee and finalStaticCalleeIsComplete. Inspect Generic/Verify only at the corresponding recorded-call readers. Reconcile labels, full signature, argument/receiver passing, bounds and result projection; do not repeat overload lookup after commitment.

## Exit and Evidence

For each of the three rows record final consumer and removed/legitimate query sites, plus positive and wrong label/type/ownership/bound controls. Any required-fact hole or repeated selection is repaired in its exact producer/reader pair and a fresh control, or blocks this task via a specific repair child. Already correct rows close by source/removal evidence and matching scoped tests, not a fabricated rewrite.

Existing starting controls: `prepared_call_expression_source`, `source_call_proof_evidence`, `call_template_seal`, `generic_constructor_field_width`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Current Increment

B0 identified the live `Verify/Call.pw::checkCallArgCategories` rescan. Its
ordinary-call caller re-enumerates visible free functions instead of reading
the selected call; in particular it can check a lexical closure invocation
against an unrelated free function with the same spelling. The existing
`resolvedCallee` source selector already explicitly gives a lexical function
binding precedence, so preserving that decision needs no new shadowing rule.

The new `selected_call_verify_shadow` run control fails with saved 3A compiler
SHA256 `dac32dca0bbb99c8e1da5469035ae67fca18e50fde4b04fcaec25855a964345b`
at the callback parameter's invocation, exit 1/type mismatch. It covers a
callback parameter, generic callback, a local function value, a nested closure
and an actual unshadowed free call. Raw pre-change output is in
`tmp/phase3b-static-calls/fixture-before.stderr`.

Remove the competing Verify helper/call. Keep operand traversal and the existing
selected template admission (`checkCallTemplateSelection`,
`checkSourceDirectCallArguments` / `checkSourceStaticCallArguments`, constraints),
which validates the full chosen signature before owner publication. This is
not a claim that the deletion alone closes B1: fresh normal/method/factory
positive, label/type/passing/bound and missing-fact controls plus final-reader
inspection remain required. No Mid/LLVM selection implementation is replaced.

The first fresh build (`20261023T115201-build-f00e74`, a1516944) succeeded,
but the newly authored shadow fixture incorrectly expected Bool `print` to
spell `true`. Its program exited 0 and produced the correct callback results;
the fixture now checks that Bool directly and prints a neutral marker. This
new, never-green fixture correction changes no language rule.

Further B1 inspection found `Check/Call.pw::checkMethodArgs` inferring
Dictionary argument types from `key` / `value` / `fallback` labels. A valid
`impl[Key, Value] Dictionary[Key, Value] as NumberKey` with `echo(key: I64)`
is rejected for `Dictionary[String, I64]`, even though its selected signature
explicitly takes I64. The a1516944 fresh compiler reproduces the rejection
(exit 1/type mismatch); the raw control is
`tmp/phase3b-static-calls/DictionarySelectedMethod.pw` and `dictionary-before.stderr`.
Remove that spelling/label special case and use the already grounded selected
method environment. `dictionary_selected_method_signature` protects this
conformance plus ordinary `getOr` typing; existing Dictionary key/value rejects
remain mandatory controls. This is a second competing signature authority,
within B1's existing method boundary, not a new feature or a new work bucket.
