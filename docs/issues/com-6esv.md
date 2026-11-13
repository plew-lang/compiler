---
id: com-6esv
status: open
deps: []
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

