---
id: met-ksi4
status: open
deps: []
links: []
created: 2026-11-23T20:03:28Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, parser, diagnostics]
---
# Reject missing trait-body delimiters before semantic admission

The fixed0655 compiler accepts `trait Child: A, B {}` under --check. Spec08 requires `A + B`; design/syntax.md requires parser failures/recovery to remain errors. The preserved minimal Comma/Plus fixtures and executed records are in phase3-trait-header-delimiter-finding.json. This was found while correcting a newly authored diamond fixture; it is separate from inherited existential interface selection.

Inspect the shared @Plew/Syntax parseTrait required-opening-brace path and compiler syntax admission. The parser's non-LBrace branch currently does nothing and its trait body loop skips unknown header tokens, so a recovered/incomplete parent list can look successful. Fix the responsible parser diagnostic/admission boundary, retaining recoverable AST for tools if needed without accepting it as a complete program. Do not add a type-checker name scan or a comma-only special case. Survey the same required delimiter handling in closely related declaration headers and split any broader confirmed family into finite follow-ups.

TDD must assert Source rejection and original offending location for malformed comma/missing-brace headers, preserve valid + chains and legal whitespace/body syntax, and exercise check/AOT/ORC (never execute malformed code). Verify SDK parse-diagnostic transport as well as compiler status; keep fixed carrier and source hashes, scoped existing syntax controls, applicable final integration and independent review. Fixtures are isolated under tests/compiler/frontend/fixtures/RequiredTraitDelimiters pending this repair; promote accepted regression coverage into the ordinary runner when fixing. This is required by overall existing-feature alignment, not a blocker for met-ajht's corrected valid + input. No language change is proposed.
