# Upstream ticket

Unmodified [wedow/ticket](https://github.com/wedow/ticket) release **v0.3.2**,
commit `266b9d38d5090f1af4e5184afd21b183b3bbe878`, MIT licensed (see LICENSE).
The `ticket` file SHA-256 is
`408f2c113ecc3bc071507593a78386f1b4cc743be6491c9e9f2627efd4d9902b`.

Use [the project entry](../../../issues/tk), which fixes the store independently
of the current directory and any inherited TICKETS_DIR. No global installation,
database, daemon, or network access is needed. Bash and ordinary POSIX utilities
are required; `query` also needs jq. This is a development tool, not a compiler
runtime or distribution dependency.

Updates replace the upstream file and license together, record the new revision
and checksum here, and recheck creation, state changes, filtering, dependencies,
invalid input, and concurrent edits in disposable data. Do not patch upstream
behavior into a project-specific tracker.
