---
id: com-oxeu
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Preserve literal package strings through locks and git arguments

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `PACKAGE-STRING-ROUNDTRIP`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Lock.emitStr/emitArr write raw quoted bytes and readQuoted has no matching escaping; Fetch.q adds single quotes without caller validation claimed by its comment. Establish literal byte transport or represented supported-input refusal before commands.

Finding references: PACKAGE-INPUT-STRING-BOUNDARY quoting portion, package-schema-escaping.

## Covered source boundary

- Lock.emitStr/emitArr211-236/writeLock
- Toml.readQuoted115-134
- Fetch.q23-27
- Resolver URL/tag acquisition flow and Version.tagName

## Guarantees and scenarios

- Admitted URL/path/tag strings containing quote/backslash roundtrip without changing values or command argument boundaries; unsupported spelling rejected explicitly before tool invocation.
- Controlled local git argv observer, no shell payload/network required; lock write/read preserves exact bytes and deterministic order.

## Excluded

- No new package string syntax, global shell API rewrite or arbitrary injection proof; proper error is acceptable for genuinely unsupported declared subset.
- No fsuq dependency.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
