---
id: com-kp3y
status: closed
deps: [com-rv13]
links: []
created: 2026-10-21T15:16:01Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [design, verification]
---
# Seal source owner facts through existing Mid and Mono readers

## Contract and Current Boundary

The owner-storage area under [met-acfl](met-acfl.md) covers header/expression/
binding/completion/aggregate/try/pattern facts and their actual Mid/Mono readers.
Ordinary, generic/provided, closure and global owners preserve source identity;
construction of a closure/signature is not successful preparation of its body.

The adopted [storage](../design/checked-body-storage.md) uses private owner-local
builders, immutable Ref-backed payloads, local indexes and shared type/proof IDs.
The all-owner semantic arrays and full-table acquisition snapshots were removed;
reader APIs pass the needed rows/indexes instead of copying an entire payload.
Retained readers remain stable across later owners and Comp forks. Failure keeps
its first diagnostic and prevents later writes, as does successful publication.

Construction-time callable metadata remains available without requiring a
successful callee body. A missing required fact fails; absence of a non-applicable
aggregate record is legitimate. Mid invocation completion and generator global
reachability read scoped successful facts. Other operation/evidence/descriptor
families belong to their named sibling tasks, not a complete CheckedBody token
claimed by this component alone.

## Executable Work and Exit

[D1](com-rv13.md) reconciles the seven fact-family writer/publication/reader
paths and decisive controls. [D2](com-vkw3.md) owns the remaining lexical
domain contrasts, and [D3](com-wqa0.md) the operation/constraint API closure.
Do not repeat the completed payload migration or wait on all of met-ucze before
checking this already implemented boundary.

Close after D1 and any exact required repair children establish current source
locations, removed competing tables/writers/readers, applicable fresh positive/
foreign/missing/post-outcome/fork/retained-reader controls and no unresolved gap
in this component. Preserve internal test intent and private writer boundaries.
Prior whole-gate/storage-cost evidence is in the
[existing index](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/README.md);
do not apply its results to later binaries without matching scope/inputs.

Final candidate full gates are an explicit independent parent obligation in
[G2a](com-p5um.md)/[G2b](com-9l3b.md), not a reason to keep this bounded
implementation component open forever. This area does not close met-acfl or the
parent automatically.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), [com-esri](com-esri.md): **Included repair** of existing
owner publication and successful readers. No new persistent incrementality or
unsupported capture/unique feature is required.

## Independent Area Reconciliation

Closed as the bounded owner-storage component at d4749a85 after independent
contract reconciliation by /root/body_receiver_completion_review. D1/com-oi3v
close the seven owner-local fact families, immutable readers and actual public
Mid owner/session admission. D2/com-vkw3 retain ordinary/provided/closure/global/
default identities. Their exact receipts, tested revisions and unchanged-input
scopes remain in those tickets and the source-owner-facts evidence index.
No additional storage repair or new feature is required by this component.

The all-owner tables/snapshots and external payload/directory writers remain
removed. Stable failure, successful publication, retained/forked readers and
missing/foreign/post-outcome controls are covered by those independently admitted
children. This reconciliation does not attribute their older whole gates to
current binaries. Operation/constraint APIs, nominal facets and exact saved
transfer targets remain the enclosing area's separately named contracts; the
last is being closed by com-tl9c/E4. Final G2, met-si6j, runtime capture/startup
work, main/seed/adopted-carrier promotion are not included.
