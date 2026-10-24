---
id: com-f0mq
status: in_progress
deps: []
links: []
created: 2026-10-24T11:14:55Z
type: task
priority: 1
assignee: Koji Murata
parent: com-2suv
tags: [frontend, verification]
---
# Preserve established source types across repeated expected contexts


## Boundary

Finite E1 paired repair, parent criteria1/2/3/5/8, about1–2 active human working
days. Independent allocation reviewer `/root/associated_context_completion_review`
approved this concrete range at `8edd03af`, preserving the existing source
semantics and legitimate first-context completion. No whole inference rewrite.

## Decisive Evidence

`value_control_context_authority` at `ba200a6e` (with public projection setup)
reproduces all4 modes: direct/block unsuffixed scalar and empty Array first
typed with I8, then recontextualized with I16, change established types and
subsequent compatibility accepts. `authority-before-3` panics134 after reporting
all4 changes. Original parse/private-reader setup failures are separate in meta
`phase3e-context-authority-before.json`. Ordinary source miscompilation has not
been established; the source construction authority invariant is violated.

## Entry and Action

- `Frontend.pw` / `SourceFacts.pw`: add a private owner-local ExprId progress Set
  in SourceBodyBuilder, not another term table or immutable payload field. It
  records completion of initial contextual typing or source binding. Existing
  owner switching/fork/publish/fail lifetime must preserve/clear it naturally.
- Add shared effective-context and commit helpers for `recordExpr` and
  `recordSemanticExprExpectedResult`. A committed source term supplies subsequent
  construction context; the caller's requested expectation remains unchanged
  for normal compatibility/conversion checking. Context cannot rewrite it.
- Commit only after a real owner-local Value/Unit term has complete arguments,
  valid owner ParamId/Self/interface scope and no unfilled saved call selection.
  Use currentSourceOwner/sourceFacts.expression, sourceTypeHasCompleteArguments,
  recordedCallParameterState, declarationTypeScope/declarationTypeDependencies
  and callConstraintScope. Pending actual calls, incomplete callee binders and
  initial argument probes remain eligible for legitimate completion. ExpectedValue
  for non-call blocks/arrays is not an unselected actual call. Scope incompleteness
  before completion does not create a new rejection path.
- Commit a Let initializer after addLetLocal and source binding storage succeed;
  do not copy the binding slot type into the expression (conversions may differ).
- Final consumers continue using existing source term/completion/valueBlock/
  aggregate/operation facts; no marker read or semantic choice is added to Mid,
  Mono or backend. Avoid shape-specific exceptions, global writer freezes and
  syntax offset heuristics. No public writer exposure for controls.

## Exit

- Both context entry points preserve established scalar/Array direct/block
  types and child/block facts; ordinary compatibility rejects I16 after I8.
- Binding commitment, provisional Array[Sq]→first Array[any Shape], generic
  empty(), closure/default/provided/global owners and Comp-fork controls pass.
- Existing E1 normal17/reject16 plus shortcircuit nonvalue/nonBool controls and
  actual Mid/native consumers pass on a freshly built compiler, all inputs fixed.
- Builder progress has no successful-payload or parallel-type authority, no
  post-outcome writer, and does not prevent incomplete/provisional completion.
- Fresh whole compiler sourcecheck; formal fixed point and median below7s,
  investigating avoidable cost before declaring performance difficult.
- Independent completion review and synchronized contract/E1/worklog/receipts.

E1 and G1 require this repair. The child does not depend on its unfinished parent;
final whole-candidate normal/gen/deps/ASan-LSan gates remain G2a/G2b.

## Current Implementation and Verification

Initial policy production `63372a7c`, contract `fbab88b5`, controls `1b3e0520`.
The exact-scope fresh sourcecheck/native33/reject20 succeeded at initial policy
and again at `c428f54b`, which removes duplicate scope/template construction.
Formal generation2 fixed points were reached, but medians7.069296 and7.109320s
missed the below7s target; no completion admission follows from these runs.
Meta `phase3e-context-self-host-initial.json` and
`phase3e-context-self-host-scope.json` retain unsuccessful performance checkpoints,
same-source diagnostic comparison, and CPU/symbol diagnosis separately.

Production `66d84b81` memoizes only the successful lexical base scope inside the
builder, keyed by actual function input and current lexical root. Unregistered
functions/roots/receivers, synthetic scopes and failures are not cached;
interface proof roots are recomposed per call. All argument-completeness,
owner/selection and type dependency checks remain. Independent static review
found no blocker. Standard build `20261024T120241-build-aa05ff` succeeded;
fresh sourcecheck succeeded and native33/reject20 are running. The final
functional receipt is `phase3e-result-authority.json`; until updated it names
the previous candidate and must not certify66d84b81. Formal performance and
independent final admission remain pending. E1/G1 dependencies remain open.
