---
id: com-9hf7
status: closed
deps: []
links: []
created: 2026-10-25T10:22:51Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Independently re-audit phase three against specifications and design contracts


## Contract and Review Scope

Fresh independent review requested after com-ugee's scoped repair. Judge the
original eleven criteria of [met-si6j](met-si6j.md), not the current implementation
or previous acceptance as authority. Read specification and all design chapters,
map relevant existing-feature contracts and issue dependencies/exclusions, trace
actual source producers through immutable facts and explicit instances to final
consumers, and use bounded counterexamples where appropriate. Preserve valid
existing scope; do not classify a current failure as a new feature solely because
it is currently rejected. This review changes no specification or production code.

Inputs: compiler HEAD795608ca, production/fixtures e73a8476, spec9b3e18d,
Syntax exact0.1.11-dev.30/8c89204230c3d865ea95a03382c3fd213731e1de.
Exact reviewed compiler bin/plewc-value-producer-final SHA256
073f0375a63a5f8d57b5a2a4fa2e305c09a4cf57178d09a1386e4d27699c0036.

## Independent Work and Exit

- phase3_types_storage_rereview: types, expected context, source-owner storage,
  publication/failure, aggregate/closure results and explicit instantiation.
- phase3_calls_proofs_rereview: all call paths, overloads, default adapters,
  trait/projection/via/provided/receiver proof and final call realization.
- phase3_completion_modes_rereview: completion/divergence/diagnostics, exit
  targets/cleanup and requested-body consistency across check/build/run/gen.
- Root: comprehensive chapter/spec/issue coverage reconciliation, task graph,
  exact evidence applicability, remaining final gates and heterogeneous any-join
  classification. No gate or issue closure is presumed from an earlier review.

Review scratch: meta/tmp/phase3-current-rereview/. Each reviewer retains an
actual read/trace coverage manifest and evidence. Durable outcome must separate
confirmed in-scope defects, architectural gaps, justified exclusions, unverified
claims and incomplete final gates. Record source/line, normative basis, minimal
reproduction and result where available. Review can complete with explicit
findings and owning tasks; that does not close G1/G2/G3 or the parent. G3 depends
on this review. No main, seed or adopted-carrier update is part of this task.

## Outcome

Review complete; **phase three is not complete**. Three independent reviewers
confirmed11 findings:3 P1 and8 P2. Ten finite required repair issues hold the
work; F3/F4 share one canonical Unit return repair with both source and final-Mid
obligations. The reviewed candidate remains073f0375, productione73a8476.

- P1 F1: [com-jzdz](com-jzdz.md) — Preserve forbidden function returns through loop completion.
- P1 F2: [com-nr7y](com-nr7y.md) — Reject function returns from global initializer source owners.
- P1 CALL-3: [com-cwu1](com-cwu1.md) — Check complete dynamic call arguments before source publication.
- P2 CALL-1: [com-ra96](com-ra96.md) — Select existential overload requirements by full argument applicability.
- P2 CALL-2: [com-zy6r](com-zy6r.md) — Retain nested array element type identity in overload applicability.
- P2 CALL-4: [com-y8l4](com-y8l4.md) — Compare full canonical trait requirement signatures for duplicates.
- P2 T1: [com-l8m1](com-l8m1.md) — Preserve shared value region result conversions through final Mid.
- P2 T2: [com-6zph](com-6zph.md) — Seal source conversion evidence against post publication mutation.
- P2 F3,F4: [com-sby0](com-sby0.md) — Normalize Unit return contracts across source checking and lowering.
- P2 F5: [com-l9yo](com-l9yo.md) — Check scalar async return completeness at source admission.

The review considered all18 design chapter responsibilities and18 specification
topics, and reconciled all71 then-required issue contracts (specialists59,
root12), plus relevant external scope owners. Actual read/trace extents and
exclusions are recorded, not claimed as every-line/every-program verification.
Source producers, retained facts, concrete instances and actual Mid/LLVM/JIT
consumers were checked; direct/wrapped/declaration-order/annotation/mode controls
exposed the defects. Fresh scoped positive controls retain their exact scope.

Durable report, complete minimal sources, hashes, commands/outcomes, inspection
manifests and failed preliminary runs are in meta/evidence/existing-feature-
conformance/source-owner-facts/phase3-specification-rereview.json. Root also
independently reproduced the loop-return check and verified current gate input
identities. The new073f normal/gen/deps milestones remain valid; previous3c
formal/ASan gates do not cover this candidate. New final gates remain open.

Affected task/area contracts are reopened with real required dependencies;
parentcriteria3/4/7 are also no longer discharged. The earlier com-ugee
missing-give repair remains scoped complete; it did not certify other result,
call or transfer contracts. No production/spec/design/fixture/runner/binary was
changed by this review. No main/seed/adopted-carrier promotion occurred.
This closes the review deliverable only, not its fixes or G1/G2/G3/met-si6j.
