---
id: com-tkz7
status: open
deps: []
links: []
created: 2026-10-25T05:47:54Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, generics, verification]
---
# Close untyped named construction head admission


## Boundary and Exit

The same G2b diagnosis exposes Record::recordExpr(Expr.Make)'s nominal fallback:
its comment promises declaration resolution, but simpleTypeRef publishes only a
head spelling. inferMakeInstance returns0 for nongeneric heads, leaving that
identity absent. com-v1wa owns the Gen producer's already selected owner; this
task owns only the shared genuinely untyped named construction head.

Classify and close the exact four rows before code: completed ty/saved fact is
unchanged; nongeneric named input selects its canonical owner in the explicit
source occurrence; partial generic retains that selected owner while ordinary
field/expected-type inference fills arguments; rigid/Self/structural terms do
not become nominal merely because a name is present. Do not unconditionally use
declaredTypeRef(args:[]) because its complete-arity precondition rejects the
partial generic case. Source visibility and factory semantics stay unchanged.

Producer -> complete source fact -> saved receiver/signature -> explicit
BodyInstance -> Mid/LLVM must hold without missing-owner final recovery. Add
focused real-declaration raw-Make controls covering nongeneric, inferred generic,
context-completed generic, aliases/homonyms, existing committed types and
rigid/Self/structural exclusions. Record exact removed fallback and refusal
controls; sourcecheck and related native/reject slices, independent review.
If classification exposes another source family, split before widening. No new
inference or language behavior is authorized. Final whole-candidate G2 remains
mandatory after both repairs.

Independent b2_completion_review accepts this bounded separation and cautions
against complete-arity APIs for partial heads. Implementation/results pending.
