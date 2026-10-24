---
id: met-7a8u
status: closed
deps: [met-qs57]
links: []
created: 2026-10-24T18:06:52Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, frontend]
---
# Close member obligation relevance with a reverse-edge worklist


## Measured Boundary and Preservation

New production499c0d7f profile assigns about0.172s to the source-call relevance
stage; its while-changed loop repeatedly reads every immutable call template and
constraint snapshot. Replace only passes after the original first pass with a
flat reverse-edge worklist. First pass keeps exact template order, relevance
skip, source key lookup, deferred predicate/first error and Direct/Static/
Protocol/Operator/conversion-seed rules. It collects valid canonical callee owner
to original caller-root edges for Direct and Operator.Direct. No propagation
until that pass completes. Out-of-range owners/callees stay skipped; keep the
final provided-owner projection unchanged.

Proof: at first-pass completion, every still-false owner's eligible template
already has immutable deferred=false; subsequent passes can only propagate
relevance over the recorded graph and cannot introduce a new error. The queue
computes the same least fixed point. Do not simultaneously change source
constraint identity lookup or infer new source meaning.

Independent scope investigation accepts this finite protocol. Add public-entry
controls for reversed chains, seeded/unseeded cycles, diamonds, conversion/
static/operator seeds and first-pass error/skip order. No test-only public API.
Compare the combined candidate with source-query baseline on identical input,
retain structural and correctness evidence, and obtain independent completion
review. This is not the below6s parent or whole-G2 completion.

## Outcome

Resolved by navigation/projection3b5162c5 and relevance8711de03, with standalone
new-control source text repair678a85b9. Source behavior, prepared admission,
identity and initial diagnostic ordering remain intact. Fresh9a698996d9e8c995d4accded21907cb46b2a0634664f6846afb622b92ffeca97 passes
all sourcecheck and17 native/7 reject controls. Same-source serial3+3 comparison
median6.769865→6.072895s with all LLVM78283576bbfe56315dc14ea9a8fa28691e749adad8ad3f4f508da30ab28f24b3.
Independent b2 reviewer checked13 references,236/239 input hashes,6 compressed
LLVMs and the fixture-only repair; accepts both finite tasks. Meta evidence
performance-six-seconds/call-navigation-relevance.json owns detailed proof.
Formal182531-self-host-6ee17d reaches generation2 fixed point, median6.051333s:
this is still above the parent target, not main/G2 admission. Subsequent finite
query/empty-view work is met-ycyn. No semantic caches or lowered proof conditions.
