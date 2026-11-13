---
id: com-6p30
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Retain global annotation and initializer view evidence by declaration

## Guarantee and Finite Work

Admit supported global type annotations at declaration preparation and initializer-owned annotations/value views at the existing initializer request boundary. Retain exact global declaration identity and its lexical evidence into saved initializer facts and final use.

A canonical no-function initializer scope is legitimate but is not authority for every global sharing a synthetic function sentinel. Preserve existing initialization dependency/order rules and lazy/whole-check behavior; do not add a new initialization model. Nominal field/payload types and defaults remain separate.

## Required Scenarios

- Two globals with identical terms but different origins, ordinary and nested viewed types, missing/wrong-instance evidence and source-site diagnostic.
- Valid no-function empty premise scope, foreign body/initializer evidence refusal, failure restoration and no double initializer evaluation.
- Requested versus whole-check initializer behavior and actual saved global/type/operation consumers in build/native/lazy.
- Missing saved initializer facts cannot become success through a shared sentinel, cache or ambient declaration.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First fixed-candidate regressions

Candidate `f14e6539` has three separate positive fixtures. Local
counterparts of all three print 42 in lazy execution.

- `global_projected_view_annotation`: a projected argument in the
  annotation, with a directly matching concrete view as initializer.
  Whole check accepts; lazy and native compilation fail in Mid
  preparation.
- `global_initializer_projected_local_view`: a typed local and value
  view inside a top-level initializer block. Check, lazy and native
  compilation reject the exact trait instance inside the block.
- `global_initializer_projected_value_view`: a directly viewed global
  initializer with a projected positional argument. All three
  front doors reject the exact trait instance at the expression.

Keep the top-level initializer execution plan unchanged. Trace the
declaration annotation and each initializer-owned recipe separately
through preparation and final storage or operation consumers.

## Initializer recipe increment

Global lowering registers a scope keyed by its declaration target.
Annotations in the initializer and positional value-view arguments use
the body phase of that scope. Admission resolves it from the actual
initializer or closure owner, checks occurrence identity and reuses the
authored recipe reader with an empty lexical premise set. A
parameterized global value view without its authored arguments now
fails as Internal before it can use unadmitted terms.

Fixed-input build `20261113T071546-build-a25f98` produced `d5b64a4f`.
The two initializer fixtures now pass check, JIT and native with
output 42. Changing the projected output to Bool still rejects in check
and JIT at the view site. Existing global forward references and
global authored signature calls preserve their JIT outputs. The
global declaration annotation fixture still passes check but fails
Mid preparation. Its declaration proof and storage handoff are the
next increment.

## Declaration annotations and Mid storage

Admit each global declaration's root annotation before recording
initializers. Its exact retained recipe supplies the initializer's
expected type and forward references to the global. The initializer
publishes the checked binding under its own declaration target. Mid
builds the initializer's storage boundary and destination from that
binding instead of the raw declaration term.

Fixed-input build `20261113T072222-build-03006a` produced `39d67842`.
All three regression fixtures and both global forward-reference and
authored-signature controls pass check, JIT and native execution
with their expected output. `global_projected_view_distinct_declarations`
uses the same annotated term on two globals and reads the first from
the second's initializer. The prior candidate reports a Mid failure.
The new candidate prints 42 and 43 during initialization and once each
from main in JIT and native execution. This tests dependency ordering,
distinct values and one execution of each initializer.

Remaining: test missing and foreign annotations and initializer
facts independently, verify the request and compatibility boundaries,
run the targeted suites and comparison, and obtain independent review.

Candidate `39d67842` also passed standard generation
`20261113T072811-gen-155438` and all 47 lazy CLI cases. The native
same-type foreign annotation probe rejects as Internal on initial
request and retry, preserves the cursor, and leaves the sibling usable.
Same-source alternating development medians over three measured runs
after one warm-up were 7.120 s for `f14e6539` and 7.148 s for `39d67842`.
All eight runs emitted identical LLVM (SHA-256 `e1f6015fc88b`).

## Scope and binding fault checks

Review found that deleting only the root annotation ID after
declaration admission still let Record reuse the raw type. The native
probe on `39d67842` aborts with "missing global annotation accepted".
The scope guard requires the exact declaration before opening an
initializer. Record requires the annotation ID for an explicitly
typed global, and Mid reads the storage binding through its
session/reader/target/owner identity. Build
`20261113T073356-build-28969e` produced `d20eb1cc`. The same probe
rejects twice as Internal, restores the caller cursor and leaves the
sibling usable. Five check/JIT controls and the distinct-declaration
native control pass.

The independent reviewer reproduced closure-local projected recipes,
nested arrays, mutable assignment, and direct projected member use in
check/JIT/native. Pre-existing direct global closure invocation
still fails Mid verification on both carriers. Startup dependency
omissions reproduce on both and belong to [com-fkxl](com-fkxl.md).
The [probe inputs](../../../evidence/rejection-domains/diagnostic-domain-implementation/global-annotation-ownership/README.md)
also preserve the remaining request RED. Preliminary initializer
recording rejects the wrong view during declaration registration.
The repair must preserve unannotated forward-reference typing and
keep final generic uniqueness checking. Exact occurrence substitution
within one owner and loss of published initializer evidence still need
their own controls.
