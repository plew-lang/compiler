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
