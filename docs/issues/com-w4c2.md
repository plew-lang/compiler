---
id: com-w4c2
status: open
deps: []
links: []
created: 2026-10-21T13:11:10Z
type: bug
priority: 1
assignee: Koji Murata
tags: [frontend, verification]
---
# Keep external use bindings file scoped inside part modules

## Contract

Spec15's part rules and [source membership](../design/sources-and-modules.md#4-discovery-membership-and-graph-closure)
share module-defined declarations across root/parts, but external `use` bindings
belong to each file. A module's public surface remains module scoped. Do not
change these semantics to accommodate current tables.

## Source-Confirmed Scope Mismatch

At compiler `78bd9691`, spec `1e0c4d0`, Syntax `00f740e1`, static inspection:

1. Frontend.recordSyntaxImportOrigins registers every root/part import with
   localModule=moduleId, preserving localStart but not a lookup file key.
2. Ir/Modules.pw registerImportOrigin/firstImportOriginNamed index by localModule
   plus NameId; Check/Visibility.pw moduleBindingAt and Resolve/Module.pw
   visibleFreeFunctions use that index without checking the originating file.
3. checkImports also compares duplicate flat names across equal localModule,
   without file membership. Different files independently importing distinct
   non-callable Token declarations can therefore collide in this check.
4. The older isImportedInto helper scans module-wide imports as well. File
   provenance exists in SourceFiles, but these readers do not consume it.

Consequences to reproduce: a part sees an external name imported only by its
root/sibling; two files' separate type/namespace bindings falsely conflict; or
foreign file overloads enter a local candidate set. The scope mismatch is
visible in source; no new compiler execution/user-program failure is claimed.
Existing module-overload set combination/deduplication is intentional within the
correct file scope and must survive the repair.

## Completion Boundary

Retain file-local import-scope identity from discovery through namespace/type/free
function lookup and duplicate checks. Separate it from module declaration/public
surface identity; a generic same-name exception is not a scope repair. Preserve
part forest/use-DAG checks, source origins and qualified/synthetic bindings.
Add root/part/sibling positive and negative controls, independent same-name
imports, overloads, aliases and pub use. Do not add a special part-only visibility
pass after a module-wide selector has already chosen the wrong candidate.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current root/part external bindings, duplicate checks and overload candidate scope. Preserve module public surfaces and repair file identity from admission through final selectors.
