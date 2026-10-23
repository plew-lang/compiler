---
id: met-6e6k
status: in_progress
deps: [com-g2qg, com-nplw, com-nucu, com-m0bf, com-e9l2, com-loyb, com-3q2n, com-4kti]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Audit saved conversions, descriptors and first-concrete consumer boundaries

## Bounded Execution and Gate Ownership

This is an area epic, not one executable multi-week task. Its current bounded
work and real prerequisites are tk dependencies under the
[parent policy](met-si6j.md#bounded-task-policy):

- [A](com-g2qg.md): already completed 3A inference/fixture cleanup.
- [C1](com-nplw.md): forward array context.
- [C2](com-nucu.md): partial-input projected member enumeration.
- [C3](com-m0bf.md): unstamped nominal producer inventory.
- [C4](com-e9l2.md): result recipe/projection readers.
- [C5](com-loyb.md): source conversion endpoints.
- [C6](com-3q2n.md): closure/dynamic descriptor dependencies.

Close this area's exact existing contract after required children/repairs and
their scoped fresh verification. The final frozen candidate normal/gen/deps/full
sanitizer/fixed-point/performance obligation is explicitly owned by
[G2a](com-p5um.md)/[G2b](com-9l3b.md) and cannot be waived when this
area closes. Historical checkpoint gates are not current-candidate certification.
Earlier current/next/WIP observations refer to their named revisions; the bounded
children reconcile what actually remains before any repair. No new meaning or
unsupported feature is authorized by this allocation.

Complete the consumer audit adjacent to source publication and callee proof transfer. Saved source result/signature/conversion/projection facts and descriptor dependencies must be interpreted with explicit source and instance identity; declaration dependency scope is not runtime descriptor reachability. Construction of first concrete evidence is permitted only within the source-selected requirement; final readers must not return to AST/type-name/ambient-cursor selection.

Audit dynamic/closure descriptors, optional payloads, result/parameter signatures, nominal registration/binder stamping, final conversion proof endpoints, structural/path/Box admission and projection normalization input/output/proof identity. Do not erase semantic/phantom arguments merely because machine payload layout ignores them. Existential inherited-interface collection is a separate feature from correct supertrait projection normalization; broader unsupported shape work is com-uutc/com-b1ro.

Acceptance: record demanded dependency paths, typed endpoint/scope/owner validation and final consumer for each family; preserve declaration checks without incorrectly demanding execution readiness. Show removal of duplicate decisions and missing-result fallbacks through AOT/JIT, including prior-call-dependent results and generated bodies. This is unfinished audit/migration, not proof of a current source-level defect.

Retained representation audit: CallTemplateReceiver.Opaque descriptions that compiler-internal types need no semantic term, and Verify/Call comments that C handles are interchangeable, must not authorize erasing semantic type identity. Inspect actual uses before changing them; machine handle/layout equality is not source compatibility. Check/Literal associated-function inference, groundedTypeOf/typeOf and construction fallback entry points remain classified producer/reader audit targets, not blanket deletion requests. Preserve operator result projection (Ord -> Bool, Ne negation) from saved operation identity.

Dependency identity rechecked at `2983c47ff7ba0b1d693d656094e9fd0dbeca63dc`: Check/Obligations.sourceCallArgumentType passes PriorCallResult.siteKey to Check/Bounds.sourceSelectedCallResult, which finds the selected template and compares the result recipe's callSite. The historical ignored-siteKey observation is not current for this path. Preserve matching/wrong-key tests during migration; other recipe variants and final-consumer closure still require their own evidence. The finite [restart reconciliation](met-j9mv.md#cumulative-restart-reconciliation) identifies current entry points and consumers; it is not a full correctness audit.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Existing conversion/projection/descriptor/result-recipe and first-concrete consumers, including PriorCallResult.siteKey controls. Preserve implemented checks; remove legacy unstamped/name/cursor decisions only with matching producer migration. No new existential/interface feature is inferred from this task.


## Nominal Body-Receiver Identity Increment

The registered-carrier repair of mid_type_recipe_instances adds a same-spelled
carrier with a different declaration identity. It exposed sameBodyRuntimeRef
comparing only names/arguments when interning body environments, which merged
that foreign receiver with the intended carrier and attempted to publish a
second different call at one body/site. Prefer canonical declaration identity
when both terms have it, including aliases whose authored spellings differ.
Keep the existing bootstrap legacy fallback only where a producer lacks it; its
remaining removal is still part of the producer audit, not proof of completeness.

The internal recipe fixture uses the normal binder and Arena.registerEnum APIs
to supply a real nominal generic payload carrier. It remains a Mid-only test,
without requiring frontend initialization, a source body or executing a callable.
Its instance-specific results, cross-instance cursor, missing publication,
known Unit, forged Unit and absent-result controls are preserved. Added controls
reject a foreign nominal payload and require distinct body identities. A duplicate
statement-owned final publication reports through CallSiteKey rather than reading
a nonexistent source expression for its diagnostic. Current-source imported AOT
passes; fresh compiler/full gates remain separate.

## Canonical Grounded-Argument Read Increment

A new ordinary source control reproduces an incorrect rejection of
keep(value: <Box value=42I64 />) when keep's unrelated generic parameter is also
named Box. The final descriptor contains a canonical closed Box[I64] nominal term,
but finalStaticCalleeIsComplete called fnArgsAllGround/tyRefIsGround, whose legacy
global parameter-name query classified the generic nominal head as symbolic.
A virtual Iterator control reproduced the same issue with Cursor[Item]. Its
canonical typeIsClosed result is true, while the name-based query returns false.

Final descriptor validation now reads canonical argument closedness directly,
rejecting zero/missing and genuinely open terms without resolveTy or global name
queries. Construction tyRefIsGround also defers to canonical closedness when the
nominal declaration is already known. The legacy unstamped construction path
remains separately auditable; this does not certify every type producer.
The new nominal/binder source fixture preserves the old failure as a negative
carrier control. Current-source imported implicit-call and owner-request controls
pass after the canonical repair; fresh/full gates remain required.

### Partial-input projected member lookup

projectedMemberResolution currently probes a trait with positionalArgsOpen before
selecting its requirement. This is an explicitly weak Existence query, not source
admission of one exact trait instance. Audit enumeration of distinct positional
instances and preserve the final chosen instance/proof through admission. Do not
merge different input instances as competing paths to one instance, or accept the
first instance merely because it was discovered first. Associated-output filters
must follow source selection under the shared query contract.

### Field-driven Enum Construction Inference

The f67c8fce measured carrier reproduces the previously recorded Optional.Some
failure with both an imported SemanticCompletionOwner payload and an ordinary
local enum's U64 payload. A standalone val value = <Optional.Some v=1U64 />
also rejects, while a generic struct constructed from the same pattern payload
succeeds. This is a missing enum construction producer, not evidence that the
pattern binding lost its declared U64 type.

The completed 3A increment routes struct and enum payload fields through one
inferMakeInstance / matchTypeArgumentConstraints path in Record and the gen
source prepass. It retains the selected nominal identity and uses recorded field
argument types; canonical input terms also retain their views when rebuilt.
Explicit/committed type arguments are not overwritten. The legacy unstamped
source-header adapter remains part of the broader producer audit above.

The generic_enum_field_inference source covers a literal, pattern payload,
block, multi-field variant, array payload and arrays with multiple enum elements
and String payloads. Current fresh native execution also reads both heap String
elements. Earlier source-imported File-input analysis/requested Mid diagnostics
are retained as scoped evidence; the new fresh gates below establish actual
native execution. FrontendInput.Text is one unified source and does not load
imports; earlier virtual-input setup failures do not establish compiler defects.

The approved test cleanup retains the safety purpose of
generic_enum_array_implicit in the existing successful runtime coverage: verify
multiple enum elements, correct values/layout, String payload cleanup and
applicable sanitizer checks. Remove unused_generic_enum_array_implicit rather
than duplicating the same now-valid input in an unused positive body. Check that
whole-body validation remains covered by genuinely invalid unused-body inputs;
retain rejection of constructions with no information to infer their arguments.
Revision 09e5a277 applies this cleanup, adds the genuinely uninferred empty-variant
reject generic_enum_field_inference_unresolved and removes the redundant unused
positive body from the runtime fixture. Creation commits b27ce52c and c552ebda
guarded unresolved generic heads, silent 8-byte array stride corruption,
stack overflow and unchecked unused bodies; they did not establish a language
ban on field-driven enum inference. Preserve these safety obligations rather
than weakening checks merely to make the suite green.

Separate observed context gap: after an inferred Some fixes an array's element
type, a following argument-less None still receives no forward element context.
Record's array loop applies only its incoming context to every child. The scratch
ArrayForwardContextGap.pw retains the input; the field-inference control uses an
explicit Optional[U64].None to isolate this distinct producer boundary. Audit
forward context without inferring backwards, treating unresolved generic heads
as complete or replacing explicit incompatible element types.

### Current Increment Closure Inventory

This is step 3A of the [phase-three execution plan](met-si6j.md#phase-three-execution-plan).
**3A is complete** at compiler/test revision 09e5a277 (implementation 108355cc),
using fresh bin/plewc-phase3a-final, SHA256
dac32dca0bbb99c8e1da5469035ae67fca18e50fde4b04fcaec25855a964345b.
The [closure receipt](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3a-completion.json)
records native6/reject8, LLVM22 generated-program ASan/LSan2, whole compiler source
check and standard gen24/reject5 with zero skip/failure. It closes field-driven
enum inference, not this issue's other producer/descriptor audits in 3C.

| Boundary | Current result | Closure evidence / retained limitation |
|---|---|---|
| Selected declaration/payload fields -> shared argument matcher -> saved nominal construction -> native array use | Record and gen prepass use inferMakeInstance / matchTypeArgumentConstraints in Resolve/Expr; Record's old struct-only gate is removed. Canonical declaration identity and views are retained by rebuildTypeTerm; explicit/committed arguments bypass inference. The nongeneric setup shortcut is in the tested fresh compiler. | Standard build 20261023T092930-build-857b7b exits0 with unchanged inputs. generic_enum_field_inference, generic_enum_array, generic_ctor_infer and generic_constructor_nested_constraints execute with golden output. Conflict/payload/field-width/arity/uninferred controls reject with expected diagnostics. |
| Old ordinary implicit-enum array reject -> successful layout/value/cleanup coverage | Obsolete reject removed; generic_enum_field_inference covers multiple enum elements and both heap String payload values. | Native and LLVM22 instrumented execution match the golden; no sanitizer errors. Existing generic_enum_array provides the explicit-argument/chain-result contrast. |
| Old unused valid-input reject -> genuine unused-body invalidity controls | Obsolete fixture/expectation and redundant unused positive body removed. Existing unused_struct_required_array_field and unused_generic_argument_bound reject in whole --check with their existing diagnostics; unused_generic_enum_context is accepted. | Fresh reject controls exit1; successful native unused-body context contrast and fresh whole compiler --check exit0. No extra duplicate unused test was added. Lazy omission of unrequested bodies remains permitted. |
| Array/heap-payload ownership -> sanitizer checks | E manifest registers generic_enum_field_inference; entries exist and are unique. Two generated-program controls pass LLVM22 ASan/LSan with leak detection and verified inserted ASan calls. | Generation is instrumented before optimization via opt -passes=asan and linked with the same LLVM22 compiler/runtime. Full compiler-instrumented A/B/E and full C/D remain final-parent gates in 3G; this is not a claim that E has run. |
| Public/shared source inference -> requested Mid / final native consumer | Fresh inferred_enum_argument_source_owner executes its frontend source-owner/conversion checks successfully; native lowering/execution controls pass. Standard gen tests exercise the shared prepass without regression. | Gen 20261023T093344-gen-52bbe8 exits0, pass24/reject5/skip0/fail0, plus gen-input-ast, with unchanged inputs. Earlier actual File-input requested-Mid evidence remains separately scoped; the fresh whole compiler --check also succeeds. |
| Forward element context / raw type / conversion / descriptor paths | Separate remaining work, not discharged by Some inference. | Keep the observed forward-context gap and the broader path inventory for 3C; do not expand 3A or close this issue from its focused success. |

The 3A exit items are discharged; proceed to 3B's selection/evidence inventory.
The [independent three-reviewer completion audit](com-h4pz.md#outcome) accepts
this scoped closure without blocking findings. General gen regression is not
a dedicated forced-branch test for enum inference in the gen prepass.
Keep this issue in_progress for 3C. Whole-parent normal/deps/full sanitizer and
current formal performance gates remain 3G; prior f67c8fce gates are not assigned
to this fresh binary. A new failure or changed input can require earlier gates.
