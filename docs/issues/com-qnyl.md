---
id: com-qnyl
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [backend, runtime]
---
# Specify remaining C interoperability API extensions

Current policy: handle Eq is not provided. Integer conversions use target signedness/value-range inclusion for lossless From/as versus fallible TryFrom, including nominally distinct CSize/USize/U64; this follows the normal conversion contract and is no longer an open threshold question. Handle identity APIs, type aliases and future repr(packed)/callconv require a concrete use and explicit source decision before implementation. They do not block the type-checking remediation. C numeric/string/ownership wrapper directions and native manifest link settings are already described in spec. expose publication is adopted. Anonymous callback and repr(c) coverage remain owned by com-0oxy and com-042v; do not duplicate them.

Design: [representation-and-abi](../design/representation-and-abi.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Check current spec for each proposed API, decide only genuinely open details, and distinguish implementation coverage audits from source-language changes.
