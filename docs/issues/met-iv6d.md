---
id: met-iv6d
status: open
deps: [met-7ust]
links: []
created: 2026-11-26T04:29:30Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, diagnostics, verification]
---
# Make source discovery membership independent of traversal order


## Contract and confirmed failure

Spec15 forbids a part file as an independent use target and assigns each part
at most one parent. Design sources-and-modules§4 requires explicit membership
and edge provenance, independent of traversal.

Fixed product2d482923 accepts Main→Owner,Main→Consumer,Owner-part→Shared,
Consumer-use→Shared when Owner is enqueued first; reversing the two Main uses
rejects. All check/AOT/ORC agree. Auto-part silently reuses an independent root
or a different parent's part too. [Executed evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/README.md).

## Finite repair and guarantees

- Replace membership-free local Bind queue interpretation with one private
  discovery entry/edge authority retaining resolved path, module, Root/Part role
  and introducing edge/parent provenance. Define input/output and ownership
  before product changes; do not hide mutable Comp behind a helper callback.
- Route handwritten and generated membership through that same admission.
  Dedup legal repeated use, reject Root↔Part conflict, different part parents,
  module conflict/cycle without order-dependent acceptance. Preserve required
  source ranges, std roots, package contexts, declaration publication and
  gen-mode entry-output suppression; no resolver/DAG-wide redesign.
- Resolve same-parent repeated part policy first in met-7ust. Do not silently
  promote the existing same-parent diagnostic as Source without specification.
- Establish meaningful fixed-candidate native/CLI RED from minimal single-cause
  inputs. Cover both orders, legal shared use, same/different-parent part,
  same/different module, explicit/auto interactions and original source edges.
- Separate acceptance correctness from Source transport certification. Only
  proven violations at the actual fresh edge admission may generate Source;
  Raw/foreign/malformed graph helpers and Input/Tool/Internal/Limit keep their
  domain. Returned/failed-session/final CLI consumers preserve typed results.
- Fresh applicable regression, fixed point/formal<=7.5s, independent review,
  synchronized evidence and bounded artifact retirement before closure.

## Ownership and exclusions

Parent com-604k owns existing-feature design conformance; com-yeua depends on
this finite producer repair before classifying its membership refusals. Other
com-yeua producers are not globally blocked. This is part of required current
work, not an unimplemented feature or a reason to reopen all of phase2.
Closed com-w4c2/root-use children do not certify this newly demonstrated case.
com-ntm8 retains masked partdiamond/crossmodule/missing reason fixtures, which
are not sufficient oracles here. General parser/path API narrowing and missing
input/phantom-dependency errors are not included. Parent/phase3/main stay open.

## Independent scope advice

qualified_member_plan confirms a discovery acceptance defect, not transport
alone; role/edge ownership is the natural finite repair. It confirms that
same-parent repeat acceptance cannot be inferred from forest alone. User
judgment is pending in the prerequisite. No product repair is claimed.
