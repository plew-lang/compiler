---
id: com-cuoy
status: open
deps: []
links: [com-bvc8, com-0w38]
created: 2026-11-06T17:52:14Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, syntax, verification]
---
# Reject invalid type suffixes instead of manufacturing parameters

## Contract and Evidence

Follow spec04 function signatures, spec02 record type grammar, and design
Syntax and Semantic Input. [Executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/record-projection-investigation.json) at Syntax8c892042 shows
`fn inspect(value: (x: I64)#Projection.First) {}` parsed without error into five
parameters: value, #, Projection, ., First. File frontend accepts it; parameter0
is just a record. The same suffix in a newtype sets parser.hasErr. This is not
loss of an already parsed projection by lowering and does not demonstrate the
common projection-head comparison defect.

## Actions and Guarantees

Trace tokens -> record type parser -> parameter boundaries -> immutable Syntax
and value-AST adapters -> compiler source admission. Reject unsupported/malformed
suffix tokens at the owning grammar boundary; never reinterpret arbitrary
punctuation or a type suffix as additional parameters. Respect the specification's
actual separators and identifier/type requirements; do not introduce a new
record projection feature or a spelling-specific #Projection workaround.

Preserve legitimate declarations, labelled record parameters, generic and
nominal projections, function types and anonymous-function inference. Shared
parameter parsing must retain context-specific closure rules rather than banning
all omitted types. Preserve the original syntax diagnostic to the returning
frontend and CLI. Compiler consumers must not publish successful malformed
signatures after parser failure.

## TDD and Completion

Use the exact one-to-five-parameter RED, assert parser error and compiler Source
rejection rather than merely a changed parameter count. Include duplicated
suffix names (formerly a misleading duplicate-label diagnostic), a second
parameter, punctuation/unknown suffix contrasts and correct nominal projection /
record parameter / inferred closure controls. Retain the newtype error control.
Check direct immutable parser and reachable legacy/macro value-AST paths.

Implement through the pinned Syntax package's normal release/pin workflow if
needed; do not leave a local path override or fix only a compiler wrapper. Close
token-to-source-admission behavior with affected parser/compiler tests and
independent neutral review. Not a parser-wide audit or language syntax change.
Required phase-three acceptance is connected directly to met-si6j.
