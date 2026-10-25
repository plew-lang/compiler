---
id: com-3qne
status: open
deps: []
links: []
created: 2026-10-24T20:09:24Z
type: bug
priority: 0
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Repair trait subject default forwarding native crash


## Boundary and Exit

Valid run fixture trait_default_trait_subject generates a native executable that segfaults139 on baseline090240dd and measured6ddf8f75, with byte-identical LLVM and matching runtime. Base as Read provides read(count: I64 = 5); X as Base must support direct and generic calls, both producing5. Diagnose selection, default forwarding, body arguments and emitted call ABI through final execution; repair the producer/consumer contract without masking the crash or changing the user program. Preserve defaults and direct/generic dispatch with a targeted ownership and sanitizer contrast where applicable.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.

## Associated Callable-form Control

Also retain compiler/tmp/phase3f-associated-copies/default-associated-5.pw: Source as Target supplies assoc value(count: I64 = 5), S as Source, direct S.value() and generic T.value(). On fresh52a3ca0d/ab881a99, check succeeds but AOT finalization rejects function662 with body receiver mismatch (Self@1 pattern, S actual and expected, actual-decl172). This is not certified by com-9clj's nondefault associated witness repair. Independent body_receiver_completion_review assigns this generated callable-form/default forwarding route here; diagnose it alongside the original instance crash without assuming identical roots. Preserve associated ABI receiver0 and both direct/generic outputs5. Required before G1 and final gates; no namespace helper expansion or receiver validation weakening. Raw default-5 and default-trace-5 records retain failure and fixed input hashes.
