---
id: com-px0e
status: in_progress
deps: []
links: []
created: 2026-10-24T13:22:40Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-9tau
tags: [frontend, generics, verification]
---
# Normalize selected callable field and local types before source publication

## Boundary and Evidence

Required E3 repair, independently bounded by /root/body_receiver_completion_review
to about1–2 active human days. At production856d661c / fresh carrier4fd8210c,
original diverging_callable_storage panic source fails source selection. A normal
associated callable fails the same way. Direct explicit field reaches Mid instead.
Meta phase3e-callable-boundary-before.json preserves exact hashes and results.

## Action

Mono/Scan.fieldTypeRefOfReceiver supplies recordDynamicMethodCall, but its nominal
branch returns substitution-only groundUnderInst and then raw projection fails
isFnType. Normalize this selected field result through existing canonical
projection grounding before callers record its type/signature. Preserve receiver
declaration binder precedence, ambient nonshadowed binders and open generic terms;
source context does not impose final concrete closedness. Structural field and
associated local callable adapters must consume the same canonical authority.
Save selected fieldIndex/bindingDeclStart and fnTypeTerm in the existing template.
Do not change isFnType, rescan source in Mono/Mid, or normalize in LLVM.

## Exit

Original associated field invocation reaches its actual downstream call boundary;
associated normal local/field and generic receiver controls execute, lexical binder
shadow controls and unbounded noncallable rejection remain correct. Raw unknown
parameter does not become callable through instantiation. Pair with com-o7ul for
end-to-end original panic success; no isolated source success certifies E3. Fresh
sourcecheck, fixed point, formal median below7s and independent completion review
are required. E3/G1/E4 retain explicit dependencies.
