---
id: com-cpi4
status: open
deps: []
links: []
created: 2026-11-02T21:39:10Z
type: bug
priority: 2
assignee: Koji Murata
parent: met-k7ks
tags: [diagnostics, verification]
---
# Preserve compiler callback refusal before checking success payload

## Existing authority and finite increment

This is a finite implementation increment under [met-k7ks](met-k7ks.md), not a competing diagnostic owner. Origin: [com-6lza](com-6lza.md), [bounded source evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), and [dependency review](../../../evidence/compiler-failure-audit/correction-owner-adoption-review.json).

## Scope and guarantee

native/llvm_backend.cpp consumeModule callback status versus output-pair validation. Handle legitimate failed callback status and its owned cause before interpreting missing output as malformed success; retain module/context disposal and zero/success/malformed pair distinctions.

Finding aliases: CALLBACK-CAUSE-SHADOW.

## Scenarios and completion

Use meaningful lower-API RED for the named cause-reduction branch with valid success, intended source refusal, non-source/internal/limit refusal where the entry contract admits it, and malformed raw validator input separately. Test conversion, retained failure/re-request and final consumer; native scope additionally requires owned-output cleanup controls. Preserve diagnostic precedence and original provenance when available; do not fabricate source precision. Reconcile all applicable cases, run affected checks and obtain independent review. Saved static evidence is not execution/GREEN.

## Excluded

No universal rich error object, new stable code taxonomy, wholesale panic conversion, CLI/ABI policy change, hidden semantic reselection, surviving-host recovery or unrelated diagnostic-family migration. Other met-k7ks work does not become a prerequisite of this finite increment.
