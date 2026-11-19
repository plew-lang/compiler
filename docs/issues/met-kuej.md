---
id: met-kuej
status: in_progress
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
Both production paths must demonstrate actual ThinLTO program/runtime participation, runtime export parity (current reference138), callbacks/ORC execution, ordinary object noninterference, errors/output cleanup, toolchain mismatch and old-to-new transition. Use fresh compiler smoke and applicable tests, independent final review and synchronized docs. Then provide the frozen candidate to parent com-p5um for its formal fixed-point and below-seven-second certification; this child does not own a second conflicting final gate.

## Exclusions
No main/seed/adopted-carrier promotion, static LLVM optimization or unrelated phase-three language fixes.

## Basis
[Reviewed isolated comparison and three-unit plan](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-runtime-thinlto-investigation.json). User approved creation and execution of these three units. Task decomposition reviewed by abi_optimization_plan_review; plan does not certify implementation.
