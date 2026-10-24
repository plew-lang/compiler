---
id: com-rv13
status: closed
deps: [com-oi3v]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-kp3y
tags: [frontend, verification]
---
# Reconcile owner payload publication and core final-reader closure

## Boundary

Phase 3D / D1. **Bounded closure verification of implemented storage.** Parent criteria: 2, 3, 8.
This is a bounded child of [com-kp3y](com-kp3y.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Record.pw`; `src/Mid/Build.pw`; `src/Codegen/Mono/Call.pw`.

Audit only header, expression, binding, completion, aggregate, try and pattern payload APIs: construction writer -> success/failure publication -> PreparedSemanticFacts -> actual Mid/Mono reader. Reuse owner-local Ref-backed storage; confirm removed all-owner tables/snapshots and distinguish required absence from a non-applicable optional fact.

## Exit and Evidence

A seven-family API table identifies writer privacy/state checks and final readers. Retained-reader, fork, missing/foreign owner/session, stable failure and post-success/post-failure writes have applicable controls. Every old writer/table/fallback in this component is removed or explicitly construction-only. Do not repeat the existing storage migration; local gaps require exact paired repair children.

Existing starting controls: `source_owner_payload_stability`, `source_builder_branch_isolation`, `prepared_aggregate_source_owner`, `prepared_try_source_owner`, `prepared_match_source_owner`, `source_fact_directory_private`, `source_prepared_payload_private`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Seven-Family Reconciliation

The inspected implementation is production b9187931 (the task-selection commit
is 3f86096e). This is verification of the existing storage component, not a new
storage migration. The table identifies the independently reviewed authority boundary.

| Family | Construction writer | Successful reader and actual final use | Required absence versus non-applicability |
|---|---|---|---|
| Header | Resolve/Record::recordSourceBodySignature; private SourceBodySignature/Parameter factories | PreparedSemanticFacts.functionSignature; preparedFunctionBodySignature; Mid::buildParametricMidBody's source signature | An executable source body without a signature is MissingSemanticType; registered bodyless declarations deliberately have no body payload |
| Expression | Resolve/Expr::recordSemanticExprInfo/Term/LiteralContext/FieldProjection and recordKnownExpressionResult; private storeBuildingSemanticExprType | PreparedSemanticFacts.expression; preparedBodyExpression; Mid::midSourceSemanticType and Mono::groundCallArgumentSource | Missing/Unrecorded fails; Pending is construction-only; published completed expression facts or retained selected call-result recipes are authoritative; Unit and NoNormalValue remain explicit categories |
| Binding | Resolve/Record::recordStmt; private storeBuildingSemanticBinding and SourceBodyData.putBinding | PreparedSemanticFacts.binding; Mid::buildMidLet consumes type and ended binding identity | A demanded let needs a matching statement row; no type/name recovery from Stmt.Let or mutable TypeCache |
| Completion | Resolve/Expr::recordInvocationCompletion/recordSemanticExprCompletion and private statement completion storage | PreparedSemanticFacts.expressionCompletion/statementCompletion/valueBlock; Check/Return::checkedSemantic*Completion/semanticStmtCompletionInOwner; Mid block construction and Mono::scanBlockInsts | Required owner/row/session absence is an error; publication removes non-value normal block rows, not checked expression flow |
| Aggregate | Resolve/Record::recordSemanticAggregate/putSemanticAggregate; private SourceBodyData.putAggregate | PreparedSemanticFacts.aggregate; preparedBodyAggregate; Mid::midSemanticAggregateForSourceBody/materializeMidAggregateValue; Mono::finalizeCurrentBodyAggregate | Optional lookup permits a non-aggregate operation; demanded Array/aggregate materialization requires its saved plan. EvaluationOnly is explicit |
| Try | Resolve/Record::putSemanticTry; private SourceBodyData.putTry | PreparedSemanticFacts.tryDecomposition; preparedBodyTry; Mid::materializeMidTry; Mono::registerTryConversion | Non-try lookup may be absent; a demanded try without its decomposition fails rather than reselecting Result/from information |
| Pattern | Resolve/Record::recordSemanticMatch/recordStructPattern/recordSemanticPatterns/putSemanticMatch; private SourceBodyData.putMatch | PreparedSemanticFacts.pattern; preparedBodyMatch; Mid::buildMidPatternMatch; Mono::finalizeCurrentBodyMatch | Statement/expression/condition identities are separate local keys; a demanded match needs its saved match plan, not a new pattern analysis |

All seven writers feed private owner-local SourceBodyData through
SourceFactDirectory.activate. That boundary accepts only new/building owners;
completed/failed owners cannot regain a writer. Public Record entry points reject
closed construction, while raw backing helpers and factories remain module-private.
putSemanticAggregate/Try/Match also check sourceOwnerConstructionClosed directly.

finishSourceFacts publishes only after the shared request/check result succeeds.
publish requires a preparation request, seals one immutable Ref-backed payload and
registers a retained reader. fail discards active/inactive builders and retains its
first diagnostic; later outcome/publication attempts cannot bless failure.
preparedSemanticFacts requires a successful owner and returns failure verbatim.
The bodyless Registered state remains distinct from a successful source body.

PreparedSemanticFacts readers retain one owner/session/payload and local indexes.
sourceConsumerFacts caches only a reader index with owner/session checks; it does
not copy the directory or every owner's rows. Construction expression/statement/
pattern getters may inspect Building state and are not final-consumer authority.
Current Mid/Mono searches contain no uses of sourceSemanticExprTypeAt,
constructionExpression/Pattern or semanticExprTerm, nor the retired all-owner
semanticExprTypes/Bindings/Aggregates/Tries/Matches/StmtCompletions or snapshot
types. Mutable TypeCache is construction input, not a missing-fact fallback.

The scoped run uses the separately retained generation2 fixed-point compiler
bin/plewc-phase3c-descriptors-fixed, SHA256
d6c3e55adfd54876c6b6f2a0d2afb60fdfe2a371eb5111fd436131a8c8d139a5.
It covers retained readers, forked construction, missing/unprepared/foreign
owners, cross-session rejection, stable failure, post-outcome writes and private
payload/directory/signature construction. Full final gates remain G2a/G2b.

## Outcome

D1 and its exact paired repair [com-oi3v](com-oi3v.md) are complete at production
**c1b731bd**. The independent audit first found a present-row/foreign-function
admission hole at public lower Mid consumers; D1 was not closed on the older
native11/reject3 prefix. The reviewed child now binds sourceFunction to private
owner/session-validated facts at prepareMidSourceState, keeps initial draft-only,
and checks session plus saved statement membership at real public consumers.
Unit-return, missing facts, foreign statement/session and the former unchecked
constructor are covered. Private cores add no new owner/type/callee inference;
existing identity canonicalization is preserved.

Fresh SHA256 **2dbfc42185400b46875e0029c4a8a027143220d04c1d60dcb0fb594dc7e98660**,
standard build **20261024T100003-build-183956**, full sourcecheck and normal28/
reject4 pass with unchanged inputs. /root/associated_context_completion_review
recognizes both D1 and com-oi3v complete without blockers, verifies current input
fingerprints/carrier, all15 reference hashes and5 embedded summaries. The original
corrected baseline and preliminary new-fixture setup/import failures remain
separate from the successful final run.

Meta **768e7d80** preserves `evidence/existing-feature-conformance/source-owner-facts/
phase3d-owner-admission.json`. Separate **20261024T100858-self-host-8126f0** reaches
generation2 fixed point, median **6.830579s**, exit0 and unchanged inputs; see
`phase3d-owner-self-host.json`. Measured compiler is retained as
bin/plewc-phase3d-owner-admission-fixed, SHA256
**434e711ea2eddeaa5cb4070bce88d69f84b9b2e3a421f9056fd48d2374c27f5f**.
All sessions are recovered. D2 domain ownership, D3 operation/constraint APIs,
subsequent tasks, parent completion and full G2 gates remain outside this closure.
No main/seed/adopted carrier promotion is made.
