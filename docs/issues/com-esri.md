---
id: com-esri
status: closed
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [design, verification]
---
# Classify existing-feature conformance and bounded work units

## Input and Method

Phase 1 of [com-604k](com-604k.md). Pinned compiler source `f89857b1f3f96763073987ae6e55996faed3ebb5`, spec `1e0c4d0`, Syntax `00f740e1`; the later seven-second policy commit changes documentation only. Reuse detailed static audit [com-nsxb](com-nsxb.md) and restart reconciliation [met-j9mv](met-j9mv.md). Checked current Sendability consumers in Infer/Type and Infer/Check, reference predicates in Codegen/Mono/Helpers, existing impl-deinit lowering and scalar-only async/C boundary evidence. This phase performs no compiler/probe/test/sanitizer/performance execution and does not label unverified combinations reproduced bugs.

The fixed inventory below covers all 53 open issues preceding this classification, including mixed/new/optional work. It records the classification at this input, not future live status or a second global issue index. Closed review/evidence issues remain closed and preserved; they are not reopened as implementation tasks. Changes to a work contract belong in its owning issue and the integration dependencies.

## Classified Inventory

Detailed scope, rationale, consumers and completion conditions remain in the linked owning issue. This snapshot does not duplicate those live contracts.

| Existing issue / owning scope | Classification |
|---|---|
| [com-042v](com-042v.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-0k37](com-0k37.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-0mwd](com-0mwd.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-0oxy](com-0oxy.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-2jrh](com-2jrh.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-2p9p](com-2p9p.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-2z5l](com-2z5l.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-5n4i](com-5n4i.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-6ygf](com-6ygf.md#existing-feature-conformance-classification) | Included repair |
| [com-7g6i](com-7g6i.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-7knz](com-7knz.md#existing-feature-conformance-classification) | Evidence: design review, not an implementation work unit |
| [com-8ec0](com-8ec0.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-8j0w](com-8j0w.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-8w4c](com-8w4c.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-9ttw](com-9ttw.md#existing-feature-conformance-classification) | Included repair |
| [com-ao7z](com-ao7z.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-b1ro](com-b1ro.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-ej0z](com-ej0z.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-gyup](com-gyup.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-h4dh](com-h4dh.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-ipdk](com-ipdk.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-lndr](com-lndr.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-lsbk](com-lsbk.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-mnsx](com-mnsx.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-nkoa](com-nkoa.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-p10m](com-p10m.md#existing-feature-conformance-classification) | Included repair |
| [com-qnyl](com-qnyl.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-qzpm](com-qzpm.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-t0kz](com-t0kz.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [com-tijs](com-tijs.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-tn1m](com-tn1m.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-uutc](com-uutc.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-vy62](com-vy62.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [com-w4c2](com-w4c2.md#existing-feature-conformance-classification) | Included repair |
| [com-wqd7](com-wqd7.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-ydgx](com-ydgx.md#existing-feature-conformance-classification) | Included repair |
| [com-yr1o](com-yr1o.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [com-zgk9](com-zgk9.md#existing-feature-conformance-classification) | Included bounded verification |
| [com-zowv](com-zowv.md#existing-feature-conformance-classification) | Outside: optional optimization |
| [met-0139](met-0139.md#existing-feature-conformance-classification) | Included bounded verification |
| [met-2t3l](met-2t3l.md#existing-feature-conformance-classification) | Included repair |
| [met-6e6k](met-6e6k.md#existing-feature-conformance-classification) | Included repair |
| [met-acfl](met-acfl.md#existing-feature-conformance-classification) | Included repair |
| [met-b04w](met-b04w.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [met-b2la](met-b2la.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [met-c58b](met-c58b.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [met-ia09](met-ia09.md#existing-feature-conformance-classification) | Included repair |
| [met-k7ks](met-k7ks.md#existing-feature-conformance-classification) | Included repair |
| [met-nm1w](met-nm1w.md#existing-feature-conformance-classification) | Outside: unimplemented or independent release capability |
| [met-op15](met-op15.md#existing-feature-conformance-classification) | Mixed: split current subset |
| [met-rzt4](met-rzt4.md#existing-feature-conformance-classification) | Included bounded verification |
| [met-si6j](met-si6j.md#existing-feature-conformance-classification) | Included repair |
| [met-ucze](met-ucze.md#existing-feature-conformance-classification) | Included repair |

## Bounded Split Contracts

The full producer/publication/final-consumer/removal and verification contract is in each new scoped issue: [com-kp3y](com-kp3y.md) source-owner storage, [com-7u06](com-7u06.md) scalar async, [com-legt](com-legt.md) current reference/intrinsic identity, [com-f8bw](com-f8bw.md) existing sendability, [com-2o4w](com-2o4w.md) scalar/pointer C boundary, [com-cgdk](com-cgdk.md) admitted process/storage, [com-fkxl](com-fkxl.md) current initialization, [com-j3pp](com-j3pp.md) admitted closure environments and [com-fuo8](com-fuo8.md) existing completion/divergence. Together with [met-8b8w](met-8b8w.md), there are ten scoped work units. The original mixed parents keep the unimplemented remainder.

[met-8b8w](met-8b8w.md) records the current-gen three end-to-end increments; its mixed parent com-vy62 retains the unimplemented macro/macrointerface public-role family. This split closes the P2 boundary ambiguity found by [independent completion review](met-8jd4.md). met-2t3l migrates an existing supported impl-deinit form and rejects the wrong location without adding capability generics. com-7g6i checks real recursive cleanup before classifying stack cost; com-0k37/met-rzt4 preserve exact bounded historical controls rather than a new infinite-termination proof. Current frontend acceptance cases from com-uutc/ownership from com-5n4i are assigned to the typed-source and existing lifetime units; rejected missing shape support is not silently enabled.

## Cross-Domain Coverage and Preservation

All 18 audited domains map to the included work: architecture/state/body/types/generics -> met-si6j and current reference/sendability; sources/lookup -> com-w4c2/com-9ttw/met-0139; syntax -> com-2p9p/met-2t3l and admitted completion; metaprogramming -> met-8b8w (new public-role family remains in com-vy62); Mid/ownership/passes -> typed-source completion, com-gyup/com-wqd7, current async/closure and collection units; ABI/LLVM -> current C boundary/com-6ygf/com-8w4c; runtime/driver -> current async/process/initialization/recursive cleanup; diagnostics -> met-k7ks/com-lndr; verification -> those units' controls, com-ydgx and the integration gates. Existing typed-stage entries, structural opcode queries, common runtime, explicit instance keys, module/context transfer and one-shot registry policy are preservation controls, not assumed missing systems.

Baseline is the recorded current-source generation-3 fixed point/7-run median 6.688276 seconds, below the approved 7-second goal; its original scope is unchanged. Do not rerun unchanged baselines for classification or promote the dirty compiler binary. No spec/API choice is needed to classify these current contracts; new meaning, ambiguous large tradeoffs and current-subset deviations that would require weakening an adopted contract still stop for user judgment.

## Outcome and First Implementation Unit

Classification and work-unit planning are complete at this pinned scope, with the macro public-form split clarified under [met-8jd4](met-8jd4.md). All prior open issues have a disposition and all audited domains have a current owner or explicit future exclusion. Required unverified contracts remain bounded verification tasks, not unclassified work or completed fixes. Source/effect availability is recorded as a producer prerequisite; actual tk edges distinguish it from preferred sequence. No compiler implementation issue is closed by this result.

Next is com-p10m: reproduce overflow/allocation failure with bounded controls, centralize the common storage-floor checks through final use, preserve valid growth/CoW and failure-state ownership, then perform applicable standard validation. No new capacity policy, new syntax or allocator overcommit experiment is necessary. There is no blocker to starting this settled unit. Preserve met-si6j and the scoped children for later phases.
