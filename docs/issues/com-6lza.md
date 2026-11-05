---
id: com-6lza
status: closed
deps: []
links: []
created: 2026-11-02T10:59:44Z
type: task
priority: 1
assignee: Koji Murata
tags: [diagnostics, verification, driver]
---

# Audit compiler-wide failure classification and panic boundaries

## Purpose and Authority

Audit the compiler as a whole before changing its error handling to repair
[com-fsuq](com-fsuq.md). This is a separate cross-compiler investigation, not an
expansion of that runner repair or a claim that every current Failure is wrong.
Contracts: [diagnostics](../design/diagnostics.md),
[driver/service boundaries](../design/driver-and-execution.md#failure-and-os-integration),
[verification](../design/verification.md), and the spec's
[panic contract](../../../spec/spec/03-expressions/11-control-flow.md#panic-と発散).

Distinguish expected source rejection, input/environment/tool failure,
implementation limitation, malformed-artifact rejection by a validator, and a
broken invariant of the compiler's own already-admitted state. Severity, prose,
module/variant names and exit1 do not establish that distinction. Determine
whether an error is a normal result of the API's input contract or an impossible
state under its admitted preconditions. In particular, a validator returning an
error for intentionally malformed input is not itself a compiler bug.

The adopted policy permits panic for genuine admitted-state invariant
violations and keeps typed returned failures for expected failure paths. It is not
permission to mechanically replace messages containing internal with panic.
Identify conflicts with current returning-service/design contracts and obtain
any required decision before adopting changes. Panic aborts without unwind or
user cleanup; do not promise surviving-host recovery or change that language rule.

## Scope and Execution

1. Pin the compiler/source/dependency revisions and define the full in-scope file
   universe before the audit. Cover lexer/parser and Syntax adapters, loading and
   dependencies, declarations/name lookup/type checking, retained sessions and
   request caches, instantiation, Mid construction/passes/verifiers, LLVM/native
   emission, generator/derive execution adapters, compiler drivers/CLI and
   JIT/FFI callbacks. Include compiler-invoked runtime support, build/package
   adapters and supervisors where they transform compiler outcomes. Distinguish
   dependency implementations from compiler-owned adapters and inspect the actual
   dependency failure contract where relied upon.
2. Inventory failure producers and shared constructors, Result/custom result
   variants, conversions, failure caches/queues and final consumers. Cover panic,
   assertions/unwrap/preconditions, terminal exit/abort/native fatal paths,
   ignored or overwritten failures, fallbacks/defaults and unsupported paths.
   Trace actual success/publication after failure, not just error messages.
   Distinguish a generator/user callback panic from a compiler invariant failure;
   both can terminate an invocation without proving intended source rejection.
3. Partition the inventory into finite reviewable batches with exact membership
   before executing them. For each entry/family record API preconditions, owner,
   input trust/stage, originating cause, returned/terminal behavior, propagation
   and retained identity/state/cleanup obligations. Attribute each site to a
   semantically inspected family; search hits and family counts are not evidence
   that the branches are correct. Split oversized batches rather than an open-ended
   all-compiler review. Reuse source-matching API/test audits without assuming
   they answered this different failure-policy question.
4. Evaluate source rejection, IO/tool failure and implementation limits versus
   true invariant violations; examine validators with deliberate invalid input
   separately from consumers of supposedly validated artifacts. Check that
   ordinary failures do not become panic, bugs do not become expected rejection,
   and no cause is lost through diagnostic construction or retained services.
5. Design the lowest suitable API-level assertions for semantic rejection and
   typed failures, with process isolation for abort/crash/timeout. Retain CLI,
   supervisor and sanitizer integration checks for their actual responsibilities.
   Compare API testing, result propagation and any process-observable transport
   needed by remaining black-box consumers. Do not preselect changed CLI codes,
   a JSON protocol or conversion of the entire rejection corpus.

Generated user-program panic behavior, a complete std/runtime safety audit,
new catch/unwind/lifetime mechanisms, host-recovery support and implementation
of unrelated language features are outside scope. Their compiler-side boundaries
and failure propagation are included. This task performs investigation and
planning only, not product changes or mass test/expectation migration.

## Deliverables and Completion

- A revision-pinned coverage map reconciles every in-scope producer/transport/
  termination path to inspected finite batches, with justified exclusions and
  explicit unverified entries. No mandatory entry remains silently unclassified;
  unresolved policy questions are brought to the user before closure.
- Every confirmed discrepancy has source or discriminating controlled evidence,
  valid controls and a proposed owning correction. Distinguish static findings
  from executed reproductions and limitations. Define prospective RED/GREEN and
  structural checks; investigation itself does not require fictional RED tests.
- Record the recommended policy and reasons in its proper design owner only
  after required decisions; otherwise retain explicit decision questions here.
  Assign all mandatory repairs to finite existing or new implementation tasks,
  with actual dependencies at affected admissions. Findings outside fsuq's named
  lanes must not be forced into fsuq or made its prerequisites without cause.
- A fresh independent review checks actual coverage, classifications, stage/input
  distinctions, evidence and follow-up ownership. Close only as investigated,
  never as repaired, compiler-wide conformance or GREEN. Audit closure alone
  does not satisfy com-fsuq: its relevant product repairs and consumer tests must
  also be installed as real prerequisites before resuming it.

## Existing Evidence and Related Owners

Start from com-fsuq's [RED and independent channel review](../../../evidence/rejection-domains/README.md)
and [preparatory boundary map](../../../evidence/rejection-domains/producer-boundaries.json).
The latter's18 literal constructors and986 helper occurrences are a partial
syntactic inventory, not full compiler coverage or semantic classification.

[met-k7ks](met-k7ks.md) owns diagnostic provenance/transport repairs;
[com-lndr](com-lndr.md) owns call-specific diagnostic distinctions;
[com-k4c9](com-k4c9.md) owns generation rejection consumers. Coordinate exact
findings with these owners; do not duplicate their existing product tasks or
require their completion merely to perform this audit. com-fsuq keeps its finite
normal/expose/ASan B repair contract and remains open after this audit is assigned.


## Task-Scope Review

The [independent document review](../../../evidence/rejection-domains/audit-task-review.json)
accepted this audit contract and dependency arrangement. An old com-fsuq sentence
about independence from com-jno0 audit closure was clarified to distinguish this
new prerequisite. No mandatory scope defect or unconfirmed concern remains.
This reviews the task definition only, not the subsequent semantic audit.

## Audit Evidence and Follow-up

[Whole reconciliation](../../../evidence/compiler-failure-audit/whole-reconciliation.json)
connects every requirement to the fixed source audit, classifications, API/process
assertion proposal, finite correction owners and actual admission dependencies.
The original inventory covers313 files/104 batches; fresh whole review found the
omitted distribution entry and the [fixed supplement](../../../evidence/compiler-failure-audit/supplemental-inventory.json)
adds its complete79 lines. Combined scope is314 files/105 batches. The original
inventory is preserved as actually incomplete, not retroactively rewritten.

Seven domain records answer395 original cross-batch questions. The
[original finding intake](../../../evidence/compiler-failure-audit/finding-intake.json)
accounts for49 entries/48 IDs and separately identifies additional conditional
findings. Finite implementation owners and actual affected-admission paths are
recorded in service/Mid, tooling and frontend/Syntax adoption evidence. The
supplemental resolver-output publication failure is assigned to
[com-sh7q](com-sh7q.md), with actual met-0139/com-604k prerequisites. Static
conditional paths are not newly executed source crash/miscompile reproductions.

[Fresh whole completion review](../../../evidence/compiler-failure-audit/whole-completion-review.json)
accepted coverage corrections WC1/WC1a/WC1b; the
[whole assignment review](../../../evidence/compiler-failure-audit/whole-assignment-review.json)
accepted W1/W2/W3 after record/source/dependency rechecks. Independent input
boundary clarification is in the
[finite review](../../../evidence/compiler-failure-audit/source-input-boundary-review.json).
Product repairs remain open; this does not certify compiler conformance or GREEN.

## Adopted Failure and Escape Policy

On2026-11-05 the user explicitly approved the Rust/Swift-based recommendation,
including specification changes. The [policy adoption delta](../../../evidence/compiler-failure-audit/policy-adoption.json)
links that decision to the current normative owners and finite implementation
scope. This resolves the two previous WC2 choices. The [independent policy review](../../../evidence/compiler-failure-audit/policy-adoption-review.json)
accepted the delta after correcting the literal spellings; the whole reviewer
independently confirmed WC2 resolved.

- [Diagnostics](../design/diagnostics.md#input-failures-and-internal-invariants)
  permits panic only for genuine contradictions of established internal
  invariants. Ordinary invalid source/input/tool/limit and validator refusal
  remain distinguishable returned failures. Recovery/failed-owner state is not
  admission; existing errors are not mechanically converted to panic. No unwind,
  deinit/host recovery, public exit-code catalog or serialization is adopted.
- The [shared escape grammar](../../../spec/spec/01-basics/02-basic-types.md#文字文字列リテラル共通のエスケープ)
  defines the closed common simple escapes and braced nonempty hexadecimal
  Unicode scalars. Unknown/nonhex/unbraced/empty/invalid forms are compile errors,
  not implicit byte conversion or panic. No new digit-count restriction; checked
  accumulation prevents machine overflow. Existing brace/line-fold rules remain.
  [Syntax design](../design/syntax.md#literal-escape-admission) records the rationale.

[com-9d4c](com-9d4c.md) owns source escape validation and successful-cache refusal;
[com-a0fc](com-a0fc.md) owns matching character scalar-value decoding. Their real
admission dependencies remain installed. [com-yeua](com-yeua.md) carries the
failure-domain policy to the named returning/process consumers before fsuq/gen
consumer repair. No product implementation, test, seed or CLI behavior changed
while adopting these contracts. Other unresolved interfaces remain their finite
implementation tasks' explicit decision boundaries, not silently chosen here.

## Completion State

The [whole requirement reconciliation](../../../evidence/compiler-failure-audit/whole-reconciliation.json)
accepts all investigation deliverables. The [final verification](../../../evidence/compiler-failure-audit/final-verification.json)
confirms314 source identities,105 exact batches,395 questions each once, and156
actual dependency steps without a reachable cycle. These structural checks
supplement, rather than replace, semantic finite/whole reviews. The adopted
specification is revision e705561. Product follow-ups stay open, including
com-fsuq, com-yeua, com-9d4c, com-a0fc and com-sh7q.

Close as **investigated**. No product repair, compiler-wide conformance, suite
GREEN, performance, main integration, carrier or seed promotion is certified.
