---
id: met-iv6d
status: in_progress
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
- Apply met-7ust: reject every second part request, including same-parent
  explicit duplicates and explicit+auto. Aggregate annotations into one auto
  request per source file before the common admission; keep explanatory origins.
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
alone; role/edge ownership is the natural finite repair. The user has selected duplicate rejection in met-7ust; contracts now distinguish
annotation aggregation from membership admission. No product repair is claimed.

## Implementation plan before product mutation

Use private source-discovery entries, not generic Bind/path-buffer rows. Each
entry owns resolved path bytes, module identity, Root/Part role and introducing
parent/origin (written/automatic source offset; initial roots have no source
edge). A private graph owns the append-only work queue and one admission
operation returning either its existing/new index or a typed conflict. Only
Root+Root reuse succeeds; any second Part admission or Root/Part conflict
refuses. This decides membership once; readers do not infer roles from rootSeen.
Retain source-edge provenance for both diagnostic locations.

Initial entry/ambient/gen-support roots use the same Root admission before
any Part can exist. File processing reads the stored role directly. Written
use/part and the file's single aggregated auto-part request call the same
admission. Module id allocation advances only for newly registered roots;
package-root lookup and imported module identity read the same entries.
Remove competing pathSeen/moduleIdOfPath and auto-part skip decisions from
this loader, without removing independently used Raw Path APIs indiscriminately.

The core accepts no Comp, source flags or callback and returns typed structural
conflicts, not Source reports. The actual fresh parser/edge owner interprets
its proven refusal and preserves Source through service/session/CLI. Format
diagnostics only on conflict; avoid per-edge report allocation or reparsing.
Initial-root invariants must be distinguished from user-authored edge failures.
No whole Comp snapshot or repeated source parsing is permitted.

Before implementation, review the private types and call sites, then execute
fixed-carrier RED/positive controls. Include both ordering directions, explicit
repeat, explicit+auto in both orders where applicable, multiple annotations
producing one auto edge, legal repeated Root use, different parents/modules,
part cycles and generated role conflicts. Native controls must distinguish raw
structural refusal from the actual fresh-source authority and exact origin.

## Active implementation checkpoint

The adopted carrier8f5e342f1577 executes36 actual CLI cases:9 positive modes
pass,27 required refusal modes expose erroneous acceptance or Unclassified
transport. Inputs unchanged. [Matrix RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/matrix-red.json).

Private SourceDiscovery/DiscoveryEntry replace loader-local Bind/pathBuf and
rootSeen. Root+Root reuse retains stored module IDs; duplicate Part and role
conflicts share admission. Written and per-file auto requests retain parent,
origin offset and automatic origin. The actual fresh owner creates Source from
the typed conflict; Raw report formatting remains Unclassified and carries
notes without granting admission. Source offsets use the first named macro
request, since shared Syntax directive top-item spans are currently zero;
unspanned empty markers retain the containing parent-file origin and existing
auto inclusion behavior. No parser rescan or new empty-marker rule is added.

First native structural/owned-source and exact primary/previous location
checks pass; generation entry suppression and dependency auto conflict also
pass. Latest-source repeat and session retention are still pending. No fresh
compiler, whole regression, formal performance or final recognition claimed.

## Independent implementation review

qualified_member_plan confirms one acceptance authority, correct stored module
IDs/roles, retained use DAG edges and bounded core/owner responsibilities. One
confirmed diagnostic defect (auto against Root incorrectly advised deleting an
explicit part) is fixed with role-specific advice and exact native assertions.
Latest native source/core/origin/gen and real session retention pass; Source
location, previous note, automatic explanation and eager/session copies survive.
Two intermediate compile setup failures from a missing outer give are repaired
and not counted as RED. [Native evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/native.json).
Fresh CLI, applicable whole and formal performance remain outstanding.
