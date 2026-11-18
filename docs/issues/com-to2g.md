---
id: com-to2g
status: open
deps: []
links: [com-jbau]
created: 2026-11-17T12:41:19Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, ownership, verification]
---
# Apply the same-reference-place rule to shared inout arguments

## Contract

[Spec/03](../../../spec/spec/01-basics/03-values.md#重なる-inout-は禁止排他) and
[Ownership and Access](../design/ownership-and-access.md#places-and-exclusivity)
are authoritative.

Spec/03 rejects two inout positions (including an inout receiver) that
use the same resolved binding and reference place and overlap after path
normalization. Intervening argument effects are irrelevant to this source
restriction. Preserve field disjointness, container granularity, and
separate reference places within one binding. For potentially aliasing
references outside the static restriction, use each evaluated, pinned cell
once through Access and preserve the runtime check.

## Fixed Candidate Observations

On c41653f1 both check and lazy execution reject the three-argument
current/rebind/current reproducer. This is the required result under the
adopted rule. Binding the old and new cells to separate variables before
the call yields the expected output, 1 and 2. The existing shared-disjoint
fixture also passed in lazy mode. The earlier rejection evidence predates
the decision and remains an observation of the same behavior.

The same candidate rejected two disjoint nested fields under one shared
struct field in both check and JIT, using its supported arrow spelling.
The two paths split at the final fields; retaining only their first
post-deref field loses that distinction.

The current shared branch uses exprSyntaxEq, including identifier spelling,
and emits Unclassified instead of Source. These facts cannot certify the
new lexical rule. Use retained binding and place identities where checking
source; keep dynamic evaluated identity separate.

## Required Verification

Assert the Source domain and reason for repeated inout access both with and
without an intervening rebind. Cover equivalent place spellings and distinct
lexical identities, inout receivers, containing paths, disjoint nested
fields, and indexing before and after dereference. Cover distinct
reference fields of one root, dynamic same/different cells, and unchanged disjoint and mixed cases.
Verify the source-to-Access handoff in check, AOT and lazy modes, including
lifetime and evaluation order. No new effect analysis, general alias
inference, or test audit work from com-jbau is required.


Independent contract review checked the accepted scope, the separation
between reference-handle identity and referent container overlap, and
preservation of read-borrow rules. Its nested-field example was reproduced
on c41653f1 with the arrow spelling supported by that candidate. The
contract review does not establish implementation conformance.
