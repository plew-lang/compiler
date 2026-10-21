---
id: met-si6j
status: open
deps: []
links: []
created: 2026-10-13T01:29:29Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Complete checked frontend authority from source to final consumers

This is the parent for the paused type-resolution/type-checking remediation. The target is one body-checking authority for committed meaning and read-only downstream consumption under explicit environments, not one AST walk. Two mandatory rules apply to every increment: **close storage through final use** and **do not stop at adding checks**. Remove the replaced decision path and structurally close write authority.

## Scope and Restart

Scope is the compiler's currently provided type-checking surface and the already approved divergence/flow changes. This is not a requirement to implement every unsupported feature, broaden inference or implicit conversions, redesign runtime/backend, or add persistent incremental compilation. Declaration worklists interpret saved obligations; they must not become another AST-driven type checker.

Implementation remains paused during the design/conformance audit. [Checked-body storage and the restart design](../design/checked-body-storage.md) are adopted and reviewed; [met-j9mv](met-j9mv.md) retains the reconciled cumulative candidate and fresh baseline. Preserve these successful increments/evidence; do not repeat an unchanged baseline solely because this issue previously described the gate as pending. Worklog owns the selected candidate/carrier, active handles, verification and next step. Historical candidates and measurements in [migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) do not establish current-tree readiness.

Design authorities: [Body Checking](../design/body-checking.md), [Types and Evidence](../design/types-and-evidence.md), [Generics](../design/generics.md), [Compiler State](../design/compiler-state.md), [Frontend Handoffs](../design/frontend-handoffs.md). The storage supplement owns the adopted physical design and restart details; these chapters own logical contracts.

## Completion Criteria

Each item requires implementation locations and scoped verification records, not checkbox completion from wrappers or green tests alone.

1. [ ] Expected types only fill permitted unknown information or check compatibility; they never overwrite expression shape, explicit or committed semantic type.
2. [ ] Distinguish unrecorded facts, local inference variables, deferred obligations, incompatibility, Unit, rigid parameters and no normal value. No unresolved source typing obligation survives successful publication.
3. [ ] One authority for types, calls, proofs and conversions connects source recording/success through explicit instantiation to final Mid/backend consumers; no AST reinference or name reselection by final readers.
4. [ ] Functions, factories, adapters, operators and implicit calls check complete signature, labels, ownership modes and bounds; candidate existence is not final validity.
5. [ ] Under the same available context, expression wrapping changes acceptance only where the adopted value/divergence rules require it. Block/if/match/short-circuit share normal results and exit targets; checked dead code cannot contaminate live joins.
6. [ ] Integrate approved divergence: value-position rejection, following-code errors versus analytical-loop warnings, loop-following give, empty match, diverging function values versus invocation and forbidden normal-function conversion. Centralize semantic completion; keep diagnostic reachability distinct from execution/ownership flow.
7. [ ] check/build/run/gen use the same semantics for requested bodies. Lazy run may omit unused bodies; it may not defer invalidity in a requested body.
8. [ ] Remove migrated reinference fallbacks, partial acceptance and duplicate semantic state; structurally separate constructing writers from immutable readers. Retained adapters are one-way representation transforms. Demonstrate final consumers, removed decisions and post-completion write rejection.
9. [ ] Close historical D1/D4/D5 controls and classify/address D2/D3/D6 risks. Uninspected coverage is not completion; preserve representative positive/reject combinations.
10. [ ] Complete normal, generation, dependency, ASan/LSan, fixed-point and formal performance gates with matching source/carrier/artifacts. Satisfy the retained 5.7-second condition or obtain an explicit approved change; focused and old-driver checks do not substitute.
11. [ ] Synchronize design contracts, issue state and worklog. Unresolved in-scope items preclude completion; main integration follows the normal integration criteria.

## Work Units

- [met-j9mv](met-j9mv.md)
- [met-ucze](met-ucze.md)
- [met-ia09](met-ia09.md)
- [met-acfl](met-acfl.md)
- [met-6e6k](met-6e6k.md)
- [met-rzt4](met-rzt4.md)

Completion-flow work also uses [com-tijs](com-tijs.md) and the existing control-flow audit [com-gyup](com-gyup.md). [com-uutc](com-uutc.md) is a retained adjacent acceptance audit, not an automatic expansion of this parent's required scope. Unsupported unique/capture shapes keep their separate tasks.

## Stop Conditions

Stop for an unapproved specification change; a language-specific design decision not derivable from adopted policy/Rust/Swift references; tooling/environment failure preventing necessary validation after diagnosis; or self-compilation at least 5.7 seconds when repair is judged difficult. A threshold crossing alone does not establish irreparable cost: investigate with matching-source comparisons. Do not weaken validators, checks, test expectations or performance conditions to continue.

Stop for erroneous tests except authorized cases: tests broken by an approved specification change, internal non-language-surface tests, or newly written tests that have never passed may be repaired after preserving their original purpose. An unrelated known limitation need not block a bounded required fix. Keep unresolved design issues explicit rather than calling a compromise the final design.
