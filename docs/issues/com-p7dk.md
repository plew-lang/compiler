---
id: com-p7dk
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Retain git query and archive producer status before dependency publication

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `FETCH-STATUS`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Actual Resolver checks mirror/materialize final status but listTags/resolveCommit bytes lose query status; archive upstream git status can disappear behind tar success. One finite acquisition-status unit must retain every selected command status and commit cache tree only after acquisition success.

Finding references: FETCH-QUERY-STATUS, FETCH-UPSTREAM-STATUS, fetch-status.

## Covered source boundary

- Fetch.run/listTags/resolveCommit/ensureMirror/materialize17-91
- resolve/Resolver114-150
- cache source-directory existence shortcut

## Guarantees and scenarios

- Same usable tag/commit bytes with status0 vs7 must differ; launch failure and no compatible valid tag remain distinct.
- Real git stub valid archive bytes then7 vs archive0 vs downstream tar failure; no current-success cache marker after failure, retry cannot accept stale partial tree.
- Keep locked provenance/referrer/version semantics; no network dependency needed for controls.

## Excluded

- No joint-solution/version solver redesign, universal process API migration or arbitrary shell safety proof.
- No direct com-fsuq prerequisite for package acquisition failures.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.
