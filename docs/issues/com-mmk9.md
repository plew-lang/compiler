---
id: com-mmk9
status: open
deps: [com-am6u]
links: []
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
