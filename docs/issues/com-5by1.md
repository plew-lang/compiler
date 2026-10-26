---
id: com-5by1
status: in_progress
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

Integrate the [approved plan](https://github.com/plew-lang/meta/blob/7893c820/agents/llm-development-workflow-proposal.md)
under the existing [verification design](../design/verification.md).

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

This is documentation work: no compiler RED/rebuild is required. Actual process
compliance, detection effectiveness and cost remain with [com-bv1s](com-bv1s.md).

## Evidence and Current Boundary

The initial wording at compiler `2f1f9b44` / meta `fc6e0ee0` passed local links,
workflow heading references and independent reviewer `/root/review_tdd_rules`
(no inherited conversation). It followed the normal entry paths, checked 148
file/heading references and reported no required correction. Detailed evidence
is retained in Git at compiler `4054b83f`; this is not review of the shorter text.

Reopened for the user-requested wording refinement. Close after verifying the
shorter documents preserve the contracts above and independently reviewing the
affected conclusions. No runtime or formal performance result is claimed.
