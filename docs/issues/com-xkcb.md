---
id: com-xkcb
status: open
deps: []
links: [com-9hny]
created: 2026-11-10T02:34:58Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, backend]
---
# Preserve function ownership modes through closure type identity and calls

Function-type ownership modes must survive finalized type identity and dynamic closure calls. The specification makes modes part of function type identity, but TypeRef currently has no mode vector; closure BodySignature preserves literal modes while dynamic calls construct Borrow-only passings. Baseline at edf4430b: Borrow construction/call succeed in lazy and eager modes; ordinary inout/move construction-only succeeds with --run, but calls fail and eager construction fails. Do not mistake successful lazy construction for supported invocation or silently prohibit it during backend refactoring.

Covered: preserve and verify mode identity from authored signature through type equality, call selection, BodySignature and Mid/LLVM consumption. Replace internal preparation errors on valid supported operations or correctly classify genuinely unsupported operations under existing contracts. Existing closure capture ownership and new source syntax are outside this task; consult before changing source semantics.

Evidence: ../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/closure-mode-baseline.json. Related W2 com-9hny migrates existing Borrow-call support without broadening modes; this gap is not automatically its dependency.

## Acceptance Criteria

Test distinct Borrow/Inout/Move function identities, literal-to-finalized-to-dynamic-call consistency, successful construction-only lazy controls, actual invocation and ownership/mutation controls across check/AOT/lazy. Establish target RED before product edits, remove competing mode reconstruction, obtain independent review. Do not claim fixes from source shape or declaration success alone.

