---
id: com-twjr
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, frontend, verification]
---
# Return package input errors for nonprogressing TOML values

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `TOML-INPUT-ERROR`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Current array readValue can repeat same cursor on mismatched delimiter; actual current isolated API stalled. Add bounded parser error/progress representation and propagate to actual Manifest/Lock/Resolver callers.

Finding references: TOML-NONPROGRESS, toml-input-termination, input-read-and-toml parser portion.

## Covered source boundary

- Toml.readBare137-175/readValue224-249/parseToml
- Manifest.parseManifest
- Lock.parseLock
- Resolver current package/lock publication

## Guarantees and scenarios

- Valid empty/scalar arrays and inline table; mismatched value=[}, truncated array/value and missing required field distinguished.
- Actual parser entry terminates with represented input failure; no partial lock/package success.
- Watchdog stall never counts as source rejection.

## Excluded

- No complete TOML implementation, package canonical-schema feature migration, escape repertoire decision or historical parser work reopening.
- Not com-fsuq broadening.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.
