---
id: com-3qne
status: in_progress
deps: []
links: []
created: 2026-10-24T20:09:24Z
type: bug
priority: 0
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Repair trait subject default forwarding native crash


## Boundary and Exit

Valid run fixture trait_default_trait_subject generates a native executable that segfaults139 on baseline090240dd and measured6ddf8f75, with byte-identical LLVM and matching runtime. Base as Read provides read(count: I64 = 5); X as Base must support direct and generic calls, both producing5. Diagnose selection, default forwarding, body arguments and emitted call ABI through final execution; repair the producer/consumer contract without masking the crash or changing the user program. Preserve defaults and direct/generic dispatch with a targeted ownership and sanitizer contrast where applicable.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.

## Associated Callable-form Control

Also retain compiler/tmp/phase3f-associated-copies/default-associated-5.pw: Source as Target supplies assoc value(count: I64 = 5), S as Source, direct S.value() and generic T.value(). On fresh52a3ca0d/ab881a99, check succeeds but AOT finalization rejects function662 with body receiver mismatch (Self@1 pattern, S actual and expected, actual-decl172). This is not certified by com-9clj's nondefault associated witness repair. Independent body_receiver_completion_review assigns this generated callable-form/default forwarding route here; diagnose it alongside the original instance crash without assuming identical roots. Preserve associated ABI receiver0 and both direct/generic outputs5. Required before G1 and final gates; no namespace helper expansion or receiver validation weakening. Raw default-5 and default-trace-5 records retain failure and fixed input hashes.

## Reviewed Repair Plan

Atc8761ebf, instance-default-7 again exits139. Its emitted gm577_9_b11 calls itself with no arguments, while the full-argument gm576_9_b6 returns its I64 argument correctly. createCallableFormWitness knows sourceIndex but lowerViaBody creates a name-only call; subsequent source recording can select the same omitted-argument witness again.

Independent body_receiver_completion_review identifies the existing SyntheticCallSite.selectedFactory → resolveWrittenMethod route as the bounded selected-declaration transport to generalize. Retain the known source through both resolveWrittenMethod and recordParametricMethodCall; the latter's trait-source branch must not overwrite it with another staticMemberResolution. Complete the ordinary default plan against the original source parameter list. This is not a generated-call exemption from signature or ownership checking.

Separately close associated logical Self/proof admission: a trait-subject conformance implementation is not a pure authored trait-namespace helper. Pinning the source alone cannot invent its proof or skip namespace checks. Preserve the selected conformance and body environment through shared instantiation/finalization, including existing source-bound evidence. Finish instance and assoc direct/generic/ABI controls and requested defaults with fresh native execution and independent review. Do not fix recursion by a backend rewrite or mask either failure.

Review refinement: pass the known conformance edge together with the selected full source declaration; admit that exact completed edge into a saved Provided operation so existing providedCopyForDeclaration interprets the concrete full-source copy. Defaults append the adapter without dropping the source from witnessFuncIds. Preserve adapter/source ParamId correspondence, including method binders absent from value arguments, rather than inferring them again from an empty omitted-argument list. First retain the existing namespace guard: source preparation has its exact lexical Self and concrete dispatch should reach an isProvided copy. Do not bypass that guard using only originTraitOwner or a synthetic marker; any remaining direct-body path must prove the retained edge and complete receiver. This refinement is independently reviewed and does not itself certify an implementation.

## Scoped Fresh Findings

Isolated source cb6e411d builds but fresh-1 rejects the instance and assoc default controls at selectedStaticCallDeclaration: Provided admitted only pure trait-owned provided methods, not an exact conformance implementation. The follow-up distinguishes immutable authored implementation functions from normalized witness functions, initialized once in registerConform and retained through derived copies and completeConformWitnesses. The exact saved proof/receiver and authored source justify implementation/default-generator admission; ordinary trait namespace checks remain intact. No synthetic exemption is added.

The result-only method-binder control also exposes recordParametricMethodCall using the strict finalMethodEnvironment before expected-result completion, dropping an already known provided proof along with unresolved method arguments. Source recording now retains inferMethodEnvironment's partial substitution/proof until the existing expected-result join and unchanged complete-call publication checks finish it. This is a finite paired call-record boundary in the same generic forwarding control; no final validation is weakened.

## Current Implementation and Remaining Verification

The isolated implementation at5c7b6562 keeps the selected declaration,
conformance and exact lexical binder vector through ordinary source recording.
Conformance registration freezes authored functions separately from normalized
witnesses. Direct nominal sources retain Direct calls; trait-subject sources
retain completed proof-backed Provided calls. Expected-result inference can
complete unknown method binders without discarding the known receiver/proof.

Copy preparation reads authored and normalized membership under a unique
original edge. Derived placements are not declaration owners. Bare conformance
implementations are copied by trait-subject expansion, and namespace expansion
keeps pure providers and extension witnesses excluded from that pass. This
removes last-wins source-owner recovery and copying an unrelated target's
implementation merely because it has the same receiver trait. Synthesized
adapters stay private; authored source-callable surfaces remain available.

The independent static review accepted these as the same finite paired
forwarding repair. Fresh3 and fresh4 failures are retained. Fresh4 passes20/21
native controls including the original crash, nominal defaults, generic binder
transport and corruption controls; its new multi-target Unit test still exposes
the copy-owner defect repaired at5c7b6562. That revision is not yet execution-
certified: standard build20261025T025908-build-2e0884, the expanded native/reject
controls, whole-source check and targeted LLVM22 ASan/LSan remain required.
No final performance, fixed point, complete suite or main admission is claimed.

The new internal identity fixture initially failed before its assertions because
its two same-named associated implementations violated declaration overlap.
Using separate source traits preserves the foreign-owner test's purpose; its
staged diagnostic then executed successfully. The new Bool golden was corrected
to the existing1/0 print contract. These were never-green new test setup errors,
not changes to established source tests. All failed runs remain in the isolated
checkout's tmp/phase3-default-forwarding directory.
