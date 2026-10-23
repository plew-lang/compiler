---
id: com-lzpe
status: open
deps: [com-9l3b]
links: []
created: 2026-10-23T10:41:59Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Synchronize phase three parents and discharge the eleven criteria

## Boundary

Phase 3G / G3. **Final closure and handoff.** Parent criteria: 11.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `docs/issues/met-si6j.md`; `docs/issues/com-604k.md`.

After G2b, verify final evidence applicability against the already closed area contracts and append the final gate references without claiming an earlier binary had passed them. Update the single parent checklist and meta worklog/progress; ensure all required descendants, deferred-scope reasons and remaining phase-four owners are explicit.

## Exit and Evidence

Every parent criterion is backed by current evidence, all required area contracts/children are closed and no in-scope unresolved item is hidden in prose. Then close met-si6j and hand off to phase four. This does not merge main, promote seeds or close com-604k: integration follows the whole conformance plan. If a missing criterion is found, reopen its real task and block G3; do not weaken a criterion.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
