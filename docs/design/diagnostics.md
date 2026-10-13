# Diagnostics

**Status:** Draft for review. This chapter defines diagnostic responsibility and failure preservation, not a stable diagnostic serialization format or a general IDE recovery framework.

## Responsibility and Authority

A domain reports why its contract failed or why permitted code merits a warning. Parsing owns syntactic failure; checking owns source meaning and source acceptance; mandatory analyses own their validity findings; native consumers own target, linking, and execution failures. Diagnostics infrastructure represents, transports, and renders those findings. It must not independently infer types, select calls, classify flow, or decide whether execution is safe.

[Syntax](syntax.md) and [source admission](sources-and-modules.md) own original source identity and provenance. [Body checking](body-checking.md) owns source completion. [Session state](compiler-state.md) owns failed request retention. [Driver and execution](driver-and-execution.md) owns command presentation, exit status, and terminal execution policy. A diagnostic message is not a substitute for any of those contracts.

Changing wording or output destination must not change acceptance, required checking, or cached failure. Conversely, adding an acceptance rule belongs in its semantic owner, not in a renderer or a string-matching test harness.

## Finding, Failure, and Presentation

Three concepts remain distinct:

| Concept | Required information | Effect |
|---|---|---|
| Domain finding | Cause, responsible operation/owner, source or generated origin, relevant context | Explains a warning or failure under the owning rule |
| Request result | Success, justified deferred obligations, or failure for the exact inputs | Controls publication and subsequent consumers |
| Rendered diagnostic | Severity, location and explanatory text, plus any supported detail | Communicates the result; does not grant or revoke execution permission independently |

An error-severity record cannot be buffered while the same required request publishes success. A failed request must carry or retain its failure even if presentation is postponed or deduplicated. Draining a warning queue, displaying an error, or suppressing a duplicate is not recovery. Pending obligations, missing facts, compiler invariant failures, and legitimate not-applicable results cannot all be represented as an empty diagnostic list.

A returning compiler service propagates failure to its caller. Terminal compatibility adapters may remain only where callers still rely on termination; making such an adapter return without converting its callers would continue with invalid state. The adopted service boundary returns results and leaves process termination to the execution/CLI adapter. This is an architectural requirement, not a claim that all old terminal sites have migrated.

Diagnostic continuation can collect additional findings after an error without authorizing publication. It must retain owner failure separately from tentative type facts, and later requests must not reinterpret those tentative facts as accepted meaning. Continuation is not a fallback overload/type selector.

## Provenance and Lifetime

Diagnostics must remain meaningful after the constructing arena or temporary checking context is released. Either the diagnostic owns its necessary source identity/context or it holds an explicitly valid reference to an admitted immutable source owner. Raw body-local IDs or borrowed message pointers without that lifetime are insufficient.

Source locations refer to the original admitted file and coordinate space, not an interned spelling's storage offset or the concatenated arena's incidental position. Generated bodies retain their source origin and relevant instantiation/default/macro context through the owning representations. A generated name does not become a source anchor simply because its bytes exist in the arena.

Domain-to-diagnostic conversion preserves an existing specific source diagnostic rather than replacing it with a generic outer failure. When only an owner-level location is available, report that limitation honestly; do not fabricate a precise expression span. Unpositioned native/tool failures are legitimate when no source operation has been established as their cause.

The necessary information depends on the finding. A conflicting access needs the responsible access and its context; a missing bound needs the selected requirement/environment; a parser failure needs original syntax location. The adopted requirement is to preserve enough provenance to explain the cause. It does not require a universal large diagnostic object, serialized compiler proof, or a new cross-process schema for every finding.

## Severity, Reachability, and Recovery

Severity follows the language/domain rule. Required validity checks cannot be downgraded into warnings to obtain a build. Warning presentation cannot turn permitted code into a different semantic program. A user-configurable lint system, warning-as-error policy, stable codes, and fix-it API are separate features; this chapter does not silently adopt them.

Plew's [control-flow specification](https://github.com/plew-lang/spec/blob/main/spec/03-expressions/11-control-flow.md) distinguishes source-explicit escape/divergence from analytically unreachable code. Source completion determines the required error/warning classification. An optimizer discovering an unreachable CFG edge cannot retrospectively change the source's acceptance or expression value formation. The renderer must consume the classification rather than look for a final `give`/`return` or repeat reachability analysis.

Recovery placeholders remain distinguishable from valid syntax/types/evidence. Later consumers may use them to explain another error only under a defined continuation contract; they cannot authorize Mid/native publication. A typed internal error marker is possible implementation support, not an adopted user-visible Never/error type.

