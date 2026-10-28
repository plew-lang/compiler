---
id: com-wfq2
status: open
deps: []
links: []
created: 2026-10-27T21:28:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Reconcile the selected conditional trait-edge test oracles


## Finite Audit Question

At source baseline9665094d/spec5bd65a5, inspect exactly tests/fixtures/reject/conditional_conformance_edge_path.pw with .err and run/conditional_conformance_edge_path.pw with .out. Both declare impl[T] Source[T] as Target where T:Required, conditioning a trait-to-trait edge on selected Source instances. Spec08 explicitly excludes separate conditional trait-to-trait conformance and requires the full declared source range. Original4bfa4247 tests condition discharge along such an edge; current accepted implementation behavior is not an adopted language oracle.

## Deliverables and Completion

Recover that exact introducing body/diff and canonical decisions, distinguishing a deliberately retained current unsupported-feature lane from adopted-valid source. Under the adopted prohibition, identify the meaningful declaration rejection and preserve conditional-proof propagation through legitimate nominal conformances/unconditional trait edges in neighboring controls. Decide deletion, movement, or rewritten test purpose from original intent rather than blessing current acceptance. A contrary semantic change needs user approval; ordinary application of the explicit prohibition does not. Assign exact test/consumer corrections and applicable RED/GREEN/independent review before closing this investigation.

The positive additionally uses foreign I64 as Required; com-z4ns explicitly owns that setup separately. No broad trait redesign, compiler/test/expectation change or real execution occurs during audit. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0011.json and its independent receipt. Unread primary/control obligations remain audit work; this is not a whole-corpus handoff.

## Explicit Declaration Trait-Assumption Conditional Edge

Batch0043 adds exactly run/declaration_trait_assumptions.pw/.out. Source[Arg] declares no Arg:Required constraint, but impl[P] Source[P] as Middle[P] where P:Required limits an edge to selected instances. Spec08 full-source-range rule forbids this distinct conditional trait-edge feature. The Wrong[Other] Missing oracle exercises that current lane, so preserve legitimate explicit bound/associated output/unconditional path and shrinking repeated-edge purposes while reconciling adopted-valid setup/oracles from original intent. This is not a ban on nominal Box[T]:Source[T] where T:Required or unconditional Middle[Q]:Target[Q] and Cycle edges. No semantic relaxation or automatic deletion is authorized; no compiler/test change or real execution during audit.

## Explicit Mixed Existential Method Condition Edge

Batch0045 adds exactly run/existential_method_condition_mixed_path.pw/.out. Base[T] itself has no T:Marker premise, but impl[T] Base[T] as Derived where T:Marker restricts the edge to selected source instances, prohibited by spec08 full-source-range rule. Preserve mixed hidden associated/caller generic condition proof purpose via legitimate nominal/unconditional paths or explicitly bounded implementation lane. Ordinary nominal Wrapper conditional tests are not this violation.

## Explicit Synthetic Call-Evidence Conditional Edge Setups

Batch0069 adds exactly run/{source_call_proof_boundary,source_call_proof_evidence}.pw/.out. Both embedded sources declare unconstrained trait B[V], then impl[V] B[V] as P where V:Q, narrowing the declared source range contrary to spec08. Original adding1a83e292/93d44d1e contains this setup. Preserve four-family receiver/declaration/condition/cycle evidence checks and StaticMethod selection closure through valid nominal/unconditional setup or an explicitly bounded current implementation lane; do not bless ordinary conditional trait-to-trait conformance. Synthetic empty Operator/Protocol operands isolate evidence, not general signature/source admission.

## Explicit Static Member Condition Producer Setup

Batch0070 adds exactly run/source_member_condition_evidence.pw/.out. Embedded unconstrained trait B[V] is restricted by impl[V] B[V] as P where V:Q, contrary to spec08 full-source-range rule. Original cac8b92f establishes this condition-proof producer intent. Preserve nonzero selected child conditions and missing/wrong proof-variant guards using legitimate nominal/unconditional setup or an explicitly bounded current implementation lane. Do not infer permission from current producer success or silently delete the finite evidence regression.
