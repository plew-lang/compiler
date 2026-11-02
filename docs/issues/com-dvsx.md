---
id: com-dvsx
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, verification]
---
# Publish development build output only after successful linking

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `DEV-BUILD-PUBLICATION`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Actual unchanged compiler/plew control replaces previous artifact on linker exit7. Native PendingFile is existing contrasted mechanism, not coverage for development shell.

Finding references: DEVELOPMENT-BUILD-PUBLICATION, driver-publication build.

## Covered source boundary

- compiler/plew build final linker -o output152-157
- native/tool.cpp PendingFile/build staging as comparison

## Guarantees and scenarios

- Real shell CLI with controlled linker success, compiler refusal, linker partial output then7, cancellation; previous good destination unchanged on failed link.
- Stage beside final destination, commit after link0, cleanup stage on failure; preserve real child status and bare file/package paths.

## Excluded

- No bootstrap/seed/public install redesign; no assumption object alone is executable.
- Not prerequisite of semantic reject/partreject oracle com-fsuq.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
