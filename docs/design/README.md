# Plew Compiler Design

> Make responsibilities and the ownership of decision logic explicit, so contributors can identify where a change belongs and understand its impact from the design documentation. Prevent ad hoc implementations and duplicated decision logic, reducing hard-to-fix bugs and open-ended architectural rework.

This reference describes the adopted architecture and the contracts that implementation should satisfy. It is not a claim that every contract is implemented. Chapters distinguish design, unresolved decisions, and audited implementation scope.

The [Plew language specification](https://github.com/plew-lang/spec/blob/main/SPEC.md) owns language semantics. This reference owns how the compiler realizes those semantics. Operational instructions, validation baselines, and current work remain in their existing documents; implementation gaps belong in [local issues](../issues/README.md).

## Available Chapters

1. [Architecture and Design Principles](architecture.md) — reviewed draft.
2. [Compiler State, Identity, and Computation](compiler-state.md) — reviewed draft; owner-local checked-body storage is adopted; implementation remains pending.
3. [Sources, Packages, and Modules](sources-and-modules.md) — reviewed draft.
4. [Syntax and Semantic Input](syntax.md) — reviewed draft.
5. [Declarations, Scopes, and Name Lookup](name-lookup.md) — reviewed draft.
6. [Types and Semantic Evidence](types-and-evidence.md) — reviewed draft.
7. [Expression and Body Checking](body-checking.md) — reviewed draft; physical storage is specified; implementation remains pending.
8. [Generics and Body Instantiation](generics.md) — reviewed draft.
9. [Metaprogramming and Generated Code](metaprogramming.md) — reviewed draft; host-unit/output/recorded-input contracts are specified, while their implementation and coverage remain unaudited.
10. [Mid Representation and Lowering](mid.md) — reviewed draft; upstream storage implementation remains pending.
11. [Ownership, Access, and Lifetimes](ownership-and-access.md) — reviewed draft; whole-program enforcement coverage remains to be audited.
12. [Passes and Optimization](passes-and-optimization.md) — reviewed draft; unique-copy input preservation needs implementation audit.
13. [Representation and ABI](representation-and-abi.md) — reviewed draft; callback and external runtime boundaries remain open.

14. [LLVM Backend](llvm-backend.md) — reviewed draft; ORC DataLayout admission remains an implementation discrepancy.

15. [Runtime](runtime.md) — reviewed draft; general concurrency and reusable embedding remain outside the audited subset.

16. [Driver and Demand-Driven Execution](driver-and-execution.md) — reviewed draft; reusable embedding and full command parity remain unaudited.

17. [Diagnostics](diagnostics.md) — reviewed draft; richer provenance and complete returning-service migration remain unaudited.

18. [Verification and Validation](verification.md) — reviewed draft; evidence scope remains distinct from implementation completeness.

All planned chapters have reviewed drafts, and the initial cross-chapter review corrections are incorporated. Prior contracts, rationale, implementation gaps and scoped evidence have been consolidated into their authoritative homes and independently checked against the original records. The final cross-domain finding is addressed by the adopted [static initialization plan](driver-and-execution.md#static-initialization-plan), with its language change and bounded execution guarantee recorded in [F1](../issues/com-7knz.md#f1--p1-synchronous-reads-during-asynchronous-global-initialization). First-edition confirmation with the user remains required.

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

[Maintenance policy](maintenance.md) defines writing, review, adoption, decision retention and the boundary between design completion and implementation completion.

Start with the architecture's responsibility map and follow the reading paths relevant to the change. Chapter boundaries describe conceptual ownership, not mandatory source modules.

A contract has one authoritative home. Overview diagrams introduce and link contracts; detailed chapters refine them. Code-level contracts should be connected to their implementation without duplicating independently maintained rules. Unimplemented adopted contracts remain documented as design, not asserted in source as existing guarantees.

For each chapter, record the implementation revision and scope actually inspected, what remains unverified, and related issues. An absent issue or passing test suite is not evidence of a complete architecture audit. Keep migration inventories and progress out of the design narrative.
