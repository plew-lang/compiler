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

## Implemented contract and outcome

Productc6720051 closes this finite discovery class. Private SourceDiscovery
entries own path/module/Root-Part role/parent/introduction. One admission
operation handles initial roots, written edges and the single collected auto
request. Root reuse retains its actual module ID and still records every use
edge for the existing DAG checker. Processing reads stored role, not rootSeen.
The loader no longer chooses acceptance via pathSeen/moduleIdOfPath or an
automatic-request skip. General Raw Path APIs are not removed by this repair.

The core returns structural conflicts without Comp, callbacks or source flags.
Raw report formatting is Unclassified; the actual fresh parsed-edge owner
creates Source while retaining both introductions. Reports/notes allocate only
on refusal. Initial roots are registered before any Part can exist. Named
macro requests supply the first relevant annotation span; legacy unspanned
empty markers keep their existing inclusion behavior and parent-file origin.
No parser rescan, global source permission or second membership validator.

- Fixed adopted8f5 matrix36:positive9 GREEN, required-refusal27 RED
  (erroneous acceptance or lost domain). Frozen inputs unchanged.
- Native core Raw/source distinction, nonmutating refusal, root/module identity
  reuse, actual order/parent/role conflicts, exact request/previous positions,
  auto explanations, entry gen suppression/dependency preservation and retained
  failed-session diagnostics pass. Setup compile failures are not RED.
- Independent qualified_member_plan accepts plan, implementation and final
  guarantees. Its confirmed wrong auto/Root corrective advice was fixed and
  tested; no mandatory finding remains.
- Fresh build20261127T024805-build-2eb17b, membership36 and existing part15/
  root-use21 pass. Saved measured carrier membership36 passes. Same-source
  old7.272381/new7.237265s and identical LLVM, without claiming all timing
  differences as contribution.
- Formal20261127T025829-self-host-adbbca:G2, input invariant, median7.325122
  <=7.5s. Generation20261127T031507-gen-a7d02c passes unchanged inputs.
- Whole20261127T031803-test-72ea07 completes3314 identical-source cases:
  254→252 failures, only partdiamond/crossmodule resolve; no added failures,
  changed remaining aggregate reasons, removed/added cases or skips.

[Canonical evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/native.json),
[fresh](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/fresh.json),
[formal](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/formal.json),
[gen](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/gen.json),
[whole](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/whole.json),
[carrier](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/carrier.json).

After consumers and review,27 generated native/comparison files/1130234499bytes
were retired. Keep latest whole252 failure payloads/receipts, frozen product,
formal generations, old/new frozen carriers/std, backend archive, RED/source/
result/runner/diagnostic and gen records through parent reconciliation, then
reassess exact reproduction needs.
[Retirement](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/retirement.json).
com-ntm8 still owns masked existing fixture oracles; recognition relies on
independent single-cause controls. Parent com-yeua/phase3, residual252, full
green and main/seed promotion remain uncompleted.
