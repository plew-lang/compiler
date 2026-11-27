---
id: met-oxch
status: open
deps: []
links: []
created: 2026-11-27T13:54:21Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [spec, design, generics]
---
# Specify associated projection through an inheriting trait

## Required source decision

For trait Parent { type Output }, trait Child: Parent {}, where T: Child,
T#Parent.Output is accepted. Decide whether T#Child.Output is forbidden because
Parent declares the member, or permitted by resolving the inherited member.
Spec08 describes explicit originating trait selection, but does not explicitly
settle this inherited namespace spelling. Spec09 requires a complete trait
instance. The current implementation is evidence, not normative grounds.

This blocks met-o5z0: promoting every absent-own-member refusal to Source would
implicitly decide this case. Do not label it a proven source violation until
adopted. No new superclass lookup or ad-hoc Source exception is authorized.

## Evidence and completion

Old149aac rejects the new Child projection control. It accepts the Parent
projection under the Child bound. TraitDef.assocTypes is declaration-local;
lexical inherited lookup retains the actual declaring parent owner. An earlier
review assumed a flattened namespace; that assumption was corrected on source
inspection. Existing inherited lexical/parameterized controls remain valid.

Record the user decision in spec08 and relevant design, covering Child/Parent
spelling and parameterized full instances, then add positive/rejection tests.
If inherited projection is adopted, clarify ambiguous/multiple inherited member
paths before implementation. Do not rewrite current behavior into a specification.


