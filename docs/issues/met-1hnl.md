---
id: met-1hnl
status: closed
deps: []
links: []
created: 2026-11-10T14:45:53Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Measure LLVM optimization code generation and trace overhead


## Investigation Scope

Separate source-to-LLVM, shared IR optimization, second O2 IR optimization,
native codegen and existing linking from diagnostic trace generation/retention.
Use the same frozen compiler input and LLVM20. Temporary native worker copies
add stage timers, non-mutating observation passes and opt-out controls; do not change production source,
normal pipeline, stop limits or adopted carrier. Compare default optimizations
without verbose trace, no IR optimizations, and no IR optimizations/O0 codegen.
Retain actual status, artifacts/hashes and scope limits; unoptimized output is
not an accepted replacement compiler. One-run exploratory costs are not formal
self-host measurements or proof of semantic correctness of unoptimized binaries.
Independent neutral review verifies attribution and bounded follow-ups.

## Outcome

Investigated; production pipeline and source remain unchanged.
Host apple-m1 normal LLVM worker227.832s comprises shared IR49.563s, O2 IR31.327s
and machine-object emission145.474s. No IR optimization plus machine O0 takes
18.674s, with object generation17.605s. The consistent generic3-case comparison
shows skipping IR alone249.316→235.139s, since machine optimization increases
165.002→234.095s. Each is an exploratory single run, not a formal build/runtime
median. Source-to-LLVM is separately8.300s.

The final diagnostic observes actual function-pass completion with non-mutating
preserves-all passes, not periodic heartbeats. Early silent attempts stalled
under unchanged60-second monitoring and are not successful measurements. Host
normal machine/data/relocation bytes match baseline; whole object differs in
5 private symbol suffixes. Observer overhead/schedule effects are unisolated.
No O0 compiler executable was run or adopted.

[Measurements, exact scopes, recipe and independent review](../../../evidence/build-cost-diagnosis/README.md).
Possible follow-ups are lower machine-code optimization levels and their actual
compiler-runtime tradeoff, or cheaper LLVM progress instrumentation. Neither is
a required fix or adopted change from this bounded investigation.

Closure reason: investigated. The final independent review accepted the bounded
measurement and attribution with the documented instrumentation and O0 limits.
Its zero-fill-section note was applied to the retained comparison evidence.
