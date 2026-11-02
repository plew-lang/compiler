---
id: com-tvgb
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, driver, diagnostics]
---
# Reject failed or partial source reads before registering source facts

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `SOURCE-READ-RESULT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

SourceAccess.read and current runtime read APIs return bytes only; exists→read is not successful-read evidence. Return input/environment failure before append/parse/publication while retaining valid empty sources.

Finding references: SOURCE-READ-FAILURE-AS-DATA, source-read, input-read-and-toml read portion, io-status input.

## Covered source boundary

- SourceAccess.exists/read47-61
- Frontend1716-1734 actual source append
- Backend1487-1489 runtime read; std/Io read boundary
- Manifest.loadManifestDeps/loadLock and Resolver reads only for acquisition propagation

## Guarantees and scenarios

- valid empty filesystem/Text/embedded resource versus absent embedded resource.
- exists true then open failure; seek/ftell/read error and short prefix cannot register complete source success.
- Required imported/root source error retained to fresh open/check failure; no read-success inferred from empty/nonempty bytes.

## Excluded

- No blanket public std API redesign, caching/source freshness architecture or arbitrary filesystem-race proof.
- No direct com-fsuq prerequisite merely because both involve failures.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.
