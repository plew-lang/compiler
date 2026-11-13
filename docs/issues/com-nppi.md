---
id: com-nppi
status: closed
deps: []
links: []
created: 2026-11-13T21:39:46Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Use retained associated equalities for lexical callable parameter types


## Contract

A callable body reads its parameter type using the exact authored signature
slot and its admitted lexical equalities. A projection with a known
right-hand type supports the same operations as that type. A projection
whose output is still abstract exposes only the operations justified by
its declared bounds. Keep declaration-time checking independent of any
eventual concrete conformer. See [Generics, section 2](../design/generics.md#2-abstract-checking-is-not-template-acceptance).

## Reproduction and suspected boundary

On `42980da6` and `98a78601`, check and JIT reject the call to `item.get()`
with a missing-bound method diagnostic for both a bare and a viewed
associated output:

```text
trait Output { type Item }
struct Counter {}
impl Counter { fn get() -> I64 { return 42I64 } }
fn read[T](owner: T, item: T#Output.Item) -> I64 where T: Output[Item=Counter] {
    return item.get()
}
```

Binding `val projected: T#Output.Item = item` from a parameter annotated
directly as `Counter` instead allows `projected.get()`. Reproduced through
a concrete `Producer` in meta scratch
`tmp/com-3jtd/projected-extension/where{,-bare,-local,-local-bare}.pw`.
Viewed and bare local controls print their respective goldens in JIT.
`lexicalBodyParameterType` exits early for a generic declaration before
using the admitted signature recipe. By contrast, local annotation
admission replays the exact retained equations to publish its source term.
Confirm the first loss in Record and the verifier's shared parameter
reader, then follow the parameter term into the selected call and Mid.

## Completion

Use matching viewed and bare projected parameters and equivalent local
annotations with distinguishable method outputs. Preserve symbolic
generic parameters with no output equality, reject a missing proof and a
foreign/mismatched equality, and retain two distinct parameter slots.
Verify check (including an unused generic body), JIT, and linked native
against a fresh carrier. Obtain independent review before closure.
Reuse the exact retained equations and authored slot IDs. Do not widen
specification, resolve by matching type spellings, consult a runtime
instance to admit the abstract body, or bypass the declaration verifier.
This repair supplies the parameter producer used by
[com-3jtd](com-3jtd.md); that task owns forwarding the selected RHS
extension evidence into candidate lookup.

## Candidate verification

The retained lexical parameter reader validates the authored slot and
replays its saved equations in the abstract receiver environment. It
does not query a concrete generic instantiation. An output with no
usable equation stays symbolic. Closed signatures continue through the
concrete recipe reader.

`lexical_projected_parameter_equalities` rejects at the method call under
`98a78601` in check/JIT. Fixed-input build
`20261113T214140-build-ad7752` produced `180bd891`. The fixture passes
check including its unused generic body, JIT, and linked native
(`49/1`). Nine positive fixtures passed check/JIT, and the diagnostics
of three existing missing or wrong-instance controls matched the precursor
in both modes. The bare projected-parameter scratch control also passes
check. Closure requires an independent review of this candidate.

## Outcome

Resolved in `0d05ff1f`. Independent review confirmed exact slot ownership,
shared Record/Verify consumption and no new conformance search. The
reviewer's test-strength finding was addressed in `ae6c1a65`: swapping
both parameter slots changes the expected `427/1`. The reviewer replayed
precursor RED and candidate check/JIT/native GREEN on that final fixture.
Additional controls preserved symbolic bounded success, missing/foreign
equality and missing-proof rejection, and accepted inherited equality,
provided-method lexical Self and a structurally nested Array output.
The projection-only validation cost was bounded, and same-source medians
were 7.762 s and 7.688 s with the same LLVM in all eight runs.
Standard generation passed 25 accepts and 5 rejects with fixed inputs
(`20261113T214557-gen-74e7cf`).

The adjacent chain `U: Output[Item=Counter], T: Output[Item=U#Output.Item]`
does not yet give either a local annotation or a parameter access to
`Counter.get`. That upstream equation admission case is recorded in
[com-3jtd](com-3jtd.md#chained-lexical-associated-equality).
