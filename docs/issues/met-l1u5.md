---
id: met-l1u5
status: open
deps: []
links: []
created: 2026-10-27T20:48:04Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile package API closure rejection with actual public reachability


## Finite Test-Oracle Question

Source-only test audit at compiler9665094d/spec5bd65a5: `tests/fixtures/partreject/import_reexport_signature/{Main.pw,Barrel.pw,A.pw,Main.err}` expects a public API closure error for Barrel.f(secret: Secret)->Secret, where Secret is private to Barrel. But this relative-module fixture has no package manifest or src/_.pw exposing Barrel.f as package-external API. Spec15 public API closure applies to names reachable from the package root public surface, not every pub declaration in an internal module. The selected imported I64 overload is itself valid.

Recover original32356b8d intent and determine current package/standalone admission assumptions; do not use the current check-all-pub implementation as the oracle. Provide a genuinely package-public leak negative and an internal-module/public-overload positive consistent with publicapiclosure_imported/wherebound. Preserve per-overload public-signature checks and original import/reexport provenance. If standalone-package policy lacks a prior adopted decision, ask before changing source admission.

## Completion and Limits

Finite expectation disposition and concrete correction ownership; later repair needs TDD and scoped review. This audit changes neither compiler nor test/expectation. com-uutc retains its broader historical uninspected combinations; this exact fixture/oracle task neither closes nor silently expands that mixed task. No whole visibility/API implementation audit, no unread-work transfer. Evidence will be meta/evidence/test-audit/scoped-reviews/frontend-batch-0005.json.

## Explicit Five-Root Same-Question Extension

Source-rejection batches0006/0007 add exactly `tests/fixtures/partreject/public_factory_hidden_parameter`, `publicapiclosure`, `publicapiclosure_assocbinding`, `publicapiclosure_global`, and `publicapiclosure_newtype` (each Main.pw, Lib.pw, Main.err). Each asserts package-public API closure without a manifest/src/_.pw exposing the relevant public surface. This brings the finite investigation to six roots, preserving factory parameter, returned/field type, associated binding, global and newtype distinctions. Do not change expectation merely to mirror current packageRootModuleOf fallback treating each standalone Lib as root; reconcile the adopted standalone/package policy first. No unread unit is transferred.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 34.

Row34: Do not enforce closure on every internal pub; preserve actual imported I64 overload/per-overload provenance. Standalone policy remains undecided. Package-root reachable public API closure is an input/declaration admission rule, not a new body-type feature. Six standalone-root oracle premises need met-l1u5 finite canonical reconciliation before this admission closes. Required admission: com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
