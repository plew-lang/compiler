---
id: com-p2qh
status: in_progress
deps: []
links: []
created: 2026-11-25T22:19:51Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [performance, mid, verification]
---
# Narrow physical write-path verification inputs for performance recovery



## Contract and finite scope

Split only canonicalMidWritablePhysicalPath from com-0t9x; remaining API
narrowing stays there. Restore the active phase-three <=7.5s gate without
weakening canonical verification. This is an existing-feature input-boundary
refactor, not a new source rule or general Mid redesign.

The helper consumes Mid locals/projections and a readonly type-head reader,
not Comp, Arena as a whole, callbacks or hidden captured compiler authority.
Ir owns reader construction from one synchronized Arena snapshot. Private
arrays expose only the existing reference-head predicate. Comp.isMutableRefInst
uses that same predicate; no duplicate semantic decision or new type resolution.
Preserve name/arity/range/ref0 semantics and typeRows/typeTerms synchronization.
Reader lifetime is the synchronous verification call; no source-wide cache.

## Actions and completion

- Establish behavior-fixed controls for empty/field/tuple/index paths, local and
  nonlocal roots, mutable/immutable/nested dereferences, invalid ref/arity, and
  both real caller refusal codes. New API tests may change signatures as part of
  this internal refactor; no manufactured RED is required for unchanged meaning.
- Replace both production callers and the helper signature. Prove unrelated
  compiler inputs cannot reach the leaf through a wrapper, closure or capture.
- Preserve complete writable-path validation, projection order, ownership errors
  and normal MutableRef replacement. No broad acceptance or verifier skip.
- Independently review the finite change; verify new compiler smoke, affected
  controls, fixed same-source LLVM and timing, required formal gate. Parent
  met-un2r still owns its full CLI/whole/closure gates.

## Plan and evidence

qualified_member_plan independently accepts this finite split and the reader
boundary. Existing cost evidence is in com-0t9x; fresh CPU sample and symbol map
are tmp/phase3-forward-frontier/type-visibility-{cpu-sample-v2,symbol-map-v1}.
These are diagnostic samples, not formal timing. Early dense-recipe fast path
was not adopted after same-source comparison did not demonstrate improvement.


## Finite implementation checkpoint

TypeHeadReader has private name/type arrays and private construction through
Arena.typeHeads; public matches is only the retained head/arity predicate.
Comp.isMutableRefInst delegates to it. The leaf receives locals, projections,
reader, body and place; both actual callers construct a synchronous snapshot.
No Comp/Arena/closure escapes through the new boundary.

Native behavior-fixed baseline, narrowed path matrix, snapshot and actual
Overwrite/Drop caller refusals all pass with unchanged inputs. Tests preserve
MoveUnavailable and DropUnavailable, respectively. Independent source review
finds no confirmed must-fix and confirms old full-Comp paths are gone. No new
source semantics or invented bug RED is claimed. Fresh candidate and timing
remain pending. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/physical-write-path-inputs/checkpoint.json).
