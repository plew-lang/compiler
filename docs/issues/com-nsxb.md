---
id: com-nsxb
status: in_progress
deps: []
links: []
created: 2026-10-21T12:58:26Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Audit adopted design contracts through implementation consumers

## Scope and Pinned Inputs

Detailed read-only design/implementation audit requested after closing the
canonical design review. Design/source input: compiler `78bd96912aacb39ee2601e95a877c33e0b556ac7`;
spec `1e0c4d08777edc521e0e64f42588d4996b1c66d8`; Syntax pin
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Preserve the dirty compiler binary and
untracked Python caches; neither supplies execution evidence.

[met-z0ro](met-z0ro.md) is the representative-domain inventory, not this audit's
completion evidence. Reuse its owning tasks, but recheck source and saved-result
consumers rather than copying its conclusions.

## Method and Completion Boundary

For each adopted boundary record the contract, concrete producer/key, storage and
publication, substitution/consumer and failure/cleanup path. Distinguish a traced
conforming route, mismatch, absent family, partial closure, unverified combination
and intentionally deferred feature. A matching declaration or verifier alone is
not end-to-end evidence. Cite exact source symbols and the pinned revision.

Cover the 18 reference domains and storage/library/collection supplements. Dig
into source-to-final-reader closure, synthetic and global owners, proof/instance
identity, Mid stages, async ownership and driver/resource boundaries. Record
uninspected combinations explicitly; do not infer a newly reproduced runtime bug
from source-only architectural gaps. Existing tests may be read, not rerun.

Finish with owning follow-ups, dependency/order reasoning and a bounded coverage
statement. Do not repair compiler code, change language semantics, run compilation
or performance gates, promote carriers or enlarge met-si6j automatically.

## Audit Results

### A. Source Authority, Storage and Concrete Consumption

Contract owners: [body checking](../design/body-checking.md),
[checked storage](../design/checked-body-storage.md),
[types/evidence](../design/types-and-evidence.md) and [instantiation](../design/generics.md).

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Session-owned checking and execution | CheckedProgram.pw CompilerSession owns Comp, requests, templates and executionFailure; lowerBody passes prepareBodyAccess's program/ambient into lowerRequestedLlvm. No mutable Comp accessor is exported by that session. | Conforming scoped outer boundary; not certification of inner stores |
| One source construction authority | Resolve/Preparation.pw prepareLexicalBodyUncached performs Record(false), Generic, Verify, Record(true); global preparation performs record/verify/record. Record.pw selects static members and verification reads/rechecks selected signatures. | Partial; met-ucze. Unifying the helper alone would not remove repeated decision authority |
| Successful owner publication/failure | Resolve/Record.pw prepareLexicalBody and Resolve/Global.pw prepareGlobalInitializer save Result and restore Cursor; expression/binding/statement writers reject completed owners, including Failed. | Existing bounded protection; no new universal Active state is claimed or required for non-recursive local requests |
| Owner-local sealed backing | Frontend.pw preparedSemanticFacts checks the owner, then retains all-owner expression/aggregate/try/match/binding/statement arrays and global indexes; Mid/Build.pw state.sourceFacts and Mono/Call.pw preparedAccessUseFacts consume them. | Partial; met-acfl. CoW snapshots preserve an older view but are not the adopted per-owner payload/cost boundary |
| Source header sealing | Resolve/Record.pw recordSourceBodySignature validates types then replaces sourceBodySignatures[fnIdx]; it has no completed-owner guard. Frontend.pw preparedFunctionBodySignature and Mid/Build.pw buildParametricMidBody consume this table. | Missing structural write closure; met-acfl. No production post-success overwrite is reproduced |
| Provided-body provenance | Resolve/Expr.pw semanticBodyOwner checks lexicalOwnerFnId and shared body identity; Mono/Call.pw sourceFunctionOwner maps closure and global initializer owners explicitly. | Existing mechanism to preserve, not wholly absent provenance |
| Synthetic declaration provenance | Resolve/Module.pw moduleOf returns entry module for unregistered offsets; methodInEntryModule uses the first statement and returns false for empty bodies. | Partial; met-ucze/met-acfl. Cannot substitute for a header's explicit module/origin; no fresh visibility miscompile claimed |
| Value/Unit/no-normal-value and binding consumption | Frontend.pw PreparedSemanticFacts expression/binding/completion readers validate owner; Mid/Build.pw buildMidStmt and buildParametricMidBody require saved facts/signature; Mono/Call.pw preparedSourceExpression and requiredAccessExpression reject missing records. | Existing successful lanes. Header/record completeness and all optional-versus-required branches remain met-acfl; do not erase these migrations |
| Aggregate, pattern and try | Record.pw publishes selected semantic aggregates/matches; Mono/Call.pw preparedBodyAggregate/preparedBodyMatch/preparedBodyTry carry body+initializer owner; Mid/Build.pw builds operands and payloads from sourceFacts. Global composite Mid switches to each initializer's facts. | Existing lanes, physical seal/final-reader closure partial; met-acfl/met-6e6k |
| Generic environment identity | Mono/Call.pw sameInstanceEnvironment compares receiver, complete proof, declaration-bound evidence, ParamIds and argument types; findBodyInstance keys by declaration plus that environment. | Conforming inspected key. It is false that body identity currently ignores all proof/bound inputs |
| Simultaneous substitution | Mono/Ground.pw groundTermInEnvironment substitutes ParamId-bound replacements outside the callee map; a legacy bare-name fallback remains for unstamped terms. | Partial migration; met-ia09/met-6e6k. Preserve the correct simultaneous lane and remove fallback only with producer stamping |
| Call publication to consumption | resolveBodyCallee reads Direct/Dynamic/StaticMethod templates; recordSelectedBodyCallee retains signature/modes/conversions; requirementCallConstraintEvidence consumes a retained implementation plan; Mid/Instantiate materializeCanonicalMidCall reads final resolution IDs. | Existing lanes, not a universal reader-reselection defect. The StaticMethod default still uses CallableConstraintEvidence.Declaration; met-ia09 owns whether each synthetic/protocol lane closes its declaration evidence |
| Completion ownership | SourceCompletion.pw centrally composes source/execution edges; completionBlock consumes give and completionLoop keeps source continuation separate. Mid/Build lowers saved facts into scope exits/CFG. | Shared completion core exists; full expression-shape/control coverage remains met-si6j/com-gyup, not a new implementation of old give semantics |

