---
id: met-7a8u
status: in_progress
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
