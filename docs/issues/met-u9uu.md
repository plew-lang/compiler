---
id: met-u9uu
status: in_progress
deps: []
links: []
created: 2026-11-24T06:08:52Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, scope]
---
# Preserve lexical type binders during namespace normalization


## Contract and observed defect

Resolve/Lexical normalizes namespace Method/Field before Record; its names environment contains value parameters/locals but omits lexical type binders. A module alias T therefore rewrites generic T.make() into a module free call. Paired source changes only alias T to Module: conflict check/ORC fail opaque mismatch; control succeeds and prints1. Do not freeze this wrong qualifier under met-wp9l.

Preserve canonical lexical type-binder scope during namespace normalization for functions, method/nominal binders, closure bodies and defaults; defaults remain outside value parameters/self. Include nominal field-default binder scope if applicable. Use declaration-owned binder ranges without copied arrays or later rescue lookup; leave real namespace calls/globals and local value precedence unchanged. This finite precedence defect is not the broader successful-binding reader migration owned by com-tr3a.

## Scenarios and completion

New part/NamespaceTypeBinder fixture and API test: function/method/nominal/closure/default T.make remain Method, only main namespace T.make becomes qualified Call, local closure T still wins, main prints1/1/1/1/19/1/99. Alias-only control must be GREEN and conflict RED before fix. Check/AOT/reachable ORC, native normalize-result assertions, normal namespace/alias/value/default controls, fresh candidate and independent review required; no Source/proof query authority added. Parent whole/formal gates stay open. Evidence starts at meta/tmp/phase3-forward-frontier/namespace-type-binder-probe-v1 and namespace-type-binder-matrix-red-v1.

## RED and source repair

Field-default paired probe confirms false acceptance, not only diagnostics: aliasT check/ORC0 and stdout99; aliasModule check/ORC1 Source bounds rejection. The dedicated partreject fixture covers this. New valid part fixture also places a non-generic namespace field default after generic structs to catch leaked binder scope. API native prechange exits-6 with normalization assertion; after Lexical change native0 with exact golden, Method5/qualifiedCall2. Source review has no must-fix; generated default helper actual owner/body preparation is added to the final native check. Fresh build and CLI gates pending. Shared candidate reader extraction is separate commit5c81e676; this product repair changes only Lexical.pw.
