---
id: met-nm1w
status: open
deps: []
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [driver, tooling]
---
# Implement package-native build admission and provenance


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

Spec17 and [Native Build Service Handoff](../design/sources-and-modules.md#native-build-service-handoff)
require validated host/target plans, user-local trust/policy admission, bounded
tool/input/loader execution and provenance-bound artifact publication. Native
FFI declarations and linking the compiler's own LLVM bridge are separate facilities.

[Manifest](../../src/Manifest.pw)::Manifest retains name and Plew dependencies;
parseManifest interprets the dependencies section. [Resolver](../../resolve/Resolver.pw)
handles git/path distribution inputs. [Tool](../../native/tool.cpp) builds and
links the selected source/harness; that route does not consume a package-native
execution plan, policy decision or artifact receipt. No C/Rust/pkg-config
dependency service satisfying the adopted handoff is present in these routes.

## Completion Boundary

Implement manifest/lock plan production, native dependency/tool/loader closure,
host/target identities, explicit local policy, constrained execution, failure
isolation and successful provenance publication through driver and generator
consumers. A lock entry is not trust, and a successful arbitrary cargo process is
not proof of a bounded admitted plan. Recheck unknown manifest sections and target
selection separately; do not silently claim full package-spec coverage from this
bounded inspection. Generated-Plew freshness remains [com-vy62](com-vy62.md).

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: unimplemented or independent release capability**.

Package-native build trust/sandbox/host-target/provenance service is absent, distinct from repairing current git/path resolution and gen harness ownership.
