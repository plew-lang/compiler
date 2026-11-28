---
id: met-8vnu
status: in_progress
deps: []
links: []
created: 2026-11-28T15:22:43Z
type: task
priority: 1
assignee: Koji Murata
parent: com-ge01
tags: [mid, frontend, performance]
---
# Measure and narrow saved Mid admission query inputs


## Guarantee and bounded actions

Investigate the two private midSourceStateAdmitted/midSourceStatementAdmitted queries under com-ge01. First measure actual calls on the fixed self-compile source. They read only current sourceFactSession scalar, Optional[PreparedSemanticFacts] and, for statements, exact statementCompletion row. No mutable service is used; construction/admitSource still owns full owner validation. Preserve session/missing facts/statement membership and all actual callers, including public builder reject behavior. Do not weaken admission or add owner authority via raw scalars.

If measured traffic justifies it, narrow actual signatures and all callers to the required data (no whole Comp/state wrapper/callback). Behavior-fixed GREEN controls and structural actual-caller inspection are required; unchanged session/foreign/missing/statement controls must reach final public consumer. Excludes prepareMidSourceState/admitSource, expression/transfer reader and evaluator redesign, no language changes. Measure same-source LLVM/time before/after and review independently. Final related whole gate is shared; do not close parent based on this subset. If little cost, close as investigated with evidence rather than implement gratuitously.

## Initial observations

Post-Array candidate deaa3 paired median7.761889 still exceeds7s. CPU windows (not whole-run percentages) retain operand/call building and ARC/copy costs. The admission queries currently accept Comp and MidBuildState despite reading only the scalar session + sealed fact handle; all direct invocations must be enumerated before edit. Required checks remain unchanged; immutable-session observations are not arbitrary fact publication authority.

## Measured selection and source boundary

Count-only LLVM22/O0 compiler on the frozen self-source: state query152530 calls, statement query0. Native0, inputs unchanged, LLVM equal to preceding candidate; no time inferred from O0. [counts](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/admission-queries/before-counts.json).

Independent input-map/source review confirmed two outside state calls plus statement delegation and eight statement calls; all ten outside callers now pass the current Comp session and that same state's facts at the original point. checkedRange short circuit, constructor/admitSource owner proof and statement-read order remain unchanged. No Comp/state wrapper survives.

Existing mid_source_owner_admission native before/after both0, immutable inputs and expected stdout exact. The public consumers still cover success, wrong owner, other owner's statement, no facts and foreign session. [controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/admission-queries/controls.json). Independent reviewer found no source repair needed. Non-instrumented time and final related whole gate remain pending; this finite subset does not close com-ge01.

## Non-instrumented bounded comparison

Build20261128T152548-build-ac6a76 passed with immutable inputs. Candidate ac8fcfa6 (sourcef967a9fa) own-source smoke passed. Five alternating same-source pairs, beforedeaa3/afterac8: medians7.847823→7.808626s, all10LLVM equal, inputs unchanged. The small observed difference is inconclusive as a stable speedup; record pair distribution rather than generalize improvement. Queries retain identical counts/output, and input-boundary design is independently supported. Original counter input fingerprints cover probe construction only, not a native-target pre/post guarantee; LLVM peer identity is recorded separately. Public consumer controls were repeated with fixture files in input hashes and passed before/after. Independent finite retention review supports the boundary cleanup without stable-speedup claim; final whole gate remains pending.
