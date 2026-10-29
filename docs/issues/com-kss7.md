---
id: com-kss7
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:18:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow LLVM floating-literal byte-normalizer inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/boundary-values-and-observation.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-boundary-values-and-observation.json), audited from source 9665094dcec8aa63ed20573b1306a0015058f595. Parent audit: [com-mmk9](com-mmk9.md). This follow-up is independent repair/investigation ownership, not a new completion requirement for com-jno0 or phase 3.

## Guarantee and Scope
Remove whole mutable Comp authority from floatText/floatTextLen; pass only immutable source bytes/range. Update the typed Mid floating-literal emission consumer without changing underscore removal, byte order, text length or source backing lifetime.

## Actions and Completion
Characterize empty/plain/separator-containing ranges and both helper results. Narrow the actual API, not a wrapper retaining full Comp. Update real consumers and remove the competing broad signatures. Check that no name/type/source-preparation/native state reaches these leaf normalizers; use TDD/refactor rules and independent review. Run only gates appropriate to the actual future change.

## Excluded
LLVM numeric parsing algorithms, language literal acceptance, other compiler interfaces and speculative performance work. No performance improvement is claimed by this audit.


