---
id: com-fyxe
status: in_progress
deps: [com-m0bf]
links: []
created: 2026-10-24T02:30:52Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Use the selected complete signature for associated literal context

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
parent criteria 1, 2, 3, 4, 8. This is the finite Check/Literal-associated-function
entry family, distinct from stamping synthetic carrier types and body keys.

Entry: `Check/Literal::checkAssocArgsLitCtxFromExpected`/`checkLitSpanCtx`;
`Resolve/ExprType::associatedReceiverFromArguments`/`groundFinalMethodParameter`;
callers in `Check/Call`, `Check/Generic`, `Verify/Stmt`, `Resolve/Record`.

## Finite Actions

1. Separate a still-uncommitted source probe from a call with a saved selected
   signature. For saved calls use the selected declaration, complete receiver
   pattern, explicit binder map and parameter context. Do not run findAssoc/
   inferFnArgs again from a head name or map ctx.args[i] to f.typeParams[i].
2. Supply permitted literal context through existing argument/context APIs while
   preserving committed literal/type facts. For preselection construction use
   the existing complete receiver matcher and isolated candidate environment;
   no second callable solver, new backward inference or later-argument guessing.
3. Retire the paired postselection AST/name replay and positional receiver/binder
   shortcut. Follow resulting terms into the saved signature, both worklists and
   final call consumers. Do not weaken literal range/width or ownership checks.

## Exit and Controls

Trace every caller as preselection or saved-call consumer and record removed
sites. Cover factory/associated calls with fixed/reordered/nested receiver
patterns, method-owned binders, aliases and same-spelling foreign nominal types,
exact numeric widths and conflicts in direct/block/if wrappers. Preserve default
forwarders and source evaluation order. Reuse `generic_constructor_field_width`,
`requirement_method_parameter_identity`, `source_static_signature_evidence` and
existing contextual constructor rejects; add targeted missing-fact/cross-owner
controls where the migrated boundary needs them. Pin fresh source/carrier/input
hashes, actual execution/rejection receipts and independent completion review.
General defaults/conformance-solver redesign is outside scope. Final G2 gates
remain mandatory.
