---
id: com-e9l2
status: in_progress
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify saved result recipes and projection identity at final reads

## Boundary

Phase 3C / C4. **Bounded closure verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Obligations.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Inventory the actual result-recipe variants in Ir, then trace Term/prior-call/project/optional-payload equivalents through sourceCallArgumentType, sourceSelectedCallResult and final type grounding. Keep source owner, callSite/slot and instance environment distinct; do not map recipe IDs onto type IDs or term zero onto Unit.

## Exit and Evidence

Every current recipe variant has its producer and final reader plus matching/wrong call-site, cross-instance, missing fact and genuine Unit/no-value controls. Retain the already repaired PriorCallResult.siteKey check. Repair only an identified variant boundary or link a blocking bounded repair; no new inference in final readers.

Existing starting controls: `source_call_result_site_authority`, `mid_type_recipe_instances`, `prepared_body_expression_owner`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Actual Variant and Consumer Inventory

| Representation | Producer | Retained identity and final read |
|---|---|---|
| Term (1) | Resolve/Expr::semanticTypeRecipeTerm; Record::semanticTypeRecipeForExpr for non-call expressions | Complete parametric term (including canonical projections); evaluateSemanticTypeRecipeForBody grounds it in the explicit BodyInstance and publishes a BodyTypeResult. |
| CallResult (2) | Resolve/Expr::recordSemanticExprCall; Record::semanticTypeRecipeForExpr and recordForItemTypeRecipe | Exact CallSiteKey including lexical owner, origin and slot. SourceSelectedCallResult checks that key against the selected template; final evaluation reads the descriptor for the explicit body/site. Diagnostic expression navigation does not select a result. |
| OptionalPayload (4) | Record::recordForItemTypeRecipe | Saved next-call recipe plus exact selected carrier declaration. Finalization reads that call result, checks owner and one child, and publishes the payload. |
| Former Project (3) | No source or test producer remains | The unused evaluator performed another assocBindingFor lookup from recipe-only trait fields. Remove this alternate projection authority and its four fields. Projections continue through canonical Term/call result evidence, not a new special case. |

All three live variants reach Ir/BodyInstances::setBodyTypeRecipeResult under
sourceKind1, separate from canonical term results under sourceKind2.
Mid/Instantiate::instantiateMidType requires the exact body/recipe publication,
checks true Unit against the retained same-site descriptor, then clears the
recipe in the instantiated local/place. Backend reads the instantiated Mid
terms; it neither evaluates a recipe nor reselects its source.

Existing mid_type_recipe_instances covers CallResult/OptionalPayload across
instances, wrong nominal carrier, missing publication and true/forged Unit.
The increment adds explicit wrong slot/lexical owner controls and Term recipes
under two explicit ParamId environments with the cursor on the other instance.
The true Unit case now runs the frontend producer before its Mid read.
Source-call site authority and prepared owner controls remain unchanged.
The first new internal edit omitted required MidLocalDecl.typeTerm in two
constructions; it failed checking and is corrected to zero without changing
the test purpose or weakening any assertion. Fresh candidate execution and
independent completion review are not yet complete.


### Source Iteration Readers and Review

Record::sourceForItemTerm reads the saved next CallResult by its exact site;
forItemPayload validates its recipe input and selected nominal carrier before
source binding. They do not reinterpret the source expression or select another
Item by name. mid_body_type_results is also a required control: a numerically
equal recipe ID and canonical type ID remain distinct sourceKind namespaces,
with per-instance projection results and missing-publication rejection in Mid.

Independent static review by /root/body_receiver_completion_review on f05188b4
confirms no Project producer or surviving reader requires the removed fields,
and the source/final/Mid identity and Unit contracts are retained. No static
blocker; fresh execution and final completion review remain pending.
