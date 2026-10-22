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

Compiler `9b2832bc` implements owner-local builder values, immutable Ref-backed payloads and a scoped reader registry. Source expression/binding/completion/header, identifier/global address, value-block, aggregate/try/pattern and closure construction/body facts use that backing. Mid and Mono consume the moved facts from explicit successful owners. The replaced all-owner tables, sparse required-expression list, value-block arena and full-table acquisition snapshots are removed. Construction APIs remain construction-only; declaration callable registration still does not require a successful callee body. Operation/evidence/origin families not moved here remain later work, so this is not a complete CheckedBody or execution token.

Controls cover retained-reader stability, Comp builder forks, separate globals/closure identities, absent/foreign facts/session, stable failures, post-success/post-failure new-node writes and private directory/payload boundaries. Focused AOT slices pass. Diagnostic workload counts at `f6ac018a` scale from 16/64 small owners (32/128 rows) and 32/128 conditional bindings in one owner (322/1282 rows); 128 retained reads reacquire storage zero times. These counts are not byte-allocation or timing measurements and complement the source/removal audit.

Exact source `85aa9a96` reaches generation-two fixed point with formal runs 7.191491 / 6.670207 / 6.676504 seconds, median **6.676504**, below seven. The rejected initial median 10.668936 and its input identity remain in the evidence, rather than being relabelled a successful measurement. The saved final measured binary is `bin/plewc-source-owner-final`, SHA256 `02d92718586ef35fdef653aa21a77419bba0afde9f71d6417cc500c568df8a6d`.

Internal fixtures retain assertions/golden output while supplying explicit construction owners and real recorded bindings; sealed readers ignore later construction-cache edits. Tests of removed private fields/index methods are consolidated at the actual private directory/payload boundaries. Mid's invocation completion and generator global reachability now consume scoped successful facts. The latter's helper used to call a construction query indirectly; the removal audit follows that call path, not only names directly appearing in Mono.

The exact `85aa9a96` measured binary passes final normal `20261022T070727-test-d92523`
(run1419 / panic47 / reject967 / part91 / partreject84 / zero skip/failure),
generation `20261022T095415-gen-9e33dc` (24 positive / 5 rejects), dependency
`20261022T095515-deps-305f4d` and LLVM22 ASan/LSan
`20261022T095520-asan-a86744` (A1 / B2433 / C1419 / D47 / E76). All exit zero
with unchanged inputs. Full normal includes lazy CLI and native/tooling controls.

The subsequent `20c1ec47` reader correction replaces whole 688-byte
SourceBodyData getter arguments with just required rows/indexes. Owner/session
guards and lookup results are unchanged. Twenty focused AOT cases, two privacy
rejects and full generation 24/5 pass. Same frozen-source alternating comparisons
measure 6.717053 -> 6.490937 seconds, with identical LLVM; these are diagnostic
medians, not formal speedup claims. Formal `20261022T112014-self-host-d515b4`
reaches generation-two fixed point with runs 7.075059 / 6.705942 / 6.566374, median
6.705942 seconds. Exact measured binary is saved as
`bin/plewc-source-owner-narrow-fixed`, SHA256
`3a6391b9c136fc59a2153815179a6d81381aa3ca3153ce96ba4acf6468453ae9`.

This component remains open until applicable final-reader coverage and evidence
are reconciled at its final revision. Continuing met-ucze also removes the remaining
post-success call-storage summary rewrite, which must precede operation sealing.
Earlier full gates are not attributed to later binaries. Main/seed/adopted carrier
remain unchanged. Evidence and reproduction controls are in meta
`evidence/existing-feature-conformance/source-owner-facts/`; parent integration
gates and the full eleven criteria remain separate.
