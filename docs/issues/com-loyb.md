---
id: com-loyb
status: open
deps: [com-6zph]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify source conversion proofs retain exact endpoints and ownership

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-6zph](com-6zph.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

## Boundary

Phase 3C / C5. **Bounded closure verification.** Parent criteria: 2, 3, 4, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Ir/ConversionProofs.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Follow the admitted structural/path/box conversion families from saved source endpoints/owner and pending completion into final argument/aggregate conversions. Inspect source construction completion separately from execution-time grounding; verify no post-outcome write or alternate conformance query repairs a missing source conversion.

## Exit and Evidence

Use existing pending-source, wrong-owner/path/proof and actual closure/boxing controls. Record endpoint/owner/instance validation and final consumers for each current conversion family. Any missing evidence is rejected or repaired at its producer, never guessed from equal ABI. Runtime representation/ARC optimization and unsupported conversions remain outside this task.

Existing starting controls: `pending_source_conversion_completion`, `source_conversion_owner_requests`, `declaration_conversion_closure`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.


## Conversion Admission Endpoint Scope Increment

Static audit and independent review identify a finite admission omission:
checkDeclarationConversionEvidence checked row/proof endpoint equality, then
only traversed proof-owned dependencies. Identity has no embedded endpoints;
ArrayRepack traversed only its child. Thus a corrupted row using another
function's same-spelled ParamId could escape the row's declaration scope.
A new File+SourceResource graph with real Lang Array declarations reproduces
that refusal assertion at runtime134 with unchanged inputs (before-5). This is
a damaged-plan admission defect, not a demonstrated ordinary-source acceptance
bug. The current producer never emits ArrayRepack with only an Identity child;
pending-source completion can legitimately retain an Identity row.

The paired common admission now checks both row endpoints in the existing
declarationTypeScope, including Identity. The standalone ArrayRepack dependency
reader checks its own endpoints and child, matching the other structural
families. Source recording/pending completion remain the sole producers; final
conversion instantiation and its exact source/target/site reader do not reselect
proofs or repair missing information. No additional proof table is introduced.

source_conversion_endpoint_scope uses two actual declaration owners, verifies
distinct terms and direct own/foreign scope results, then checks positive and
foreign Identity rows and Array plans plus standalone Array dependency. The
new Comp code passes this preflight in the existing compiler after the repair.
Fresh source checking and the actual Mid/native conversion controls are still
required; preflight alone does not complete this task.

Earlier new-fixture setup attempts used FrontendInput.Text for Array without
ambient Lang and requested body preparation. Text parses only its supplied
graph; stdRoot does not make it File loading. analyzeFrontendDeclarations also
prepares bodies. The normal File CLI check succeeds on the same text. Independent
review classifies this as fixture/API graph mismatch, not a source regression
or unassigned repair. The final probe uses the established File+resource path
and declaration-only admission. Preliminary failed runs remain separate raw
records; they are not the decisive endpoint reproduction.


## Bounded Completion

Production **96e375a7**, fresh compiler SHA256
**ae44a45f4742e653a71a642999919e8f6f40182e7e02a317df2290c9a17cc788**.
Standard build **20261024T083905-build-bdcd46** and full fresh sourcecheck pass.
Scoped native22/reject7 plus generic native3 pass with unchanged inputs.

Independent completion review by /root/body_receiver_completion_review recognizes
this finite task complete without blockers, and verifies all21 referenced file
hashes plus249/194 target input fingerprints. Identity/Missing/Retag/Box/Array/
Enum retain exact endpoint/owner/path evidence through source completion,
explicit body environment, final conversion, frozen Mid proof and LLVM.
recorded_conversion_consumption preserves source/target and equal-final-type
negative controls; the actual heap/structural/generic/closure controls pass.

Canonical variant/producer/consumer map, correction and validation records:
meta **1646925c**, evidence/existing-feature-conformance/source-owner-facts/
phase3c-conversion-evidence-closure.json. The original before-5 assertion failure
is distinct from preliminary Text-graph setup failures and from the successful
embedded preflight/fresh tests. No ordinary-source acceptance bug is claimed.
All sessions are recovered; final G2a/b and C6 onward remain incomplete.
This does not establish latest formal performance, parent completion, main
integration or candidate ASan success.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 63.

Row63: Audit reuse creates no extra endpoint repair and does not reopen already-correct finite evidence. Do not transfer Text-graph setup failures into source regressions or require unsupported conversions/ARC optimization. com-loyb retains exact saved source/target/site/owner conversion proof through completion and final instantiation. Existing finite96e375a7 endpoint fix remains valid, while reopened com-6zph must close new current gaps before this area. Required admission: met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
