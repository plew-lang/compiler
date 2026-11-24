---
id: met-eqw2
status: in_progress
deps: []
links: []
created: 2026-11-24T02:53:00Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics]
---
# Admit callable declarations as non-value source refusals

Cover assoc_fn_value_arg, named_fn_value_arg and named_fn_value_return. Named expressions already retain Fn binding with valid target0. Associated Field only retains TypeQualifier base, unknown target and no member category: establish actual qualified member identity/category at source admission, rather than treating any qualifier/Field as proof. Reject declarations used as values before unavailable-type compatibility; retain the same cause through retries/cache and owning consumer. Protect callable invocation, closure wrappers, local closure priority, real fields, type qualifiers and static globals. This is non-value declaration admission, not com-l4x2 callable signature checking. Evidence: meta/evidence/rejection-domains/diagnostic-domain-implementation/phase3-value-inference-refusal-investigation.json. Preserve Raw unknown/malformed results as non-Source; no message-based classification, fabricated success receipts, fixture weakening or eager checking of unused ORC bodies. Require producer-to-cache-to-owned-final-consumer assertions, targeted native controls, fresh candidate CLI check/AOT/reachable ORC, structural old-path removal and independent neutral review. Parent whole/formal gates remain open.

## Acceptance Criteria

Existing adopted d2 CLI is RED: all3 required modes reject Unclassified. Add internal Source/Raw/wrong-operation/missing-member/target0 and retained-failure tests before product change; positives must remain GREEN.

