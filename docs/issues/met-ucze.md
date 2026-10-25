---
id: met-ucze
status: open
deps: [com-qehq, com-qb05, com-17yh, com-4kti, com-fyxe, com-072n, com-3qne, com-o3vw, com-6cw6, com-ra96, com-zy6r, com-y8l4]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-ra96](com-ra96.md), [com-zy6r](com-zy6r.md), [com-y8l4](com-y8l4.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

## Contract

One source construction/selection owner commits the declaration or requirement,
lexical owner, receiver/evaluation inputs, full signature, substitution, result
recipe, conversions and evidence. Candidate probes may refine permitted unknowns;
Generic, Verify, Mono and final readers consume the committed result rather than
selecting another member. Shared lookup called repeatedly is not one authority.
Preserve source order, visibility, labels, ownership, bounds and ambiguity.
First concrete evidence for an already selected abstract requirement is legitimate
instantiation, not permission to choose a different source path.

Design: [Body Checking](../design/body-checking.md),
[Lookup](../design/name-lookup.md), [Frontend Handoffs](../design/frontend-handoffs.md).

## Current Boundary

Owner-local operation/constraint payloads, navigation-only indexes, saved static/
dynamic/operator/protocol templates and recorded-signature readers are implemented
increments. Static protocol operations retain selected requirements; the old
ProtocolSelection.Direct alternative and post-success storage-summary rewrite
were removed. Canonical iteration requirements and lexical provided-body ownership
remain semantic obligations. None of this certifies all remaining paths without
the child closure records below.

Auxiliary storage/access-demand analysis must not mutate a published source
operation. Keep its independent result and eager/demand access-analysis contrasts.
Pending source conversions finish before successful owner publication; final
readers cannot turn missing selection/evidence into presence-only acceptance.
Keep method/operator/protocol result projections and the same source provenance.

## Executable Work

- [B0](com-qehq.md): reconcile the eight actual paths and select residuals.
- [B1](com-qb05.md): ordinary/method/factory saved-selection closure.
- [B2](com-17yh.md): operator/protocol/iteration/try selected requirements.
- [com-4kti](com-4kti.md): shared ordinary-generic/projected source candidate
  enumeration, applicability and full-instance admission through saved final use.
  The C2 finding is closed by the fresh shared-frontier repair and its independent review; B0/B1/B2 alone did not establish this boundary.
- [B3](com-v2xk.md) under met-ia09 owns exact callee condition environments;
  [D3](com-wqa0.md) owns the final operation/constraint API write boundary.

Close this area after its required children/repairs and scoped fresh controls,
with producer/final-reader/removal locations per path. Retain matching successful
evidence from the [source-owner index](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/README.md).
The old sequential WIP/next/gate paragraphs are Git history, not current work.
Whole-candidate gates remain required by [G2a](com-p5um.md)/[G2b](com-9l3b.md)
before the parent closes; area closure alone is not release/seed readiness.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), [com-esri](com-esri.md): **Included repair** on existing
written/generic-bound/provided/operator/implicit calls. No new opening, unique
generics or protocol surface is introduced by this work.

## Reconciled Area Completion

Independent body_receiver_completion_review accepts this finite area after all
required children and repairs closed. The following are current evidence owners,
not claims that their earlier binaries passed today's whole-candidate gates.

| Path | Selected fact through final consumer and removed decision |
| --- | --- |
| Ordinary | B1/com-qb05: saved Direct declaration, type arguments and argument plan -> body/signature -> Mid/LLVM. Verify's free-function candidate reselection is removed. |
| Method / view | B1, com-4kti and com-fyxe: complete receiver/instance/ParamIds/proof -> shared applicability and exact SourceAdmission -> saved operation -> final callee. Dictionary type overwrite and post-selection literal relookup are removed. |
| Factory / default | B1, C3 producer repairs and com-3qne: selected original declaration/edge/binders -> ordinary default plan -> Direct/Provided -> final ABI. Recursive adapter, lost original owner and wrong-target copies are repaired. |
| Operator | B2/com-17yh and C4/com-e9l2: operands/selection/result -> actual callee -> explicit result projection. Missing-result Bool/left-operand recovery is removed. |
| Protocol / iteration | B2 and C4: canonical requirement/slot/Prior dependency/Item recipe -> descriptor -> Mid For. ProtocolSelection.Direct and structural-next replacement are removed. |
| Try | B2: saved Result decomposition and From slot/proof -> FinalTryResolution -> Mid/LLVM, without type-name From reselection. |
| Inherited / provided | B3/com-v2xk, com-6paa, com-072n/com-9clj and com-3qne: original declaration vs placement, complete receiver and condition IDs -> both worklists -> body key/signature/adapter. First-copy, wildcard and last-wins owner recovery are removed. |
| Dynamic / interface | B4/com-yojf, C6/com-3q2n and D3/com-wqa0: binding/field/interface root/trait/slot -> descriptor -> common Mid/LLVM admission; foreign owner, same-ABI and wrong-field controls remain. |

com-o3vw additionally closes the structural index canonical U64 producer through
field/access use, retaining original 42/99 output and generic/nested/read/write
controls. The child Outcomes and linked receipts hold exact revisions, controls,
removed paths and independent reviews. The latest default-forwarding evidence
covers native 41/reject 6 and targeted LLVM22 ASan/LSan 9; this is not full ASan.

Retained providedBodyProof and selected witness interpretation instantiate the
placement of an already selected copy. They are explicit representation/evidence
transforms, not permission to search by name for a new source implementation.
No unfinished in-scope source-selection family remains in this area. Final
frozen-candidate normal/gen/deps/sanitizer/fixed-point/performance gates remain
G2a/G2b obligations; neither phase three nor main/seed/carrier promotion is
certified by this scoped closure.

## Trait Chain Readmission

com-6cw6 closes the G2b-discovered placement regression at production b16439fa /
fixture573ff620. Original source edge, complete receiver, surface owner and root
birth edge remain distinct from lexical provided-body ownership. Both concrete
copy readers interpret the saved ordered proof; gated diagnostic candidates
never select a call. Independent body_receiver_completion_review accepts the
repair and this area's reclosure after native47/reject23 and sourcecheck, with
both 381-input maps unchanged. Original fifteen rejection pairs and 3qne41/6
remain intact; nested-root and exact-duplicate controls pass. Receipt
meta/evidence/existing-feature-conformance/source-owner-facts/trait-chain-placement-repair.json.
Final changed-input G1/G2 gates remain separate; historical gates do not qualify.
