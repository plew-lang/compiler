---
id: com-fyxe
status: in_progress
deps: [com-m0bf, com-qbwg, com-i62n, com-uruz]
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

### Contextual Operand Recording Correction

5adff7cc source-checks successfully with its fresh candidate. The reordered
receiver and method-owned binder controls progress, but nested Array arguments
expose a missing saved expression term at source-constraint closure. Numeric
literals are not expressionNeedsTypeContext shapes; testing that predicate before
using the selected parameter skipped arrays containing only such literals.
The correction records every still-unresolved operand with the selected expected
term, rather than using a syntax-based contextual-shape gate. Completed terms
remain untouched. An incomplete user call now reports the established cannot
infer all type arguments diagnostic; corrupt explicit reader requests still
fail without reconstruction. A no-context associated call reject is added.

### Bare Generic Qualifier Identity

Fresh 36223da3 candidate4 passes all 19 focused native and 11 rejection cases
(no internal errors), plus the full compiler-source check. The new real-module
same-name alias fixture exposes the remaining preselection boundary: with no
complete receiver term, findAssoc admitted unrelated homonymous receiver owners
and could save the first label-only candidate. The alias had already identified
a declaration; missing type arguments do not make that identity unknown.

The paired local fix resolves that bare qualifier's owner once in its explicit
source domain, then filters candidate declared receivers by that owner alongside
the existing complete-receiver test. It does not append a partial nominal term,
select by expected result, change body keys, or add an inference solver. Internal
raw name-only clients with no declaration keep their existing probe behavior;
source qualifiers with a known owner cannot cross to another owner. Fresh
execution and final independent review of this increment remain pending.

### Alias Identity Projection

Fresh5 still rejects the right-side alias despite the owner predicate: the
qualifier adapter used aliasReal to return the use selector's source token,
which belongs to the importing module and is not itself an imported binding.
The source identity query must run on the original alias. assocRecvName now
projects that identity to the defining declaration's real name span using the
shared typeDeclName projection. It never treats an identity offset as a spelling.
concreteTypeQualifierTerm then queries that span in its defining module. This
preserves the owner into both the bare-head filter and concrete receiver path;
no postselection recovery or result matching weakening is introduced.

### Saved Source Closure and Planned Body Repair Handoff

14153136 fresh6 passes the compiler source check and focused-3 native19/reject11
with unchanged inputs. The real-module alias trace now records distinct callees,
complete receiver terms and exact reordered binders, and seals them successfully.
Its native finalization exposes the already planned com-6paa unowned body
receiver. The new explicit Pair[B,A] return variant proceeds through Concrete Mid
but fails physical type representation for the same registered receiver family.
These are retained failures, not successful evidence. The original Self variant
is permanent body_receiver_alias_identity. No further shape workaround is used.

Keep this task in_progress pending final native controls and final independent
review. Its source-side producer/reader repair is ready for com-6paa's planned
implementation prerequisite; that task now proceeds without declaring this
native exit complete or weakening the final parent gate.

## Completion Hold

39c3e27f fresh5 passes module alias controls4 but the required internal signature
authority fixture fails on the unassigned late Buffer producer. This task's
source-selection/parameter-context path remains statically coherent; no final
completion is claimed. The approved producer task [com-qbwg](com-qbwg.md) is now
an explicit completion prerequisite. After it closes, rerun this task's required
fresh controls and independent completion review; the task remains in_progress.
See [C3 classification reconciliation](com-m0bf.md#scope-stop-unassigned-late-synthetic-buffer-producer).

Buffer checkpoint ce98f5f4 fresh62a36bc4 now executes this task's context and
authority controls successfully; module4 also pass. Final certification remains
withheld: the required focused suite stops at optional_chain, a separately
unassigned pre-rewrite producer. See the current
[C3 stop](com-m0bf.md#scope-stop-unassigned-pre-rewrite-optional-chain-producer).
No newly required repair is silently included here.
The approved [com-i62n](com-i62n.md) now owns that producer as a required
completion prerequisite; rerun this task's own controls/review after the repair.


## Current Validation Hold: Custom-factory Source Receiver

Fresh2 on production **7aeda7d5**, fixture checkpoint **38b33f37**, passes full
compiler source checking and module4. The scoped runs retain their actual
successes but do not complete: string_interpolation exposes an ownerless Options
factory receiver already saved before body admission. The independent review
classifies a separate source/context producer, now assigned to
[com-uruz](com-uruz.md). This is not permission to widen this task or recover the
owner in final readers. See
[C3 scope stop and proposed allocation](com-m0bf.md#scope-stop-unassigned-custom-factory-source-receiver)
and meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-chain-factory-scope-stop.json. This task remains in_progress; final
completion review and G2 gates are still required.
