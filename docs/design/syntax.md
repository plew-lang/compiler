# Syntax and Semantic Input

**Status:** Reviewed draft. This chapter defines syntax representation and its translation boundary. It does not adopt an additional typed IR or certify complete removal of legacy parser helpers.

## 1. Responsibility

The shared `@Plew/Syntax` package owns lexical and grammatical interpretation. The compiler loader uses that grammar to discover structural directives; semantic lowering translates the resulting syntax into compiler input. Lookup and checking own declaration binding, type formation, applicability, conversions, and source completion meaning.

The purpose of this boundary is to make a syntax change traceable: update one grammar, preserve the information needed for semantic checking, and connect the resulting operation to its ordinary consumers. A special parser or syntax-shaped checker in a later stage is not an alternative route to meaning.

## 2. Shared Grammar, Distinct API Results

The compiler-facing representation is `SyntaxFile`: private flat pools addressed by typed node IDs and typed ranges. Nodes hold scalar fields and child references rather than recursively owned copies of complete value trees. File roots are distinct from the pool of all top-level nodes.

Direct parsing constructs those rows. A completed parse publishes a read-only graph for normal traversal. A loader may append the next file through the designated construction entry, retaining the precise root range for each file; this does not grant semantic consumers arbitrary node mutation. Every reader must retain the correct store/session context.

Macro-facing APIs may return value ASTs. Their result shape is an explicit API boundary, not the compiler's internal traversal format. The intended grammar authority is the direct parser, with materialization adapting its nodes into value ASTs. Compiler passes must not repeatedly materialize whole value trees or store them secretly in persistent rows.

Node ID zero denotes absence where the representation permits it. A required child cannot become valid merely because zero is convenient. Ranges must identify the correct typed pool and a contiguous, in-bounds sequence. During recursive construction, a parent's final ID cannot be assumed to have been allocated before its children. Variable-length child lists must be assembled so their published range remains contiguous despite nested appends.

This is a cost and ownership choice. It avoids recursive value-tree retain/drop and copying during ordinary traversal; it does not guarantee that every scalar read or CoW operation is free. Representation validation covers roots, child kinds, ranges, optional IDs, and source coordinates independently of language-level checking.

## 3. Information Preserved at the Handoff

| Syntax information | Semantic input must retain | Decision deferred to its owner |
|---|---|---|
| Names and qualified segments | Spelling/provenance, segment order, each segment's arguments and labels | Namespace/type/projection/variant interpretation and declaration identity |
| Call arguments and parameters | Explicit order, labels, passing modes, annotations, defaults and their origins | Candidate applicability, selected signature, omitted argument elaboration |
| Construction and literals | Written form, members/entries, annotations and omitted context | Expected-type completion and full type compatibility |
| Blocks and branches | Ordered statements, branch structure, lexical exits and source requirements | Value availability, completion classification, type merging and ownership |
| Patterns and conditions | Pattern form, binding mutability, condition origin and scope | Binding types, exhaustiveness and allowed control targets |
| Generated operations | Originating source operation and explicit synthesis kind | Required protocol selection, evidence, validity and final lowering |

Source spans refer to the original admitted text. Interned spelling can be shared or copied without turning its new storage offset into the operation's source location. If a current API uses a source offset to recover module membership, lowering must preserve the original offset until that dependency is replaced by explicit provenance. Synthetic names or appended text are not a substitute for source ownership.

Semantic input is not a checked artifact. An annotation or contextual hint is a request to check under a type, not proof that the resulting expression has that type. If lowering carries a hint to an omitted construction or closure annotation, checking must validate and publish the completed result. Backend consumers must not infer success from syntax fields that happen to be filled.

## 4. Normalization Without Competing Meaning

Normalization may remove syntactic distinctions only if later consumers do not need them for meaning, evaluation order, control targets, or diagnostics. The operation's children and provenance must survive until the responsible semantic stage consumes them.

Three cases make the boundary concrete:

- A guard failure block carries its guard origin through syntax/materialization into semantic input. The common completion analysis checks its required exit. Lowering must not decide this by asking whether its last statement looks like a return.
- A binding while-condition may normalize into an if-chain shape, but retains that it was a loop condition. Control checking can then exclude the outer loop target while evaluating the condition, without excluding a new loop created inside that condition. Closure bodies establish separate control boundaries.
- String interpolation can normalize to an ordinary value block and generated writes. The displayed expression and options retain source order and source identity. Semantic checking decides whether they produce values and which protocol applies; Mid owns evaluation and cleanup. Lowering must not synthesize an executable formatting call for a path that never produces the required value. This does not excuse static checking of source expressions in a requested body, including unreachable source.

