---
id: com-yr1o
status: open
deps: []
links: []
created: 2026-10-13T01:03:55Z
type: task
priority: 3
assignee: Koji Murata
tags: [runtime, driver]
---
# Define reusable host environment termination before Hot Restart integration

Current one-shot execution deliberately does not promise surviving-host restart. Approved future direction: [Hot Restart decision](../design/decisions/hot-restart.md). Historical evidence is [archived evidence](../../../evidence/2026-10-01/compiler/orc-restart/README.md); its generated-C rewriting and linear ledger are diagnostics, not production lifecycle APIs.

Complete by defining environment ownership of globals, allocations, frames, queued calls, timers and code; quiescent termination, generation-token delivery, foreign-resource boundaries and pre/post-commit failure transitions. Preserve ordinary Promise/deinit semantics and the common AOT/JIT runtime. Verify repeated cleanup and fresh state, old notification rejection, failures and recovery, AOT comparison and sanitizer fault controls. Platform/embedding claims require separate target evidence. New source semantics or a separate runtime require a decision. This issue is deferred implementation/design work, not a new active implementation goal.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: unimplemented or independent release capability**.

Reusable execution teardown/Hot Restart is deliberately future host scope. One-shot failure/signals/root lifetime remains included.
