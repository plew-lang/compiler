---
id: met-m7wx
status: closed
deps: []
links: []
created: 2026-10-21T11:49:55Z
type: chore
priority: 3
assignee: Koji Murata
tags: [design, documentation]
---
# Improve canonical contract navigation and remove stale descriptions

## Resolution: Editorial Boundary Closed

Stable logical obligations remain in Frontend Handoffs; legacy index/migration
observations are preserved below rather than discarded. Checked-body Storage owns
the adopted physical contract, and met-j9mv owns restart reconciliation evidence.
Stale "restart pending" duplication was replaced with issue links in Compiler State
and Frontend Handoffs. The existing section anchors were preserved.

Syntax and Mid Entry link the common string decoder directly. Spec15's opaque
handle paragraph now uses the already adopted LLVM/FFI explanation rather than
generated C/header typedefs. The architecture reviewer found no change to accepted
source, nominal handles, lifetime, sendability, ABI responsibility or runtime
guarantees, and no lost retained evidence. The temporary plan was incorporated
and retired. Local link/anchor and diff checks accompany the documentation change;
this resolution is not an implementation audit or test result.

## Scope

Editorial improvements from the design-only [met-ukm5](met-ukm5.md) review,
design `1d83231e` and spec `16f2f139`. These are not new source semantics or
evidence of a compiler defect.

- Frontend Handoffs retains stable contracts beside legacy row/count sentinels,
  concrete migration mapping and stale "reconciliation pending" prose. Preserve
  necessary invariants and rationale, but move changeable migration/current-state
  details to their owning issues and link them. Checked-body Storage remains the
  physical storage authority; do not create another status ledger.
- Link Syntax's string-literal handoff directly to the common decoder contract.
  Make lexical validity/selected value versus later physical representation easy
  to locate. Existing contracts already prohibit LLVM-only semantic validation;
  no new decoder framework or authority is needed.
- Spec15's opaque-handle paragraph still describes generated C/header typedefs,
  while its FFI section adopts Plew-owned declarations lowered through LLVM.
  Correct that mechanism-only wording, preserving one-word ABI, distinct nominal
  handles and the user's responsibility for foreign ABI/lifetime correctness.

Completion: one home for each current contract/status, working local links and
no changed acceptance or runtime guarantee. Keep prior decisions and migration
evidence reachable through issues/Git rather than deleting necessary information.

## Retained Migration Observations

Transferred from Frontend Handoffs at `b50a2606` during editorial cleanup. These
are bounded historical observations, not a new source audit or the adopted reader
API. The cumulative reconciliation in [met-j9mv](met-j9mv.md) supersedes old next-step
status. Source/instance authority and implementation closure remain [met-si6j](met-si6j.md).

### Legacy Lookup Carriers

The current name-index scheme uses row ID plus one, zero for absence, and current
row count as a transient missing-reader result. Do not cache that count across
appends. Function indexes cover generated rows too, separately from the source
callable set. Generic struct/enum lookup must seek the first matching generic
row rather than filter only the first same-named row. Additional predicates
continue through same-named candidates instead of stopping at the first failure.

A global type-parameter-spelling query excludes registered nongeneric struct
and enum names, not generic declarations, traits, or newtypes. It is not lexical
binder resolution, type identity, visibility, or conformance. Bare-name indexes
exclude arguments, views, existential/sendable decoration; their result is not
a type-equality decision. Scalar predicates need not materialize aggregate rows.

### Bounded Frontend Mapping

The following are retained implementation observations and bounded migration
contracts, not certification of the current tree. The audit base and physical
storage question remain those in Compiler State. Evidence lives in meta's
[typechecking remediation evidence](../../../evidence/typechecking-remediation/).
Focused success never replaces whole-compiler, sanitizer, fixed-point, or
performance gates, and historical watchdog failures are not newly reproduced bugs.

| Boundary | Retained state and limitation |
|---|---|
| Static/conversion proofs | Private arenas append complete child-first proofs and expose common readers; no replacement API. Proof-ID-bearing source tables and whole-owner authority still need closure. Decoding/freeze-thaw are not admission. |
| Final calls | Arena owns rows, five payload pools, and index. Publisher owns ranges and rejects duplicate body/site before row/payload publication. A private argument-tail handle checks continuation/ranges, but is neither a rollback transaction nor foreign-arena authority proof. Mid/LLVM use scalar readers; Comp owns semantic preparation/diagnostics. |
| Prepared call constraints | Private Building/Prepared states publish owned immutable snapshots only after successful function/global source obligations and common admission. Mono's Direct reader uses Prepared data without rechecking constraints. This alone does not seal type facts, selection tables, or proof stores. |
| Recorded bound consumption | Written Direct calls pass saved child proofs to concrete body admission. Static/protocol/operator/implicit calls and entry requests retain Declaration paths in the recorded candidate; do not claim complete migration. Extern/bodyless calls still require final call admission. |
| Source templates | Private rows reject selected-site replacement after Prepared; conservative storage classification is auxiliary, not reselection. Private append-only operand/type/view pools and lookup indexes do not yet prohibit every append after owner success. Historical slices: compiler `ce6e87fd` and `16f5af17`. |
| Bounds/projections | FunctionBoundArena owns stable rows and ordered per-owner indexes together. Projection-presence summaries remain tri-state for forward children. Selected normalization equations replay proofs, not lookup. |
| Owner readers | Mono expression, await, construction, assignment, Access projections, call-argument Expression sources, and global closures must share explicit successful owner facts. Global targets and closure owners cannot come from ambient Cursor. Constructing-reader closure remains incomplete. |
| Completion | PreparedSemanticCompletionOwner must identify exact session/snapshot; expressions, statements, and blocks share immutable source/execution flow. Earlier flow migrations are bounded work, not proof all readers use the shared channel. |
| Remaining acceptance | General Unit value binding/conversion, source-place mutability/ownership at all call kinds, captured generic shapes, and full signature/result/bound consumer coverage require audit. No language prohibition or confirmed current bug follows from absence of audit. |

Focused evidence directories retain separate scopes: `source-typing-closure`,
`diagnostic-continuation`, `conversion-proof-boundaries`,
`structural-proof-admission`, `box-proof-admission`, `box-proof-subjects`,
`path-proof-admission`, `assumption-authority`, `call-proof-admission`,
`call-proof-boundary`, `call-signature-admission`, `static-signature-admission`, and
`call-bound-admission`. The last includes append-only proof/final-call publication
and source-template row/pool slice comparisons. These are evidence pointers, not
adopted physical storage APIs or a current all-green claim.
