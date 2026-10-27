---
id: com-l92e
status: open
deps: []
links: []
created: 2026-10-27T19:19:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, runtime, verification]
---
# Attribute ambient destructor panic regressions to their final access paths

## Contract, Evidence and Scope

The fully read panic fixtures ambient_combined, ambient_drop and ambient_writeback_drop intend closure/existential/deinit/writeback access detection. Normal/D assert a common overlap message and status only. Those predicates cannot distinguish actual selected destructor/setter ambient access from an earlier conservative rejection. This is a bounded path/detection gap from inspected assertions, not proof the current compiler takes a wrong path, and not unread audit work transferred away.

For exactly those three inputs, verify original intent, derive minimal equivalent no-access/untaken-path positives and phase-attributing observable controls for deinit and IndexSet writeback through final access. Show preemptive/omitted/wrong-path checks are discriminated using actual checker/compiler request where necessary; retain useful existing positive coverage if proven. Preserve current runtime intent; source deinit placement migration remains met-2t3l and pointer syntax migration met-op15, not anonymous fixture rewriting. Do not add compiler-specific semantic exceptions or require every unrelated program mode. No implementation performed by audit; later changes use TDD and independent review.

Scoped evidence: meta/evidence/test-audit/scoped-reviews/runtime-batch-0084.json and batch-0084-disposition.json (test/source baseline 9665094d). This is a separate finite follow-up, not a child/prerequisite of the audit epic or a claim repairs passed.


