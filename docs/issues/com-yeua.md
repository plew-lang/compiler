---
id: com-yeua
status: open
deps: []
links: []
created: 2026-11-02T21:30:19Z
type: task
priority: 1
assignee: Koji Murata
tags: [diagnostics, frontend, driver, verification]
---
# Carry producer failure domains to compiler rejection consumers

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `SOURCE-FAILURE-DOMAIN-CHANNEL`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Current mixed service/CLI Failure/status1 cannot soundly discriminate intended source rejection in existing finite negative consumers. Add a fail-closed producer-owned discriminator through returning service/cache/terminal adapter for named cases; do not derive class from final text. Exact external carrier/API representation must be chosen and documented within current diagnostic/driver contracts.

Finding references: SERVICE-DOMAIN-LOSS consumer distinguishability, rejection-domains80controls/32false-success.

## Covered source boundary

- CheckedProgram CompilerSessionResult/ProgramCheckResult/Result caches
- Compiler compileSource/runCheck/runProgram adapters
- DeclarationProgram and PreparedProgram typed origins before conversion
- normal reject/partreject, expose18, ASan B channel integration; gen channel is separately consumed by com-k4c9

## Guarantees and scenarios

- Returning source rejection vs wrong-session/raw invariant/implementation-limit/tool-input failure with same rendered Error/status are distinguishable.
- Drain/repeat failure keeps its origin; internal default/unclassified fails closed.
- Actual process adapter controls cover silent1, internal1, status2, signal, timeout, diagnostic then signal versus correct source rejection.
- Define minimal typed/per-run channel and its lifetime; public status or callback ABI changes require explicit documented decision, not implicit adoption.

## Excluded

- No compiler-wide blanket panic rule or stable public diagnostic serialization mandated.
- No source semantics or all-runner expansion.
- Parent audit classification is evidence, not this product channel.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.

