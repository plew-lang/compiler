---
id: met-9ym8
status: closed
deps: []
links: []
created: 2026-11-23T06:42:31Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain opaque generic numeric expectation refusal ownership

## Contract and scope

The abstract generic checker owns the refusal of numeric literals for opaque
caller parameters and provided Self. Preserve that cause through raw services,
request caches, owning consumers and CLI classification without changing source
acceptance, diagnostic wording/order or inference. Dependencies retain their own
failures; Array-context causes remain separate.

Private checking requests propagate through bounds/condition/block/statement
traversal, selected direct-call arguments, Make fields and Array recursion.
Public direct wrappers and Mono remain Raw. Only the actual numeric rejection
branches issue this dedicated negative cause. Preserve caller ParamId versus
provided Self declaration/trait identity, expected term, operand, source location,
recorded owner and session; observe those identities without rechecking meaning.

Lower alone records numeric syntax provenance at its six literal/fold branches.
A recorded semantic owner, fresh serial or copied span alone is not authorship.
The issuer consumes known syntax attributes instead of retrieving the owning
Expr, admitting non-Bool unsuffixed integers and all Floats as before. This
registry is syntax provenance, not a successful type/inference database.

## Guarantees and verification

- Meaningful baseline RED: actual opaque refusals remained Unclassified;
  the initial whole/eager consumer aborts at its source-ownership assertion.
  Test setup errors and timeouts are retained separately, not counted as RED.
- Caller argument/local Int/Float and provided Self; negative integer, suffixed
  Float, nested statement scope and if-body. Valid concrete expectations stay
  accepted. Unrequested provided bodies remain unrequested in ORC.
- Block/Array/closure inputs which fail earlier keep those distinct diagnoses;
  they are not claimed to reach the opaque producer.
- Raw with an active owner, private owned requests, foreign session/root/owner,
  changed expected/operand/location/serial/span/kind, recorded synthetic copied
  spans and equal-text Internal reports. Both Lower entries and negative folding
  retain provenance; Bool and suffixed Int do not retain unnecessary receipts.
- Raw retries/drain, actual lazy prepareFunction retries, failed-session retention,
  fresh whole/eager failure and no checked-program publication. The consumer's
  current golden is18 lines; private probes require empty stdout/stderr.

Canonical evidence, all baseline/candidate hashes, excluded attempts, private
probes, exact outputs, performance samples and independent reviews are in
[numeric_refusal_intake.opaque_checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-contextual-operand-regression.json).
Fixtures are OpaqueNumericFailureDomains.pw/.out, OpaqueNumericMain.pw and the
public generic_numeric_rigid_caller / generic_opaque_numeric_* rejection inputs.

## Accepted outcome

Product5bafacff passes frozen candidate-v3 build5bbb04, generation54fe10,
24public /96Conflict /348related mode controls and LLVM22 ASan/LSan private
and consumer native probes. Goldens, empty runtime stderr and all input hashes
were independently verified. The CLI protocol preserves com-9clj's known three
mode failures; this is not whole-suite green.

Formal20261123T120158-self-host-435306 has unchanged immutable inputs and
G2 LLVM/runtime/successor-binary equality. All7 generation/measurement artifact
records were independently hash-checked. Five times7.812497,7.184613,7.217558,
7.227027,7.232612seconds give median **7.227027 <=7.5**. Measured compiler
SHA2562b5475f3cf961992b36bc9bb84b65157e971c88ddb8c835ac0918aff64ab1083
passes18 fresh measured-compiler modes, including correct factory selection and
unrequested provided-body behavior, with unchanged inputs.

Independent reviewer generic_conflict_source_review accepts the finite contract,
source through final use, lifetime and formal performance with no unresolved
mandatory finding. Earlier formal7.599326 is retained as an unmet checkpoint.
Its full difference from7.227027 is not attributed to the small optimization:
same-source development ThinLTO comparison observes only7.058343→7.042118,
with10 equal LLVM outputs.

Close this child only. com-yeua, complete normal-suite reconciliation and phase
three remain open; neither main/seed nor the user's regular carrier is promoted.