File paths in this table are relative to src unless otherwise qualified. These
are source traces, not new passing tests or proof of every language combination.

### B. Mid, Ownership and Representation Boundaries

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Mandatory stage chain | Mid/Prepare.pw privately constructs instantiated/access/drop/executable tokens in order; Mid/Program.pw caches Result per body and requires a ready signature. Backend/Llvm/Mid.pw preflight reads executable input. | Conforming inspected preparation path; foreign-arena raw IDs still require admission discipline |
| Structural operation vocabulary | Mid/Ir/Structure.pw owns opcode recognition and occurrence/successor queries; Mid/Async.pw uses them rather than collecting AST locals. Unknown opcodes and parametric-only forms are rejected at stage boundaries. | Existing shared structure, not a missing visitor framework |
| Ownership/effect guarantee distinction | DeclarationProgram.pw CheckedDeclarationBody and Mid/OwnershipAnalysis.pw cache local verification; declaration graph retains unresolved calls/destruction; PreparedProgram/CheckedProgram close concrete global/ambient effects. | Existing distinct scopes; generic/dynamic effect combinations remain explicit, not silently certified by local tokens |
| Async activation ownership | Mid/Build.pw marks async input locals ownsAtEntry; Backend/Llvm/Async.pw genLlvmAsyncFunc retains Borrow arguments directly into frame slots and transfers Move; MidAsync completes source drops before Promise/frame release. | Partial; com-tn1m. No explicit common Mid activation-input acquisition plan exists; move decision out of backend without double acquisition |
| Async suspension/ready await | Mid/Async.pw includes Drop and borrowed-owner dependencies in liveness; Backend/Llvm/MidAsync.pw midAsyncSuspend branches done Promises directly to completion. | Existing lanes; do not claim all await operations reschedule |
| Async supported result family | Verify/Func.pw restricts payloads; Backend.pw PlewPromise value and MidAsync completion use i64; Async.pw rejects generic/method entries. | Partial; com-tn1m/met-b2la, separate from a reproduced ownership failure |
| By-value private ABI | Backend/Llvm/ValueAbi.pw maps logical types to omitted/direct/byval lanes; parameter binding and call emission consume those lanes. | Existing common ABI, no struct-size threshold asserted by this audit |
| C ABI conversion | Backend/Llvm/CAbi.pw centralizes F32 conversion, inout temporary/writeback, target narrow-integer extension; ValueAbi remains private. | Conforming scalar subset; aggregate/public-callback coverage remains com-042v/com-0oxy/com-qnyl |
| Optional return-copy transform | Mid/Optimize.pw returnTransferOperand lacks scopeTransferOperand's explicit isUnique exclusion, rewrites Copy to Move before final executable verification. Verify.pw rejects unique Copy at declaration/executable stages. | Confirmed eligibility omission; malformed-input acceptance still needs a controlled end-to-end case (com-wqd7). Authored declaration checking is a real earlier guard, not assumed absent |
| Buffer lifetime and failure | Backend/Llvm/Mid.pw Set commits new slot before old release; Clear/Truncate commit count before retired-range release; Remove* transfers its result. Arrays.pw cowArraySlot performs typed retains after shared backing separation. | Existing lanes. Reentrant retired-range traversal and dictionary/set invariants remain com-zgk9, not certified by commit order alone |
| Buffer capacity safety | std/Core.pw reserve -> Mid.pw plain count+additional -> Arrays.pw wrappers -> Backend.pw emitted allocation/grow/reserve. Addition/multiplication/growth and malloc-null have no checked failure boundary on this route. | Source-confirmed mismatch, new owning bug com-p10m; no runtime crash reproduced |

### Remaining Audit

Source/package admission, syntax/new capabilities, library/reference transport,
runtime/JIT/startup, native ownership/failure, diagnostics and verification coverage
are being traced before final classification and repair order are published.
