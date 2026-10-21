# Plew Compiler Design

> Make responsibilities and the ownership of decision logic explicit, so contributors can identify where a change belongs and understand its impact from the design documentation. Prevent ad hoc implementations and duplicated decision logic, reducing hard-to-fix bugs and open-ended architectural rework.

This reference describes the adopted architecture and the contracts that implementation should satisfy. It is not a claim that every contract is implemented. Chapters distinguish design, unresolved decisions, and audited implementation scope.

The [Plew language specification](https://github.com/plew-lang/spec/blob/main/SPEC.md) owns language semantics. This reference owns how the compiler realizes those semantics. Operational instructions, validation baselines, and current work remain in their existing documents; implementation gaps belong in [local issues](../issues/README.md).

## Available Chapters

1. [Architecture and Design Principles](architecture.md)
2. [Compiler State, Identity, and Computation](compiler-state.md)
3. [Sources, Packages, and Modules](sources-and-modules.md)
4. [Syntax and Semantic Input](syntax.md)
5. [Declarations, Scopes, and Name Lookup](name-lookup.md)
6. [Types and Semantic Evidence](types-and-evidence.md)
7. [Expression and Body Checking](body-checking.md)
8. [Generics and Body Instantiation](generics.md)
9. [Metaprogramming and Generated Code](metaprogramming.md)
10. [Mid Representation and Lowering](mid.md)
11. [Ownership, Access, and Lifetimes](ownership-and-access.md)
12. [Passes and Optimization](passes-and-optimization.md)
13. [Representation and ABI](representation-and-abi.md)
14. [LLVM Backend](llvm-backend.md)
15. [Runtime](runtime.md)
16. [Driver and Demand-Driven Execution](driver-and-execution.md)
17. [Diagnostics](diagnostics.md)
18. [Verification and Validation](verification.md)

All 18 chapters have been reviewed, the adopted language rules are synchronized
with the specification, and the design/editorial review findings have been
resolved. First-edition confirmation with the user remains a separate milestone
under the [maintenance policy](maintenance.md#first-edition-and-implementation-restart).
Implementation status and pinned audit evidence belong in the linked issues;
the chapter list is not a second implementation-progress ledger.

## Detailed Contracts and Decisions

- [Standard Library Boundaries](standard-library.md) assigns declaration ownership, public package routes, private runtime handoffs and representative channel APIs without expanding implicit names.

- [Checked-body Storage and Implementation Restart](checked-body-storage.md) defines the adopted owner-local storage/API, alternatives, measurement criteria and the gate before paused compiler work resumes.
- [Frontend Handoffs and Admission](frontend-handoffs.md) refines saved semantic facts, publication and final-consumer admission.
- [Declaration and Execution Audit](declaration-and-execution-audit.md) retains declaration obligations and scoped demand-execution audit details.
- [Mid Operation Details and Execution-Entry Audit](mid-entry-audit.md) retains operation-level invariants and the scoped entry/probe map.
- [Collections and the Safe Buffer Floor](collections-and-buffer.md) refines the runtime, ownership and representation contracts for safe collection storage.
- [Explicit Divergence](decisions/divergence.md) retains the adopted completion policy and rejected alternatives.
- [Hot Restart](decisions/hot-restart.md) separates the approved future host direction from current one-shot execution and historical feasibility evidence.

## Reading and Maintenance

[Detailed implementation conformance audit](../issues/com-nsxb.md) records pinned
source-to-consumer traces, evidenced gaps, preserved conforming paths and explicit
unverified combinations. Its completion does not certify compiler implementation.

The [review follow-up issues](../issues/met-ukm5.md#outcome-and-next-boundary)
record each resolution and its implementation boundary. Accepted comparisons
are incorporated into the owning chapters and retired under the maintenance
policy. Any future active proposal remains separate from this adopted reference
and the language specification.

[Maintenance policy](maintenance.md) defines writing, review, adoption, decision retention and the boundary between design completion and implementation completion.

Start with the architecture's responsibility map and follow the reading paths relevant to the change. Chapter boundaries describe conceptual ownership, not mandatory source modules.

A contract has one authoritative home. Overview diagrams introduce and link contracts; detailed chapters refine them. Code-level contracts should be connected to their implementation without duplicating independently maintained rules. Unimplemented adopted contracts remain documented as design, not asserted in source as existing guarantees.

For each chapter, record the implementation revision and scope actually inspected, what remains unverified, and related issues. An absent issue or passing test suite is not evidence of a complete architecture audit. Keep migration inventories and progress out of the design narrative.
