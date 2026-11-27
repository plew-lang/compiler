---
id: met-7ust
status: closed
deps: []
links: []
created: 2026-11-26T04:29:30Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, verification]
parent: met-iv6d
---
# Define repeated part admission from the same parent


## Adopted decision and completion boundary

The user selected rejection of every second part request, including same-parent
written duplicates and explicit+automatic inclusion. All requests share one
membership admission authority. Multiple macro annotations first aggregate to
one implicit sibling request per source file; they do not produce duplicate
membership requests. Retain source-edge origin for explanatory diagnostics.

Normative contracts: spec15 part restrictions, spec16 automatic inclusion,
and design sources-and-modules§4. No dedup exemption for generated requests.
The reason is one source of membership acceptance and refusal, with annotation
collection separate from edge registration. Product repair remains met-iv6d.

Independent qualified_member_plan accepts spec/design/task alignment, with no
confirmed must-fix. The [scoped source inventory](../../../evidence/rejection-domains/diagnostic-domain-implementation/part-membership-discovery/usage.json)
finds no repeated written target or explicit generated target in compiler/src,
compiler/std or syntax/src; no migration of those product files is indicated.
This lexical survey is not a parser or an audit of arbitrary external sources.
Intentional contrary cases stay as met-iv6d RED/GREEN controls.

The documentation guarantee is complete after signed publication; met-iv6d
owns product implementation, regression and performance gates.
