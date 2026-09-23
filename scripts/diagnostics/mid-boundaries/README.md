# Mid boundary recheck (manual)

These nine inputs describe specification-correct behavior. They are outside
normal fixture discovery while the failures remain unresolved. Do not replace
expected output with an internal error or an incorrect rejection.

From the compiler repository:

```sh
python3 -B scripts/diagnostics/mid-boundaries/check.py --out tmp/mid-boundaries-normal
```

Use a new output directory. The runner records compiler/input hashes, exit
codes, LLVM and stdout/stderr, and uses the existing watchdog for subprocesses.
After repair, move useful regression inputs into the normal corpus.

On main compiler `386812ce`, five controls pass and four inputs fail compilation:

- `view_parenthesized`: Mid preparation internal error. Direct view calls,
  parentheses around the base alone, and parenthesized read-only views pass.
- `generic_deinit`, `generic_deinit_impl`, `generic_deinit_unused`: the declaration
  checker incorrectly rejects deinit as belonging to a non-unique struct.
  A concrete unique struct with deinit and a generic unique struct without
  deinit both pass. The unused declaration also fails, before runtime lowering.

The `.out` files describe successful execution after the defects are fixed.
The diagnostic exits 1 on this baseline. No compiler implementation, seed,
standard fixture registration or verifier is changed by this audit.
