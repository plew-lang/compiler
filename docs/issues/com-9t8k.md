---
id: com-9t8k
status: in_progress
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
