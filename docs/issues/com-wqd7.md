---
id: com-wqd7
status: open
deps: []
links: []
created: 2026-10-13T00:48:29Z
type: task
priority: 1
assignee: Koji Murata
tags: [mid, ownership, verification]
---
# Close uniqueness eligibility of return Copy-to-Move transfer

Unverified safety boundary, not yet a reproduced compiler bug. The inspected return-transfer helper lacks the explicit uniqueness/final-destruction eligibility check present in scope-transfer handling. Executable UniqueCopy rejection occurs later, so the audit has not established whether a malformed unique Copy can be converted to Move before rejection.

Evidence: compiler source base 6fe09bc7c0e75260b3f773643921478b5020b94f; src/Mid/Optimize.pw returnTransferOperand and scope-transfer eligibility; focused review recorded in the optimization chapter. Do not report this investigation complete merely because valid compiler inputs do not generate the malformed case.

## Design

[Local ownership transfer contract](../design/passes-and-optimization.md#ownership-aware-copy-optimization) excludes unique values and requires proof preservation. Determine whether admission already proves eligibility; otherwise add the missing guard at its responsible boundary, without weakening executable verification.

## Acceptance Criteria

Prove and test that malformed unique Copy cannot become accepted through return transfer. Cover unknown/incomplete destruction information, valid eligible temporaries, and named/borrowed/special exclusions. Preserve full-body occurrence counting and final-consumer validity. Close with the actual proof or fix and its scoped verification.
