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
