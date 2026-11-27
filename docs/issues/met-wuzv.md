---
id: met-wuzv
status: open
deps: []
links: [met-gjxo, com-9sa5]
created: 2026-11-27T05:23:46Z
type: task
priority: 2
assignee: Koji Murata
parent: com-604k
tags: [frontend, verification]
---
# Determine coherent inputs for public declaration verification

Determine the actual Comp/Arena/interner/module coherence contract from the retained foreign-corpus replacement probe, then classify and assign any required repair without broadening nominal label admission.


## Executed probe and scope


met-gjxo exposed an additional Raw-state hazard: open a valid source Comp,
replace its public Arena with a different two-byte corpus and an invalid nominal
row, then call public checkDeclShapes. Before nominal label validation, the
ambient-name checks reuse the old Comp's source/cached spans against the new
bytes and panic (`interner stored a span outside the source buffer`). The
standalone nominal byte/span core itself rejects malformed spans safely.
[Executed probe](../../../evidence/rejection-domains/diagnostic-domain-implementation/declaration-labels/raw-arena-incoherence.json)
retains a native snapshot and phase markers proving the public Syntax decoder
completed before this replacement check failed. It is internal caller-owned
state, not evidence that ordinary user source triggers this panic.

Investigate the whole-state publication/input contract: either make such
replacement unrepresentable at the appropriate owner boundary or diagnose
incoherent Raw snapshots before dependent readers use unrelated cached spans.
Do not add another nominal Source flag or reorder checks merely to hide this
foreign-corpus inconsistency. The met-gjxo skip-authentication control preserves
the actual source corpus while replacing its Arena value and injecting a
nonzero-scope duplicate; that remains a required rejecting control.

## Investigation endpoint

1. Identify the public verifier's required Comp/Arena/interner/module metadata
   coherence contract and the actual corpus/span readers in this reproducer.
2. Determine whether this replacement is permitted input rejected incorrectly,
   or representable but not authorized input missing a boundary/invariant
   contract. Preserve the observed panic separately from that classification.
3. If repair is required, assign a finite implementation owner, guarantee and
   actual prerequisites. If outside scope, retain contract grounds and the
   exact guarantee limit. Investigation completion is not product repair.

The native snapshot/result/markers linked above are the finite evidence. Do
not infer ordinary-source crashes, a nominal comparison-core defect or a need
to harden every Raw reader from this internal inconsistent snapshot. This is
a prerequisite of com-604k; phase-three applicability must be derived from the
contract instead of adding an unclassified direct dependency. met-gjxo's
independent label/skip guarantees do not depend on this investigation's repair.
Scope/placement independently reviewed by qualified_member_plan.
