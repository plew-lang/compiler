---
id: com-2p9p
status: open
deps: [met-u3lg]
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, verification]
---
# Audit shared grammar closure across arena and value AST paths

The direct compiler arena and macro value-AST parser paths must share grammar decisions. Design: [Syntax](../design/syntax.md). This retained boundary is not evidence that either consumer already covers every construct; discarded Plew.g4 status does not describe the current parser.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Inspect shared parse producers and both consumer representations, compare supported syntax/errors with paired fixtures, and close divergences without a second grammar authority.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Current arena/value-AST parse entry points for admitted block/if/match/interpolation/pattern/function forms and paired malformed inputs. Verify one grammar authority, spans and any reachable legacy parser; new absent syntax is outside. Matching current paths may close with evidence, without deleting private unused helpers merely for style.

## Explicit Trait Accessor Unknown-Token Setup

Batch0074 adds exactly run/syntax_file_trait_children_accessors.pw/.out. Original b60ef527 accessor positive and02c52198 print-order change retain embedded type Item; fn next despite spec01 newline/no-semicolon rule. At Syntax8c892042 lex561–980 maps semicolon to Unknown and parseSyntaxTraitDecl5135–5232 falls through to p.advance without p.fail. Fixture never asserts hasErr; no actual error flag was observed. Reconcile this finite positive setup/unknown-token diagnosis through the shared grammar authority, preserving binder/supertrait/associated/signature accessor purpose in adopted grammatical input or explicitly bounded current parser lane. It is not an intentional diagnosed recovery test or new semicolon permission. Include existing struct_field_semicolon/semicolon_separator rejects as static contrasts, not all grammar/error-recovery combinations or completed audit.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 75.

Row75: Preserve14 metadata outputs/spans/binders/associated/signatures and valid grammar. No semicolon permission, measured hasErr flag or all-error-recovery matrix. Shared Syntax grammar/direct arena/value materialization are input admission. Exact trait accessor positive semicolon/Unknown-token setup and absent hasErr assertion need existing finite shared-authority reconciliation. Required admission: com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Test Admission Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) installs required finite repair/investigation prerequisites at this actual admission: met-u3lg (row79). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
