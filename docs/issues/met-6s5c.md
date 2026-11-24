---
id: met-6s5c
status: closed
deps: []
links: []
created: 2026-11-24T02:23:59Z
type: task
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Trace remaining value-inference refusal producers

Fresh normal48a65b retains262 negative classification failures and23 nonnegative failures. Investigate only reject/assoc_fn_value_arg, reject/block_generic_literal, reject/named_fn_value_arg, reject/named_fn_value_return and reject/type_operator_unused_function_operator. They print the same unavailable-type-context reason but that is not evidence of one producer or Source eligibility. Reproduce each with adopted d2 carrier, inspect real source expression/name/expected-type path, originating typed result and each retained/cache/driver consumer. Compare spec and existing owners; do not mark Source from message, fabricate an authored receipt, add broad rechecking or weaken fixtures/verifier. Investigation does not claim implementation completion.

## Acceptance Criteria

For all5 cases preserve source/golden/carrier/actual CLI domain evidence; identify exact producer return and source ownership/admission and actual consumer path, with relevant normal/raw/failure controls. Classify Source-eligible semantic refusal versus unsupported/unresolved/malformed/internal state by existing contracts. Reconcile existing tickets, create finite repair children with guarantees/exclusions/dependencies and executable RED scenarios for distinct owners. Independent neutral review of coverage and assignments; leave product repairs and parent whole/formal gates open.


## Executed frontier and split proposal

Adoptedd2 reproduces all5 check/AOT Unclassified rejections; run rejects3 reachable callable-value cases and correctly defers2unused bad bodies. Diagnostic trace shows inferred0 at tcCheckValue positions arg/return/block-result, not one proven violation. Three positive programs pass9modes with expected ORC stdout; raw native compatibility(0,0)/(999,998) remains Ok(Unresolved), proving broad Source promotion unsound. Source paths identify3 repair domains: callable declaration value admission(3), numeric literal under rigid result context(1, validExpr0), rejected operator selection lost before result typing(1). Preserve namespace qualifiers/static globals and local closure priority; literals obey existing builtin numeric context; operator diagnostics require actual canonical selection origin. Related completed met-g2x4 explicitly excludes these residuals. Canonical phase3-value-inference-refusal-investigation.json retains actual reports/source locations. Independent review and exact child assignment remain before investigation closure; no product source has changed.

## Investigation closure

Investigated at compiler9be1f948 with adopted d2 and unchanged product sources. Actual diagnostic snapshot probe confirms named Fn target0, absent associated member identity, existing Raw opaque refusal without Source event, and canonical Add missing-callee sentinel. Assigned repairs to met-eqw2, met-5lik and met-uqzw, all com-yeua dependencies. Independent neutral reviewer typing_obligation_plan_review verified actual evidence and all three assignment contracts; no mandatory gap. Close discovery only; implementation children, parent285 failures and phase3 remain open. Canonical evidence retains reports and limitations.
