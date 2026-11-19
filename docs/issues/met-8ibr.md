---
id: met-8ibr
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
# Centralize symbol-preserving compiler ThinLTO linking


## Contract and scope
Own a single explicit compiler ThinLTO link profile in scripts/support/llvm_link.py for raw LLVM and summary-bearing LTO-object inputs. Preserve ordinary machine-object linking; reject claiming that an existing machine object is a ThinLTO input. Keep one runtime C implementation, dynamic development LLVM, selected LLVM20 clang/libLTO/linker and platform export policy. This is compiler development/bootstrap tooling, not a new end-user dependency on LLVM IR tools.

## Actions and guarantees
Add explicit input/profile selection and toolchain provenance; share flags instead of duplicating per-script decisions. Preserve source/runtime inputs and errors. Do not switch development callers until the producer and integration task are ready. Existing compiler-backend archive may remain machine code. Never silently downgrade to runtime-only LTO.

## Scenarios and completion
TDD: command plans for text and LTO-object both include runtime, ThinLTO and export policy; ordinary machine object remains unchanged; incompatible input/profile combinations reject before mutation; explicit LLVM override mismatch rejects; actual libLTO/linker provenance is recorded. Execute a small real cross-TU link including preserved exports and failure paths. Independent review and synchronized build contracts required. Final compiler fixed-point/performance gate stays in com-p5um.

## Exclusions
No runtime fork, static LLVM rebuilding, new backend, public plew CLI feature, ordinary application build policy change or seed promotion.

## Basis
[Reviewed isolated comparison and three-unit plan](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-runtime-thinlto-investigation.json). User approved creation and execution of these three units. Task decomposition reviewed by abi_optimization_plan_review; plan does not certify implementation.

## Outcome: resolved

[Retained evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-thinlto-link-profile.json) records RED/GREEN and latest19 profile tests, three real cross-TU links, export/optimization checks and fixed-input tooling shell exit0. After that shell, only the ThinLTO validator and its test changed; profile-OFF legacy controls are explicitly reused while latest profile tests reran. The entire final source is not claimed to have rerun the shell.

Review found libraries could override the profile; strict library arguments and actual cc1 mode checks now reject it before preparation. Additional real counterexamples cover stale metadata and bare-bitcode filename/header spoofing; stdin analysis plus exact block recognition fixes the latter. Independent final review found no must-fix and accepted finite completion. Production callers remain unchanged; met-jv7m/met-kuej and formal performance are not certified.
