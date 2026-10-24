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

## Implementation Checkpoint

58fdf37a removes the associated literal helper's name reselection and positional
receiver-argument map. Fresh candidate phase3c-associated-context-1 was built by
20261024T033516-build-ef3316 (exit 0, unchanged inputs). The direct reordered
receiver control progressed beyond the old incorrect range rejection, but the
method-owned-binder case still lacked literal context. This is not closure.

Independent static review identified the paired mixed API: checkMethodArgs could
run resolvedCallee before reading saved selection, and
recordedDirectCallEnvironmentAt treated foreign callee/incomplete substitutions
as absent selection. The next source increment reads Direct/Static saved
signatures before any syntax query, shares static signature projection with
source constraint checking, rejects malformed selected substitutions, and
separates constructCallParameterEnvironment with an explicit selected-row guard.
A new internal control covers saved receiver use despite an unresolvable
qualifier, missing substitutions, cross-callee requests, forbidden construction
after selection, and a real unselected construction query. New sources pass the
old fixed carrier's full source check; fresh execution/review remain pending.

### Producer Completion Paired with the Reader

The 63aa7b4e fresh candidate passes compiler-source checking and reports the
method-binder loss as an incomplete saved substitution instead of falling back.
The next increment retains partial inferFnArgs results when an associated
receiver cannot yet close. Existing result-pattern matching can therefore fill
receiver binders without discarding a method binder learned from an explicit
argument. No new inference direction or candidate solver is introduced.

A transient SourceCallParameterState distinguishes unselected, non-applicable
dynamic/protocol families, incomplete static selection and a complete selected
signature. Record and literal validation project the same stored operation.
After result completion, Record supplies still-unresolved child expressions
with exact parameter context in their lexical scope; completed operands are
never reinterpreted, and a fast scan avoids signature/environment work for
already-complete operands. The validation reader rejects incomplete selections.
All source checks pass, but fresh execution and independent review are pending.