Source-program rejection, unsupported implementation facilities, malformed compiler IR, native/toolchain errors, and runtime traps retain distinct causes. Wording should identify an internal compiler failure when a required invariant is broken rather than blame a valid user program. Runtime panic/terminal lazy failure still follows its execution contract; constructing a compile diagnostic does not add unwinding or deinit guarantees.

## Repeated Requests and Ordering

Deduplication belongs to a defined diagnostic/request scope and preserves failure. Identity must distinguish unrelated owners or instances that happen to produce equal text or share a source line. Source-level warnings can be retained once for their immutable source node, while instance-dependent failures may need different context. No text-only global deduplication policy is adopted.

Within fixed inputs and an equivalent request scope, diagnostics should be reproducible enough to investigate and test. Demand execution may discover findings in a different order and may never request unrelated bodies; it need not emit the same complete list as whole-target check. Neither mode may change the rule applied to the same checked operation. Parallel traversal order or hash iteration must not silently become an acceptance rule.

Queue draining transfers presentation responsibility to the caller. If several layers render the same terminal result, duplicated messages can obscure the primary cause; adapters should define which layer emits queued warnings and which emits the returned failure. A failed native publication may have its own diagnostic after source warnings, but cannot convert the source result into success.

## Change Paths and Verification

For a new diagnostic, first identify the domain rule and authoritative result, then retain its location/context and transport it to the driver. For richer location display, change provenance and representation/rendering rather than searching source again in the renderer. For continuation changes, review failed-owner retention and every publication gate, not only the number of displayed messages.

Verification should cover acceptance/status as well as message content; original file-local locations after multi-file loading; direct versus synthesized origins; warning draining followed by repeated failed requests; duplicate requests; domain-conversion preservation; and returning service versus CLI termination. A golden string alone cannot prove that a failed request remains failed or that the final consumer refuses execution.

## Reference Designs and Rationale

[Rust's diagnostics guide](https://rustc-dev-guide.rust-lang.org/diagnostics.html) separates diagnostic structure, severity, spans, and presentation from the main checking path. Plew adopts the responsibility distinction without requiring Rust's localization, lint registry, error-code index, or suggestion machinery in this initial design.

Rust's [ErrorGuaranteed](https://rustc-dev-guide.rust-lang.org/diagnostics/error-guaranteed.html) records that an error was emitted. Plew's request failure must likewise remain explicit, but an output event alone is not its adopted execution-permission model. Buffering or draining diagnostics must not invalidate retained failure.

[Swift's diagnostic architecture](https://www.swift.org/blog/new-diagnostic-arch-overview/) describes using constraint-solving context and fixes to explain invalid code. Plew needs retained causes and context too, but does not adopt Swift's solver or hypothetical repair search. In particular, explanatory recovery cannot become a second successful interpretation of ambiguous source meaning.

## Implementation Evidence and Open Boundaries

Focused source inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`:

- `Diag.pw` defines owned severity/location/message records, a stderr renderer, and terminal compatibility adapters. Locations are unpositioned, line-only, or file/line; the representation does not provide general ranges, related-location chains, stable codes, or structured fixes.
- `Frontend.pw` retains pending diagnostics and source-owner diagnostic failures separately. `takeDiagnostics` drains the pending array. Selected `Codegen/Infer/Check.pw` paths retain owner failure during continuation and reject it at later owner checks; this is not an audit of every publication path.
- `Codegen/Emit.pw::diagnosticAt` maps source offsets through source-file ranges and counts file-local lines. Out-of-range synthetic offsets fall back to buffer-wide line counting. `fnAnchor` prefers original declaration offsets; `exprOffset` prefers retained spans and otherwise uses form/child fallbacks. Those fallbacks do not meet precise generated-origin provenance by themselves.
- Selected match/return checking queues deduplicated unreachable warnings using retained node identities. Declaration/Mid diagnostic conversion preserves embedded frontend diagnostics and maps selected ownership/access failures to user-facing messages; other errors use owner anchors or generic internal-failure reporting.
- Compiler/execution adapters drain queued diagnostics and emit returned failures. Native LLVM/tool messages also have direct stderr paths outside CompileDiagnostic. Their presence does not establish a unified structured diagnostic transport or returning API migration.

Full producer coverage, precise generated-origin chains, deduplication across all instances, every terminal call site, error recovery, and complete diagnostic ordering remain unaudited. The physical format for richer provenance is not fixed here. No compiler/test/performance run was performed for this documentation chapter.
