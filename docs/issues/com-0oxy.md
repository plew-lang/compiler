---
id: com-0oxy
status: open
deps: []
links: []
created: 2026-10-13T00:51:00Z
type: task
priority: 3
assignee: Koji Murata
tags: [backend, frontend, runtime]
---
# Complete anonymous-function C boundary design

The specification adopts anonymous-function use-site selection of Plew/C entries, mandatory unlabeled parameters, stable lazy entries where needed, and no named-function-to-value exception. It leaves the C function-pointer type syntax, eligibility through parameters/results/storage, captured environments, supported boundary types, nullability, and handling of pointers received from C unresolved. General context ownership, initialization, thread/reentry, lifetime, and publication still need a boundary contract.

This is deferred design work and unimplemented general interoperability, not a claim that the existing exposed compiler callback is broken. The compiler callback uses an exposed free function and integer ID indexing Dictionary-held MutableRef state, and requires no captured closure conversion.

## Design

[Representation and ABI](../design/representation-and-abi.md#native-external-boundaries); [Driver registry/lifetime](../design/driver-and-execution.md#registry-and-lifetime). Semantic changes require user decision and spec synchronization. Do not derive eligibility from optimization accidentally eliminating a capture; resolve the rule explicitly. Entry reuse must not merge distinct environments.

## Acceptance Criteria

Decide the unresolved public boundary with the user, then specify producer-to-consumer eligibility, ABI, ownership, failure, and lifetime checks. Implement/test accepted and rejected routes under the adopted eligibility, including labeled, capturing and incompatible cases through variables, generic instances, returns and storage. Preserve the common runtime and ordinary demand compilation, without runtime ABI switching.

## Decision Point and Fixed Internal Requirements

Before general public callback implementation, decide function-pointer type syntax, nullability, eligibility through parameters/results/storage and captured-environment handling together. The recommended baseline is a context-free thin pointer with explicit external context/ID, but it is not adopted public syntax or eligibility. These decisions are not prerequisites for the current internal exposed compiler callback or the source-checking remediation.

Existing admitted callbacks consume the common finalized C signature, execution owner, managed gate, startup dependencies, borrow/access checks and code/context lifetime. Preserve those contracts without waiting for a new public API. Arbitrary foreign-thread entry and C-owned runtime startup/unload are deferred to a concrete native API or embedding host with specified synchronization/return/lifetime needs; no automatic attach or first-entry initialization is implied. The owning ABI chapter records this distinction and physical validation conditions.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: unimplemented or independent release capability**.

General anonymous C function-pointer/context eligibility and public syntax remain open/absent. Existing exposed free-function/compiler callback safety is covered by the scalar/pointer child without deciding a new API.
