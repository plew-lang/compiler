---
id: com-nsxb
status: in_progress
deps: []
links: []
created: 2026-10-21T12:58:26Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Audit adopted design contracts through implementation consumers

## Scope and Pinned Inputs

Detailed read-only design/implementation audit requested after closing the
canonical design review. Design/source input: compiler `78bd96912aacb39ee2601e95a877c33e0b556ac7`;
spec `1e0c4d08777edc521e0e64f42588d4996b1c66d8`; Syntax pin
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Preserve the dirty compiler binary and
untracked Python caches; neither supplies execution evidence.

[met-z0ro](met-z0ro.md) is the representative-domain inventory, not this audit's
completion evidence. Reuse its owning tasks, but recheck source and saved-result
consumers rather than copying its conclusions.

## Method and Completion Boundary

For each adopted boundary record the contract, concrete producer/key, storage and
publication, substitution/consumer and failure/cleanup path. Distinguish a traced
conforming route, mismatch, absent family, partial closure, unverified combination
and intentionally deferred feature. A matching declaration or verifier alone is
not end-to-end evidence. Cite exact source symbols and the pinned revision.

Cover the 18 reference domains and storage/library/collection supplements. Dig
into source-to-final-reader closure, synthetic and global owners, proof/instance
identity, Mid stages, async ownership and driver/resource boundaries. Record
uninspected combinations explicitly; do not infer a newly reproduced runtime bug
from source-only architectural gaps. Existing tests may be read, not rerun.

Finish with owning follow-ups, dependency/order reasoning and a bounded coverage
statement. Do not repair compiler code, change language semantics, run compilation
or performance gates, promote carriers or enlarge met-si6j automatically.

## Audit Results

In progress. Findings and final coverage are recorded below as source paths close.
