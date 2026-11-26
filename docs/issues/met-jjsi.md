---
id: met-jjsi
status: closed
deps: [com-ctl6]
links: []
created: 2026-11-26T02:35:43Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain non-impl part admission refusals through source loading


## Contract and selected boundary

Spec15 and design sources-and-modules restrict parts to impl/part/macro items.
Current product324c3cfc correctly rejects actual partfreefn but leaves its
domain Unclassified. Source errors from this same structural admission class
(types/free functions/extern/top-level value/re-publication) must retain their
source origin through failed service/session construction and check/AOT/ORC.
The pure PartSyntaxCheck and private source String append/register/parse owner
are established by closed com-ctl6; do not add a second checker or public
Source permission. Raw roots/items must remain non-Source.

## Actions and guarantees

- Freeze adopted fffc4df776f2 and run existing partfreefn across three CLI modes
  and actual native producer/session retention to establish target RED.
- Exercise each distinct structural admission branch with fresh source, not a
  caller-supplied AST: free fn, type, extern, top-level val, Published wrapping
  and public part where parser accepts it. Distinguish parser rejection from
  the intended admission rule. Cover impl/nested part/macro/root positives;
  generated and handwritten membership obey identical admission.
- Typed shared core remains the single decision; actual fresh OtherPartItem
  generates Source with its original offset/message. Raw and foreign roots,
  direct item adapters, invalid ranges, same-text injected non-Source reports
  and unrelated loader failures do not gain source origin. Existing root-only
  use producer and final consumers remain correct.
- Retained/drained/failed-open diagnostic preserves the domain; no live cache
  is invented after pre-Lower construction fails.
- Meaningful native RED/GREEN, fresh CLI, applicable regression/fixed-point
  <=7.5s, independent guarantee review, evidence preservation and cleanup.

## Excluded and neighboring owners

No change to language rules, queue/graph membership, name lookup, source
acquisition or all255 residuals. Missing input, duplicate parent/cross-module
part ownership and use DAG failures require their own producer investigation.
com-ntm8 retains known masked partmissing/partdiamond/partcrossmodule reason
controls; partfreefn itself has a well-typed alternative, so this task does
not presume that fixture is erroneous. com-qt11 retains general parser/Raw API
capability narrowing and opaque-node reader validity. com-k4c9 owns gen channel.
RootUseMain's internal assertion preserving OtherPartItem Unclassified belonged
to com-ctl6's excluded boundary; this repair must update that internal control
to the newly adopted producer guarantee without weakening Raw controls.

## Starting evidence and completion

[Latest whole](../../../evidence/rejection-domains/diagnostic-domain-implementation/root-use-refusals/whole.json)
records3313 unchanged cases and255 failures, including partfreefn. Current
root-use native also demonstrates its Unclassified domain as an unaffected
control. No new defect is inferred from wording alone.

Close only the named source-admission class with exact source/hash/results and
independent review. Parent com-yeua, phase3, broader API task and main remain
open. Finite plan must be reviewed before product change.

## Outcome and evidence

Product2d482923 closes this selected structural admission class. The existing
private source String operation generates Source from its fresh OtherPartItem
verdict. Raw/foreign/direct-item adapters and InvalidRange retain their domains.
The message leaf has one authority; no second checker, lookup, snapshot, replay
or public source permission was introduced. Parser does not accept pub part,
so its Raw import alternative is not claimed as a fresh source path.

- Adopted fixed fffc reproduces six actual CLI domain misses (handwritten and
  generated part, check/AOT/ORC). Native producer/session RED assertions execute
  after successful compile/link; setup failures are not counted.
- Native GREEN covers source matrix, Published recursion, allowed impl/part/
  macro directives, Raw/direct-item/foreign/other domains, failed session
  retention, and root-use regression. Real handwritten/generated paths assert
  exact diagnostic and Helper.pw/Main.gen.pw line2.
- Fresh build20261126T024200-build-c45aa7 passes; CLI15 and root-use21 pass,
  also on the saved measured carrier. Same-source7.311515→7.297441s, all LLVM
  equal. Formal20261126T025103-self-host-41f505 reaches G2 with unchanged
  input and median7.350680<=7.5s.
- Whole20261126T030736-test-e1230a completes3314 cases:3313 shared source
  hashes unchanged plus one explicit generated-part regression PASS.255→254
  failures, only existing partfreefn resolves; no new failures, changed
  remaining reasons, removed cases or skips, invariant inputs.
- Independent qualified_member_plan accepts plan, product and finite final
  guarantees. Its request for exact cause/location assertions was implemented
  and rechecked; no mandatory finding remains.

[Native](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/native.json),
[fresh](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/fresh.json),
[formal](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/formal.json),
[whole](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/whole.json),
[carrier](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/carrier.json).

After consumers/review and evidence preservation,36 generated native/comparison
files/1266070173 bytes were retired. Keep exact frozen product, latest whole254
failure payloads, formal generations, old/new frozen carriers/std, source/
manifest/result/log/runner evidence and required backend archive through parent
reconciliation, then reassess exact reproduction needs.
[Retirement](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/retirement.json).
Parent, residual254, broader API and main/seed remain uncompleted.
