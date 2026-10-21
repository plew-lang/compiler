---
id: com-ao7z
status: open
deps: []
links: []
created: 2026-10-13T00:52:45Z
type: task
priority: 3
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Complete standalone release admission on clean supported hosts

Single-file static LLVM distribution feasibility and local relocation were verified for historical candidates, but this does not establish public-release readiness. Clean-host, minimum-OS, signing/notarization, current-source reconstruction and promotion gates remain separate. Existing candidate binary/scratch paths were cleaned; preserve historical evidence as evidence rather than asserting an artifact still exists.

Evidence: retained meta evidence/2026-10-01 compiler/static-llvm-performance and compiler/thinlto records, and saved meta evidence/2026-10-01/validation-results.json; current meta validation describes the adopted distribution entry separately. Recipe initially targets macOS 26/arm64 with LLVM 20.1.1; this is not a supported-platform promise for other systems. No new package or release test was run during design consolidation.

## Design

[Driver distribution contract](../design/driver-and-execution.md#distribution-boundary) and [build guide](../../scripts/build/README.md). Keep ordinary dynamic-LLVM development unchanged; distribution archives and optional ThinLTO are explicit recipe inputs, not default carrier replacements.

## Acceptance Criteria

Rebuild selected current sources with recorded compiler/tool/archive/resource/license hashes and target/minimum OS. Audit non-OS dynamic closure and run relocation with only allowed OS tools, then independently verify clean supported hosts and minimum OS. Exercise build/run/check/gen/resolve, diagnostics/output preservation, explicit checkout resource selection, and separate git/native dependency requirements. Complete applicable suites, sanitizer, fixed point/performance and promotion criteria; record signing/notarization and release identity. Do not equate local PATH hiding or historical gate success with release completion.
