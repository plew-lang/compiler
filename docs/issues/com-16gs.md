---
id: com-16gs
status: closed
deps: []
links: []
created: 2026-10-24T20:09:24Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Verify canonical associated bounds in lowering fixture


## Boundary and Exit

Internal run fixture syntax_lower_associated_type_bounds aborts134 with assertion failed on both baseline090240dd and measured6ddf8f75; emitted LLVM is byte-identical. Identify the exact assertion and direct/legacy lowering path before changing expectations. Compare the adopted associated projection and lexical ParamId contracts. Preserve bound count/order, trait owner, canonical Self/ParamId predicates, positional arguments, offsets, and absence of monomorphization side effects. Do not assume the fixture is wrong from an undifferentiated assertion panic; split a valid-source implementation defect if found.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.

## Outcome

Resolved by fixture-only commits f1da1ddc and 8dc8e43e; production remains
b6645ac1. The original direct path fails its head-name assertion 20. The
canonical lowerLexicalAssociatedType producer instead stores
Self#Collection[T].Item. Both lowering paths now require a nonzero lexical Self
receiver, exact trait declaration owner and member, and complete positional
ParamId arguments. Existing count/order, bound owners, offsets and no-mono
checks remain, with valid reserved type sentinels.

Fresh c50d2a04 completes associated-2 with exit 0, original ok golden and
248 unchanged inputs. Independent c2_classification_review accepted the original
intent, stronger identity assertions and whole-fixture evidence after the
nonzero controls were added. No production, verifier, API or language change.
Raw compiler/tmp/phase3-internal-fixtures/associated-2; receipt
meta/evidence/existing-feature-conformance/source-owner-facts/associated-bound-fixture-maintenance.json.
Final complete G2 gates remain mandatory and uncertified.
