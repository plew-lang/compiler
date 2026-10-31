---
id: com-vy62
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, driver]
---
# Audit metaprogramming isolation and generated-source freshness

Retained boundaries: isolation of multiple provider Syntax versions, host dependency separation, stale generated-part detection and authoring support. String runner exchange and host/target responsibilities are adopted; version isolation/freshness must not be inferred merely from successful generation. Current chapter audit is focused and does not prove full implementation.

Design: [metaprogramming](../design/metaprogramming.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Compare current producers and final consumers with the package/metaprogramming specs, record evidenced gaps separately from uninspected cases, and close each selected isolation/freshness contract end to end.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

Frontend.pw's generated-sibling admission uses sawDirective plus file existence;
when the required sibling is absent that branch does not diagnose or enqueue it.
There is no recorded-input receipt check in this admission route. Native tool.cpp's
gen path builds one harness per requested file, stages its stdout and renames one
.gen.pw; successful output staging is already present, but does not produce the
adopted portable recorded-input validation evidence or isolate incompatible provider
graphs into logical host units before combined publication.

Codegen/Gen.pw::synthGenMain still constructs parseItem and derive calls itself and
chooses the bare type receiver when d.args.count()==0. This is different from the
library-owned deriveFromSource boundary and does not preserve the distinction
between a bare directive and explicitly empty parentheses by argument count alone.
The exact user-visible failures of missing/stale output and provider-version
combinations need fresh focused probes; the missing admission/handoff is source
confirmed. General arbitrary external file/environment freshness is deliberately
outside the adopted guarantee, not an implementation defect. Native package build
admission is separately [met-nm1w](met-nm1w.md).

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Mixed: split current subset**.

[met-8b8w](met-8b8w.md) owns current gen's directive-form/library handoff, compatible host units/private result framing and recorded-input receipt/admission through their final consumers. Its scope does not introduce new public macro declarations.

The new `macro X as ...` / `macrointerface` syntax, macro-role registration/visibility and standard-provider migration to that form remain unimplemented public-family work in this parent. Current Syntax has ordinary Derive/ParameterizedDerive traits and trait-based providers; completing their bounded handoff repair neither certifies that legacy role model as the final design nor closes this parent. When the public role family is implemented, it must use the same host/framing/admission contracts rather than a competing generator. Arbitrary provider I/O freshness and package-native execution remain outside the adopted current contract.

## Qualified Test Intake com-5azh Row80

[Exact scope and retained roles](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) route only the current required subset to met-8b8w. The original status and qualified future/optional/historical/duplicate disposition remain unchanged. This subset neither closes a mixed parent nor reopens a closed duplicate; follow the canonical repair above.
