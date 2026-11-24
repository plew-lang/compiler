---
id: com-p5um
status: open
deps: [com-61jt, com-auvx, com-jy25, com-nqiq, com-1a6q, com-jgy9, com-kphi, com-8lj3, met-6vbn, met-kuej]
links: []
created: 2026-10-23T10:41:59Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Verify the frozen candidate fixed point and formal self compilation time

## Recorded diagnostic fixed-point measurement (2026-11-19)

The WIP formal measurement at that checkpoint was [ThinLTO source0d677b0a](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-thinlto-formal-self-host.json), run20261119T164158-self-host-8d831e. Exit0, unchanged inputs, generation2LLVM/runtime/successor binary match. Candidatefc2fba44 has7.303893/6.810615/6.929691 seconds, median **6.929691 seconds**, restoring below7. Actual linker/libLTO/backend inputs are frozen and per-generation tool identities checked. This is a WIP refresh, not final frozen-G1/G2b completion. The gate remains open until its prerequisites and final admission close; main/seed/adopted carrier stay unchanged.


[Source56985a02 formal record](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-assignment-formal-self-host.json): standard run20261119T094138-self-host-59a400, carrier37fefb30, unchanged inputs and exit0. Generation2LLVM/runtime/successor binary match; all three measurements use1963e4c5. Times7.620871/7.132441/7.186216 give median **7.186216 seconds**, above the absolute seven-second limit. Neutral review verified197 src/std files against56985a02 and the recorded hashes/attribution. This is a diagnostic WIP measurement, not frozen-G1 final gate completion or functional green. Main/seed/adopted carrier remain unchanged; recovery has not been judged difficult.

The nominal-layout index trial is rejected for no demonstrated whole-time benefit. A natural sealed SourceBodyData head-reader trial instead creates a1200-byte snapshot at the caller; it is not adopted. An extra verified argpromotion/SROA diagnostic still leaves that snapshot. [Caller investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-source-head-projection-investigation.json). Conservative snapshots for reference roots remain within the current ABI contract; extending forwarding requires its own safety proof, not disabling access or ownership checks.

## Current Candidate and Gate Boundary

Use the current development carrier and latest formal receipt from the
[meta worklog](../../../agents/worklog.md) and the
[approved performance criterion](../../../agents/validation.md#自己コンパイル性能基準).
The final gate requires a G1-admitted frozen candidate; passing a development
fixed point does not close this task. Historical073f0375/043e2402/3c532ce1
and November19 measurements certify only their recorded inputs. Current whole
source admission and exact measured-compiler correctness gates remain required;
main/seed promotion is separate.

## Boundary

Phase 3G / G2a. **Final standard gate.** Parent criteria: 10.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `scripts/diagnostics/measure-self-host.sh`; `docs/issues/met-si6j.md`.

Use meta ./validate self-host with the explicitly recorded validated carrier and frozen G1 inputs. Preserve generation transition LLVM/runtime comparisons and all adopted-generation runs. Record the measured compiler/hash for G2b; no concurrent build/test or diagnostic instrumentation.

Each generation and timed repeat must produce nonempty LLVM IR and runtime C.
Empty output is a measurement failure before linking, comparison, or median
publication, even when the compiler process reports success. The tooling
regression covers both artifacts. Compiler-side output error propagation is
tracked by [com-x386](com-x386.md).

## Exit and Evidence

Standard gate exits0 with unchanged inputs, fixed point and formal median within the [approved bound](../../../agents/validation.md#自己コンパイル性能基準). Investigate any observed regression with matching-source conditions, fix easy extra copies/searches and return repairs to their owning task; stop if the adopted limit cannot be repaired. Do not promote seed/carrier or merge main here.

Existing starting controls: The finite deliverable above names exact controls/commands before any required execution.

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Outcome

Independent c2_classification_review accepts refreshed standard gate
20261025T061121-self-host-f849e0 at sourcef225570e (production043e2402,
fixture17537a40). Exit0, all5,990 inputs unchanged and matching G1/current
files/tools/dependencies. Generation1 ->2 changes LLVM; generation2 ->3
matches LLVM/runtime exactly. All measured outputs match. Timings6.384374 /
5.954309 /5.924183 seconds give formal median5.954309 seconds, below7
(and below6). No sampling or overlapping validation.

Measured compiler: meta/tmp/validation/20261025T061121-self-host-f849e0/self-host/generation-2/next/plewc,
SHA256 3c532ce1c7d1e2b0be6bc1c24b8c215a92be87625c65f531a0d83dc1719830b1.
The generation3 successor has the same hash. G2b consumes this exact compiler.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/phase3g-self-host.json
retains all timing/artifact references. Older gates remain in Git/raw history
and are not same-source speed comparisons or new-candidate certification.
Full suites, parent completion and main/seed/adopted carrier remain uncertified.

## Test Admission Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) installs required finite repair/investigation prerequisites at this actual admission: com-nqiq (row11), com-jy25 (row12). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 97.

Row97: Direct standalone claim needs external complete fixed-input proof. Preserve measured candidate/fixed point/approved formal bound/refresh; old3c532ce1 not current gate, no new anonymous checker repair. Existing open G2a is actual G2b prerequisite after G1. Standalone collector is bounded; standard validate includes locked closure/native/support/carrierStd/run_gate before+after, so B133 assigns no new standard-gate defect. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Dynamic LLVM / Plew-runtime ThinLTO diagnostic

[Six-second CPU window](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-wide-cpu-investigation.json) shows distributed ARC/Array preparation and verification costs, without proving a new unnecessary source pass. Review permits a separate isolated link trial: retain the exact formal56985a02 optimized LLVM/runtime/native backend archive and dynamic libLLVM, add clang20 `-flto=thin`, and record the selected LLVM20LTO implementation and hashes. Compare identical source with all old/new outputs and samples retained. This targets Plew/runtime optimization, unlike the older static-LLVM-library ThinLTO distribution trial.

No permanent product pipeline, source semantics, ABI, runtime duplication or carrier/seed/main change is authorized by the diagnostic result alone. A benefit may include global codegen/layout effects, not only cross-TU inlining. Direct-native-object development integration would require its own compatibility assessment after evidence.

### Diagnostic outcome and reviewed integration units

[Retained link comparison](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-runtime-thinlto-investigation.json) shows all5 alternating pairs improve: medians7.027126→6.704112 seconds, all10LLVM outputs equal formal2eabe0dc. The measured symbol-preserving candidate9b148ff0 retains138/138 runtime exports and24CLI controls. Earlier debug-option and symbol-internalization attempts are separate; they are not the measured success. Performance review found no must-fix. This is not a formal7-second gate or whole-program semantic certificate.

Integration review recommends three finite units: (1) shared compiler-link profile with actual toolchain/export recording; (2) summary-bearing native ThinLTO object producer under an explicit internal request, preserving ordinary machine output; (3) ADD→USE transition and both-path final validation, depending on1+2. Text and native stages must agree, the common runtime remains single, and a native machine object must never be relabelled as LTO-capable. Bare bitcode is not sufficient ThinLTO proof.

User approved execution. Units are met-8ibr (shared link), met-jv7m (native artifact), and met-kuej (integration, depending on both). This gate depends on met-kuej; no formal gate ownership is duplicated. Finite integration met-kuej and WIP formal performance recovery are now verified; final G1/G2b gate completion remains open.
