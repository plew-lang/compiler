---
id: com-vy62
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, driver]
---
# Audit metaprogramming isolation and generated-source freshness

Retained boundaries: isolation of multiple provider Syntax versions, host dependency separation, stale generated-part detection and authoring support. String runner exchange and host/target responsibilities are adopted; version isolation/freshness must not be inferred merely from successful generation. Current chapter audit is focused and does not prove full implementation.

Design: [metaprogramming](../design/metaprogramming.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Compare current producers and final consumers with the package/metaprogramming specs, record evidenced gaps separately from uninspected cases, and close each selected isolation/freshness contract end to end.
