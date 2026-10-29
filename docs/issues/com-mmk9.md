---
id: com-mmk9
status: in_progress
deps: [com-am6u]
links: [com-kss7, com-ktyj, com-50me, com-qt11, com-u6h0, com-pmwi]
created: 2026-10-27T02:15:37Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Audit unnecessary inputs and capabilities across compiler APIs

## Question and Actions

Using com-am6u, inspect what each assigned API/constructor needs for its
responsibility versus what its callers pass or its retained context exposes.
Check individual values and indirect access through fields/captures/globals or
large context objects; replacing a broad context with a wrapper is not enough
if the same unrelated capabilities remain accessible.

Assess frontend, Mid/async/ownership, backend and input/driver/session boundaries.
Do not infer that a broad parameter is wrong merely because it is broad: source
positions, declaration navigation and domain-specific environments can be valid
inputs. Ground each finding in the API's contract, caller and actual access.
Suggest the narrow required input or interface and name the affected consumers.

Classify justified inputs, confirmed responsibility mismatches, unresolved
questions and optional simplifications. The target is API input/capability
separation, not a complete implementation-correctness or performance audit.
Reuse matching evidence where available without inheriting aggregate claims.

## Completion

Every assigned inventory row has evidence and a disposition. Missing cases are
explicit; confirmed corrections and unresolved questions have finite follow-up
owners. Obtain independent review of coverage and grounds. Repairs are separately
owned work, and this epic closes on its audits/operational rules rather than on
those repairs or any implementation project's final gates. No compiler source or
expectation changes are performed within this audit.

## Audit Basis and Scenarios

The dependency com-am6u is closed as factual discovery. Its
[acceptance](../../../evidence/compiler-api-audit/inventory-acceptance.json)
pins all 1,504 source/API families and their individual evidence/review limits.
Use each family responsibility, actual typed calls and supplied/default values,
full reachable authority and legitimate inputs together. A broad owner receiver
is not wrong merely because it owns several fields; direct reads alone also
cannot hide capabilities reached through delegates, globals or retained handles.

For every family, retain justified inputs and explicitly identify the affected
API subset for mixed findings. Classify justified inputs, confirmed unnecessary
authority, unresolved questions or optional simplifications. A confirmed excess
requires concrete unrelated authority and a narrower input that preserves the
responsibility, error provenance, lifetime and required effects. Test algorithm
correctness, speculative performance claims and repairs remain excluded.

Scenarios: explicit scalars/byte ranges; owned domain state; orchestration owners;
whole Comp versus actual domain services; indirect state/capture/global access;
constructor/default/native ownership; observer/diagnostic IO and latches; cached
reader/session identity; source-versus-instantiation-versus-execution handoffs;
no-production/recursive/fixture-only callers; failure-prefix and restore ownership.
Each adopted row needs independent review and exact input-fact references. Missing
or unread rows stay pending; local disposition counts cannot close the whole audit.

[Capability reconciliation](../../../evidence/compiler-api-audit/capability-reconciliation.json)
owns exact adopted decision/review hashes and finite follow-up assignment.
Currently 52 families are independently accepted: 36 justified inputs,
13 confirmed excess-authority cases, 1 unresolved questions and
2 optional simplifications. Required findings have 6 finite follow-up owners;
repairs are not completion prerequisites of this audit.
Remaining 1,452 inventory families have not received capability verdicts.
No compiler/source/test/binary repair or product execution has been performed.
