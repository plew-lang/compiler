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
# Give selected floating arithmetic controls explicit numeric context


## Finite Supplemental Source Repair

Source-only batch0015 audit at9665094d/spec5bd65a5 reads exactly run/float_arith.pw/.out and run/float_f32.pw/.out. Spec02 provides F32/F64-polymorphic decimal literals with no default numeric type. float_arith passes bare-literal arithmetic/comparisons into generic print without a unique floating context; float_f32 ends with print(3.14e0). Both F32 and F64 provide ordinary arithmetic, so current historical output does not certify adopted source admission. Earlier batch0084 read float_arith as a supplemental contrast, not an executed green or a primary admission; retain that evidence snapshot with this later qualification.

## Guarantees and Completion

Recover original63b9b302 arithmetic/IEEE operation intent and float_f32's typed receiver intent. Supply explicit type/suffix context at the unconstrained occurrences, preserving six arithmetic/comparison outputs and four F32 outputs. Keep a genuinely ambiguous F32/F64 rejection contrast and typed F32 versus F64 operations, without reintroducing a hidden default type or weakening forward inference. Clarify incidental historical double-representation comment if it implies a semantic guarantee; no F32 numerical-floor redesign belongs here.

Later repair requires RED/GREEN for intended source reason, meaningful output assertions and independent review. This audit changes/executes neither source nor compiler, does not certify all floating semantics, and does not transfer unread primary obligations. reject/float_remainder detection isolation remains com-ntm8, not a new permitted floating remainder feature. Meta evidence/test-audit/scoped-reviews/frontend-batch-0015.json and its independent receipt retain limits.

## Explicit Numeric-Base Supplemental Control

Batch0019 adds run/int_literal_bases.pw/.out. The final print(1_000.5) has no unique F32/F64 context under generic print[T], even though the ten earlier integer/base/suffix observations have explicit or inherited types. Preserve all eleven expected lines by establishing explicit float context; do not drop numeric separators or introduce an implicit float default. This is a supplemental source/oracle read, not a newly completed primary outcome or execution.
