---
id: com-xlmh
status: open
deps: []
links: []
created: 2026-10-28T01:14:39Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, mid, verification]
---
# Strengthen the mixed-tail-enum return regression oracle

## Contract and Evidence

The exact input is `tests/fixtures/run/mid_body_build_return_error_match.pw`,
with `.out` and `.ll.expect`. Its actual adding commit `b60ef527` used
`tests/run/`; source and both companions were inspected. The stated purpose is
to preserve the mixed-payload tail enum across `makeError`/`propagate`/`build`
and aggregate field projection. The correct error is Unsupported.Projection.

Both that arm and None print the identical Body sum16. The companion requires
only the module-wide literal `switch i64`; it does not distinguish these tags.
The actual default worker in `tests/harness/test.sh:100–133` compiles, checks
that literal, links, then requires exit0 and stdout16. Thus a tag corrupted to
None while the Body fields remain intact can satisfy all these assertions.
This is a confirmed weakness of the predicate, not a reproduced compiler defect
or proof that the current generated program takes the wrong arm.

## Scope and Completion

Make the intended discriminant and nested Projection distinguishable from None
and the other error/payload cases, retaining the dynamic returned aggregate,
propagation path, Body field observations and meaningful IR check. Demonstrate
that the intended positive passes and the specific tag-loss alternative fails
the actual assertions. Keep source versus physical ABI claims separate; a
generic switch marker alone cannot certify a body or a return ABI. Do not
expand this into every enum/return feature or change physical layout by fiat.

`com-rb1s` addresses a different zero-sized byval checker and is not this owner.
Stale legacy-path comments are optional prose work in `com-lm8j`. Later repair
follows TDD and scoped independent review; this audit changes neither fixture,
golden, compiler nor runner and executes no real compiler or generated program.
Batch0056 assigns this input's source role only; finding the detector weakness
does not also complete its separate outcome obligation. Evidence lives under
meta `evidence/test-audit/scoped-reviews/frontend-batch-0056.json` and its review.
This finite follow-up is independent of audit completion.

