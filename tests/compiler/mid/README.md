# Parametric Mid diagnostics

`ParametricBodyCoverage.pw` enumerates authored function bodies after the real
frontend has recorded declaration-time facts. It calls `MidFunctionTemplates`
without requesting a concrete body instance, executable Mid, or LLVM generation
for those bodies. Each successful body must retain the same canonical identity
when requested again.

Arguments are an absolute source path, an absolute standard-library directory
with a trailing slash, and optionally `all`. A fourth argument `drops` also
runs the shared ownership rewrite on each parametric body. The default selects the module
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
The `drops` mode also reports `ownership-built` and `ownership-failed`.
A zero process exit alone is not a passing inventory: require both failure
counts to be zero. A cache-identity violation panics. Input-dependent counts are intentionally
not golden outputs.

This is a manual diagnostic outside the normal fixture suite. Successful
conversion does not prove whole-program type/borrow/effect checking, and must
not be reported as completion of `plew check`.

The ownership inventory checks canonical structure, not executable admission.
It retains symbolic type recipes and `try`/`for` branches; implicit conversions,
access materialization, and concrete destruction contracts still belong to
later stages. `tests/fixtures/run/mid_symbolic_drops.pw` independently checks
conditional cleanup and preservation of the immutable source snapshot.

## Declaration-time global effects

`DeclarationAccess.pw` runs the shared global-effect graph over source function, closure and global-initializer
bodies without requesting executable instances for unused declarations.
Compile and link it as above, then run `test-declaration-access.py --probe PATH
--std PATH --out NEW_DIRECTORY`. The cases distinguish unused ordinary
and generic conflicts, transitive calls, nested/generic destruction, disjoint
globals, ownership returned beyond the borrow lifetime, nested closures and
global initialization. Creating a closure alone must not propagate its body effects. The probe also
checks that concrete body, layout, and destruction inventories remain unchanged.

The result retains unresolved call, value, storage and symbolic destruction
obligations. `clear` means no definite conflict in this analysis, not successful
whole-program checking. Obligation discharge remains required before this can supply a checked-program
token. Conflict identity refers to a result node, including synthetic bodies.
