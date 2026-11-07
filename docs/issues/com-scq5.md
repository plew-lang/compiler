---
id: com-scq5
status: closed
deps: []
links: []
created: 2026-11-07T16:41:03Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, documentation]
---
# Clarify extension declaration and member publication contracts

## Adopted Contract

The user confirmed on 2026-11-08 that non-public extensions may contain public impls. This follows the existing visibility composition for non-public types; do not introduce a rejection or a new warning as part of this task.

- `pub extension Name { ... }` publishes the extension declaration name; an unmodified extension name is module-private.
- An impl inside the extension independently controls member visibility with `pub impl` versus unmodified `impl`.
- External use requires the extension binding and selected member to be accessible, together with ordinary receiver/type and package reachability requirements. Inner `pub impl` never publishes the extension name, and `pub use` never widens member visibility.
- Non-public extensions with public impls are valid. Public extensions with non-public impls keep those members module-private. Neither source loading nor receiver applicability grants a missing name binding.

## Documents and Guarantees

Update [spec09](../../../spec/spec/02-type-system/09-extensions.md) with explicit declaration syntax and the four extension/impl visibility combinations, [spec15](../../../spec/spec/04-execution/15-modules.md#公開と再公開) with publication/use/re-publication examples, and the existing public API closure references without changing their package-root applicability. Preserve [spec05](../../../spec/spec/02-type-system/05-structs-enums.md#メンバの可視性) and [macro role visibility](../../../spec/spec/04-execution/16-metaprogramming.md): this task does not prohibit public members of non-public owners.

Update [Name Lookup](../design/name-lookup.md#shared-module-binding-admission) to assign declaration publication to module binding/public-surface construction and member access to the selected member's visibility authority. Preserve canonical declaration provenance through selective use, alias, namespace and re-publication; downstream applicability cannot reselect an inaccessible source. Update [Syntax](../design/syntax.md) to preserve authored extension publication independently from each impl's publication through direct parsing, materialization/freezing and semantic input. Link existing source/module contracts rather than duplicate ownership rules.

## Acceptance and Boundary

Reconcile each visibility combination, external import/use, re-publication and package-root reachability with one consistent contract; include an example where non-public extension plus public impl remains accepted but cannot be imported externally. Check links and contradictory wording and obtain neutral independent document review. No compiler behavior, test expectation, package pin, seed or carrier is changed by completing this documentation task.

The product implementation is owned by [com-9hde](com-9hde.md), including shared Syntax public-wrapper support, retained extension visibility and module-publication consumers. Its existing kind/owner/legacy-path review repairs remain there. [met-bejv](met-bejv.md) owns the three existing fixture-purpose reconciliations after the publication and canonical binding paths are available. No new implementation owner or parallel visibility authority is created.



## Completion Record

Resolved as a documentation-only contract on 2026-11-08. spec09 now defines
the explicit syntax and four visibility combinations; spec15 connects normal
publication/re-publication; Name Lookup and Syntax assign separate retained
declaration/member facts and their consumers. Neutral independent review by
`extension_publication_contract_review` found no required correction or pending
surface decision. Its optional example-reachability clarification was adopted.
[Review record](../../../evidence/rejection-domains/diagnostic-domain-implementation/extension-publication-contract-review.json).
Local links and diff whitespace checks passed. This closes only documentation;
no compiler acceptance, GREEN, exact pin uptake or product completion is claimed.
