---
id: com-oi3v
status: in_progress
deps: []
links: []
created: 2026-10-24T09:47:32Z
type: task
priority: 1
assignee: Koji Murata
parent: com-rv13
tags: [frontend, mid, verification]
---
# Admit source Mid build states through exact owner and session boundaries

Close the evidenced lower Mid builder admission gap found by D1; preserve private source facts and exact function/owner/session through state construction and actual statement consumers.


## Boundary and Evidence

Finite paired repair discovered by D1 com-rv13. Parent criteria2/3/8. Expected
active effort1–2 working days; source state admission and core source statement
builders only. No language change, new lifetime scheme, runtime model or general
CheckedBody capability migration.

At production b9187931/task head3f86096e, the public MidBuildState.initial accepts
arbitrary sourceFacts. Public lower builders then read matching rows without
checking that the retained facts belong to state.sourceFunction. A valid first
owner let lowers successfully; the same fact/statement with second as the source
function also succeeds. The new internal mid_source_owner_admission probe fails
with `another source owner's binding reached Mid`. This is actual lower Mid
consumer admission, not an ordinary-source miscompilation. `before-1` failed its
new-test I64-return setup before the decisive case; corrected `before-2` is the
reproduction. Carrier d6c3e55adfd54876c6b6f2a0d2afb60fdfe2a371eb5111fd436131a8c8d139a5,
watch-command per compile/link/run, inputs unchanged, session81648 recovered.

The same source API also lets a value-less return bypass missing/foreign-session
facts and statement membership. Normal buildParametricMidBody obtains correct
facts; that does not authorize accepting foreign state through its public lower
consumers. The source backing remains opaque; no new backing writer is needed.

## Reviewed Implementation Plan

1. Keep initial as a facts-free draft constructor. Introduce validated source
   state construction through Comp and exact source function/explicit owner;
   combine an immutable source identity with private retained facts. Use the
   existing owner/session algebra and existing alias/closure/global identities.
2. Public source-consuming builders check the current Comp session and saved
   statement completion membership before creating Mid. Private core consumers
   use admitted state without resolving the owner for every expression.
3. Re-admit only the existing global builder's explicit source-facts switch.
   Pure synthetic/draft Mid construction remains distinct from authored source
   consumption. Do not add new domain semantics or a fallback when facts are absent.
4. Migrate the approximately8 existing internal factory fixtures without changing
   their test intent; add same-session wrong-owner/present-row, foreign-session,
   missing source, wrong statement and Unit-return controls at real consumers.
5. Build a fresh compiler, run full sourcecheck plus affected storage/Mid/domain
   controls and the decisive new fixture, preserve input/carrier hashes, obtain
   independent completion review. Keep performance below the existing7s goal;
   formal measurement is a separate isolated checkpoint when needed.

Reviewed by /root/associated_context_completion_review: use validated source
construction (B) plus minimum public-consumer session/membership guards (A).
A-only lazy/cached guards keep constructible invalid states and are not the
preferred endpoint. The paired producer/state/reader boundary is finite and
appropriately sized; no unallocated larger redesign was identified.

## Dependency and Exit

D1 depends on this child before claiming its foreign/missing actual-consumer
closure. D2 keeps domain-wide closure/global/default/provided verification; this
repair only consumes their existing owner identities. D3 keeps operation and
constraint writer closure. Do not silently move either sibling's work here.
Exit requires removal of arbitrary-facts source construction, shared admission at
all affected public source-consumer entries, no private-core re-resolution,
positive/negative actual Mid evidence, internal fixture migration, source/fresh
validation and independent review. Final G2/parent completion remains outside it.
