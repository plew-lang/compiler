---
id: met-9luu
status: in_progress
deps: [met-g9dh]
links: []
created: 2026-11-27T09:01:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [frontend, ownership, verification]
---
# Install admitted parameter groups in body scopes

Make closure and named-body parameter installation consume the admitted binding group before publishing closure facts or introducing locals. Preserve explicit local shadowing and distinct outer scope bindings.


## Contract and confirmed failure

Current da2c8c0a82e9 executes duplicate labelled and duplicate suppressed-name
closures with arguments11/22 and returns22. A named fn with duplicate
suppressed parameter names does the same. Record appends each parameter via
addLocal, addLocalCn appends to cur.locals, and localIndexByName searches
backwards. The parameter group is never admitted before this makes an invalid
second binding shadow the first. resolveClosureFunctionType and descriptor
publication do not establish binding-name uniqueness.

Consume an admitted parameter group before publishing a closure descriptor/
SourceBodySignature or installing its locals. Use the same group rules as
named signatures; do not add a closure-only duplicate-name loop or make the
low-level addLocal reject every repeated name. Retain stable binding identities
and the original admitted signature through installation; do not re-infer
labels/types or construct a second local environment/duplicate parameter array.

Explicit sequential val/mut val shadowing and outer-variable/parameter
shadowing remain valid under spec03. Captures and implicit receiver data are
not additional user parameters in this group. Inventory the finite parameter
installation callers and distinguish raw storage append from semantic group
admission. If another simultaneous binder group has the same missing boundary,
record its evidence and assign a real owner rather than claiming all scopes
fixed here. Do not change unrelated pattern/capture semantics by assumption.

RED/GREEN: actual duplicate-labelled/suppressed closure invocation plus
unused-created closure signatures, same/different parameter types, inferred
contexts and wrappers; named body consumption of admitted groups, Raw/foreign
groups without Source promotion, no partial locals/facts on failure, stable
identity through captures/ownership. Preserve explicit sequential shadow and
outer-binding restoration; the executed positive controls are in binders.json.
Focused real Record/retention/consumer controls and neutral review are required;
parent met-auj6 owns aggregate compatibility/performance gates.

The user confirmed that semantic parameter introduction owns validation. Body
scope storage must consume the admitted result rather than revalidate it or
accept an allowShadow switch. Closure signature introduction invokes the shared
admission once before publication; its generic storage helper remains neutral
to the declaration category. No new local environment is needed for the check.

## Owned introduction plan and RED

The fixed A candidate (7771bb48 product) matrix has24 legal successes and30
target failures: duplicate labelled/suppressed/mixed/differently typed and
block-wrapped closure groups, local/imported check/AOT/ORC. Repeated bindings
are accepted; distinct contextual signatures and shadowing execute correctly.
Receipt: meta declaration-parameters/closure-red.json. The initial contextual
negative used invalid omitted-type syntax; it was removed from target evidence
and replaced with a legal contextual positive before this RED record.

Record's Expr.Closure branch owns the completed group before reading any
signature cache, publishing descriptors/body signatures or installing locals.
The public resolveClosureFunctionType constructor remains Raw and invokes the
shared comparison; the private admitted continuation avoids a second scan in
owned Record. Raw named-body introduction validates before clearing/installing
locals; the owned named path consumes its admitted declaration.

Lower retains one private passive authored closure signature receipt (Expr with
its existing CoW parameter array, serial/span/body/signature identity and original
Lower scope), not a second local environment. On actual conflict only, Record
verifies that receipt, original lexical owner, request session/root, active owner
and actual sourceControlNodePath. It retains one typed closure-signature refusal
with the saved proof/path. Raw preparation/cache retains Unclassified; only the
owned service validates and interprets the saved refusal as Source. No duplicate
name judgement, full graph walk or parent-owner reconstruction is repeated by
that consumer. Generic owned diagnostic conversion preserves notes as well as
reason and primary location. This is one shared-producer/service-boundary frame,
not a separate event dictionary for each binding/label rule. No Source success
fact or arbitrary diagnostic-promotion API is created. No success-path bodywalk
is added.

WIP source checking passes. Fresh/native/mutation/cache/retention controls and
independent finite certification remain pending.

## Foreign-owner counterexample and repair

Independent review identified an actual Lower closure transplanted from another
function into the current owner's existing Let initializer slot. A current
structure path alone would pass despite unchanged foreign signature/span/serial.
Native closure-parameter-native-red-v2 executes the target failure explicitly
(status-6, Transplanted assertion; preceding cases pass), not a setup failure.
The receipt now retains its original Lower scope and binds that scope to the
canonical lexical function/global/default owner via SourceTypeUses before the
current path check. Native green-v2 passes all12 owned/Raw/public/full Record/
cache/name/body/span/serial/synthetic/foreign/transplanted controls with unchanged
inputs. Source scopes are compared; no acceptance flag or second environment
is added. The proof-building path is failure-only. Retained session and fresh
build controls remain pending.

Expanded owner-branch RED has96 cases:24 legal successes and72 duplicate
acceptances on fixed A (input-invariant). It includes global initializer, direct/
block-wrapped parameter and field defaults, provided and generic original-owner
paths. Receipt closure-owner-red.json. These are real accepted programs on A;
not unrelated setup rejections. The initial session harness used an unsupported
unique-yield match form; it is corrected to the existing statement-return pattern
and excluded from evidence of executed assertions.

## Raw preparation and retained consumer repair

Native session-red-v4 proves direct Source emission at Record leaks through
public prepareLexicalBody: exact duplicate binding-name Source report on Raw
Comp. CheckingRequest is constructed by the shared preparation pipeline and is
not owned-session authority. Source review independently confirmed this caller
chain. The corrected producer emits ClosureSignatureRefusal (Unclassified),
stores one immutable proof/path frame, and ownedFailure/sourceFailureHasOwner
validate it without re-running acceptance. Both owned conversion points now
retain notes. Native green-v3 passes12 scenarios plus forged payload/session and
failed-builder checks; session-green-v1 passes Raw repeated preparation, owned
retries, whole failed-session and eager source classification with exact notes.
No setup failures are counted as target RED.

The finite addLocal inventory is binding-installation-callers.json. Verify/Mono
consume registered signatures or retained closure descriptors; low-level
verifyFunc/checkGenericFunction are not Raw registration APIs. Reviewer confirmed
that repeating admission in these passes would violate the intended owner split.
Unrelated statement/pattern/loop binding policies are not claimed fixed.

Latest native green-v4 adds malformed-group refusal and confirms13 scenarios
plus forged/session/failed-builder proof checks. Latest session-green-v2 also
checks Raw diagnostic drain. Neutral source review of97143377 found no further
Diag-case, payload/proof/root or note-retention must-fix. Fresh v3,96 owner
matrix and normal capture/ownership regressions remain pending; not closed.

## Final-candidate focused gates

Frozen build v3 (20261127T102918-build-15aced) passed on adopted da2 carrier.
Its complete .pw source set equals current product97143377/testsec680ec1;
aggregate/file-manifest proof is closure-source.json. On that fresh compiler,
closure96/96, declaration114/114 and8 existing capture/context/generic/unique
fixtures on old+fresh (16 executions) pass with unchanged inputs. Receipts are
closure-{green,declaration-regression,regressions}.json. Selected gen and final
neutral certification remain pending. Parent retains whole/fixed-point/perf.
