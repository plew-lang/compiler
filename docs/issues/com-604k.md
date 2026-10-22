---
id: com-604k
status: in_progress
deps: [com-p10m, com-w4c2, com-6ygf, com-9ttw, met-si6j, met-k7ks, met-2t3l, com-ydgx, com-2p9p, com-wqd7, com-zgk9, com-lndr, met-0139, com-8w4c, com-7g6i, com-0k37, com-7u06, com-legt, com-f8bw, com-2o4w, com-cgdk, com-fkxl, com-j3pp, com-esri, met-8b8w]
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

Phase 2 is complete: com-p10m (checked Buffer arithmetic/allocation publication), com-w4c2 (root-owned use), com-6ygf (layout admission) and its teardown prerequisite com-34wl are closed. The strengthened declaration controls from independent review com-i5vp now pass after the symbol-pool lifetime repair. The [completion audit](../../../evidence/existing-feature-conformance/phase-two-review/completion-audit.json) matches current source/std/fixture and native-test hashes to the applicable saved gates, verifies affected native/product checks, and confirms generation-2 fixed point with median 6.211262 seconds. The fresh independent re-review [com-io5f](com-io5f.md) now recognizes all phase-two units, including the repaired ORC lifetime, with no blocking findings. This is bounded phase-two completion, not completion of the epic. Proceed to the frontend increment below; final integration gates remain required. The manual diagnostic repair com-ydgx is not a prerequisite when that repair uses the existing standard sanitizer gate.

com-w4c2 follows the approved root-only use rule, with one module-wide binding environment shared by parts. Its scope includes real part/provider/consumer migration; the former file-local lookup direction is superseded. Reconsideration conditions for macro dependency verbosity/collisions belong to the source design, not an immediate exception or another mandatory feature family.

The frontend uses com-kp3y for owner-local header/expression/binding/completion publication through actual Mid/Mono readers, then met-ucze/met-ia09/met-6e6k and final met-acfl closure. Existing closures/globals/aggregate/try/pattern readers must remain valid during each increment. Sequence is recommended implementation order, not evidence that every entire task blocks another: record a hard tk edge only where the complete named contract actually needs the prerequisite. met-si6j retains its existing current-surface criteria.

Current-gen handoff/framing/receipts are scoped by [met-8b8w](met-8b8w.md); its parent com-vy62 retains the absent macro/macrointerface public-role migration, which does not block current-feature integration. This is a migration boundary, not a change to the adopted final macro design.

Other boundaries close in independent finite units. Current-reference identity precedes changing reference sendability; source operation/effect summaries must be available before global startup publication; generated result/provider identity must be final before its receipt publication/admission. These producer requirements do not imply waiting for unrelated new features or a second runtime. Current runtime/ABI/driver unit descriptions name their exact subset and final consumers.

## Integration Completion

All required task contracts hold through actual final consumers and cleanup/failure. Required unknowns have scoped proof or repair; existing successful lanes and declaration checks remain. Remove source reinference/reselection, required-fact fallback and replaced writers/readers for migrated contracts; legitimate instantiation and independent verification are preserved.

Complete current-source cross-boundary review and normal, generation, dependency, ASan/LSan, fixed-point and formal performance gates with matching inputs/artifacts/conditions. User-approved formal median is below 7 seconds; at least 7 seconds triggers investigation and stopping if repair is judged difficult. Preserve positive/reject/corrupt-boundary controls and source-mode parity for equivalent requested work. Do not turn unsupported APIs or every unknown language combination into this goal.

Synchronize spec/design/source/issue/evidence, then meet normal main integration criteria and merge before selecting new feature families. Investigation completion is not implementation completion; passing existing tests alone is not architectural closure. Any necessary unapproved semantic/architecture change is a user decision, not an excuse to weaken the design or gates.
