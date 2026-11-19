---
id: com-yeua
status: in_progress
deps: [met-c1pg, com-to2g, com-ew3i, com-x7ql]
links: []
created: 2026-11-02T21:30:19Z
type: task
priority: 1
assignee: Koji Murata
tags: [diagnostics, frontend, driver, verification]
---
# Carry producer failure domains to compiler rejection consumers

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `SOURCE-FAILURE-DOMAIN-CHANNEL`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Current mixed service/CLI Failure/status1 cannot soundly discriminate intended source rejection in existing finite negative consumers. Add a fail-closed producer-owned discriminator through returning service/cache/terminal adapter for named cases; do not derive class from final text. Exact external carrier/API representation must be chosen and documented within current diagnostic/driver contracts.

Finding references: SERVICE-DOMAIN-LOSS consumer distinguishability, rejection-domains80controls/32false-success.

## Covered source boundary

- CheckedProgram CompilerSessionResult/ProgramCheckResult/Result caches
- Compiler compileSource/runCheck/runProgram adapters
- DeclarationProgram and PreparedProgram typed origins before conversion
- normal reject/partreject, expose18, ASan B channel integration; gen channel is separately consumed by com-k4c9

## Guarantees and scenarios

- Returning source rejection vs wrong-session/raw invariant/implementation-limit/tool-input failure with same rendered Error/status are distinguishable.
- Drain/repeat failure keeps its origin; internal default/unclassified fails closed.
- Actual process adapter controls cover silent1, internal1, status2, signal, timeout, diagnostic then signal versus correct source rejection.
- Define minimal typed/per-run channel and its lifetime; public status or callback ABI changes require explicit documented decision, not implicit adoption.

## Excluded

- No compiler-wide blanket panic rule or stable public diagnostic serialization mandated.
- No source semantics or all-runner expansion.
- Parent audit classification is evidence, not this product channel.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.

## Frontend and Syntax Failure Audit Intake com-6lza

- `SOURCE-DOMAIN`: Newly registered existing com-yeua exact unit already covers returning/cache/CLI origin; do not create duplicate D1 catchall.

Exact scopes/scenarios/exclusions are in [finite intake](../../../evidence/compiler-failure-audit/frontend-syntax-owner-candidates.json); adopted paths are in [assignment](../../../evidence/compiler-failure-audit/frontend-syntax-owner-adoption.json). Preserve existing owner scope and unresolved policy boundaries. This is audit intake, not product completion.

## Adopted Failure Policy

