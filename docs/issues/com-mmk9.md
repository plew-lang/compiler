---
id: com-mmk9
status: in_progress
deps: [com-am6u]
links: [com-kss7, com-ktyj, com-50me, com-qt11, com-u6h0, com-pmwi, com-debo, com-g127, com-4ccf, com-rgml, com-oftp, com-q6pv, com-6u4o, com-0lz8, com-17ha, com-zcwf, com-uk6c, com-9aap, com-l8kt, com-aii4, com-8vut, com-yeea, com-r2sw, com-geem, com-0t9x, com-egv2, com-m4kt, com-l0mr, com-u09r, com-vyk7, com-j3l9, com-orku, com-805m, com-8b4d, com-3bnf, com-bz23, com-zq25, com-pu7h, com-sk71, com-7aaj, com-wfpt, com-0fk5, com-fcmw, com-h4cm, com-iq17, com-6h5i, com-7cpj, com-g5lm, com-4wxu, com-zbas, com-ru19, com-fppu, com-iflh, com-8tqu, com-3njd, com-zm8w, com-0f8m, com-djoz, com-9h5s, com-e1ea, com-6u0t, com-5m8j, com-y63b, com-cmrh, com-lgu1, com-o1fh, com-gv0c, com-sj16, com-9ovy, com-vbvu, com-uvys, com-lzm2, com-id5r, com-2qxd, com-ktrb, com-sxzv, com-v7fu, com-gewn, com-ge01, com-n5lu, com-dsfy, com-xc6h, com-i86w, com-9sa5, com-g49i, com-e2dp, com-eu8i, com-tfz7, com-fpmj, com-if6u, com-xh2h, com-q40o, com-muiu, com-3i84, com-g8kd, com-3fb5, com-o312, com-g70q, com-jc6v, com-wv5l, com-9508, com-tqwa, com-16j0, com-og6p, com-9uw1, com-yr4c, com-a1qy, com-igex, com-tpxd, com-u1tx, com-crym, com-t4gm, com-ma6z, com-wmr0, com-fsxx, com-ough, com-dxgh, com-nq9x, com-zefb, com-5d3q, com-jwzi, com-ui4c, com-62pl, com-1bh1, com-90e7, com-dgbf, com-0cfk, com-s0zb, com-y1h9, com-jyy5, com-307g, com-4auy, com-zfr6, com-x48z, com-ia8o, com-vh0x, com-euq7, com-0huw, com-fboq, com-r3od, com-hd9n, com-j2oe, com-8egj, com-nd29, com-404b, com-6vcb, com-togc, com-efhz, com-zhn0, com-lawd, com-0vbn, com-0od6, com-p1mt, com-4sw4, com-p8xt, com-61ji, com-j84i, com-rs2x, com-f4oz, com-74ky, com-oihh, com-nzei, com-v9md, com-ynz6, com-esbb, com-1fbr, com-jm7l, com-tqeu, com-3mcv, com-f87d, com-mrab, com-zftv, com-ctor, com-j2i7, com-5bmt, com-e6zm, com-iaqs, com-xp8r, com-qadp, com-n8nh, com-ozkj, com-n2fv, com-a5os, com-mxo0, com-j3cp, com-cvnk, com-8r3r, com-j7nu, com-pn1y, com-mexd, com-p9rd, com-f17t, com-kb6f, com-d4m2, com-9nbx, com-nei5, com-ct0w, com-0htd, com-kt7y, com-eatt, com-yb1d, com-cuiw, com-08i0, com-qrmt, com-59sf, com-aqud, com-l50h, com-yyyl, com-ot44, com-pmiz, com-70tb, com-3j3n, com-sj9s, com-zigu, com-p5q2, com-4vvt, com-be0m, com-4oor, com-hnm8, com-xx65, com-vk09, com-bw8e, com-iri8, com-lwsd, com-z07h, com-pra8, com-88dq, com-gqtz, com-3gut, com-kpd0, com-9i94, com-nee8, com-ixfs, com-847f, com-hux9, com-lp4q, com-pf1a, com-nfj8, com-8by9]
created: 2026-10-27T02:15:37Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Audit unnecessary inputs and capabilities across compiler APIs

## Question and Actions

Using com-am6u, inspect what each assigned API/constructor needs for its
responsibility versus what its callers pass or its retained context exposes.
Check individual values and indirect access through fields/captures/globals or
large context objects; replacing a broad context with a wrapper is not enough
if the same unrelated capabilities remain accessible.

Assess frontend, Mid/async/ownership, backend and input/driver/session boundaries.
Do not infer that a broad parameter is wrong merely because it is broad: source
positions, declaration navigation and domain-specific environments can be valid
inputs. Ground each finding in the API's contract, caller and actual access.
Suggest the narrow required input or interface and name the affected consumers.

Record justified inputs, confirmed responsibility mismatches and optional
simplifications. An unresolved question is an interim investigation state, not
a completed audit verdict. The target is API input/capability separation, not a
complete implementation-correctness or performance audit. Reuse matching
evidence within its actual scope.

## Completion — all conditions are required

