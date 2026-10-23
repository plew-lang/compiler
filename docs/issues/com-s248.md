---
id: com-s248
status: open
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Assign D1 through D6 to current controls and responsible closure tasks

## Boundary

Phase 3F / F4. **Finite evidence-disposition task.** Parent criteria: 9, 11.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `docs/issues/met-si6j.md`; `docs/issues/com-uutc.md`; `docs/issues/com-nsxb.md`.

Produce exactly six rows using the migration evidence: D1 expected-array overwrite; D4 partial operator validity; D5 flow/ownership; D2 downstream reinference; D3 state conflation; D6 partial duplicated checks. For each select the concrete current input/control, owner/fact/final consumer, task and decisive evidence or missing evidence.

## Exit and Evidence

Every class maps to current applicable positive/reject or structural corruption controls in existing tasks; a known defect cannot be dispositioned only as future review. New required repairs become dependencies of their area and G1. Risk classes are not relabelled as newly reproduced bugs. Keep the six-row mapping in the parent, not a second mutable issue-status index.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
