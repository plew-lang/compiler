---
id: com-darc
status: open
deps: []
links: []
created: 2026-11-02T21:37:23Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Enforce assertion enabled Python at standard validation launchers

## Contract and audit evidence

Only actual validate/run_gate child environment and normal/gen/ASan nested tooling launcher chain: parent PYTHONOPTIMIZE survives envmerge despite config allowlist omission; python3/-B does not protect assertions. Ensure optimized mode cannot produce standard accepted gate without effective assertions.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `assert-mode-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Parent PYTHONOPTIMIZE1/2 and ordinary unset; actual nested python child assert predicate/sentinel must execute or refuse; child environment record matches enforced mode; explicit/unittest controls remain effective; standard success/failure aggregation.

## Excluded

- No wholesale allassert test rewrite, manual diagnostic mandatory registration, model/platform reset, or new CLI semantic switch. No product compiler behavior correction inferred.

## Admission boundary and prerequisites

- type: standard validation evidence soundness
- owners: ["com-9l3b", "com-p5um where measurement tooling tests required", "com-604k final integration"]
- consumer: Actual registered normal/ASan tooling tests and measurement wrapper. Source area/G1 only if relying on those tests; no unrelated source audit prerequisite.



Actual accepted connections and conditional exclusions are recorded in [tooling adoption](../../../evidence/compiler-failure-audit/tooling-owner-adoption.json). The optional restart diagnostic has no unconditional standard-gate prerequisite; recorded standard-gate edges are installed. Product repair remains open.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.
