---
id: com-4bib
status: in_progress
deps: []
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

## Prepared Seven-Row Request Map (Not Executed)

Read-only preparation at36680385 finds no new mode-specific defect; this is
not current-candidate parity certification. The finite comparison remains:

| Row | Shared source request/owner | Required contrast |
| --- | --- | --- |
| ordinary | prepareLexicalBody -> recordParametricFunction/checkGenericFunction/verifyFunctionDeclaration; Function(canonical declaration) | same requested body under check/build/run, positive and missing-call rejection |
| generic/provided | same lexical preparation; provided semanticBodyOwner, separate concrete instance | symbolic generic and provided method requested in all modes |
| closure | nested source preparation/publication; Closure(expression), separate bodyKey | parent construction and demanded child success/failure |
| global | prepareGlobalInitializer(target), individual Global(target); startup root is separate | same startup positive/reject under all modes |
| default | registered parameter/field generator Function, retained DefaultGeneratorOrigin | omitted parameter/field defaults plus independent owner publication |
| generated | gen harness uses ordinary lexical preparation; resulting application is a separate program | harness positive/reject and generated application check/build/run |
| invalid unused | check/build request whole target; lazy session/run omit unrelated body | whole-target rejection versus requested-only success, then explicit request rejection |

Existing source_typing_owner_requests/default_generator_source_publication and
gen greet/helperboundary/UnresolvedField controls supply intent. The current
scratch plan/runner at compiler/tmp/phase3f-mode-parity is unexecuted; its pinned
initial E4 carrier must be reviewed/updated before use. No F3 InternalSession CLI
job or historical diagnostic-host success is reused as current product success.
