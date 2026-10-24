---
id: com-yyqd
status: in_progress
deps: []
links: []
created: 2026-10-24T19:13:59Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, types, storage]
---
# Keep recursive type summaries on minimal read-only pools


## Boundary and Evidence

Latest formal20261024T190512-self-host-b70978 gen2fixed median6.051719s,
measured compileredd0ae71 saved bin/plewc-perf-operation-head-fixed.
Same-source operation-head cleanup is correct but formal overall unchanged.

Current f215 profile5s: closeBodyProjectionTerms47self samples,42 at pre-guard
Arena full argument assembly by disassembly offsets; not environment ARC.
typeIsClosed1897 instructions with Arena-recursive ABI, selected caller sites
retain259-instruction full argument assembly. typeTermRefSameHead173instructions
has direct TypeTerm loads and no same issue, excluded.

Keep public readonly Arena APIs. Thin wrappers pass only terms/record-field/
argument/associated-argument pools (plus bytes for closedness) to private
recursive readers. Share the exact Self-name byte predicate. No inout capability
change, no new cache, no moved caller guard, no omitted checks. Preserve zero/
out-of-range, unknown/forward children, record short circuit and mismatch,
child order, declaration stamping, immutable snapshot and lazy bytes behavior.

Validate sourcecheck and structural/forward/snapshot/associated-projection/Mid
controls. Machine proof must show giant caller argument assembly removed.
Compare against measured edd on identical new source, then formal run if useful.
Independent review required; no source acceptance/ownership/output change, no
main/seed/adopted carrier promotion.
