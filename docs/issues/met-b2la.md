---
id: met-b2la
status: open
deps: [met-yotl]
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, ownership]
---
# Implement adopted unique generic capability contracts


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

The adopted spec06/08 capability contract admits copyable-only, unique-only and
allowunique binders, explicit autounique nominal types, capability-qualified
Self/associated types/candidate families, and two distinct existential types.
See [Generics](../design/generics.md#capability-discharge-and-witness-admission) and
[Types](../design/types-and-evidence.md#capability-and-conditional-selection-contracts).

The pinned Syntax `TypeParamListAst`, `SyntaxSig`, `SyntaxTrait` and their parsing/
materialization retain parameter names and sendable flags, without the adopted
copy-capability markers. [Lower/Decl](../../src/Codegen/Lower/Decl.pw)::lowerTypeParamBinds
also retains names/ParamIds/sendable only. [Check/Unique](../../src/Codegen/Check/Unique.pw)::checkGenericUniqueArgs
rejects unique arguments except the existing reference-cell exceptions.
[Lang](../../std/Lang.pw) still declares ordinary Optional/Result and opaque
Promise[T], rather than the adopted capability contracts. This is a missing
end-to-end feature family, not an assertion that ordinary generics do not work.

## Completion Boundary

The [R1/R2 design prerequisite](met-yotl.md) is resolved. Implement its single
fixed semantic expansion-depth limit and select the initial numeric constant
using ordinary/adversarial controls. Include finite-deep overflow, changing
projections, SCCs and cold/warm cache behavior. No infinity proof/detector,
additional budget dimensions or public override API is required by this design.

Carry capability declarations through pinned Syntax, semantic terms, checked
conditions, conformance/existential formation, instantiation, ownership and final
copy/drop. Preserve one chosen candidate family through ordinary calls and via.
Cover conditional deinit presence/absence and unchanged child cleanup, copyable
mode adaptation versus invalid explicit move, and unique Optional/Result/Promise
consumption. Do not relax the old unique-argument guard before the full ownership
contract is implemented. Ordinary deinit placement is separately owned by
[met-2t3l](met-2t3l.md). The existing [type-checking remediation](met-si6j.md)
is a foundation, not a promise to implement this entire new feature in its scope.
