---
id: met-gjxo
status: closed
deps: []
links: [com-9sa5, met-wuzv]
created: 2026-11-27T04:45:28Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, diagnostics, verification]
---
# Admit nominal field and variant uniqueness across every module


## Contract and confirmed failure

Nominal declaration admission must validate each struct's field names, each
enum's variant names and each variant's payload labels independently of module
number or body demand. Source field unification is specified in spec05;
frontend/declaration handoffs require valid source declarations before successful
publication. Unused imported declarations are not an exception.

Fixed productc6720051/594990c485aa has48 executed controls:24 legal passes,
12 local invalid-shape rejections lacking Source classification and12 imported
false successes, across check/AOT/ORC.
[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-labels/README.md).
Actual checkDeclShapes filters struct/enum loops to module0.

## Required investigation before implementation

- Trace actual Syntax/legacy Lower and registerStruct/registerEnum inputs,
  declared and generic nominal identities, synthesized rows and gen harness
  duplicates. Identify reservation versus successful declaration publication
  and actual source-owner boundaries. Do not assume an Arena row/span or
  private Source-mode enum alone proves source ownership.
- One label equality/conflict authority must be shared by source admission and
  Raw validation. The core reads bytes/label spans and returns a typed conflict
  or malformed-input distinction, not a Source report. Actual source decl
  owner binds its complete labels and original/duplicate slots/locations.
  Source errors cannot be reported from an unrelated Raw/synthetic/foreign row.
- Preserve the existing gen shape-check suppression needed by its trusted
  macro harness; ordinary compiled generated source follows normal rules.
- Study actual data/reader needs and avoid another parallel declaration checker,
  public source flag, whole mutable Comp facade or per-request AST reconstruction.
  Remove the unused checkDupFields ctx and narrow its genuine byte/name inputs
  as the coordinated com-9sa5 field-leaf migration, without absorbing that task.

## Scenarios and completion

1. Meaningful fixed-candidate RED for all three imported false-success shapes
   and local missing Source origin. Preserve legitimate labels, same payload
   label in different variants, different types/modules, generics and unused
   import modes. Rejection must precede successful declaration publication.
2. Real producer/retained result/session/CLI paths with original/duplicate
   locations and exact intended reason. Raw registerStruct/registerEnum,
   synthetic declarations, foreign/wrong source slots and malformed spans
   never gain Source or turn ordinary invalid input into compiler panic.
3. Remove module-zero acceptance and competing old decisions. Shared core,
   source/Raw adapters and gen boundaries receive structural plus executed
   controls; no whole-verifier rewrite or weakened checking.
4. Fresh applicable regressions, fixed point/formal<=7.5s, independent final
   review, synchronized evidence/tickets/worklog and bounded cleanup.

## Ownership and exclusions

Parent com-604k owns existing-feature conformance. com-yeua depends on this
finite producer repair for its declaration-label refusal channel. com-9sa5
owns the existing broader verifier/input audit; preserve its other functions,
remaining callers and guarantees. No parameter/type-name duplicate overhaul,
extern ABI/layout redesign, all-shape audit, new feature or language decision.
Independent qualified_member_plan accepts this finite scope and its separation
from behavior-preserving API narrowing. Actual declaration ownership and
gen/synthetic registration paths were inspected before implementation.

## Implemented boundary and verification

The 48-control real-CLI matrix is RED against saved594990c485aa: 24 legal
controls pass; 24 invalid-shape controls fail acceptance/domain assertions.
All input hashes remain unchanged. The pure comparison core's executable
controls pass, and the whole compiler source passes `--check` with this carrier.
The final source snapshot v2 built successfully
(20261127T050944-build-2c10ca), with48 public controls passing. Final finite
recognition is recorded below. Setup mistakes in the newly written core harness were corrected
and do not count as RED.

The private parsed-item lowering chain carries the existing admission origin to
completed nominal labels immediately before registration. Public Syntax and
legacy decoders stay Raw. No persistent source receipt or source-state heuristic
is added. Raw/synthetic fallback verification shares the same core, removes
module-zero filtering and the unused ctx parameter. The private synchronous loader-to-verifier continuation skips already
admitted nonzero-scope nominal rows; public/caller-owned verification still
checks every Raw row, including replaced Arenas and injected nonzero scopes.
Scope-zero synthetic rows remain checked on both paths. This uses the actual
private fresh-construction call chain, not a persisted scope-number capability.
Structural review found the four nonzero-scope nominal registration paths all
covered by the registration-before-publication check. Gen suppression remains.

Independent review accepts the private Source/Raw call boundary,
registration position and private verifier handoff. Its required native
controls are recorded below. Diagnostic order for multiply
invalid enums is now all variant names before payloads; the complete variant-name group is checked before any payload group,
so the single comparison core owns each complete group. This only changes
which violation is reported first when both kinds are already invalid;
no declaration acceptance or effectful evaluation order is changed.

Native final-source controls passed compile/runtime/link/execute with invariant
inputs: private Source refusal before registration, Raw/synthetic/fake-scope
checks, actual public Syntax decoder, coherent Arena replacement after source
admission, malformed/overflow spans and gen suppression. Session controls
retain exact Source message/location/notes after frontend state is gone across
repeated opens. Evidence: declaration-labels/native-v4.json and session-v1.json.
The separate foreign-corpus replacement panic is retained under met-wuzv;
its invalid whole-Comp snapshot does not replace the coherent fake-scope
control, which still rejects. Native setup-only v2 compilation failure and
the v3/debug whole-state panic are not counted as successful controls.

Formal20261127T051755-self-host-5658f2 reached generation2 fixed point, all
inputs unchanged, samples7.782508/7.359985/7.306692s, median7.359985s<=7.5.
Same-source alternating comparison: old594990c485aa median7.393742s versus
new fresh v2 median7.346164s; all6 LLVM hashes equal. This does not establish a
performance improvement; it finds no measured regression. The exact formal
measured binary da2c8c0a82e9 passes48/48 public controls. Generation20261127T053546-gen-54ed7b passed with invariant inputs. Whole
20261127T053719-test-48c29a completed with unchanged inputs/no worker failure.
All3314 cases and source hashes match the252-failure baseline:249 remain,
exactly duplicate_enum_variant/duplicate_struct_field/duplicate_variant_field
resolved, no new failures or other aggregate result changes, no skips or
added/removed cases. This is not whole-green. Final recognition and retention disposition are recorded below.

## Final finite certification

qualified_member_plan independently reviewed source86906902, task/design,
Source/Raw/core/publication/forwarding, all finite native/public/session
scenarios, formal<=7.5, gen and whole reconciliation, and accepts met-gjxo
only. No confirmed code violations or missing mandatory guarantees remain.
The separate corpus-coherence investigation is open met-wuzv, not the closed
editorial met-m7wx; its exact failure material remains retained. Broader
com-9sa5, remaining249 failures, parents/phase3/main green are unrecognized.

After review19 regenerable native/comparison products (846459028bytes) were
retired, preserving sources/input/result/log evidence and the unresolved
debug failure. Formal generations and measured da2c8c0a82e9/std remain; saved
carrier48 controls pass. Old comparative carriers and latest249 failure
payloads remain through parent reconciliation, then their owners recheck
retention. Canonical evidence README indexes the final guarantees; obsolete
18-case/interim duplicate receipts were removed after transfer. Closure
bookkeeping follows signed evidence/task commits and pushes.
