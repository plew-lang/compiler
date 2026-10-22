---
id: com-io5f
status: closed
deps: []
links: []
created: 2026-10-22T02:30:19Z
type: task
priority: 2
assignee: Koji Murata
parent: com-604k
tags: [design, verification]
---
# Re-review phase-two completion after the ORC lifetime repair

## Scope and Pinned Input

User-requested fresh independent review of phase two after the production ORC lifetime repair. Review input: compiler `959345b8774094d3ebf54b5f2cfccc6121f245ef` (production `87b382d2`), meta `401baeee90ce23de49f41e7e5d1a890fd5332319`, spec `595bb5b847f24534be6e68e279f8bfc4409d8a2e`, Syntax exact `0.1.11-dev.30` / `8c89204230c3d865ea95a03382c3fd213731e1de`. Existing dirty `bin/plewc` and Python caches are preserved and are not review inputs or patches. The checked development carrier is `bin/plewc-orc-lifetime`, SHA256 `c36716d9f95e123f2b62158e44e2287476757eaf52b6bd93e41bc1a2a47d18b3`.

Three independent reviewers own Buffer arithmetic/allocation/ownership, root-owned use and provider/consumer migration, and ORC layout admission plus full native teardown dependencies. The parent reconciles scope, saved input/artifact identities, completeness of evidence, and the final assessment. Closed issue status and the previous completion audit are claims to verify, not proof by themselves.

## Review Completion Conditions

Trace each bounded contract from its producer through final consumers and failure/destruction, check that replaced authorities are gone, and verify positive/negative controls reject or succeed for the intended reason. Pay particular attention to the repaired unexecuted lazy-call lifecycle and whether preserving the symbol pool closes all destruction dependencies. Preserve the distinction between LLVM22 bridge/host instrumentation and instrumentation of libLLVM or generated JIT instructions.

Use existing applicable full-gate and performance evidence with checked scope and identities; execute focused controls where they add independent evidence. Do not run another formal performance measurement or full suite merely to reproduce unchanged records. Do not add future features or final main-integration gates to phase two. Record findings with severity, source locations, reproduction/contract and whether they block phase-two recognition. A review can finish with follow-up repairs still open; that is not implementation completion.

## Current Work

Independent review is complete. [Saved reports and evidence](../../../evidence/existing-feature-conformance/phase-two-rereview/README.md) preserve the three unedited reports, focused results and parent reconciliation. No production/spec/test/harness changes were made. Phase three has not started.


## Findings and Recognition

All three reviewers recognize completion of their assigned phase-two contracts, with no P1/P2/P3 repair request blocking recognition:

- Buffer: traced common checked floor, private/shared ownership, publication and cleanup; current carrier passes focused runtime O0/O2 and JIT cases in normal and LLVM22 runtime sanitizer configurations. Existing typed AOT sanitizer evidence was inspected and its scope preserved.
- Root-owned use: traced root/part admission, one binding environment, final lookup, and actual provider/consumer migration. Five positive/nine negative fixtures plus module isolation, real Hash generation/consumer checks and Syntax derive controls pass in 37 commands. Prior normal/gen input hashes still apply to the unit.
- ORC: confirmed the pool owner closes both Reexports symbol handles and Notifiers captures through full manager destruction without retaining the destroyed engine. Four normal/sanitizer native/lazy configurations pass. Mixed lifecycle probes pass 64 sessions per configuration. Removing only the retain assignment in scratch causes three SIGTRAPs with the same struct layout/test; repaired runs succeed three times. Layout positive/negative controls discriminate the intended boundary.

One non-blocking diagnostic-quality observation remains: missing Hasher is rejected at the generated constraint with indirect wording. The positive/negative pair establishes correct isolation; cause-reporting improvement is recorded in met-k7ks without making it a stage-two repair condition.

Parent reconciliation confirms unchanged production/test/scripts during review, current carrier identity, saved formal generation-2 fixed point and median 6.211262 seconds, and source/std/fixture applicability of the saved full gates. Original full suites and formal timing were not rerun. Bridge/host/runtime instrumentation is not relabeled as libLLVM/JIT/frontend instrumentation.

**Phase-two completion is independently recognized.** This closes the review, not com-604k or the final main/seed integration gates. The previous com-i5vp failing review remains an accurate record of its older input; this new review certifies the repaired input at the bounded phase-two scope.
