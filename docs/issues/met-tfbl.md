---
id: met-tfbl
status: open
deps: []
links: [met-g53w, com-cwu1]
created: 2026-10-26T05:22:49Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, diagnostics, verification]
---
# Audit lexical call binding, candidate fallback and diagnostic isolation

## Purpose and Boundary

Investigate the complete lexical call-binding and visibility decision chain
before choosing a repair. The user suspects several exposed design defects:
incorrect binding priority, premature failure instead of completing permitted
candidate lookup, and inaccessible-name diagnostics interfering with semantics.
Treat these as distinct hypotheses, not as already proven root causes.

This is a finite phase-three investigation (about 1–2 human working days), not
permission to redesign every name-resolution subsystem or implement new language
features. It must end with an evidence-backed responsibility map and concrete
bounded repairs/dispositions. Investigation closure alone cannot close the
underlying defect, met-g53w, B1, the source-selection area or G1.

## Confirmed Failure and Evidence

At compiler b5df0276, the following valid input rejects inside std/Lang.pw:91:

```plew
use @Std/Io only { print }

fn fallback(value: I64) -> I64 { return value }

fn main() {
    val value: Optional[I64] = <.None />
    print(value.unwrapOr(
        fallback: fn() -> I64 { return 5I64 }
    ))
}
```

The lazy standard method has a parameter `fallback: fn() -> T`; its `fallback()`
must invoke that parameter. The unrelated app declaration makes the visibility
checker report an unimported function in another module. Here external means an
ordinary function in another module, not C/FFI. Old carrier23f7 and newe6ff both
reproduce --check exit1. The checkpoint retains exact source, commands, binary
hashes and diagnostics; no wrong runtime dispatch or unintended visibility grant
has been established by this rejecting input.

