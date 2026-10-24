---
id: com-m3c6
status: in_progress
deps: [com-m0bf, com-nqjd, com-6paa, com-qbwg, com-s5k5]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Verify nominal facet batch publication remains one-way

## Boundary

Phase 3D / D4. **Bounded API/removal verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Ir/Types.pw`; `src/Codegen/Check/Visibility.pw`; `src/Codegen/Resolve/Record.pw`; `src/Frontend.pw`.

Reconcile finishTypeDeclarationResolution and its private mutation against C3 source nominal producers. Check the all-or-nothing validation of ordered unique row identities, permanent phase closure and legal later appends. Trace the completed declaration dependency into successful source-owner admission.

## Exit and Evidence

Existing type_declaration_publication plus focused invalid/duplicate batch, post-publication row/append and branch controls establish the current API boundary. No production per-row overwrite writer remains. Do not conflate semantic term publication with runtime nominal layout or reimplement the already adopted batch.

Existing starting controls: `type_declaration_publication`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Publication Reconciliation

Runtime production remains `c1b731bd`; no new facet resolver is introduced.

| Boundary | Actual authority / retained consumers |
|---|---|
| Initial declaration resolution | `Frontend` completes source/module/declaration registration before `resolveTypeDeclIdentities` constructs `ResolvedTypeDeclaration` rows in arena order. Qualified syntax-generated terms join this same initial batch; C3 producers retain selected declaration domains. |
| Atomic batch admission | `Arena.finishTypeDeclarationResolution` first rejects a completed phase, sentinel/out-of-range rows and non-increasing identities (including duplicates). It checks the entire batch before calling private `applyResolvedTypeDeclaration` for any row. |
| Parallel representations | Private application updates both `TypeRef` and pooled `TypeTerm` facets from the admitted values, preserving structural children, cached closedness/projection presence and name-index keys. No public per-row replacement API remains. |
| Permanent closure / later append | Successful publication sets private `typeDeclarationResolutionFinished` permanently. `registerType` may append complete construction/substitution terms later, but no later row can reopen the phase or modify issued declaration facets. C3 source producers, not this batch API, own complete late construction identity. |
| Source success dependency | `checkSourceTypingObligations` requires `typeDeclarationResolutionComplete` before owner publication, even if no expression happens to use a nominal member. Lexical/global/nested owner preparation all call this gate before sealing. `finishSourceFacts` retains the first failure or immutable successful payload. |
| Final reads | D1/D2 source readers and Mid admission consume the published complete terms/signatures. C3 receiver/body-key, associated-call and Buffer controls retain exact selected identity through concrete instances. This facet audit does not reopen runtime nominal layouts or claim all future term producers are supported. |

Controls retain invalid/duplicate batch, post-success and post-append rejection,
two-representation stability and independent branch coverage in
`type_declaration_publication`; the strengthened fixture also checks a reverse
ordered batch causes no partial writes. `source_declaration_dependency` contrasts
uncompleted versus completed declaration phases on the same valid source body,
and checks an already failed request cannot be blessed by later dependency
completion. `type_declaration_writer_private` guards the private mutation API.
Existing closedness/projection/name-index/unification and C3 nominal controls
exercise preserved metadata and downstream identity.

## Required Raw-storage Repair

Independent review found public mutable `typeTerms` and8 child pools bypass the
otherwise closed batch. Do not claim this whole API closed before
[com-s5k5](com-s5k5.md) passes. Its finite allocation was independently approved,
and D4/G1 depend on it. The before control `type_term_rows_private` was accepted
(exit0) by the c1b731bd fixed compiler/source, a decisive privacy failure. The
new source dependency fixture's earlier body-zero setup failure is separate;
after reserving block zero it passes both negative and positive source paths.
