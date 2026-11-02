---
id: com-u0m8
status: open
deps: []
links: []
created: 2026-11-02T21:37:23Z
type: bug
priority: 3
assignee: Koji Murata
tags: [tooling, verification]
---
# Require genuine source rejection in the restart diagnostic

## Contract and audit evidence

Only optional scripts/diagnostics/orc-restart/restart-check.py run(accepted!=0) and source-reject/old-handler check. Separate source refusal observation from tool/compiler crash/watchdog failure; old handler state preservation independently asserted.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `optional-restart-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Controlled valid host/app, intended compiler source rejection, accepted edit, compiler ordinary tool failure, actual signal and watchdog timeout; only intended source domain may count source refusal; old handler remains callable separately.

## Excluded

- No surviving production host/panic recovery policy, full protocol-bound/no arbitrary descendant proof, production run/fsuq admission dependency, or allORC runtime/sanitizer overhaul.

## Admission boundary and prerequisites

- type: optional diagnostic evidence only
- owners: ["optional HotRestart diagnostic consumer; no unconditional G1/G2/integration owner"]
- consumer: Only future source-rejection/persistent host claim using restart-check. Do not make optional HotRestart prototype a production acceptance prerequisite.

- If shared domain transport adopted, consume only actual relevant adapter; no blanket fsuq prerequisite.

Actual accepted connections and conditional exclusions are recorded in [tooling adoption](../../../evidence/compiler-failure-audit/tooling-owner-adoption.json). The optional restart diagnostic has no unconditional standard-gate prerequisite; recorded standard-gate edges are installed. Product repair remains open.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.
