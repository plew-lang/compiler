---
id: com-6zph
status: open
deps: []
links: []
created: 2026-10-25T10:39:43Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Seal source conversion evidence against post publication mutation


## Confirmed Review Finding

P2 finding T2 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** compiler-state success immutability; checked-body-storage private builder, UseConversionFact and read-only publication; parent criterion8.

**Actual:** A real source owner and retained reader succeed. Public conversion rows/maps are cleared; the owner still succeeds but its previously successful final conversion reader now fails. This is a reproduced structural writer escape, not a spontaneous ordinary-source miscompile claim.

**Source chain:** `src/Frontend.pw:355,2473-2510; Ir.pw:3721-3725; Codegen/Check/Obligations.pw:40-82; Codegen/Mono/Call.pw:2511-2525`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `types/conversion-postpublish.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Hide/move conversion backing behind owner-aware construction and successful immutable read admission, retaining stable shared proof identities and exact site/endpoints. Close raw writer escapes and consume the sealed evidence at real final readers. Preserve meaningful malformed-input controls without exposing production writers to pass tests.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
