---
id: com-qomc
status: open
deps: []
links: []
created: 2026-11-13T20:47:03Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, generics, verification]
---
# Restore inherited conditional evidence when boxing newtypes as existentials


## Guarantee and scope

A nominal newtype, including two inherited layers, can be boxed as an
existential when its underlying implementation supplies the complete
conditional requirement. The public witness is interpreted with the logical
receiver and the inherited body uses its physical receiver. Keep the selected
declaration, clause IDs, substitutions and condition proof through checking
and the actual dynamic call. Unproven conditions and foreign/missing evidence
remain rejected. This repair does not change trait, newtype, existential
or extension rules.

## Reproduction

On unchanged `tests/fixtures/run/existential_newtype_condition_witness.pw`,
`plewc-phase3b-implicit` (`f9ee3c79`) and
`plewc-com-zqqi-receiver-20261112` (`61e6af2d`) pass `--check`.
`plewc-com-ab7u-final` (`381d515a`) and the current extension candidate
(`cde1692d`) reject line 6 with
`selected conformance evidence does not satisfy its declaration conditions`.
The fixed-input normal run `20261113T185937-test-6b3c54` also reports
this rejection. These checkpoints bound the regression; the introducing
revision and first broken proof handoff have not been identified.

This fixture is a real consumer in the earlier
[callee evidence verification](com-v2xk.md) and
[inherited receiver contract](met-ia09.md#inherited-receiver-boundary).

## Work and completion

- Reproduce and distinguish declaration proof preparation, inherited
  logical/physical receiver interpretation, and existential boxing.
  Follow the original condition from witness preparation through the
  failing consumer and locate the first conflicting or missing evidence.
- Keep the existing fixture and its four expected outputs. Confirm
  direct and both inherited receiver levels, `Related[Self]`, adjacent
  interface boxing controls and corrupt/missing proof rejection. Confirm
  the existing RED and verify check, JIT and linked native with a fresh
  carrier and independent review.
- Use the [evidence contract](../design/types-and-evidence.md#5-conformance-evidence)
  and previous [boundary](com-v2xk.md#closure-reconciliation). No
  proof-verifier weakening or ambient receiver lookup is permitted.
