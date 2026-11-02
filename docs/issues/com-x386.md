---
id: com-x386
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [backend, driver, verification]
---
# Return non-success when required compiler text output fails

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `TEXT-OUTPUT-RESULT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Current void fwrite/writeText channel and finishCompilation can report Success after required output failure. Old-carrier runtime-output controls establish finite observed channel; current writeText repair needs current-path controls.

Finding references: TEXT-OUTPUT-STATUS-LOSS, io-status output.

## Covered source boundary

- Backend LlvmModule.writeText/emitLlvm
- Backend emitLlvmRuntime plew_write_raw1386
- Compiler.finishCompilation109-118 and required runtime/text CLI adapter

## Guarantees and scenarios

- Normal stdout byte-identical; closed descriptor/write failure/flush failure returns non-success and no admitted complete artifact.
- Current writeText versus runtime artifact paths explicitly controlled; stderr failure distinguished from source rejection.
- Owned module/context released normally after output failure; do not double-free transferred native pair.

## Excluded

- No requirement native verifier on raw diagnostic/seed LLVM text, no general logging reliability or all print APIs migrated.
- Not a semantic rejection consumer prerequisite.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
