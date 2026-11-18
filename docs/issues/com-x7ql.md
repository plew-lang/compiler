---
id: com-x7ql
status: open
deps: [com-j8k0, com-ew3i]
links: []
created: 2026-11-18T15:24:06Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, ownership, verification]
---
# Preserve outer unique bindings across nested shadowing


## Contract and completion

Implement the binding-scope rules in [com-j8k0](com-j8k0.md). Have frontend
select the exact replaced binding and its scope once. Pass a binding-end
identity to Mid only when the declaration replaces a binding in the same
scope. Keep verifier state consistent with Mid; neither Mid nor LLVM should
reconstruct the decision from name spelling. Preserve RHS access, temporary
cleanup and already-consumed behavior.

Prove RED and GREEN independently of the bare-block change using an existing
statement scope. Cover old and new same-scope values with observable exactly-once
destruction, RHS move, nested shadowing with an outer read, nested shadowing with
an actual move, and borrow controls across real drop versus temporary hiding.
Exercise ordinary and relevant pattern/condition binding scopes. Check native
and ORC output with ownership sanitizer controls, then obtain independent review.

After [com-ew3i](com-ew3i.md) enables bare statement blocks, replace
`unique_shadow_cliff_use.pw` with a success fixture that retains the original
bare block and proves inner value 2, outer value 1, and their destruction order.
Keep a distinct same-scope early-destruction control.
