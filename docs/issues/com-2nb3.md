---
id: com-2nb3
status: closed
deps: []
links: []
created: 2026-11-02T21:46:43Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reject discovered import cycles before recursive surface queries

## Contract and audit evidence

Closed com-d57o historical parser spellings/F2 and com-vrvl JIT F3 are not this defect; new finite source-admission task.

Origin: [com-6lza](com-6lza.md), [finite source/Syntax intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json), unit `IMPORT-CYCLE-ADMISSION`.

## Scope and guarantee

- Frontend discover imports/reexports→first recursive Lower/trait/type surface lookup and checkImports→detectImportCycles order

## Scenarios

- Reciprocal same-selector public reexport cycle/source refusal; bare cycle without selector recursion.
- Acyclic chain/diamond/repeated import/alias and missing public selector controls.

## Excluded

- No import/cache subsystem rewrite or timeout extension.

Static discoverable cyclic selector path can recurse before cycle diagnostic; no executed current source hang claimed.

## Completion and adoption

Exact producer→retention→required consumer, meaningful defect-specific RED/positive/refusal/boundary/noninterference controls, original failure preserved, legitimate prefixes retained, applicable gates and independent review. Do not infer authorization for an undecided syntax/panic/CLI policy from this assignment. Preserve original error and legitimate published prefixes; make no rollback/recovery promise beyond the actual API contract.

Required admission proposal: {"phase": "source-admission-before-G1-and-integration", "receivers": ["com-61jt", "com-604k"], "reason": "Actual source use DAG admission; new defect outside closed historical F2 controls. Direct source G1 prerequisite, not reopen com-d57o or expand JIT F3."}. Actual accepted edges are recorded in the audit adoption evidence after cycle review.

## Retain the Cycle for the Diagnostic

Independent review of com-9hde fixture migration exposed a current
spec/15 violation on 241b58b6. All of namespace_import_cycle,
namespace_reexport_cycle, and namespace_self_import_cycle exit 1 and
show "module use graph contains a cycle (spec/15)" without identifying
the modules in the ring. The first two source rings are First → Second
→ First. The last is Main → Main. Main is only an entry prefix in the
first two. The issue is observable in check, AOT, and lazy.

ModuleScopeBindings.finishModule detects the back edge before surface
recursion, but ScopeBindingFailure.ImportCycle retains only the use
offset. Frontend's later Visibility.detectImportCycles implementation
has path reconstruction. Restore the full structured ring at the early
producer and render it once using canonical module identities, excluding
noncycle prefixes and preserving the primary location and Source domain.
Keep one cycle authority and reconcile/remove the redundant late walk
after proving it supplies no additional valid guarantees. Add a RED
test for the ring itself before changing the producer. Cover ordinary,
public re-export, self-loop and acyclic cases in the affected modes.

## Executed Cycle Ring Repair

The early binding DFS now retains the suffix of its active path and the
closing node. The diagnostic adapter renders that sequence using source
module paths. The old late DFS is removed. The removed import-edge walk
used the same successful file import path that already records binding
origins, including namespace imports with no selective names.

The registered command-line diagnostic test fails all nine cycle checks
on 241b58b6 and passes all nine on a diagnostic rebuild. It checks that
the reported sequence is one closed ring of exactly the expected modules;
the entry prefix in the two-file cases is excluded. Three acyclic
module controls pass. The private Source receipt is preserved on all
nine corrected invocations. [Original fixed-point RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/module-cycle-ring-red.json).

Independent implementation review confirmed that every edge in the old
walk has a binding origin, and that gen and ORC reach the early admission
boundary. The old edge table remains available for direct visibility.
The expanded diagnostic test covers five cycle shapes in check, AOT and
lazy, including named imports and reciprocal same-selector re-exports.
It reports 15 failures on 241b58b6 and passes on the 593906c6 diagnostic
candidate with all acyclic controls. The focused builder fixture confirms
the closing offset and exact ring survive repeated finish and attempted
registration after failure.

## Outcome

Completed at c65002f2 after independent closure review. The exact builder
payload passes its golden in JIT and native. Four existing acyclic JIT
goldens cover namespaces, aliases and repeated reachability through two
paths; a missing export still rejects with its own reason. The registered
ring test and the focused producer test cover separate consumer and
retention guarantees. Phase-wide validation remains with G2a/G2b.
