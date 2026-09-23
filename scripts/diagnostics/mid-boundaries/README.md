# Mid boundary smoke (manual)

Uses the shared normal fixtures for generic unique deinit, lexical binder
identity and parenthesized view receivers. The normal and sanitizer suites
also cover these inputs; the manual runner is for focused diagnosis.

From the compiler repository:

```sh
python3 -B scripts/diagnostics/mid-boundaries/check.py --out tmp/mid-boundaries-normal
```

Use a new output directory. `--asan` instruments raw generated LLVM with
LLVM22 before linking. `--cases DIRECTORY` selects another paired `.pw`/`.out`
corpus. Compiler/input hashes, exit codes and exact output are recorded;
the existing watchdog wraps each subprocess. Reject and multi-module coverage
belongs to the standard normal suite.
