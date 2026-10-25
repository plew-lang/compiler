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

## Targeted Implementation and Results

Production043e2402 (ff016aae/9849c4b1/4a9e2e30) with fixture17537a40
passes standard build20261025T060222-build-122b57, focused-3 native12/
reject7, sourcecheck-3 and full gen20261025T060459-gen-6ca12d positive25/
reject5/skip0/fail0. All terminate0 with recorded inputs unchanged. Candidate
bin/plewc-gen-receiver-3 SHA256
f67e25ae60b8ee8bba902325f6341c805fa39619100f6402ebd29b8230c88785.
Receipt meta/evidence/existing-feature-conformance/source-owner-facts/synthetic-construction-identity-repair.json.

The exact directive owner offset is distinct from its canonical struct name
span. An initial new implementation confused those fields of the legacy Bind
identity carrier; the intermediate failed gen remains failed. The corrected
producer gets spelling from the selected StructDef and retains its offset as
identity. Bare derives do not manufacture a construction term. Common Record
consumes saved/typed heads without spelling recovery; typed generic/rigid/Self/
record controls and missing-head corruption remain distinct. No receiver
verifier or visibility rule was weakened. Original directiveargs unchanged.
Independent final result/fingerprint review pending; latest static review has
no blocker. Full changed-input G1/G2 obligations remain mandatory.
