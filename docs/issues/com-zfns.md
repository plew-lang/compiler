---
id: com-zfns
status: open
deps: []
links: []
created: 2026-11-02T21:37:23Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Preserve setup and stopped outcomes in the self compilation observer

## Contract and audit evidence

Only measure-self-compile.sh input manifest/metadata/read/write failure stopping, retained idle-stop outcome and child signed-status versus process-observable/report agreement. Setup failure must not proceed to accepted timing by carrier0. Preserve stdout/stderr, sampler cleanup and nonzero stopped outcome.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `observer-results`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Manifest write/lock-selected read failure with deterministic carrier0; setup success; ordinary carrier7; actual child signal vs integer similarcode; idle TERM-to0 retains stopped outcome; sampler drain/reap.

## Excluded

- No formal timing result/CLI protocol/panic choice; com-nqiq test oracle and com-jy25 progress implementation remain separate. No arbitrary process-tree cleanup theorem.

## Admission boundary and prerequisites

- type: actual observer and conditional downstream evidence admission
- owners: ["com-9l3b when registered fingerprint/sampling controls rely on observer", "com-p5um when adopting observer evidence"]
- consumer: Raw diagnostic observer is not ./validate self-host. Its normal test-measure-self-compile-input-fingerprint.sh and sampling.py integrations must preserve failure; official fixedpoint/timing gate remains separate.

- Only if changing measured input identity schema: coordinate exact test oracle com-nqiq; no blanket prior completion needed.

This is an admission proposal, not an installed dependency. Record actual dependencies after cycle and responsibility review.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.


