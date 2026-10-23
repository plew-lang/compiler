---
id: met-ucze
status: in_progress
deps: [com-qehq, com-qb05, com-17yh]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

## Contract

One source construction/selection owner commits the declaration or requirement,
lexical owner, receiver/evaluation inputs, full signature, substitution, result
recipe, conversions and evidence. Candidate probes may refine permitted unknowns;
Generic, Verify, Mono and final readers consume the committed result rather than
selecting another member. Shared lookup called repeatedly is not one authority.
Preserve source order, visibility, labels, ownership, bounds and ambiguity.
First concrete evidence for an already selected abstract requirement is legitimate
instantiation, not permission to choose a different source path.

Design: [Body Checking](../design/body-checking.md),
[Lookup](../design/name-lookup.md), [Frontend Handoffs](../design/frontend-handoffs.md).

## Current Boundary

Owner-local operation/constraint payloads, navigation-only indexes, saved static/
dynamic/operator/protocol templates and recorded-signature readers are implemented
increments. Static protocol operations retain selected requirements; the old
ProtocolSelection.Direct alternative and post-success storage-summary rewrite
were removed. Canonical iteration requirements and lexical provided-body ownership
remain semantic obligations. None of this certifies all remaining paths without
the child closure records below.

Auxiliary storage/access-demand analysis must not mutate a published source
operation. Keep its independent result and eager/demand access-analysis contrasts.
Pending source conversions finish before successful owner publication; final
readers cannot turn missing selection/evidence into presence-only acceptance.
Keep method/operator/protocol result projections and the same source provenance.

## Executable Work

- [B0](com-qehq.md): reconcile the eight actual paths and select residuals.
- [B1](com-qb05.md): ordinary/method/factory saved-selection closure.
- [B2](com-17yh.md): operator/protocol/iteration/try selected requirements.
- [B3](com-v2xk.md) under met-ia09 owns exact callee condition environments;
  [D3](com-wqa0.md) owns the final operation/constraint API write boundary.

Close this area after its required children/repairs and scoped fresh controls,
with producer/final-reader/removal locations per path. Retain matching successful
evidence from the [source-owner index](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/README.md).
The old sequential WIP/next/gate paragraphs are Git history, not current work.
Whole-candidate gates remain required by [G2a](com-p5um.md)/[G2b](com-9l3b.md)
before the parent closes; area closure alone is not release/seed readiness.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), [com-esri](com-esri.md): **Included repair** on existing
written/generic-bound/provided/operator/implicit calls. No new opening, unique
generics or protocol surface is introduced by this work.
