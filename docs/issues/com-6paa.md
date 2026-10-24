---
id: com-6paa
status: open
deps: [com-m0bf, com-nqjd, com-fyxe]
links: []
created: 2026-10-24T02:29:50Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve declared receiver identity through final body keys

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
parent criteria 2, 3, 8. This owns registered body receiver production and its
paired key/closedness readers, after other late nominal producers are migrated.

Entry: `Mono/Call::canonicalBodyReceiverRef`, `selectedCallableSubstitution`,
`internBodyInstance`,
`sameBodyRuntimeRef`, `finalStaticCalleeIsComplete`;
`Resolve/Record::parametricSelfRef`; `Mono/FreeFn::registerMethodInst`;
`Mono/Resolve::tyRefIsGround`; `Mono/Ground::assocItemRef`, `setSelfItemEnv`, `setSelfItemEnvForBody`,
`collectDeclarationTypes`, `groundTermInEnvironment`, `groundTermForBody`,
`typeTermSameHead`, `typeTermRefSameHead` and paired legacy bare-name substitutions.

## Finite Actions

1. Migrate declaration and final-body Self environment construction together
   (`collectDeclarationTypes` must not pass through an unowned receiver merely
   because recvInstRef is zero). Retain selected associated Item evidence.
   Use the selected function's complete declared receiver and explicit
   instantiation environment when no instance receiver was supplied, including
   selectedCallableSubstitution rather than recreating f.recvTy from its name. Preserve
   ParamId and nominal owner while removing only the caller's outer views and
   reapplying the selected declaration's own view. Trait-subject/provided copies
   must use retained evidence, not pretend that a trait name is a concrete type.
2. Carry that receiver through body interning, stored signatures, final callee
   descriptors and Mid/backend instance lookup. A supplied receiver and the
   equivalent receiver obtained from the declaration must canonicalize to one
   key; unrelated same-spelled declarations must remain distinct.
3. After nqjd producer closure, retire the paired spelling/whole-program
   parameter-name fallbacks for published semantic nominal types. Keep valid
   primitive/structural/rigid terms explicit. Do not remove every legacy helper
   indiscriminately or merge same-layout distinct owners. No new body-key format
   or runtime ABI is required.

## Exit and Controls

The C3 internal diagnostic currently prints known.hasDecl=1, canonical.hasDecl=0,
then matches the unstamped receiver against two distinct nominal owners (1,1).
Turn it into a regression with proper registered declarations and assert
complete receiver/owner, same-owner key reuse and distinct-owner key separation.
Cover source alias/same-name modules, ordinary/generic/associated/extension and
provided receivers, explicit/synthesized receiver input, and final signature
missing/foreign identity controls. Reuse `mid_type_recipe_instances`,
`mid_unique_type_identity` and existing source owner/static signature controls.
Fresh scoped native/reject controls, exact removal/consumer locations, pinned
inputs and independent completion review required; final gates stay in G2.
