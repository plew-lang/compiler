---
id: met-sxk9
status: closed
deps: []
links: []
created: 2026-11-10T12:46:01Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, performance]
---
# Restore readonly isActive and measure self compilation


## Guarantee and Scope

Restore only SourceFactDirectory.isActive from inout fn to fn. Preserve its
owner comparison and None behavior. No other readonly/inout migration, source
language change, main/seed/carrier promotion or original performance recovery
claim. Historical origin24192d1f; current source baselineed9e607f.

## Verification

Pure refactor: use existing source_owner_payload_stability and
mid_source_fact_presence executable controls with exact outputs. Build both
old/new compilers with the same standard dev-build pipeline and fixed input
carrier, then compile identical final source in balanced alternating runs with
excluded warmups, recording all samples, hashes and medians. This is a paired
diagnostic, not formal fixed-point performance certification. Independent
neutral review verifies sole-line scope and actual measurement basis.

## Outcome

Resolved: SourceFacts.pw isActive alone is restored to readonly fn. Existing
owner comparison/None logic and13 call sites are unchanged. Both candidates
were built with the same standard dev pipeline and fixed carrier. Six balanced
same-final-source pairs measure7.949246/7.936873 seconds, about12.4ms lower
(0.156%); no statistically established speedup or clear regression is claimed.
All14 output LLVM hashes match across old/new. Existing SourceFact AOT controls2
pass exact stdout/empty runtime stderr. Independent source and final evidence
reviews accepted the finite guarantee.

[Saved samples, gates, inputs and reviews](../../../evidence/performance-regression-history/readonly-isactive/README.md).
Initial CLI trace-argument setup errors and unobservable --run timeout are not
passing coverage; final AOT controls replace only that targeted preservation
check. No JIT success, formal fixed-point/performance re-certification, whole
suite, seed/adopted-carrier promotion or com-1hd3 recovery is claimed.
