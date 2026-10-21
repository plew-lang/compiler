---
id: com-kp3y
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [design, verification]
---
# Seal source owner facts through existing Mid and Mono readers

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [met-acfl](met-acfl.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Owner-local header/expression/binding/completion publication and acquisition for ordinary, generic, provided, closure and global owners already admitted by the compiler. Preserve aggregate/try/pattern consumers and declaration-time signature queries. Independent closure construction versus body completion is included. This is the adopted storage increment, not a claim that all operation/evidence families are already a complete CheckedBody.

## Producer to Final Consumer and Removal

Frontend preparedSemanticFacts and building writers; Resolve/Record source headers and owner requests; Global initializer owners -> private sealed payload plus shared term/proof IDs -> Mid/Build parametric entries and Mono/Call prepared readers. Remove moved all-owner arrays/index/snapshot acquisition and post-completion writers in the same increment. Do not add a parallel store behind the old authority.

## Completion and Verification

Real function/global/closure owners, repeated success/failure, absent/foreign facts, post-success/post-failure mutation and retained-reader stability across later owners; aggregate/try/pattern execution and rejects; current AOT/JIT paths. Source signatures used during construction must not require a successful body. Storage cost controls stay outside formal timing.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
