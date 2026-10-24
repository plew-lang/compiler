---
id: met-v1jg
status: in_progress
deps: [met-qs57]
links: []
created: 2026-10-24T18:01:18Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, frontend]
---
# Reduce source call navigation copies and bucket divisions


## Boundary and Evidence

Prior production499c0d7f / candidatec37f338f has matching-source median6.606803s,
not formal below6s. Its uninstrumented profile lives under
compiler/tmp/perf-six-source-index/full-profile with separately executed symbol-map.
Earlier reverse assembly attributes callTemplateIndex samples to variable bucket
udiv, not the hash mixer itself. Keep exact six-field key equality and its hash.

Candidate: retain one callTemplateIndex session query but borrow Comp in place
(inout) rather than owning a whole-Comp by-value snapshot. Its35 production
callers are already mutable session operations. Index capacity is privately
produced at16/double; check and document power-of-two capacity before replacing
bucket modulo with mask at all insertion/rebuild/find/probe sites. Keep missing
and collision behavior. Also project only the site/bounds needed by the hot
selectedCallHasDeferredConstraints path if independently reviewed safe.
No prepared checks, full bound typeIsClosed checks, source identity/failure or
owner/session isolation may disappear. No semantic cache or name-based reselect.

Use existing default_argument_call_templates and prepared/source constraint
controls plus full sourcecheck. Freeze fresh input, compare old/new on identical
source serially with LLVM equality, then independent bounded-task admission.
This task does not alone certify formal <6s or main/G2 completion.

## Selected Protocol

Retain arbitrary positive rebuild capacities: a private bucket projection uses
mask only when capacity is a power of two, otherwise the former modulo. Probes
advance by one and wrap at capacity, equivalent for all positive capacities.
Do not narrow this internal API to powers of two. Extend the existing default
argument fixture for127/128 rebuild, exact key lookup, intentional equal-hash
serial collisions and missing keys. Prepared constraint projection is siteKey
plus count/subject scalar getters; prepared admission and closedness stay intact.
