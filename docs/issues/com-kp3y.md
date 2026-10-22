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

Start from compiler `6b267289` (production `87b382d2`), spec `595bb5b`, Syntax exact `0.1.11-dev.30` / `8c892042`. Reuse the matching phase-two fixed point/formal median 6.211262 seconds and reviewed source/std/fixture evidence; do not rerun an unchanged baseline. Development carrier is `bin/plewc-orc-lifetime`, SHA256 `c36716d9f95e123f2b62158e44e2287476757eaf52b6bd93e41bc1a2a47d18b3`. Keep generated development binaries/caches outside commits; standard build may replace bin/plewc, while saved carriers, main and seed remain unchanged.

Current concrete producers are Frontend.storeBuildingSemanticExprType/storeBuildingSemanticBinding/storeBuildingSemanticStmtCompletion, Record.putSemanticAggregate/putSemanticTry/putSemanticMatch/recordSourceBodySignature and lexical/global preparation publication. The competing physical authority is Comp's all-owner semanticExprRecords/semanticAggregates/semanticTries/semanticMatches/bindings/statements/signature arrays and snapshot indexes. Consumers include PreparedSemanticFacts, MidBuild.sourceFacts, Mono preparedSourceExpression/access/binding/result readers and checked completion readers. Construction-time queries must remain distinct from sealed readers.

Migrate this family through private per-owner construction storage and immutable Ref-backed payloads, with local indexes from source identities. Shared type/proof pools remain session-owned IDs. Outcome publication must retain first failure and release builder storage; no mutable writer can escape into the payload. Move consumers and remove replaced full-array snapshots/writers in the same increment. Preserve callable-signature queries without requesting callee bodies.

Closure declaration metadata currently records a parent preparation owner while the body uses a distinct high-bit Mono key. The body facts must acquire their own source identity/outcome without treating successful construction as body success. Global initializer facts likewise retain per-declaration identity rather than the synthetic all-global sentinel. These are existing explicit storage contracts, not new language features. Keep call-selection/conversion work not migrated by this increment explicitly owned by its later task, preserving current successful readers.

Before closing: normal/error/foreign-owner/post-outcome mutation and retained-reader stability controls; existing aggregate/try/pattern/generic/closure/global AOT and lazy paths; removal audit for every moved field; source-local storage/acquisition counters outside formal timing; applicable full gates and fresh fixed point/formal median below seven seconds. Store/verifier-only completion is forbidden.

## Implementation Checkpoint (Not Complete)

The first storage migration replaces the all-owner expression/aggregate/try/match/binding/statement/signature arrays and their snapshots with owner-local builders, immutable Ref-backed payloads and one outcome directory. Closure body outcomes have distinct identities; capture plans move into the parent's payload, and Mid no longer snapshots every closure for local cell checks. Session identity checks are added. Replaced private-field negative controls (eight old fields) are consolidated into directory privacy and sealed-payload privacy controls; the original intent is preserved at the two actual boundaries.

Development builds through `20261022T033421-build-763af5` pass using the fixed phase-two carrier. The saved draft `bin/plewc-source-owner-bindings` is not an adopted carrier or seed. Identifier targets/global addresses now freeze with source facts; Mid and final access readers no longer recover them through the construction TypeCache/cursor.

Focused AOT execution exposed and corrected three distinct cursor/state defects: closure verification retained the parent's owner, late call-argument constraints read the last traversal cursor, and a repeated inline closure walk was mistaken for a recursive preparation request. The full parent request remains active across its construction/check walks; closure publication is separate and occurs only after nested obligations close. Post-outcome guards now reject newly created nodes as well as previously recorded nodes. Retained-reader, foreign-session, stable-failure, post-success/post-failure writer controls and both privacy controls pass in the focused `closure-request-slice` execution. A diagnostic-only aggregate copy preserved the assertions while showing returned diagnostics; the unchanged aggregate fixture must also run in the milestone suite.

The next candidate also moves expression requirements into the owner-local manifest and removes the replaced global sparse obligation lists. Required rows are checked before publication; tentative non-value/capability rows do not cross the sealed boundary. Closure Mid parameter/result/block readers consume the body header, with construction captures remaining in the enclosing payload. Development build `20261022T035206-build-e90085` passed; saved candidate: `bin/plewc-source-owner-manifest`.

Required before completion: broader aggregate/try/pattern/generic/provided/closure/global AOT and lazy execution, complete removal audit, storage-cost workloads outside formal timing, fresh fixed point/formal median below seven seconds and applicable milestone gates. Main and seed remain unchanged.

Formal self-host run `20261022T035434-self-host-53544b` reached generation-3 fixed point, but **failed the task performance criterion**: 11.142268 / 10.668936 / 10.647393 seconds, median **10.668936**. The unchanged-source phase-two carrier took 6.113867 seconds for generation 1. This is a correctness/fixed-point result, not permission to adopt the candidate. Diagnostic CPU sampling is separate (`tmp/phase3-owner-facts/profile-manifest`); it places most additional work in source preparation, including repeated whole-expression reads and owner/index lookup. Investigate the construction read path without restoring all-owner semantic storage or weakening required rows. Broader normal-suite correctness is still pending.

The open-builder custody gap is fixed: the directory owns one active builder value and private inactive values, while publication retains only immutable Ref-backed payloads. A Comp branch cannot mutate or empty the original builder/payload. Stable reader indexes are saved with Cursor; repeated Mono expression reads reuse their owner's handle instead of acquiring directory storage per expression.

Development build `20261022T045019-build-e4c356`, saved `bin/plewc-source-owner-readers`, passes the expanded AOT slice (15 run fixtures and 2 privacy rejects; `tmp/phase3-owner-facts/readers-slice/summary.json`). It covers value-builder forks, stable failures and retained readers, cross-session rejection, 128-read acquisition controls, foreign body/statement completion, aggregate/try/match/binding/global/closure consumers and the corrected normal reference/async/access cases. The new branch fixture initially compared a pre-preparation type ID with a legitimately refined post-preparation ID; its final stability assertion now saves the published type before advancing the other branch. Its isolation assertions are unchanged.

The preceding scoped candidate reached generation-2 fixed point in `20261022T044054-self-host-6a4524`, median **6.900832** seconds (7.236029 / 6.900832 / 6.777429). This satisfies the median target for that source; it is not a measurement of subsequent reader-registry changes.

The removal audit found another in-scope authority: `Arena.semanticValueBlocks` is still written by Record/refinement and read by Mid's value-block epilogue. Move its result/completion rows into each owner's payload and delete the array and its construction/final readers before claiming this increment complete. Required block rows must close with their expression manifest; tentative optional rows cannot become sealed success. Normal/generation/lazy/storage-cost and the final candidate's fixed-point/performance gates remain pending.
