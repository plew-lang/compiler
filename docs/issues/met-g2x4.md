---
id: met-g2x4
status: closed
deps: []
links: []
created: 2026-11-23T13:45:54Z
type: task
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics]
---
# Preserve owned source typing-obligation refusals

## Contract and boundary

Carry an authored expression's unresolved array-element obligation from source
recording through publication, retained owner failure and the private owned
consumer to check/AOT/ORC. Follow [body checking](../design/body-checking.md)
and [diagnostics](../design/diagnostics.md). Message text is not authority.
Parent com-yeua and phase three remain open.

Only Lower-authored empty arrays lacking an element context create this
obligation. Both Lower entrances retain serial/span/range provenance. Raw,
foreign owner/session/operation, synthetic replacements, missing/corrupt facts,
unfinished declaration resolution and dependency failures remain fail-closed.
A normal completion with the same owner is required; a missing expression fact
never gains Source authority, including an intentionally deferred one.
Determined term storage discharges the obligation at the common writer.

The producer validates lexical ancestry while its builder exists and retains
that root with the negative event. Failed closure builders are discarded;
observation must not rediscover their parents. The one read-only observer
checks the saved event, persistent expression ownership and syntax provenance.
No successful fact, inference expansion or catch-and-relabel path is added.

## Guarantees and executed scenarios

- Raw recording/Raw publication, session/root/owner changes before and after
  failure, Lower serial before/after recording, span, unknown event, missing
  fact/completion and obligation discharge followed by fault injection:
  SourceTypingMain private12-scenario native exits0, empty stdout/stderr.
- Direct/wrapped/nested/discarded arrays and a closure: Raw cached retry/drain,
  owned prepareFunction retry then whole check, fresh whole/eager; global
  initialization separately. SourceTypingFailureDomains native matches its
  exact21-line golden, exit0 and empty stderr.
- LLVM22 ASan/LSan private/consumer: all stages0, input hashes unchanged,
  exact expected outputs and empty stderr;20764/28586 memory checks and
  5303/6620 checked function bodies.
- Actual final CLI18 controls preserve11 intended source refusals,4 unused-lazy
  successes and3 valid typed-array/generic/closure language controls. Registered
  in the normal harness; failures join its ordinary failure aggregation.

Scenario7 is an internal storage fault injection using a determined scalar
term before corrupting the fact, not a claim of accepting an Array as I64.
Valid Array completion is covered by the separate language controls.

## Outcome and evidence

Resolved at source5f12e9a1 (later29c6167a only harness/docs;728d3a83 only parent
metadata). [Complete finite evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-source-typing-obligation-refusal.json)
retains RED, native/lifetime, final artifact and normal receipts.

Final standard build001731 and gen-f14f22 pass with unchanged inputs. Formal
1c067a reaches G2 with LLVM/runtime/successor equality; standard3 samples
7.717293/7.247575/7.149129, median7.247575<=7.5. All5 artifact records were
hashed from real files; measured compiler1b22eb22 passes18CLI smoke controls.

Whole20261123T145308-test-b59031 finishes exit1, input hashes unchanged,
7642 matched worker pairs, no supervisor failure. Against prior295 failures,
only the5 targeted empty-array refusals resolve:290 remain,0new,0reason changes.
The10 resolved source/golden files have unchanged hashes; registered CLI gate
passes. [Whole reconciliation](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-post-typing-normal-suite.json).

Independent reviewer typing_obligation_plan_review accepts finite closure:
source/assertions,191 source hashes, native/lifetime receipts, formal real
artifact hashes, CLI/gen/build and final normal files/events were independently
cross-checked. No independent rerun is claimed; no mandatory finding or gate
remains. Remaining generic compatibility Unresolved, named-function admission,
other refusal domains, met-bejv fixtures and com-p8xt API narrowing are excluded
and do not become complete through this closure.
