---
id: com-mt7l
status: closed
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Require part and generation golden files before comparing output

## Contract and Evidence

Unchanged part worker passes when Main.out is missing and app stdout empty; unchanged generation compare block also passes without App.out. Six controlled observations preserve stderr cat errors.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-2](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Reject missing/unreadable required part/gen goldens regardless of output. Preserve real empty goldens, exactness/newline policy and valid nonempty comparisons. Fail at owning hygiene/consumer boundary, not by changing fixtures or swallowing IO errors.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 2.

Row2: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Required part/gen goldens must be readable before comparing output; empty valid goldens remain valid. Apply at actual normal/gen admission without changing fixtures to mask IO failure. Required admission: com-9l3b, met-8b8w.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 95.

Row95: Preserve original snapshots and accepted correction, one repair count. Not kp0h terminal-result closure/tfxc selector/every output oracle; no duplicate reopening or individual fixture absence claim. met-py42 stays closed duplicate; actual com-mt7l owns part Main.out and gen App.out missing/unreadable required-file read failure with valid present-empty comparisons. Normal/gen adapters must propagate failure. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Repair Scenarios

Exercise the actual normal part caller/worker/collector and positive gen loop
through each production final summary and exit. Use missing and unreadable
required goldens with empty and nonempty program output, plus a controlled
nonzero read after returning matching bytes (the file remains readable).
Retain valid empty, newline-only, nonempty and legacy trailing-newline matches,
and both empty/nonempty mismatch directions. Keep exact run-mode comparisons
in the existing runner-status controls unchanged.

Use isolated controlled compiler/linker programs for deterministic I/O faults;
never edit committed fixture expectations or copy a replacement comparator into
the regression. Preserve read diagnostics. Actual read status, not merely a
preflight exists/readable check, owns admission to comparison. Validate the
shared dispatcher and existing status controls, and applicable actual normal/gen
consumers with frozen candidate/source. Known unrelated WIP source failures must
remain explicit rather than changing goldens or claiming whole-candidate GREEN.

## TDD Evidence

The [fixed RED](../../../evidence/required-goldens/red.json) uses unchanged
production comparisons at fb85fb74 and test commit31ccc459: six false successes
across part/gen, with16 preserved controls. It records exact source hashes,
command and terminal exit1. Final test assertions also distinguish I/O diagnostics
from progress and unrelated compiler/link/runtime failures.

At7c42951d the [22 controls](../../../evidence/required-goldens/green.json),
existing56 runner-status and160 dispatcher controls exit0. The
[five isolated mutation kinds](../../../evidence/required-goldens/mutations.json)
detect ignored read status, rejection of valid empty goldens and hidden read errors.
The [complete gen consumer](../../../evidence/required-goldens/gen-consumer.json)
passes25 positive/5 reject plus gen-input-ast with unchanged inputs. The
[complete normal consumer](../../../evidence/required-goldens/normal-consumer.json)
returns every planned identity once (2,834), with part93/partreject84 passing.
Its exit1 and five known source failures match the earlier same-carrier/source
run; full candidate GREEN and phase-three closure are not claimed.

## Outcome

Resolved at product revision7c42951d. Each owning part/gen consumer checks the
actual read status before comparison, retaining diagnostics, valid empty goldens
and legacy comparison behavior. No source/fixture expectations were changed.
The [independent completion review](../../../evidence/required-goldens/review.json)
derived the contract before inspecting the diff, independently reproduced the six
baseline false successes and final22 passing controls, and reconciled standard
normal/gen evidence. Its findings contain no mandatory defects, unconfirmed
in-scope concerns or unresolved specification; closure is accepted on that evidence.

The [evidence entry](../../../evidence/required-goldens/README.md) owns the saved
results and limits. Known five source failures remain at their open owners and
com-9l3b remains open; this finite repair is not whole-suite GREEN or main/seed
admission.
