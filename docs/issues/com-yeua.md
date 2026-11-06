---
id: com-yeua
status: in_progress
deps: [met-c1pg]
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
