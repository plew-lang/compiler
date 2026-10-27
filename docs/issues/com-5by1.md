---
id: com-5by1
status: closed
deps: []
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Integrate TDD scope and independent review rules into development entry points

## Contract and Actions

Maintain common TDD, scoped-task and independent-review rules under the existing
[verification design](../design/verification.md).

- AGENTS/index: require reading the TDD rules at every task start.
- Meta workflow: derive scenarios from the full guarantee and preserved behavior;
  automate one at a time, confirm intended RED, reach GREEN and refactor; reconcile
  coverage, expectations, detection and structural conditions before closure.
- Issue README: action titles, scoped guarantees, producer/consumer/removal paths,
  scenarios, evidence, dependencies and closure conditions.
- Test README: expectation grounds, distinguishing assertions, actual paths/modes
  and registration/audit criteria.
- Review procedure: independent contract-first assessment, evidence-based finding
  dispositions and re-review of affected conclusions.

Preserve GREEN controls and pure-refactor/documentation/investigation exceptions.
Keep one owner per rule and use links elsewhere. No compiler source, expectation,
tool behavior, gate threshold or dependency change; no additional user paperwork.
The user's follow-up requests shorter wording without changing these contracts.

## Documentation Checks and Exit

- Mandatory entry is discoverable; rereading advice does not contradict it.
- Scenario coverage comes before incremental tests; intended RED cannot be replaced
  by setup errors or wrong-reason failures. Exceptions require no artificial RED.
- Guarantees map to effective assertions and real paths; structural/API removal
  needs structural evidence. Counts, code coverage and all-green are insufficient.
- Validation grain preserves final gates without running all of them each cycle.
- Review separates violations, hypotheses, optional improvements and semantics;
  dispositions require grounds, not unbounded objections or unanimous approval.
- Validate links/headings and contract preservation; obtain a fresh-context
  walkthrough and independent completion review before closing.

This is documentation work: no compiler RED/rebuild is required. A documentation check does not establish future compliance, detection
effectiveness or implementation cost.

## Outcome and Evidence

Resolved at compiler `90efda0f` / meta `a7fef840`. Local links and 17 workflow
heading references passed; both repository diffs passed whitespace checks.
Independent reviewer `/root/review_tdd_rules` rechecked the affected contracts
against compiler `4054b83f` / meta `db8eb591`: required entry, scenario coverage,
RED/GREEN, exceptions, records/gates and reasoned review remain intact. It found
no required correction and permits closure; the author accepts this grounded
conclusion. The initial fresh-context review remains in Git at `4054b83f`.

Compiler execution and operating effectiveness were not tested. No source,
expectation or gate change is claimed; no implementation trial is required
to close this documentation work.
