---
id: met-q7ig
status: open
deps: []
links: []
created: 2026-11-27T07:12:54Z
type: task
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [spec, frontend, design]
---
# Decide label uniqueness for requirements closures and function types

Confirm the scope of label uniqueness before changing accepted requirement or closure signatures. Use the recorded84 family controls; separately define function-type well-formedness without changing suppressed-label or local-binder rules.


## Decision needed

Fixed da2c8c0a82e9 rejects local ordinary/generic fn, method, associated fn,
factory, provided method and default-labelled duplicate signatures. The same
named declarations imported from another module are incorrectly accepted.
That module dependence can be repaired under the existing declaration rule.

However, trait requirements and global closure literals with repeated labels
are accepted in both locations in the84 recorded family controls. spec04
requires ordered labels and includes labels in function type identity, but
does not explicitly define uniqueness within one signature. spec08/design
shared callable admission primarily specify overload validity/collision; they
do not establish this additional rule for every function-type surface.
No function-type acceptance claim is made without a separate executed probe.

Independent qualified_member_plan recommends uniform distinctness, but finds
insufficient authority to change requirement/closure acceptance automatically.
Confirm whether the same label may occur twice in any one actual callable
signature and function type, or whether the existing named-declaration-only
restriction should remain the language rule. Label-suppressed positions have
no external label and are not duplicate labels. Repeated local binder names
are a separate question and must not be changed by this decision.

## Endpoint

Record the user's decision, synchronize the corresponding spec/design contract
and assign finite implementation/verification children under met-auj6. Cover
the named/signature/requirement/closure/function-type boundaries actually
selected; preserve default/provided forwarding and existing gen policy. Do
not close from implementation convenience or a same-named checker alone.
Existing Source-domain/module-independent repair and broadened semantic
acceptance changes must remain distinguishable in test/result claims.

[Recorded evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-parameters/README.md).
