---
id: met-gjxo
status: in_progress
deps: []
links: [com-9sa5]
created: 2026-11-27T04:45:28Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, diagnostics, verification]
---
# Admit nominal field and variant uniqueness across every module


## Contract and confirmed failure

Nominal declaration admission must validate each struct's field names, each
enum's variant names and each variant's payload labels independently of module
number or body demand. Source field unification is specified in spec05;
frontend/declaration handoffs require valid source declarations before successful
publication. Unused imported declarations are not an exception.

Fixed productc6720051/594990c485aa has18 executed controls: all9 local
invalid shapes reject Unclassified, while identical9 imported shapes succeed
in check/AOT/ORC.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-labels/README.md).
Actual checkDeclShapes filters struct/enum loops to module0.

## Required investigation before implementation

- Trace actual Syntax/legacy Lower and registerStruct/registerEnum inputs,
  declared and generic nominal identities, synthesized rows and gen harness
  duplicates. Identify reservation versus successful declaration publication
  and actual source-owner boundaries. Do not assume an Arena row/span or
  private Source-mode enum alone proves source ownership.
- One label equality/conflict authority must be shared by source admission and
  Raw validation. The core reads bytes/label spans and returns a typed conflict
  or malformed-input distinction, not a Source report. Actual source decl
  owner binds its complete labels and original/duplicate slots/locations.
  Source errors cannot be reported from an unrelated Raw/synthetic/foreign row.
- Preserve the existing gen shape-check suppression needed by its trusted
  macro harness; ordinary compiled generated source follows normal rules.
- Study actual data/reader needs and avoid another parallel declaration checker,
  public source flag, whole mutable Comp facade or per-request AST reconstruction.
  Remove the unused checkDupFields ctx and narrow its genuine byte/name inputs
  as the coordinated com-9sa5 field-leaf migration, without absorbing that task.

## Scenarios and completion

1. Meaningful fixed-candidate RED for all three imported false-success shapes
   and local missing Source origin. Preserve legitimate labels, same payload
   label in different variants, different types/modules, generics and unused
   import modes. Rejection must precede successful declaration publication.
2. Real producer/retained result/session/CLI paths with original/duplicate
   locations and exact intended reason. Raw registerStruct/registerEnum,
   synthetic declarations, foreign/wrong source slots and malformed spans
   never gain Source or turn ordinary invalid input into compiler panic.
3. Remove module-zero acceptance and competing old decisions. Shared core,
   source/Raw adapters and gen boundaries receive structural plus executed
   controls; no whole-verifier rewrite or weakened checking.
4. Fresh applicable regressions, fixed point/formal<=7.5s, independent final
   review, synchronized evidence/tickets/worklog and bounded cleanup.

## Ownership and exclusions

Parent com-604k owns existing-feature conformance. com-yeua depends on this
finite producer repair for its declaration-label refusal channel. com-9sa5
owns the existing broader verifier/input audit; preserve its other functions,
remaining callers and guarantees. No parameter/type-name duplicate overhaul,
extern ABI/layout redesign, all-shape audit, new feature or language decision.
No product fix or GREEN is claimed.

Independent qualified_member_plan accepts this finite scope and its separation
from behavior-preserving API narrowing. It requires actual declaration ownership
and gen/synthetic path study before implementation.
