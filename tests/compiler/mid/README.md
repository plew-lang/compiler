# Parametric Mid diagnostics

`ParametricBodyCoverage.pw` enumerates authored function bodies after the real
frontend has recorded declaration-time facts. It calls `MidFunctionTemplates`
without requesting a concrete body instance, executable Mid, or LLVM generation
for those bodies. Each successful body must retain the same canonical identity
when requested again.

Arguments are an absolute source path, an absolute standard-library directory
with a trailing slash, and optionally `all`. The default selects the module
containing main; `all` includes every loaded module. Extern functions and
bodyless declarations are not body requests. Closure bodies are reached through
the production builder; this is not an independent closure completeness audit.

Compile this probe using the selected carrier's `--emit-object` and
`--trace-phases` under `scripts/support/trace-command.py`. Link the object with
that carrier's `--runtime` output using `scripts/support/llvm_link.py`. Keep
artifacts under `tmp/`; do not replace the compiler or seed. Run the resulting
probe under `scripts/support/watch-command.py`.

Stdout ends with `built`, the successful body count, `failed`, and the failed
body count on separate lines. Frontend failures are printed and Mid failures
are traced to stderr; trace output also contains normal builder diagnostics.
A zero process exit alone is not a passing inventory: require `failed` to be
zero. A cache-identity violation panics. Input-dependent counts are intentionally
not golden outputs.

This is a manual diagnostic outside the normal fixture suite. Successful
conversion does not prove whole-program type/borrow/effect checking, and must
not be reported as completion of `plew check`.
