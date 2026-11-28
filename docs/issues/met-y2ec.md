---
id: met-y2ec
status: in_progress
deps: []
links: []
created: 2026-11-28T00:18:18Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-wxn1
tags: [frontend, generics, verification]
---
# Preserve fixed receiver substitutions through call-pattern matching

## Contract and scope

Implement [simultaneous substitution and rigid patterns](../design/types-and-evidence.md).
Keep the original admitted call pattern and its fixed environment. Receiver,
impl, lexical Self and known method replacements belong to the caller; never
infer their children as unresolved callee binders. Argument ranking and contextual
result completion must use this same distinction and infer only remaining
callee-owned slots. This is a required child of met-wxn1, not deferred optional
optimization or a new language rule. met-wxn1 must wait for this repair.

## Evidence and cause

Meta remaining-consumer-checkpoint.json and diagnostic paths document the normal
provided expected-result repair. v27 passes all normal whole-check cases, but
Source fixture RecursiveProvidedExpectedResult.pw fails in its recursive call.
The same frozen native compiler with only its target closure explicitly typed
also refuses (recursive-provided-typed-control-v28), so result completion alone
cannot close this boundary. Preserve both tests and distinguish these evidenced
failures from unexecuted internal counterexamples.

Ranking currently substitutes receiver values into parameter patterns, then
starts the common matcher with zero argument slots. Contextual provided results
also embed fixed receiver values before constructing rigid boundaries. Both can
lose the distinction between a replacement's caller ParamId and an unresolved
callee ParamId from the same recursive declaration.

A small internal contrast must isolate the mechanism: original pattern
`(fixed: R, transform: fn(U) -> U)`, fixed R mapped to Array[caller U], unknown
callee U, expected `(fixed: Array[caller U], transform: fn(Bool) -> Bool)`.
The correct completion is callee U = Bool while the fixed replacement stays
unchanged. Execute this contrast before treating it as decisive RED.

## Implementation sequence and guarantees

1. Add small collision/noncollision/mismatch controls and confirm meaningful RED.
2. Retain original admitted patterns and explicit known receiver/impl/Self terms
   through prepared argument ranking. Reuse the existing structural matcher;
   do not add a second inference solver or recover meaning from spelling.
3. Use the same original-node boundary preparation for contextual results.
   Final parameter/result publication reads the selected completed signature,
   never a proposal or expected type. Remove competing pre-substitution paths.
4. Pass both recursive Source cases and current component22/normal whole-check
   controls. Check failed candidate substitutions do not leak into another
   candidate. Different ParamIds and mismatch refusals remain distinct.
5. Independent source/evidence review and same-source cost assessment. Do not
   add unconditional boundary allocation/construction to ordinary empty-context
   calls. Parent final CLI/gen/formal/whole gates remain required.

Excluded: new generic language semantics, query caching, met-2yhf Missing/
Ambiguous classification, backend/ABI changes and unrestricted solver expansion.

## Review and completion

Independent scope review confirms this is one finite shared boundary, suitable
as a child blocking met-wxn1. Required actions and tests above cover ranking,
expected-result completion and final use, not just a table or verifier assertion.
Normal v27 success is not completion evidence for the recursive cases. Keep this
issue open until executed controls and independent review prove the contract.

## Starting RED

ProvidedResultBoundaryMain builds an actual generic provided placement whose
receiver is Wrap[caller U], retains its original selected proof, and asks the
Direct result-completion API for an independent Bool method result. v29 reaches
the targeted assertion "provided receiver replacement was re-inferred as a
method binder" with native -6; compilation/link succeed and inputs are unchanged.
This isolates expected-result rigidity from the earlier Source ranking refusal.
The expected fixed field is explicitly the selected receiver, not a type inferred
from the implementation pattern. Extend with mismatch/noncollision/candidate
isolation before completion; do not treat this single RED as full coverage.
