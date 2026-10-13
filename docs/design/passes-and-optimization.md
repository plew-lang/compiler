# Passes and Optimization

## Responsibility

Pass infrastructure owns traversal vocabulary, preparation entry points, execution order, and the validity boundary of derived analyses. Individual passes own their transfer functions, rewrite proofs, and diagnostics. Infrastructure must not become a second semantic selector or a universal interpreter of every analysis's effects.

The [Mid chapter](mid.md) owns representation and canonical publication. [Ownership, Access, and Lifetimes](ownership-and-access.md) owns mandatory ownership/access behavior. This chapter explains how those operations compose and how optional transformations preserve their contracts. LLVM's optimization pipeline is a later consumer, not a replacement for mandatory Mid checking.

## Mandatory Preparation and Optional Optimization

The production executable preparation path is explicit: instantiate, elaborate accesses, optionally optimize eligible copies, elaborate drops, and verify executable Mid. Entry and successful result types distinguish these stages. Low-level canonical IDs remain storage identities; obtaining an ID does not establish pass completion or permit manufacturing a stronger token.

Mandatory transformations discharge abstract operations needed for execution. Mandatory analyses enforce language/internal invariants. Optional optimization removes costs while preserving observable behavior and acceptance. Turning an optimization off must not disable mandatory checks, leave executable markers unresolved, or require a separate runtime meaning.

A stage-preserving optimization can produce a new body identity while retaining the stage's guarantees. Its implementation must prove those guarantees for the output; reusing the wrapper type is not proof. If a future optimization requires a weaker or different intermediate stage, its placement and restoration obligations must be designed explicitly rather than hidden inside a generic `optimize` hook.

Declaration ownership requests and execution preparation remain distinct entry paths. Declaration checking can validate symbolic obligations without a concrete executable instance. It must not be forced through machine-level instantiation merely to share a pass loop, nor can its result stand in for executable verification. Program-wide effects require their own closure/publication guarantee beyond body-local passes.

## Structural Traversal Has One Owner

The Ir module owns opcode recognition, required stage replacement, operand/place/destination enumeration, and CFG successor enumeration. Its well-formedness validation owns mandatory payload and pool/range checks. Indexed traversal assumes those checks have established the relevant bounds.

Traversal enumerates occurrences, not distinct arena IDs. Two instructions using the same operand row are two uses. Switch case order, repeated successors, and the otherwise edge remain observable to consumers of the enumeration; a set-based traversal must not silently replace the canonical occurrence sequence. Receiver and argument lanes are distinct. Aggregate elements and closure captures use their proper pools.

Structural roles do not establish semantic effects. A slot named destination can hold a Drop target rather than a definition. A projected write can use its root and index without defining the whole root. Each analysis interprets these roles under its own contract: ownership consumption, liveness, initialization, aliasing, and occurrence counting are different questions.

Unknown opcodes are never empty instructions. Mandatory consumers reject unsupported/invalid input. An optional optimization may conservatively return the unchanged input when a known instruction is outside its supported subset; this does not authorize downstream executable verification to accept an unknown instruction. Shared enumeration also does not automatically broaden an optimization's legal cases.

Adding an opcode therefore requires updating recognition/schema validation and the relevant structural roles first, then every applicable transfer function, rewrite, verifier, and emission consumer. A default branch that silently skips the new opcode defeats this boundary even if a source test still passes.

## Analysis Identity, Validity, and Failure

An analysis result belongs to the exact body snapshot, arena/session domain, stage, and any external semantic inputs it reads. Examples include destruction contracts used for profitability and interprocedural effects derived from a prepared-body graph. Equality of source function or block count is not sufficient cache identity.

Analyses reading only a fixed immutable input snapshot retain their validity while new snapshots are appended. Results that also depend on external contracts or graph state remain valid only while those inputs satisfy the same validity contract. That does not make an old result valid for the new output. A transformation either proves the specific result remains applicable, computes a corresponding output result, or requires recomputation. Sharing unchanged rows is not a blanket preservation claim: adding a use can invalidate use counts even when the original operand rows are unchanged.

Program-level analyses also depend on their graph domain. Adding bodies, call edges, destruction relationships, or new reachable effects can invalidate a previously closed summary. Body-local cache reuse cannot grant program-level execution permission. The state/computation and driver contracts govern request identity and publication; this chapter does not introduce persistent cross-session caches.

Failure and not-applicable results remain distinct. A failed mandatory pass publishes no successful stage token. An optional rewrite that finds no eligible candidate returns the input unchanged. An incomplete analysis, malformed range, or missing required semantic fact cannot be reported as a successful proof of no effects or no ownership obligation.

## Transformation Protocol and Cost

Canonical rewrites read fixed input rows and append changed rows/ranges into a new snapshot. No-op passes return the original handle without reconstructing a body. Scratch plans are pass-local and belong to that input; their indices are not global arena offsets or reusable plans for another instance.

When an expansion changes block/local numbering, the pass computes its plans and prefix/remapping tables from the fixed input once. Local creation, edge remapping, and operation emission share those tables. Appending output must not change the basis of the plan. Access elaboration uses this protocol for the evaluation DAG, getter/parent/setter expansion, and reverse writeback sequence.

Read-only analyses accept the smallest domain they need. Ownership dataflow can consume the canonical arena rather than retaining unrelated mutable frontend state. Indexed traversal avoids creating owned arrays merely to list operands or successors. These choices reduce ARC/CoW overhead without compiler-specific ownership exemptions.

