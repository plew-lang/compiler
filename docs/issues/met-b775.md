---
id: met-b775
status: in_progress
deps: []
links: []
created: 2026-11-28T10:31:20Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [performance, mid, ownership]
---
# Reuse verified ownership analysis for the same canonical Mid body

First design and measure a bounded reuse of ownership analysis already computed during successful declaration ownership verification, through existing MidOwnershipRequests to destructionBody/elaborateCanonicalMidDrops for the identical original immutable canonical body. Current controlled selfcompile:45752 analyses,37558 unique body IDs,8194 repeat requests; repeat-path attribution and memory cost still require measurement. This is not a process-global cache and does not assume every repeated ID is safely reusable.

## Acceptance Criteria

Enumerate exact provider/consumer and canonical/session/arena lifecycle; retain actual successful analysis as owned opaque evidence, never infer validity from a naked integer ID. Preserve input shape verification, failures, Drop output verification, executable verification and accessibility analysis; never reuse across instantiated/access/drop-rewritten IDs. Check loops, joins, move/destruction, invalid/foreign contexts, failures and repeat outcomes with TDD and independent review. Quantify actual reused requests/transfers and retained states/RSS; compare noninstrumented same-toolchain fixed-source outputs and time. Adopt only supported improvement, or reject bounded candidate with evidence. No language, verifier or benchmark weakening. Formal sub-7-second recovery remains a separate overall goal gate.


## Bounded validity and scenarios

The flow provider remains after shape, flag and binding-origin checks in the shared verifier; only successful declaration verification publishes it. Drop owns an opaque computed-flow/input pair. Requests and tokens are fixed to sourceFactSession before cache lookup, within the existing same-Comp append-only arena contract. Arbitrary Raw arena replacement or same-session fork substitution is not certified (met-wuzv); no body count or integer ID is claimed as an arena identity. Accessibility, cliff refinement, output verification and executable verification remain separate.

Scenarios: original repeated request/destruction; loops/joins/moves and existing declaration ownership controls; append unrelated body; malformed/failed request and repeated failure; independent compilation session and unregistered request token; transformed output gets fresh analysis. Existing measured repeated-flow counts are the cost RED; the new session fixture additionally exercises cache admission RED. Measure actual reuse/retained states/RSS before adoption.
