# Maintaining the Compiler Design Reference

## Purpose and Authority

The [reference purpose](README.md) governs both writing and review: expose responsibilities and decision ownership so a contributor can locate a change, understand its consumers, and finish the corresponding change without duplicating authority. Document the architecture Plew should implement, not merely the arrangement most convenient for the current source tree. Identify a compromise, its intended endpoint, and removal conditions instead of presenting the compromise as that endpoint.

The [language specification](https://github.com/plew-lang/spec/blob/main/SPEC.md) owns program meaning. This reference owns compiler responsibilities, representations, boundaries, invariants and their rationale. Neither an implementation accident nor an unapproved proposal changes the specification or an adopted design contract.

Keep the design in the compiler repository. Code and contract updates can then share a commit and checkout; a separate design repository would add revision/synchronization and working-context costs. This placement does not make the implementation authoritative over design. Reconsider separation if an independently distributed design or multiple compiler implementations give it a concrete benefit. Meta retains development operations, validation baselines, current work and evidence; it does not own a second compiler design.

## One Contract, One Home

| Record | Owns |
|---|---|
| Language specification | Meaning, accepted/rejected source forms and language guarantees |
| Reference chapter or detailed supplement | Adopted responsibility, representation, boundary contract and rationale |
| Active proposal | A comparison that is too difficult to review through conversation and the reference diff alone |
| Decision note | A concise adopted/rejected judgment, tradeoffs and reconsideration conditions |
| [Local issue](../issues/README.md) | An implementation gap, bounded investigation, unresolved design work or optional improvement |
| Meta worklog and validation documents | Current work, stopping conditions, selected artifacts and validation baselines |
| Source-local contract | Concrete type/API/operation preconditions and guarantees, connected to the owning design |

An overview can introduce a contract and link its owner. A supplement can refine operation details without establishing a competing authority. Do not leave the only current contract in a worklog, proposal or conversation. Do not copy changing issue status, priorities or performance baselines into chapters.

A design/implementation disagreement needs classification before action: an erroneous design requires reconsideration; a known migration gap remains an issue; an unrecorded implementation deviation needs evidence and a linked issue. Do not silently adopt the implementation or silently certify it by correcting prose.

## Writing a Chapter

Write the English reference directly. Use a short chapter brief only when it resolves a real writing question, and remove it after incorporation. Avoid a parallel reference made of chapter plans. Boundaries describe conceptual responsibilities, not mandatory source modules, a new IR, or a prescribed implementation order.

Cover the following questions where relevant; the headings and number of sections are flexible:

- What does this domain decide, and what must it leave to another domain?
- What are its inputs, prerequisites, authoritative state and published guarantees?
- Which identities, owners, mutation rights, lifetimes and environments must survive?
- What do consumers receive, and which decisions must they never repeat?
- How are construction, publication, failure, cycles and repeated requests distinguished?
- What are the units and costs of traversal, copying, storage, indexing and caching?
- Why was this design chosen, which meaningful alternatives were rejected, and when should they be reconsidered?
- How does a representative case reach its final consumer, and how is that contract verified?

A useful starting shape is:

```markdown
# Domain

## Responsibility and Boundaries
## Concepts, Representation and Ownership
## Processing and Handoff Contracts
## Invariants and Failure
## Representative End-to-End Path
## Rationale, Alternatives and Cost
## Implementation Mapping and Verification
```

Combine sections in small chapters, add domain-specific sections when needed, and omit irrelevant questions. Do not require empty boilerplate or unsupported declarations of correctness. Keep schedules, assignees and detailed migration work in issues. Link implementation details close to their contracts without reproducing every API or source file.

The template combines examples from [Rust MIR](https://rustc-dev-guide.rust-lang.org/mir/index.html), [Swift ownership](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md), [Go's compiler overview](https://github.com/golang/go/blob/master/src/cmd/compile/README.md), [Zig AIR](https://github.com/ziglang/zig/blob/master/src/Air.zig), and the rationale/alternatives questions in the [Go proposal template](https://github.com/golang/proposal/blob/master/design/TEMPLATE.md). It is a Plew writing convention, not a shared official template or an adoption of those projects' proposal processes.

## Evidence and Review

Separate the adopted contract, unresolved decisions and observed implementation. Each chapter names the inspected revision and actual scope, unverified scope, and related issues. A missing issue does not prove coverage. Do not turn every uninspected combination into a mandatory defect; create investigation issues for concrete work worth tracking and link them back to the owning chapter.

An unimplemented adopted contract belongs in the reference with its implementation gap recorded. Do not add that guarantee to source comments as if implemented. After implementation, keep concrete API/operation contracts close to source and the architectural boundary in the reference.

Review each completed chapter with a third-party agent. Review responsibility ownership, source-to-final-consumer continuity, specification consistency, reference-language comparisons and implementation-evidence limits. A review of prose or a focused source inspection is not a compiler test gate. Record the corrected decision in its authoritative home rather than retaining a separate chronological review ledger.

Use representative cross-domain paths and a small previously unexplained change to test the reference: can the reader locate the decision owner, affected consumers, invariants and required verification without first reconstructing the source implementation? Existence of all chapter files is insufficient.

## Adopting and Changing Design

During preparation of the first edition, refine the reference with the user without requiring separate proposal documents. Preserve the distinction between discussion and adoption. Language changes and consequential architecture decisions still require the project's existing user decision process.

After the first edition, decide with the user whether a separate proposal improves review. Cross-domain influence or a changed responsibility alone does not require one. Use a proposal when alternatives, impact or migration are difficult to follow through the reference diff and discussion. Correct prose directly; review behavior-preserving internal cleanup with normal implementation work.

Active proposals use descriptive filenames under `proposals/` when needed; no numbering, review board, waiting period or new adoption ledger is required. Distinguish under discussion, under review, adopted and declined. On adoption, update the relevant reference and specification if meaning changes. Adoption does not mean implementation completion.

## Retaining Decisions and Gaps

Retain rejected alternatives so they are searchable and can be reconsidered when assumptions change. Usually a few lines in the owning chapter or a themed decision note suffice: alternative, reason/tradeoff, and reconsideration condition. Use a separate descriptive file for a complex judgment. Rejection is not a permanent prohibition.

Keep rationale needed to understand the current design in its owner and link it from decision notes. Completed proposal text, chronological debate and verbatim reviews belong in Git history. Keep only active proposals in the working tree. Do not introduce an ADR for every edit.

Use the pinned `tk` and Markdown store described in [Local Compiler Issues](../issues/README.md). Its operations, metadata, priorities, integrity limits and closure rules have that single home. The choice keeps issues searchable/editable with code in Git, without a database, daemon, separate repository or synchronization service. The tool's implementation language is not a correctness or maturity guarantee.

An implementation issue closes only after the contract holds from producer to final consumer, replaced authorities and temporary paths are removed, applicable correctness/performance gates pass, and design/source contracts agree. A saved table or added verifier alone is insufficient. Investigation can close with findings and follow-up issues without claiming a fix. Keep closed files and their stable IDs; retain the reason, revision, scope and decisive evidence. Closure certifies only the stated outcome and scope.

## First Edition and Implementation Restart

The first edition is a design milestone confirmed with the user, separate from compiler completion or authorization to resume a paused implementation. Cover the main responsibilities and their consistent boundaries, retain necessary prior contracts/rationale/open work, and complete chapter and cross-chapter review. It does not require every detailed API or every language combination to be implemented or designed.

Before resuming paused implementation, meet its existing detailed-design and restart conditions. A sentence locating the work in the architecture is not a substitute for concrete storage/API choices, failure/cost reasoning, affected consumers and verification criteria. Current candidates and validation evidence remain in the worklog/evidence records rather than this maintenance policy.
