---
id: met-3f14
status: closed
deps: []
links: [met-lrep]
created: 2026-11-23T23:14:37Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Bound successful normal-suite scratch artifact retention

## Contract and Scope

Normal run/panic/reject/part/partreject workers use unique run/case scratch and
adjacent durable JSON receipts. Retire successful products only after their last
consumer and result publication. Preserve discoverable FAIL/pending evidence,
progress supervision, input fingerprints, status classification and accounting.
Temp/result publication failures fail closed; worker exit0 alone is not success.
Source/std, carriers/seeds and formal fixed-point products are excluded. Manual
probes, build/self-host archives and historical cold stores are separate owners.
This repair does not close phase3 semantic work or eliminate all disk pressure.

## Design and Scenarios

Shared fixed t_* outputs caused persistent accumulation and concurrent collisions.
The common worker owns LLVM assertions, link, supervised execution and final
output/diagnostic assertions. It publishes a fsynced result before retirement,
then updates the retirement receipt. The existing dispatcher owns scheduling,
reconciliation and child recovery; the suite owns its separate shared runtime.
No second scheduler or generic zero-status cleanup trap is introduced.

RED reproduced PASS with generated LLVM left in shared TMPDIR and no receipt.
Controls cover all five phases, program nonzero/signal, cancellation with actual
child recovery and pending retention, concurrent identical cases/two dispatch
runs, temp creation failure, write/fsync/rename failures, publication-before-
retirement and symlink protection. Ten lifetime tests, 160 dispatcher scenarios
and22 golden controls pass; original status controls remain registered.

## Completion Evidence

Resolved by d7dacd6b. Meta [saved verification](../../../evidence/normal-artifact-lifetime/README.md)
contains commands, hashes, scenario reports, consumer map and scope limitations.
Four real old/new-worker cases retain identical terminal results and three LLVM
hashes while reducing retained allocated bytes86,200,320→16,384. This is storage,
not a compiler speed or peak-disk benchmark.

Immutable whole20261124T154015-test-f2b289 completed3313 common cases:3031 PASS
payloads retired,282 FAIL retained, pending0/skip0, no infrastructure worker
failure. All five labels differing from the historical whole replay identically
with old/current workers using the same current carrier and source. Whole exit1
reflects semantic failures and is not green/main integration. Cumulative retired
successful products18,908,516,352 bytes; failed products752,435,200 bytes remain
under the run roots indexed in the saved report. Wall elapsed includes host sleep
and supplies no throughput comparison.

Independent normal_artifact_lifetime_review checked d7dacd6b source, final
consumers, controls and all3313 actual receipts: no mandatory implementation gap,
no duplicate directory, no receipt/payload mismatch, finite closure accepted.
Documentation-only stale preimplementation/pending statements were removed.

## Retention and Cleanup

Necessary evidence was saved and pushed before retiring task-owned successful
comparison snapshots/payloads. The current282 unresolved failures remain under
compiler/tmp/normal-cases; their owning phase3 fixes retire them after cause
resolution and evidence preservation. Small receipts remain discoverable. Product
inputs, current carrier, formal evidence and recovery cold stores are untouched.
A pass/retired:false receipt after interruption is not a payload-existence promise.
