---
id: com-vv94
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Reject failed native spawn initialization before using its resources

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `NATIVE-SPAWN-INIT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

posix_spawn actions/attribute init explicitly report ENOMEM, but current tool uses/destroys objects without checking initialization. Fail closed on that existing resource channel; do not invent universal recovery.

Finding references: NATIVE-SPAWN-INIT-RESOURCE-GUARD, native-os-setup.

## Covered source boundary

- native/tool.cpp72-131 run actions/attrs init and teardown
- supported-host POSIX init contract

## Guarantees and scenarios

- Controlled actions-init failure, attrs-init after actions success, addopen/chdir failure, spawn failure, EINTR wait and successful child status.
- Never use/destroy uninitialized opaque resources; clean only initialized objects and preserve established signal state.
- Explicit setup failure must not be labelled source refusal; terminal setup error is sufficient.

## Excluded

- No arbitrary allocator recovery, universal libc fault resilience, process group/reusable-host redesign or new fsuq gate.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
