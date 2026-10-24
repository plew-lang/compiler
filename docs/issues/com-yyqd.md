---
id: com-yyqd
status: closed
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

## Outcome

Production a1ed4c14, placement-only58e5888f. Initial build191613 rejected free
functions in impl-only part; three helpers moved verbatim into defining Ir.pw.
Successful standard build20261024T191829-build-638558; fresh474f057d sourcecheck
and normal26/panic2/reject8 pass unchanged. Same source oldedd median6.062866s,
new4745.872261s, all six LLVM outputs identical. Independent b2 rechecked source,
14 referenced hashes, all input records, six LLVM outputs and actual machine code.
Recursive helper ABI and measured hot callers close; typeIsClosed wrapper still
has16sites/10functions, a residual optimization rather than universal elimination.
Strict machine instruction count closeBodyProjectionTerms435→87, not436→88
which included one blank disassembly line. Five closedness sites259→19–24;
private readers have no retain/drop.

Formal20261024T192558-self-host-689981 gen2 fixed point, complete LLVM/runtime
and successor binary hashes equal, exit0/inputsunchanged. All three measured
times6.349646/5.871513/5.899920s; median5.899920s. Saved measured6ddf8f75 at
bin/plewc-perf-type-pools-fixed. Speed criterion independently admitted.
Durable receipts: meta/evidence/performance-six-seconds/type-pool-queries.json
and type-pools-formal-self-host.json. Whole performance parent remains open for
measured-compiler milestone verification; no phase3/G2/main/seed promotion.
