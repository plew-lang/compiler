---
id: com-loyb
status: open
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify source conversion proofs retain exact endpoints and ownership

## Boundary

Phase 3C / C5. **Bounded closure verification.** Parent criteria: 2, 3, 4, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Ir/ConversionProofs.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Follow the admitted structural/path/box conversion families from saved source endpoints/owner and pending completion into final argument/aggregate conversions. Inspect source construction completion separately from execution-time grounding; verify no post-outcome write or alternate conformance query repairs a missing source conversion.

## Exit and Evidence

Use existing pending-source, wrong-owner/path/proof and actual closure/boxing controls. Record endpoint/owner/instance validation and final consumers for each current conversion family. Any missing evidence is rejected or repaired at its producer, never guessed from equal ABI. Runtime representation/ARC optimization and unsupported conversions remain outside this task.

Existing starting controls: `pending_source_conversion_completion`, `source_conversion_owner_requests`, `declaration_conversion_closure`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
