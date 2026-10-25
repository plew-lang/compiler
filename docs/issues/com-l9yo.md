---
id: com-l9yo
status: open
deps: []
links: []
created: 2026-10-25T10:39:43Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Check scalar async return completeness at source admission


## Confirmed Review Finding

P2 finding F5 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/04 nonUnit return completeness and admitted scalar Promise result; body-checking source success; diagnostics cause preservation.

**Actual:** async fn action() -> Promise[I64] {} and partial return reject check/build only as internal declaration Mid construction failed. Correct scalar full return succeeds; equivalent synchronous missing return reports ordinary source error. No invalid async execution is claimed.

**Source chain:** `src/Codegen/Check/Return.pw:274; Mid/Build.pw:3514`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `flow/async-Promise-nonunit-fallthrough.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Check the logical inner scalar result contract and execution-completion requirement before successful async source publication. Preserve async frame/runtime separation and valid scalar returns; do not add composite/method/generic async support or merely translate a late Mid error string.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
