---
id: com-v5zn
status: closed
deps: []
links: []
created: 2026-11-12T09:35:59Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Compare short-projection types by original declarations

## Guarantee and Finite Work

Use the admitted declaration identity when comparing source type terms during
short-projection selection, including before the late nominal-resolution pass.
Both prepared clause receiver matching and complete trait instance deduplication
must compare original nominal declarations, lexical ParamIds and structural
children. A qualified use and a selective alias of the same declaration are
equal. Identical spellings from different modules are distinct. Use the
admitted module table and shared semantic type traversal.

Evidence and original inputs are in [com-erlx](com-erlx.md#checkpoint-exact-identity-at-short-projection-selection).
This issue owns the shared comparison and its short-projection consumers.
Original owner lifecycle, pending-clause preparation and failed-prefix
publication remain with com-erlx. Remaining view admission and evidence
transport remain with com-3jtd. Preserve existing specifications.

## Required Scenarios

- The prepared receiver matches its original nominal declaration, including
  a qualified use and an alias. It rejects an identically named declaration
  from another module.
- Two trait instances whose positional arguments contain different nominal
  declarations remain ambiguous. Two aliases of the same complete instance
  collapse to one candidate. Preserve nested argument and binder identity.
- Preserve later-clause/nonmember/legacy and associated-type controls where
  the old carrier supports them. The pending qualified subject case remains
  in com-erlx and is not certified by the ready-clause fixtures.

## Completion

Record RED on the pre-fix candidate with exact rejection reasons or observed
false acceptance. Execute the new fixtures through the compiler and existing
controls, follow [TDD and independent review](../../../agents/development-workflow.md#独立レビューと完了認定),
check the performance baseline, and record the exact candidate and remaining
scope. The product path must consume the shared comparison in both places.

## Outcome

Resolved at `09184bc6`. Before late nominal resolution the source comparison
uses admitted declaration-name offsets on both sides. Both short-projection
receivers and complete-instance argument trees use the shared structural
walker. Qualified heads bypass lexical binder and associated-name lookup;
unqualified binders still choose the nearest matching ParamId.

RED on the pre-fix `f58e0884` candidate: both positive fixtures rejected, both
negative fixtures accepted. The first comparison candidate `c8a35caa` fixed
those basic cases, but failed both same-spelled binder controls. The final
nested variants passed on the development candidate `bb83c356` and the
formal candidate `378d4f6e` via the normal part/partreject workers. The two
positive entries also ran in lazy mode on the development candidate. Fourteen
internal cases across both lowering adapters plus the prepared conditional
conformance check/AOT/lazy and six associated runtime controls passed.
The failed-impl-prefix scenario remains owned by com-erlx.

Independent review found the qualified binder and associated-name collision;
the reviewer confirmed both adapter repairs and fixture registration. The
distinct/alias fixtures also place the nominal comparison under a structural
argument child. Qualified/later pending-subject preparation and impl-bound
publication remain with com-erlx.

Formal validation `20261112T094546-self-host-2e4b6a`, carrier `c36716d9`,
reached generation-3 fixed point, input hashes unchanged. Exact measured
compiler is saved as `bin/plewc-com-v5zn-fixed-20261112`. Three compiler times
were 7.189750, 6.656284 and 6.631129 s (median 6.656284 s). Same final source,
warm then alternating old and new for three runs each, yielded 6.428045 and
6.548543 s respectively. This comparison includes com-erlx checkpoint changes
and does not isolate the cost of this issue. Generated LLVM was stable within
each carrier. No seed or main promotion.
