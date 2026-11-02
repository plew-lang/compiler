---
id: com-uy99
status: open
deps: []
links: []
created: 2026-11-02T21:37:24Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Propagate generation linker configuration query failures

## Contract and audit evidence

Only test-gen.sh clang --ldflags substitutions53/63. Evaluate query/status before invoking consuming linker so config error+clang0 cannot certify setup success; preserve actual selected tool/version and valid generator pipeline.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `gen-query-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Config outputs valid flags but returnsnonzero; no-output failure; validflags0/linksuccess; validquery/linkfailure; valid generator/source failure controls.

## Excluded

- Not source cause discrimination com-k4c9, actual dependency resolution, external tool protocol redesign, arbitrary all shell substitutions. Standard preflight narrows but does not eliminate later IO/query failure.

## Admission boundary and prerequisites

- type: standard generation runner setup
- owners: ["com-9l3b", "met-8b8w only affected gen evidence", "com-604k integration"]
- consumer: Actual test-gen.sh harness/app link setup, not optional diagnostic.



This is an admission proposal, not an installed dependency. Record actual dependencies after cycle and responsibility review.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.


