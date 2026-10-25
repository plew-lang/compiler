---
id: com-nr7y
status: open
deps: []
links: []
created: 2026-10-25T10:39:42Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Reject function returns from global initializer source owners


## Confirmed Review Finding

P1 finding F2 from [com-9hf7](com-9hf7.md).
Production e73a8476, exact candidate073f0375, spec9b3e18d.

**Contract:** spec/11 return exits the enclosing source function; body-checking section4 and compiler-state owner identity. An implementation startup helper is not a user source function.

**Actual:** Global initializer return passes check/AOT. Emitted startup helper returns before storing the global, while main still continues. A closure-local return in a global initializer is valid and passes. No incomplete-startup native execution was attempted.

**Source chain:** `src/Codegen/Resolve/Control.pw:64-69; SourceFacts.pw:581-588; Mid/Build.pw:2608-2645`.

Full minimal source and real outcomes are retained in meta evidence/existing-feature-conformance/source-owner-facts/phase3-specification-rereview.json (source `flow/global-return-branch.pw`); raw scratch is meta/tmp/phase3-current-rereview/.

## Required Finite End State

Represent absence of an enclosing source function for global owners at transfer admission and refuse that return before publication. Preserve legitimate closure returns and actual saved target/cleanup mappings; do not solve this by changing global dependency planning.

Close producer -> saved/publication -> explicit instance -> actual final reader, and remove the superseded semantic decision/writer rather than add a late verifier-only patch. Preserve existing positive and rejecting contracts. Verify decisive new controls and affected modes, then independently review this task and affected area. Final G2a/G2b/G3 remain mandatory, separately owned; no gate, verifier, existing expected output or seven-second condition may be weakened. No new language meaning is required or authorized by this finding.
