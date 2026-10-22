---
id: com-w4c2
status: closed
deps: []
links: []
created: 2026-10-21T13:11:10Z
type: bug
priority: 1
assignee: Koji Murata
tags: [frontend, verification]
---
# Restrict use to module roots and share their bindings with parts

## Adopted Contract

The module specification and [source membership](../design/sources-and-modules.md#root-owned-use-bindings) now require root-owned use bindings. A module root may declare top-level `use`/`pub use`; its declarations and imported bindings are shared by the root and every transitive part. Handwritten and generated parts may not contain use declarations. No generated-use hoisting, root editing or macro-only visibility exception is adopted. Ordinary duplicate/alias/public-overload rules remain unchanged.

The user adopted this rule after examining `root_import_type_in_part`. Its positive expectation is valid under the adopted contract and must be preserved; do not turn it into a root-import rejection test. The earlier file-local repair direction is superseded by the approved specification change, not by silently accepting an implementation accident. Further macro-specific dependency/hygiene choices are deferred under the linked design's reconsideration conditions.

## Source Evidence and Current Gap

Static inspection at compiler `78bd9691` (rechecked without source edits while recording the new contract): Frontend.recordSyntaxImportOrigins registers root and part imports with localModule and source spans. Ir/Modules.registerImportOrigin/firstImportOriginNamed index module plus NameId; Visibility.moduleBindingAt/checkImports and Resolve/Module.visibleFreeFunctions use those module indices. The older isImportedInto helper likewise queries module imports. This module-scoped lookup shape is suitable for the adopted contract; lack of file-scoped binding tables is no longer a defect.

The previous admission accepted use in parts and Syntax derives emitted imports into generated parts. Implementation 8321aa0e and Syntax 0.1.11-dev.30 close that gap, including saved generated sources and explicit consumer-root support bindings.

## Producer to Final Consumer and Removal

Use parsed structural directives plus established root/part membership to reject misplaced use before registering semantic bindings or admitting the module for lookup. Publish root bindings once into the common module environment; retain source identity for diagnostics and the DAG. All name/namespace/type/function/overload/public-surface consumers use that environment without part-depth or import-origin precedence. Do not add file-local use stores, post-selection part visibility filters, spelling exceptions or a second directive grammar.

Move handwritten part dependencies explicitly into their owning source roots and resolve ordinary alias conflicts there. Update standard macro output to omit target-part use declarations and update consumer roots to supply the documented dependency names. Apply the normal Syntax version/pin workflow when changing that provider. Host provider and harness modules may use dependencies in their own roots; these do not silently become target-root imports. Replaced part-import registration paths must be unreachable for admitted input. New macro/macrointerface public-role syntax is not required by this work.

## Completion and Verification

Preserve root_import_type_in_part and add nested/sibling-part controls proving root names and overload sets are shared independent of traversal order. Reject use/pub use in direct, nested and generated parts with the correct source location; alias or namespace syntax must not bypass placement checks. Test ordinary duplicate/non-callable conflicts, same-declaration deduplication, aliasing, public forwarding, separate-module isolation, use DAG and part-forest preservation.

Exercise generation with support dependencies explicitly present in the consumer root, and clear failure when a required name is absent. Do not exempt old generated imports merely because a receipt exists or a macro emitted them. Inspect the purpose of existing fixtures invalidated by this approved specification change before migrating them; this is permitted specification-migration work under the goal's stop conditions. The original positive root-import fixture requires no semantic change.

## Outcome

Resolved in compiler 8321aa0e/b02fcda6 with Syntax 0.1.11-dev.30. [Saved evidence](../../../evidence/existing-feature-conformance/root-owned-use/README.md) records the producer-to-reader migration, normal suite skip/fail zero, generation suite skip/fail zero, focused raw-IR ASan/LSan, generation-2 LLVM/runtime fixed point and formal median 6.138237 seconds. The existing root-import positive test is preserved. No file-local import store, generated import hoisting, post-selection visibility filter or macro privilege was added. Main/seed promotion and full integration gates remain outside this closed repair.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current module bindings and directive admission under the approved root-only rule, including the corresponding source/generated-output migration. Preserve one module environment and ordinary collision/overload rules. Macro-specific isolation or dependency injection is future design work, not a condition of this repair.
