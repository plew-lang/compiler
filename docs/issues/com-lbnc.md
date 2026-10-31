---
id: com-lbnc
status: open
deps: [com-2hx2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Audit phase three test oracles paths and missing contract controls

## Scope and Actions

Derive finite assertion batches from com-2hx2 and the current harness for existing
phase-three contracts, including any relevant global/default/provided/gen/Mid or
mode assertions regardless of directory. Read the eleven criteria in met-si6j,
verification design and the spec chapters for each tested rule. Build the needed
local discovery map here; no whole-corpus audit is an input dependency.

1. Derive required positive/reject/ownership/flow/mode contrasts from contracts
   before using existing test names or implementation explanations as an oracle.
2. Check each assigned test's original purpose, expected result, distinguishing
   assertions, actual exercised decision path and registration. Confirm that
   rejection is for the intended reason and successful output distinguishes the
   relevant callee/state. Differentiate literal construction from callable use.
3. Prioritize the demonstrated false-coverage boundaries: same-module versus
   unrelated module shadowing, direct global call versus local copy, closure
   formation versus invocation labels/count/passing, and gen owner/visibility.
4. At important boundaries use known-bad candidates, justified transformations
   or isolated selective fault controls to check detection. Do not equate old/new
   agreement with correctness or assume arbitrary wrapping is meaning-preserving.
5. Classify valid, wrong expectation, weak assertion/path, unregistered, missing
   controls, unresolved specification and separately unsupported functionality.
   Never change a golden merely to fit the current compiler.

## Exit and Evidence

All assigned assertions have a contract/path disposition. Missing required
contracts are identified independently from the test list. Confirmed failures
and necessary test/runner corrections have finite proposed actions and linked
receiving owners before closure. com-x7r3 receives unassigned repair placement
from the combined audits and installs actual repair/G1 dependencies afterward;
Its completion is not a prerequisite for closing this input audit. Respect
existing test-error stopping rules.
Independent review checks oracle grounds and missing boundary combinations.
This task audits and proposes controls; repairing compiler/expectations belongs
to the routed tasks, with RED before each actual repair. It does not certify a
new candidate, add every unimplemented feature or repeat all final gates.

## Reusable Scoped Intake Controls

The adopted com-k35g outcome under meta/evidence/existing-feature-conformance/audit-intake/api-session-and-inputs.json retains com-geem matching/inference/grounding and com-r2sw scalar-key/proof-tag controls. Use them when deriving this task's semantic oracle/path contrasts; an API narrowing conclusion alone is not exercised source-semantic coverage. Existing test-audit qualified roles remain distinct from this decision-boundary audit.
