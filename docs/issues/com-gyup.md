---
id: com-gyup
status: closed
deps: []
links: []
created: 2026-10-13T01:09:56Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Reassess continuation-specific move-state joins

Resolved as bounded current-surface verification at compiler 2899ddad. The old
R10-O1 probes put a wholly source-diverging return block in a Boolean operand;
that form is now correctly rejected by the adopted value-position rule and must
not be restored as a positive test. The historical inputs remain in meta's
block-expression-tenth-review evidence, rather than defining current acceptance.

The replacement control conditional_move_continuations covers AND, OR,
condition-chain and loop contexts with a normal RHS path plus a consuming return
path. Its 12 executions consume each resource once, with dynamic String fields
also exercising cleanup. Check and AOT/golden pass. Companion rejection controls
cover a consuming normal RHS and a later use reached from break/continue, both
inside a short-circuit RHS and directly in a loop. All four reject in check with
the expected ownership diagnostic.

Verify's branch handling reads the shared completion contract and preserves live
continuations. DeclarationProgram's checked Mid ownership analysis validates
loop exits/backedges and diagnoses MoveUnavailable; the loop controls exercise
that real path rather than relying only on frontend move flags. No move analysis
or unreachable-code checking is disabled, and no new loop syntax is enabled.
Source completion, analytical reachability and ownership flow retain their
separate responsibilities. No new implementation defect was reproduced within
this bounded admitted scope, so no speculative ownership rewrite is required.

The exact carrier is bin/plewc-selected-callee-evidence-fixed, SHA256
ae0e81c4a820d7dedad39f717180f20875935aefe5d02f48e5a5d06554a0a897.
Scoped commands, fixture hashes and results are retained in meta/evidence/
existing-feature-conformance/source-owner-facts/continuation-ownership-audit.json.
The positive control is included in ASan's pre-optimization compiler ownership
manifest. Parent-wide final candidate
gates remain required; this investigation closure does not certify them.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**, investigated with current specification-valid controls.
