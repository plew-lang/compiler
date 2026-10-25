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

## Implemented Boundary and Targeted Results

Production b16439fa (with a79c7b8c/5028e749/d88d92ac) separates
lexical body ownership from callable surface ownership. Conform.viewRootOwner
and viewRootConformIdx preserve where a root first became necessary; Func
sourceRootConformIdx survives copy production and deduplication. Both final
copy readers use the already selected ordered proof and complete receiver to
interpret that anchor. Membership of an owner anywhere in the path is no longer
sufficient. The nested Root -> Via -> Base and Root -> Base contrast prevents
that regression; exact duplicate selected placements still fail both readers.
The diagnostic-only gated candidate bucket preserves ordinary/inherent priority
and labels/types; it never selects or publishes a gated call.

Fixture 573ff620 and candidate bin/plewc-chain-placement-3 (SHA256
550bb667e81c70addc44005caf46d61a866c69ebdc917a0599b0d20acfdc57bc)
from standard build 20261025T045029-build-8b56fb pass focused-2 native47 /
reject23 and sourcecheck-3, exit zero and recorded inputs unchanged. All fifteen
original reject sources/expectations and default-forwarding41/6 are retained.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/trait-chain-placement-repair.json
records current results and initial failures remain in scratch.
Independent final result/fingerprint confirmation is pending; static re-review
reports no blocker. Changed-candidate G1/G2 obligations remain open.