The [diagnostic contract](../design/diagnostics.md#input-failures-and-internal-invariants)
now permits panic only for genuine contradictions of established internal
invariants. Ordinary invalid source/input/tool/limit and validator refusals
remain typed failures. Existing generic internal wording is not proof of that
precondition; unresolved classification must fail closed as non-source failure.
Preserve the domain through returned/cache/terminal consumers and the named
negative-test lanes. An abort/crash/timeout never counts as correct source
rejection, even after an expected diagnostic. No public exit-code catalog or
protocol was selected by this policy; retain the existing explicit interface
decision boundary. Implementation and actual consumer RED/GREEN remain open.

## Execution scenarios

Keep the original producer-to-consumer scope. First establish a typed domain on
returning diagnostic values with an unclassified, non-source default. Equal
severity/location/message must not imply equal failure domains. Rendering must
remain nonterminal and preserve the human output. Then classify the named actual
producer branches and preserve domains through request/cache/stage conversions,
before implementing a private per-invocation result channel in terminal adapters
and consuming it in the existing negative lanes. Public exit codes, diagnostic
text and ORC callback ABI remain unchanged; any required change retains the
explicit decision boundary above.

Required controls: equal rendered source/internal/input/tool/limit failures;
unclassified default; warning versus failed request; repeat/drain/cache retention;
source parser/check rejection versus missing input/raw owner/limit/tool failure;
actual normal/expose/ASan B consumer with silent1, internal1, status2,
signal/timeout and expected diagnostic followed by abnormal termination. Reuse
com-fsuq's saved80 controls and keep gen consumption in com-k4c9. API tests are
necessary but do not replace real producer/CLI/consumer integration or scoped
independent completion review.

## Current implementation checkpoint (not closure)

Typed FailureDomain and fail-closed diagnostic values are implemented. Existing
rendered text remains unchanged. Meaningful source/input/stage-conversion REDs,
source owner cache repeat/drain controls and GREEN on both the fixed old carrier
and the freshly rebuilt compiler are recorded in
[the implementation checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/README.md).
Standard build 20261105T164302-build-d0fd8b passed with unchanged inputs. No
whole profile, fixed point, formal performance or final consumer completion is
claimed. The checker is explicitly a manual scoped probe pending the complete
channel/consumer integration; the task remains in_progress.

Remaining: producer classification beyond the named initial return/global-access
and missing-root-input branches, including validating the fixed parser contract;
CompilerSession/ORC and all named retention/conversion boundaries; the private
per-invocation result channel and actual normal/expose/ASan B consumers; required
validation and independent task completion review. Parser text saying
unsupported is not a classification oracle: current spec/02 explicitly excludes
multi-scalar character literals until Grapheme is defined. Preserve unknown
origins rather than guessing from wording.

## Authorized ABI Refusal Distinction

The user authorized checking the eight managed expose inputs against actual
backend support, correcting their tests, and recording future support. Preserve
all18 cases: six source-exposure restrictions and four conflicting external ABI
cases require Source; the eight Buffer[I64]/Ref[I64]/String/Array[I64] parameter
and result cases require precise Limit, normal exit1, intended ABI reason and
no sanitizer/supervisor failure. Ordinary reject/partreject and ASan B source
lanes remain Source-only. Do not accept arbitrary non-source failures or tag an
implementation restriction as a language prohibition. No skip or deletion.

The source-owned boolean support query first obtains checked final destruction;
its failed contract/ABI queries propagate their original domain, while its
explicit supported-subset false result produces Limit. Preserve supported scalar,
pointer, narrow integer/F32 and native O0/O2 controls. Controlled doubles must
cover Source/Limit cross-substitution, wrong reason, status/signal/timeout,
sanitizer and missing/malformed channel. The original 80 RED and subsequent88
controls remain historical evidence, not proof of this amended contract.

[met-2qbc](met-2qbc.md) owns future managed/unique C exposure eligibility and
ownership decisions, separately from repr(c) aggregate layout com-042v. Future
support is not a new prerequisite for phase three. Precise refusal and preserving
existing positive ABI behavior remain required here. The previous WIP channel
checkpoint is retained in meta; these tasks remain in_progress and unclosed.

## Scoped Exposure Classification Verification

The [approved finite correction](../../../evidence/rejection-domains/diagnostic-domain-implementation/managed-abi-correction.json)
records meaningful fixed-candidate RED, new build20261106T024018-build-0778a6
with unchanged inputs, actual Source10/Limit8 and C/Plew/Clang/O0/O2 positives,
96 controlled domain/status/reason contrasts and CLI regression7. Independent
managed_expose_refusal_review accepts this finite correction, including exact
old/new eight inputs and producer preconditions. No skip/deletion or new ABI
support. met-2qbc remains future work. This is not completion of this task:
remaining producer/classifier integration, runner controls and applicable gates
plus independent whole-task review still apply.

## Scoped Type Producer Checkpoint

[type-domain-checkpoint.json](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-domain-checkpoint.json)
records source type/literal producer RED→GREEN and fresh API checks. A discovered
raw counterexample compared an unowned nominal to a builtin and falsely produced
Source. I64/F64/function/record contrasts in both directions now remain
Unresolved before shape/sendability/conformance decisions; ordinary and generic
value checks retain non-Source refusal. Compatibility owns this decision and
resolves a legacy nominal owner once, rather than classifiers correcting it.
Independent review accepts the finite source/API checkpoint only.

The real production reject observation preserves all150 prior passes and reaches
342/1068;726 remain failures, not skips or accepted refusals. The normal-dispatch
internal valid-rejection double now emits the private channel; all160 unchanged
control assertions pass. Other producers, named retention/conversion boundaries,
instrumented ASan B and whole-task completion verification remain outstanding.

## Scoped Field Visibility Checkpoint

[visibility-domain-checkpoint.json](../../../evidence/rejection-domains/diagnostic-domain-implementation/visibility-domain-checkpoint.json)
records same-fixture producer RED→GREEN and fresh API4 probes. Known private
read/write/pattern and pub(get) setter refusals are Source at the four existing
producer sites. Unknown owner/field behavior and visibility/order are unchanged.
Public getter and same-module private access remain accepted. Independent review
accepts source changes and fresh API only. Actual normal reject classification
preserves342 prior passes and reaches388/1068, with680 failures retained.

Classification caution: current FrontendInput.Text parses only its root, without
the File branch's dependency discovery. Missing factory messages through that
path do not establish source invalidity. Initial dependency/stdRoot setup errors
are excluded from RED; the final cross-module fixture uses File graph admission.
Text graph support is not added by this increment. Parent completion, other
producers/retention, instrumented ASan B and all final gates remain outstanding.

## Trait-Cycle Repair Prerequisite

[met-c1pg](met-c1pg.md) owns the two confirmed defects: malformed graph inputs
are not diagnosed at their validity boundary, and unresolved/invalid identities
can be used as cycle evidence. It is an actual prerequisite of this task, with
com-x95z supplying the existing symbolic-projection admission conclusion.
The user approved filing this repair after clarifying both responsibilities.

[Executed raw evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-admission-blocker.json)
retains the three counterexamples; current raw diagnostics remain non-Source.
No Source annotation has been applied to the cycle/growth branches. Do not
classify those refusals until met-c1pg establishes the input/comparison contract.
Then finish this task's source-domain retention and real consumer integration;
met-c1pg does not close this task or substitute for the channel/consumer gates.
TraitCycleFailureDomains remains intentional WIP RED pending that paired work.
See [task/dependency adoption](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-cycle-task-adoption.json)
for the checked graph and planning review; no implementation is certified there.

## Nested Conditional-wrapper Source Refusal Control

The newly maintained reject fixture
`associated_condition_normalization_nested_missing` exercises an actual source
where-condition refusal through nested projection/conditional conformance.
[Execution and independent review](../../../evidence/rejection-domains/diagnostic-domain-implementation/nested-conditional-wrapper-controls.json)
show check/lazy exit1 with the intended where diagnostic but an unclassified
private receipt; normal reject reports FAIL(classification=1). Good and
Required-added controls pass, so this is not arbitrary invalid raw input.
Keep this source producer/transport case within the existing domain-classification
work; do not weaken com-fsuq's consumer or tag unrelated failures Source. The
location currently points to the requirement declaration, and lazy refusal adds
ORC wrapper diagnostics; neither is certified fixed by this test addition.

## Aggregate Partial-Move Producer

An exact negative-worker replay of the prior normal suite's 743
classification failures on c41653f1 returned 739 Unclassified, one
Internal, one Limit, and two successful compilations. The accepted
cross-module extension cases remain owned by met-bejv. Preserve the
other dispositions separately; Unclassified is not a proof of an
established source violation.

Scope of this increment is spec/11's refusal of aggregate partial move.
The shared ownership verifier establishes the violation for explicit
moves and selected consuming method receivers. It now issues Source at
that boundary. The explicit-move arm no longer repeats the same check
after this verifier succeeds. No other refusal changes domain.
Five existing fixtures and the new consuming_receiver_partial_move
fixture changed from Unclassified to Source with identical diagnostics.
Three positive controls preserved their outputs. Independent review
confirmed both producer routes and the redundant reread removal.
The full candidate gate and broader producer work remain open.

## Source Control Transfer Producers

Two existing lexical checks now classify proved source violations at their
owners: an explicit return in a declared diverging function or closure, and a
statement following a source control transfer. Owners, completion facts and
diagnostics are unchanged. The analytical execution path still uses its warning
and records source-valid statements.

The exact c41653f1 candidate and the diagnostic rebuild were compared with
the negative worker's owned channel. All 25 existing targeted fixtures
changed from Unclassified to Source and kept byte-identical stderr and
their required diagnostic reason. Four JIT output controls passed,
including warning-only loop reachability and a covered match arm.
Independent review confirmed that synthetic/analytical branches do not
become source errors and no internal-context branch changes domain.

## Callable Registration Conflict Producer

The shared declaration registration now reports Source only when the
comparison produces Possible overlap in the same callable bucket. The
Unproved, AnalysisLimit, and preexisting assembly/provided-copy routes do
not use the new classification. On the revised diagnostic build all 14
affected negative fixtures kept their exact diagnostics and became Source.
The ordinary and trait dependent-structural positive overload fixtures
kept their output. Independent review accepted the registration boundary.

A separate trial on the default-factory diagnostics passed its 15 matching
fixture reasons, but review found that a synthesized empty construction may
lack a written construction site. The trial is not adopted. Retain the
nominal owner's proof and the written construction's actual lexical origin
before classifying this missing-access case. Keep the unproved cases out
of the Source lane.

## Resolved Identifier and Value-Place Producers

Use the existing value-binding predicate across generic and ordinary source
checks. Only resolved non-value classifications produce Source; an unfilled
or unknown binding is a compiler failure. For overlapping inout arguments,
attach Source to proved value-place conflicts only. Shared-place classification follows the adopted same-reference-place rule
once the producer matches that rule by resolved binding (com-to2g).

The diagnostic rebuild makes 28 of 29 focused cases Source and keeps all
29 stderr streams byte-identical. The remaining shared-cell negative
(overlapping_inout_ref_self) stays Unclassified pending the stable-cell
proof. Four accepted JIT controls pass. The initial all-place trial is
superseded by the independently reviewed narrowed candidate.

## Selected Where Refusal Classification

Both trait_subject_arity_confer and
associated_condition_normalization_nested_missing were traced in check,
AOT, and lazy to the missing proof in prepareCallTemplateConstraints.
[Producer trace](../../../evidence/rejection-domains/diagnostic-domain-implementation/where-source-producer-trace.json).
The missing-proof branch consumes the retained recipe for a written
source operation and requires a valid subject and registered trait owner.
The private locator receipt originates in semantic Record, not in arbitrary
raw template keys or result recipes. Raw append cannot issue it. Raw
replacement or direct recording and expected-result template mutation
revoke it; internal refinement cannot promote a raw row. The general
semantic Record API still owns its expected-type analysis and is distinct
from bare template storage mutation.

The diagnostic candidate passes both real source error inputs in check,
AOT, and lazy. The grouped 49-case check preserves exit 1 and the exact
expected reason in all cases and produces Source in 46. Two unclassified
cases come from the separate iteration diagnostic owner. The third,
trait_via_stronger_target, is a generated delegation call with no written
call span. Preserve classification fail-closed there until the authored
via declaration supplies the diagnostic provenance. The native control
covers raw append with and without a matching expression, raw replacement
of an authored call, and the public direct recorder's substitution path.
The latter three demonstrated incorrect Source in successive intermediate
builds. All corrected cases retain the same reason and remain non-Source.
A wider existing synthetic evidence fixture remains at its baseline
failure; it has not been edited as part of this correction.

## Iteration Producer Boundary

Compiler 76a15cb2 records the lowered source `for` and its iterator
expression together. Record uses that origin when the checked operation
has no applicable iteration protocol. A selected operation without result
evidence and a raw duplicate statement keep their non-source domain.
Compiler cbf8b74f applies the same boundary to the existential interface
check before selecting the iterator. Closed-recipe rechecks have no source
publication authority.

[Executed controls and reviews](../../../evidence/rejection-domains/diagnostic-domain-implementation/iteration-source-refusal.json)
cover the 22 known classification failures in these two iteration branches,
the original rejection reasons, check/AOT/demanded JIT, undemanded JIT,
positive iteration and an authored/raw native contrast. Cursor/Item
compatibility and existential type formation remain distinct from this
classification. Ownership/API work remains with [com-03ra](com-03ra.md)
and the unresolved formation question with [com-nsv6](com-nsv6.md).

The neighboring delegation cases are now covered by [com-6esv](com-6esv.md).
Its final candidate preserved 20 exact Source refusals across check, AOT,
undemanded ORC and generation.

## Rejection Classification Refresh

The diagnostic build from implementation revision `47085e32`
(SHA-256 `0b5f6ce279818350bc526ca5a19ccd7c0a395b07f47904914eb263c6765b855a`)
replayed all 1,171 flat reject inputs through the private terminal channel:

| Terminal outcome | Cases |
|---|---:|
| Source | 672 |
| Unclassified | 496 |
| Internal | 1 |
| Signal with no terminal record | 2 |

This is the flat rejection corpus on an unoptimized diagnostic carrier.
The Internal result is the known `blanket_headless` case in
[com-wka4](com-wka4.md). Both signal cases reproduce on the preceding
unoptimized carrier: `nominal_newtype_projection_limit` and
`overload_structural_analysis_limit`. The prior optimized fixed-point
carrier reports a completed Limit and Unclassified respectively. Neither
outcome on either carrier meets normal Source rejection.

The three existing async borrowed/inout parameter fixtures supplied RED:
the declaration checker rejected all three with their existing diagnostic,
while the channel completed as Unclassified in check, AOT, undemanded ORC,
and gen. The checker now looks up the written signature receipt for the
exact rejected declaration on the failure path. Same 12 reasons and failure
statuses, now Source. Five positive ORC controls passed (ordinary async,
owned input, suspended delegated copy and move, and synchronous receiver).
An isolated native Frontend probe copied the rejected function and its
parameter data to a fresh declaration ID without an authored signature.
The authored original returned Source and the raw duplicate did not, with
the same diagnostic text. Other parameter-mode reasons are unchanged.

The largest remaining report families start with bare method ambiguity (19),
missing applicable method (13), arithmetic conformance (12), and normally
completing value blocks missing `give` (11). These are clusters by printed
reason for triage; the corresponding producer must establish the fact and
source origin. This is neither a full suite nor completion of this issue.

### Existing fixture stops at the wrong rejection

`unique_shadow_cliff_use.pw` was introduced by `62e495f3` to check that an
outer unique owner does not revive after an inner declaration shadows it.
The diagnostic and the optimized fixed-point candidates both reject line
9 for a normally completing value block without `give`, even after the
final read is removed. Replacing the bare block with `if true { ... }`
isolates the intended property: the final read is rejected at line 13 as
use after move, and removing it makes the program pass `--check`. The
fixture has no reason golden. Keep it out of the missing-`give` evidence
until its test intent is restored. The fixture itself is unchanged.

The subsequent specification decision is tracked by [com-j8k0](com-j8k0.md).
[com-ew3i](com-ew3i.md) owns bare blocks and [com-x7ql](com-x7ql.md) owns
nested unique shadowing and the combined success fixture. Both are
prerequisites here; this fixture is not a missing-give control.

### Missing-give producer checkpoint

The migrated shadowing fixture now runs successfully under
[com-x7ql](com-x7ql.md). The other ten original cases return the same
diagnostic and normal failure status, now with Source: ten in check,
ten in AOT, and four in demanded ORC. Six undemanded ORC inputs still
succeed. An additional if-chain case changed from Unclassified to Source
in check and demanded ORC. Three successful standalone and shadowing
fixtures retain their ORC output.

The two Lower paths record the exact block-to-value-expression relationship,
excluding the directly discarded standalone block. Record decides the
violation once and uses that receipt only to decide the failure domain. A
native producer probe rejects raw block and expression substitutions with
the same message and no Source, including when the exact authored
standalone expression and block are reused in a raw value position.
Independent re-review verified that distinction in both Lower paths.

### Bare ambiguity producer survey

The 19 baseline check inputs all return Unclassified. A diagnostic-only
replay separates the same printed message into two matching-provided
candidate failures and three gated-source failures in findMethod, plus
14 conformance proof admission failures in requireConformanceProof.
Establish the origin of each actual request before classification.

[Producer replay](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-bare-ambiguity-producers.json).

The three-mode replay locates the proof failures more precisely. In check
and AOT, all 14 come from the Requirement branch of
checkStaticMemberObligation. In ORC, nine come from the Requirement branch
of selectStaticMethodTemplateCall and five complete without requesting the
failing body or operation. Both failing paths ask instantiateBoundProof to
resolve a concrete member-dispatch witness from a recorded requirement.
This is distinct from first-concrete SourceAdmission checks for where
clauses. Both preparation paths must carry the same authenticated source
operation to diagnosis. Unauthenticated raw requests and unrelated proof
failures remain separate controls. The five direct lookup cases take an
instance route (four) or the associated route (one) in all three modes.

### Concrete requirement ambiguity classification checkpoint

The declaration and ORC requirement paths pass the retained operation key to
concrete witness preparation. Only an Ambiguous proof-query result reads
that origin. The selected operation must match its published source identity
and satisfy the existing call-proof provenance check. The shared diagnostic
preserves its wording, anchor, status and channel. Raw proof queries retain
their default domain.

Matched check and AOT each classify 14 Source, and ORC classifies the nine
demanded failures while retaining five successful undemanded inputs.
The separate lookup failures remain Unclassified. Suppressing publication
of source provenance in an isolated build retains the same rejection and
Unclassified for four representative inputs in check, AOT and ORC.
Independent review covered the proof result, provenance and both consumers.
The subsequent diagnostic factoring was independently re-reviewed.

### Ranked method ambiguity classification checkpoint

Both Lower paths record the authored method expression identity. Internal
expression-checking paths retain that identity into ranked lookup. The
public raw lookup signatures still supply no source origin. The producer
checks the exact selector and argument range, and generated rewrites cannot
gain authority from a span inherited from the original expression.

The 19-case replay agrees on terminal status, channel and first diagnostic
line. Check and AOT each classify all 19 as Source. ORC classifies 14
demanded failures and preserves five successful undemanded runs. Three
normal source programs pass check and match their ORC goldens. A native
producer probe distinguishes the valid authored lookup from an unregistered
raw expression with a span, different arguments and a registered synthetic
call. Independent re-review confirmed the raw API boundary and fallback
propagation.

The next baseline cluster with the same printed missing-method reason
contains 13 check rejections. Some are compiler-internal fixtures, so use
their intended assertions and the actual rejection path before deciding
whether a source diagnostic applies.

### Missing-method and member visibility checkpoint

The Record rejection paths classify an authored missing-method call only
with the recorded method identity, exact selector and arguments, a valid
receiver term, and no synthetic call-site marker. A selected private
method instead uses the failed visibility check and the authored call.
The raw visibility helper retains its previous diagnostic and domain.

For the 13-input replay, check and AOT each produce 12 Source failures,
while ORC produces nine demanded Source failures and three successful
undemanded runs. The synthetic factory shape in
mid_source_state_unchecked_factory remains Unclassified in all three
modes. Classify it with authored factory construction, preserving the
separate Lower origin for rewritten expressions.

The two compiler-internal selected-call privacy fixtures now use typed
inputs and test one private API each. Their existing goldens pass in check
and AOT. In each isolated mutation, exposing only the targeted API made
its fixture pass. Three successful source controls passed check and ORC,
and the change passed independent re-review.

[Producer replay](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-missing-method-producers.json).

### Binary arithmetic witness rejection checkpoint

A diagnostic-only probe places all 12 check/AOT and nine demanded ORC
failures in the existing arithmetic-legality rejection. Lower now retains
the exact arithmetic operation and operand IDs for written infix and
compound assignments. The checker requires that receipt, the published
operator template and its exact result recipe, and available receiver and
right operand terms before attaching Source. The operator template writer
is module-private, and raw template replacement revokes source publication.
The failure path does not repeat witness lookup.

The final candidate matches the baseline stderr, exit and terminal channel
across all 36 executions. Check/AOT each report 12 Source, and demanded
ORC reports nine Source. Three undemanded ORC inputs still succeed. An
isolated build with source-operation publication suppressed produces eight
same-diagnostic Unclassified failures and one unchanged lazy success
across three controls. Five successful operator and compound-assignment
controls pass check and ORC. Independent re-review found no remaining
blocker for this slice. This does not extend to ambiguous Pending causes
in other selection paths or to comparison, unary, and synthetic operators.

[Producer replay](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-arithmetic-rejection.json).

### Construction and named factory checkpoint

Compiler f5fd1c7c retains the exact written construction and source location.
Authorized contextual typing, default completion, and named rewriting refresh
the receipt only when the incoming expression still matches. Default factory
visibility requires the loaded lexical site and the selected nominal owner.
Named factory failure also validates the retained rewrite serial and original
argument payload. The public raw visibility path keeps its prior domain.
Default-field ranges retain the arena's existing immutable-slice contract.

Check and AOT each classify all 12 previously Unclassified fixtures as
Source. ORC classifies 11 reached refusals and keeps the undemanded helper
successful. All 36 runs retain identical stderr, status and terminal
channel. Six positive construction controls pass check and ORC. Same-ID
Make and Method replacement was checked in a native origin control, and a
named argument-pool mutation kept the original refusal Unclassified.
Independent re-review found no blocker within the supported boundary.

[Replay and controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-factory-rejection.json).

### Declaration call-access checkpoint

Against 34b75f5a the 11 receiver overlaps went through declaration access
in check/AOT and all six reached ORC cases. Five ORC cases were undemanded.
An isolated declaration-only prototype also made the six borrow overlaps
Source in check/AOT and the three reached ORC cases. Across the 51 runs,
stderr, exit status and terminal channel were identical to baseline.

The prototype was not adopted. Independent review found a falsifier by
inspection: cache a valid disjoint call via `MidFunctionTemplates.body`,
replace its canonical argument to alias the read receiver, and request that
body through a fresh `DeclarationBodyRequests`. A genuine symbolic key still
exists, so key attribution alone cannot classify the mutated operands.
The native probe reproduced the counterexample: the first declaration
request accepted the disjoint source; a fresh request on the changed cache
returned typed ConflictingReceiverAccess with Source instead of Unclassified.
The repair must tie
the conflict to the operands emitted by the source builder and retain the
typed local-access error. Check both the raw verifier and cached-request
boundary, including preservation of ordinary disjoint source calls.

[Probe replay](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-call-access-rejection.json).

A second prototype captured the finding while the builder still owned newly
lowered operands. All 51 comparisons passed and the native cached-argument
mutation returned Unclassified. The prototype remains exploratory. Review
found a public write path for the receipt and repeated CFG/access scans of
successful bodies. A numeric canonical body ID alone is also insufficient
proof across sessions. Preserve the result through a sealed builder/request
boundary with one ordinary declaration access evaluation; keep existing raw
verifier input as a separate boundary to exercise. The exact authored and
cache-mutation checks belong together in the declaration-demand fixture.

Compiler 82fe7185 uses one local access scan for normal declaration
requests. Its fresh path consumes its own builder result; the raw analysis
keeps its own unclassified result. On a cache-hit conflict, the request
replays the frozen source into an isolated arena and compares the receiver
and argument modes and storage places as well as the call site and conflict.
Both request and template caches check source session before reuse. Their
zero-argument factories no longer expose private cache initialization.

All 51 comparisons passed again. The native declaration-demand fixture
covers fresh and warm source conflicts, disjoint-to-conflicting mutation,
a same-kind conflict with different storage roots, wrong-session caches,
and retry after rejecting a foreign template. Independent re-review found
no further scoped blocker. Formal self-host and full-suite verification
remain pending for this revision.

### Associated declaration bounds checkpoint

Baseline a01aa74e returns Unclassified for ten associated declaration bound
refusals in each of check, AOT and ORC. The missing-proof branch in
`checkAssociatedBounds` is the producer. An isolated prototype authenticated
the selected binding and trait clause, matching all thirty baseline messages,
exit statuses and channels while reporting Source.

Independent review identified dependencies also present in the query: sibling
associated outputs, target arguments, and local declaration assumptions. A
native probe changed only the sibling `Item` binding used on the right of
`Cursor[Item = Item]` and obtained Source from the direct recheck although
the original List implementation was valid. This falsified the prototype.
The next candidate must separate a private, fresh source-declaration
admission from raw rechecks, including the early callable-form path.
Check native mutation plus normal diagnostic and valid conformance controls.

[Replay and native counterexample](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-associated-bound-rejection.json).

Compiler d1eb1dc9 constructs Comp inside new owned frontend entry points.
Only that private path supplies SourceAdmission to the associated-bound
query. Caller-owned analyzers and public rechecks use Raw. The mode also
passes through early callable-form evidence and parent recursion. The old
public callable evidence signature remains as a raw wrapper.

Final candidate retains diagnostics/status/channel across all 30 original
runs. Added defaulted and inherited-parent witness controls pass all four
check/AOT/ORC/gen modes. Four positive fixtures pass check and exact ORC
outputs. The native domain fixture verifies healthy List, changed sibling
output, and prepopulated raw state; its native build precedes the final
compatibility-wrapper restoration. Source entry structure passes its
architecture check. Final independent re-review found no scoped blocker.
Formal self-host and whole-suite gates remain pending.

### Free call applicability checkpoint

Baseline c64b0c94 reproduces ten unclassified free-call refusals in check
and AOT, and three reached ORC refusals. Seven ORC helpers remain
undemanded and successful. An isolated authored Call/Arg receipt prototype
preserved stderr/status/channel in thirty runs and classified the reached
refusals as Source.

The prototype was not adopted. Independent source review identified a
single-field counterexample to execute next: a valid authored free call
can receive CachedCallee.NoStaticCallee through public typeCache. The
resolver then skips selection, and the unchanged written-call receipt
misclassifies its failure as Source. Attribution must include the
selection-failure producer. The prototype also added an owned argument
array per authored free call; its performance cost has not been measured.

[Replay and remaining control](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-free-call-rejection.json).

The single-field counterexample is now executed natively. A healthy copy of
the same admitted source accepts `accept(value: 1I64)`. Changing only that
call's `typeCache.callee` to NoStaticCallee before body preparation causes
the receipt prototype to return the original refusal as Source. The next
repair must retain the actual negative selection producer, and distinguish
freshly established absence from a cache assertion. The source text and
native stdout are preserved in the linked evidence.

Compiler abb4d895 issues a negative-selection receipt only after the resolver
actually queries visible free functions and finds none. Failed consumers
check the authored Call shape, original argument range, source owner and
retained argument fields. A raw NoStaticCallee assertion cannot issue it.
Successful calls retain only a scalar origin; argument copies are limited
to actual missing selections.

All thirty original comparisons preserve stderr/status/channel; check/AOT
each report ten Source failures, ORC reports three and retains seven lazy
successes. Native entry controls pass for repeated authored refusal and the
healthy-call cache mutation. Five additional native controls exercise the
classifier directly for altered owner/Arg/parent, raw copy and synthetic
registration. They are helper-boundary tests, not full entry replays.
Closure shadowing and a generic default witness pass check and exact ORC.
Independent final re-review found no remaining scoped blocker under the
immutable declaration/AST payload contract. Formal self-host and broad
suite validation remain pending.

### Comparison checkpoint

Compiler 7f1647a8 registers the six authored comparison operators in the
existing binary-origin producer and uses the arithmetic attribution check
at the definite compareNeedsTrait refusal. All 27 baseline comparisons
preserve text/status/channel. Seven check/AOT refusals and four reached
ORC refusals are Source; three ORC cases remain undemanded successes.
The isolated carrier with source operation publication disabled keeps
all refusals Unclassified. Three positive fixtures pass check and exact
ORC output. Independent source review found no blocker for this branch.

Two original cases remain Unclassified: match_value_pattern_type uses
a generated comparison and nested_array_noeq fails at selected operator
bound obligations. These are still required work within this task.
Formal self-host and whole-suite gates remain pending.

[Replay and publication control](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-comparison-rejection.json).

Compiler 47f4f342 also transports authored binary provenance when a selected
operator's implementation bound has no proof. It reuses the original
operator diagnostic and its location. Final comparison replay has eight
Source failures in check/AOT and five reached ORC failures; generated
match_value_pattern_type remains Unclassified. All 27 text/status/channel
comparisons pass, source-publication-disabled failures remain Unclassified,
and three successful check/ORC controls pass. Independent review found no
scoped blocker. Pending operator routes and formal final validation remain
outstanding.

Compiler 6c0de400 retains authored value-pattern row identity, value
expression and original offset. Record can authenticate the generated Eq
only against that retained row; raw arm copies have no authority.
All 27 comparison replays preserve exact baseline stderr/status/channel,
with nine Source refusals in check/AOT, six reached ORC refusals and three
undemanded successes. Four positive value-pattern fixtures pass check and
exact ORC output. An isolated carrier copies the same arms through raw
pushMatchArms: three modes retain the refusal reason/status/channel as
Unclassified. Its copied row uses fallback line 1, recorded separately from
the authored exact-location replay. Independent source review found no
scoped blocker; legacy value-AST lowering was inspected, not independently
executed in this increment. Formal final gates remain pending.

### Source-bound ambiguity checkpoint

Nine baseline cases comprise four viewed-constraint queries, four general
pattern queries and one instantiated proof query, as verified by isolated
producer markers. Compiler 7d2e9878 preserves the ambiguous result at the
saved call-constraint consumer and applies its existing source receipt.
Found/Missing behavior and the single proof query remain unchanged.

All 27 comparisons retain baseline text/status/channel. Four check/AOT
and three reached ORC refusals now have Source. The publication-disabled
carrier keeps all refusals Unclassified. Three valid proof-path controls
pass check and exact ORC output. Independent review found no scoped blocker.
Four general pattern consumers and one instantiation consumer remain
required work. Formal final gates remain pending.

[Replay and producer trace](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-bound-ambiguity-rejection.json).

Compiler 5deeecc6 forwards the saved call site through first-concrete
source-bound checking, including interface evidence replay. The existing
ambiguity classifier authenticates the site; the raw helper's default
remains unclassified. Five check/AOT and four reached ORC cases now return
Source. All 27 comparisons and source-publication-disabled controls pass.
Three source/interface positives pass check and exact ORC output, and
independent source review found no scoped blocker.

The internal fixture interface_boxing_conditions imports the compiler;
its check hit a 30-second diagnostic O0 limit. It is not counted as
validated here and still needs native/full validation. Four general
pattern-query consumers and formal final gates remain outstanding.

Compiler 3c6c13b1 closes the four general-query consumers. Additional
isolated instrumentation showed all four originate at selected static
member admission, including the fixtures whose names mention boxing.
The written member wrapper passes the original lookup origin. Admission
authenticates Method/ExtMethod selector and argument range through the
existing source marker; the public raw helper preserves its old signature
and default Unclassified behavior. The proof query is still performed once.

All 27 replays preserve exact baseline text/status/channel, now with nine
check/AOT Source refusals, four reached ORC refusals, and five undemanded
successes. An isolated omission of lookup origin restores Unclassified
for exactly those four. Three successful member-selection controls pass
check and exact ORC output. Independent source review found no scoped
blocker. Normal selected-member origin checks are bounded but performance
has not been measured; formal final validation remains pending.

### Immutable receiver checkpoint

Compiler 435be989 threads the saved method operation index to a private
receiver checker. Immutable refusal authenticates source publication,
recipe/site/expression, original Method/ExtMethod receiver and argument
range. The public raw receiver checker keeps its signature and no origin.
All 24 baseline text/status/channel comparisons pass. Seven check/AOT and
six reached ORC refusals are Source, one lazy helper remains successful.
Source-publication-disabled refusals remain Unclassified. Three mutable
receiver fixtures pass check and exact ORC output; independent source
review found no scoped blocker. Generated index_immutable remains required
work. Formal final gates are pending.

[Replay and publication control](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-immutable-receiver-rejection.json).

### Generated index-write origin checkpoint

Compiler 4fd1f1d0 retains a private receipt only at five source assignment
lowering entry points, then authenticates its synthetic serial, receiver and
argument range against the published source call. Public raw index builders
remain without source authority. All 24 immutable-receiver comparisons retain
exact stderr/status/channel; check/AOT eight and reached ORC seven refusals
are Source, with the same one undemanded ORC helper succeeding. Three mutable
index fixtures pass check and exact ORC output (six executions).

The new native index_write_failure_domain fixture prints ok: ordinary source
refusal is Source while replacing the generated call using the public raw
builder yields the identical refusal with Unclassified. Its File resource
input loads ambient standard declarations and uses a U64 index. Earlier
fixture setup failures are not counted as RED or product failures.
Independent review found no scoped blocker, including the source/raw contrast.
A public signature regression from the prior ambiguity increment is repaired:
staticMemberResolution keeps its original public signature; source origin is
accepted only by its private delegate. Comp-importing native fixture compiles.
Formal final gates and com-yeua overall remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-immutable-receiver-rejection.json).

