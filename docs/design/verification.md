# Verification and Validation

**Status:** Reviewed draft. This chapter defines evidence and admission responsibilities. It does not certify full specification coverage or prescribe the current operational baseline.

## Responsibility

Verification checks that an artifact satisfies the invariants required by its next consumer. Validation gathers evidence that the compiler implements the language and architectural contracts across representative paths. Neither activity is a replacement for the authority that selects source meaning.

The purpose of this reference is to make changes and their consequences predictable. Therefore a change must identify the contract it affects, the producer and final consumer, the evidence that would expose a broken handoff, and the limits of that evidence. Passing a convenient test or adding another check is not sufficient if the authoritative fact never reaches its intended consumer.

Language acceptance comes from the specification and responsible semantic/mandatory-analysis stages. Optional optimization must preserve valid input; it cannot be the only reason ownership is safe. A verifier must not reselect a different overload, invent missing evidence, or normalize invalid input into accepted source meaning.

## Admission Guarantees by Boundary

| Boundary | Relevant guarantee | Not established by this guarantee |
|---|---|---|
| Syntax/admission | Well-formed admitted input, original provenance, consistent source/configuration identity | Type correctness or execution permission |
| Source checking | Selected meaning and complete source facts under the declared environment | Every concrete instance or physical ABI |
| Declaration ownership/access analysis | Its named static obligations and retained deferred dependencies | Complete concrete executable preparation |
| Instantiation | Concrete substitutions and evidence for the selected meaning | Validity of an unchecked generic declaration |
| Mid structure/stage verification | Defined rows, operands/targets/types and stage-specific ownership/access obligations | Whole-program effect closure or native linking |
| Startup plan | Closed global may-access dependencies, noncyclic initializer graph and readiness before body entry | General I/O/lock/channel progress or public callback eligibility |
| Prepared execution scope | Required body and interprocedural dependencies closed for that scope | Whole-target check if unrelated bodies remain |
| LLVM verification | LLVM structural/type validity at the relevant transformation boundary | Plew value semantics, correct ABI choice, or source acceptance |
| Native publication/linking | Required symbols, target/ABI/resource contract, successful materialization/artifact | Correct program behavior for every input |

[Compiler state](compiler-state.md), [Mid](mid.md), [Ownership/Access](ownership-and-access.md), [Passes](passes-and-optimization.md), and [LLVM Backend](llvm-backend.md) define the actual contracts. This table is a reading map, not an independently maintained second schema.

A stage token records successful passage for an exact immutable artifact in its owner. A matching numeric ID, public canonical field, or wrapper name does not prove cross-arena validity or authorize mutation. A local body token cannot stand in for closed global effects, initializer requirements, or callable publication.

## Structural, Semantic, and Flow Checks

Structural checks validate row/pool bounds, tags, operand shape, target membership, and required metadata before consumers dereference them. Semantic consistency checks compare retained types, signatures, passing modes, conversions, and finalized ownership contracts. Flow analyses establish path-dependent availability, consumption, access extent, flag initialization, and cleanup obligations. These checks may share traversal infrastructure while retaining different guarantees.

Malformed unreachable IR can still violate structural/type contracts and must not be accepted merely because execution will not reach it. Conversely, runtime availability obligations use the relevant reachable control flow rather than pretending every dead path executes. Source reachability/error rules remain the checker's responsibility and cannot be replaced by CFG reachability.

Each new opcode or payload field must participate in common structural walking, its type/ownership/access classification, transformation remapping, and applicable verification. Unknown mandatory operations fail closed. An optional pass can leave known unsupported valid input unchanged; it must not silently drop an operation or weaken verification.

Verifier coverage must be evaluated against the producer schema and downstream assumptions. A verifier can share canonical accessors/walkers, but tests should not simply repeat the same buggy selection logic as their oracle. Positive constructed IR and deliberate corruption test different obligations. Include wrong-owner evidence, missing contracts, invalid target/type relationships, and mutations outside the current source parser's normal output when claiming malformed-input defense.

The unique-Copy input-preservation gap described in [Passes](passes-and-optimization.md) remains relevant: post-pass rejection alone does not prove that an optimizer cannot repair an invalid operation into an accepted one. Either establish valid pass input or guard the transformation's domain before claiming preservation of malformed-input rejection.

