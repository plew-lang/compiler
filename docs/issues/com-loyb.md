---
id: com-loyb
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify source conversion proofs retain exact endpoints and ownership

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
