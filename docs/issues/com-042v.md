---
id: com-042v
status: open
deps: []
links: []
created: 2026-10-13T00:51:00Z
type: task
priority: 3
assignee: Koji Murata
tags: [backend, frontend, verification]
---
# Close repr(c) layout and aggregate C ABI implementation coverage

The spec documents repr(c) shared structs, but the earlier expose implementation deliberately covered scalar/pointer boundaries rather than general aggregate classification. The retained implementation note reports repr(c) parser/AST/type support absent. This migration has not exhaustively audited current support; confirm the actual parser-to-final-consumer state before treating it as a current reproduced defect. A matching LLVM struct shape alone does not establish a valid target C function ABI.

Evidence: spec/04-execution/15-modules.md shared struct section; former meta C callback note (Git history); representation chapter focused source base 6fe09bc7c0e75260b3f773643921478b5020b94f, whose CAbi scope covers scalar/pointer conversion and attributes. Historical exposed probes do not prove aggregate support.

## Design

[Representation and ABI](../design/representation-and-abi.md#native-external-boundaries) separates C memory layout, call classification, ownership eligibility and target policy. Preserve common imported-call/exposed-definition classification. This issue does not adopt a new repr syntax or authorize relaxing acceptance.

## Acceptance Criteria

Audit shared Syntax, AST/semantic type representation, layout, construction/access, imported/exposed direct/indirect calls and diagnostics. Record confirmed gaps, then close accepted-spec support through all consumers with target-specific C comparisons, two-way calls, inout, stack/results, O0/O2 and applicable sanitizer checks. Unsupported targets must reject explicitly; reference Clang remains a development tool.

