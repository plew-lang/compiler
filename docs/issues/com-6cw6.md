---
id: com-6cw6
status: in_progress
deps: []
links: []
created: 2026-10-25T04:23:49Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Preserve trait subject chain placement without leaking caller views


## Boundary and Exit

Required repair exposed by G2b full normal 20261025T034939-test-9cc5f8.
Fifteen maintained trait_subject_chain_conflict* / try_from_body_obligation
rejects regress: four lose ambiguous bare diagnostics and eleven report internal
multiple receiver copies. Same-source controls: old 6ddf8f75 passes all exact
expected refusals; c50d2a04 and measured 73078e5d reproduce all fifteen failures.
No fixture source/expectation changes. Receipt
meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-normal-initial-failure.json;
raw compiler/tmp/phase3-chain-conflict/compare-1.

Entry producer: Codegen/Decl.applyBlanketTo, sourceConformanceForDeclaration and
instantiateProvidedMethods. Saved boundary: original witness/source edge, complete
receiver and concrete view/path placement. Consumers: Mono/Call.proofConcreteWitness
and providedCopyReceiverMatches, then the existing explicit callee environment.
First establish a copy table correlating both observed failures. Split the repair
if they prove independent roots rather than expanding one unspecified rewrite.

Caller s#C.a() may choose the outer source, but cannot rewrite lexical lookup of
self.b() inside shared impl B as A. Distinct legitimate paths must receive the
existing SourceAdmission ambiguity diagnosis; do not translate an internal error
string or select/deduplicate the first copy. A duplicate exact placement remains
an invariant violation. Keep the original-source-edge filter and saved-call
authority, rather than restoring broad unrelated-edge copying.

Validate all fifteen original rejects, valid single/explicit-root chains with
positive and negative caller-view independence, generic argument/newtype/nested
view identity, default-forwarding 41/6 scope and wrong receiver/proof/duplicate
corruption controls. Follow producer -> retained placement -> selected concrete
copy -> BodyInstance -> Mid/LLVM. Fresh targeted validation and independent
completion review precede closure. Reconcile affected areas/G1; then rerun the
changed candidate's G2a/G2b. The prior formal result remains historical evidence.

Independent body_receiver_completion_review accepts this finite task scope and
its split condition. It is not cause confirmation or implementation acceptance.
No new language surface, ABI, altered watchdog or test/verifier weakening.
