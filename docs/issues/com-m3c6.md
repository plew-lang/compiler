---
id: com-m3c6
status: closed
deps: [com-m0bf, com-nqjd, com-6paa, com-qbwg, com-s5k5]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Verify nominal facet batch publication remains one-way

## Boundary

Phase 3D / D4. **Bounded API/removal verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Ir/Types.pw`; `src/Codegen/Check/Visibility.pw`; `src/Codegen/Resolve/Record.pw`; `src/Frontend.pw`.

Reconcile finishTypeDeclarationResolution and its private mutation against C3 source nominal producers. Check the all-or-nothing validation of ordered unique row identities, permanent phase closure and legal later appends. Trace the completed declaration dependency into successful source-owner admission.

## Exit and Evidence

Existing type_declaration_publication plus focused invalid/duplicate batch, post-publication row/append and branch controls establish the current API boundary. No production per-row overwrite writer remains. Do not conflate semantic term publication with runtime nominal layout or reimplement the already adopted batch.

Existing starting controls: `type_declaration_publication`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Publication Reconciliation

Production `9b4652a3` encapsulates canonical storage without changing source
semantics; `3c37252c` synchronizes comments/design. No new facet resolver is introduced.

| Boundary | Actual authority / retained consumers |
|---|---|
| Initial declaration resolution | `Frontend` completes source/module/declaration registration before `resolveTypeDeclIdentities` constructs `ResolvedTypeDeclaration` rows in arena order. Qualified syntax-generated terms join this same initial batch; C3 producers retain selected declaration domains. |
| Atomic batch admission | `Arena.finishTypeDeclarationResolution` first rejects a completed phase, sentinel/out-of-range rows and non-increasing identities (including duplicates). It checks the entire batch before calling private `applyResolvedTypeDeclaration` for any row. |
| Parallel representations | Private application updates both `TypeRef` and pooled `TypeTerm` facets from the admitted values, preserving structural children, cached closedness/projection presence and name-index keys. No public per-row replacement API remains. |
| Permanent closure / later append | Successful publication sets private `typeDeclarationResolutionFinished` permanently. `registerType` may append complete construction/substitution terms later, but no later row can reopen the phase or modify issued declaration facets. C3 source producers, not this batch API, own complete late construction identity. |
| Source success dependency | `checkSourceTypingObligations` requires `typeDeclarationResolutionComplete` before owner publication, even if no expression happens to use a nominal member. Lexical/global/nested owner preparation all call this gate before sealing. `finishSourceFacts` retains the first failure or immutable successful payload. |
| Final reads | D1/D2 source readers and Mid admission consume the published complete terms/signatures. C3 receiver/body-key, associated-call and Buffer controls retain exact selected identity through concrete instances. This facet audit does not reopen runtime nominal layouts or claim all future term producers are supported. |

Controls retain invalid/duplicate batch, post-success and post-append rejection,
two-representation stability and independent branch coverage in
`type_declaration_publication`; the strengthened fixture also checks a reverse
ordered batch causes no partial writes. `source_declaration_dependency` contrasts
uncompleted versus completed declaration phases on the same valid source body,
and checks an already failed request cannot be blessed by later dependency
completion. `type_declaration_writer_private` guards the private mutation API.
Existing closedness/projection/name-index/unification and C3 nominal controls
exercise preserved metadata and downstream identity.

## Outcome

Closed with required repair [com-s5k5](com-s5k5.md), production `9b4652a3` and
contract/comment synchronization `3c37252c`. Independent review found the
previously public mutable scalar/child arrays bypassed the dedicated batch API;
the repair hides all9 arrays behind scalar/element readers. No public raw alias
or external per-row writer remains. The original facet batch, legal append,
metadata and selected nominal source domains are preserved.

Receipts in meta's `evidence/existing-feature-conformance/source-owner-facts/`:
`phase3d-nominal-storage-before.json`, `phase3d-nominal-storage.json` and
`phase3d-nominal-storage-self-host.json`. The before raw row mutation compiled
exit0. New dependency fixture body-zero setup failures are recorded separately
from that decisive API defect.

Standard build `20261024T104423-build-8e5a45`, fresh all-source check and
normal17/reject12 passed with immutable inputs. Fresh carrier SHA256
`fa45a269e36932f2e1830059b7495829cbf0de5734311ac503a0e0e64e04a964`.
Formal `20261024T104921-self-host-920e54` reached generation2 fixed point;
7.304837/6.752248/6.762261 seconds give median **6.762261 seconds**, exit0 and
frozen inputs. Measured WIP `bin/plewc-phase3d-type-storage-fixed` SHA256
`380d649e240dd71e366323a4167ac39200dc77a0993fcec4cc5cda1dd8822275`.
No same-source speedup is claimed.

Independent reviewer `/root/body_receiver_completion_review` accepted both D4
and its repair: inverse-normalized40-file read migration has no unexplained
behavior differences; functional245 and formal5900 current inputs match; all
receipt/binary hashes match. All run sessions including91165/60041/84680/2285/
8284/15255/18703/76943 were recovered through actual exit codes. Source dependency
negative/positive, reverse batch, private apply and every raw pool family are
covered separately.

D4 does not certify runtime layout, future unsupported producers, final G2
whole-candidate gates, area/parent reconciliation or main/seed/adopted-carrier
promotion. Those obligations remain separately owned.
