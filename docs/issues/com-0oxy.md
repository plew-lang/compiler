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

Decide the unresolved public boundary with the user, then specify producer-to-consumer eligibility, ABI, ownership, failure, and lifetime checks. Implement/test accepted routes and rejected labeled/capturing/incompatible routes through variables, generic instances, returns and storage. Preserve the common runtime and ordinary demand compilation, without runtime ABI switching.

