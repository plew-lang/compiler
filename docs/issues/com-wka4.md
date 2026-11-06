---
id: com-wka4
status: open
deps: []
links: [com-z4ns, com-0w38, com-amjl]
created: 2026-11-06T17:52:13Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Validate declaration ownership before admitting bare impls

## Contract and Evidence

Spec07's opening rule, spec09's orphan rule and spec15's impl placement require
bare impls to belong to the declared subject's defining module, regardless of
trait ownership. Follow design name-lookup, types-and-evidence and frontend
handoffs. [Executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json) records a record bare conformance and bound use accepted by
--check at compiler95332efd. Missing/incorrect ownership admission is a confirmed
acceptance problem; the exact bypass cause is still to be traced. Do not assume
all foreign nominal impls are currently accepted.

## Actions and Guarantees

- Trace impl header -> resolved subject declaration -> registration -> source
  success, including empty and associated-type-only impls. Establish canonical
  declared subject identity and owner once at the proper declaration admission
  boundary. A member/body scan alone cannot certify the impl header.
- Require a real eligible declaration, not just a same-spelled name, source span
  or synthetic record layout. A structural type occurrence does not establish
  declaration ownership. Missing identity fails closed with a Source diagnostic.
- Preserve owner-module bare impls, same-module part placement, trait-provided
  bodies and trait-subject owner rules. Imported/re-exported aliases retain the
  actual declaration owner. Named extensions use their separate placement rule.
- Inspect API inputs for unrelated cursor/layout/declaration mutation authority;
  preserve the canonical owner receipt through consumers rather than resolving
  spelling again. Do not merely add a record-specific branch.

## TDD and Completion

Cover owned nominal success; foreign nominal bare impl rejection even with a
locally owned trait; import/re-export identity; missing or nondeclaration subject;
record bare subject; empty/associated-type-only/method-bearing impls and valid
extension controls. Start with actual fixed-carrier RED/GREEN contrasts. Inspect
existing test intent before changing invalid setups (com-z4ns is related).
Complete real producer-to-registration/source-success closure, remove competing
ownership decisions, run affected gates and obtain independent neutral review.

## Boundaries and Intake

com-0w38 owns record prohibition even inside extensions. com-amjl owns trait-view
proof, not impl ownership. These are related, not automatic implementation
prerequisites. No new ownership language, blanket nominal impl prohibition,
solver redesign or main/seed promotion. Required phase-three acceptance is
connected to met-si6j and met-ia09. Product implementation remains open.
