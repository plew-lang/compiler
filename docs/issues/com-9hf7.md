---
id: com-9hf7
status: in_progress
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
