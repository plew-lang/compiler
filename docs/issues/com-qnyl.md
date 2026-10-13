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

Retained design questions: handle Eq (currently not provided), platform-width conversion thresholds, type aliases and future repr(packed)/callconv. C numeric/string/ownership wrapper directions and native manifest link settings are already described in spec and are not wholly undecided. expose publication is adopted. Anonymous callback and repr(c) coverage are owned by com-0oxy and com-042v; do not duplicate them.

Design: [representation-and-abi](../design/representation-and-abi.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Check current spec for each proposed API, decide only genuinely open details, and distinguish implementation coverage audits from source-language changes.
