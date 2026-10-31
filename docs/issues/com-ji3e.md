---
id: com-ji3e
status: open
deps: []
links: []
created: 2026-10-28T00:55:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Cover cross-module getter-only field access


## Finite Guarantee and Evidence

Source-only audit at compiler9665094d/spec5bd65a5 finds no registered contrast for the public-read/module-write asymmetry of `pub(get) mut val` (spec05 Member visibility). Current run/pub_get_field and member_pubget_write operate inside the defining module. Module-private cooperation confirms same-module writers. part/memberwisemodule exercises public factory construction attributes and calls sum(), not external direct getter access or forbidden post-construction setter. Three selected reject roots only check pub-selector/val grammar.

Bounded candidate discovery uses whitespace-tolerant pub(get)/pubget searches over tests/scripts and full reads of the resulting source roots/companions, part Main/Lib, references and registrations. This is a static coverage gap in the inspected corpus, not a reproduced compiler bug or a proof that arbitrary generated tests could not express the rule. Existing com-zgk9 concerns collection places/inout through pub(get) arrays and does not own this elementary visibility contrast. Evidence is retained in audit-batch0055 and its independent receipt.

## Scope and Completion

Add or reuse exactly one owner-authorized two-module pair: direct external read succeeds, direct external write fails for the getter-only field. Publicly construct an otherwise valid object through an admitted factory; do not accidentally test private factory/field reachability, immutable caller binding, absent name/import, or only construct-time attribute assignment. Preserve same-module write success and public read+write ordinary field behavior as needed neighboring controls; do not duplicate the entire visibility matrix or broaden into collection inout/callback effects.

Recover original purposes and follow task-start TDD with fixed candidate/input: a setter test must fail for the intended visibility reason and the read contrast must exercise the public getter path. Trace declaration visibility/selected place permission through normal module resolution and actual run/partreject consumer; independent review checks discrimination and registration. Applicable gates belong to the later repair. Audit does not edit tests/compiler/runners or require this repair to finish before audit closure. No phase3/main/seed completion implied.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 57.

Row57: Use admitted public factory and mutable caller to isolate permission. Preserve internal writes/ordinary public field and existing valid tests; no full visibility matrix or compiler bug claim. com-ji3e exact two-module external pub(get) read-success/write-rejection detector is required for selected field permission and writable-place admission. Same-module and factory publication controls cannot detect this boundary. Required admission: met-ucze, met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
