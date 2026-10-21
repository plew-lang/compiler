---
id: com-604k
status: in_progress
deps: [com-p10m, com-w4c2, com-6ygf, com-9ttw, met-si6j, met-k7ks, com-vy62, met-2t3l, com-ydgx, com-2p9p, com-wqd7, com-zgk9, com-lndr, met-0139, com-8w4c, com-7g6i, com-0k37, com-7u06, com-legt, com-f8bw, com-2o4w, com-cgdk, com-fkxl, com-j3pp, com-esri]
links: []
created: 2026-10-21T15:16:01Z
type: epic
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Align existing compiler features with adopted design

## Goal and Authority

Implement the adopted responsibility, decision, publication, ownership and failure contracts for features already provided by the compiler, from input through final consumption. Remove known in-scope deviations and obsolete migration authorities before returning to new feature implementation. The meta [progress plan](../../../agents/compiler-design-progress.md) owns phases/current stage; this epic owns integration scope and completion. Design/spec remain normative; no new compiler architecture is adopted here.

Scope classification is [com-esri](com-esri.md). Its pinned matrix records inclusion, exclusion and split ownership, not mutable issue statuses. Required integration work is expressed by this epic's tk dependencies, not another checklist with copied states. Mixed parents remain open for their excluded feature work; completion of their scoped child does not complete the original feature.

## Ordering and Start Conditions

Start with com-p10m (checked Buffer arithmetic/allocation publication), then com-w4c2 and com-6ygf as independent current correctness boundaries. No source/type-system migration blocks the first Buffer unit. The manual diagnostic repair com-ydgx is not a prerequisite when that repair uses the existing standard sanitizer gate.

The frontend uses com-kp3y for owner-local header/expression/binding/completion publication through actual Mid/Mono readers, then met-ucze/met-ia09/met-6e6k and final met-acfl closure. Existing closures/globals/aggregate/try/pattern readers must remain valid during each increment. Sequence is recommended implementation order, not evidence that every entire task blocks another: record a hard tk edge only where the complete named contract actually needs the prerequisite. met-si6j retains its existing current-surface criteria.

Other boundaries close in independent finite units. Current-reference identity precedes changing reference sendability; source operation/effect summaries must be available before global startup publication; generated result/provider identity must be final before its receipt publication/admission. These producer requirements do not imply waiting for unrelated new features or a second runtime. Current runtime/ABI/driver unit descriptions name their exact subset and final consumers.

## Integration Completion

All required task contracts hold through actual final consumers and cleanup/failure. Required unknowns have scoped proof or repair; existing successful lanes and declaration checks remain. Remove source reinference/reselection, required-fact fallback and replaced writers/readers for migrated contracts; legitimate instantiation and independent verification are preserved.

Complete current-source cross-boundary review and normal, generation, dependency, ASan/LSan, fixed-point and formal performance gates with matching inputs/artifacts/conditions. User-approved formal median is below 7 seconds; at least 7 seconds triggers investigation and stopping if repair is judged difficult. Preserve positive/reject/corrupt-boundary controls and source-mode parity for equivalent requested work. Do not turn unsupported APIs or every unknown language combination into this goal.

Synchronize spec/design/source/issue/evidence, then meet normal main integration criteria and merge before selecting new feature families. Investigation completion is not implementation completion; passing existing tests alone is not architectural closure. Any necessary unapproved semantic/architecture change is a user decision, not an excuse to weaken the design or gates.