The [control-flow specification](https://github.com/plew-lang/spec/blob/main/spec/03-expressions/11-control-flow.md) governs `give`, return, divergence, and source versus analyzed reachability. Parser metadata records relevant syntax and origin; it is not a second completion algorithm. The body-checking chapter owns the shared semantic result, and Mid consumes it when constructing control flow.

Implicit calls introduced by syntax must carry a recognized operation kind and use the ordinary checking/evidence pipeline. They do not become user-written name references that require a new use directive at the call site, nor may they resolve arbitrary same-named helpers by spelling. Conversely, explicit source trait names retain their normal visibility requirements.

## 5. Diagnostics and Failed Parses

Parser failures retain the original location and syntactic cause. Any recovered nodes or placeholders remain distinguishable from successful input; they cannot authorize semantic publication or native execution. Whether a tool continues to collect diagnostics is separate from whether the compiler accepts the body.

Materializing a macro AST must preserve the documented coordinate convention and node content. Parsing a derive target does not require type-checking the target's implementation merely to construct its syntax. Generated text later enters ordinary source admission and checking, as described in [Sources, Packages, and Modules](sources-and-modules.md).

This chapter does not promise lossless trivia, arbitrary error recovery for editors, or stable serialized node IDs. Those would require explicit tooling contracts. Original diagnostic provenance is required even when the chosen internal syntax representation omits comments or delimiters that are irrelevant to compilation.

## 6. Example and Change Impact

For a new contextual construction form, the parser records the written fields and omitted type position. Lowering preserves that omission and its source owner. Checking supplies only the context legitimately available at that point, validates every field and the whole constructed type, and publishes the result. Wrapping the expression in a value block must not create a second construction resolver in Mid or backend code.

For a new control-flow sugar, list which lexical target and source requirements survive normalization before choosing its lowered shape. For a new qualified-name segment, extend the syntax/materializer/lowering handoff without having the parser guess whether the segment denotes a type or namespace. For a macro value API change, test its adapter separately from compiler traversal so a convenience API does not become a performance dependency of every compilation.

Validation must cover direct parsing and macro materialization of the same grammar, nested-child range construction, original coordinates, malformed input, and preservation of semantic metadata through normalization. Semantic tests must compare direct and wrapped expressions under the same context, including escaping paths. Structural tests alone cannot prove type inference or control behavior.

## 7. Comparisons and Rationale

[Rust's AST-to-HIR lowering](https://rustc-dev-guide.rust-lang.org/hir/lowering.html) normalizes syntax while tracking owners and assigning identities to synthesized nodes. Its [HIR account](https://rustc-dev-guide.rust-lang.org/hir.html) explains out-of-line item/body storage and distinct definition/node identities. Plew uses these as responsibility references, not a requirement to copy HIR or Rust's ordering of expansion, resolution, and lowering. Plew's semantic input must preserve whichever decisions remain legitimately deferred.

[SwiftSyntax](https://github.com/swiftlang/swift-syntax) provides a source-accurate syntax tree supporting macro inputs and generated syntax. The relevant similarity is a shared syntax vocabulary serving tools and compilation. Plew does not infer from it that its compiler needs lossless trivia or recursively owned value AST traversal. Its compiler-facing arena and explicit macro value adapter serve different consumption needs while sharing grammar.

## 8. Implementation Mapping and Audit Limits

Compiler source base inspected: `6fe09bc7c0e75260b3f773643921478b5020b94f`. Focused reading covered [Loader](../../src/Loader.pw), [semantic lowering entry](../../src/Codegen/Lower.pw), [condition/block lowering](../../src/Codegen/Lower/Match.pw), and [interpolation lowering](../../src/Codegen/Lower/String.pw). Some introductory comments still describe older parser/provenance arrangements; comments alone are not evidence of the current route.

At the pinned Syntax revision `00f740e1178e5b992cfdd30ddaa5a0612ce27b43`, inspected public entries `parseProgramSyntaxInto`, `parseProgramAst`, `parseItem`, `parseExprAst`, and `parseBlockAst` use direct SyntaxFile construction; value entries materialize their result. This supports the shared-grammar handoff for those entries. It does not prove every legacy helper is unreachable or that every grammar form and adapter is equivalent.

Concrete handoff fields at these inspected revisions include `SyntaxNameSegment` spans and per-segment argument/label slices, separate root ranges from node pools, and parent IDs finalized after child append. Changes to these representations must trace direct construction, materialization, freeze, and compiler Lower together.

`SyntaxBlock`/`BlockAst.guardElseOffset` uses zero for an ordinary block and otherwise the guard failure source offset plus one. Materialization and freeze retain it; Lower records the block ID and original offset in `blockExitRequirements`, and Record checks normal completion through common `SourceCompletion`. The value is provenance, not a parser-side divergence verdict.

`SyntaxCondClause`/`CondClause.isWhileCondition` survives binding-while normalization, materialization, freeze, and translation into `ConditionClause`. Verify uses it to mask the outer loop target during condition evaluation. A nested loop body establishes its own target, while a closure establishes another control boundary. Bool-only while conditions use the same checking rule through `Stmt.While`. These field mappings describe selected inspected paths; they do not expand the audit to all grammar forms.

Unverified scope includes complete grammar/materializer coverage, all normalized control metadata, all source-offset ownership dependencies, and downstream consumption of every synthetic operation. No parser suite, compiler execution, or performance measurement was run for this chapter. [Local issue management](../issues/README.md) records retained follow-up work; these limits must not be read as a clean implementation audit.

Chapter review found no blocking design problem. The distinction between executable interpolation synthesis and required static source checking was clarified in response to review. The implementation limits above remain unchanged.

## Retained Follow-up Investigations

[shared grammar/materialization coverage](../issues/com-2p9p.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
