---
id: com-gye8
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, driver, diagnostics]
---
# Distinguish undeclared dependencies from unavailable declared inputs

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `DEPENDENCY-FAILURE-CAUSE`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Manifest resolution empty sentinel merges undeclared dependency with declared-but-missing lock/referrer/commit. Loader currently blames missing declaration for both. Preserve required resolution refusal origin, not merely change renderer wording.

Finding references: dependency-cause, B070/1 B075/2.

## Covered source boundary

- Manifest.resolveDepImport/resolveGitDepImport126-187
- Frontend1772-1788 required import resolution
- Lock.lockCommitForConstraint
- Resolver/source acquisition failure propagation

## Guarantees and scenarios

- Undeclared @name, declared missing lock, absent referrer/commit, unavailable cache source and valid path/git dependency give appropriate originating failure, never phantom accepted module.
- Shared check/build/run equivalent fixed inputs obey same rule while expected body/request scopes remain different.

## Excluded

- No new dependency grammar, automatic resolver command policy or multi-version solver work.
- No direct fsuq prerequisite; producer domain channel separately covers tested negative source lanes.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.
