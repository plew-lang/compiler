---
id: com-qb05
status: open
deps: [com-qehq, com-zy6r, met-tfbl]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Verify written static calls consume one saved source selection

## Lexical Visibility Investigation

[met-tfbl](met-tfbl.md) is a required investigation before fresh closure. An
unrelated loaded module's same-named function makes a local closure parameter
call fail visibility. The user requests a responsibility-level audit of lexical
priority, candidate continuation/failure categories and diagnostic-only search,
not an assumed closure-specific patch. The optional missing-use hint may be
removed if it interferes; actual visibility rejection must remain. The audit
must assign confirmed repairs before closing; no earlier finite call/argument
repair or green gate certifies this new boundary.

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-zy6r](com-zy6r.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

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

## Outcome

Resolved the scoped written-call boundary at source/test **2d7e4d2f**.
[The receipt](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3b-static-call-closure.json)
pins the saved fresh compiler SHA256
`62ded91b39e3cfe348e370d4587074899b4c0647da464b4c70f30ef7b536aa16`,
source/control hashes, both pre-change counterexamples, standard build,
scoped execution results and remaining gate scope.

### Removed Competing Decisions

- `Verify/Expr.pw::verifyExpr` now traverses free-call operands without calling
  the removed `Verify/Call.pw::checkCallArgCategories`. That helper enumerated
  visible same-named free functions after Record had selected a lexical closure;
  it could reject a valid callback against the unrelated free signature.
- `Check/Call.pw::checkMethodArgs` no longer assigns Dictionary argument types
  from receiver spelling and the labels `key` / `value` / `fallback`. A valid
  Dictionary conformance can declare `echo(key: I64)` even if its Key is String.
  Its selected method environment is the authority, just as for other receivers.

Both are actual reproduced false rejections, not hypothetical cleanup. The new
run fixtures `selected_call_verify_shadow` and
`dictionary_selected_method_signature` execute the corrected behavior. The
newly authored shadow fixture initially guessed Bool output text incorrectly;
its final form tests the returned Bool directly and prints a neutral marker.
No existing test's input, expected outcome or diagnostic was weakened.

### Producer Through Final Use

| Written family | Source admission and saved authority | Instance and final consumption | Decisive controls |
|---|---|---|---|
| Ordinary | `Record.pw::recordFreeCallExpression` / `recordParametricFreeCall` → `Resolve/Expr.pw::recordSemanticExprCall` retain declaration, argument mapping and caller-owned substitution/result. Generic reads `checkRecordedDirectCallArguments`. `checkCallTemplateSelection` plus `checkSourceDirectCallArguments` and source constraint admission validate the chosen signature before owner publication. | `Mono/Call.pw::resolveBodyCallee` → `selectDirectTemplateCall` grounds saved terms; `enqueueSelectedCallee` passes retained constraints to the actual body; `completeStaticBodyCallee` consumes its prepared signature and checks conversions/result projection. Mid and LLVM use the final site/resolution, never another source name search. | New same-name closure control; `prepared_call_expression_source`; wrong labels in called/unused/generic-unused bodies; concrete wrong types, missing bounds and unique/inout rejects. |
| Method / view | `recordParametricMethodCall` / `recordUnresolvedMethodTemplate` commit Direct or selected StaticMethod. Generic's `checkSymbolicMethodArgs` and Verify's `verifyRecordedMethodCall` read the selected declaration/requirement. `recordedDirectCallEnvironment` / source static signature admission retain impl/method substitution. Source mode/place checking remains `checkArgInoutMode` / `checkUniqueArgModes`; no Dictionary-label type override survives. | `selectDirectTemplateCall` / `selectStaticMethodTemplateCall` instantiate the saved target. Exact requirement implementation selection is legitimate first concrete realization, not another overload competition. The same prepared BodySignature/final CallResolution feeds Mid/LLVM. | `verify_call_selected_authority` changes method/view spelling after selection and rejects a missing selection; `generic_call_selected_authority`; `recorded_method_result_authority`; new Dictionary conformance control plus ordinary Dictionary key/value rejects; method label/type/bound and receiver-mode controls. |
| Factory / default | `Resolve/Global.pw::prepareFactoryConstruction` records a selected synthetic factory call, then uses the same method admission. Pure memberwise/enum aggregates remain a separate construction. `Defaults.pw::recordDefaultArgumentCall` produces selected generator calls with distinct origins and lexical environment. | The static tail above prepares the actual factory/generator. `Mid/Build.pw::buildMidCallEvaluation` consumes saved parameter mapping/evaluation order; `Mid/Instantiate.pw::instantiateCanonicalCallTarget` resolves the saved site; `Backend/Llvm/Mid.pw::midCanonicalEmitDirectCall` emits the recorded callee/signature. | `factory_type_overload`, `factory_receiver_type_overload`, `generic_factory_default_selector`, `default_argument_call_templates`, `default_eval_order_method`; supplemental conditional-conformance factory with valid/missing bound, wrong label/type and valid borrow/bare-unique rejects, including actual native results. |

`prepareLexicalBodyUncached` still performs one Record construction, generic
compatibility and Verify operand/receiver checks, then complete defaults,
conversions, call signatures/constraints and source obligations before owner
success. Those compatibility/operand walks retain their checks; none may
select a different callable. D3 retains the separate write-authority audit.
`source_call_proof_boundary`, `source_call_constraint_evidence`,
`source_call_proof_evidence`, `call_template_seal` and
`source_operation_owner_storage` verify malformed/missing/foreign evidence,
unresolved or absent selections, and post-success/failure write rejection.
`finalStaticCalleeIsComplete` checks final descriptor closure; it is not the
source checker. No new AST/name fallback or public writer was added.

### Scoped Verification and Remaining Ownership

Standard build **20261023T115854-build-8e602a**: exit 0, unchanged inputs.
The exact saved fresh compiler passes **20 native golden controls**, **34
expected rejects** (no internal diagnostics), and `--check src/_.pw` (exit 0).
The main focused batch has 18 native/27 rejects; a supplemental factory/label
batch adds 2 native/7 rejects. All 260 focused fingerprints and 5,760 recorded
build input files still match after execution, including pinned dependencies.
Every child process was watched through the existing watchdog and collected.
Raw artifacts: `tmp/phase3b-static-calls/`; saved compiler:
`bin/plewc-phase3b-signatures`. Test selection is diagnostic because the standard
suite entry has no per-case filter; it substitutes for no final gate.

This closes B1's three written-call paths, not the whole type checker. B2 owns
operator/protocol/try projections; B3 owns retained clause/ParamId/physical-Self
and provided-proof completion; B4 owns universal interface admission; C4/C6
own their result/descriptor boundaries; D3 owns final operation API audit.
Normal/gen/deps/full ASan-LSan and fixed-point/formal performance remain G2a/G2b.
No timing was measured or attributed to this candidate; the f67c8fce formal
6.815672-second median remains a historical baseline. Main/seed/carrier are
unchanged. Next selection belongs to worklog, not this closed task.

## New Independent Task Review

B1: traced ordinary/method/factory/default producers through saved selection, complete signatures/evidence and explicit instances into actual Mid/LLVM. Verified removal of free-call Verify reselection and Dictionary label-based type override, plus wrong/missing-selected controls.

phase3_semantic_audit independently accepts this task at compiler dab97d52 /
meta58c9713d in [com-bkqq](com-bkqq.md). This is a new task-specific review,
not an inference that a prior unrecorded review occurred. The evidence reviewer
confirms the cited current controls actually PASS in final normal gate
20261025T062041-test-509a3f using exact candidate3c532ce1, with unchanged inputs.
This scoped acceptance does not certify the reopened value-result boundary or
phase-three parent.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 66.

Row66: Preserve ordinary/method/factory/default full signatures/labels/modes/bounds/result and final Mid/LLVM no-reselection. Do not reopen com-cwu1 accepted different boundary or infer old task/whole-area closure from repeated controls. com-qb05 original finite saved written-call authority repairs retain their exact evidence; current reopening for com-zy6r and required met-tfbl disposition still block re-admission. B67/B70/B80 are qualified reuse, not new repair discoveries. Required admission: met-ucze.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