### Call-inference producer investigation

Eight existing fixtures remain Unclassified across all 24 check/AOT/ORC
executions, with exact baseline diagnostics/status/channel retained. A separate
instrumented compiler pins all eight check refusals to
checkRecordedCallLiteralArguments's Incomplete state, rather than the later
checkCallTemplateTypeArguments consumer. selectedCallParameterState currently
uses the same state for malformed saved ranges/arity and genuine unresolved
inference slots. Source publication alone cannot classify both as Source.
Next repair must preserve source-owned negative inference evidence, contextual
completion, and a raw healthy-template-to-incomplete mutation contrast. No
repair or completion is claimed by this investigation.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-call-inference-investigation.json).

Call-inference repair scenarios: preserve the eight CLI refusals and positive
contextual inference; report authored incomplete source as Source through
repeated body requests; preserve the same error as Unclassified after public
raw replacement of a healthy open source template with unresolved slots,
wrong arity, or invalid pool range. Reuse the private source publication and
recipe identity rather than storing another copy of selection/inference data.
Before implementation, the new native fixture aborts specifically at
"source inference lost its origin" with the fixed 4fd1f1d0 candidate;
preparation and native build both succeed. Product and raw controls are pending.

### Incomplete call inference origin checkpoint

Compiler b7d4c530 transports the source origin on the transient Incomplete
parameter state. Only the recorded reader can pass a private saved operation
index. An unresolved zero slot requires a valid saved substitution and exact
source publication/recipe/site/expression identity. Malformed arity/range or
nonzero invalid type references remain Unclassified; public raw query and
raw template replacement cannot grant Source. Complete substitutions avoid
provenance checks; the pool is scanned once and no parallel fact store is added.

