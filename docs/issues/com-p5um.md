---
id: com-p5um
status: open
deps: [com-61jt, com-auvx, com-jy25, com-nqiq]
links: []
created: 2026-10-23T10:41:59Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Verify the frozen candidate fixed point and formal self compilation time

## Current Candidate Refresh

Reopened for the source repair e73a8476 in [com-ugee](com-ugee.md). The prior
043e2402/3c532ce1 gate remains valid only for its recorded inputs/binary; it does
not certify the new source or candidate073f0375. G1 current admission and the
actual final measured compiler must determine which checks can apply. The
current ordinary suite on candidate073f0375 is a repair milestone, not evidence
that an as-yet unmeasured successor passed the gate. Do not weaken any final
fixed-point, performance, gen/deps or LLVM22 sanitizer requirement.

## Boundary

Phase 3G / G2a. **Final standard gate.** Parent criteria: 10.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `scripts/diagnostics/measure-self-host.sh`; `docs/issues/met-si6j.md`.

Use meta ./validate self-host with the explicitly recorded validated carrier and frozen G1 inputs. Preserve generation transition LLVM/runtime comparisons and all adopted-generation runs. Record the measured compiler/hash for G2b; no concurrent build/test or diagnostic instrumentation.

## Exit and Evidence

Standard gate exits0 with unchanged inputs, fixed point and formal median below 7 seconds. Investigate any observed regression with matching-source conditions, fix easy extra copies/searches and return repairs to their owning task; stop if the adopted limit cannot be repaired. Do not promote seed/carrier or merge main here.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Outcome

Independent c2_classification_review accepts refreshed standard gate
20261025T061121-self-host-f849e0 at sourcef225570e (production043e2402,
fixture17537a40). Exit0, all5,990 inputs unchanged and matching G1/current
files/tools/dependencies. Generation1 ->2 changes LLVM; generation2 ->3
matches LLVM/runtime exactly. All measured outputs match. Timings6.384374 /
5.954309 /5.924183 seconds give formal median5.954309 seconds, below7
(and below6). No sampling or overlapping validation.

Measured compiler: meta/tmp/validation/20261025T061121-self-host-f849e0/self-host/generation-2/next/plewc,
SHA256 3c532ce1c7d1e2b0be6bc1c24b8c215a92be87625c65f531a0d83dc1719830b1.
The generation3 successor has the same hash. G2b consumes this exact compiler.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-self-host.json
retains all timing/artifact references. Older gates remain in Git/raw history
and are not same-source speed comparisons or new-candidate certification.
Full suites, parent completion and main/seed/adopted carrier remain uncertified.

## Test Admission Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) installs required finite repair/investigation prerequisites at this actual admission: com-nqiq (row11), com-jy25 (row12). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
