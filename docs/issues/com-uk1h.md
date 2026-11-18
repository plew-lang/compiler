---
id: com-uk1h
status: open
deps: []
links: []
created: 2026-11-18T10:09:30Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, traits, generics]
---
# Resolve trait field requirements through their via witnesses

Spec/08 defines field requirements as access to storage selected through an explicit via witness. At 241b58b6 a locally defined Drawable with val width: I32 and impl Sprite as Drawable { val width: I32 via w } is accepted when unused. For item: Sprite, item#Drawable.width fails with no such field; inside fn read[T](item: T) -> I32 where T: Drawable, item.width fails with traits declare methods, not fields. These precede and are independent of shared-inout overlap classification. The missing trait-field selection path is separate feature work outside the current existing-feature conformity phase.

## Design

Resolve and validate field witnesses at their declaration owner. Publish the exact storage declaration and projected type under the selected trait instance; concrete and generic consumers, including Mid, consume that selection. Keep intrinsic field selection and shared inout overlap consumers on the same physical field identity.

## Acceptance Criteria

Cover a concrete view and a generic bound reading a differently named storage field, two requirements with overlapping names but distinct trait witnesses, missing and incompatible witness negatives, and the unaffected unbounded generic negative. Compile and execute the success controls in AOT and lazy modes. Independently verify the saved selection from publication through lowering.

