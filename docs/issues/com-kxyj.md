---
id: com-kxyj
status: open
deps: []
links: []
created: 2026-10-28T07:07:17Z
type: task
priority: 2
assignee: Koji Murata
tags: [mid, verification, tooling]
---
# Reconcile positive Mid observations in two codegen checks

## Contract and Evidence

At fixed source baseline9665094d, tests/compiler/codegen/test-mid-coverage.py requests --emit-mid-coverage on run/generic_extension_receiver_record_direct_field.pw, then compares --require-mid on the same source. The fixture has reachable ordinary/generic bodies. Current backend emits positive canonical body records on successful prepared-body emission. Yet observe(llvm, '') returns no fallbacks; successful quiet requirement plus identical LLVM passes, so disabling the observation flag entirely can pass this registered diagnostic test. Its actual a50d795e introduction has the same empty-observation path.

This is a finite test detector gap, not a reproduced compiler emission defect. Other registered closure-environment, existential-witness and await checks require positive emission evidence, so globally disabling the flag is not claimed invisible to the whole suite. Independent contract-first batch0125 review and a parent probe of extracted pure production reader functions with synthetic result data confirm it. Valid emission passes, absent emission also passes; malformed zero canonical ID, missing definition, duplicate record and altered LLVM controls fail. No original checker main, real compiler or application was executed. Saved batch0125 evidence records exact source hash and reproduction scope.

## Guarantee and Finite Scope

Make the flagged successful compilation of this known reachable fixture establish actual positive emission evidence corresponding to the generated definition(s) selected for the finite test purpose. Absence of every observation must fail. Keep valid fallback reporting, positive canonical IDs, unique symbol-to-definition association, malformed/duplicate/unknown-record rejection, warning filtering and unchanged LLVM comparison. Quiet successful --require-mid with no fallback legitimately has empty diagnostics; do not globally reject that separate result contract.

Use controlled RED cases through the actual registered checker path for a disabled observation flag, correct positive records, quiet requirement success, legitimate fallback/error agreement, diagnostic corruption and changed LLVM. Reuse existing reader controls where they discriminate the same contract. Keep the expected presence assertion independently grounded in the chosen source/body contract, rather than accepting the reader's empty result as its own oracle. A focused real fixed-candidate check and independent review follow any later repair.

## Exclusions and Completion

Do not require every emitted helper or all possible source bodies to have the same record, revive the retired fallback backend, demand all-mode/all-language coverage, change compiler meaning, or expand com-pshx's fixed66 .ll.expect set. Source-admission migration and unrelated verifier/ownership repairs remain separate.

Close after relevant RED/GREEN and actual producer-to-final-checker evidence, preserving quiet requirement and fallback semantics. This finite follow-up has no audit-closure dependency; recording it is not repair acceptance or phase3/compiler conformance certification.

## Second Finite Predicate: Strong Cell Factory Evidence

tests/compiler/codegen/test-mid-strong-cell.sh counts any two emit-done name=value trace lines, without binding fn identity to Ref and MutableRef factory instances. Actual7f567e5 introduced this predicate; current Io.print reaches the same-spelled String factory and trace Any.pw carries only the unconsumed fn identity. A copied unmodified checker with a compiler double accepts two explicitly unrelated value records; zero/one and forbidden-fallback controls fail. This establishes target-discrimination weakness, not a current fallback defect. Normal canonical-only compilation and the canonical-production architecture gate remain complementary protection.

Recover this check’s original factory-lowering purpose. Require relevant evidence for both selected factory instances, or explicitly narrow/retire the count guard’s claim with exact evidence that the shared gate covers those instances. Keep separate normal-both-target, missing-one-target plus unrelated value, and forbidden fallback controls if retaining that claim. Do not add a general trace framework, all factories/types/modes, or reference API migration to this task.

The two checkers share positive-observation validity as their responsibility but retain two separate completion items: requested coverage observations and strong-cell target evidence. A precise claim/retirement disposition may replace obsolete checks only with the original guarantee and applicable shared coverage accounted for. Independent postinitial review accepted this bounded grouping; audit evidence does not certify either repair.



## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 90.

Row90: Quiet successful require-mid remains valid; warning filtering/fallback/positive IDs/definition mapping/unchanged LLVM preserved. Keep two finite completion items, evidenced retirement/narrowing only preserving guarantee; no all-body/trace framework/current backend defect claim. Normal registrations must require real positive body emission for reachable coverage fixture and selected Ref/MutableRef factory evidence, not any two value names. Actual final physical emission observation and gate claims depend on this detector. Required admission: com-9l3b, com-h61e.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
