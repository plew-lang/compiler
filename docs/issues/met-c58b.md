---
id: met-c58b
status: open
deps: []
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, driver, runtime]
---
# Implement effect-closed global initialization planning


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

Spec07/14/15 and the [static initialization plan](../design/driver-and-execution.md#static-initialization-plan)
require transitive execution effects and conservative static cycle rejection,
with async initializers started only after prerequisites are ready. Global reads
do not discover dependencies or wait; ordinary function recursion is distinct.

[Resolve/Global](../../src/Codegen/Resolve/Global.pw)::collectGlobalDeps walks direct
AST operands. A Call visits arguments, not its selected callee's effects; unhandled
block-bearing forms fall through without dependencies. globalDfs orders this
restricted graph; orderGlobalsByDependency also returns early for at most one
global. [Frontend](../../src/Frontend.pw) invokes this before later preparation.
[CheckedProgram](../../src/CheckedProgram.pw)::prepareInitializersInSession
prepares the combined global body; its existing access analysis is not the adopted
initializer-readiness/effect-closure plan. No runtime misordering was reproduced
by this audit; the missing dependency coverage is directly visible in source.

## Completion Boundary

Produce and retain closed execution summaries before constructing the initializer
DAG; include selected calls, defaults/conversions, actual closure invocation,
async continuations, worker work, known callbacks and implicit copy/drop/deinit.
Reject static dependency cycles including the single-root case; distinguish
function SCCs from initializer SCCs. Execute prerequisite-ready owners once, with
ordinary explicit awaits and no hidden global force/wait/event pumping. Verify
direct/indirect/conditional cycles, declaration-order reversals, drop effects and
AOT/JIT agreement. [com-8j0w](com-8j0w.md) retains other process/assoc questions.