All eight fixtures pass exact baseline stderr/status/channel comparison in
check/AOT/ORC (24 executions), now Source. Normal generic array inference,
associated result context and provided default forwarding pass check and exact
ORC output (six executions). New native fixture prints ok: cached source
refusal, healthy body, and raw zero/arity/range/invalid-TypeRef contrasts.
Independent review's missing invalid-TypeRef control was added and executed;
no further scoped findings remain. Broad/final gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-call-inference-rejection.json).

### Post-inference finite rejection refresh

Pinned b7d4c530 diagnostic carrier replays the 498 surviving previous
non-Source flat rejection inputs with --check. Candidate and every input hash
remain unchanged. Results: Source144, Unclassified350, Internal1, signal2,
accepted1. No transport timeout/error. Previous Source672 inputs are not
revalidated by this replay. The retired unique_shadow_cliff_use fixture was
removed in 747602af and is explicitly excluded, not counted as a pass.

Internal blanket_headless remains assigned to com-wka4. Both O0 signal cases
are the already recorded resource cases; neither counts as Source. The accepted
polymorphic_recursion check also succeeds with the prior 4fd1f1d0 candidate;
both candidates' AOT retains its identical unsupported-polymorphic-recursion
refusal. No new acceptance regression from the inference repair is established.
This is a diagnostic refresh, not a full suite or task closure.

