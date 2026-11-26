---
id: met-jjsi
status: in_progress
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

## Plan review and first RED

Independent qualified_member_plan accepts this finite scope. Cover actual
structural branches, not combinatorial declaration variants; include an actual
generated non-impl part. Parser parseSyntaxPublishedItem does not accept
`pub part` (syntax/src/_.pw rejects it as expected-declaration after pub), so
its Raw import branch is not claimed as a fresh-parser Source path.

Fixed adopted fffc CLI: partfreefn and new explicit generated_part_nonimpl each
reject correctly across check/AOT/ORC but are Unclassified (six actual domain
misses), nine root/shared-part positives pass. Native actual session-open RED
part-item-service-native-red-v1 fails its Source assertion after successful
compile/link. Native source matrix covers default OtherPartItem, Published
recursion, allowed impl/part/directive, Raw and same-text domains; both plain
and actual-generated variants reach the target missing-Source assertion after
all cases. Inputs unchanged. Product repair now maps fresh OtherPartItem to
Source within the existing private source operation; its message has one
shared leaf. Raw wrappers keep their domain. Native GREEN remains in progress.

## Implementation review checkpoint

The shared message leaf and fresh OtherPartItem mapping have no confirmed
must-fix in independent review. It requested stronger actual handwritten/
generated service assertions so another Source error cannot masquerade as
part admission. Both native producer and session tests now assert the exact
part message and Helper.pw/Main.gen.pw line2. Location-strengthened source/session reruns pass; source matrix/Raw direct/
foreign and session GREEN also passed.
[Checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-item-refusals/native.json).
