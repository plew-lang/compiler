---
id: met-auj6
status: in_progress
deps: [met-q7ig]
links: [com-9sa5]
created: 2026-11-27T07:01:06Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [frontend, diagnostics, verification]
---
# Admit named callable parameter labels across modules

Preserve existing labelled-parameter distinctness independently of module and body demand, through actual callable declaration admission and retained Source failures. Trace all current authored/derived callable paths and agree a finite implementation scope before editing product code.


## Confirmed boundary and semantic limit

Fixed development carrier da2c8c0a82e9 rejects an unused local ordinary
`pub fn bad(value: I64, value: I64) {}` as duplicate parameter label, but
accepts the same declaration moved to an unused imported module in all three
check/AOT/ORC modes. Local rejection is Unclassified. Existing
reject/duplicate_param_label.pw confirms the existing labelled-parameter
distinctness intent. Verify/Decl.pw checkDupParamLabels checks only module0
nonextern/nonprovided rows.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-parameters/README.md).
Preserve this existing local declaration rule across modules; do not invent
a new function-type rule or a policy for repeated unlabeled local bindings.
Spec04 labels/ordered arguments, source declaration admission and diagnostic
owner contracts are authoritative; stop for an actual undecided language rule.

## Investigation before product edits

Map every existing authored/derived callable route feeding this check: free,
instance/associated methods, factories, generic signatures, default/provided
adapters, trait requirements and extern/closure categories. Distinguish
source declaration identity, completed parameter group and reserved row from
successful publication. Determine which existing rules/exemptions apply and
which source owner can bind the labels; do not assume a Func row or span
proves Source. Reuse existing callable admission where it owns the contract,
not a new per-message event table or a post-hoc declaration relookup.

Independently review the finite repair/caller map before implementation. If
a separate category cannot be covered by the same class, retain an explicit
required owner/dependency rather than silently excluding it.

## Guarantee, scenarios and endpoint

- One real label-conflict authority shared by source declaration admission
  and Raw verification; consider the existing dependency-light byte/span
  core before adding another checker. No whole mutable Comp in comparison
  leaves and no label text/module number as source authority.
- Reject existing duplicate labelled parameters before successful declaration
  publication in every applicable module, regardless of unused body demand.
  Preserve label suppression, valid distinct labels, overload/default
  selection, source evaluation order and the existing trusted gen policy.
- Source owner attaches original/duplicate slots and mapped locations;
  failures retain domain/message/notes through returning and session/CLI
  consumers. Raw/synthetic/foreign/malformed operands cannot gain Source.
  Whole inconsistent Comp-corpus validation remains met-wuzv.
- Meaningful fixed-candidate RED, then public check/AOT/ORC and real native
  owner/Raw/generated/retained-result controls for the selected categories.
  Cover legal pairs, imported unused declarations, explicit/omitted labels,
  generic/default/provided handling and authentic versus injected metadata.
- Remove module-zero/competing decisions and needless revalidation of
  completed source groups. Narrow the com-9sa5 parameter-label leaf without
  absorbing its type-name/default/arity/field-membership audit.
- Applicable fresh/gen/whole gates, fixed point/formal<=7.5 and same-source
  regression assessment, independent final review, durable evidence and
  bounded retirement. The parent/phase3 and unrelated existing failures
  remain open; no main/seed/bin promotion.

## Initial route survey (product unmodified)

Independent qualified_member_plan accepts the scope/ownership separation and
requires label versus local binder controls, authored versus derived group
identity, interner-ID/byte-span equivalence, implicit receiver exclusion and
gen distinction before selecting the implementation.

The84 executed family controls preserve all inputs. Local labelled duplicates
reject Unclassified and imported copies succeed for ordinary/generic free,
instance/associated methods, factory, provided method and default-parameter
forms. Distinct labels and the existing one/both suppressed duplicate-binder
forms succeed in both placements; do not turn them into a new binder rule.
Trait requirements and global closures accept the duplicate-labelled forms
in both placements. Extern(c) labelled forms fail earlier for its independent
no-label rule, not duplicate-label validation; do not count those as this RED.

Source trace: registerAuthoredCallable in Lower/Types has four production
callers: Syntax/legacy free declaration and Syntax/legacy impl method (the
latter includes associated/factory/provided definitions). It registers the
Func before binding the completed source signature. bindAuthoredRequirementSignature
is a separate existing requirement path; synthetic/default/provided copies and
closure registration must be enumerated separately before authority changes.
The old checker compares nameIds with no zero/foreign evidence and ignores
noLabel positions. Do not assume a direct byte-span migration is equivalent
for arbitrary Raw or generated parameters. Further mapping remains required.

## Required semantic boundary

Follow-up independent review of the84 controls finds that the existing named
module-independent repair is justified, but extending label uniqueness to
requirements/closures and function types is not already explicit in spec04.
met-q7ig retains the required user decision and spec/design/implementation
assignment. It is an actual dependency; do not silently exclude those observed
categories or implement a new rule while claiming a behavior-only repair.
No parameter product code has been edited.
