---
id: met-wxn1
status: in_progress
deps: [met-4dxy]
links: []
created: 2026-11-27T15:58:48Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [frontend, generics, diagnostics, verification]
---
# Retain inherited associated selections through source and instantiation

Contract: spec08 inherited associated-member uniqueness and docs/design/types-and-evidence.md#associated-member-selection. Read parent met-o5z0 before work. No new source semantics or main/seed/carrier promotion. Preserve candidate identity separately from conformance evidence paths. TDD and independent final review are required; parent certification remains separate.

Consume the common query for both TypeAst/SyntaxType short and explicit projections and trait lexical associated names. Remove declaration-local traitOwnerHasAssocId prefilters in cachedValue/cachedSyntaxProjectionSource and competing candidate selection in chooseShortProjectionSource/lowerLexicalAssociatedType. Preserve ProjectionBoundState readiness, scope and demand timing rather than blindly preparing every unrelated bound.

Publish canonical actual declaring owner/complete arguments/member together with the authored root selector and justified inheritance/substitution recipe. Changed parent arity requires derived argument recipes, not reusing the child argument count. The original Child view must be admitted independently: T:Parent does not justify T#Child.Output merely because normalization produces T#Parent.Output. Keep same-name modules, aliases and original source positions.

Follow that selection through Source type admission, declaration/body facts, generic instantiation and actual AOT/ORC execution. Audit Lower/TypeRecipes, Check/AuthoredTypes, Mono/Resolve assocBindingFor and selected proof output readers. Concrete witness output access is legitimate; fresh member-name/source selection is not. Preserve the original root's conformance path and no late canonical-term mutation to repair missing publication. Remove replaced decision paths.

Guarantees must run end to end, including qualified/short/lexical forms, parameterized/arity-changing inheritance, diamonds, ambiguous/equal-output cases, missing Child view proof, same-name modules and unused body controls. Do not close from saved fields or added invariants alone. If split further, retain this complete producer-to-final-consumer guarantee at this owner.




## Producer-to-consumer implementation sequence

The inherited language matrix is already RED on fixed149aac (39 cases,27 target
mismatches); do not replace it with service-only outcomes. Query unit A is closed.

1. Inspect the two TypeAst/Syntax projection adapters and lexical-self projection
   adapter together with Source recipes/admission. LoweredTypeProjection currently
   has only one source and argument-recipe list: it cannot represent both the
   authored Child proof and substituted Parent output when their arities differ.
   Add the explicit saved selection/provenance at that handoff before changing
   canonical term ownership; do not reconstruct it from an interned term later.
2. Replace chooseShortProjectionSource and direct-member prefilters with the
   common query over admitted matching roots/equation context. Retain bound
   readiness and original declaration scope; avoid eager unrelated clause loading.
3. Derive Parent argument recipes from retained substitution edges, preserve the
   authored Child receiver/view recipes and admission obligations, and consume
   saved selection through AuthoredTypes, facts, Mono and witness output readers.
4. Run qualified/short/lexical and changed-arity accepts through AOT/ORC and
   generic instantiation; NoChildProof must still reject at the authored view.
   Audit/remove competing source/member selection and review the whole B chain.

This is an execution sequence within the existing task, not a relaxation of its
final-consumer completion boundary. Missing/Ambiguous owned transport belongs C.


## Source handoff design and native RED

`InheritedSelectionMain.pw` drives analyzeFrontendForRequests on Inherited.pw
and then requires the parameter's published projection to name declaring Parent.
Frozen native `inherited-source-selection-red-v2` builds/links successfully and
fails specifically with the old direct-member rejection for T#Child.Output.
Meta `inherited-source-selection-red.json` records actual status/input hashes;
the initial v1 unwrap panic is not relied upon to classify the cause.

