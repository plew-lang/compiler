---
id: com-za4f
status: closed
deps: []
links: []
created: 2026-11-02T21:46:44Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Preserve global storage identity of callable values

## Contract and audit evidence

Exact met-tfbl proposed unit3; source storage result is producer fix, not backend arbitrary recovery.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `CALL-GLOBAL-RECEIVER`.

## Scope and guarantee

- met-tfbl V4 Local.isGlobal→ClosureLocal loss→final Mid receiver, simple noncapturing global only

## Scenarios

- Simple global/local counterpart check/native/JIT; exact declaration/storage identity retained to required receiver preflight.

## Excluded

- No new capture support or weakening preflight/string-ID recovery.

Existing global fn passes check but native/JIT fails; no repaired output claim.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "3-source", "receivers": ["met-ucze", "met-acfl", "com-61jt"], "reason": "Required existing source meaning/publication/final consumer closure; install at named area and G1, not merely assignment epic."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Required predecessor for com-r88j

Use the source target publication already implemented in eab68d76; do not depend on closure of com-r88j. com-r88j now depends on this task (tk accepted, no cycle). The newer global target must not break legitimate existing global-initializer preparation. `prepared_access_source_owner` passes with the frozen c07a4ce0 source/carrier and aborts with eab68d76 because its initializer callback is categorically rejected as ClosureGlobal. Normal function global callable execution was already unsupported and remains this task's original scope.

TDD: `tests/fixtures/run/global_callable_storage.pw` checks global-initializer call, ordinary function global call and local shadow (expected 42/42/7). eab68d76 candidate accepts check but rejects AOT/ORC Internal; meta scratch `tmp/phase3-lexical-call-binding/global-storage-red.json`. Keep global declaration target distinct through CallResolution, validate against retained source template and canonical global storage, use existing global MidPlace/LLVM helpers. No name/string recovery, no preflight weakening, no capture support expansion. Additional controls: imported alias/module global, return/function ABI, malformed target/type and local/global confusion, existing initializer source-owner probe, standard local closure positives.

Completion requires actual native/ORC receiver execution, retained-owner negative probes, original initializer prefix and applicable gates plus independent review. Source preparation alone does not close this task.

## Canonical snapshot contract and verification

Accepted product revision: **2172ca70**. Global source targets remain distinct in CallTarget. Mid copies the selected whole global into an ordinary owned evaluation temporary before arguments; call-scope cleanup owns its release. LLVM consumes the canonical receiver, with no hidden global load/retain. Optional declaration origin preserves target0 and is checked against the actual Assign source, receiver, type and capabilities. Existing copy-transfer optimizations preserve these evaluation homes.

Global preparation adds only selected Dynamic.ClosureGlobal value dependencies from saved per-owner CallTemplates, through the common preparation/order entry. Name-based dependency recovery was rejected by a real named-pow false-cycle control. Single/multiple-global cycle and failed-owner retry controls pass. General block/callee-effect startup summaries remain com-fkxl.

Evidence: meta `evidence/rejection-domains/diagnostic-domain-implementation/phase3-global-callable-snapshot.json` and `phase3-call-cache-outcomes.json`. Defect-specific RED precedes the implementation. Fresh global storage, pre-argument/callee replacement snapshot, imported alias, named pow, callable pow, Unit/String result cases pass in18modes/6native. LLVM22 ASan/LSan4 controls pass; standard gen and72old/new positive modes/12LLVM pairs pass. Final candidate build `20261120T030816-build-2d8c9f` passes, including exact native global-origin/order/existing initializer-prefix controls. Same-type source/receiver swaps, forged origin, Overwrite and inout are rejected; matching Read remains accepted.

Final whole normal run `20261120T032029-test-6ec017` completes with immutable inputs, skip0 and no worker failure:329→324fail, no additions/changed reasons. This is finite nonregression, not all-green. Alternating same-source5pairs medians6.864809→6.873567s, all10LLVM equal; no formal fixed-point update. Independent no-history reviewer `lexical_call_binding_plan_review` accepted this finite guarantee after final whole-delta review, with no remaining must-fix. Cache observation regressions were corrected in com-r88j, and existing initializer-prefix behavior is retained.

Parent com-yeua/phase3 and excluded com-fkxl/com-l4x2/com-3mh9 remain open; no new capture support, language rule, main integration or carrier promotion is claimed.
