---
id: com-zqqi
status: closed
deps: [com-erlx]
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit method signatures through their selected call and body consumers

## Guarantee and Finite Work

Connect registered inherent/trait-impl method parameter/result annotation occurrences to common lexical admission and retained signature consumption. Bind exact registered method, originating impl/member premises, Self receiver and any extension source; preserve authored Self independently from public/provided placement.

Carry those facts into selected method-call types and actual BodySignature publication, rejecting missing justification before source declaration success. Raw trait requirement/translated provided-signature handoff belongs to the requirement sibling; body-local annotations belong to the body sibling. Do not duplicate com-4k31 candidate/path dispatch selection or API authority-narrowing repairs.

The [com-erlx re-review](com-erlx.md#resumed-checkpoint) found that a failed
parent can retain raw registered callable rows after a successful earlier
member. Check the existing missing/failed-owner admission guarantee against
that prefix, including the implicit trait-receiver premise. Authored where
premises are staged by com-erlx.

## Required Scenarios

- Unused and instantiated inherent/trait methods; direct/inherited/selected-extension premise and missing/unrelated/wrong-instance premise.
- Receiver/Self, same-spelled foreign binders and impl/member conditions remain exact through parameter/result/BodySignature consumption.
- Missing retained evidence cannot be repaired by ambient body state; actual native/lazy calls agree with saved types and preserve passing modes.
- Default helpers and async/Unit representations remain noninterfering; both adapters and error recovery are covered.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First RED

On candidate `1f9a99d6`, the new
`method_signature_unproved_trait_projection` is incorrectly accepted by
`--check`: the unused method's `T#Project.Item` has only an unrelated Marker
premise. Adding the direct Project premise passes; expressing the same
invalid signature as a free function rejects at the projection with the
expected source diagnostic. This confirms the existing admission rule can
be reused and the method path is missing the handoff.

## Failed owner checkpoint

`ImplProjectionBoundOrigin value receiverRecovery` registers a method of a
trait receiver, then rejects a later member of the same impl. On `1f9a99d6`
the earlier method still contributes an implicit receiver premise. The fix
ties authored methods to their exact source scope and requires completion of
the parent before either enumerating or validating that premise. A completed
impl still supplies the premise. Generated callable identities continue to
use their existing evidence path.

Build `20261112T110559-build-383a49` produced candidate `61e6af2d`.
All nine `ImplProjectionBoundOrigin` cases passed. The retained trait-subject,
Unit forwarding and default callable-form fixtures passed in check, JIT and
AOT. The unused method signature RED and the selected signature/body
handoff remain open.

On identical compiler sources, alternating three measured compiles after
warmup gave medians of 6.375821 s for `1f9a99d6` and 6.401968 s for
`61e6af2d`, with identical LLVM across all runs. The comparison does not
replace the formal fixed-point measurement.

## Signature handoff checkpoint

Build `20261112T111926-build-598946` produced candidate `f18feecc`.
Both lowering adapters now register method source slots with the existing
signature admission path. Impl-owned recipe edges are admitted against the
original impl premises. Selected method signatures and body signature
publication consume the retained recipes. The original unused-method RED
rejects at line 5 with the exact conformance diagnostic in check, JIT and
native compilation. Nine internal controls and nine distinct public fixtures
passed in their applicable modes, including trait-subject receivers,
associated results, default factories and Unit forwarding. Compiler sources
also compiled to LLVM with the candidate.

`RetainedMethodSignatureConsumers` passed with a real inout call whose
parameter and result project through a nested impl-bound argument. It compares
the admitted types with both final records. Both consumers reject the same
environment after its impl evidence is removed, even when a body result is
pre-populated. The public control passed check, JIT and AOT.

The duplicate-callable recovery test reproduced an unowned diagnostic row on
`f18feecc`. Registration now binds the lexical function before the surface
can reject it. The failed row cannot contribute a receiver premise or reach
synthetic signature handling. Candidate `dbf95c14` passed the recovery mode
and the existing scoped positive/reject controls.

### Independent review and provided placement

The independent `zqqi_completion_review` reviewed
`5eae678d..3374cb2e` and the registration correction that became
`645dbf9c`. It withheld closure on three findings: provided placements
missed the authored recipe, receiver-premise replay could recalculate a
nested trait argument, and the reader accepted a conflicting lexical Self.
The review also identified repeated per-method parent graph traversal and
separate reads of the full signature when consumers ask for parameters and
results. The raw requirement contract remains with com-30u1.

The provided-placement RED on `dbf95c14` showed a real selected method
recovered receiver evidence after removal. Build
`20261112T113513-build-e9ab21` produced candidate `dd653ed9`, which
uses the existing lexical owner and selected environment to read the original
signature. Both final consumer modes and all eight targeted positive
check/JIT/AOT fixtures passed. A substituted foreign lexical Self is rejected.
Identical-source medians were 6.431953 s before signature admission and
6.427369 s after it, three interleaved measurements per carrier after warmup.
LLVM differed only in generated generic body symbol components when matched
by body ID.

## Outcome

Resolved in `0facda47`. Both lowering adapters register the original
implementation and authored signature slots. Selected and provided method
consumers share the admitted graph and the selected instance environment.
Receiver arguments use earlier validated projection equations, including on
the witness side. Missing equations defer instead of selecting another
conformance. Canonical lexical Self creation uses the trait's binder and a
stable spelling across file and standard input. The reader rejects foreign
nominal receivers, conflicting lexical Self and duplicate binder IDs.

Final build `20261112T115943-build-685231`, candidate `c0b0a04f`.
Two unused signature declarations with one and two levels of receiver
projection passed from a file and standard input. Four final-consumer
scenarios passed, including both projection depths with an explicitly
selected witness and with the equations removed. The 49 existing/free and
implementation-origin controls passed, including value-adapter acceptance
and wrong-instance rejection. Selected extension, trait conformance,
provided receiver, default arguments, async, Unit, fallible factories and
newtype controls passed check/JIT/AOT. Both unproved and wrong-instance
methods reject at their annotation. A 133-fixture differential run matched
132 outputs or diagnostics and changed the intended formerly accepted
unproved signature. Generation `20261112T120511-gen-38644c` passed 25
successes, five rejections and the gen-input AST case with fixed inputs.

The final independent re-review found no remaining in-scope violation
after the input-independent Self binder, child-first equations, concrete
witness comparison, and foreign nominal receiver fixes. The old generic
projected receiver dispatch probe still reports `no matching method` on
both carriers. It is covered by the complete-instance dispatch contract
in [com-4k31](com-4k31.md); the receiver replay control starts from an
explicit witness to isolate the signature contract.

Same-source medians were 6.529688 s (`dd653ed9`) and 6.576449 s
(`c0b0a04f`), three interleaved runs after warmup. LLVM matches when
generated generic body symbol components are normalized by body ID.
Formal fixed-point, full-suite and sanitizer gates remain with met-si6j.