Use one append-only Comp selection record, referenced by an opaque draft token
on PType and then explicitly bound once to its immutable source occurrence.
Keep the full Missing/Unique/Ambiguous query outcome, authored roots/argument
recipes, and derived declaring-instance recipes. A token is not Source proof.
Binding validates session-local term/site/scope/recipe association, not ambient
cursor or reverse lookup from a canonical interned term. Avoid copying the query
graph at each handoff; SourceTypeUses may retain a token without depending on
Frontend-specific graph types.

The independent API review found this consistent with authoredChildren-to-recipe
handoff and identified required implementation boundaries:
- Canonical child recipes match Parent term children; Child argument provenance
  belongs on a separate edge, including changed parent arity.
- Authored Child admission and declaring-member evidence have distinct fields;
  a single AuthoredTypeViewProof.selector cannot mean both.
- Lexical/nested receiver creation via loweredProjectionReceiverRecipe also
  records occurrences and must carry the token, not only the two main wrappers.
- Query outcome never establishes conformance. Final readers consume the saved
  identity and justified derivation; no late selection or token-based authority.

This design remains within the adopted contract. Final implementation and
producer-to-final-consumer certification are not yet complete.


## Saved-query implementation checkpoint (not B completion)

PType now carries a selection draft token. TypeAst/Syntax wrappers and lexical
receiver occurrence creation explicitly bind it once to the exact source use.
The append-only Comp record retains query graph/outcome, original argument
recipes, session/site/scope/member and term identity. Reads check the source
recipe/occurrence and original complete root; different terms/sessions and
rebinding fail Internal, never Source. A query result is not a conformance proof.

Native source-selection-retention.json succeeds through actual Source admission,
checks authored Child root and declaring Parent candidate/edge, duplicate-bind
rejection and foreign-term/session rejection, then reuses the valid record.
The original publication test remains RED at its Parent identity assertion
(source-selection-publication-wip.json): Source admission now succeeds, but the
canonical term is still Child. Thus the authored Child proof requirement remains
intact at this checkpoint; no Parent publication/final-consumer claim is made.
Missing/Ambiguous owned refusal and remaining legacy selection paths are also
unfinished. Continue with separate original-root proof and declaring-instance
recipe/publication; do not merely rewrite the canonical owner and drop Child.


## Readiness and lexical retention checkpoint

Bare lexical early returns in both adapters and the nested lexical receiver
record now use captureLoweredLexicalSelection with the original Child/Self root.
The record separates publishedInstance/publishedArguments from authored root
recipes; Parent canonical publication must still preserve the latter.

Required equation owners are collected from explicit root terms and reached
header edge terms. Relevant non-Ready premises go through the existing
preparedProjectionBound state machine. Head-only identity lookup is separate
from consuming Failed/Lowering; no unrelated Failed may propagate before the
owner dependency check. Empty contexts/dependency sets return without walking
unrelated clauses. Further dependency qualification by receiver must be checked
before certifying the complete source-scope guarantee: same-owner bounds on a
different binder must not cause artificial recursive preparation. Use the
existing pending subject matching/binder contracts, not name equality.

Finite native evidence in meta projection-members includes lexical/nested RED
and GREEN, required Failed/Lowering preservation, irrelevant same-state control,
and a real Unlowered Key equation reached while lowering an earlier Container
bound's projected argument (old Source rejects, new Source accepts). The initial
normal EquationScope input already passed and is a GREEN control, not RED.
Setup failures are excluded. Final-source noninterference controls and source
re-review are retained separately from the earlier checkpoint results.

Independent incremental review confirmed the saved-root/published-instance
separation and dependency traversal direction. It found two concrete gaps:
state consumption before owner filtering and nested lexical default-root
capture. Both have specific REDs and source fixes; re-review confirms those
paths are removed. This is not B completion: remaining work is receiver-sensitive
readiness where needed, canonical declaring-instance publication/derived recipes,
separate authored-root and declaring evidence, competing selection removal and
final consumer/AOT/ORC certification. Owned refusal remains C.
