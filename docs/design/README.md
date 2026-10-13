# Plew Compiler Design

> Make responsibilities and the ownership of decision logic explicit, so contributors can identify where a change belongs and understand its impact from the design documentation. Prevent ad hoc implementations and duplicated decision logic, reducing hard-to-fix bugs and open-ended architectural rework.

This reference describes the adopted architecture and the contracts that implementation should satisfy. It is not a claim that every contract is implemented. Chapters distinguish design, unresolved decisions, and audited implementation scope.

The [Plew language specification](https://github.com/plew-lang/spec/blob/main/SPEC.md) owns language semantics. This reference owns how the compiler realizes those semantics. Operational instructions, validation baselines, and current work remain in their existing documents; implementation gaps belong in local issues once issue management is established.

## Available Chapters

1. [Architecture and Design Principles](architecture.md) — first draft for review.
2. [Compiler State, Identity, and Computation](compiler-state.md) — reviewed draft; physical checked-body storage remains unresolved.
3. [Sources, Packages, and Modules](sources-and-modules.md) — reviewed draft.
4. [Syntax and Semantic Input](syntax.md) — reviewed draft.
5. [Declarations, Scopes, and Name Lookup](name-lookup.md) — reviewed draft.
6. [Types and Semantic Evidence](types-and-evidence.md) — reviewed draft.
7. [Expression and Body Checking](body-checking.md) — reviewed draft; physical storage remains unresolved.
8. [Generics and Body Instantiation](generics.md) — reviewed draft.
9. [Metaprogramming and Generated Code](metaprogramming.md) — reviewed draft; isolation/freshness/runner protocols remain open.
10. [Mid Representation and Lowering](mid.md) — reviewed draft; upstream checked-body storage remains unresolved.
11. [Ownership, Access, and Lifetimes](ownership-and-access.md) — reviewed draft; whole-program enforcement coverage remains to be audited.
12. [Passes and Optimization](passes-and-optimization.md) — reviewed draft; unique-copy input preservation needs implementation audit.

The remaining chapters are not yet written. They will cover ABI; LLVM; runtime; the driver and demand-driven execution; diagnostics; and verification. Their absence does not make the available chapters detailed specifications for those areas.

## Reading and Maintenance

Start with the architecture's responsibility map and follow the reading paths relevant to the change. Chapter boundaries describe conceptual ownership, not mandatory source modules.

A contract has one authoritative home. Overview diagrams introduce and link contracts; detailed chapters refine them. Code-level contracts should be connected to their implementation without duplicating independently maintained rules. Unimplemented adopted contracts remain documented as design, not asserted in source as existing guarantees.

For each chapter, record the implementation revision and scope actually inspected, what remains unverified, and related issues. An absent issue or passing test suite is not evidence of a complete architecture audit. Keep migration inventories and progress out of the design narrative.
