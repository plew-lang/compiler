---
id: met-z0ro
status: closed
deps: []
links: []
created: 2026-10-21T11:01:35Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Inventory specification and design conformance at the current implementation

## Scope and Method

Inventory adopted specification/design contracts against compiler
`ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, and pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Implementation is read-only;
no compiler/test/performance execution or feature repair is part of this task.
The existing dirty binary is not an audit carrier.

Inspect each reference chapter's responsibilities and evidence limits, compare
representative producer-to-consumer paths with source and tests, and reconcile
existing issues before creating follow-ups. Classify observed semantic/design
mismatches separately from absent implementations, partially implemented contracts,
unverified coverage, and intentionally deferred features. Absence of one name or
one passing test is not proof of absence/completeness.

Completion: every reference domain has a bounded source-inspection record; major
evidenced gaps have owning issues and completion boundaries; uncertain cases stay
explicit; the resulting dependency/order recommendation does not start repairs or
expand the type-checking parent's scope automatically. This is a finite audit,
not a second hand-maintained issue/status index.

## Classification and Limits

- **Mismatch:** the inspected route implements a different adopted rule. This can
  be established in source without claiming a fresh user-program reproduction.
- **Absent:** a required mechanism is missing across the inspected input,
  representation and consumer route, not merely absent under one spelling.
- **Partial:** relevant implementation exists, but the required boundary is not
  closed through final use/publication/destruction.
- **Unverified:** a concrete question remains; no failing behavior is established.
- **Deferred:** deliberately outside the adopted initial scope or explicitly
  future work; absence is not counted as a defect.

The inventory covers all 18 reference domains and the related standard-library
and storage supplements by representative source paths. It is not an exhaustive
review of every rule, syntax combination, target or failure path, and it does not
estimate completion from chapter/file counts. No build, check, run, sanitizer,
bootstrap or performance command was executed. Tests were read as evidence of
intended current behavior, not rerun or treated as specification authority.

This is an audit snapshot, not a second live task/status index. Owning issue files
below hold subsequent implementation status and completion evidence.

## Major Findings and Owning Work

| Adopted boundary | Observed implementation at the audit revision | Class and owner |
|---|---|---|
| One immutable source result per owner | Frontend::preparedSemanticFacts qualifies the owner but copies views of all-owner expression/aggregate/try/match/binding/completion arrays. Private write guards exist; the adopted owner-local payload is not implemented. | Partial: [met-acfl](met-acfl.md), [storage design](../design/checked-body-storage.md) |
| One source-selection authority | Resolve/Preparation::prepareLexicalBodyUncached runs record(false), generic check, declaration verify, record(true); global preparation similarly repeats recording/checking. Existing saved facts do not prove selection has one owner. | Partial: [met-ucze](met-ucze.md), [met-si6j](met-si6j.md) |
| Explicit declaration/body provenance | Resolve/Module::moduleOf falls back to entry module for unknown offsets; methodInEntryModule derives ownership from a first statement and rejects an empty body as non-entry. This cannot supply the general synthetic/empty-body ownership contract. No fresh visibility miscompile is claimed. | Partial: [met-acfl](met-acfl.md), [met-ucze](met-ucze.md) |
| Saved calls/proofs/conversions through final use | Ir/FinalResolutions and saved body signatures exist, and Mono consumes many saved facts. Registration/setters and remaining independent interpretations still require producer-to-final-consumer closure. The prior cumulative reconciliation remains applicable to unchanged source. | Partial: [met-ia09](met-ia09.md), [met-6e6k](met-6e6k.md) |
| unique / allowunique / autounique capabilities | Syntax binders and Lower retain names/sendability only; Check/Unique still globally rejects most unique generic arguments. Lang's Optional/Result/Promise do not carry the adopted capability model. | Absent as an end-to-end family: [met-b2la](met-b2la.md) |
| Impl-only deinit | Pinned Syntax and Lower accept struct-body deinit; CompilerExecution::SessionRegistration and Std/Ffi::CString still use it. Spec03 requires inherent impl placement. | Mismatch: [met-2t3l](met-2t3l.md) |
| New standard references and `.*` | Core has Ref/MutableRef plus the old WeakRef[T]/WeakMutableRef[T] split; Lower handles Arrow/ArrowMethod. FrozenRef/MutexRef/Guard/Weakable and exact WeakRef[R] restoration are not present in this path. | Absent/old API: [met-op15](met-op15.md) |
| Ref and its weak handle are nonsendable | Infer/Sendability::typeRefIsSendableDepth instead inherits pointee sendability for Ref[T]/WeakRef[T]. MutableRef already rejects. No cross-thread execution bug is reproduced because spawn is rejected. | Mismatch: [com-qzpm](com-qzpm.md) |
| Worker/channel execution and sendability effects | Current Syntax/semantic forms and reject fixtures exclude spawn; no Sync transport/endpoints accompany this route. Type-level sendable flags are only a subset. | Absent: [com-qzpm](com-qzpm.md) |
| Fixed atomic/non-atomic allocation plan | Backend::emitLlvmRuntime emits ordinary rawbuf/weak increments and decrements. No AOT may-share plan/physical RC specializations or conservative atomic JIT baseline is present in the inspected allocation route. | Absent/design mismatch: [com-qzpm](com-qzpm.md) |
| Application-wide managed JIT pause | CompilerCallbacks synchronously lowers a body through MutableRef on the requesting thread. Single-execution lifetime ownership exists; an independent compiler owner and multi-worker quiescence/native gate protocol do not. | Absent multi-worker extension: [met-b04w](met-b04w.md) |
| Typed Promise outcomes and unique receipt | Verify/Func explicitly limits async payloads to integer/Bool; runtime and MidAsync use an i64 slot. General composite/unique results and their destruction/receipt protocol are missing. | Partial: [com-tn1m](com-tn1m.md), [met-b2la](met-b2la.md) |
| Closed global initialization plan | Resolve/Global::collectGlobalDeps visits direct operands/arguments, not called-body effects, and leaves block-bearing forms to its default case. DFS over this restricted graph is not the adopted transitive effect/readiness plan. | Partial: [met-c58b](met-c58b.md) |
| Library-owned derive input and host units | Gen::synthGenMain directly synthesizes parseItem/derive and branches on args.count()==0. A per-source harness exists; isolated compatible host units and the exact source-to-provider boundary are not closed. | Partial: [com-vy62](com-vy62.md) |
| Missing/stale generated-input rejection | Frontend admits a generated sibling only if it exists; no missing-output branch or recorded-input receipt validation occurs there. Tool stages stdout atomically but publishes no matching portable receipt. | Absent admission mechanism: [com-vy62](com-vy62.md) |
| Native package execution admission | Manifest carries package name and Plew dependencies; Resolver handles git/path. Tool's own LLVM/harness linking is not package-native plan/trust/sandbox/artifact-provenance support. | Absent in inspected routes: [met-nm1w](met-nm1w.md) |
| ORC DataLayout agreement | native consumeModule replaces a nonempty layout with the engine layout without comparing it; object emission has an agreement check. | Source-confirmed mismatch: [com-6ygf](com-6ygf.md) |
| Diagnostic cause and provenance | Owned diagnostics/warnings/failure queues exist. The record is severity/location/message with line-only locations and synthetic offset fallbacks; some terminal/direct-stderr paths remain. | Partial: [met-k7ks](met-k7ks.md), [com-lndr](com-lndr.md) |
| Language-level test discovery/runner | Syntax top-item variants and CLI modes do not collect spec15 test declarations. External fixture suites are a different, existing mechanism. | Absent: [com-8ec0](com-8ec0.md) |
| Equivalent CLI input admission | Distribution routes check directly; native Tool resolves for build/run, while gen has its own path. Source inspection establishes an asymmetry, not a wrong check result. | Unverified consequence: [met-0139](met-0139.md) |
| Full C aggregate/anonymous-callback boundary | CAbi has scalar/pointer/narrow-number handling and expose exists. repr(c) aggregate classification is not represented end to end; public callback typing/context/thread facilities also retain explicit design-open scope. | Partial/unverified/deferred, kept separate: [com-042v](com-042v.md), [com-0oxy](com-0oxy.md), [com-qnyl](com-qnyl.md) |
| Return-copy optimization preserves invalid-input rejection | returnTransferOperand lacks the explicit unique check present in scopeTransferOperand. Earlier admission/final verification may still reject the malformed case. | Unverified safety question, not a reproduced bypass: [com-wqd7](com-wqd7.md) |

## Reference-Domain Coverage

Each row records what was actually read and what remains unknown. General design
alignment of a selected route is not whole-domain implementation certification.

| Domain | Source path inspected | Bounded result / remaining work |
|---|---|---|
| 1. Architecture | CheckedProgram, PreparedProgram, CompilerExecution and pipeline entries below | Common pipeline exists; semantic authority/storage and new runtime contracts remain partial. |
| 2. State/identity | Frontend semantic facts, CompilerSessions, Ir/BodyInstances | Private source guards and session registry exist; owner-local sealing and complete readiness/publication keys remain met-si6j work. |
| 3. Sources/modules | SourceAccess, Loader, Frontend discovery, Manifest, Resolver | Shared parse-driven discovery and impl-only parts exist. Generated receipts/native plans and cross-mode admission are missing or unverified. Snapshot race/cycle combinations are not exhaustively audited. |
| 4. Syntax | Pinned Syntax type/binder/struct/top-item nodes and parsing/materialization; Lower/Decl/Expr/Types | Existing shared syntax and divergence flags exist. New capabilities, `.*`, impl-only rejection and test input need migration. Full grammar equivalence remains com-2p9p. |
| 5. Lookup | Resolve/Module, Resolve/Preparation and saved call construction | Candidate infrastructure exists; provenance fallbacks and single selection authority remain partial. No new overload-resolution runtime failure was reproduced. |
| 6. Types/evidence | Ir TypeRef/TypeTerm, FinalResolutions and binder lowering | Saved terms/proofs exist; capability data and closure through every concrete consumer are incomplete. |
| 7. Body checking | SourceCompletion, Frontend, Resolve/Preparation/Global, Verify/Func | Central source/execution completion is already implemented; repeated selection and saved storage closure remain. Do not revive old give semantics. |
| 8. Generics | Lower/Decl, Check/Unique, Ir/BodyInstances, Codegen/Existentials | Ordinary generics/instance/existential infrastructure exists; new capability model and complete runtime-opened bridge coverage are not established. |
| 9. Metaprogramming | Gen, Frontend generated admission, native Tool gen | Harness/output staging exists; provider boundary, compatible host units and receipts are not complete. |
| 10. Mid | Mid/Prepare, Mid/Verify, Mid/Types and MidAsync preparation | Typed instantiate/access/drop/executable stages and verifier exist. All opcodes/synthetic/malformed paths are not certified. |
| 11. Ownership/access | Check/Unique, Core reference code, Mid access/drop contracts and preparation | Current borrow/access/drop mechanisms exist; new standard projections/Guard/capabilities must be integrated. Full alias/destruction-path coverage remains unaudited. |
| 12. Passes/optimization | Mid/Optimize return/scope transfer, Mid/Prepare | Optional copy pass exists. Return unique eligibility is retained as an investigation; general copy propagation is not an adopted missing correctness feature. |
| 13. Representation/ABI | CAbi, ValueAbi, Core weak wrappers and Ffi | Shared scalar C boundary exists. New weak/Guard representation and C aggregate/public callback coverage are incomplete or explicitly open. |
| 14. LLVM backend | native consumeModule/object/ORC publication, MidAsync | Common module ownership/verification exists; layout disagreement is confirmed. No target-wide ABI/resource-failure audit was run. |
| 15. Runtime | Backend emitted allocation/weak/Promise/queue/timer C, CompilerExecution | Current event loop is timer-only with virtual time. General OS/pending-worker services, typed outcomes and atomic modes are incomplete; no timing-performance claim is made. |
| 16. Driver | CompilerExecution/Callbacks/Sessions, distribution, native Tool, build scripts | One-shot ORC and static-distribution recipes exist; worker coordination, effect-closed startup, native packages and parity are outstanding. Release admission remains com-ao7z. |
| 17. Diagnostics | Diag, Emit source anchors, callback adapters | Owned diagnostics and warnings exist; original provenance/context/returning boundaries are partial. |
| 18. Verification | Mid/Prepare/Verify/Types, tests README and rejection fixtures | Stage gates/fixtures exist. New adopted surface is not covered merely by old rejection tests or earlier green suites. No new tests executed. |

Standard Library was additionally compared with Core/Lang/Async/Ffi declarations:
module/visibility infrastructure exists, but the adopted shared-reference/Sync and
unique-result API family is not implemented. Buffer backend typed-element support
exists; collection place/reentrancy and all typed copy/drop cases remain the
separate [collection audit](com-zgk9.md), not newly established defects.

## Counterchecks and Intentionally Excluded Scope

- MidAsync::midAsyncSuspend already branches directly to completion for a done
  Promise. The registration helper's enqueue branch does not prove all awaits
  yield; the generated code bypasses it when already complete.
- DeclarationProgram and CheckedProgram already request declaration-level global
  access analysis. The earlier claim that this graph is entirely unconnected is
  obsolete. That access analysis is not the new initializer-readiness DAG.
- SourceCompletion already distinguishes source and execution exits and consumes
  give at the block boundary; divergence function-type metadata is present.
- expose, scalar C calls, the Dictionary/session-ID registry, one-shot ORC, embedded
  standard resources and static build recipes already exist. They are not counted
  as wholly absent because release/host/general callback coverage remains open.
- Shared-reference cycle collection is explicitly future additive work
  ([com-2z5l](com-2z5l.md)); reusable execution/Hot Restart, general closure move
  capture, public lifetimes, arbitrary projections, conformance splitting and a
  general specialization solver remain outside the current initial scope. Do not
  convert these into defects or type-checking-remediation prerequisites.
- Rich error codes/automated fixes, every target and every optional optimization
  are not made mandatory by this audit.

## Suggested Repair Boundaries

Do not turn this inventory into one all-features implementation goal. The current
recommended foundation remains [met-si6j](met-si6j.md)'s source-to-consumer closure,
with its selected candidate and retained performance/gate conditions. The bounded
ORC layout bug can be handled separately as a correctness fix. Capability/deinit
and reference API work can then use that foundation; worker/channel/atomic/JIT
coordination must be planned together before enabling spawn. Global startup and
generation/native admission have their own effect/input/publication boundaries and
can be selected independently when their prerequisites are met. These are work
ordering recommendations, not newly asserted hard tk dependencies or authorization
to start repairs now.

## Administrative Differences

Some design/issue status text still says restart reconciliation/physical choice is
pending although met-j9mv records the adopted storage choice, current reconciliation
and fresh baseline. This is documentation lag, not proof of an implementation
regression or that the new storage exists. Current candidate/restart state remains
in worklog/met-j9mv; normalize stale chapter/parent status with the next affected
update rather than rerunning an unchanged baseline solely because of old prose.

## Outcome

The bounded inventory is complete: all reference domains have an inspected path,
major evidenced gaps have owners, and uncertain/deferred cases are explicit. Eight
new owning tasks were created; nine existing issues received current source
rechecks. No implementation task was closed and no repair, specification change,
compiler execution or performance measurement was performed. The untouched dirty
binary and caches remain unrelated; compiler/main/seed/carrier are not promoted.
