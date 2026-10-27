---
id: met-bejv
status: open
deps: []
links: []
created: 2026-10-27T20:48:04Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile extension binding assumptions in two module rejection fixtures


## Exact Unresolved Test Assumptions

Source-only audit at compiler9665094d/spec5bd65a5: exact `tests/fixtures/partreject/extension_bundle_crossmodule/{Main,A,B,Lib}.pw` plus Main.err and `tests/fixtures/partreject/extension_private_method/{Main,Ext,Lib}.pw` plus Main.err. The first expects duplicate members from separately authored A.Extra/B.Extra although Main merely namespace-imports A/B. The second namespace-imports Ext but spells unqualified #Extra and expects method-private rather than missing selector binding.

Spec15 requires explicit binding when naming #Ext; spec09 merges parts of the same resolved extension identity. Neither alone proves same spelling across different module owners creates one identity or that loading a namespace binds its contained extension globally. Current Lower/Impl extId interns spelling; this is an implementation observation, not an adopted name-resolution rule. Treat these exact expected reasons as unresolved/current-lane assumptions rather than confirmed valid normative rejection or proven current compiler bug.

## Deliverables and Completion

Recover original purposes and adopted extension declaration identity/publication policy; distinguish same-extension parts from different owners, namespace/selective/alias binding, private method visibility and authorized opt-in. Use a same-owner duplicate negative and distinguishable-owner/explicit-binding controls as appropriate to an already adopted rule. If declaration publication/identity policy is genuinely unspecified, obtain a surface decision before changing acceptance. Do not invent global-name union or automatic namespace flattening from current behavior.

A bounded canonical disposition and concrete owned correction close this investigation; TDD/scoped review apply to later repair. No compiler/test/runner repair in audit, no general extension feature rewrite, and no unread fixture transfer. Broader historical com-uutc extensions/duplicate-declaration range remains separately unclosed. Evidence will be meta/evidence/test-audit/scoped-reviews/frontend-batch-0005.json.

## Explicit Third Cross-Module Bundle Assumption

Batch0007 adds exactly `tests/fixtures/partreject/trait_subject_cycle_extension_crossmodule/{Main,A,B,Lib}.pw` plus Main.err. It expects the A-as-B/B-as-A edges from separately owned same-spelling E bundles to merge and form a cycle, although source does not identify them as one resolved extension. The cycle rejection is correct if they are parts of one extension; the unresolved issue is that identity premise. Include this third root with the earlier two, preserving genuine same-resolved-bundle cycle controls and distinct-owner comparisons. Do not relax cycle verification or choose global spelling identity during audit.
