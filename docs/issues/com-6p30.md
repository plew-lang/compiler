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
