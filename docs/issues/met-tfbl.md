---
id: met-tfbl
status: in_progress
deps: []
links: [met-g53w, com-cwu1, com-jno0]
created: 2026-10-26T05:22:49Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, diagnostics, verification]
---
# Audit lexical call binding, candidate fallback and diagnostic isolation

## Purpose and Boundary

Investigate the complete lexical call-binding and visibility decision chain
before choosing a repair. The user suspects several exposed design defects:
incorrect binding priority, premature failure instead of completing permitted
candidate lookup, and inaccessible-name diagnostics interfering with semantics.
Treat these as distinct hypotheses, not as already proven root causes.

This is a finite phase-three investigation (about 1–2 human working days), not
permission to redesign every name-resolution subsystem or implement new language
features. It must end with an evidence-backed responsibility map and concrete
bounded repairs/dispositions. Investigation closure alone cannot close the
underlying defect, met-g53w, B1, the source-selection area or G1.

## Confirmed Failure and Evidence

At compiler b5df0276, the following valid input rejects inside std/Lang.pw:91:

```plew
use @Std/Io only { print }

fn fallback(value: I64) -> I64 { return value }

fn main() {
    val value: Optional[I64] = <.None />
    print(value.unwrapOr(
        fallback: fn() -> I64 { return 5I64 }
    ))
}
```

The lazy standard method has a parameter `fallback: fn() -> T`; its `fallback()`
must invoke that parameter. The unrelated app declaration makes the visibility
checker report an unimported function in another module. Here external means an
ordinary function in another module, not C/FFI. Old carrier23f7 and newe6ff both
reproduce --check exit1. The checkpoint retains exact source, commands, binary
hashes and diagnostics; no wrong runtime dispatch or unintended visibility grant
has been established by this rejecting input.

