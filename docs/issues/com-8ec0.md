---
id: com-8ec0
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [verification, driver]
---
# Implement specified language-level test collection and execution

The specified test declaration is not the current fixture runner. Collect all test blocks in the selected target independent of references, retain ordinary module visibility, exclude test declarations from production linking, and leave ordinary program semantics unchanged. expect-family failures use a runner-continuation channel distinct from production assert/panic. Failure transport, async/doc tests and diagnostic display integration still need design; expected/actual labels and the basic expect family are already specified.

Design: [verification](../design/verification.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Implement producer-to-runner collection and failure reporting with no silent discovery omissions; resolve only the remaining protocol details, and validate production exclusion and unchanged ordinary-code meaning.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

Pinned Syntax TopItemAst/semantic top-item forms have no language test-block
variant in the inspected grammar. Distribution CLI and native tool modes do not
collect/run such declarations. tests/README.md describes external run/reject/
part/gen/sanitizer fixtures instead. Thus the language-level test feature of
spec15 remains absent; the existing fixture infrastructure and its passing records
are real but do not establish language test support.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: unimplemented or independent release capability**.

Language-level test syntax/discovery/runner is absent. Existing external fixture and sanitizer infrastructure remains mandatory for validation.
