---
id: met-auj6
status: closed
deps: [met-q7ig, met-g9dh, met-9luu, met-ldvd]
links: [com-9sa5]
created: 2026-11-27T07:01:06Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, diagnostics, verification]
---
# Admit callable parameter groups across modules

## Contract and confirmed failure

Spec04 requires unique declared parameter binding names, including suppressed
positions, and unique non-absent signature labels across named declarations,
requirements, closures and function types. Explicit val/mut val re-declaration
and outer-scope shadowing remain valid. Function types have no local binders.
The declaration-introduction owner admits a complete group before signature
publication; body-scope consumers install the admitted group without repeating
acceptance or changing generic local append into a collision policy.

Fixed da2c8c0a82e9's84 family controls show local Unclassified rejection but
imported acceptance for ordinary/generic free functions, methods, associated
functions, factories, authored provided methods and default forms. Requirements
and global closures accept repeated labels in both locations. Extern(c) labelled
forms reject earlier for the independent no-label rule. Runtime labelled and
suppressed closures, and a named suppressed fn, return22 for inputs11/22.
Generic addLocal append plus reverse lookup allows invalid parameter groups
to behave as shadowing. Local explicit sequential and outer/parameter shadow
positive controls are retained.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-parameters/README.md)
records carrier/std/manifest/driver/source hashes and invariant inputs. The
user decision/spec/design are owned by met-q7ig. Old supported behavior is
not proof of the adopted rule, and syntax/setup errors are not RED.

## Finite implementation children

- met-g9dh owns the shared comparison/group contract and named/requirement
  signature admission before successful registration. Keep Source versus Raw
  provenance and genuine completed-group ownership. Trace the four production
  registerAuthoredCallable callers and the separate requirement/extern paths.
- met-9luu consumes admitted groups for body scopes and closure introduction
  before descriptor/publication. Preserve stable identities, captures and
  legitimate shadowing. Do not scatter duplicate loops into closure branches.
- met-ldvd applies label-only uniqueness through function type construction,
  type-use admission and retained consumers, without inventing local binders.

The latter two depend on met-g9dh; all three block this parent. coordinate
only the com-9sa5 parameter-label leaf, not its broader type-name/default/arity
and metadata audit. Whole inconsistent Comp-corpus input is met-wuzv, not a
reason to infer Source authority from a scope number or diagnostic text.

## Completion and integration

Reconcile the complete authored/derived caller map and existing gen policy;
original groups are admitted once and forwarded/default/provided/via/generic
forms preserve that result. Remove module-zero/competing decisions and excess
validation or parameter-array/environment reconstruction. Preserve declaration
versus body-demand boundaries and source evaluation order.

Prove fixed-carrier RED and targeted public/native/Raw/source/retained-result
controls for each child, including absent labels, binder-name conflicts,
legitimate shadowing, implicit receiver/captures, generic/default/requirement
and closure/type paths. Keep labels and binder names as separate guarantees.

After children pass independent reviews, perform aggregate fresh/gen/whole
reconciliation, fixed point/formal<=7.5 and same-source regression assessment,
independent parent review and bounded evidence/product cleanup. Baseline is
3314 cases/249 inherited failures, not green; no tests or verifier weakening,
no main/seed/bin promotion and no phase3 closure from this parent alone.

## Integration checkpoint

All three finite children are independently certified and closed. Final
source d712af31 passes C84/B96/A114, all common-evidence visibility native
controls, Raw/legacy/session retention and selected gen. Formal fixed-point/
performance run20261127T115307-self-host-425d2d uses the retained adopted da2
carrier against frozen function-type-label-build-v2; whole-suite reconciliation
and independent parent certification remain pending. This is not phase3 closure.

Formal20261127T115307-self-host-425d2d passed: G2 fixed point, unchanged
inputs, samples7.886941/7.380636/7.350523, median7.380636<=7.5. Same-source
alternating comparison da2 versus measured149aac is7.425221 versus7.322186,
all6LLVM equal and input hashes unchanged. No observed regression. Whole-suite
reconciliation is now running on the measured149aac candidate.

## Finite completion

Resolved at product d712af31. Independent final review accepted the structural
caller/consumer boundary and all targeted/gen/formal/same-source/whole evidence.
Whole20261127T121111-test-c32d9f completes3314 common cases,249->248 failures:
only reject/duplicate_param_label resolves, no new or other changed result,
skip0, no worker failure, all6651 fixtures/expectations and11 std files match.
Residual248 failures and payloads remain owned by com-yeua and existing scoped
owners. Meta declaration-parameters/{whole,whole-inputs,formal,comparison}.json
contains exact receipts. Reviewed successful native intermediates686423893bytes
were retired; source snapshots, baseline/current failure payloads and formal
generations are retained for the next producer comparison. Saved measured
149aac carrier/std hashes match and its84-case matrix passes. This certifies
finite parameter-group admission, not phase3/main/seed or all compiler green.
