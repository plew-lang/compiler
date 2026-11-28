---
id: met-p5w2
status: in_progress
deps: []
links: []
created: 2026-11-28T14:36:49Z
type: task
priority: 1
assignee: Koji Murata
parent: com-i86w
tags: [performance, mid, api-scope]
---
# Narrow direct Array classifier metadata inputs

Bounded existing-audit subset mid-builder-direct-array-and-unsupported-shape-queries: midDirectArrayIndexExpr only. First map current direct/delegated reads, both actual callers and snapshot transport, confirm measured call volume, then choose scoped readonly inputs and implement without retaining Comp/MidBuildState through a wrapper or callback. Preserve raw stored type-head identity, admitted body facts, expression/access normalization and exact optional trace output. Do not broaden to recursive evaluator services com-xc6h or claim parent com-i86w completion; midExprIsCall own authority remains its separate parent subset.

## Acceptance Criteria

Review current input/caller map and minimal reader design before implementation. Preserve direct Expr.Index and Lower AccessCandidate forms; only the real Array declaration with one argument is direct; other Index witnesses, deferred/nonvalue facts and missing/bounds sentinels retain prior behavior. Keep trace enabled/disabled and numeric fields/order; do not normalize aliases/views or reselect source meaning. Constructors retain only justified metadata with coherent owner snapshots. Actual producer and both consumers change; old whole-Comp/state classifier path is removed. TDD or behavior-fixed GREEN controls plus structural capability checks, measured copies/call count and same-source uninstrumented LLVM/time, independent final review; final related whole gate is shared with met-b775/met-i61c. No ARC exemptions or verifier/test weakening.

## Current input map (product4ac60a9c)

- Classifier: Mid/Build.pw midDirectArrayIndexExpr,1017-1070. It reads c.arena.exprs/count, c.decls.accessCandidateForExpr/count/at.placeExpr, state.sourceFacts through midSourceSemanticExpression→PreparedSemanticFacts.expression, raw c.arena.typeCount/typeTermAt fields hasDecl/declOffset/siteOffset/args.len, c.langArrayDeclOffset and c.traceCodegen. No writer, interner, source selector or materializer is called. eprint/eprintU64 are the only trace effects. PreparedSemanticFacts is a sealed session/owner-bearing Ref[SourceBodyData] reader; preserve it rather than reconstruct facts.
- Actual private callers: midValueOperandForSourceExpr (both c and state inout) after source-type preparation and candidate lookup; midExprIsCall (owned readonly c/state) after expression bounds, before sourceExprRequiresCallSelection. The latter function's own wide-input obligation remains the other parent subset. All source/test references were searched; functions are not named values in Plew.
- Measured LLVM22/O0 count-only compiler:326777 classifier calls=295575 from value router+31202 from call-kind query; raw Expr.Index0; access-candidate misses323147, normalized candidate forms3630, direct results3530. Native status0/input unchanged. Do not infer seconds from O0 counts.

## Proposed bounded input boundary (review before implementation)

Keep the classifier as one private query over a private MidArrayPlaceInputs value: expression array; an Ir-owned access-place reader capturing only candidate rows+dense index; the existing Ir-owned TypeHeadReader extended with a raw four-scalar head-shape query; Optional[PreparedSemanticFacts]; Array declaration identity; trace-enabled scalar. No Comp, MidBuildState, callbacks or wrappers containing either. Both callers construct fresh inputs directly from needed fields/readers at the original call position; no cached view across later arena mutations.

Access-place and type-head readers have owner-only constructors. Return Optional place IDs so valid ExprId0 is distinct from absence; preserve first candidate wins, holes and bounds. Head shape exposes raw hasDecl, declaration/site offsets and argument count only; no alias/view normalization or name-based Array matching. Arena's existing synchronized typeRows/typeTerms contract applies; this does not promise safety for arbitrary malformed Raw arena substitutions (met-wuzv). New readers own CoW snapshots and require no language borrow/lifetime feature.

The classifier keeps the original normalization order, Value-only fact condition, zero/out-of-range type miss, declaration identity+one-argument predicate, expression-count sentinel, and numeric trace text/order, including when Array identity is0. Existing mutable builder/evaluator services are unchanged. Tests must exercise raw/normalized forms, non-Array witnesses, absent/deferred facts, zero/bounds, metadata snapshot stability, and trace on/off; reuse suitable existing Mid integration controls. Final source/output/performance/whole-group checks remain required.

## Implementation and finite behavior controls

The classifier now accepts only MidArrayPlaceInputs. Ir issues access snapshots and raw TypeHeadShape through existing typeHeads. Both actual callers construct inputs at the original point; no whole Comp/state/callback is retained. Private test injection preserves production module prefixes and never publishes test issuers in product. Standard harness registers test-direct-array-classifier.py. Metadata snapshot stability, first registration, place0, holes/bounds, raw shape, raw/normalized indexing, nonvalue/missing facts, invalid IDs, nonArray heads, and exact enabled/disabled trace are asserted. Before-v4 and after native probes passed; final permanent runner passed LLVM22/149 with immutable inputs. Evidence: [focused controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/array-classifier/focused.json).

Independent source/test review found no required boundary/behavior gap. Corrected its one stale summary phrase (snapshot controls are in the same probe). Performance/whole-group validation and task completion remain pending.

## Measured finite adoption

Non-instrumented before60294 / afterdeaa3 (source0bf3) alternate5pairs: medians7.920921→7.761889s, paired delta median−.178432s; all5pairs faster, all10LLVM equal/input unchanged, RSS effectively same. Count-only probes preserve all326777 classifier calls and3530 direct outcomes with identical LLVM. Native router stack frame allocation reduced from0x9200 to0x4870 in earlier pre-performance leaf/new candidate disassemblies (not the immediate paired before; excludes saved registers); this is not a whole-process memory claim. Independent reviewer supports finite adoption, not formal7s/fixed-point/whole completion. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/array-classifier/). Build compile/link passed but missing snapshot bin/ made final mv fail; recovered linked executable and smoke are recorded explicitly, not a successful build gate.
