---
id: met-b04w
status: open
deps: []
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [driver, runtime, backend]
---
# Implement managed worker pause coordination for lazy compilation


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

Spec15 and [Worker Demand Coordination](../design/driver-and-execution.md#worker-demand-coordination)
require a compiler-affine owner independent of application workers, request
coalescing, managed quiescence, native return/callback gates and complete
publication. A C call may continue outside managed execution; waiting for it to
return is not the pause protocol. Runtime meaning must remain common with AOT.

[CompilerCallbacks](../../src/CompilerCallbacks.pw)::plew_compiler_prepare_body
currently looks up a MutableRef session and synchronously calls lowerBody on the
requesting thread. [Native ORC](../../native/llvm_backend.cpp)'s source generator
invokes this bridge synchronously. Existing one-shot execution and session
registry solve the current single-application-thread lifetime, but no managed
participant registry/quiescence handshake/independent compiler service is present
in this inspected execution route. This is missing multi-worker support, not a
reproduced race in a worker feature which the compiler currently rejects.

## Completion Boundary

Close request ownership, ORC follower/coalescing behavior, all managed participants,
cooperative stops, native entry/departure races and compiler-required lock
restrictions through publication/failure/resumption. Test root-waits-worker and
C-waits-worker progress, retained Guard/access roots and termination. Introduce
this with worker support ([com-qzpm](com-qzpm.md)); do not duplicate runtimes or
turn reusable embedding/Hot Restart into this task's implicit scope.
