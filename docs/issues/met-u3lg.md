---
id: met-u3lg
status: open
deps: []
links: []
created: 2026-10-28T03:26:29Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification, tooling]
---
# Reject unavailable inputs in scoped negative architecture guards


## Contract and Confirmed Counterexample

The exact checker `tests/compiler/architecture/test-loader-no-value-parser-fallback.sh` must report unavailable inputs or failed search as failure, while retaining its three forbidden Loader spellings. Source baseline9665094d; checker SHA256daaad6757bae52f2af0be3e90bdea86c37def5d13288bb418d53e61f953ffaae.

Each negative `rg -q` runs inside an `if`, so `set -e` does not distinguish nonmatch1 from search error2. A missing Loader makes all conditions false and the checker emits PASS/exit0. An isolated byte-identical script copy with real sh/rg confirms three controls: clean existing source exit0, forbidden parseProgramAst source exit1, missing source exit0 with IO errors and PASS. No Plew compiler or generated application was executed and production inputs were unchanged. Evidence: meta/evidence/test-audit/scoped-reviews/loader-missing-input-probe.json; independent static findingR82-loader-input-failure in review-frontend-batch-0082.json.

## Guarantee, Scope and Scenarios

Own the Loader guard input/search-result boundary and the exact trace-guard extension below, not parser implementation or all architecture tests. Preserve the current forbidden value-AST entry/traversal patterns and valid-source success. Missing/unreadable source and unavailable/failing search must never become a successful absence claim. The latter cases are required repair controls, not all measured by the audit probe. Keep nonmatch1 distinct from errors without merely silencing stderr.

Use the existing fixed script for RED, including a valid source, each forbidden form and unavailable input; exercise the actual production checker in an isolated repository rather than duplicating its predicate in a separate passing test. After repair, require the corresponding GREEN and verify the standard registration still calls this guard. Do not change compiler acceptance, forbidden patterns, fixtures, goldens, other gates or supervision policy.

## Completion and Limits

Independent review must reconcile actual exits/markers, negative search errors, the preserved clean/forbidden controls and final dispatcher use. Retain exact revision/command/input evidence. This is a finite runner repair outside test audit closure; it is not an audit prerequisite or evidence that the parser itself is wrong.

## Negative-Only Trace Guard Input Extension

Batch0132 extends the finite input/search-error boundary to tests/tooling/test-trace-phase-progress.sh, exactly its two negative grep predicates over src/Codegen/Mono/Call.pw. Missing/unreadable input or failed search can become absence and reach PASS while other positive source checks succeed (static source counterexample; no copied execution here). Preserve valid input and both forbidden-pattern rejections, distinguish nonmatch from search error, and retain the existing Loader controls. These two named checkers only; not every architecture grep or compiler trace implementation.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 79.

Row79: Exactly Loader three forbidden spellings and MonoCall two negative patterns. Keep clean/forbidden controls, nonmatch vs error. Loader copied probe measured; trace is static only. No compiler/parser/trace semantic repair or every-grep scope. Normal test.sh registers both named architecture/trace guards. Unavailable negative-only input or failed search can look like absence/PASS; repair before normal gate and shared-parser Loader evidence are relied on. Required admission: com-9l3b, com-2p9p.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