[Immutable source/probe receipt](https://github.com/plew-lang/meta/blob/81cf8f1e/evidence/existing-feature-conformance/source-owner-facts/overload-structural-checkpoint.json).
Old carrier: bin/plewc-dynamic-argument-admission SHA256
23f7d582501b394f3390fbd9e2ebd577cc9892cf6c7de4d5129b70ae5f14b583.
New carrier: bin/plewc-overload-structural-shared SHA256
e6ff9d19d8501b32422f7c7bc1c8e0a8fc189105015fef6d67bc00347cdf0a6d.

Independent architecture review classified the live Check/Visibility decision
as outside closed com-cwu1's dynamic argument admission and com-qb05's finite
Verify/Call name-rescan repair. A similar responsibility defect remains at a
different stage. Do not reopen com-cwu1 or treat its earlier evidence as coverage
of this new boundary.

## Canonical Contracts

- [Lookup responsibilities and binding results](../design/name-lookup.md#3-scope-inputs-and-binding-results): local/parameter binding identity, visible candidate sets and diagnostic-only excluded-name search are different results. A name index or visibility helper must not become a competing selector.
- [Free-function surfaces](../design/name-lookup.md#4-free-functions-and-public-surfaces): visible module declarations and imported public overloads form one set, without preference by source origin. A private suggestion cannot hide a visible applicable candidate.
- [Frontend handoffs](../design/frontend-handoffs.md): body requests check call visibility/defaults in their lexical environment; later consumers retain the selected source operation and original provenance.
- Read spec03/04/15 for lexical shadowing, callable forms, per-declaration visibility, use aliases/republication and root/part scope. Do not infer Plew rules solely from existing helper behavior.

Distinguish no binding from an existing binding that is noncallable or has wrong
arguments. Do not silently invent fallback past a shadowing binding, or priority
between imported and module-local free overloads. Establish the required result
from spec/design for each case; seek a user decision if the existing contract is
insufficient. The user's concern about fallback is an investigation requirement,
not blanket authorization to bypass an inapplicable higher-priority binding.

## Investigation Actions

1. Map the actual producer-to-reader chain: scope/binding construction, binding
   kind, lexical owner, visible candidate collection, applicability, source
   selection/publication, visibility/import validation, diagnostic rendering and
   concrete final consumption. For each decision record its owner, inputs,
   returned success/failure category, saved identity and downstream readers.
2. Trace the reproducer in detail. Begin with Resolve/Lexical.pw,
   Resolve/Record.pw::recordFreeCallExpression / recordExpr,
   Resolve/Expr.pw::resolvedCallee, Resolve/Module.pw::visibleFreeFunctions /
   findFunc / firstVisibleFuncByName / firstFuncByName / labelMatchOnlyInvisible,
   Check/Visibility.pw::checkExpressionVisibility / checkUseVisibility, and their
   actual callers. Explain why the current precheck runs before local call
   classification. Do not assume the function resolver itself prefers a free
   function merely because a prior visibility checker rejects the expression.
3. Inventory every use of unrestricted same-name lookup on these paths, including
   diagnostic helpers and cached indexes. Separate legitimate declaration/index
   navigation from semantic selection and provenance checks. Verify whether a
   helper chooses a target, suppresses a candidate, emits a terminal error or
   only adds optional explanatory text. Follow equivalent type/namespace checks
   when they share this failure mechanism; do not expand to unrelated algorithms.
4. Exercise lexical parameters/locals, captured bindings and global callable
   values against module declarations, flat imports, aliases and namespaces.
   Include multiple loaded modules with same-named public/private declarations,
   visible overloads, nested shadowing and differing labels/types. Distinguish
   no binding, noncallable binding, no selector match, no type match, ambiguity,
   inaccessible declaration and unavailable builtin service. Record observed
   versus required outcomes, not just whether compilation exits nonzero.
5. Test semantic isolation: add/remove/rename an unreachable same-named declaration
   in an otherwise unrelated loaded module, reverse relevant declaration/import
   traversal order, and vary wrapping/owner where permitted. Such changes must
   not alter a resolved lexical call or the visible candidate set. Intentional
   changes to actual imports/public candidates remain legitimate semantic inputs.
6. Contrast --check, native build/execution and lazy run at their applicable body
   request boundaries; inspect generation, default/provided bodies and copied
   source origins where the same checks execute. Unrequested-body omission is
   intentional; do not eagerly scan all bodies to make the test uniform.
7. Evaluate the out-of-scope search/hint path independently. The user permits
   deleting the hint feature. Prefer removing it if isolating it is unnecessary
   complexity; retaining a hint requires proof that it runs only after genuine
   lookup failure and cannot alter acceptance, chosen binding/candidates,
   inference, visibility rights or execution. Do not mistake the current terminal
   error enforcement for an already isolated optional hint. Deleting it must not
   remove required rejection of actual inaccessible or nonambient functions.
8. Produce the responsibility-level repair plan. Include competing selectors,
   incomplete failure categories, spelling-based identity recovery, ambient
   cursor dependencies and ownerless whole-AST scans if observed. Do not restrict
   the fix to fallback, std, one syntax shape, or skipping visibility for closures.
   Preserve correct paths; no duplicated resolver or late-name fallback.

## Completion and Handoff

- Save bounded executable contrasts with exact carrier/source/std/module hashes,
  actual commands/results and required outcomes. Preserve this repro and positive
  controls plus genuine missing-use/private/ambiguous/wrong-argument controls.
- Report one end-to-end authority/reader map and explicit findings: confirmed
  defects, justified behavior, uninspected boundaries and any genuinely missing
  specification decision. Do not claim all possible scoping defects exist.
- Assign each confirmed gap to an existing correctly scoped task or a new finite
  repair with concrete producer/removal/consumer actions and regression matrix.
  Attach real dependencies before investigation closure. If a correction exceeds
  the finite scope, split it rather than leaving an open-ended implementation.
- For each proposed helper removal, show how legitimate enforcement survives.
  A passing reproducer or removal of diagnostic text is not design completion.
- Obtain independent review of the investigation and task decomposition before
  closing this task. Repairs then need their own actual execution/mode validation
  and independent completion review; final G1/G2a/G2b/G3 remain mandatory.

The separately observed generic-requirement existential-boxing failure remains
recorded in met-g53w; it is not silently bundled into this lexical/visibility audit.
This ticket's creation authorizes investigation planning, not a language change or
an already accepted implementation. No compiler source or test expectation is
changed by registering this task.

## Investigation Results (Implementation Not Started)

Source reviewed at a8f85323 (semantic source b5df0276); no compiler/std/test
source was edited or rebuilt. Old23f7 and newe6ff were compared on **65 distinct
probe projects** through check/native/JIT, with supplemental gen controls.
All five diagnostic batches finished exit0 with fixed inputs; **588 watched
commands** include compile/link/runtime steps and the initial invalid macro setup.
Exit0 of the collector does not mean the observed programs are correct. Old/new
exit codes and actual execution stdout agree for every compared case.

The four new macro probes initially lacked a package manifest. Their missing
Syntax dependency errors are setup failures, not visibility evidence. Re-running
with the existing exact Syntax manifest/lock fixes that setup; those fresh
macro outcomes replace the initial four for semantic conclusions.

Durable commands, source catalogs, binary/source/std/tool hashes, logs' primary
diagnostics and observed output: meta/evidence/existing-feature-conformance/
source-owner-facts/lexical-visibility-audit.json. Source catalogs and runner code
are saved, so tmp is not the sole reproducibility record. No formal performance,
fixed point, sanitizer/full suite or repaired acceptance is claimed.

### Authority and Reader Map

| Boundary | Current owner/result | Audited outcome |
| --- | --- | --- |
| Namespace qualification | Resolve/Lexical::namespaceExprModule and resolveLexicalModuleExpr, lexical name list plus ImportOrigin | Distinguishes a local value from a same-spelled module; explicit qualified call remains qualified. Both controls execute correctly. |
| Module/global binding | Check/Visibility::moduleBindingAt, Resolve/Global::globalIndexAtUse | Original module/use identity restricts global candidates. This lookup is not inherently an unrestricted global-name search. |
| Local lookup | Resolve/Locals::localIndexByName, newest local first; typedLocal forces a pending global type | Correct nearest-value identity is available. Global declaration installation and global type completion are separate. |
| Identifier classification | Check/Generic::resolveIdent returns Value/Function/TypeQualifier/Undefined plus target | Prefers a value independently of its callability. Call-name selection does not consume this classification. |
| Pre-call visibility | Record::recordExpr invokes checkExpressionVisibility before its Call branch; gen performs checkUseVisibility on the whole expression arena | Reconstructs free-function meaning from spelling without the local binding or selected operation. Can fail before the real selector runs. |
| Call classification/cache | Resolve/Expr::resolvedCallee, AST-expression CachedCallee | Suppresses free lookup only if the currently observed local.ty already is fn. Noncallable or pending values fall through; NoStaticCallee conflates dynamic/no-match states. |
| Free candidates | Resolve/Module::visibleFreeFunctions and findFunc | Collects module declarations and public import/re-export overloads, checks all candidates, preserves ambiguity; first selector-only candidate is diagnostic fallback. Tested union/order/invalid controls do not show global precedence. |
| Source operation | Record::recordFreeCallExpression, recordDynamicLocalCall; direct/dynamic CallTemplate | Selected local closure records bindingDeclStart and function term. Raw globals are nevertheless encoded as ClosureLocal. pow is classified separately by name before ordinary lexical resolution. |
| Closure arguments | Resolve/Expr::recordDynamicCallTemplate, Check/Call::checkCallArgs, source template closure | Context/types are partly checked, but labels/access modes/full arity do not share the ordinary signature admission contract. Template closure later asserts plan count. |
| Instantiation/final use | Mono/Call::selectDynamicTemplateCall and checkFinalClosureCallEvidence; Backend/Llvm/Mid::midCanonicalClosureCallPreflight | Consumes retained binding/function type. Preflight requires a matching Mid local for ClosureLocal, so a global selected under that variant fails later. It does not repair the original source name decision. |
| Generation harness | Codegen/Gen::synthGenMain and Module::findFunc genMode fallback | Synthetic parseItem/write calls rely on global spelling lookup after the early sweep. The fallback itself has no synthetic-origin check; removal of the sweep alone is not a complete safe repair. |

### Confirmed Findings

**V1 — Diagnostic-driven preselection (the original failure).**
checkExpressionVisibility has two terminal-error paths: no visible free function
plus any loaded same-name free declaration; or some visible free declaration
without matching labels plus any loaded same-name matching-label declaration.
Neither first tests whether the call is a lexical value invocation. Both
firstFuncByName and labelMatchOnlyInvisible are used only by this checker;
firstVisibleFuncByName also has a legitimate resolveIdent consumer and must not
be removed indiscriminately. The restricted/free candidate resolver is not the
source of the original external-name interference.

The failure reproduces for parameters, locals, a global callable value, aliased
names, defaults and provided methods. Public versus private unrelated declarations
both interfere; renaming/removing the unrelated declaration restores correct
42 output where the independent global/capture limitations do not intervene.
Adding a private zero-argument declaration can break a previously valid local
closure even when a public wrong-label free overload is already imported.

This is **not an isolated optional hint facility**. These functions emit terminal
errors before lookup failure is established. The user permits deleting the hint:
recommend removing the unrestricted pre-call diagnostic search, with genuine
visibility enforcement owned by lexical/source selection. Do not merely hide the
message, special-case closures/std, or weaken missing-use/private rejection.

**V2 — Type-dependent lexical priority and incomplete classification.**
A fn-typed parameter named callback correctly overrides callback(). Changing that
parameter to I64 makes callback() invoke the ordinary same-named function and
print11. Rebinding a fn-valued local to a scalar behaves the same way. resolveIdent
would retain the nearest value, but resolvedCallee implements its own type-based
condition. Thus the suspected priority problem exists separately from V1; it is
not evidence that the ordinary free resolver always prefers global functions.

A pending inferred global callback is not typed before the fn test. When a
same-named ordinary function exists, it is selected and prints11. An explicit
equivalent fn annotation sends the call into the dynamic/global path, where V4
then fails. Lookup uses value type readiness as a binding discriminator and
caches that decision. A missing binding, a noncallable binding, a pending value
and a selected dynamic target must not be represented by one failure sentinel.
Independent review confirms that falling through a noncallable local/parameter
violates spec03's nearest lexical binding rule and design/name-lookup section3.
This is an existing contract violation, not a new specification choice.

**V3 — Incomplete closure signature admission.**
Both a local/parameter closure and a closure-valued field declared with
fn(value: I64) accept callback(other: 42I64), and native/JIT print42. Spec04
requires closure labels and declaration order to match. Missing/extra arguments
instead produce internal error: selected call has an incomplete argument plan.
Unexpected inout to a by-value closure passes check then fails Mid preparation.
Wrong argument types and out-of-range I8 literals do reject normally: do not
replace the useful existing context/type checks with a weaker new checker.
The producer records positional arguments and template closure checks their
count; no single source admission owner checks the complete fn-value signature
before publication. This is a separate repair from com-cwu1's already accepted
existential requirement argument checks.

**V4 — Global callable receiver loses storage kind.**
A simple noncapturing global fn value, with no name collision, passes check but
fails native/JIT with function/main requires verified Mid lowering. The lexical
lookup returns a Local record flagged isGlobal; recordDynamicLocalCall publishes
ClosureLocal without preserving that distinction. Final preflight then searches
only Mid locals by bindingDeclStart. Keep the source/global identity and lower a
real global receiver through the canonical pipeline; do not weaken the local
receiver preflight, reinterpret identity as a string or introduce AST emission.
This finding concerns a noncapturing global value, not adding a new capture shape.

**G1 — Generation compensates for an unscoped fallback with an ownerless sweep.**
The same V1 failure occurs during gen, including in an application-only helper
unneeded by the macro. Normal lazy run can omit that valid unused helper;
check/native and gen currently reject it. Conversely genuine unused missing()
is omitted by lazy run as intended. Gen's findFunc fallback searches every
loaded free declaration whenever genMode is set, not only trusted generated calls.
The source shows a policy gap; the probes do not demonstrate successful private
user dispatch through it. Remove broad mode privileges by retaining explicit
synthetic declaration/origin identity. Then check requested user bodies in their
lexical environment instead of checking all Expr.Call rows without their owners.

### Correct or Separately Scoped Controls

- Correctly typed local/parameter closures override a same-module or explicitly
  imported matching free function and execute42. An imported and a module-local
  overload form one candidate set; reversing which origin owns I64/Bool yields
  the same11/42 outputs. No early-first-candidate defect was found in those cases.
  Reversing declarations/imports preserves these results. A call before a local
  declaration invokes the free function11; a later call invokes the new local42.
  Wrapping the local closure in a value block preserves both V1's collision
  failure and its renamed positive control, without introducing a new cause.
- Missing imports, selective import of a private function, an imported public
  overload with a private matching alternative, wrong visible labels/types,
  ambiguity and numeric range errors remain rejected. These are preservation
  controls; the new repair may simplify diagnostic wording without granting access.
- Explicit namespace qualification and a module name shadowed by a local value
  behave correctly. A generic T with an unrelated module struct T succeeds in
  check/native/run/gen. No corresponding type/namespace leak is established.
- A closure capturing another function value is rejected by checkedCaptureCell.
  com-b1ro/com-esri explicitly exclude that environment shape from current feature
  conformance. Do not mislabel its earlier expected-positive probe or expand
  phase3 to implement that shape. V1 can precede this independent limitation.
- Global-closure Mid failures, missing/extra-argument internal errors and wrong
  labels are actual unsuccessful or invalidly accepted probes, not passing gates.
  No repaired-path performance or final task/area completion is claimed.

### Specification Interpretation Boundary

A local closure parameter named pow that would return42 is ignored for
pow(base: 2I64, exp: 3U64); actual native/JIT output is8. Both Record and ExprType
prioritize the named Pow protocol operation before the ordinary lexical path.
Spec12 explicitly defines this named operation, unlike an ordinary imported
function, but does not spell out its interaction with same-named local values.
Do not silently change that language-facing behavior as a repair side effect.
Before touching this special route, confirm whether the existing named-operation
contract permits the priority or whether ordinary lexical shadowing must win.
The general noncallable-value fallback is separately confirmed as V2's violation
of the existing lexical contract. Do not use pow's special boundary to defer V2.

### Proposed Finite Repair Decomposition (Not Yet Registered)

1. **Binding-first call selection and visibility, eager/lazy paths (V1/V2).**
   Share the lexical binding classifier with call-name selection. Retain binding
   identity/kind before deciding callability or completing pending global types.
   Separate absent/noncallable/pending/selected states and candidate exclusions;
   scope caches to the admitted source decision. Apply visibility to the selected
   declaration/origin, remove unrestricted pre-call hint searches and preserve
   valid/free overload frontiers. Binding classification must not promote
   resolveIdent's firstVisibleFuncByName result into a selected overload: collect
   and apply the complete free-function frontier separately. This unit replaces
   the normal body Record precheck; unit4 owns the gen sweep/fallback migration.
   Verify local/parameter, aliases, defaults and
   provided bodies end to end in check/native/run. Preserve named-operation
   semantics until their scope interaction has an explicit disposition.
2. **Complete closure-value signature admission (V3), independent of1.**
   Project an already selected function-value signature through shared argument
   validation for labels/order/count/type/context/access passing before recording
   a complete argument plan. Cover local and field targets with valid, wrong
   label/order/count, unexpected-inout, wrong type and literal-range controls;
   preserve actual dynamic target through Mid and native/JIT. Do not reopen the
   unrelated finite existential repair merely to hide the new required scope.
3. **Global closure receiver through final use (V4), consuming1's binding kind.**
   Carry global declaration/storage identity from selection through the source
   target, instance, canonical Mid receiver and LLVM call. Cover inferred/explicit
   globals, same-name functions, aliases and module provenance; retain real local
   preflight checks. Native/JIT must execute the actual global closure42, not
   merely pass check or compile a different free function11.
4. **Explicit gen-harness authority and lexical gen requests (G1), consuming1.**
   Replace the mode-wide global fallback with explicit trusted synthetic target
   identities/origins, while source macro/default/provided helpers use ordinary
   lexical decisions. Remove/replace the ownerless call-visibility sweep only
   after its required enforcement has an owner. Exercise macro helper and unused
   application contrasts plus genuine inaccessible source calls, real generated
   parseItem/write execution and the existing full gen gate.
   If gen's old paths remain after unit1, record that explicit transitional gap;
   unit1 alone cannot establish visibility authority for every mode.

### Independent Review and Current Disposition

Two independent reviewers accepted the source-level causes, evidence limitations
and four finite repair units. Architecture review verified V1/V2/G1 and the
binding-classification versus overload-selection distinction. Signature/consumer
review independently verified V3/V4's producer-to-reader chain and their inclusion
in existing-feature conformance; function-typed capture remains excluded.

Both independently recounted the initial58 projects/522 commands. Architecture
review additionally verified the final7 order/wrapping controls, giving65 projects
and588 commands, with unchanged inputs and no old/new exit/stdout differences.
Neither review certifies a repaired implementation or any final validation gate.
Review conclusions and required scope refinements are incorporated above rather
than stored in separate review files.

New repair tasks/dependencies have not yet been added: the goal requires stopping
when required task changes are discovered. This investigation remains in_progress
pending assignment of the required repairs/decision dispositions; investigation
and decomposition review are complete. Parent/G1 must not close on this report.
