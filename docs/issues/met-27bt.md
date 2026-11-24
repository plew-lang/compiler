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

