---
id: com-yjq0
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
# Admit requested body and closure type views through saved final facts

## Guarantee and Finite Work

Attach local type annotations and value-view occurrences to the actual requested lexical body/closure owner, including ordinary, method/provided and deinit bodies. Apply common exact-instance admission at that owner's source check, then retain proof/type facts into instantiated body operations and final consumers.

An unused enclosing signature is not permission to eagerly check its body. Do not use a shared synthetic body, ambient caller cursor, another closure's readiness or type-term identity as source authority. Globals and default generators have separate siblings; no new closure/unique feature is included.

## Required Scenarios

- Valid and missing/unrelated/wrong-instance premises for local annotation and value view, with nested constructors and actual use.
- Same-spelled foreign binders, sibling closures/provided bodies, caller-callee environment separation and failure/retry restoration.
- Lazy unrequested body versus whole-check/requested body, supported build/lazy/gen entry paths, and real final saved type/proof consumption.
- Declaration-only acceptance must not be confused with successful body admission; missing saved facts cannot trigger a new source lookup.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First reproduction and work boundary

Candidate `plewc-com-ab7u-final` (`381d515a`, product `428ce8ca`)
rejects the following before starting `main` in both `--check` and
`--run`:

```plew
use @Std/Io only { print }
trait Marker {}
fn unused() {
    val number = 42I64
    val value: I64#Marker = number
}
fn main() {
    print("main")
}
```

Replacing the annotation with `val value = number#Marker` preserves the
whole-target rejection and allows lazy `main` to print `main`. The
annotation failure comes from `verifyProgram(includeBodies: false)`
calling `checkTypeViewSources`, which scans every interned TypeRef.
Lowering records an authored type use under a body role but both local
statement adapters keep only its TypeRef in the statement. Interned
type identity cannot distinguish a declaration from an unrequested
local or closure occurrence.

The new `local-view-unused` case in `tests/tooling/test-lazy-cli.py`
fails on the frozen baseline with the diagnostic above. The preceding
whole-target check and build controls both reject for conformance.

Start with a paired local annotation fixture for declaration-only,
whole-target and requested-body checking. Trace which remaining
consumers require the exact local annotation and remove their
dependence on the global scan as that authority moves to lexical body
preparation. Then trace the closure, provided/deinit and concrete
consumers against the same owner contract. Keep type-view source
formation distinct from discovering or publishing executable bodies.

## Request timing increment

Lowering now retains authored occurrence IDs in the existing block and
expression type-use lists. Declaration verification reads its own list;
body recording checks only the block and expression lists reached by its
request. This removes the scan across interned type terms and avoids
resolving a selected view head twice within a single check.

Build `20261113T031508-build-6c50d3` passed with immutable inputs.
Candidate `plewc-com-yjq0-request-timing` (`5590955d`) passed the lazy
CLI suite, including the new unused/requested/check/build controls, and
checked the compiler's own source. A valid locally annotated generic
view with a matching bound also printed `42` under JIT.

Generation `20261113T032010-gen-986660` passed. In a same-source
alternating comparison, the medians were 6.902333 s before and
6.821464 s after the timing change (three measured runs per carrier).

## Exact instance for body annotations without projections

The frozen baseline and request-timing
candidate both accept `val values: Array[I64#Marker[I64]] = []` when
the sole conformance is `I64 as Marker[Bool]`. The current head check
compares trait owner and arity without checking positional arguments.
The new rejection fixture confirmed this RED.

Requested non-projection annotations now require the same exact
instance query as authored signatures, with assumptions from the
lexical declaration. Build `20261113T032208-build-d6ed26` passed.
Candidate `plewc-com-yjq0-exact-local` (`f540d3b5`) rejects the RED
input in check, build and run. The lazy CLI suite passes, and both a
concrete and a generic view with a matching bound print `42`.

Projection recipes, value views, owner-scoped proof publication and
final readers still need migration. Mid already reads sealed local
binding types. Mono's `scanLocalDeclarationType` grounds that binding
through the general term reader, and its statement walk also scans the
raw annotation. Both consumers need to take their input from the
admitted occurrence under the same body owner. The common formation
audit outside this body lifecycle remains under [com-3jtd](com-3jtd.md).
