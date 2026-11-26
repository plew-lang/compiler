---
id: met-7ust
status: open
deps: []
links: []
created: 2026-11-26T04:29:30Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, verification]
parent: met-iv6d
---
# Define repeated part admission from the same parent


## Decision required

Spec15/design define at most one parent, not whether the same parent may name
the same part twice. Spec16 defines auto-part membership, not repeated-edge
handling. Current explicit+explicit rejects while explicit+auto dedups; both
paths must be represented in the common discovery admission repair met-iv6d.

Choose whether same-parent repeats are uniformly deduplicated, uniformly
rejected, or explicitly distinct by written/automatic origin. Recommended:
deduplicate the same parent/target once for explicit and automatic introduction,
while different parents and Root/Part conflicts always reject. This follows
one logical edge/one parent and avoids a macro-specific acceptance exception.
Tradeoff: repeated written part no longer diagnoses a redundant directive.
Reject-all would make explicit+auto inclusion fail where it currently succeeds.

Independent qualified_member_plan confirms no existing normative decision
and that diagnostic wording is not a specification.
[Executed minimal cases](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/README.md).

## Scope and completion

Obtain user decision, update spec15/spec16 and matching sources-and-modules
contract as needed, check existing same-parent explicit/auto usage and identify
required migrations, add the chosen scenarios to met-iv6d, obtain independent
review and save/push the decision. Do not implement graph machinery here or
weaken tests. Until decided, no new Source authority for same-parent repeats.
This task is open awaiting language judgment; product is unchanged.