## Test Responsibilities

Tests are classified by their assertion, not by filename, directory prefix, or whether they import compiler modules. The [test layout](../../tests/README.md) owns actual discovery, companions, and suite membership. Operational run commands, adopted carriers, and integration gates remain in the project's operational documents rather than being copied as timeless design rules here.

- Language acceptance/rejection tests exercise public source rules, including diagnostics and status. Compiler crashes or timeouts do not satisfy an expected source rejection.
- Execution tests exercise output, side effects, evaluation order, destruction, and traps. A narrow stdout golden does not observe all those properties automatically.
- Internal contract tests exercise construction/publication/consumption and malformed artifacts at the owning boundary. They must not require exposing private helpers solely to preserve an accidental test dependency.
- IR/trace tests establish a chosen mechanism or transformation, with explicit raw/optimized stage and target assumptions. They do not replace semantic execution.
- Tooling tests validate runners, watchdogs, input recording, exit handling, fixture discovery, and instrumentation controls. A sound compiler result is unhelpful if a runner mistakes a crash or omitted case for success.

For architecture changes, include a path from the authoritative producer to the final consumer. A fact-reader test alone does not show that the backend uses the stored decision instead of redoing lookup. Useful comparisons include direct versus block-wrapped expressions, declared versus generic use, local versus imported overloads, source versus generated bodies, and AOT versus demand execution under equivalent inputs. These comparisons preserve Plew's own contextual/inference rules; they do not assume that all syntactically different contexts must infer identically.

Reuse inputs when they expose the same path, adding independent assertions where appropriate. Similar output is not proof that tests are redundant: ownership, failure, ABI, and compile modes can differ. Conversely, copied fixtures without a distinct failure mechanism add maintenance cost. Discovery and required companions must be explicit; missing expectations and silently skipped inputs cannot count as green coverage.

## Sanitizer Evidence

Memory instrumentation supplements static verification and semantic tests. Record which code was instrumented: compiler, generated application instructions, native bridge, runtime helpers, or a raw pre-optimization compiler. Instrumenting only a C runtime or bridge does not observe uninstrumented Plew LLVM loads/stores or nested JIT instructions.

The selected LLVM optimizer, instrumentation pass, link driver, and sanitizer runtime must be compatible. Runtime startup/toolchain failure is distinct from a detected Plew memory error. Detection controls, including an otherwise optimizable invalid access, establish that the chosen instrumentation route can observe the intended failure class.

Optimization can erase an invalid access before instrumentation, so raw pre-optimization ownership checks complement normal optimized tests. They cannot be replaced by disabling optimization everywhere or weakening the normal pipeline. Each profile reports its actual input set; partial ownership supplements are not the full corpus, and memory-safety evidence is not a proof of semantic equivalence or absence of all leaks.

## Specified Language-Level Tests

