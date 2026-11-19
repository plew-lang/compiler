---
id: met-jv7m
status: closed
deps: []
links: []
created: 2026-11-19T15:28:59Z
type: task
priority: 1
assignee: Koji Murata
parent: com-p5um
tags: [backend, tooling, performance]
---
# Emit summary-bearing ThinLTO objects from owned LLVM modules


## Contract and scope
Add an explicit internal ThinLTO artifact request to the existing native LLVM backend. The same owned Module/Context must produce valid ThinLTO pre-link bitcode with its summary; ordinary --emit-object still produces a machine object. Bare LLVMWriteBitcodeToFile or embedded-bitcode machine output is not proof of ThinLTO support.

## Actions and guarantees
Use selected LLVM local pre-link/summary writer APIs. Preserve target/triple/DataLayout/CPU, required verification, progress, errors and single ownership/destruction. Avoid blindly stacking ordinary O2 and ThinLTO pre-link pipelines. Preserve raw sanitizer contracts. Add capability before switching callers (ADD then USE); no old-carrier silent fallback.

## Scenarios and completion
TDD: inspect real summary-bearing output, link it with the shared runtime C, execute and compare an equivalent machine-object control; normal object output remains native; malformed/target/toolchain mismatch/output failure preserve errors and do not publish stale success. Cover Module/Context lifetime and failure paths with appropriate native/sanitizer controls. Independent review required. Internal worker output selection is explicit; no public plew build option required.

## Exclusions
No new backend/runtime, application source semantics, lifetime feature, distribution toolchain dependency or seed promotion.

## Basis
[Reviewed isolated comparison and three-unit plan](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-runtime-thinlto-investigation.json). User approved creation and execution of these three units. Task decomposition reviewed by abi_optimization_plan_review; plan does not certify implementation.

## Completion evidence
Explicit native writer and private CLI added; production callers remain unchanged.
RED: old worker rejects --thinlto, old compiler lacks --emit-thinlto-object.
GREEN: LLVM20/22 real summaries, Thin/machine executable controls, target/layout/IR/sanitizer/output-error controls, same borrowed Module live across success/failure. LLVM22 producer and lifetime harness ran ASan/LSan with detect_leaks=1. Fresh isolated standard build 20261119T161917-build-4e6a52 passed with unchanged inputs; actual Plew print42 and shared runtime C linked/executed identically in both modes with explicit apple-m1.
[Recorded hashes and results](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-thinlto-native-producer.json).
Independent reviewer thinlto_producer_review derived controls, inspected source and LLVM20/22 artifacts, added independent machine execution, and finally confirmed snapshot equality and fresh CLI evidence. No unresolved must-fix. The initial machine/runtime evidence gaps were filled by persistent tests.
Probe is documented as scoped, not an automatically enumerated fixture. Caller transition belongs to met-kuej; no full suite, formal timing or carrier promotion claimed.
