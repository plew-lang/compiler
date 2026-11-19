---
id: met-kuej
status: closed
deps: [met-8ibr, met-jv7m]
links: []
created: 2026-11-19T15:28:59Z
type: task
priority: 1
assignee: Koji Murata
parent: com-p5um
tags: [backend, tooling, performance]
---
# Integrate compiler ThinLTO build paths and validate the transition


## Contract and scope
Connect formal text-LLVM compiler linking and development native-LTO-object compilation to the same compiler link profile. Depends on shared linking and native artifact support. Keep ordinary application/native machine-object consumers unchanged and the runtime implementation single.

## Actions and guarantees
Bootstrap new output capability from an existing carrier via supported text path, smoke the new candidate, then switch dev rebuild to the explicit new request. No capability-probe fallback that silently changes pipelines. Record actual clang/libLTO/linker/flags in formal measurement. Preserve watchdogs, input freezing and fixed-point raw LLVM/runtime comparisons.

## Scenarios and completion
Both production paths must demonstrate actual ThinLTO program/runtime participation, runtime export parity (139 including the new native producer API), callbacks/ORC execution, ordinary object noninterference, errors/output cleanup, toolchain mismatch and old-to-new transition. Use fresh compiler smoke and applicable tests, independent final review and synchronized docs. Then provide the frozen candidate to parent com-p5um for its formal fixed-point and below-seven-second certification; this child does not own a second conflicting final gate.

## Exclusions
No main/seed/adopted-carrier promotion, static LLVM optimization or unrelated phase-three language fixes.

## Basis
[Reviewed isolated comparison and three-unit plan](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-runtime-thinlto-investigation.json). User approved creation and execution of these three units. Task decomposition reviewed by abi_optimization_plan_review; plan does not certify implementation.

## Verified outcome
Revision0d677b0a. Shared compiler ThinLTO profile connects dev summary-bearing objects and formal/bootstrap text callers. Explicit old-carrier refusal has no fallback; ADD through supported text is exercised by the formal old-carrier generation1 successor.
[Integration evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-thinlto-integration.json) retains the new actual-tool freeze controls, successful fixed-input dev build, direct-object7 and lazy CLI47 controls and export139/139 parity.
[Formal WIP measurement](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-thinlto-formal-self-host.json): standard20261119T164158-self-host-8d831e exits0 with unchanged inputs; generation2rawLLVM/runtime/successor binary match. Measured candidatefc2fba44aeb3a8d5f39af9856cc967bc0031cebdc6d07f76f4c326740953ba5a has samples7.303893/6.810615/6.929691, median6.929691s. The exact formal candidate separately passes direct-object7, lazy CLI47 and real-runtime Thin/machine producer execution.
Independent thinlto_integration_review inspected contracts/source, found actual link tools missing from freeze, re-reviewed its repair, then verified all evidence and accepts finite closure.
Bootstrap caller is source-reviewed; shared text execution is proved by formal run, not a new full bootstrap claim. Parent G1/G2b, phase3 functional completion, full sanitizer and main/seed/carrier/distribution promotion remain outside this closure. Parentcom-p5um retains final frozen-G1 admission ownership.
