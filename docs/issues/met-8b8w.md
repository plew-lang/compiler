---
id: met-8b8w
status: open
deps: []
links: []
created: 2026-10-21T15:41:34Z
type: task
priority: 2
assignee: Koji Murata
parent: com-vy62
tags: [frontend, driver, verification]
---
# Close current gen handoffs without introducing macro-role syntax

## Scope and Boundary

Current-feature implementation/verification split from [com-vy62](com-vy62.md) for [com-604k](com-604k.md), after the independent phase-one review [met-8jd4](met-8jd4.md). Source inspection input: compiler `cf2cc2ef`, spec `1e0c4d0`, Syntax `00f740e1`. The current implementation provides ordinary `Derive`/`ParameterizedDerive` traits and trait-based providers; new `macro X as ...` declarations, host-only `macrointerface`, macro-role registration/visibility and migration of standard providers to that public form are absent and remain in the parent. Introducing them is not a completion condition of this child.

This is an explicitly bounded migration step, not adoption of the legacy runtime-trait provider model as the final design. Its completion does not establish the adopted macro-role contract or close com-vy62. Preserve ordinary trait/conformance semantics and source visibility; do not create compiler-only name exceptions to simulate the future role model.

The [root-owned use contract](../design/sources-and-modules.md#root-owned-use-bindings) applies to target output as to every ordinary part. Target output must omit `use`/`pub use`; consumer roots explicitly supply documented support bindings. The corresponding current provider/consumer migration is owned by [com-w4c2](com-w4c2.md), while this task preserves normal generated-part admission without hoisting or a macro exception. Host provider/harness imports remain in their own module roots. This does not add new macro-role syntax to either task.

## Existing Producer to Final Consumer

Use three end-to-end increments under the current admitted provider forms:

1. Preserve bare versus parenthesized directive form, including empty parentheses, from parsing/recording to configuration construction and selected existing provider call. Move source-slice/range decoding to the provider's selected library-owned String-to-String handoff, then check the returned generated source normally. Internal adapters may realize this existing boundary; no new public authoring syntax or fake macro-role proof is required. Preserve annotated-item AST availability without requiring the not-yet-generated target conformance.
2. Retain selected provider declaration/package/configuration identity and partition incompatible provider graphs into isolated host units. Execute compatible-unit invocations with common state and source order; transport one private framed String result per invocation, separating incidental prints/diagnostics. The runner alone assembles and publishes the target. Do not transport nominal AST values across host-version boundaries.
3. Produce recorded-input receipts from the selected current provider/source/configuration graph and consume them at ordinary generated-part admission. Reject missing/stale output and incomplete/failed publication; preserve committed-output cold checkout and the approved Go-style external-input limits. Future macro-role facts must not be fabricated in a receipt or inferred as implemented from this current-form result.

## Removal and Verification

Remove argument-count-only form selection, compiler-owned AST decoding on migrated handoffs, stdout-as-result ambiguity and file-existence-only generated-output admission for the affected current routes. Preserve ordinary construction/visibility and target-source checking. Host-unit/provider identity must be fixed before framing/receipt publication; internal increments own those producers instead of waiting on an unspecified new role feature.

Use valid bare/configured/empty-parenthesized current providers, original spans, incidental print, compatible-unit state, incompatible Syntax graphs, invocation order, partial failure/no publication and fresh/stale/missing receipt controls. Exercise gen then ordinary check/build/run admission, with standard gen/dependency/normal/sanitizer/fixed-point/performance gates as applicable at milestones. Formal self-compilation target remains below 7 seconds.

No compiler/test/performance execution was performed while splitting this scope. Close only with actual revision/scope, final-consumer evidence and replaced-path removal. Retain new macro public-form work in the parent; a current-form receipt/handoff is not proof of that future declaration/role implementation.

## Test Audit Evidence

Scoped audit at compiler test/source baseline `9665094d` is saved in
[review dispositions](../../../evidence/test-audit/scoped-reviews/disposition.json).
Driver findings 4/6 identify invalid legacy provider shape in privatefield and
missing same-provider state / bare-versus-empty-parenthesized controls. These
are evidence for this existing scope, not new macro-role syntax or audit closure
prerequisites. Recover original private-access intent under ordinary factory
visibility; do not preserve obsolete blanket private-field rejection by accident.
