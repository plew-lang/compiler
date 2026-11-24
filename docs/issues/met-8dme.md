---
id: met-8dme
status: in_progress
deps: []
links: []
created: 2026-11-24T00:15:28Z
type: task
priority: 1
assignee: Koji Murata
parent: met-lrep
tags: [frontend, verification]
---
# Validate retained requirement scope authority against missing authored metadata

Wholec608e1 newly aborts internal existential_symbolic_result. This fixture does not call existentialWitnessPlan: after replacing sourceTypeUses by empty state, it expects recordAnyRequirementSlot and existentialRequirementSignature to reject missing authored signature as Internal. Determine actual panic and creation intent; decide from retained-authority/admission contracts whether a valid saved scope is independent authority or missing current authored admission must propagate before cache hit. Do not classify this with generic closed-payload regression and do not simply weaken expectations.

## Acceptance Criteria

Freeze actual RED and cold/warm/source failure cases; prove authority and invalidation contract, repair correct cache/admission boundary or outdated internal setup while preserving fault detection. Existing source and concrete dispatch controls retained; independent review and final met-lrep whole gates.


## Authority resolution and tested repair

SourceTypeUses reset destroys canonical authored occurrences, not just a raw index. Warm source interface retains member/scope selection identity; that cannot authorize a signature interpretation after its owned occurrence store is lost. Updated internal fixture retains prior raw TraitDef mutation assertions, then checks warm rank same slot and warm signature Internal invalid authored type occurrence; a separate cold Comp checks missing authored signature Internal in both rank/signature. Existing private failed-admission warm-hit controls remain. Native scope-green-v3 succeeds with invariant source/fixture inputs, exact ok golden and empty stderr. No product guard was weakened and no source semantics changed. Independent design review supports these separate authorities; final exact-run review and standard integration gates pending.
