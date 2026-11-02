---
id: com-f0fn
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Represent oversized package version components as input failure

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `VERSION-PARSE-LIMIT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Unbounded parseVer decimal U64 accumulation reaches normal checked arithmetic panic condition. Choose checked numeric parse/representation result and propagate package input/implementation limit rather than using arithmetic panic as source rejection.

Finding references: VERSION-COMPONENT-INPUT-OVERFLOW, version-component-overflow.

## Covered source boundary

- Version.parseVer10-29/compareVer/satisfies/pickLatest
- Resolver126-127
- Core.Num U64 Add/Mul and Lower/Impl numeric checked mapping; Arith checked helpers

## Guarantees and scenarios

- Boundary U64 values, above-bound decimal, leading zeros, valid ordinary components and unbounded external tag byte input.
- Valid numeric ordering/constraint meaning preserved; oversized component returns explicit package input/representation failure, no wrap/signal counted as intended rejection.

## Excluded

- No silent new semver grammar/length restriction, arbitrary huge-test requirement or solver redesign.
- No direct fsuq dependency for package input.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.
