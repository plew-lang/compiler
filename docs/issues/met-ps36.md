---
id: met-ps36
status: in_progress
deps: []
links: [met-3f14]
created: 2026-11-24T09:31:08Z
type: chore
priority: 1
assignee: Koji Murata
tags: [tooling, maintenance]
---
# Clean accumulated scratch without losing development state


## Scope and guarantees

User-authorized one-time disk cleanup, separate from automatic producer-lifetime fix met-3f14. Preserve main tracked/user-modified state, current and explicit comparison carrier bytes with each exact stdlib, latest fixed-point/input snapshot and outstanding normal failure baseline. Before removing old scratch/worktrees, retain HEAD refs, staged/unstaged/untracked and nonregenerable ignored assets in a verified local content-addressed archive; unknown extensions are not discarded. Recognized generated LLVM/object/executable/cache and old traces may be retired after compact measurement/result/source evidence is retained. Never follow symlinks during deletion; changed inputs fail closed. Do not remove branches or main seeds. OS cleanup is limited to inactive project/LLVM temporary entries, not other application state.

## Verification and completion

Inventory and process/open-file checks; archived source/metadata/unknown-asset mode/hash/link roundtrip; exact carrier+stdlib and user-file before/after hashes; change-detection and symlink-escape self-tests; independent safety review before destructive stage and outcome review. Measure reclaimed space, preserve current resumption paths and document kept generated material reasons/expiry. Commit/push compact necessary evidence before deletion. Full ASan/self-host is not necessary for a storage-only operation; selected carrier runtime/stdlib smoke checks suffice. Canonical compact record: meta/evidence/disk-cleanup/2026-11-24/. Local private archive and restore data stay under meta/artifacts/retained/2026-11-24/, outside tmp and outside Git.
