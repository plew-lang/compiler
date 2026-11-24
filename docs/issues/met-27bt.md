---
id: met-27bt
status: in_progress
deps: []
links: []
created: 2026-11-24T00:14:20Z
type: task
priority: 1
assignee: Koji Murata
parent: met-lrep
tags: [backend, verification]
---
# Refresh private Ready witness probes with retained interface receipts

Whole normalc608e1 newly fails ready-witness-plan-private: manually fabricated FinalExistentialResolution lacks required retained source interface. ReadyWitnessPlanMain intentionally tests physical descriptor/ABI/Ready corruption and exact LLVM receiver/argument lanes, not source conformance; inspect its setup and saved finalcall construction against new interface count/call signature receipts. Replace obsolete setup with valid real frontend-derived boundary data or narrowly built private receipts, preserving each malformed authority case and cache/no-allocation/address checks. Do not relax product admission or replace rejected cases with ignored errors.

## Acceptance Criteria

All existing mode0..20 and witnessCallControl positive/negative cases execute intended physical boundary. Setup succeeds before each deliberate corruption and failures are asserted at the owning boundary. Preserve exact source prefixes and fingerprinted inputs; independent review; standard registered gate and final normal integration pass/reconciliation.


## Layered setup checkpoint

All mode0..20 keep their exact Ready/LoadValue/KeepAddress negatives after admitting the interface count. CallControl now obtains genuine final call/source-root/instance-root/template evidence from real source, prepares its declared closed record layouts before executable discovery, and preserves all effective descriptor slots. Synthetic Move I64 stays explicitly at saved physical ABI/callWitnessValueFunction, not source-capability fabrication. Inout positive/role-only negative use the exact saved canonical lane term. Fast LLVM22O0 native-v4 passed all assertions; its copied runner label/scope still says endpoint-preflight, so final evidence must identify actual ReadyWitnessPlan prefix/test hashes and use standard runner acceptance. Real source check/AOT/ORC all passed separately. Standard optimized runner is active with original optimizer flags, root cwd, native60s timeout and full source/std/Syntax/native/support input fingerprints. Independent source review found no must-fix or assertion loss; task remains open pending final standard execution and integration.
