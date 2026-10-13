---
id: com-mnsx
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [runtime, frontend]
---
# Specify remaining text view and iteration APIs

Retained standard-library design work: builder API boundaries not already covered by the adopted formatting/output contracts; normalization and Grapheme representation; Slice/Substring/SubBuffer ownership and retained-storage cost; missing generic Iterator/Iterable signatures. Step and existing formatting/output contracts are already specified and must not be reopened merely because the old note listed builder or iteration broadly. Consult current basic-types spec before choosing any API.

Design: [representation-and-abi](../design/representation-and-abi.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Separate already specified contracts from genuinely absent API decisions; document remaining choices and ownership/cost consequences before implementing them.
