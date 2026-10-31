---
id: com-9ttw
status: open
deps: [com-7u8z]
links: []
created: 2026-10-21T13:09:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [driver, frontend, verification]
---
# Close dependency resolution over admitted source graphs and constraints

## Adopted Boundary

[Source/package admission](../design/sources-and-modules.md#2-packages-are-not-modules-or-directories)
and spec17 require newest-compatible selection over the admitted dependency
constraints, same-major unification, direct source bindings, the top-level lock
and source-reachable dependency resolution. This is a resolver/admission task,
not the native package executor in met-nm1w or mere CLI parity in met-0139.

## Evidence and Counterchecks

Read-only audit at compiler `78bd9691`, spec `1e0c4d0`:

- `resolve/Resolver.pw::runResolver` queues all root manifest git dependencies,
  then all selected git manifests' git dependencies. It does not construct the
  source-use closure first, nor follow a path dependency's manifest to discover
  its required git dependency on this route.
- `pickLatest` runs per edge before `verKey(url, major)` deduplication. The first
  package for that key is published; later constraints do not revalidate/update
  the selected version. With tags 1.2.0 and 1.3.0 and constraints 1 then 1.2,
  the source algorithm picks 1.3.0 first and skips the later 1.2 candidate even
  though a jointly compatible 1.2.0 exists. This is symbolic source analysis,
  not a network/package fixture execution.
- `Frontend.pw` actually reads entryLock once and passes it to every file's
  resolveGitDepImport; each file supplies its own direct manifest bindings.
  The comment on Manifest.loadLock saying per-package lock use is stale; it
  must not be treated as proof that dependency locks govern target admission.
- Manifest.resolveGitDepImport -> Lock.lockCommitForConstraint checks the
  importing edge against that root lock. It can therefore reject the skipped
  later constraint; this is not silent acceptance of every incompatible version.
  It does not repair failure to find/publish the valid combined resolution.

## Completion Boundary

Make the admitted source graph and accumulated constraints the resolution input;
retain explicit request origins and root-lock provenance through loading. Include
path-to-git edges, unused/dead manifest dependencies, same-major refinement and
incompatibility, different majors, ordering independence and stale root locks.
Do not adopt manifest-wide resolution or silently relax version constraints to
match the existing traversal. Establish fresh local fixed repositories/fixtures
before claiming a demonstrated CLI failure. No compiler code was changed here.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Existing git/path dependency resolution, source-use reachability, joint same-major constraints and top-level lock. Local fixed repos cover path-to-git, unused edges, constraint order, compatible/incompatible versions and cold/warm locks. No native-package executor.

## Test Admission Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) installs required finite repair/investigation prerequisites at this actual admission: com-7u8z (row23). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
