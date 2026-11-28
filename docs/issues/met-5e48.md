---
id: met-5e48
status: in_progress
deps: []
links: []
created: 2026-11-28T15:39:46Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [mid, performance]
---
# Measure and eliminate repeated draft statement prefix copies


## Guarantee and sequence

Measure midAppendStatement's draft mutation protocol before repair. Current code retains a MidBlock, copies its statements Array, appends while the old array remains held, then replaces the block. Post-Array native assembly gf7393 retains the old statement buffer before Array.append and drops the retained old MidBlock afterwards. MidBlock destructor pwdrop894 is present in the sampled Mid-building window. Confirm physical CoW copy count/elements/bytes with a private scoped runtime probe; do not infer time from O0 counts.

If confirmed, append through the existing draft place rather than retaining/replacing its whole prefix. Preserve out-of-range no-op, closed-block no-op, statement order and payload, terminator identity, other blocks, and external CoW snapshots. No change to canonical storage, ownership semantics, Array runtime/LLVM product code, checks or source admission. Behavior-fixed before/after controls must explicitly retain outer and inner snapshots. Enumerate actual helper callers; verify targeted statement/CFG controls and same-source LLVM/time. Independent boundary/source/test/performance review, final related whole gate shared with pending performance changes. Do not close stage3/parent/whole gate from this finite repair.

Design: mid.md Draft Construction permits owned temporary arrays; it does not require repeated prefix replacement. Excludes pooled canonical transforms, branch algorithms, deinit timing changes and generic Array/ARC redesign.

## Boundary decision and before controls

Independent boundary review confirms only draft MidBlock.statements needs mut val, matching ordinary place composition (spec03). Terminator stays val and canonical MidBlockNode/ranges unchanged. Direct nested-place append must follow bounds/open guards with no retained prefix temporary. No language/architecture decision is introduced.

Private runtime scope around append measured381605 prepares/queries,256782 shared-buffer reallocation events,755249 copied elements/138965816 bytes (max prefix59), no explicit-copy calls and scope inactive at exit. O0 probe, not an elapsed-time claim; native target/declared std/manifest/lock pre/post fingerprints unchanged and target LLVM equals preceding counter-free-equivalent output. The C hooks are diagnostic only; product runtime/LLVM were not changed.

MidStatementAppendMain/test-mid-statement-append baseline and modified native probes passed. Controls retain real outer/inner snapshots and other-block aliases, verify statement/place projection payload/order, empty/bounds/closed3kinds and terminator identity; additional direct Open checks are being repeated before/after. Review found no product source correction required. Existing all_diverge/evaluation_boundaries ordinary functions necessarily traverse prepareCanonicalForLlvm→Ready→genLlvmPreparedMidBody (Backend/Llvm/Any, no AST fallback) and Mid/Program→templates→buildParametricMidBody. Their baseline native execution and mid_if_all_diverge passed. After fresh candidate plus copy/time validation remain pending.

## Counter result of local prototype

Direct append preserves all private before/after controls (now including explicit Open and outer terminator checks), but the physical counter is unchanged:256782 shared reallocations/138965816 bytes, while prepare checks double381605→763210. Target LLVM identical. [evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/draft-append/). No copy-elimination completion claim. Spec03's indexed nested get-modify-set model explains a remaining temporary ownership path through Access; removing that requires its own stability/effect proof rather than bypassing selection/checks. Optimized timing is pending before prototype adoption/rejection.
