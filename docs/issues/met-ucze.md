---
id: met-ucze
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

The historical 2983c47f review found Resolve/Preparation trying Record(false), Generic, Declaration and Record(true), with Record/Generic staticMemberResolution paths and different bound/trait candidate inputs. This was a structural read-only finding, not a newly reproduced current miscompile. Recheck the cumulative candidate before deciding which paths remain.

Make one source construction/selection owner authoritative and preserve the selected declaration, requirement, lexical owner and evidence through publication and final consumption. A shared selector repeatedly run by downstream readers is not completion. Preserve candidate order, visibility, labels, full signature, ownership and bounds; do not make a candidate-exists predicate final acceptance. Distinguish constructing a first concrete witness for a source-selected abstract requirement from selecting an already fixed witness again.

Acceptance: trace ordinary, generic-bound, provided, trait-subject, operator and implicit calls; remove competing source selectors/fallback accept paths, retain ambiguity/reject controls, and record remaining paths and removal conditions. The storage restart gate of met-si6j applies.
