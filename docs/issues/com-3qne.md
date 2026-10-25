---
id: com-3qne
status: open
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