[Current groups, input hashes and mode comparison](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-post-inference-classification-refresh.json).

### Duplicate requirement origin scenarios

Reuse the private fresh-owned frontend admission boundary used for associated
bounds, generalized as FrontendDeclarationOrigin. Preserve all public raw
checker/analyzer signatures and Raw delegation. Add Source only directly after
callableDeclarationConflict returns true; propagate its failure unchanged.
Do not retain the origin on Comp or reconstruct trust from public mutable
sourceTypeUses / traitReqPool, and do not add requirement snapshots.

Scenarios: six existing duplicate-requirement fixtures in check/AOT/ORC, with
exact baseline diagnostic/status/channel; source failures through both owned
frontend constructors; same input through both caller-owned analyzers remains
Unclassified; healthy owned Comp succeeds, public requirement mutation makes
a duplicate and raw checker/admission retains Unclassified, and a fresh caller-owned analysis with a preseeded orphan requirement retains Unclassified. Keep
distinct requirement positives and existing associated-bound source/raw native
controls. The native RED on the prior b7d4c530 carrier is exactly
"source duplicate lost its origin" (exit134); setup succeeds.

### Duplicate requirement source origin checkpoint

Private FrontendDeclarationOrigin generalizes the existing fresh-owned
associated-bound boundary. Both owned constructors create Comp internally;
loadFrontendDeclarations passes authority only to private declaration admission
and duplicate-requirement checking. Public analyzers and both public checkers
retain their signatures and Raw delegation. Source is emitted only when the
shared callable conflict query returns true, without changing propagated errors
or retaining authority on Comp. No extra signature sweep or receipt table.

Six existing duplicate fixtures retain exact diagnostic/status/channel in
check/AOT/ORC (18 executions), now Source. Three distinct requirement/structural
overload positives pass check and exact ORC output (six executions). Native
trait_requirement_failure_domain prints ok: owned entry failures, both raw
analyzers, healthy owned state then public requirement mutation, public duplicate
and admission rechecks remain distinct. The separate fresh preseeded orphan
control tests raw entry authority, not the semantic validity of that orphan.
An initial never-successful fixture incorrectly reinitialized an already
initialized Comp; that invalid test setup was removed, not counted as a product
failure or an accepted API requirement. Associated_bound_failure_domain also
prints ok after the private enum rename. Architecture guard passes. Independent
review and correction review found no remaining scoped issue. Formal final
gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-trait-requirement-rejection.json).

### Witness-result mismatch origin scenarios

Classify only the actual callableResultTypesEqual false branch in
checkConformanceMethodBounds: implementation and factory result mismatch.
The owned source conformance sweep passes existing private declaration origin;
public checker remains Raw, with unchanged signature. Preserve all signature
read/parameter/constraint failures and other mismatch reasons unchanged. No
origin on Comp, repeated proof lookup or parallel signature snapshot.

Scenarios: nine existing ordinary/associated/provided/unit/fallible factory
rejects across check/AOT/ORC; both owned and both caller-owned input analyzers;
healthy owned Comp then a real witness-ID pool mutation to a different
well-typed same-selector method with the wrong result, verified through both
public method-bound and conformance checkers as Unclassified. Include normal
provided/associated/via/factory/unit-equivalence positives. Baseline native
setup succeeds and fails at "source witness result lost its origin" (exit134).

### Witness result origin checkpoint

The owned conformance sweep now passes its existing private declaration
origin to method-bound admission. The public checkConformanceMethodBounds
signature remains unchanged and delegates Raw. Only a confirmed false result
comparison emits Source for implementation/factory return mismatch; signature
reads, constraints and all other mismatches retain their original behavior.
There is no new receipt table, repeat comparison, or authority stored on Comp.

Nine existing rejection fixtures retain exact stderr/status/channel in
check/AOT/ORC (27 executions), now Source. Provided/associated results, via Self
results, fallible factories and implicit/explicit unit equivalence pass check
and exact ORC output (eight executions). The new native fixture prints ok:
owned two-entry Source failure versus caller-owned two-entry Unclassified,
then a successful owned Comp whose actual witness link is replaced with the
well-typed unrelated Other.make of a different result. Both public local and
whole-conformance checkers preserve the same mismatch as Unclassified.

The initial internal fixture wrongly asked a successful owned admission to
publish its constraint evidence again. Removed that unsupported setup demand;
owned constructor success remains the healthy control. The mutation refusal
returns before publication and does not claim re-admission is supported.
Independent source/correction review found no remaining scoped issue.
Formal final gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-witness-return-rejection.json).

### Witness factory-kind and parameter-ownership scenarios

Use existing private declaration origin only on confirmed factory-kind
(isFactory / isAnonymousFactory) and argument ownership (inout/move/borrow)
mismatches. Keep calling convention, result, Missing, read/constraint and
publication errors unchanged. No added state, lookup, comparison or loop.

Two existing fixtures cover factory-as-associated-method and default-argument
ownership mismatch in check/AOT/ORC. New native source/raw tests cover each
reason through both owned constructors and both caller-owned analyzers. Healthy
owned state is mutated via the real witness-ID link to a well-typed same-selector
function of wrong kind/mode; both public checkers must preserve the exact reason
as Unclassified. Preserve ordinary default forwarding, factories and inout
witness positives; no successful re-publication of completed evidence required.
Native baseline setup succeeds and fails specifically at
"source witness contract lost its origin" (exit134).

### Witness factory-kind and parameter-ownership checkpoint

Only the two confirmed mismatch branches select Source/Unclassified from the
existing private declaration origin. Calling convention, result mismatch,
Missing, all fallible reads/queries and publication behavior are unchanged.
The comparison order and public checker signatures are unchanged; no new
state, scan, lookup or declaration copy.

Two existing fixtures retain exact stderr/status/channel in check/AOT/ORC
(six executions), now Source. Default forwarding, fallible factories, generic
inout witnesses and via forms pass check and exact ORC output (eight executions).
New witness_contract_failure_domain native fixture prints ok. Each reason has
owned-two-entry Source and caller-owned-two-entry Unclassified controls, then
healthy owned admission plus a real witness-ID link mutation to Other.value
(non-factory) or Other.act (inout argument). Both public checkers preserve the
exact mismatch as Unclassified. No successful re-publication is requested.
Independent design/source review has no remaining required finding.
Formal final gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-witness-contract-rejection.json).

### Missing conformance witness scenarios

The final !matched branch in method-bound admission is distinct from supertrait
lookup Missing. Header/label/type comparisons exhaust the finite witness list;
requireAdmittedRawRequirement/readRequirementParameter errors propagate via try.
Direct structural equality and grounding/projection normalization have no
numeric cutoff on this path. Projection cycles preserve symbolic terms.
com-pq5j's capped supertrait member searches remain outside this change.

Only the final no-witness diagnostic receives the existing private declaration
origin. Preserve raw public entries and all previous query failures. Scenarios:
five flat reject fixtures across check/AOT/ORC; empty and wrong-signature source
through both owned/caller-owned entries; healthy owned conformance then actual
witness link mutation to wrong selector or same selector/different nominal type
through both public checkers; erased source signature map retains the reader's
original non-Source diagnostic rather than becoming Missing. Positive complete
overloads, default forwarding, via and Chain conformance remain required.
Before implementation, all15 process refusals were Unclassified and native
fixture failed specifically at source missing witness lost its origin.

### Missing conformance witness origin checkpoint