Dataflow converges by its declared state domain and transfer/join rules. Packed physical states may reduce storage/copy cost but cannot alter the lattice or collapse uninitialized, consumed, inaccessible, and uncertain meanings. Worklists handle recursive edges; a recursion guard or iteration cap must report a failure when it prevents a required answer, not publish a guessed fixed point.

An analysis may reuse an earlier fixed point when its input graph and transfer behavior are unchanged. When drop planning adds consume effects, the final state must incorporate those effects as described in the ownership chapter. Avoiding a repeated scan is legitimate only under that preservation argument.

## Ownership-Aware Copy Optimization

The adopted local optimization replaces eligible Copy operations with ownership transfer where the source is an unnamed, independently owned temporary with one definition and one use. It supports identity return transfer and an immediately following source ScopeExit transfer. It is not general CFG copy propagation.

Eligibility counts occurrences across the complete body, including unreachable blocks, address-taking, projections, and captures. Source and destination types/roles must match the operation's proof. Named locals, unique values, parameters, borrowed/inout storage, capture cells, and relevant special locals are excluded. Scope transfer additionally requires that the source obligation ends at that immediate boundary while the destination survives it. A different binding-end marker is not permission to consume either participating owner.

The rewrite preserves result-boundary provenance and cleanup markers so ordinary drop elaboration and verification see the transfer. It cannot cross intervening user effects or CFG edges merely because a copy appears redundant. In particular, reducing reference counts must not advance the last owner's user-visible destruction.

Profitability is separate from legality. A frozen destruction classification can avoid building a new snapshot for release-free values where the scope-transfer rewrite has no relevant benefit. Missing/unready cost facts are conservative and never establish release freedom. Cost information cannot relax single-use, lifetime, or ownership proofs.

The backend's omission of physical no-op destruction is a different optimization boundary: Mid obligations and verification remain intact, and any required ambient check remains conditional on the actual cleanup path. Neither optimization is implemented by deleting arbitrary LLVM retain/release pairs without preserving their source ownership contract.

## Verification and Diagnostics

Structural validation guards intermediate boundaries appropriate to their stage. Executable verification always runs before LLVM lowering; optimization settings do not suppress it. Additional debug checking can inspect every intermediate snapshot but does not create a weaker release-mode validity rule.

For a new pass, define input stage, required facts/analyses, output stage, changed identities, preserved results, unsupported cases, and failure reporting. Tests should include valid controls and malformed IR for the relevant production checker, not only a dump that resembles the intended output.

Optional transformations need both enabled/disabled behavior comparisons and checks of their intended structural effect. Performance measurements answer whether a legal transformation pays for its analysis and snapshot cost; fewer copies alone do not establish faster compilation or execution. Comparisons must hold source and compiler generation conditions fixed. Measurement operations/baselines remain outside this architectural reference.

Pass diagnostics preserve body identity, failing stage, and source/operation provenance where available. Dumps must identify the snapshot/stage they represent. A successfully registered body or a progress counter is not an executable-admission certificate.

## Comparative Rationale

[Rust MIR passes](https://rustc-dev-guide.rust-lang.org/mir/passes.html) distinguish preparation products and transform bodies through explicit passes. Its [visitor/traversal infrastructure](https://rustc-dev-guide.rust-lang.org/mir/visitor.html) centralizes structural walking while clients provide their behavior. Plew adopts the separation, using indexed scalar-pool queries rather than requiring Rust's visitor APIs or in-place mutation model.

[Swift's optimizer design](https://github.com/swiftlang/swift/blob/main/docs/OptimizerDesign.md) distinguishes optimization of language-level information from later LLVM work and describes analysis invalidation by changes to instructions, calls, and branches. Plew likewise places ownership-sensitive transformations before loss of semantic information. The Swift document contains explicitly provisional scheduling details; those are not adopted Plew rules.

[LLVM's new pass manager](https://llvm.org/docs/NewPassManager.html) makes analysis preservation/invalidation explicit. Plew needs that correctness property, but an LLVM-style extensible manager is not required for the current small typed preparation chain. Immutable body identities provide a natural validity boundary; explicit dependencies remain necessary for external semantic inputs and whole-program graphs. Reconsider a general manager when multiple pipelines or pass combinations make the explicit chain harder to maintain, not merely because other compilers have one.

## Implementation Audit and Open Scope

Focused source inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: `src/Mid/Prepare.pw` for typed admission and pass order; `src/Mid/Ir/Structure.pw` for indexed structural roles and opcode recognition; `src/Mid/Optimize.pw` for occurrence counting and local transfer eligibility; and `src/Mid/DataflowState.pw` for packed value-state representation. Existing canonical pass contracts also describe Access's fixed expansion plans and domain-limited analysis inputs.

One specific audit boundary remains: the return-transfer helper does not explicitly check uniqueness or a finalized destruction contract, unlike the scope-transfer helper’s local uniqueness guard. Because executable UniqueCopy rejection is later, this inspection does not establish that an invalid unique Copy cannot be transformed into Move first. The adopted exclusion above remains required; input validation or an explicit eligibility guard must close this boundary before claiming malformed-input preservation.

This is not a complete audit of all transfer functions, visitor users, cache keys, or malformed-IR defenses. No universal pass manager or preservation API is asserted to exist. General copy propagation, broader ARC optimization, and a new SSA layer remain possible future proposals, not completion requirements or implemented guarantees. Cross-stage and program-level cache validity must be checked as their detailed driver/runtime consumers are documented.
