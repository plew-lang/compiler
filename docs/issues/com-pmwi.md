---
id: com-pmwi
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:41:17Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, diagnostics, verification]
---
# Narrow native JIT observation and error-report inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-native-and-path.json), [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-native-and-path.json); fixed source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md); independent of com-jno0/phase 3. No repair has been performed by this audit.

## Guarantee and Scope
Trace/error helpers cannot mutate unrelated JIT resources; preserve optional failure latch, printable instance identity, progress event count/order, owned error disposal and outputs.

Affected private APIs only: traceJitUnit and jitError. Observation needs trace policy, mutable completion counter, printable opaque instance identity and explicit session/body/stage. Error reporting needs owned llvm::Error plus optional failed-latch reference; creation failures have no JIT owner. Neither helper needs engine, symbol maps, lazy descriptors or resource mutation. Preserve disabled-trace count behavior, completed-boundary order/flush/output and failure retention. The public trace setter, verifier/optimizer/empty-name APIs and all JIT lifecycle/materialization/public C signatures stay unchanged.

## Actions and Completion
Inventory actual callers and delegated effects for these exact APIs. Apply TDD/refactor rules with behavior-preserving controls, narrow real signatures and update consumers, remove competing broad alternatives, and prove no full compiler/JIT authority is retained indirectly. Preserve failure provenance, source/session identity, borrowed/owned native lifetimes and ordering. Obtain independent review and gates appropriate to the future change.

## Excluded
JIT lifecycle/materialization algorithms, diagnostic wording redesign, public C ABI changes and runtime behavior changes.


## Adopted Implementation Intake

[com-k35g](com-k35g.md) classifies this exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain the open repair.

[Scoped intake outcome](../../../evidence/existing-feature-conformance/audit-intake/api-session-and-inputs.json) preserves every main/mixed role and the normative reason. Native JIT trace/error helpers use policy/counter/owned LLVM error/failure latch rather than engine mutation. Public ABI, materialization and resource lifetimes remain existing contracts.

The original audit-time independence does not waive this implementation admission. Keep the original finite guarantee, caller/delegate/control and excluded optional scopes. This is assignment only, not product repair/GREEN.
