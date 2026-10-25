---
id: com-4bib
status: closed
deps: [com-i20o]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, verification]
---
# Assign and verify requested-body semantics across command modes

## Boundary

Phase 3F / F1. **Bounded mode-parity investigation and controls.** Parent criteria: 7, 11.
This is a bounded child of [met-si6j](met-si6j.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/CheckedProgram.pw`; `src/DeclarationProgram.pw`; `src/CompilerExecution.pw`; `tests/harness/test-gen.sh`.

Build a fixed seven-row parity table for ordinary, generic/provided, closure, global initializer, default generator, generated body and invalid unused body. For each state the actual requested work and check/build/run/gen command or CompilerSession request. Whole-target versus lazy omission and the separate gen program are intentional; compare only equivalent requested bodies.

## Exit and Evidence

Each row has concrete positive/reject inputs, command/request, expected requested/unrequested scope and actual shared checker/owner. Run only missing representative contrasts; route a reproduced mode-specific source checker/invalidity deferral to a mandatory bounded repair. Do not require run/gen to inspect all unused application bodies or create a second runtime.

Existing starting controls: `source_typing_owner_requests`, `unused_struct_required_array_field`, `compiler_session_demand`, `compiler_session_initializers`, `default_argument_call_templates`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Outcome: Bounded Mode Parity Verified

Source01e17fdb, fresh compiler bin/plewc-trait-associated-owner-2
SHA033ff8473787d5fd300e6ce5d2f2df9b6e7a978c7188acbfb947f4f3dd84e244.
F1 run3 completed15/15 groups and60 commands, inputs unchanged. Seven rows:

| Row | Shared source authority and verified contrast |
| --- | --- |
| ordinary | prepareLexicalBody/Function(owner); same positive output and missing-call rejection in check/AOT/run |
| generic/provided | canonical semanticBodyOwner, declaration-bound abstract checking and separate concrete environment; requested positive/negative in all modes |
| closure | parent source publication/checkNestedSourceFacts, Closure(expression)/bodyKey then canonical Mid; invoked child positive/negative in all modes |
| global initializer | prepareGlobalInitializer(target), independent Global(target) payload then startup root; same startup positive/negative |
| default generator | independent Function(generator), DefaultGeneratorOrigin; omitted parameter/field defaults and immutable-owner publication pass |
| generated body | separate selected generator host and application; greet/helperboundary positives, invalid macro helper, requested invalid generated method, and incomplete AST-input Eq contrast |
| invalid unused | whole check/build reject; lazy run omits unrelated invalid body; internal repeated failure/owner isolation controls pass |

Compiler.compileSource uses CheckedProgram.check for ordinary whole builds and
separate analyzeFrontend(genMode) for the selected generator host. Check consumes
checkCompilerSession/completeFrontendDeclarations; run opens CompilerSession and
requests declaration roots through common source preparation. The driver adds
no alternative source checker or runtime.

Initial6dd13/14 stopped at Eq.derive's associated receiver environment. Required
com-i20o repaired the lexical Self/namespace boundary and is independently closed.
The original033 run2 then correctly generated Eq but stopped on a mistaken,
never-successful scratch expectation. Its empty main does not request invalid
Eq: whole check/build reject the exact missing Eq/Ord witness, lazy run succeeds.
The separate generated-method negative actually called by main rejects identically
in all three modes. Original language fixtures and their expectations are unchanged;
failed earlier runs remain failed. Frozen preparation README is historical, not
current status.

Durable receipt: meta/evidence/existing-feature-conformance/source-owner-facts/
phase3f-mode-parity.json; earlier limits/failures in phase3f-mode-parity-initial.json
and trait-associated-namespace-repair.json. Independent b2 verified128 references,
301 final and208 reused inputs plus the static handoff, and accepted this finite
exit with no material gap. F3, gen-all, G2, phase3/main and seed promotion are not
certified. Required B/com-9p68 remains linked through com-072n, areas and G1.