Only final !matched refusal now uses existing private owned declaration origin.
Five fixtures retain exact stderr/status/channel in check/AOT/ORC (15 executions),
now Source. Complete overloads, default forwarding, via forms and Chain
conformance pass check and exact ORC output (eight executions). New native
missing_witness_failure_domain prints ok: empty/wrong-nominal signature source
owned-two-entry Source versus caller-owned-two-entry Unclassified; healthy
owned conformance followed by actual witness link changes to a different
selector or same selector/different nominal parameter type; public checker
both entries preserve Missing as Unclassified. Erasing the public source-use
map after restoring the original link preserves the reader's original
selected requirement has no authored signature error as non-Source.

Independent plan/source review confirmed that this direct matcher has no
numeric cutoff and propagates read/recipe errors. The separate capped
supertrait search issue com-pq5j is unchanged. No added scan/state/snapshot.
Formal final gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-missing-witness-rejection.json).

Next investigation pins four source calling-convention mismatches (receiver
readonly/inout in both directions, instance/associated, sync/async) to the
existing sibling refusal. All four check processes currently return the exact
calling-convention diagnostic with Unclassified; they are not repaired by this
checkpoint. [Probe](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-calling-convention-investigation.json).

### Calling-convention mismatch scenarios

Only the confirmed isAssoc/selfInout/selfMove/isAsync mismatch branch receives
existing private declaration origin. Preserve public Raw API signatures, prior
read/query failures, other comparison branches and evidence publication.
Four new flat fixtures pin receiver readonly/inout in both directions, instance
versus associated, and sync versus async: all12 baseline process runs refuse
with the same message but Unclassified. Native baseline reaches the exact
source convention mismatch lost its origin assertion (exit134).

Native controls use File resources with the actual std root for Promise and
exercise each source through owned2/raw2. A separate healthy Text-owned state
with one user conformance has Mutable/inout, Associated/assoc and unique
Moving/move receiver entries. Each actual witness-link mutation is asserted and
restored, and public checker both entries must keep the exact reason as
Unclassified. No successful re-publication is requested. Preserve normal
receiver/associated/async/default/via positives and previous result failures.

### Calling-convention mismatch checkpoint

Only the confirmed calling-convention predicate now selects Source/Unclassified
from existing private declaration origin. Four flat fixtures retain exact
baseline stderr/status/channel in check/AOT/ORC (12 executions), now Source.
Normal async instance dispatch, via/associated forms, inout receiver default
forwarding and generic default forwarding pass check and exact ORC output
(eight executions). Native calling_convention_failure_domain prints ok.

Its four File+std source cases each exercise owned2 Source/caller-owned2
Unclassified. Separate healthy Text state has one user conformance; its real
witness ID is changed to registered Mutable/inout, Associated/assoc and unique
Moving/move receivers with asserted flags. Both public checkers keep the same
calling-convention refusal as Unclassified; each mutation restores the original
link. No successful re-publication is requested. Independent plan/source review
has no remaining required finding. No new state, scan, lookup or snapshot.
Formal final gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-calling-convention-rejection.json).

### Implementation-bound classification scenarios

The first implementation-bound consumer owns refusal when an implementation
requires a proof not guaranteed by its requirement. Cover successful query
results Missing and semantic Ambiguous, preserving acceptance and exact reasons.
Fresh owned Frontend entries classify Source; public caller-owned entries and
public proof interpretation remain Unclassified, including SourceAdmission demand.
Query Err/Limit must propagate before interpretation; no failure remapping.
The second retained-evidence and publication failures remain unchanged.

Two source fixtures exercise check/AOT/ORC. Native controls cover owned2/raw2,
actual witness-link mutations, public Ambiguous interpretation, and equal, weaker,
inherited and exact-direct-premise positives. Baseline six process outcomes are
Unclassified; native exits134 at `source implementation bound lost its origin`.
Query error preservation is a structural check, not an executed resource-limit
claim; resource/re-entry work remains com-pq5j.

### Implementation-bound checkpoint

The first consumer now classifies Missing and semantic Ambiguous from a
successful query using private declaration origin. Query Err/Limit returns
before interpretation; public interpretation remains fixed Unclassified.
No query, scan, retained state or evidence construction was added.
Six check/AOT/ORC refusals retain exact stderr/status/channel and become Source.
Native source/raw, witness mutation and positive controls print ok; three
existing trait constraint fixtures pass check and exact ORC output (six runs).
Frontend input boundary structural test passes. Independent static review found
no required defect; unrelated indentation was reverted. Its public interpreter
control uses fabricated data, separately from actual query ambiguity controls.
No executed Limit control is claimed. Full gates and com-yeua remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-implementation-bound-rejection.json).

### Direct supertrait proof classification scenarios

Only successful direct supertrait query outcomes Missing/semantic Ambiguous
are classified by existing private declaration origin. Keep the public
prepareConformanceSupertraits entry Raw; both existing private admission callers
forward origin. Preserve normalization, retained-evidence and publication failures
and query Err/Limit. No new state, query, scan or proof selection.

Nine source fixtures (eight existing Missing, one new Ambiguous) refuse with
Unclassified in all27 baseline check/AOT/ORC runs. Native scenarios cover owned2,
caller-owned2 and public prepare/full-check after unsuccessful raw admission,
including a provided callable form; healthy parent/child control retains and
reuses nonempty supertrait evidence. Existing projected/generic/callable-form
positives remain controls. Independent plan review found no required violation.

### Direct supertrait proof checkpoint

Existing public prepare remains Raw; two private admission callers pass the
existing origin to the direct query consumer. Missing and semantic Ambiguous
classify Source for fresh owned admission only. Nine source fixtures retain
exact stderr/status/channel in check/AOT/ORC (27 runs), now Source. Five existing
projected/generic/provided/default/via controls pass check and exact ORC output
(10 runs). Native source/raw/public recheck and saved-parent controls print ok.

Independent review required nonempty parent evidence checks; each clause now
requires a stored row and valid proof ID, with exactly one nonempty clause in
the control. Failed raw admission must publish none. A never-passed extra
control's trait-body syntax was corrected to valid default-argument callable
form syntax; that setup failure is not GREEN. Independent re-review confirms
this reaches callable-form parent preparation and has no remaining finding.
Query Err/Limit preservation is structural, not an executed Limit claim.
Full gates, com-yeua and phase3 remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-supertrait-rejection.json).

### Next producer boundary: overlapping conformances

Source inspection finds two producers of the same diagnostic, not one failure
to wrap at the end: registration (Registration.pw checkConformanceRegistration,
called by registerDeclaredConformance from legacy and Syntax impl lowering) and
post-admission overlap (checkAdmittedConformanceOverlap, called by
Frontend.admitFrontendNominalDependencies). The latter already has a private
origin-aware caller; registration needs origin forwarded through the actual
Syntax top-item/published-item/impl private path. Public raw lowering and
registration APIs must remain Raw, including the legacy AST path. Do not infer
source origin from public SourceTypeUses, selected IDs or the shared message.

Before changing code, establish which producer the six remaining overlap
fixtures reach; cover registration and normalized projected overlap separately,
public/raw controls and a disjoint positive. Preserve structuralOverlap
AnalysisLimit as Limit via its existing try, not as source overlap. No change
to acceptance or new proof/scan is intended. This is a restart investigation
record, not an approved implementation or completed test.

### Overlap classification scenarios

Isolated diagnostic tracing of the six current refusals identifies registration
for extension_conformance_generic_overlap / extension_duplicate_conformance,
and post-admission for conformance_dependent_receiver_overlap,
conformance_receiver_projected_overlap, conformance_target_projection_overlap
and impl_receiver_projection_overlap. All18 baseline check/AOT/ORC runs are
Unclassified with complete terminal reports and the expected overlap reason.

Forward existing origin through private Syntax top-item/published/impl and
registration paths; all public entries and legacy lowering remain Raw. Apply
origin only at the three overlap refusal returns, not normalization or Limit.
Native scenarios: fresh owned2 versus caller-owned2 for direct/pub/extension,
projected target and receiver; public registration and Syntax top/published/impl
rechecks on actual IDs; legacy AST lowering on parsed source; explicit raw
duplicate arena followed by public admitted checker; disjoint namespaces and
distinct trait arguments remain valid. Producer trace is diagnostic evidence,
not a semantic candidate. Normal source/native controls and independent review
are required before recognizing this checkpoint.

### Conformance overlap checkpoint

Private origin now reaches both producers through Syntax lowering and nominal
admission. Public APIs and legacy lowering retain Raw; no origin state, scan
or query was added. Three overlap returns use the private diagnostic producer.
The six fixtures keep exact stderr/status/channel in 18 check/AOT/ORC runs and
become Source. Six existing disjoint/projected/extension/provided controls pass
check and exact ORC output (12 runs). Native owned/raw, public registration,
public Syntax/legacy lowering and post-admission raw injection controls print ok.

New native setups were corrected before GREEN: public lowering is tested at
its pre-admission phase, separately from owned canonical registration; manual
Comp constructions reserve TypeRef sentinel before lowering. Setup failures
were not counted as RED/GREEN; the original Source-domain RED assertion is
unchanged. Independent review confirms matching stages, source identities and
restoration contracts, with no remaining required finding. Structural overlap
AnalysisLimit preservation is checked structurally, not an executed Limit claim.
Full gates, com-yeua and phase3 remain open.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-conformance-overlap-rejection.json).

### Next ownership producer inspection

The eight finite use-after-move refusals share Verify/Expr.pw's Ident branch:
recordIdentBinding establishes the local and verifyIsMoved reads mutable
cur.verifyMovedIdx before constructing an Unclassified diagnostic. A source
expression marker alone is insufficient authority for this state-dependent
refusal: public raw verifier callers can supply or alter ownership state.
Trace the owning verification entry and its moved-state production before
choosing a private origin/capability boundary. Preserve checked dead-code and
branch-merge behavior; do not alter ownership acceptance merely to classify
failures. No ownership classification implementation is claimed here.

