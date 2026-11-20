---
id: com-r88j
status: in_progress
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

## WIP verification checkpoint

Product changes and finite evidence are retained in meta `evidence/rejection-domains/diagnostic-domain-implementation/phase3-lexical-call-binding.json`. Fresh build 20261119T233117-build-79f17e and standard gen 20261119T235538-gen-7c1f78 exit 0. Source-native probes cover failure ownership, pending original failures, inferred/annotated/imported-alias global target, and private argument-access recording with an intentionally omitted-recording detector. Native and ORC language controls exercise actual local receivers, default/provided callers and temporal scope boundaries. Genuine free visibility/selector/ambiguity refusals remain unchanged in 36 old/new mode controls. Same-source alternating five-pair medians are 6.727844/6.720914 seconds, all ten LLVM outputs equal; this is diagnostic, not a new formal fixed point.

Interim independent source review found no remaining confirmed must-fix after restoring argument access recording and using typed value completion in ExprType. Final independent acceptance and normal whole-suite comparison remain required. This checkpoint does not close this task, com-yeua or phase 3. Global final receiver support, full function-value argument admission and gen authority remain with the excluded owners above.

## Whole-suite interruption and adoption corrections

Normal run 20261120T001448-test-7ffc79 was aborted by ENOSPC and has no whole-suite conclusion. Exact worker inspection found no survivors. Independent native reruns and old frozen-source controls distinguish two existing capture-boundary test failures from two new regressions: raw NoStatic cache must not mint NoMatch/Source evidence; global-initializer callback preparation must retain its previously working prefix. Keep the existing free_call_failure_domain expectation. A raw error from the free-only helper now blocks forged cache authority (fresh verification pending). com-za4f is a required predecessor for final global storage consumption; it consumes eab68d76 source publication, not this task's closure. Independent review accepted this dependency and responsibility split. No finite task closure before both corrections and full-suite comparison.
