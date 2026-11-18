---
id: com-to2g
status: in_progress
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

## Source Classifier Increment

The lexical classifier now separates the reference expression from its
post-deref field path. It reads recorded identifier targets and compares
the whole field prefix up to its container boundary. The adopted rebind
negative is Source in check and lazy on a diagnostic rebuild. The nested
disjoint test and the explicit distinct bindings print 1 and 2 in lazy
and native execution. The prior direct static negative passes its reason
and domain check in check, AOT, and lazy. Existing disjoint, indexed
referent and read receiver JIT controls pass. Native distinct-alias
overlap/container panics and pinning also retain their outcomes.

Handle selection with an unknown key remains dynamic. Equal typed
constant Array keys have a static proof; different constant keys execute
successfully. An interposed mutation of a global index was rejected as
overlap by c41653f1. The new lexical checker accepts it, but lazy
execution now exposes a Mid preparation failure, so the source-to-use
boundary remains open. The reviewed checkpoint also still compares field
spellings. Audit Record's saved projected fields and use their identity
for equivalent view/via paths. Check transient field path costs before
the performance gate. Do not close the task on the scoped controls.

## Index Evaluation Handoff

AOT tracing on the previously saved diagnostic build reported a Mid
type mismatch on the block evaluating an Array reference element selected
by a global key. A single global-index operand reproduces it too. Direct
global reads and a local snapshot used as the key are successful controls.
The shared index helper treated every projection-free Copy as a
body-local slot, even for a global place whose local field is zero.

The builder now reuses only a proven stable local root. Other keys use
the existing materialization path, so the saved local names the evaluated
integer. The rebind fixture passes check and prints 1 then 2 in JIT and
native code. All eleven existing index-evaluation JIT outputs match.
Independent review confirmed the fix covers physical indexing in
ordinary value, place, and normalized-inout builders and preserves
the distinct selected-Index call path. Field selection and formal
performance verification remain open.

## Saved Field Selection

The Source overlap classifier uses the same selected field slots as Mid
for handle fields and for the referent path. Missing slot evidence leaves
the pair to the dynamic check. It does not compare spellings or re-run
field lookup. The rebind rejection and both nested disjoint and mutable
index controls retain their outcomes on the diagnostic candidate.
