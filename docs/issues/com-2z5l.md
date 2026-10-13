---
id: com-2z5l
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime]
---
# Implement future shared-reference cycle reporting and reclamation

The concurrency spec describes a future additive shared-reference-graph collector, separate from deterministic normal ARC destruction. Report detected garbage cycles and reclaim memory without running cyclic members user deinit; idle per-thread ownership/sharing boundaries need an implementation protocol. This is not an existing collector or an evidenced newly reproduced bug.

Design: [runtime](../design/runtime.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Define/report the supported graph and safe-point protocol, preserve normal ARC semantics, verify reporting and reclamation separately, and retain the specified no-deinit behavior for reclaimed cycles.
