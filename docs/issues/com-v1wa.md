---
id: com-v1wa
status: in_progress
deps: []
links: []
created: 2026-10-25T05:47:53Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, generics, verification]
---
# Retain selected parameterized derive receiver identity


## Boundary and Exit

G2b gen20261025T054226-gen-36c9dc exits1 with frozen inputs:23 positive,
5 rejects and1 failure. Existing directiveargs fails harness compilation with
body receiver mismatch; trace actualTagged decl0 versus patternTagged decl395.
Old6ddf8f75 also reproduces, so this is not attributed to the recent root fix.
Valid fixture expectations remain unchanged.

Gen::checkDirectiveArgsPublic resolves the exact directive declaration in its
source module, then synthGenMain drops that identity in Expr.Make ty0. Retain
the selected owner as a complete/non-inferred construction head and pass it
through ordinary Record, saved selection, BodyInstance and final ABI. Preserve
visibility/public-field checks; no downstream name fallback or weakened receiver
check. No new macro role or generic macro language surface.

Controls: original directiveargs unchanged; alias and same-spelled unrelated
module declarations; ordinary derives and private-field/visibility rejects;
sourcecheck and representative C3 receiver/owner controls. Fresh full gen can
close its bounded controls but never substitutes for G2a/G2b after all repairs.
Common untyped-Make admission is separately owned by com-tkz7.

Independent b2_completion_review accepts this finite scope and separation;
completion remains subject to actual results and independent final review.