**Done means all required input-authority questions have an evidenced answer.**
Moving an unanswered question to another task is not completion. Implementing
the repairs found by this audit is separate work.

1. Cover every inventory family and every mixed API component. For each, compare
   its responsibility and required inputs with actual caller/default/constructor
   values and reachable authority, including relevant delegates, captures,
   globals and retained state. Preserve necessary effects, identity, lifetime,
   diagnostics and failure/restore behavior when proposing narrower inputs.
2. Resolve **every required input-authority question** with source-grounded,
   independently reviewed conclusions: justified inputs, confirmed unnecessary
   authority, or a genuinely optional simplification. This includes the original
   419 main unresolved families and 71 unresolved mixed components, including
   components inside a J/C/O family. Follow their answers in the resolution index;
   these historical counts do not mean that accepted answers remain unresolved.
   No required input investigation may remain unresolved at closure.
3. Splitting an investigation or assigning it to another issue does **not**
   complete it. Its unanswered questions remain required work of this audit;
   the final reconciliation must follow each original family/component through
   any splits to its substantive answer. Closing a follow-up issue, registering
   an owner or producing an inventory/review receipt alone is insufficient.
   If a user decision or unavailable evidence prevents an answer, explain the
   blocker and keep this task open; do not silently defer or reclassify it.
4. For confirmed excess, identify the affected actual APIs/consumers, concrete
   excess authority, narrower required contract and a finite repair owner.
   Product repairs are separate: their implementation, behavior tests, GREEN,
   performance, main integration and seed promotion are not audit prerequisites.
   Optional simplifications remain optional.
5. Independently review the resolved conclusions and the complete family/component
   reconciliation under these conditions, dispose all required corrections and
   synchronize the current acceptance, task and worklog. Counts or review rounds
   do not substitute for answered questions. Retained earlier evidence is usable
   only within its checked scope; the earlier permissive closure rule is revoked.

No compiler source, tests, expectations, binaries or execution runners are changed
within this source-only audit.

## Audit Basis and Scenarios

The dependency com-am6u is closed as factual discovery. Its
[acceptance](../../../evidence/compiler-api-audit/inventory-acceptance.json)
pins all 1,504 source/API families and their individual evidence/review limits.
Use each family responsibility, actual typed calls and supplied/default values,
full reachable authority and legitimate inputs together. A broad owner receiver
is not wrong merely because it owns several fields; direct reads alone also
cannot hide capabilities reached through delegates, globals or retained handles.

For every family, retain justified inputs and explicitly identify the affected
API subset for mixed findings. Classify justified inputs, confirmed unnecessary
authority, unresolved questions or optional simplifications. A confirmed excess
requires concrete unrelated authority and a narrower input that preserves the
responsibility, error provenance, lifetime and required effects. Test algorithm
correctness, speculative performance claims and repairs remain excluded.

Scenarios: explicit scalars/byte ranges; owned domain state; orchestration owners;
whole Comp versus actual domain services; indirect state/capture/global access;
constructor/default/native ownership; observer/diagnostic IO and latches; cached
reader/session identity; source-versus-instantiation-versus-execution handoffs;
no-production/recursive/fixture-only callers; failure-prefix and restore ownership.
Each adopted row needs independent review and exact input-fact references. Missing
or unread rows stay pending; local disposition counts cannot close the whole audit.

## Current State and Next Action

**Reopened; the whole API input audit is incomplete.** The prior closure treated
classification and finite ownership as sufficient despite unanswered questions.
That closure rule and whole-audit completion claim are withdrawn. The current
[acceptance state](../../../evidence/compiler-api-audit/capability-acceptance.json)
retains the previous checkpoint's exact hashes without accepting its completion
claim under the corrected conditions.

The factual inventory remains complete:1,504 families /199 targets /82,074 primary
lines. [Existing capability decisions](../../../evidence/compiler-api-audit/capability-reconciliation.json)
provide a reviewed first-pass checkpoint:447 J /625 C /419 U /13 O, plus mixed
components and189 finite repair/investigation owners. Zero unclassified families
means classification coverage only, not zero unanswered investigations. Family
counts are not independent bug counts.

Next, use the existing U investigation scopes to resolve all419 main U families
and every mixed U component, following their necessary delegated inputs/effects.
Retain actual evidence and record new findings against exact family/API components;
do not overwrite immutable earlier decisions or count reassignment as resolution.
Existing J/C/O findings and factual/independent receipts remain reusable within
their source identity and stated limits. No product repair or execution occurred.
The completed inventory and useful scope-list corrections are not discarded.

[Substantive answer index](../../../evidence/compiler-api-audit/capability-resolution-index.json)
tracks every original unresolved main/component separately and binds each accepted
answer, independent review and repair owner. Historical first-pass counts above
are not current unresolved totals. Use this index for current investigation state;
closed repair/investigation issue counts alone never establish completion.

[Independent reopening-contract review](../../../evidence/compiler-api-audit/review-reopen-contract.json)
covers these corrected completion conditions and document consistency only; it
does not answer the outstanding API investigations or close the audit.
