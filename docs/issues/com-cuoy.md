---
id: com-cuoy
status: closed
deps: []
links: [com-bvc8, com-0w38, com-nudy]
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

## Verified implementation increment

Syntax e8aee7c (signed tag 0.1.11-dev.32) validates parameter boundaries,
name token shape and the annotation requirement shared by direct and legacy
parameter parsers. Anonymous-function parsing can supply contextual types;
existing word-shaped spellings, including the extern `val~:` spelling, are
preserved. The macro-facing AST materializes the direct parse and the tests
additionally drive the public legacy `parseFuncDecl` entry.

The fixed prior compiler and Syntax controls reproduced the false acceptance.
The tagged consumer passed the new Syntax regression and four adjacent
fixtures. The compiler built against that revision rejected the three CLI
fixtures in check/run/gen, plus a numeric name and unknown suffix, and
accepted the extern word-name control. The rebuilt compiler ran its own
source check. The independent reviewer confirmed both entry paths and
diagnostic ownership; name compatibility and the annotation omissions found
in review were addressed and rechecked. The discovered dotted-segment problem
is separately owned by [com-nudy](com-nudy.md).

Compiler 86a5c87c resolves the signed tag at its exact commit and carries the
reconstructed seed and CLI rejection controls.
[Fixed-point and bootstrap evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-parameter-pin-self-host.json).
Normal suite 20261117T091050-test-7de352 is pending; retain in-progress status
until its failures are accounted for.

## Normal Suite Reconciliation

The immutable-input normal run 20261117T091050-test-7de352 exercised the
exact-pin bootstrap binary and passed all three new parameter rejection
fixtures. Its 782 failure signatures are a strict subset of the 784 from
20261115T224510-test-d61556. The two removed failures are
conformance_source_selection_conditional and reject/conditional_conformance_view,
both corrected fixture cases. No new failure signature was found. This
closes the task's parser and compiler admission scope with the prior
independent review. It does not close the project's failing normal gate
or phase-three performance requirement.
