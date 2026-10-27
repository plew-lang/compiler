---
id: met-2wca
status: open
deps: []
links: []
created: 2026-10-27T20:42:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Plan adopted Optional payload labels for selected Chain and array regressions


## Contract and Finite Scope

Source-only admission audit at compiler9665094d/spec5bd65a5: `tests/fixtures/part/namespace_chain_identity/{Main,First,Second,Noise}.pw` protects nominal Chain identity, permuted binder positions, equal concrete arguments and empty behavior. First/Second.chain construct Optional.Some using `v=`; spec05 declares Some(value:T). Current std/Lang57-60 defines Some(v:T), and Core's Optional Chain implementation527-531 constructs v=. The Chain requirement names themselves match the adopted contract. This fixture has current-public-API grounds, not fully adopted payload-label admission.

## Deliverables

Recover the original Chain identity regression and enumerate exactly this root's Optional producers plus the defining Lang Some declaration and Core Optional Chain producer. Plan the label handoff from canonical declaration through construction/pattern/member checks and the compiler's structural Optional consumer, keeping the four existing results and nominal/binder/empty controls. Distinguish payload-label migration from autounique/allowunique capability work (met-b2la); do not silently extend that epic or require its whole implementation just to classify this existing copyable case. Check correctly labeled construction, wrong-label rejection and corresponding Some/None decomposition under a coherent fixed Std input.

## Completion

An explicit bounded migration/disposition with concrete owned repair if needed, preserving the current regression and adopted public signature. This audit neither changes source/Std/expectations nor adopts an alias label or new rule. Unread Optional/Result fixture obligations remain in the audit; this is not an all-Std rewrite. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-part-0003.json and its independent review.

## Explicit Three Array-Negative Producers

Batch0008 adds exactly tests/fixtures/reject/array_forward_context_block_conflict.pw, array_forward_context_explicit_conflict.pw, and array_forward_context_none_first.pw, with their .err companions. All root-authored Some constructors use current `v=` rather than adopted `value=`. The first two must fail for incompatible I64/U64 element context, not merely wrong label yielding a generic type-mismatch message. The third must preserve the leading unbound None forward-inference rejection; its later Some label still needs a coherent public-API migration.

Include these exact three roots with the existing namespace_chain_identity root, not every unread Optional/Result fixture. Preserve direct/block equivalence, explicit type mismatch and no later-element backward inference. No new label alias, capability feature prerequisite or source/expectation change is adopted by audit.

## Explicit Two Chain-Negative Producers

Batch0010 adds exactly tests/fixtures/reject/chain_missing_factory.pw with .err and chain_value_type_mismatch.pw (no companion). Both explicitly construct Optional.Some(v=...) against the current Std signature. Preserve missing empty() conformance versus continuation Value/result mismatch and the original source-anchor purpose as separate reasons; migrating labels is not proof those checks ran. The selected scope is now the original part Chain root plus five standalone negative roots, not the entire Optional corpus.
