---
id: met-g2x4
status: in_progress
deps: []
links: []
created: 2026-11-23T13:45:54Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, diagnostics]
---
# Preserve owned source typing-obligation refusals

## Contract and boundary

Own the refusal for an authored expression that cannot complete its required
source type at the source-body publication boundary. Follow
[body checking](../design/body-checking.md) and
[diagnostics](../design/diagnostics.md); message text is never authority.
Parent: com-yeua, within phase three. This is not inference expansion.

## Work and guarantees

1. Trace recordSourceTypingObligation -> checkSourceTypingObligations ->
   source-owner failure retention -> private owned observer -> CLI consumers.
   Separate an actual unresolved source obligation from missing/corrupt facts,
   unfinished declaration resolution, foreign ownership and synthetic input.
2. Establish RED on the fixed 5bafacff/2b5475 carrier for the five existing
   source_typing_* empty-array negatives (direct, wrapped, nested, discarded,
   global). Preserve diagnostic, location, normal exit and rejection semantics.
3. Add producer-owned negative evidence only for justified authored refusals;
   preserve Raw/Internal/Unclassified and dependency failures. Never mark all
   Pending, Unrecorded or missing facts Source. No catch-and-relabel adapter.
4. Cover raw/owned, owner/session/operation mismatch, cached retry/drain,
   reached versus unreached lazy bodies, whole/eager, valid typed-array controls
   and global publication separately. Preserve prior accepted type facts.
5. Review the producer-to-consumer path independently; validate affected modes,
   native lifetime where metadata changes, normal-suite reconciliation and
   applicable formal fixed-point/performance gates (ceiling7.5s).

## Excluded

Generic compatibility's separate Unresolved producer, named-function value
admission, all remaining rejection domains, extension fixtures met-bejv,
API-input narrowing com-p8xt and new inference rules remain their own scopes.
Do not close com-yeua or phase three from this finite increment.

## Initial evidence

Whole normal 20261123T123611-test-19e1c3 finished with unchanged inputs,
295 failures, no newly failing cases or changed failure reasons against the
previous complete314 run. The five negatives still return unclassified1.
Resolve/Record.pw currently uses the same refusal text for absent facts,
Pending/Unrecorded and value-block missing terms: those paths must be
separated by real producer evidence before any Source interpretation.

## Investigation / RED checkpoint (not implementation acceptance)

Fixed carrier2b5475, unchanged frozen source5bafacff:
[executed15-mode record](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-typing-obligation-red.json).
All five check/AOT cases and the global ORC case reject with the intended
message, exit1 and complete channel, but Unclassified (11 RED assertions).
Four unused-function ORC cases correctly exit0 without failure channel;
preserve these as GREEN non-interference controls, not missing rejections.

Preparation owns function/global publication; nested closure publication runs
through checkNestedSourceFacts. recordSourceTypingObligation currently stores
required expression IDs without request origin. Thus owner membership alone
cannot distinguish Raw/internal obligations from admitted authored requests.
The next implementation plan must carry justified negative provenance from
recording to publication, preserving Raw entry points and using one read-only
observer. Absent expression facts must not grant that provenance.

Independent planning review typing_obligation_plan_review found no mandatory
scope/contract correction or new semantic decision. It independently checked
whole failure maps, original result/stdout hashes,7642worker pairs and32unchanged
resolved fixture files. This is plan/evidence review, not code acceptance.
[Whole reconciliation](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-post-numeric-normal-suite.json).

## WIP implementation boundary

Dedicated SourceTyping cause and retained negative events are being added.
Only Lower-authored empty arrays without element context register a typed
obligation; general expression recording avoids a new lookup. Private
publication checks carry request origin for function/global/nested closures;
Raw wrappers retain Unclassified. Missing expression facts remain Raw,
including intentionally deferred but never completed facts. Pending source
facts additionally require their normal completion and matching owner.
Successful term storage discharges the array obligation at putExpression.
Lower metadata now retains its own serial in both lowering entrances.

Independent source review identified pre-record serial replacement and stale
obligations after completion; both have dedicated probe scenarios and WIP fixes.
The initial build rejected a private origin type in a public impl; the core
was moved into a private impl, preserving the public Raw wrapper. This is not
implementation acceptance. Standard frozen build1c0f8f and final private probe
remain to be collected; don't reuse the failed860807 setup/build as a pass.

### Corrected failure lifetime checkpoint

Private12-scenario native typing-private-v7 exits0 with empty stdout/stderr;
raw/request/session/root, serial before/after recording, span, owner before/after
event, missing facts, missing completion and resolved-obligation fault injection
are covered. Consumer typing-consumer-v3 exits0 with exact21-line golden and
empty stderr: five function/closure shapes through Raw retry/drain,
owned prepareFunction retry then whole checking, fresh whole/eager, plus global.
Inputs unchanged for both. These are native execution receipts, not ASan gates.

The closure consumer found a real failure-lifetime bug in the initial observer:
failed closure builders discard parent links. Root ancestry is now checked only
at the producer while live and retained in the negative event; observation
validates the saved event and persistent expression ownership without rebuilding
that ancestry. Post-event foreign-owner observation is now rejected as well.
Final build001731, CLI18, gen f14f22 and metadata ASan/LSan both pass with
unchanged inputs. Formal1c067a reaches G2, LLVM/runtime/successor hashes match;
standard3 measurements7.717293/7.247575/7.149129, median7.247575<=7.5.
All5 generation/measurement artifact records were independently hashed at
collection; actual measured compiler1b22eb22 also passes18CLI controls.
The normal harness now registers that CLI gate (29c6167a; source unchanged).
Whole20261123T145308-test-b59031 is running on source-identical typing-normal-v4
and the measured compiler. Compare against295; this task remains open until
whole reconciliation and final independent acceptance. No parent closure.
