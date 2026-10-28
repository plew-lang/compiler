---
id: com-s922
status: open
deps: []
links: []
created: 2026-10-27T21:46:23Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Give selected numeric controls explicit literal context


## Finite Supplemental Source Repair

Source-only batch0015 audit at9665094d/spec5bd65a5 reads exactly run/float_arith.pw/.out and run/float_f32.pw/.out. Spec02 provides F32/F64-polymorphic decimal literals with no default numeric type. float_arith passes bare-literal arithmetic/comparisons into generic print without a unique floating context; float_f32 ends with print(3.14e0). Both F32 and F64 provide ordinary arithmetic, so current historical output does not certify adopted source admission. Earlier batch0084 read float_arith as a supplemental contrast, not an executed green or a primary admission; retain that evidence snapshot with this later qualification.

## Guarantees and Completion

Recover original63b9b302 arithmetic/IEEE operation intent and float_f32's typed receiver intent. Supply explicit type/suffix context at the unconstrained occurrences, preserving six arithmetic/comparison outputs and four F32 outputs. Keep a genuinely ambiguous F32/F64 rejection contrast and typed F32 versus F64 operations, without reintroducing a hidden default type or weakening forward inference. Clarify incidental historical double-representation comment if it implies a semantic guarantee; no F32 numerical-floor redesign belongs here.

Later repair requires RED/GREEN for intended source reason, meaningful output assertions and independent review. This audit changes/executes neither source nor compiler, does not certify all floating semantics, and does not transfer unread primary obligations. reject/float_remainder detection isolation remains com-ntm8, not a new permitted floating remainder feature. Meta evidence/test-audit/scoped-reviews/frontend-batch-0015.json and its independent receipt retain limits.

## Explicit Numeric-Base Supplemental Control

Batch0019 adds run/int_literal_bases.pw/.out. The final print(1_000.5) has no unique F32/F64 context under generic print[T], even though the ten earlier integer/base/suffix observations have explicit or inherited types. Preserve all eleven expected lines by establishing explicit float context; do not drop numeric separators or introduce an implicit float default. This is a supplemental source/oracle read, not a newly completed primary outcome or execution.

## Direct-Literal Cast Contract Reconciliation

Batch0032 adds exactly run/float_cast.pw/.out as the fourth finite pair. Its first
three int-to-float source operands have explicit I64/U64 types; the last7 as F64
was initially described as an unconditional ambiguous Source defect. That verdict
is withdrawn: frontend-handoffs:72-74 explicitly retains permitted direct
unsuffixed-literal cast context, and current castLiteralContextTerm plus
run/mid_cast_literal_context.pw protect7 as F32/-7 as F64. Current code/old goldens
do not themselves settle adopted meaning; spec02's integer literal family and
spec12's From[Source] explanation still need reconciliation with that design.

Recover the direct-literal cast decision and determine the exact permitted
literal/target pairs, contrasting typed integer operands, unsuffixed direct
literals, explicit suffixes, Bool, block-wrapped operands and newtype boundaries.
Keep all four float_cast outputs and the existing Mid literal-cast control.
If canonical records do not decide the source oracle, obtain a focused judgment;
do not silently repair the last literal, add a default source width, remove a
permitted cast, or certify it source-clean from current acceptance. This is a
finite contract/oracle question, not a confirmed compiler bug or an all-cast
rewrite. The other three named numeric-context controls remain unchanged.

Correction evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0032-cast-context-correction.json and its independent receipt preserve the original batch/receipt hashes and replace only this verdict. No source, expected output or runner was changed or executed.

## Explicit Float Lexical and Generic Context Roots

Batch0047 adds exactly run/{float_exponent,float_generic_witness,float_int_literal_ctx,float_literal}.pw/.out. Exponent/generic witness/plain literal roots lack unique F32/F64 context under generic print or generic numeric calls; preserve lexical and witness purposes with explicit context. float_int_literal_ctx separately claims ordinary integer literal becomes F64 in binding/argument/Array/operand/result contexts; spec02 names only integer-family targets, while frontend-handoffs72–74 retains direct-literal cast context only. Recover exact canonical decision before accepting or mechanically rewriting those ordinary contexts; add no implicit numeric conversion/default. Its print(1.5+2) is independently nonunique. Existing float_arith/float_f32 and corrected float_cast intake reused; do not retract permitted direct7 as F32/-7 as F64 controls or replace the pending cast decision with current acceptance.

## Explicit Empty Generic Array Float Context

Batch0049 adds exactly run/generic_empty_array_arg.pw/.out. Generic Add plus generic print does not uniquely select F32/F64 for unsuffixed seed1.5. Retain empty-array/seed and nonempty summation purpose with explicit available context in eventual repair; suffix alone does not settle the later-sibling inference contract owned by com-pxja.

## Explicit Numeric Match-Operand Context Question

Batch0054 adds exactly run/{match_expr,match_literal}.pw/.out for the annotated match-result-plus-unsuffixed1 subexpressions (match_expr38 and match_literal49). spec12 permits expected-result sharing for both bare numeric literals; body-checking forbids generic Output-to-operand propagation. Determine whether a not-yet-typed numeric match operand falls within the same permitted local expectation while preserving transparent block/if/match behavior and independent Self/Rhs/Output witnesses. Current success does not decide this source contract. Retain finite inference question rather than automatically suffixing/rejecting it or extending general backward inference; obtain judgment only if canonical rules remain insufficient.

## Explicit Mid Float Operand Integer Context Question

Batch0058 adds exactly run/mid_float_operand_context.pw/.out for final value:F32 * 2. Existing finite ordinary integer-to-float question covers spec02 integer-family-only literals versus known operand context. Preserve five decimal F32 controls and sixth multiplication purpose; do not settle the source rule by current success, rewrite automatically or conflate with permitted direct-literal cast.

## Explicit Mid Immediate Newtype Float Literal Question

Batch0059 adds exactly run/mid_newtype_literal_context.pw/.out for direct7 asRatio where Ratio=F32. Retain existing direct-literal/immediate-newtype contract reconciliation rather than blanket rejection or automatic suffix fix. Other integer extremes, suffixed operand, decimal and nested-wrapper controls remain distinct valid purposes.

## Explicit Nested Operator Literal Context Questions

Batch0063 adds exactly run/operator_literal_nested.pw/.out: ordinary integer arithmetic assigned F64 and if/match value operands next to bare arithmetic need existing finite canonical reconciliation. Spec02 integer-family-only and spec12 local literal sharing versus body-checking independent Output/operand rules must be reconciled before permission/rejection or mechanical suffix changes. Preserve eleven outputs, precedence, unsigned division/range and typed controls; no new inference rule adopted.

## Explicit Synthetic Literal Warmup Dependency

Batch0066 adds exactly run/recorded_literal_value_compatibility.pw/.out for its first unrecorded raw Expr.Int checked under F64. This current helper setup does not establish ordinary integer-to-float source permission; existing finite canonical literal-context reconciliation covers it. Preserve distinct successful I64 recorded fact and refusal to reinterpret that committed fact as F64. This batch assigns observed behavior only, not a new normal-source admission. No automatic suffix, removal or expanded float rule.
