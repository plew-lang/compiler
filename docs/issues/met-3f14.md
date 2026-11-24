---
id: met-3f14
status: in_progress
deps: []
links: [met-lrep]
created: 2026-11-23T23:14:37Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Bound successful normal-suite scratch artifact retention

Repeated completed/interrupted normal runs exhaust the developer filesystem because per-case generated LLVM remains in shared TMPDIR. Incident20261123T224611-test-41ce46 aborted with ENOSPC after about10GiB available at start; not a compiler regression or completed suite. Recovery receipt is meta evidence/rejection-domains/diagnostic-domain-implementation/phase3-existential-normal-enospc.json. Investigate scratch producer/consumer lifetimes and retain failure diagnostics and all required comparisons; define run-owned artifacts and retire successful transient output only after its final consumer and durable result. Preserve actual progress supervision, input fingerprints, exit status and all tests. Do not delete src/std/carriers/seeds/fixed-point material or weaken tests. This tooling follow-up is separate from semantic phase3; met-lrep integration/retry is separately closed; this artifact-lifetime repair remains open.

## Acceptance Criteria

Identify every consumer of normal per-case LLVM/runtime/binary and its last use; add bounded-lifetime cleanup with tests for successful/failing/interrupted runs, retained failure evidence and concurrent/isolation safety. Validate meaningful disk reduction and normal result equivalence. Independent review required.


## Bounded Feasibility Check (2026-11-25)

Static tracing found a small, shared repair surface:

- [case-phase.sh](../../tests/harness/case-phase.sh) owns normal run/panic/part LLVM, link trace, binary and output consumers within each worker. It currently writes fixed `t_*` names directly to shared TMPDIR with no retirement. Reject/partreject diagnostics use the same shared naming and need isolation too.
- [test.sh](../../tests/harness/test.sh) already owns and retires its shared runtime in a unique directory. Preserve that once-per-invocation preparation and its fault controls.
- [normal-case-dispatch.py](../../scripts/support/normal-case-dispatch.py) already owns result reconciliation, parallel dispatch and cancellation/process-group recovery. Reuse its existing authority; no new scheduling system is indicated.

Recommended finite repair: introduce run/case-owned scratch, retain an identifiable small result/artifact index, and retire successful case products after their final consumers and durable result publication. Keep FAIL/unfinished evidence discoverable by run/case. Temp creation must fail closed rather than fall back to shared names. A worker emits FAIL with exit0, so a zero-status EXIT trap is not proof of success. Preserve exact PASS/FAIL accounting, crash/timeout distinctions, progress and child recovery.

Existing [dispatcher fault controls](../../tests/tooling/test-normal-dispatch.py) and [worker/runtime status controls](../../tests/tooling/test-runner-exit-status.py) supply focused test seams. Add successful retirement, failure/interruption retention, two-run isolation, directory-creation failure and publication-before-retirement controls; demonstrate reduced peak/retained bytes on representative real cases with unchanged results. Old source/std/carrier/seed/formal inputs are never cleanup targets.

Normal common workers are the bounded scope. Independently owned manual probes, build/self-host archives and historical cold stores are not automatically covered; do not claim this repair eliminates every repository disk-pressure source. No production changes, runtime experiment or measured savings were performed for this light investigation. Static independent review found the localized approach feasible, with the above retention/order/isolation conditions required before closure.

## Implementation Scenarios

The task is in progress with the run/case lifetime boundary selected above. RED: the unchanged production worker emits PASS but leaves shared generated LLVM and has no durable case result. The new integration control reproduces that exact deficiency. Required contrasts: all five phase PASS/FAIL accounting, program nonzero/signal, cancellation with live child recovery and pending retention, simultaneous identical workers and two dispatch runs, temp creation and publication write/fsync/rename failures, publication-before-retirement and symlink protection. Existing dispatcher/status/golden fault controls remain registered and keep their original expectations. Representative real old/new workers must agree on results and LLVM while demonstrating peak/retained-byte reduction; a current whole-suite comparison remains required before closure.
