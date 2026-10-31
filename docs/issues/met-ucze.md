---
id: met-ucze
status: open
deps: [com-qehq, com-qb05, com-17yh, com-4kti, com-fyxe, com-072n, com-3qne, com-o3vw, com-6cw6, com-ra96, com-zy6r, com-y8l4, met-g53w, met-tfbl, com-geem, com-0lz8, com-17ha, com-7cpj, com-9aap, com-kb6f, com-uk6c, com-1fxn, com-27h6, com-4wxu, com-6z28, com-ckde, com-cn5o, com-cx2r, com-e681, com-jvmv, com-k3cc, com-k5i6, com-kgom, com-m13a, com-y9r7, com-zcrx, com-00c4, com-03ra, com-2jwz, com-33jc, com-4aon, com-9mqu, com-9z44, com-bswq, com-edyb, com-fczr, com-hnm8, com-j0r9, com-majd, com-nukp, com-pweb, com-t63i, com-tn1g, com-u1tx, com-ukzt, com-zai9, com-a3ph, com-h5be, com-n5lu, com-wjky, com-0u0i, com-0y1t, com-1eo5, com-8ejz, com-bvfx, com-cnvd, com-fpmj, com-iucg, com-k3i6, com-lpof, com-tr3a, com-xsw7, com-0huw, com-13js, com-79k3, com-9i94, com-bw8e, com-cwq1, com-fboq, com-hd9n, com-mq3s, com-nee8, com-oorl, com-q8eb, com-r3od, com-sezm, com-07tb, com-1fbr, com-74ky, com-8yzi, com-aaia, com-esbb, com-jix5, com-jm7l, com-mvx1, com-p8xt, com-q400, com-s696, com-zpo1, com-0pl3, com-3s8q, com-4c9t, com-59sf, com-847f, com-eatt, com-k0zf, com-kwd5, com-ot44, com-qadp, com-yyyl, com-zftv, com-1bh1, com-5d3q, com-62pl, com-88dq, com-jwzi, com-nq9x, com-orol, com-s0zb, com-ui4c, com-zefb, com-zhs6, com-bfvd, com-ntm8, com-z4ns, met-4slo]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

## Lexical Visibility Investigation

[met-tfbl](met-tfbl.md) is a required investigation before fresh closure. An
unrelated loaded module's same-named function makes a local closure parameter
call fail visibility. The user requests a responsibility-level audit of lexical
priority, candidate continuation/failure categories and diagnostic-only search,
not an assumed closure-specific patch. The optional missing-use hint may be
removed if it interferes; actual visibility rejection must remain. The audit
must assign confirmed repairs before closing; no earlier finite call/argument
repair or green gate certifies this new boundary.

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

## Scoped Audit Intake com-vr57

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-frontend-services.json) assigns exact required input-authority repair subsets to this admission contract: com-0lz8, com-17ha, com-7cpj, com-9aap, com-kb6f, com-uk6c. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-yjyu

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-defaults-and-literals.json) assigns exact required input-authority repair subsets to this admission contract: com-1fxn, com-27h6, com-4wxu, com-6z28, com-ckde, com-cn5o, com-cx2r, com-e681, com-jvmv, com-k3cc, com-k5i6, com-kgom, com-m13a, com-y9r7, com-zcrx. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-lk60

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-constraints.json) assigns exact required input-authority repair subsets to this admission contract: com-00c4, com-03ra, com-2jwz, com-33jc, com-4aon, com-9mqu, com-9z44, com-bswq, com-edyb, com-fczr, com-hnm8, com-j0r9, com-majd, com-nukp, com-pweb, com-t63i, com-tn1g, com-u1tx, com-ukzt, com-zai9. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-ptko

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) assigns exact required input-authority repair subsets to this admission contract: com-a3ph, com-h5be, com-n5lu, com-wjky. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-8ttz

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-verification.json) assigns exact required input-authority repair subsets to this admission contract: com-0u0i, com-0y1t, com-1eo5, com-8ejz, com-bvfx, com-cnvd, com-fpmj, com-iucg, com-k3i6, com-lpof, com-tr3a, com-xsw7. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-3z5o

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) assigns exact required input-authority repair subsets to this admission contract: com-0huw, com-13js, com-79k3, com-9i94, com-bw8e, com-cwq1, com-fboq, com-hd9n, com-mq3s, com-nee8, com-oorl, com-q8eb, com-r3od, com-sezm. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-7kzd

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-recording.json) assigns exact required input-authority repair subsets to this admission contract: com-07tb, com-1fbr, com-74ky, com-8yzi, com-aaia, com-esbb, com-jix5, com-jm7l, com-mvx1, com-p8xt, com-q400, com-s696, com-zpo1. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-4sg9

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-selected-instances.json) assigns exact required input-authority repair subsets to this admission contract: com-0pl3, com-3s8q, com-4c9t, com-59sf, com-847f, com-eatt, com-k0zf, com-kwd5, com-ot44, com-qadp, com-yyyl, com-zftv. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Scoped Audit Intake com-7a5t

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-construction.json) assigns exact required input-authority repair subsets to this admission contract: com-1bh1, com-5d3q, com-62pl, com-88dq, com-jwzi, com-nq9x, com-orol, com-s0zb, com-ui4c, com-zefb, com-zhs6. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Test Admission Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) installs required finite repair/investigation prerequisites at this actual admission: com-ntm8 (row5), com-bfvd (row17), com-z4ns (row26), met-4slo (row32). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
