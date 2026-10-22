---
id: com-kp3y
status: in_progress
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

## Selected Implementation Input and Removal Inventory

Start from compiler `6b267289` (production `87b382d2`), spec `595bb5b`, Syntax exact `0.1.11-dev.30` / `8c892042`. Reuse the matching phase-two fixed point/formal median 6.211262 seconds and reviewed source/std/fixture evidence; do not rerun an unchanged baseline. Development carrier is `bin/plewc-orc-lifetime`, SHA256 `c36716d9f95e123f2b62158e44e2287476757eaf52b6bd93e41bc1a2a47d18b3`. Preserve the existing dirty binary/caches and main/seed.

Current concrete producers are Frontend.storeBuildingSemanticExprType/storeBuildingSemanticBinding/storeBuildingSemanticStmtCompletion, Record.putSemanticAggregate/putSemanticTry/putSemanticMatch/recordSourceBodySignature and lexical/global preparation publication. The competing physical authority is Comp's all-owner semanticExprRecords/semanticAggregates/semanticTries/semanticMatches/bindings/statements/signature arrays and snapshot indexes. Consumers include PreparedSemanticFacts, MidBuild.sourceFacts, Mono preparedSourceExpression/access/binding/result readers and checked completion readers. Construction-time queries must remain distinct from sealed readers.

Migrate this family through private per-owner construction storage and immutable Ref-backed payloads, with local indexes from source identities. Shared type/proof pools remain session-owned IDs. Outcome publication must retain first failure and release builder storage; no mutable writer can escape into the payload. Move consumers and remove replaced full-array snapshots/writers in the same increment. Preserve callable-signature queries without requesting callee bodies.

Closure declaration metadata currently records a parent preparation owner while the body uses a distinct high-bit Mono key. The body facts must acquire their own source identity/outcome without treating successful construction as body success. Global initializer facts likewise retain per-declaration identity rather than the synthetic all-global sentinel. These are existing explicit storage contracts, not new language features. Keep call-selection/conversion work not migrated by this increment explicitly owned by its later task, preserving current successful readers.

Before closing: normal/error/foreign-owner/post-outcome mutation and retained-reader stability controls; existing aggregate/try/pattern/generic/closure/global AOT and lazy paths; removal audit for every moved field; source-local storage/acquisition counters outside formal timing; applicable full gates and fresh fixed point/formal median below seven seconds. Store/verifier-only completion is forbidden.