The [language test mechanism](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md#テスト)
is separate from the current fixture runner. Test blocks are declarations,
collected throughout the selected target independently of references, with
ordinary module visibility and no macro/name-based discovery. Production
linking excludes those declarations; ordinary code does not acquire a different
meaning in a test mode. Tests of non-public members belong to their defining
module, including its parts.

The expect family uses explicit expected/actual values and a failure channel
that lets the runner continue; production assert/panic retains its ordinary
termination behavior. [Implementation and remaining runner
protocols](../issues/com-8ec0.md) must not be inferred from fixture-suite success.
Newtype language regressions should define their own types and explicitly
exercise Self versus concrete positions; Std numeric API validation is a
separate assertion rather than an incidental dependency of those regressions.

## Self-Hosting and Performance

Self-hosting checks a specific compiler workload. A fixed point compares the compiler's LLVM and runtime outputs across generations under fixed inputs/toolchain/configuration. It is valuable evidence of reproducibility and bootstrap stability, not proof against a stable miscompilation or proof of whole-language correctness. Native artifact determinism is a different question from comparing raw compiler output.

The bounded measurement protocol starts from an explicitly identified carrier C0. C0 produces output O1, from which C1 is built; C1 produces O2. If O1 and O2 match, measure C1. Otherwise build C2 from O2 and compare its O3 with O2; measure C2 if they match, and fail if they do not. Each output includes both LLVM and runtime material. Repeated timing runs must reproduce the fixed-point outputs. Report which compiler produced the measured outputs, not the carrier's timing as if it were the stabilized compiler's performance.

A performance claim names the measured interval, source/std/dependency hashes, carrier and measured compiler, generations, optimizer/pipeline, runtime/native support, machine conditions, repetition count, and summary. Source-to-LLVM time is not end-to-end build/link time. Compare old/new compilers on the same source when attributing a regression; different sources, thermal conditions, instrumentation, or overlapping jobs can invalidate that inference. Reduced operation counts explain a mechanism but do not establish a net wall-time gain.

Current numerical thresholds and accepted carriers are operational state, not language or timeless architecture. Preserve reproducible summaries under version control; scratch artifacts and logs need not remain indefinitely. Do not promote a WIP compiler/seed merely because it compiled its own source once. Integration and seed promotion require the applicable full gates, not a narrower chapter test.

## Evidence Scope and Maintenance

An evidence record identifies exact revisions/inputs, command/configuration, tested scope, exit status, relevant artifacts, and limitations. A process still alive, a heartbeat, or an incomplete log is not a successful result. Inputs must remain fixed during a run; editing source while a test imports it invalidates that run's claim even if its executable stayed unchanged.

Separate adopted contracts, known implementation discrepancies, unverified areas, and completed validation. A source inspection can establish a particular call path or missing guard; it cannot prove all runtime behavior. Absence of a reported issue is not evidence of conformance. Completed issue records preserve their verification scope; they do not convert nearby unaudited paths into completed work.

For a documentation change, validate links, terms, authority boundaries, and source-backed claims; running all compiler suites does not substitute for that review. For an implementation change, select tests from the changed contract and broaden at the required integration boundary. Never weaken a verifier, test, sanitizer profile, or stop condition to make the evidence easier to obtain.

## Reference Designs and Rationale

[Rust compiletest](https://rustc-dev-guide.rust-lang.org/tests/compiletest.html) supports different compile/run success and failure modes. Plew similarly distinguishes assertion responsibilities without adopting Rust's full harness or treating an internal test as a language specification.

[Swift's testing guidance](https://github.com/swiftlang/swift/blob/main/docs/Testing.md) separates compiler/runtime/library tests and cautions against incidental platform assumptions in IR tests. Plew uses the same distinction between semantic regression and chosen physical mechanism; its smaller project does not need Swift's entire testing infrastructure.

[LLVM's testing guide](https://llvm.org/docs/TestingGuide.html) distinguishes unit, regression, and broader program tests. LLVM verifier/regression success remains evidence within LLVM's domain; Plew must separately validate source semantics, ownership, and ABI handoffs. These references inform coverage choices rather than mandate more test frameworks.

## Implementation Evidence and Open Boundaries

Focused source inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`:

- `Mid/Prepare.pw` admits parametric input without claiming validity, then instantiates, elaborates Access, optionally optimizes copies, elaborates Drop, and verifies executable Mid. Completion tokens are created through their stage operations, and the executable verifier registers global-access information; interprocedural closure remains a separate responsibility.
- `Mid/Verify.pw` shares a stage-sensitive walk. Declaration ownership verification explicitly excludes conversion eligibility, Access elaboration, and whole-body semantic success. Executable checks include type consistency in unreachable blocks while ownership dataflow follows reachable paths. This is selected-path inspection, not a completeness proof for every opcode/field.
- `tests/README.md` distinguishes normal/gen/deps/sanitizer coverage, manual native diagnostics, input companions, and ASan A–E scopes. Native ORC bridge probes explicitly do not instrument nested generated JIT instructions.
- `scripts/diagnostics/measure-self-host.py` compares LLVM/runtime hashes across up to three generations, identifies the compiler used at the matching comparison, requires repeated runs, and rejects changed measured outputs. Bootstrap uses raw LLVM/runtime comparison under its own workflow. Their complete watchdog, hashing, and failure behavior is not audited by these selected reads.

No compiler/test/performance execution was performed for this chapter. Existing accepted validation records belong to their recorded revisions and do not certify the current design's full implementation. Schema-wide verifier coverage, every runner/discovery path, cross-mode semantic coverage, and all chapter contracts still require explicit evidence before implementation-complete claims.
