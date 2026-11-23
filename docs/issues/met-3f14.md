---
id: met-3f14
status: open
deps: []
links: [met-lrep]
created: 2026-11-23T23:14:37Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Bound successful normal-suite scratch artifact retention

Repeated completed/interrupted normal runs exhaust the developer filesystem because per-case generated LLVM remains in shared TMPDIR. Latest20261123T224611-test-41ce46 aborted with ENOSPC after about10GiB available at start; not a compiler regression or completed suite. Recovery receipt is meta evidence/rejection-domains/diagnostic-domain-implementation/phase3-existential-normal-enospc.json. Investigate scratch producer/consumer lifetimes and retain failure diagnostics and all required comparisons; define run-owned artifacts and retire successful transient output only after its final consumer and durable result. Preserve actual progress supervision, input fingerprints, exit status and all tests. Do not delete src/std/carriers/seeds/fixed-point material or weaken tests. This tooling follow-up is separate from semantic phase3; met-lrep recovery and full retry remain mandatory there.

## Acceptance Criteria

Identify every consumer of normal per-case LLVM/runtime/binary and its last use; add bounded-lifetime cleanup with tests for successful/failing/interrupted runs, retained failure evidence and concurrent/isolation safety. Validate meaningful disk reduction and normal result equivalence. Independent review required.

