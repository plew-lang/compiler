---
id: com-i5vp
status: closed
deps: []
links: []
created: 2026-10-22T01:08:48Z
type: task
priority: 2
assignee: Koji Murata
parent: com-604k
tags: [design, verification]
---
# Review phase-two correctness completion independently


## Scope and Reviewed Input

Independent completion review of phase 2's bounded correctness units, not main integration or the whole conformance goal. Initial input: compiler ce65512ab257e4fe65dd214963364d24436ebeda (implementation 9fd85bb6), meta 3be032fc, spec 7f08c79e2b9ef388ebbbbb0a5a01e1fba57ec915, Syntax 8c89204230c3d865ea95a03382c3fd213731e1de. The preserved dirty compiler binary and Python caches are not review patches.

Three independent agents inspect Buffer capacity/allocation, root-owned use and source/provider migration, and object/ORC DataLayout ownership/publication with saved validation. The parent also reconciles issue scope, progress, carrier hashes and gate identities. Review producer-to-final-consumer contracts and failure cleanup, rather than accepting green totals alone. Do not turn future features or the final integration gate into extra phase-two repair requirements.

## Findings and Corrections

- Buffer reviewer: no blocking defect found; traced checked preparation, typed ownership, receiver publication and final destruction. A focused checker on the final carrier passed runtime O0/O2 and JIT cases. Existing collection reentry remains separately scoped.
- Corrected P2, root-owned use documentation: the sources/modules example and two metaprogramming paragraphs retained part-local imports despite the adopted root-only contract. Correct them to target-root shared bindings, keeping provider host imports separate.
- Corrected P3, spec wording: selective use still said names bind to the file. Correct it to the module.
- Corrected P2, ORC negative control: the supposed signature-only mismatch input contained executable code and lacked body identity metadata, allowing another rejection reason to satisfy the assertion. Use an actual declaration with valid plew.body metadata; test absent/matching layout registration and lookup success without preparation, and incompatible layout failure/terminal state/lookup failure with the case-specific layout diagnostic.

## Re-review and Outcome

The root-use reviewer accepts the four corrected documentation passages and recognizes com-w4c2 completion. The ORC reviewer accepts the strengthened signature-only test design, but that positive control exposed a new production failure: LLVM20 heap corruption after looking up, not executing and destroying a lazy entry. Three standalone reproductions confirm SIGTRAP; a technical OS report extract identifies free-block corruption at the next allocation. The leading SymbolStringPool lifetime hypothesis is source-based and not yet proven by a production patch.

P1, native teardown: [com-34wl](com-34wl.md) owns isolation, correction and regression proof. com-6ygf is reopened with that prerequisite. Buffer remains accepted; root-use is accepted after documentation synchronization. **Phase-two completion is not recognized at this point.** Phase-three implementation is held. The production admission patch has no new finding; documentation/test corrections did not change compiler production source, seed or carriers.

[Review evidence](../../../evidence/existing-feature-conformance/phase-two-review/README.md) preserves the three failing normal runs, native/test hashes, technical crash excerpt and LLVM22 native ASan/LSan success. The sanitizer success does not override a normal-build heap corruption: libLLVM and generated JIT instructions are outside that instrumentation. Original performance/integration evidence retains its original input scope. Full-suite and performance reruns were not performed for this review; future production correction must use applicable validation. The review is complete as an investigation, with an open blocking repair; it does not certify phase two or main readiness.

## Verification Limits

The Buffer reviewer reran its bounded checker using the recorded final carrier: generated runtime O0/O2, normal JIT CoW and both capacity panic controls passed. Typed receiver failure ordering is also checked by source tracing; injection occurs in the actual generated C floor, not directly into the LLVM receiver slot. Collection reentry and other whole-floor operations remain their own tasks.

The root-use reviewer reran three existing positives and four targeted rejections on the saved carrier and re-reviewed the corrected spec/design passages. No production/Syntax/fixture changes were needed. The ORC reviewer independently accepted the new signature-only control but withheld completion because its legal unexecuted-entry lifecycle crashes normally. Reviewers verified saved carrier/source/test hashes and respected the distinction between bridge/host ASan and libLLVM/JIT instructions. The normal checker now deletes old success summaries at run start; a failed current run cannot be mistaken for a prior success.

## Blocking Repair Follow-up

The independently discovered teardown blocker is resolved by com-34wl (`87b382d2`), with the strengthened regression unchanged, both native configurations green, fresh fixed point/median under seven seconds, and affected AOT/JIT product checks. See [repair evidence](../../../evidence/existing-feature-conformance/orc-lifetime/README.md). com-6ygf can close and phase two can advance on that bounded evidence. This follow-up addresses the existing review findings; it is not a claim that the independent agents reviewed the new patch. The original review input and withheld completion above remain historical evidence, not the current unresolved state.

## Current-State Completion Audit

[The saved audit](../../../evidence/existing-feature-conformance/phase-two-review/completion-audit.json) checks the phase-two requirements against current files and artifacts rather than issue status alone. Buffer's arithmetic, allocation and ownership controls remain covered by its floor/sanitizer evidence and the later normal gate. Root-use's normal/generation and focused sanitizer controls remain applicable: all 166 source, 11 standard-library and 5,232 fixture input hashes still match that normal gate. Subsequent production changes are confined to native layout admission and pool ownership, covered by the strengthened normal/sanitizer controls and current measured compiler's product entry checks. The earlier saved carriers and the current measured carrier match their recorded hashes; the full raw self-host result matches its saved hash and reports unchanged inputs. The audit confirms the existing review finding is repaired and phase two is complete. Whole-conformance and final-candidate integration requirements remain open in com-604k.
