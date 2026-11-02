---
id: com-c3tx
status: open
deps: []
links: []
created: 2026-11-02T21:37:23Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Validate ASan corpus identities and preserve worker query status

## Contract and audit evidence

Exactly asan-compile-corpus.sh B and asan-gate.sh C/D result loops: selected case identity/membership, one terminal result, upstream dispatch status and error-marker query/read failures. Count equality alone cannot certify every selected case; failed error search must not become absence-of-sanitizer PASS.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `asan-results-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Exact allcases pass; missing/duplicate/foreign/substituted/extra/malformed rows; upstream worker/ls/xargs failure with downstream reader0; errorlog missing/unreadable/grep2; true ASan/LSan marker; clean output; real counted status domains retained.

## Excluded

- Normal dispatcher closed com-kp0h not reopened; ASan B source-domain owns fsuq; no instrumentation weakening, skip/count reduction, allprocess tree or everygrep audit; manual ASan profiles remain documented limits.

## Admission boundary and prerequisites

- type: standard ASan evidence admission
- owners: ["com-9l3b", "com-604k integration"]
- consumer: Actual ./validate asan B/C/D aggregate must not claim complete selected corpus from scalar counts. G1 only if exact sanitizer evidence consumed; no phase3 generic admission from counts.



Actual accepted connections and conditional exclusions are recorded in [tooling adoption](../../../evidence/compiler-failure-audit/tooling-owner-adoption.json). The optional restart diagnostic has no unconditional standard-gate prerequisite; recorded standard-gate edges are installed. Product repair remains open.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.
