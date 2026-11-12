---
id: com-80t4
status: in_progress
deps: []
links: []
created: 2026-11-12T21:08:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Retain jointly inherited associated constraints in generic calls


## Contract and Reproduction

[Spec08](../../../spec/spec/02-type-system/08-traits.md#トレイトの継承supertrait)
defines supertraits as constraints on the same subject. The
[conformance-evidence contract](../design/types-and-evidence.md#5-conformance-evidence)
identifies instances by owner and positional arguments and treats associated
outputs as predicates on that instance.

```plew
trait Parent {
    type Key
    type Value
}
trait First: Parent[Key=I64] {}
trait Second: Parent[Value=Bool] {}
trait Service: First + Second {}

fn needs[T](value: T) -> I64 where T: Parent[Key=I64, Value=Bool] {
    return 7I64
}
fn forwarding[T](value: T) -> I64 where T: Service {
    return needs(value: value)
}
fn main() {}
```

The fixed compiler at `076646bc` rejects the body with ambiguous conformance.
The signature-refinement candidate `34a254d6` rejects with an unsatisfied
where clause. There is no trait signature projection or concrete conformance
in this reproduction. The shared proof selection in
`src/Codegen/Mono/Resolve.pw` compares the full requested predicate list
against each path independently; neither path alone provides both outputs.

## Guarantee and Completion

- One authored premise must supply all its compatible declared guarantees
  for the exact inherited instance. Preserve a proof path for every equation
  from where admission through saved call evidence, its validation, and final
  instantiation. A requested output cannot select an otherwise ambiguous
  concrete or trait-subject path.
- Cover the accepted conjunction in both supertrait orders and a concrete
  final call; preserve single-path and opaque-premise controls and reject
  absent, incompatible, and wrong-instance predicates. Preserve different
  roots, distinct concrete paths and explicit source selection.
- Reuse the signature controls and compare check, JIT, and native at their
  actual consumer. Record the retained prerequisites and independent review
  before closure. No general solver, syntax, or signature-owner migration is
  part of this issue.

## Requirement and Interface Consumer

Independent review of candidate `34a254d6` reproduced the same rejection when calling this requirement through
`any Service`. The diagnostic points to the requirement's where clause:

```plew
fn get() -> Self#Parent.Key where Self: Parent[Key=I64, Value=Bool]
```

A concrete `Worker` implementing `Parent`, `First`, `Second`, and
`Service`, followed by `val service: any Service = <Worker />` and an
`I64` read of `service.get()`, is the final-consumer control. Removing
the requirement's where clause exercises the successful signature path
in `inherited_associated_complementary_paths`. This is an actual
prerequisite for [com-30u1](com-30u1.md), including signature validation
and interface/provided replay through the shared proof repair.

## Retained predicate checkpoint

The selected inherited proof supplies the instance and its local output
facts. When another output is needed from the same premise, acquisition
records the exact associated projection and the declared path that proves
its equation. Saved-plan comparison reads that equation by canonical
receiver, owner and positional arguments with the same declaration root.
Direct authored premises and executable witnesses retain their original
output authority. Preferred-path lookup limits which sibling can supply
the requested equation.

Fixed carrier `34a254d6` rejects both
`generic_joint_supertrait_constraints` and
`interface_joint_supertrait_constraints`. Candidate `1a0e89e7` passed
check, JIT and native for both, including a provided method under reverse
supertrait order, and for six inherited-signature controls. Nine targeted
negative controls preserved their diagnostics, including the new
`generic_joint_supertrait_constraints_excluded_path` and existing opaque,
conflicting, wrong-instance, and competing concrete-path controls.
An explicit `#Service` that includes both branches still checks successfully.

Standard build `20261112T211727-build-73997a` and generation
`20261112T212101-gen-599d84` passed. Same-source medians were
6.799868 s and 6.817552 s, with identical LLVM across all eight runs.
