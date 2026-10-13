# Explicit Divergence Without a Public Bottom Type

**Decision:** Adopted in the language specification. This note retains rationale
and rejected alternatives; [Body Checking](../body-checking.md#4-blocks-branches-patterns-and-completion)
owns the compiler contract. Adoption does not certify implementation migration.

## Motivation and Choice

Plew favors an explicit callable contract, no privileged uninhabited type, and a
concise way to express termination. It retains `diverge fn` alongside ordinary
empty enums such as Infallible. The overlap is accepted as a consequence of those
priorities, not because unification is logically impossible or separation is an
independent goal. A general empty match follows exhaustiveness/completion rules;
calling an ordinary function returning an empty enum does not implicitly diverge.

No public Never or expected-type bottom coercion is introduced. A wholly
source-diverging expression cannot directly initialize, assign, supply an
argument/operand, or provide a give/return/break value. Branch aggregation can
omit a value from a branch that transfers elsewhere. Thus an if with one yield
and one return can produce a value, but a block containing only return cannot.
This is a clarity policy, not an indispensable safety property. Wrapping any
expression with give is deliberately not an acceptance-preserving operation.
Short-circuit operands have no special exception: write an explicit if for a
conditional return. A bare match arm and a block arm containing the same
nonreturning call both propagate divergence at the branch boundary.

Callable declarations are the boundary. A normal function declared to return T
may have a body that never returns, and calls still have its declared T contract.
A declared diverging call produces no value. A generic todo returning T can
therefore be used in a value position without making callers depend on body
inspection, inlining, or optimization. A normal function reaching its end without
a required value is a different error.

## Following Code and Static Typing

Explicit return/give/break/continue, declared diverging calls, and empty matches
prohibit following code in the affected source region. Escape targets remain
explicit: give exits its block, break its loop, return its function. Their outer
continuations are not thereby prohibited. Some branches escaping does not
prohibit continuation through another branch.

Analytically nonterminating loops warn rather than establish source divergence,
including a loop whose body returns. Source checking continues after that warning.
A warned give contributes to static result typing, but creates no actual reachable
CFG/ownership join. A return inside that warned region still prohibits its own
following statement. Do not weaken the error because the enclosing region was
already unreachable. Constant-condition optimization cannot change source
acceptance or turn one surviving branch into the source-level contract.

These examples are independent and assume suitable enclosing result contracts:

```plew
loop { return 0 }
next() // warning
```

```plew
val x: I64 = {
    loop {}
    give 1I64 // warning; participates in static result typing
}
```

```plew
loop { break { return 0 } } // error: the break value does not produce a value
```

Development-time early return/panic consequently requires removing or commenting
following code. That cost is accepted. Rejected following-code diagnostics cannot
supply a successful result from a later give. Additional error recovery is a
separate concern. [Zig's unreachable-code test](https://github.com/ziglang/zig/blob/master/test/cases/compile_errors/unreachable_code.zig)
is a precedent for rejecting statements after return, not adoption of all Zig
reachability rules.

## Function Values

Divergence belongs in anonymous-function and function-type contracts too. Creating,
copying, passing, or returning a diverging function value is an ordinary value
operation; invoking it has no normal result. A normal function returning such a
function value still returns normally. Generic type parameters may hold that
function type, but a call's absent result is not an inferred Never or Unit.

Neither direction of implicit conversion between a diverging function and an
ordinary function is allowed; even an ordinary Unit-returning type is different.
Use an explicit normal wrapper when its declared result contract is intended.
Body inspection or an expected type cannot promote a normal literal to diverge.
Diverging bodies reject normal return/fallthrough and explicit result types.
Capture, escape, unique, borrow and exclusivity rules still apply to accesses
before termination. Sendable removal preserves divergence under the ordinary
capability-erasure rule; its adopted modifier order and async/spawn restrictions
remain specification-owned. No C/FFI nonreturning contract is silently inferred.

## Alternatives and Consequences

- **Public Never:** improves generic/type unification, but is not adopted. Function
  types carry the needed callable contract without turning absence of a result
  into an ordinary value. No compile-time or runtime speed advantage is claimed.
- **Unify divergence with every empty enum:** possible without privileging a type
  name, but would infer termination from an implicit type property. Rejected in
  favor of declaration-visible behavior.
- **Remove both implicit inference and diverge:** would require empty-match
  elimination, such as matching a panic result, to communicate termination.
  Rejected for verbosity.
- **Permit divergence only when an expected type exists:** coherent, but rejected
  to keep direct value use explicit and uniform with unannotated initialization.
- **Allow arbitrary following code:** warning-only handling was considered, but
  explicit-transfer rejection removes ambiguity about an unreachable give's role.
  Analytical loop warnings remain deliberately separate.

[Rust RFC 1216](https://rust-lang.github.io/rfcs/1216-bang-type.html) motivates bang
type integration into generics. [Never fallback](https://doc.rust-lang.org/edition-guide/rust-2024/never-type-fallback.html)
is a separate inference policy, not an unavoidable consequence. Swift's
[SE-0102](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0102-noreturn-bottom-type.md)
replaces noreturn with an empty return type while distinguishing universal bottom
subtyping. These concerns can be decided separately. Plew intentionally differs
in direct value use, and does not claim the alternatives are unsound.

## Implementation Closure

One source-completion authority owns classification and sequential/branch
composition, preserving exit targets and diagnostic causes separately from CFG
reachability. Lookup/type compatibility/substitution/overload/aggregate/evidence
readers retain divergence inside function types; declaration divergence is not a
new overload key. Mid, LLVM and demand execution consume the selected callable
contract, never rediscover it from AST shapes or function names.

Verify closure creation versus invocation, function contracts through fields,
generics and associated types, both conversion rejections and explicit wrappers,
capture/access before termination, nested escape targets, branch arms, warning
regions with type errors, and check/build/run parity. This is an implementation
completion requirement, not evidence of a newly run test or completed migration.

The [migration issue](../../issues/com-tijs.md) owns current completion conditions and affected-test follow-up; the meta worklog owns the paused candidate and implementation restart prerequisites.