### Ownership refusal transport plan

The 8 current use-after-move fixtures produce 23 Unclassified refusals and one
unused ORC success across24 baseline executions. A private lexical preparation
helper is not source authority: public raw prepareLexicalBody reaches it.
The existing CompilerSession does own private Comp, but forwarding a detached
public token into Frontend would permit owner/input substitution.

Use a closed structured CompileDiagnostic sum: ordinary rendered Report versus
a dedicated semantic refusal. No parallel message/cause authorities. The owning
request consumer generates Source from its own typed result; raw APIs merely
render the semantic refusal Unclassified. Keep its canonical cache variant, not
a flattened Raw Report. No diagnostic-text classification or global source flag.
Independent source investigation and plan review supports this arrangement;
reorganizing CompilerSession/Backend modules is unnecessary.

First isolate a behavior-preserving Report/accessor migration. Existing
DiagnosticValues, FailureDomains and DiagnosticNotes are GREEN baselines. Preserve
all constructor labels/defaults, severity/domain/location/message/notes and
terminal failure transport. Internal test field reads migrate to accessors, not
new expectations. Then add the ownership semantic variant and owned consumer
projection with Source/Raw, corrupt cursor, cache re-request, generic, lazy,
branch/dead-code and positive controls. Both stages require independent review.

### Diagnostic scratch input integrity correction

During the Report migration, self-compilation rejected an unchanged constructor.
The cause was the diagnostic build's delta-only copy: abandoned prototype
changes survived in SourceTypeAdmissions.pw (extra required member) and Mid/Ir.pw
(old sourceCallConflicts API), because these product files had reverted to the
comparison revision and were no longer copied. The rejection also reproduced
without the Report sum; it was not evidence against the new representation.

Replace that scratch copy with a complete source sync and per-file hash equality
assertion before compiling. Prior observations remain recorded but candidates
from this scratch after the prototype edits are not certified exact product
revisions. Revalidate affected native/control scopes on the complete product
source and reconcile the final full gates before task completion. Formal
self-host records used distinct frozen worktrees and are outside this scratch
correction. The Report migration remains WIP until fresh complete-input gates.

### Structured Report migration checkpoint

The Report/accessor migration builds from complete product src (every source
file hash matches), with std contents also matched. Existing DiagnosticValues,
FailureDomains and DiagnosticNotes retain exact status/stdout/stderr. The real
private terminal producer passes25 controls. DiagnosticNotes passes LLVM22
ASan/LSan with explicitly instrumented IR. A temporary runner executes the
latest implementation-bound, supertrait and overlap native fixtures against
this complete source and prints three ok lines; only their entry names change
for import. These three boundary scopes are freshly revalidated.

Independent source review confirms all client changes are five-accessor syntax
substitutions except four constructor order adjustments; unchanged expectations,
constructor defaults, Note fields and leaf DAG. No substitutions occurred inside
string literals. Source authority/ownership acceptance is unchanged in this
first step. Dedicated ownership variant and owned interpretation remain next.
Full gates and performance remain open; previous mixed-scratch observations
are not silently promoted to product revision certification.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-diagnostic-report-values.json).

### Report fixed point and performance follow-up

Standard run20261118T224254-self-host-cdd742 uses verified development carrier
37fefb30 and reaches generation2 equality of LLVM, runtime and successor bytes
(e2360a6d). The input is unchanged. The run nevertheless fails after the third
LLVM output is empty while the compiler exits0; com-x386 retains this existing
output-status observation. Two successful times8.392522/8.330378 are not a
formal median. An older seed carrier c367 first rejected a current type check,
so its failed attempt supplies no timing.

A no-storage alternating diagnostic on the same current source and explicit
current std emits one LLVM hash in all6 outputs. Earlier37fefb30 compiler median
is7.376004; newe2360a6d median7.602993. This proves a difference between those
compilers, not sole attribution to Report (the older compiler predates other
changes). Before adding ownership semantic refusal, build the immediately
pre-Report55b70b6e complete-source optimized baseline and isolate the difference.
The7-second goal remains unmet, not judged difficult/impossible.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-diagnostic-report-self-host.json).

### Performance source review and next comparison

Independent performance review distinguishes facts from hypotheses. Plew's
current enum layout adds a tag word even for one variant (GenericStruct.pw /
Enums.pw); if Err dominates the payload, Result[T,CompileDiagnostic] also grows
one word on success paths. Return ABI stays UnchangedValue. A nonconsuming
Report payload bind produces EnumPayloadCopy and potential whole-report ARC,
but its successful-compile execution frequency and optimized cost are unmeasured.
Defaults already existed in the old struct, so their mere existence is not a
new cost. No sole cause or optimization is adopted from these observations.

The next comparison uses55b70b6e versus180d4c3f, complete fresh source trees,
the same carrier/LLVM/pipeline and one fixed compile input. Record wall/user/sys,
RSS, sizes and LLVM/runtime equality. Separate compiler-runtime difference from
processing a larger source. Examine hot Result return/try/Ok machine code first
if the difference persists, then count getter/factory executions; do not distort
the API or weaken source authority based on speculation. Fresh snapshot file
sets, not delta copies, are required for this comparison.

### Exact Report performance comparison

Fresh Git-archive55b70b6e baseline, identical37fefb30 carrier and LLVM20
pipeline, succeeds with complete input hashes unchanged. Five alternating pairs
on the same current source give7.461869 versus7.664992 seconds; all10 emitted
LLVM hashes and both generated runtimes agree. This isolates a roughly0.20-second
compiler-runtime difference from processing a different source. It is diagnostic
comparison evidence, not a completed formal self-host median.

Independent optimized-IR and final-arm64 review finds some widened Result
returns, but the large `check` IR expansion becomes fewer final instructions
and zero stores. `buildMidCallEvaluation` grows in frame/code size. These static
counts do not quantify dynamic causes; getter ARC is not established as the
primary cause. The report abstraction and authority boundaries remain required.

A fresh isolated diagnostic source changes only buildEnumFromValues initialization
from full zero to explicit LLVM undef. This tests inactive-payload costs; it is
not an adopted product change. Before adoption, audit tag/active-field initialization,
all match/ownership/repack/ABI consumers and zero-sentinel/byte-observation
dependencies; retain semantic controls, ownership sanitizer coverage and
same-input measurement. No verifier or failure classification is weakened.
[Exact evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-diagnostic-report-exact-performance.json).

The isolated inactive-padding diagnostic reached a second optimized compiler
(5770fa52), so its own code reflects the proposed lowering. Alternating5-pair
comparison gives7.711814(product) versus7.640997(diagnostic), roughly0.9%.
Eight existing native enum/Result/try controls and two explicit LLVM22
ASan/LSan controls pass exact expected output. The LLVM output hashes differ
as expected from zero versus undef padding; this is not fixed-point evidence.
The product source remains unchanged and the optimization is not adopted.
Independent consumer review found typed variant-selected ARC/match/repack,
but full active-field count/types/order must be established or enforced before
adoption, including malformed raw Mid controls. The small improvement alone
does not recover the7-second goal. Remaining repeated-work costs still require
measurement; recovery is not judged difficult. Exact record above includes
both generations, the setup-recording error and all control results.

### Performance diagnostic disposition and next bounded probe

The inactive-padding experiment is not adopted. Its raw-Mid safety inquiry
confirmed the independently reviewed enum construction gap com-d607, assigned
to phase-four Mid/LLVM admission without adding a phase-three prerequisite.
Reordered elements are a valid field-index mapping control, not an error. This
small optional optimization does not justify expanding this diagnostic task.

Existing phase traces record7183 lexical function verification events with7183
distinct function indices. Whole-function duplicate verification is not established.
The finite resolveTy performance increment is adopted: use the existing pooled
immutable head instead of acquiring owning TypeRef child arrays, retaining the
same semantic decisions. Latest-source alternating5-pair medians are7.654653
versus7.582012 seconds; all10 LLVM outputs equal each other and the prototype's
initial self-compile output. This is not a formal standard-run median or
successor-binary fixed-point claim. Source/std files exactly match the validated
cd16d25a candidate. Direct native before/after, existing native receiver/generic/
projection controls, two rejection inputs in check/AOT/ORC, legacy zero-nameId
and retained-view-base assertions pass. Independent adoption review finds no
must-fix. Manual TypeHeadResolution documents the direct regression controls.
[Reader evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-pooled-type-head-reader.json).

The adjacent finite reader cleanup also consumes existing canonical head/child
readers in tyRefIsGround, acquires immutable childCount once, and obtains only
nameStart/nameLen inside callableParameterTypeMatchRank's numeric branch.
Complete semantic children, projection failures and rank decisions are unchanged.
Fourteen scoped controls plus actual registered-path native checks pass, and
all10 LLVM outputs on the final source agree with each other and the initial
prototype output. Independent review approves structural adoption. Latest medians
are7.540963 ->7.548907 seconds: no wall-time improvement is demonstrated.
The static TypeRef retain/drop calls disappear from both queried functions,
but this is not dynamic performance or final gate evidence.
[Reader cleanup evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-pooled-grounding-ranking-readers.json).

The7-second objective remains unmet, not judged difficult. Stop speculative
leaf-reader edits as a performance strategy: next isolate remaining aggregate
getter result-copy costs with a minimal program and actual optimized IR before
choosing a broader change. Do not assume the existing argument-forwarding
optimization covers returned temporary projection. Ownership semantic refusal
and this task's final producer-to-consumer/gate work remain unfinished.

