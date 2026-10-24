---
id: com-gnj9
status: in_progress
deps: [com-2suv, com-fbqh, com-px0e, com-o7ul, com-tl9c]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Verify saved exit targets drive Mid cleanup and final lowering

## Boundary

Phase 3E / E4. **Bounded final-consumer verification.** Parent criteria: 3, 5, 6, 8.
This is a bounded child of [com-fuo8](com-fuo8.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Mid/Build.pw`; `src/Mid/Prepare.pw`; `src/Codegen/Mono/Call.pw`; `src/Backend/Llvm/Mid.pw`.

Use E1 saved completion/target rows to trace give, return, local loop exit and empty-match paths into Mid CFG edges, cleanup and final LLVM. Reconcile existing com-gyup continuation ownership evidence rather than reopening it by default. Check abandoned result bindings/interpolation and mutable pattern captures at their actual final consumer.

## Exit and Evidence

Positive cleanup/ownership cases execute and incompatible/missing-source facts reject; no AST/last-statement/name rule reconstructs source completion in the migrated final readers. Record applicability of existing sanitizer evidence and register any newly exercised ownership path for the final suite; local source repairs are paired with the actual reader.

Existing starting controls: `give_exits_block`, `pattern_mutable_capture`, `block_loop_completion`, `block_abandoned_result`, `conditional_move_continuations`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Current Boundary Finding

E3 and its three repairs are independently closed at771150e1 with a6.978049s
formal checkpoint. Current E4 controls execute correctly, but exact source target
identities are not saved. body-checking/checked-body-storage require them; relative
completion tags and Mid lexical stacks do not discharge that contract.
The independently reviewed finite paired repair com-tl9c owns the producer,
publication and actual Mid mapping. E4 remains incomplete until it is admitted.
