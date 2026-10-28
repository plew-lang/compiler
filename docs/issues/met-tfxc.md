---
id: met-tfxc
status: open
deps: []
links: []
created: 2026-10-28T10:21:39Z
type: bug
priority: 2
assignee: Koji Murata
tags: [mid, tooling, verification]
---
# Reject empty explicit Mid diagnostic case selections

## Contract and Source Evidence

Exactly scripts/diagnostics/mid-boundaries/check.py --cases DIRECTORY selects a paired .pw/.out corpus. Its own README defines that request, and verification forbids treating skipped cases as exercised coverage. An empty or nonexistent directory yields sources=[]; with valid compiler/runtime setup, results=[] and all([]) produce exit0. Source baseline9665094d; review-runtime-batch-0133.json records independent static reasoning. No real compiler/checker/program or controlled probe was executed for this finding. Current default seven selected pairs exist and have meaningful output checks.

## Finite Guarantee and Scenarios

Reject an empty or nonexistent explicitly requested corpus before reporting successful diagnostic verification. Compare exactly those selections with one valid paired corpus and a missing required companion. Preserve normal seven-case selection, present-empty golden validity, exact output/status/empty stderr, input hashes, new-output-directory rule, watchdogs and raw LLVM22 ASan route. Existing source/API migration qualifications remain separate.

Use task-start TDD against the actual production selector/result path with controlled setup as appropriate, confirm intended RED rather than compiler/tool setup failure, repair at the selection boundary and require corresponding GREEN and scoped independent review. No all-checker/all-platform matrix, compiler/source/golden changes or weaker instrumentation. com-kp0h retains normal five-phase dispatch completeness; com-mt7l retains the two required expectation-read predicates (met-py42 is a closed duplicate). This task owns neither.

## Completion and Limits

Record exact input/commands, preserve working controls, verify final summary/status propagation and independent findings disposition. This is a separate bounded repair with no audit dependency; audit assignment is not repaired success, whole Mid coverage or compiler certification.
