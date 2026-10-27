---
id: com-sn9w
status: open
deps: [com-2hx2]
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Audit phase three API authority from source decisions to final consumers

## Entry and Scope

Use the revision-pinned map/bounded batches from com-2hx2 and the normal
project development rules. Existing evidence is a starting point, not a certificate. Audit
all assigned phase-three decision boundaries, not just the lexical reproducer.

For each API/constructor compare the information and operations it needs with
what callers actually provide and what fields, captures, globals or Comp allow
it to obtain. Trace legitimate input production, committed decision/failure,
publication, explicit instantiation and final use. Identify independently repeated
selection/inference, ambient owner recovery, partial admission and unrestricted
fallbacks. Follow all observed callers of the competing API; inspect old-path
removal claims against source.

Do not treat every broad parameter as a proven bug or forbid legitimate lookup,
source positions, concrete instantiation or independent IR consistency checks.
For each finding give a contract, concrete path and reproduction or source-level
contradiction. Separate confirmed violation, bounded unresolved hypothesis,
justified design and optional simplification. Describe the narrow end-state API
and its producer-to-consumer replacement; wrapping Comp alone is no boundary.

## Output and Completion

Every assigned map row has a supported disposition and required checks. Provide
finite repair candidates with producer/consumer/removal scope and test controls;
link existing owners rather than duplicating them. Feed com-x7r3 with the map
and findings. Independent review checks unexamined entry points and responsibility
claims. This is an audit: implementation, gate success, whole-phase admission
and semantic changes are excluded. Each confirmed finding must have a finite
proposed repair/disposition and a linked receiving owner before audit closure. com-x7r3 is the receiving assignment
owner where final repair placement needs the combined audits; it installs actual
repair and G1 dependencies after these audits close. Do not require com-x7r3 to
finish before its prerequisite audit can close. Audit closure does not certify
repair completion or allow G1 admission.