### Normal-suite reconciliation after pooled readers

Candidate c6f5542b (product5ff6defd) completed the standard normal suite
20261119T014141-test-d92083 with unchanged inputs and exit1. The harness has399
failures:368classification,16internal run refusals,12internal run aborts,
2structural gates and1diagnostic mismatch. Supervisor397failure events are
a different count. The finite list and comparison limitations are retained in
[normal evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-pooled-readers-normal-suite.json).
Do not infer producer causes from consumer classification labels or attribute
different-source signature changes to the pooled reader edits.

The newly observed source_completion_diagnostics refusal was a missed internal
Report accessor migration. Four reads now use the existing severity/message
accessors; assertions and golden output are unchanged. Fixed-candidate original
check refusal and repaired actual ORC exit0/exact output are retained in
[accessor evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-completion-diagnostic-accessors.json).
Independent neutral review found no must-fix; source/evidence review only, not an
independent execution. Untraced watchdog interruption and an unsupported CLI
flag ordering are not GREEN. AOT and full normal remain uncertified. Other new
signatures and the semantic ownership variant remain open.

The two new structural gate failures were stale probes for the former raw access
helper and pre-forwarding method condition. They now require the source-owning
helper after ownership and before publication, its common access analysis and
source provenance interpretation, and the selected synchronous/async-forwarding
method admission. Both scripts pass, including existing provided-method ORC
output. Four isolated mutations remove required ownership/access/provenance or
async admission checks and are rejected. The ownership mutation removes a call;
order is separately checked by source-position assertions. Independent review
has no must-fix. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-structural-test-reconciliation.json).
No product repair, full-suite pass or phase-three closure follows from these
internal compatibility corrections.

### Declaration access scalar consumer

CPU sampling of c6f5542b mapped callTemplateAt to current body identity. The
declaration request only needs mayHaveStorageArguments, already exposed by
the same owner-aware operation head reader. checkBody now consumes that
scalar projection; owner/session/site checks, conservative defaults, required
ownership and conditional access verification remain unchanged. No new store,
authority or compiler-specific ARC exception.

An exact archived prototype built with carrier37/common LLVM20 pipeline. The
same-source alternating5pairs have medians7.646253/7.621242seconds and all10LLVM
identical; one8.176s after sample is retained. Treat25ms as a small observation,
not certified recovery. Existing head/storage-publication controls emit equal
LLVM in4compiles; unchanged baseline native golden successes are explicitly
reused, not relabeled new execution. Independent review has no required concern
and accepts the structural cleanup. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-declaration-access-head-reader.json).
Formal fixed point,7seconds and task/phase-three closure remain unachieved.

### Compact immutable diagnostic presentation storage

The Report case retains its public DiagnosticReport payload type. That type
privately owns one immutable report in Array value storage; its factory alone
establishes cardinality. Accessors derive the same severity/domain/location/
message/notes. No public Ref, weak identity, nonsendable field, source authority
or parallel presentation/cause store is introduced. The existing private
presentation contract is explicit in diagnostics.md.

The exact archived prototype has matched5-pair medians7.552111/6.975506seconds
on identical fc67841d source, all10LLVM equal. This is diagnostic timing, not an
official fixed point or7-second completion. Creation adds one allocation per
report to reduce the success-dominant Result inline failure width.

Validation includes8before/after-library x old/new-compiler native andLLVM22
ASan/LSan controls; heap-backed message/location/notes escape the report, copied
reports survive owner destruction, Result dictionary removal preserves failure,
notes retain CoW, and any-sendable erasure remains available. Constant-only
String escape tests were strengthened before acceptance. The registered normal
fixture diagnostic_value_lifetime has4native/ASan runs with exact stdout/empty
stderr and equal old/new LLVM. Three unchanged diagnostic rendering goldens and
the actual ProducerFailureDomains native source-cache retry/drain/raw-domain
probe pass. External weak/storage access is rejected in8contrasts.48ownership
CLI outcomes and8domain/input cases preserve primary diagnostics, status and
channel. Both compilers retain7auxiliary ORC missing-module/context errors; this
is not a repair or certification of that existing terminal-refusal path.

Independent adoption review found no required issue. The independently adopted
declaration head reader is not in this prototype binary; the combined frozen
source requires formal/affected final gates. Main, seed and adopted carrier are
unchanged. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-diagnostic-value-storage.json).

The semantic ownership refusal remains next. Preserve compact transport when
adding its canonical owned context; do not reintroduce a large inline alternative
or a duplicate mutable Report merely to carry Source classification. This is a
representation constraint on the already-planned variant, not new task scope.

Sanitizer evidence correction: the first hand-run sanitizer controls omitted
compiler --asan and only checked generic __asan_ presence; those labels were
withdrawn (native results remain valid). Re-generated with --asan, then LLVM22
ASan and sanitizer link/LSan. Four storage controls each contain286actual memory
check calls (267/268inside plew.body.*); the registered two contain271(253inside
plew.body.*). All six sanitizer executions pass. Current evidence records flags,
call counts and the invalidated attempt. Independent review of actual raw and
instrumented LLVM confirms genuine function-body instrumentation, not merely
global/module registration. Full compiler/corpus ASan remains unclaimed.

### Combined formal self-host checkpoint

Standard self-host20261119T035845-self-host-8760ac on95bf9d60 passes with
unchanged inputs. Generation2LLVM/runtime and successor binary match; all three
measured LLVM/runtime hashes agree. Times7.698432/7.067001/7.069988seconds, median
7.069988. The first slow sample is retained. The7-second goal remains unmet,
not judged difficult to recover. This validates the combined diagnostic storage
and declaration head-reader fixed point, not full functional gates or closure.
[Formal evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-compact-diagnostic-formal-self-host.json).


### Semantic use-after-move transport increment

The verifier now returns a compact dedicated cause with session, authored owner,
resolved declaration binding, expression and owned location. Raw caches retain
this variant. Internal session dependencies use private raw cores; public exits
interpret only their own result after session/expression/owner comparison.
General reports are unchanged. Fresh eager/request constructors also interpret
failures before their Comp escapes. No moved-state analysis is repeated.

The baseline eight inputs plus reached/unused generic controls have30old/new
comparisons:28Unclassified refusals becomeSource with identical primary errors,
status and auxiliary ORC messages; two unused lazy cases remain successes.
This first CLI candidate predates the eager-open review correction. The current
source manual native test passes forged cursor, real different owner, foreign
session, invalid expression, raw cache/drain, owned retry, whole and eager cases.
New semantic lifetime and existing report lifetime controls pass native and
proper LLVM22ASan/LSan, including actual Plew body memory checks.

Independent review found and then verified the eager-open correction; no remaining
source must-fix. Final candidate reconciliation, generated layout/performance
and full gates are still pending. This task is not complete.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-ownership-semantic-refusal.json).

The initial semantic candidate regresses the identical-source official-inner
comparison7.189309→7.319353seconds (all10LLVM equal). Investigate aggregate
Result/diagnostic representation and ARC dispatch before final adoption. Do not
weaken source authority or mislabel this as within the7-second objective.

The internal source_closure_publication abort was a stale raw-navigation
expectation: saved owner/expression plus foreign bodyKey was expected to succeed.
The fixture now checks InvalidBlock for that inconsistent identity, then checks
valid minimal navigation consumes prepared metadata and the canonical body's
sourceFunction equals saved.bodyKey. Native RED/GREEN, original golden and
independent contract review are retained. No product admission rule was weakened.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-closure-navigation-fixture.json).

### Opaque cause transport

CompileDiagnostic now owns private fixed-cardinality Array storage of one
closed DiagnosticData sum. Ordinary factory labels/defaults are unchanged;
branch-internal enum observations migrate to the dedicated named factory and
typed optional accessor. The sole cause remains canonical in caches; private
source-owned interpretation is unchanged. Context observation allocates no
extra Array and introduces no reference identity.

Latest72c7f39b baseline/prototype same-source5pairs give7.275936/7.239295seconds,
all10LLVM equal. Representative raw Result[U64, CompileDiagnostic] shrinks24to16
bytes. Treat36ms as a small observation, not demonstrated7-second recovery or
proof that ARC alone caused the prior regression.28Source refusals/two unused
lazy successes and auxiliary ORC messages are identical in60CLI controls.
Manual owner/cache native,6privacy refusals, and native/LLVM22ASan/LSan for
semantic and ordinary report lifetime pass. Fresh candidate emits byte-equal
LLVM/runtime for those executed lifetime controls; execution reuse is explicit.
Independent source/design reviews have no must-fix. Formal/full gates remain.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-diagnostic-cause-value-handle.json).

The remaining new function_completion_type_identity refusal called the removed
viaSignatureMatches helper. All original type/grounding/overload assertions stay;
the final detached comparisons now exercise four actual selected delegation
programs, with exact distinct refusal reasons and both positive contracts.
Fixed-candidate RED, full native GREEN and neutral review pass. The strengthened
divergence case rejects at body checking before the delegation comparison; no
claim is made that it isolates that private branch.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-completion-identity-fixture.json).

## Public surface classification checkpoint

The private surface core retains Exposure separately from existing inference
diagnostics. Only fresh admission interprets Exposure as Source; public raw
rechecks remain Unclassified. [Finite evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-public-surface-refusal.json)
records 42 RED/GREEN CLI pairs, ten positive checks, native authority/retry
controls, and four reached inference-fault controls preserving Internal/location/notes.
Independent source/evidence review found no must-fix. This does not close this
ticket, the full normal suite, or the 7-second performance gate.
