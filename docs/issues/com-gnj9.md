---
id: com-gnj9
status: closed
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

## Completion and Independent Admission

The paired com-tl9c repair now closes producer -> private publication -> saved
identity -> actual Mid destination/cleanup at dea2b38d, refined36680385. Its
outcome and durable receipt own exact source/removed paths and controls.

Direct/nested gives, block/if/match results, return through block/loop, nested
break/continue and while-condition local loops, closure-local return, try Err
return and operand-first exits retain their source targets. Abandoned result/
interpolation and mutable pattern/conditional ownership controls execute through
strict Mid verification and LLVM. Existing com-gyup ownership evidence is
reconciled, not reopened or replaced by reachability assumptions. Missing, wrong
kind, foreign session/owner and same-owner nonenclosing/sibling loop mapping fail
at the real readers. Saved relative completion remains a separate pure algebra.

Independent review admits the initial90 functional cases and refined60 affected
cases, all-source checks and exact fixed-point artifacts. Refined formal median
is7.072914s. On 2026-10-25 the user removed below7s from the bounded3E completion
exit. /root/body_receiver_completion_review reconciled E1–E4 and found no other
unfinished E4 obligation. Close with com-tl9c under that approved exit; retain
the measured time and historical unmet records. This does not certify G2,
whole phase three or main/seed/adopted-carrier promotion.