[Immutable source/probe receipt](https://github.com/plew-lang/meta/blob/81cf8f1e/evidence/existing-feature-conformance/source-owner-facts/overload-structural-checkpoint.json).
Old carrier: bin/plewc-dynamic-argument-admission SHA256
23f7d582501b394f3390fbd9e2ebd577cc9892cf6c7de4d5129b70ae5f14b583.
New carrier: bin/plewc-overload-structural-shared SHA256
e6ff9d19d8501b32422f7c7bc1c8e0a8fc189105015fef6d67bc00347cdf0a6d.

Independent architecture review classified the live Check/Visibility decision
as outside closed com-cwu1's dynamic argument admission and com-qb05's finite
Verify/Call name-rescan repair. A similar responsibility defect remains at a
different stage. Do not reopen com-cwu1 or treat its earlier evidence as coverage
of this new boundary.

## Canonical Contracts

- [Lookup responsibilities and binding results](../design/name-lookup.md#3-scope-inputs-and-binding-results): local/parameter binding identity, visible candidate sets and diagnostic-only excluded-name search are different results. A name index or visibility helper must not become a competing selector.
- [Free-function surfaces](../design/name-lookup.md#4-free-functions-and-public-surfaces): visible module declarations and imported public overloads form one set, without preference by source origin. A private suggestion cannot hide a visible applicable candidate.
- [Frontend handoffs](../design/frontend-handoffs.md): body requests check call visibility/defaults in their lexical environment; later consumers retain the selected source operation and original provenance.
- Read spec03/04/15 for lexical shadowing, callable forms, per-declaration visibility, use aliases/republication and root/part scope. Do not infer Plew rules solely from existing helper behavior.

Distinguish no binding from an existing binding that is noncallable or has wrong
arguments. Do not silently invent fallback past a shadowing binding, or priority
between imported and module-local free overloads. Establish the required result
from spec/design for each case; seek a user decision if the existing contract is
insufficient. The user's concern about fallback is an investigation requirement,
not blanket authorization to bypass an inapplicable higher-priority binding.

## Investigation Actions

1. Map the actual producer-to-reader chain: scope/binding construction, binding
   kind, lexical owner, visible candidate collection, applicability, source
   selection/publication, visibility/import validation, diagnostic rendering and
   concrete final consumption. For each decision record its owner, inputs,
   returned success/failure category, saved identity and downstream readers.
2. Trace the reproducer in detail. Begin with Resolve/Lexical.pw,
   Resolve/Record.pw::recordFreeCallExpression / recordExpr,
   Resolve/Expr.pw::resolvedCallee, Resolve/Module.pw::visibleFreeFunctions /
   findFunc / firstVisibleFuncByName / firstFuncByName / labelMatchOnlyInvisible,
   Check/Visibility.pw::checkExpressionVisibility / checkUseVisibility, and their
   actual callers. Explain why the current precheck runs before local call
   classification. Do not assume the function resolver itself prefers a free
   function merely because a prior visibility checker rejects the expression.
3. Inventory every use of unrestricted same-name lookup on these paths, including
   diagnostic helpers and cached indexes. Separate legitimate declaration/index
   navigation from semantic selection and provenance checks. Verify whether a
   helper chooses a target, suppresses a candidate, emits a terminal error or
   only adds optional explanatory text. Follow equivalent type/namespace checks
   when they share this failure mechanism; do not expand to unrelated algorithms.
4. Exercise lexical parameters/locals, captured bindings and global callable
   values against module declarations, flat imports, aliases and namespaces.
   Include multiple loaded modules with same-named public/private declarations,
   visible overloads, nested shadowing and differing labels/types. Distinguish
   no binding, noncallable binding, no selector match, no type match, ambiguity,
   inaccessible declaration and unavailable builtin service. Record observed
   versus required outcomes, not just whether compilation exits nonzero.
5. Test semantic isolation: add/remove/rename an unreachable same-named declaration
   in an otherwise unrelated loaded module, reverse relevant declaration/import
   traversal order, and vary wrapping/owner where permitted. Such changes must
   not alter a resolved lexical call or the visible candidate set. Intentional
   changes to actual imports/public candidates remain legitimate semantic inputs.
6. Contrast --check, native build/execution and lazy run at their applicable body
   request boundaries; inspect generation, default/provided bodies and copied
   source origins where the same checks execute. Unrequested-body omission is
   intentional; do not eagerly scan all bodies to make the test uniform.
7. Evaluate the out-of-scope search/hint path independently. The user permits
   deleting the hint feature. Prefer removing it if isolating it is unnecessary
   complexity; retaining a hint requires proof that it runs only after genuine
   lookup failure and cannot alter acceptance, chosen binding/candidates,
   inference, visibility rights or execution. Do not mistake the current terminal
   error enforcement for an already isolated optional hint. Deleting it must not
   remove required rejection of actual inaccessible or nonambient functions.
8. Produce the responsibility-level repair plan. Include competing selectors,
   incomplete failure categories, spelling-based identity recovery, ambient
   cursor dependencies and ownerless whole-AST scans if observed. Do not restrict
   the fix to fallback, std, one syntax shape, or skipping visibility for closures.
   Preserve correct paths; no duplicated resolver or late-name fallback.

## Completion and Handoff

- Save bounded executable contrasts with exact carrier/source/std/module hashes,
  actual commands/results and required outcomes. Preserve this repro and positive
  controls plus genuine missing-use/private/ambiguous/wrong-argument controls.
- Report one end-to-end authority/reader map and explicit findings: confirmed
  defects, justified behavior, uninspected boundaries and any genuinely missing
  specification decision. Do not claim all possible scoping defects exist.
- Assign each confirmed gap to an existing correctly scoped task or a new finite
  repair with concrete producer/removal/consumer actions and regression matrix.
  Attach real dependencies before investigation closure. If a correction exceeds
  the finite scope, split it rather than leaving an open-ended implementation.
- For each proposed helper removal, show how legitimate enforcement survives.
  A passing reproducer or removal of diagnostic text is not design completion.
- Obtain independent review of the investigation and task decomposition before
  closing this task. Repairs then need their own actual execution/mode validation
  and independent completion review; final G1/G2a/G2b/G3 remain mandatory.

The separately observed generic-requirement existential-boxing failure remains
recorded in met-g53w; it is not silently bundled into this lexical/visibility audit.
This ticket's creation authorizes investigation planning, not a language change or
an already accepted implementation. No compiler source or test expectation is
changed by registering this task.
