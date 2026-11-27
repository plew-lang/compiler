---
id: met-q7ig
status: closed
deps: []
links: []
created: 2026-11-27T07:12:54Z
type: task
priority: 1
assignee: Koji Murata
parent: met-auj6
tags: [spec, frontend, design]
---
# Specify parameter binding and signature label uniqueness

## Adopted contract

The user approved distinct non-absent labels in every callable signature,
including trait requirements, closures and function types. All declared
parameter binding names are distinct within one parameter group, even with
label suppression. Function types introduce no local binders; repeated bare
unlabelled type positions remain valid. Explicit sequential val/mut val and
outer-scope shadowing remain governed by spec03.

The declaration-introduction owner, not generic local storage, admits the
complete group. It knows whether this is a parameter definition or an explicit
shadowing declaration, and needs only the new parameter group for uniqueness.
It does not inspect unrelated outer bindings. Accepted signatures and body
scope installation consume that result without separate per-kind checks or
an addLocal allowShadow flag. Low-level local append is not semantic admission.

## Evidence and rationale

Fixed da2c8c0a82e9 rejects named duplicate labelled declarations locally but
accepts imported copies. Trait requirements and global closure literals accept
duplicate labels in both placements. Runtime probes show labelled/suppressed
closures and a named suppressed-parameter fn return22 for arguments11/22:
Record appends parameters one by one and reverse lookup chooses the last.
This is missing group admission, not legitimate explicit local re-declaration.
Positive sequential shadowing returns22 and outer/parameter shadowing returns
22 then11. The exact probes/results are in the linked evidence.

Spec04, name-lookup Parameter Group and Signature Admission, and body-checking
state the contract. A signature can be needed without creating a body scope,
so checking only at local installation would miss requirements/unused bodies.
Do not duplicate the group data/validation in declaration and scope consumers.

## Implementation assignment and completion

Required children under met-auj6: met-g9dh(shared group/named/requirement
admission), met-9luu(body scope consumption and closure introduction),
met-ldvd(label-only function type admission). The latter two depend on the
shared group contract; the parent depends on all three and owns aggregate
compatibility, fixed-point/performance and final recognition.

This task completes the user decision, synchronized contract and finite task
assignment, not product implementation. Independent qualified_member_plan
accepted the rules and split, requesting removal of stale pre-decision wording
and synchronization of the reproducible runtime receipt before closure.

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-parameters/README.md).

## Final documentation review

qualified_member_plan confirmed the adopted introduction-side ownership,
separate label/binder rules, legal shadowing/unlabelled type positions,
reproducible5 runtime controls, three-child dependencies and parent gates.
No document/scope blocker remains. Product code is unchanged; this task's
closure certifies decisions/contracts/assignment only.
