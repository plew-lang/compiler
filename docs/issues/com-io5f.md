---
id: com-io5f
status: in_progress
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

Independent review is running. No production/spec/test changes are authorized as part of this review. Scratch reports and focused outputs belong under `compiler/tmp/phase2-re-review/{buffer,root-use,orc}/`; final reports and assessment will be retained as review evidence. Phase three has not started.

