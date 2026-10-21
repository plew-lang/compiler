---
id: met-31n6
status: closed
deps: []
links: []
created: 2026-10-21T10:42:55Z
type: chore
priority: 2
assignee: Koji Murata
tags: [documentation, design]
---
# Audit decision retention and remove superseded discussion documents

## Scope and Completion

Audit the adopted outcomes, rationale, rejected alternatives/reconsideration
conditions and outstanding work before removing superseded discussion documents.
Source input: meta `9979e825` and pre-consolidation versions in its Git ancestry;
reference input: compiler `c71cc68d` and spec `3b73ea3`. Three independent reviewers
cover sharing/runtime, unique generics, and the remaining discussion families.
Implementation correctness and compiler/performance execution are outside this audit. A source comment that links a removed document is redirected; executable source is unchanged.

- Map retained decisions to specification, design/decision notes and local issues.
- Repair evidenced omissions without reviving superseded proposals or adding policy.
- Remove redundant discussions and redirect live navigation to the canonical homes.
- Preserve historical evidence and its revision/scope rather than presenting it as
  current implementation certification.
- Check links, anchors, issue metadata and diffs; preserve candidate/carrier and
  unrelated binary/cache changes. Keep this issue after scoped completion.

## Source-to-Authority Review

Three independent reviewers compared the retained decisions, not just the
current short redirects. Sharing used meta `24d691f1` (also `8bbb5446^`), including
the 1,028-line final proposal; unique generics used `8bbb5446^`, including its
994-line final proposal. The third reviewer compared the other current discussion
entries with their pre-consolidation Git versions and the original review task.
Early alternatives do not override later approved decisions.

| Decision family | Retained authority and audit result |
|---|---|
| Sendability, CoW transfer and RC | spec03/14; [Runtime](../design/runtime.md#storage-arc-and-cow). One sendability axis, Ref restrictions, atomic joins and no runtime promotion preserved. |
| FrozenRef, MutexRef, Guard, projections and weak references | spec03; [Ownership](../design/ownership-and-access.md#standard-reference-projection-handoff), [ABI](../design/representation-and-abi.md#typed-operations-and-weak-restoration). Shared cell lifetime, lock ownership and exact weak restoration remain distinct. |
| Spawn, globals, worker results and channels | spec14; [Runtime](../design/runtime.md), [Standard Library](../design/standard-library.md). Immutable capture, explicit unique input, destination-affine completion, close, cancellation and capacity retained. |
| Unique generic capabilities, conditions and deinit | spec03/05/06/08/11/14; [Types](../design/types-and-evidence.md#capability-and-conditional-selection-contracts), [Generics](../design/generics.md). Mode adaptation, bounded candidate families, existential identity/opening and final destruction retained. |
| Ordinary closure move capture | [com-b1ro](com-b1ro.md). Capture-time transfer, environment copy capability and call-time consumption remain separate future decisions, not a newly adopted feature. |
| Defaults, trait requirements and via | spec04/08; [Name Lookup](../design/name-lookup.md#shared-callable-applicability), [Body Checking](../design/body-checking.md#5-selected-operations-and-evaluation). Shared applicability, explicit-before-default evaluation and call-end temporary lifetime retained. |
| Blocks and explicit divergence | spec04/11; [Divergence decision](../design/decisions/divergence.md), [Body Checking](../design/body-checking.md#4-blocks-branches-patterns-and-completion), [com-gyup](com-gyup.md). Current rules supersede old acceptance expectations; historical probes stay historical. |
| C entry points and callbacks | spec15; [ABI](../design/representation-and-abi.md#native-external-boundaries), [Driver registry](../design/driver-and-execution.md#registry-and-lifetime), [com-qnyl](com-qnyl.md). Expose, labels and ordinary lazy materialization retained; general callback/context/thread facilities remain scoped unresolved work. |
| Lazy execution, pause and startup | spec07/14/15; [Driver](../design/driver-and-execution.md), [Runtime](../design/runtime.md). One runtime, independent compiler owner, managed/native gates, static initialization plan and conservative cycle rejection retained. |
| Generated code and native build | spec16/17; [Metaprogramming](../design/metaprogramming.md), [Sources](../design/sources-and-modules.md), [R4/R6/R7](com-7knz.md). Explicit generation, recorded-input freshness scope, author-managed external observations, combined publication and admitted native execution retained. |
| Hot Restart and distribution | [Hot Restart](../design/decisions/hot-restart.md), [Distribution](../design/driver-and-execution.md#distribution-boundary), [com-ao7z](com-ao7z.md). Future restart/500ms scope and release-validation limits are not certified by historical probes. |
| Reference maintenance and storage restart | [Maintenance](../design/maintenance.md), [Storage](../design/checked-body-storage.md), [met-si6j](met-si6j.md), [met-j9mv](met-j9mv.md). Purpose, rejected alternatives, tk, source-to-consumer obligations and scoped restart evidence retained. |

Other deleted technical entries contained only redirects and qualifications.
Their Syntax, frontend, Mid, collection, access and optimization destinations were
checked directly; current work, validation baselines and historical evidence
remain in their existing operational/evidence homes. This is not a second
maintained decision index: the table records the bounded migration audit.

## Corrections Before Removal

No reversal or missing major adopted semantic rule was found in the reviewed
families. The following information would otherwise have lost its useful home:

- Ownership now retains MutexRef's per-cell ownership cost and why a Guard need
  not itself be heap allocated; cell lifetime does not alone prevent early unlock.
- Runtime now retains on-demand RC combinations and the accepted analysis/code
  growth cost, including argument/result alias relationships.
- com-b1ro retains the independent future move-capture questions.
- Generics now retains explicit capability/range rationale, rejection of inherited
  associated-type redeclaration, deferred conformance splitting/reconsideration
  conditions, and representative capability/destruction verification controls.
- Body Checking no longer describes completed restart reconciliation and the
  fresh baseline as still pending. New storage implementation remains pending.
- Active navigation goes directly to specification/design/issues. Removed entries
  are not retained as empty forwarding files. Spec16 and a Frontend source comment no longer depend on removed meta
  discussion paths. Historical evidence keeps its results/revision limits and
  distinguishes present navigation from historical acceptance rules.

The [blind channel-review input](../../../evidence/channel-policy-blind-review/input.md)
remains historical evidence. Its original results and subsequent decisions remain
in [the immutable pre-consolidation record](https://github.com/plew-lang/meta/blob/24d691f1/agents/thread-sharing-spec-draft.md#採用理由を伏せた通信規則の独立レビュー2026-10-20);
current contracts are spec14, Runtime and Standard Library, not the old proposal.

## Result and Verification Scope

Resolved within the documentation-retention scope. Twenty-seven superseded
proposal/comparison/redirect files were removed after the three independent
reviews and the corrections above. The general reviewer rechecked the final
retention/navigation diff and found no remaining blocking omission or new semantic
decision. Closed issue files, immutable history and historical evidence remain.

Verification: scanned 266 remaining tracked Markdown files across meta, compiler
and spec against the pre-edit link/anchor inventory; no new missing local link or
anchor was introduced. Existing unrelated historical reference failures are not
certified as repaired. All three repository diffs pass whitespace checks. Confirmed
that compiler implementation/test/seed/dependency tracked trees remain unchanged
except for the single Frontend comment redirect; the existing dirty binary hash
is unchanged. This source-comment edit is not a new self-host measurement.

No compiler, runtime, sanitizer or performance tests were run for this prose/link
change. Implementation completeness, performance and first-edition acceptance
remain separate; main, seed and selected carrier were not promoted. Keep this
issue as the completed audit record, not a new mutable discussion authority.
