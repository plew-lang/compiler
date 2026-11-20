---
id: com-r88j
status: closed
deps: [com-za4f]
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Select lexical call binding before visibility checks

## Contract and audit evidence

met-tfbl explicitly investigation with four not-yet-registered repair units; propose precise unit1 rather than claim investigation owns implementation.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `CALL-LEXICAL`.

## Scope and guarantee

- met-tfbl V1/V2 normal source Record/Expr/visibility eager/lazy route; retain nearest absent/noncallable/pending/selected kind

## Scenarios

- Local/parameter vs same-named private/unimported/module/imported function; noncallable shadow and pending global.
- Full free-function frontier, aliases/defaults/provided bodies, valid omission and genuine visibility refusals.

## Excluded

- No pow precedence decision, broad diagnostic hint rewrite or reopening com-cwu1/com-qb05.

Existing met-tfbl executed rejecting/correct-dispatch controls reused only within saved source/carrier; this assignment executes nothing.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. This proposal is not implemented or verified. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Current candidate recheck

Compiler source c07a4ce0 / candidate `tmp/phase3-nested-closure-limits/build/bin/plewc` still rejects a function-typed parameter named `print` without using @Std/Io: `fn apply(print: fn(value: I64) -> I64) -> I64 { return print(value: 7I64) }`. Check/AOT/ORC all return the unrelated non-ambient Std diagnostic (Unclassified); the selected lexical parameter must not require a Std import. Evidence: meta `evidence/rejection-domains/diagnostic-domain-implementation/phase3-visibility-precheck-recheck.json`. Source inspection confirms normal Record calls checkExpressionVisibility before its Call arm reaches recordDynamicLocalCall / complete free-function selection. Continue this existing repair before com-yeua promotes these visibility refusals. Preserve the original full unit1 scope and separate pending-global/name-kind handling from com-za4f's final receiver consumption.

## Implementation boundary and TDD scenarios

Normal call head binding is chosen before visibility and applicability: nearest value identity/storage kind versus the complete free-function frontier. Share the nearest value query with identifier resolution; never treat the first visible function as a selected overload. A value's pending type completion and noncallable outcome cannot fall back to free selection. Pass the selected binding index/identity to recording rather than resolving its name again; retain the final identity in the existing call template. Preserve global source identity as a distinct target; actual global Mid/LLVM receiver success remains com-za4f and must not be relabelled as an implementation limit. Keep existing named pow semantics and gen sweep behavior as explicit exclusions.

Source refusal for a selected noncallable binding uses a structured cause and retained private negative event; raw callers remain Unclassified, only owning consumers classify Source. Reuse the existing failed free-call outcome map as a typed NoMatch/NonCallableBinding sum, without a new broad cache. Type completion/normalization failures propagate before recording a noncallable event; do not turn unknown/zero/pending type into a completed noncallable decision.

Current fixed-candidate RED: new lexical_call_value_shadow rejects in check/AOT/ORC with an unrelated import diagnostic; new lexical_call_noncallable_parameter and lexical_call_noncallable_shadow are incorrectly accepted in all three modes. Meta scratch `tmp/phase3-lexical-call-binding/red.json` retains actual results. Required next contrasts: private/unimported candidate add/remove/rename invariance, visible/imported overload union and aliases, defaults/provided callers, pending versus annotated global identity, original pending type failures, source/raw/forged refusal ownership, preserved named pow/gen behavior, actual local receiver output through native/JIT and unchanged unrelated closures. No complete closure-value signature or global runtime guarantee is claimed by this unit.

## Verification and finite acceptance

Accepted product revision: **2172ca70**. Meta evidence: `evidence/rejection-domains/diagnostic-domain-implementation/phase3-lexical-call-binding.json`, `phase3-global-callable-snapshot.json`, and `phase3-call-cache-outcomes.json`.

Nearest-binding, pending type, genuine free visibility/overload/alias/default and foreign-declaration noninterference controls passed. Source refusal requires the retained private failed operation; raw, foreign/forged and equal-text diagnostic controls do not acquire Source authority. The final cache representation distinguishes Selected, actual NoCandidate and CachedNonStatic. Observers retain their no-static/declaration-growth contract; only actual failed search issues NoMatch evidence. Invalid cached function indices remain raw errors. The unchanged four regression fixtures and new String/Bool scope control pass with the final candidate; eight exact internal native probes also pass.

Fresh build `20261120T030816-build-2d8c9f` passed. Whole normal run `20261120T032029-test-6ec017` completed with immutable inputs, skip0, no worker failure: 329→324 failures, no added failures or changed failure reasons. The five removals are the four cache regressions and the diagnostic-only `generic_unbounded_callable` golden. The two old capture-boundary tests fail identically on frozen pre-change source and remain parent com-yeua work, not an accepted regression.

Same-source alternating five-pair comparison: old median6.864809s / new6.873567s, all ten LLVM equal. This is diagnostic, not a new formal fixed point. Global receiver/lifetime and selected dependency-order closure are supplied by completed prerequisite com-za4f. Independent no-history reviewer `lexical_call_binding_plan_review` verified the guarantees, final candidate evidence and whole delta, and accepted this finite scope without remaining must-fix. Cache observational regressions found during adoption were corrected, not waived.

This does not close com-yeua, phase3, full function-value admission com-l4x2, gen authority com-3mh9, or general startup effect closure com-fkxl. main/seed/adopted carrier are unchanged.
