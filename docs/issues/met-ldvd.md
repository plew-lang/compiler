---
id: met-ldvd
status: in_progress
deps: [met-g9dh]
links: []
created: 2026-11-27T09:01:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [frontend, types, verification]
---
# Validate labelled function types through type admission

Apply the adopted non-absent-label uniqueness rule to function type construction and source type-use admission without introducing local binders or rejecting repeated unlabelled positions.


## Contract and implementation boundary

A function type has unique non-absent labels but no local binding group.
`fn(value: I64, value: I64) -> ()` is invalid; `fn(I64, I64) -> ()` is valid.
Use the shared label comparison contract from met-g9dh through actual type
construction/admission and retained type-use consumers. Do not infer a binding
name from an absent label, type identity0 or a display string.

Trace Syntax/legacy builders, source type uses, callable/closure signature
function-type construction and canonical type interning. Reject malformed
authored labels before successful type-use publication. Raw/synthetic terms
cannot obtain Source authority from matching labels or spans. Do not reopen
source inference or reinterpret associated/view evidence to diagnose duplicates.
Preserve ordered labels, contextual compatibility and existing completion/mode
contracts. A valid admitted callable signature can carry its already proved
label uniqueness; avoid rechecking it through every derived type consumer.

RED/GREEN against the fixed carrier: direct/nested annotated function types,
fields/parameters/results and source wrappers/associated type uses as applicable,
labelled duplicates versus repeated unlabelled positions, distinct legal labels,
ordinary/diverging function types and omitted-annotation closure contexts.
Exercise real type-admission/retained consumers plus Raw/foreign/malformed
controls; no verification weakening or same-text Source classification.
Focused tests and neutral review precede parent aggregate whole/fixed-point/
performance validation. No new function type feature or local shadowing rule.

## RED and implementation plan

Fixed final B (product97143377, frozen closure-parameter-build-v3) accepts all
84 new actual inputs. Expected32 legal successes pass;52 duplicate-label cases
are target RED. No setup or unrelated rejections. Cases cover local/imported
check/AOT/ORC, direct/nested/field/result/requirement/associated/diverging types,
used and unused body annotations, distinct/mixed labels and repeated bare types.
The unused body intentionally stays accepted in run while check/build must
reject; body demand is not moved to initial declaration scanning.
Receipt: meta declaration-parameters/function-type-red.json; reproducible manual
test-function-type-label-admission.py.

Actual producer map: Lower/Types.pw lowerType/lowerSyntaxType record authored
occurrences after Raw term construction; TypeRef.argLabels stores ordered name
IDs, slot0 is the result and label0 means absent. Syntax parser explicitly
records args=[return,parameters...] and parallel empty result label for ordinary
and diverging Fn types. Body frontiers are isolated by Lower expression/statement
use-array swaps. SourceTypeVisibility.checkSourceTypeUsesWithOrigin is the common
declaration/body type-use acceptance boundary, before checkedTypeUses insertion.
Canonical interning remains identity construction, not semantic acceptance.

Reviewed implementation direction, before product edits:

- Keep the shared byte/span comparison. Decode only non-absent parameter labels,
  retaining their original parameter-slot/position correspondence. Do not create
  local binders or infer names from typeID0, displays or missing labels.
- Bind original label spans to the occurrence and ordered canonical labels in
  private Lower metadata. Legacy TypeAst also has argLabelSpans (Materialize
  preserves them); use coherent available spans, not interned-name spans.
  Caller-built missing-span AST still enforces uniqueness with Raw/unpositioned
  diagnostics. Missing metadata never means skipped validation.
- Extract existing type occurrence ownership capture/matching (private Lower
  receipt, declaration sealed root/slot proof or body frontier/path) into shared
  SourceTypeUseFailureEvidence. Rename visibility-specific private origin/owner
  names to type-use names; visibility keeps its separate namespace decision.
  Evidence is obtained internally by the actual producer, not supplied by callers.
- A type-signature refusal/frame holds that shared evidence and its own conflict
  payload. It does not carry visibility's namespace data or reuse closure's Expr
  frame. Raw/body preparation remains Unclassified; owned interpretation consumes
  saved evidence without duplicate comparison, full graph walk or owner re-search.
- Check before checkedTypeUses success insertion. Do not reuse a failed term's
  owner across occurrences. Keep deferred body frontiers and existing gen policy.
  Already admitted callable-derived signatures retain their label guarantee.

Neutral planning review confirmed this is C's shared owner boundary, not an
unrelated visibility redesign. Internal visibility proof-inspection tests may
follow the extracted .evidence field while preserving their original mutation,
owner and slot assertions. Existing visibility controls must accompany the new
Raw/foreign/malformed/retained type-signature controls. Product edits and GREEN
are not yet claimed.
