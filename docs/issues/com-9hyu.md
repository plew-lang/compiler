---
id: com-9hyu
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: bug
priority: 2
assignee: Koji Murata
tags: [runtime, verification]
---
# Make existential dictionary replacement observe the new value

## Evidence and Boundary

com-8iys source-only audit of tests/fixtures/run/any_generic_collection.pw at9665094d found d["a"] changed from Sq(s=3) to Rect(w=3,h=3); both return area9. Omitting that assignment produces the same complete stdout. Original a2c967bb explicitly intended to exercise reassign; this is a test detection gap, not evidence a real compiler currently skips writes. Report: meta/evidence/test-audit/scoped-reviews/run-head-0087.json.

## Guarantee

Make the overwritten key expose both the new payload/witness outcome and unchanged other key/size as applicable. Reuse existing insert/read and heterogeneous controls; preserve Dictionary[String, any Shape] source validity and actual normal-run path. A controlled suppressed or wrong replacement must fail the actual assertion; correct replacement must pass. Choose distinct semantic results rather than physical layout or RC spelling. Include applicable heap cleanup checks if the changed payload needs them.

## Completion and Exclusions

Follow TDD, verify complete stdout and actual registration/runner, independent review. Finite fixture/assertion repair; no general Dictionary implementation rewrite unless a separately evidenced defect is assigned. No new language rules and no fresh candidate correctness claimed by this issue.

