---
id: com-j1cl
status: open
deps: []
links: []
created: 2026-10-27T21:41:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Clarify the direct and provided member collision oracle in one extension


## Finite Adopted-Oracle Question

At source/test9665094d/spec5bd65a5, examine exactly reject/extension_direct_provided_surface_overlap.pw (no companion). It rejects direct Sample.same and trait A's provided same inside one named extension E, even with no call. Introducing2b00f0c7 deliberately added the collision check now in Lower/Registration730-748. Current rejection establishes implementation intent, not the adopted source oracle.

Spec09 rejects only unselectable same-extension collisions and permits distinct trait provenance; its named direct/direct and same-trait cases do not expressly settle direct versus provided. Spec07 gives inherent members priority on the bare surface, but does not expressly extend that priority to named bundles. Determine whether an existing canonical decision fixes E.same versus E#A.same before changing this negative. Do not infer a new priority, ban or public rule from the implementation comment alone.

## Completion and Limits

Recover original selected-root diff and canonical design/spec grounds; document the chosen applicable existing rule or seek user judgment if the direct/provided priority remains a source-surface choice. Assign precise test/oracle correction with normal valid direct/inherent-provided, two-trait selector and truly inseparable duplicate contrasts, plus normal declaration-check/no-use paths. Preserve source provenance through selected consumer; no local spelling exception.

This audit performs no compiler/test/expectation change or execution and does not reopen all extension lookup. Meta evidence/test-audit/scoped-reviews/frontend-batch-0014.json and its independent review own scoped evidence. Unread primary units stay in their audit.
