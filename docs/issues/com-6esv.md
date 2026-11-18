---
id: com-6esv
status: closed
deps: [com-atac, com-ceny]
links: [com-3jtd]
created: 2026-11-13T18:41:32Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Use shared callable selection for explicit via delegation

## Guarantee and scope

Use the ordinary callable applicability rules to validate explicit method
delegation and publish the same selected operation to the forwarding body.
Preserve the trait requirement contract across its complete admitted
receiver/binder scope, including visibility, callable kind, labels and
default completion, argument and receiver modes, async/diverge, and the
exact result/failure types. See [spec/08](../../../spec/spec/02-type-system/08-traits.md#トレイト準拠と-via)
and [shared applicability](../design/name-lookup.md#shared-callable-applicability).

The [dependent receiver reproduction](com-ukzt.md#dependent-receiver-counterexample)
compares explicit forwarding with equivalent `via`. The independent
`viaSignatureMatches` gate rejects the latter by comparing raw receiver
and result terms. Trace that precheck and both lowering routes through
source call publication and final body selection. Remove duplicate decisions
and carry the exact selected declaration, substitutions, default environment,
and constraint evidence to the forwarding call. Retain declaration-time
checking even when a witness is unused, and preserve ordinary diagnostics
for missing, incompatible, and ambiguous targets.

This is the behavioral repair. The remaining conformance/helper authority
audit belongs to [com-ukzt](com-ukzt.md); its two affected entry points may
be removed here if the shared path subsumes them. Trait/value view formation
remains with [com-3jtd](com-3jtd.md). Preserve existing field delegation,
generated callable forms, and trait-subject forwarding.

## Completion

- Reproduce the dependent receiver failure with the pinned compiler. Test the
  named delegation against explicit forwarding and the plain-receiver control.
- Exercise source checking without a witness use and actual JIT/native dispatch.
  Include compatible defaults, incompatible receiver/argument/result or mode,
  and invalid target visibility/ambiguity under the existing rules. Reuse nearby
  controls and verify direct/generic consumers where the operation permits both.
- Follow the admitted selection through the final forwarding body. Verify that
  a second raw signature decision or post-publication candidate search is gone,
  then obtain independent completion review and record the evidence.


## Reproduction on the Iteration Fixed Point

The [four-case comparison](../../../evidence/rejection-domains/diagnostic-domain-implementation/via-applicability-red.json)
uses the generation-2 fixed point of compiler `76a15cb2`. The dependent
receiver still fails only through `via` at the raw signature precheck.
The equivalent explicit call and the ordinary and defaulted `via`
controls pass check and return 42 in JIT.

Use the declaration's real delegation occurrence and requirement signature
as the input to shared applicability. Preserve the exact receiver and
parameter modes, result and failure type, and async/diverge contract when
judging candidate applicability. A raw early Boolean cannot authorize a
separate forwarding-body search. Preserve declaration-time invalidity even
when JIT never demands the witness. The fixed-point reproduction is RED
evidence, not an adoption decision or completion result.

The regression fixture is
[`trait_via_projected_receiver`](../../tests/fixtures/run/trait_via_projected_receiver.pw).
With the fixed-point carrier it rejects before ordinary selection. The
[isolated admission experiment](../../../evidence/rejection-domains/diagnostic-domain-implementation/via-applicability-red.json)
shows that requesting the ordinary lexical body at declaration admission
preserves rejection of a missing target and a stronger `where` even in
undemanded JIT. The same experiment incorrectly accepts receiver-mode and
Unit-result mismatches, so lexical admission alone does not satisfy the
delegation contract. Continue with selected-operation verification and
authored provenance before replacing the precheck.

## Forwarding Occurrence Handoff

Both Lower inputs now retain the call expression returned when constructing
the forwarding body, keyed by the declaration ID actually registered. The
generated callable-form adapter takes only the body and does not publish an
authored via witness. The temporary precheck reads the target from this
stored expression. It remains the gate until selected-operation validation
can replace it. The scoped check/JIT comparison preserves all 26 prior
outcomes, including the projected receiver regression's RED.

## Selected Admission Implementation

The ordinary lexical body request now owns declaration-time via validation
in check, AOT, lazy execution and generation. It checks the saved selected
signature and the witness's admitted argument/result types and modes before
publishing owner success. Lower retains the exact call. The first implementation separately retained
the awaited result for async; com-ceny removed that intermediate await. The old raw signature
precheck and candidate search were removed. Via source failures retain the
exact authored occurrence; a generated adapter has no such entry.

Comparison reached 48/48 selected check/JIT/AOT controls, five rejection
inputs carrying Source in all four modes, and three new positive native
goldens plus their gen admission. Independent review exposed lexical Self,
receiver-shaped trait requirements and async result handling; the new
controls cover those boundaries. The demanded async instance method still
fails on the pinned baseline even as an ordinary call, independently of
delegation. [com-atac](com-atac.md) owns its entry ABI repair and blocks
closure of this issue. Explicit trait-view result materialization is
also reproduced on the baseline and tracked under [com-qb05](com-qb05.md).
No full-suite or formal performance result is claimed.

## Independent closure review

Final execution candidate `47085e32` includes both [receiver
entry](com-atac.md) and [single-activation forwarding](com-ceny.md).
The projected receiver, Self result and trait-subject requirement fixtures
passed native AOT, ORC and generation. Five malformed delegation fixtures
rejected as Source in each of check, AOT, undemanded ORC and generation.
Independent supplementary checks confirmed ordinary ambiguity and
cross-module visibility diagnostics, argument/result identity even where
an ordinary conversion exists, and correct diverging-target admission
and rejection. The reviewed final consumer preserves the exact call row,
default plan, instance evidence and witness proof from lexical selection.
The old independent raw signature gate and candidate search are gone.

This closes the supported method delegation contract. Explicit
trait-view projection remains [com-qb05](com-qb05.md), and future
copyability-split families remain [met-b2la](met-b2la.md). Phase-wide
performance and full test gates remain separate.
