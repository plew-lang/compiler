---
id: com-a08g
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, frontend, verification]
---
# Validate consumed dependency and lock fields before resolution

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `PACKAGE-FIELD-ADMISSION`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Current supplied Manifest/Lock records can default required consumed values or ignore unsupported field shape. Validate current consumed source choice/identity fields with explicit unsupported/input result; coordinate canonical fixture schema without silently implementing future package facilities.

Finding references: PACKAGE-INPUT-STRING-BOUNDARY field-admission portion, package-schema-escaping.

## Covered source boundary

- Manifest.parseManifest43-74
- Lock.parseLock88-106
- Resolver.runResolver/needsResolution
- Frontend required dependency load

## Guarantees and scenarios

- Absent manifest for bare source remains allowed; supplied malformed package record is different.
- Missing/empty required git/path identity, incompatible source choices, malformed lock entry and unsupported supplied shape fail before required source resolution.
- Version absence retains documented free constraint where permitted; do not make every field mandatory.

## Excluded

- No all spec17 new member/bin/tool/native facilities implemented, no fixture acceptance rule guessed.
- No broad schema rewriting inside TOML termination repair.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.

