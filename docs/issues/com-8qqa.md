---
id: com-8qqa
status: open
deps: []
links: []
created: 2026-11-02T21:37:24Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Propagate dependency harness lock query failures

## Contract and audit evidence

Only test-deps.sh lock-field/count queries85/99/114/151 and their extraction pipelines/check boundary. Downstream expected-looking text or last pipeline status cannot erase failed lock read/query.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `deps-query-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Selected lock valid expected value/count; malformed/missing/unreadable lock; failed query with expected-looking partial bytes and downstreamsed0; normal mismatch; package runner failure preserved.

## Excluded

- No resolver grammar/manifest/source policy implementation, full resolver IO publication redesign, gen/fsuq negative scope or all shell pipeline audit.

## Admission boundary and prerequisites

- type: standard dependency runner evidence
- owners: ["com-9l3b", "com-604k integration"]
- consumer: Actual ./validate deps fixed package/lock assertions before dependency lane acceptance; not automatic all G1 dependency.



Actual accepted connections and conditional exclusions are recorded in [tooling adoption](../../../evidence/compiler-failure-audit/tooling-owner-adoption.json). The optional restart diagnostic has no unconditional standard-gate prerequisite; recorded standard-gate edges are installed. Product repair remains open.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.
