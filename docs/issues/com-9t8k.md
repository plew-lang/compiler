---
id: com-9t8k
status: closed
deps: [com-ksl8]
links: []
created: 2026-10-24T17:15:04Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, mid, verification]
---
# Index instantiated local result types in one canonical body scan

## Bounded Action

Within appendCanonicalInstantiatedLocals only, replace the per-eligible-local
output CFG scan with a call-local dense last-nonzero-rvalue-result index. Preserve
output block/statement order, every original whole destination's local-count
extension, anonymous/nonparameter/recipe-zero eligibility, extra temporary
metadata, zero-no-override, and every original instantiateMidType call/error.
The index is a mechanical representation result, not source type inference or
a cache shared across body/environment/stage. No helper is exposed for testing.

/root/body_receiver_completion_review independently confirms this input-validity
argument and human-under-one-day scope. Existing result queries read completed
rvalue/operand/place/conversion rows and do not depend on appended local rows.
Dedicated internal contrasts plus existing recipe/Unit/missing/owner/cleanup
controls precede admission. Measure total self compilation and identical-source
old/new behavior; no below6s contribution is promised before measurement.
## Outcome

Closed with production7e3b8aeb and fixtureddcad2b5. Standard
build20261024T171854-build-e31918 and fresh full-source checking pass.
Native17/panic2/reject7 all pass with unchanged inputs; fresh compiler
bf6de4f19011e75b764bc63a7e52b0f2c79573d664828d1483fa4a9087849258.

Identical-source alternating old/new3-run diagnostic medians7.032251/6.980165s
generate identical LLVM6adaa78... . This is a small difference with variability,
not a formal performance certificate or an isolated guaranteed52ms gain. The
representation-preserving complexity improvement and absence of clear total
regression are admitted; below6s/parent milestone gates remain incomplete.

/root/body_receiver_completion_review verifies all10 receipt references,
239 focused and239 matching inputs, binary and embedded summaries.
Durable evidence: meta/evidence/performance-six-seconds/local-result-index.json.
No main/seed/adopted-carrier promotion.
