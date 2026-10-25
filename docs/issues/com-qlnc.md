---
id: com-qlnc
status: open
deps: []
links: []
created: 2026-10-25T14:02:11Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, documentation]
---
# Specify shared concrete-argument overload admission

## Boundary and Decision

Canonical specification/design update prerequisite for [met-g53w](met-g53w.md).
The user selected the independently reviewed concrete-argument rule and requested
this task before implementation. The three-reviewer synthesis and edge cases
are retained in [the implementation task](met-g53w.md#review-of-the-selected-contract-change).
The current written equal-generic-shape restriction has not yet been replaced.

For ordinary type overloads in the same declaration-conflict domain and selector,
every pair of callable forms must have at least one corresponding argument
position with semantically distinct types independent of unresolved type
parameters. Generic arity and other generic parameter positions need not match.
Different ordered labels are different selectors, not type overloads.

## Finite Work

1. Update spec/02-type-system/07-methods-impl.md to remove the blanket generic
   shape restriction and state the pairwise rule. Align related examples and
   explanations in functions/defaults, factories, traits, generics and operators;
   search the spec for contradictory claims rather than only editing one section.
2. Define type independence and normalized semantic identity: method, enclosing
   nominal/impl/trait parameters, abstract Self and unresolved projections count
   as dependencies; already fixed Self/equalities can normalize to concrete
   types. Array[I64] can discriminate, Array[T] cannot. Do not add general
   constraint solving to manufacture a discriminator.
3. Cover omitted-default callable forms, three candidates distinguished at
   different pairwise positions, dependent-only rejection, and ambiguity at a
   call despite valid declarations. Preserve separate capability-conditioned
   groups, receiver/origin domains, and existing forward-inference rules.
   Type-argument count, return types and general where success do not become
   fallback discriminators or a new candidate priority.
4. Update docs/design/name-lookup.md and the relevant generics/frontend handoff
   contracts: one declaration-admission relation shared by free functions,
   methods, associated functions, factories and trait requirements; source
   selection retains the chosen declaration/requirement and binder environment
   through concrete and existential consumers. Distinguish declaration conflicts,
   call applicability and successful publication.
5. Reconcile met-g53w's implementation acceptance cases with the resulting
   canonical contracts. Record spec/compiler document revisions and obtain
   independent completion review of the documentation before closing this task.

## Completion and Exclusions

The spec and design agree on acceptance/rejection examples and the ownership of
each decision; old generic-shape claims and links are reconciled. The reviewed
decision is readable from the canonical documents without depending on chat.
Validate the documentation diff, local links and relevant contradictory wording.

This task changes documentation and implementation-task contracts only. It does
not implement overload resolution, alter compiler/test expectations, run builds
or claim fixed-point/performance/full-suite success. met-g53w remains open for
implementation and producer-to-final-consumer verification after this prerequisite.

