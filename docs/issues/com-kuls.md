---
id: com-kuls
status: open
deps: []
links: []
created: 2026-10-27T21:31:49Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile the cross-module construction regression with factory visibility


## Finite Source-Oracle Boundary

Source-only batch0012 audit at9665094d/spec5bd65a5 inspects exactly tests/fixtures/reject/construct_private_field_crossmodule.pw. Introducing69192359 intended a per-field cross-module construction prohibition. Adopted spec05 instead gates memberwise construction by factory visibility: an explicitly public memberwise factory may accept private fields. Current Dictionary exposes no memberwise factory, so this source remains invalid, but its old comment misstates the public rule. Its keys/vals/hashes/buckets are now Buffer fields while root passes [] Array literals; generic exit1 can remain even when the intended access gate is absent.

## Deliverables and Completion

Recover the exact original input/diff; preserve meaningful encapsulation coverage under the factory-visibility rule, distinguishing no exported factory, an exported factory accepting private storage fields, and forbidden later private field access. Use a stable owner-authored multi-module fixture if Dictionary internals cannot isolate that contract; do not reintroduce a field-visibility construction ban or expose Dictionary implementation fields. Preserve [:] as the ordinary public construction route. Record the selected reason and valid neighboring controls with RED/GREEN and independent review in the later repair.

Audit records no observed compiler failure and changes no test, Std or runner. This is one finite input-oracle/detection repair, not an all-construction rewrite or a new language choice. meta/evidence/test-audit/scoped-reviews/frontend-batch-0012.json and independent review retain source-only limits.
