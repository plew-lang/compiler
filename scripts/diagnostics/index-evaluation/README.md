# Focused index evaluation checks

The normal corpus `tests/fixtures/run/index_evaluation_*.pw` covers preparation
of index keys and reference owners, reverse writeback, ordinary key calls,
nested keys, generic call instances, custom owned keys, and normal-read controls.
Expected output follows the specification; the runner uses the same fixtures.

From the compiler repository:

```sh
python3 -B scripts/diagnostics/index-evaluation/check.py --out tmp/index-normal
python3 -B scripts/diagnostics/index-evaluation/check.py --asan --out tmp/index-asan
```

Output directories must be new. Compiler/input hashes, LLVM, stdout/stderr and
exit codes are preserved. Each subprocess uses the existing watchdog. ASan mode
uses LLVM22 instrumentation and ASan/LSan linking. This focused check does not
replace the full compiler sanitizer gate.
