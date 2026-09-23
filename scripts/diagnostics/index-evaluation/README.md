# Index evaluation audit (manual diagnostic)

These cases specify correct evaluation and writeback behavior, not the known
incorrect output. They are deliberately outside the normal fixture discovery
while the defects are investigated. After repair, move the useful regressions
into the normal corpus rather than maintaining duplicate tests.

From the compiler repository:

```sh
python3 -B scripts/diagnostics/index-evaluation/check.py --out tmp/index-audit-normal
python3 -B scripts/diagnostics/index-evaluation/check.py --asan --out tmp/index-audit-asan
```

Output directories must be new. The runner preserves compiler/input hashes,
LLVM, stdout/stderr and actual exit codes. Every subprocess uses the existing
watchdog. ASan mode uses LLVM22 `opt -passes=asan` on compiler `--asan` output,
checks for instrumentation, and links with the same LLVM22 clang and ASan/LSan.
Override `--llvm-prefix` or `--compiler` explicitly if needed. This is a focused
program audit, not a replacement for the full compiler sanitizer gate.

On compiler `f452c936` (binary SHA256
`aa149015485d7602107eb6fabf4480278ef92c19e3c338d4529aca680d312750`), both modes
exit 1: four executable cases have incorrect output, one fails to compile,
and three controls pass. Accepted cases have no sanitizer diagnostics.

| Case | Expected | Current failure / control |
|---|---|---|
| inout_index | First element becomes 11 | Later argument changes key; second becomes 12 |
| inout_receiver_key | First element becomes 11 | Same issue through an inout method receiver |
| inout_key_during_body | `[11, 2]` | Getter uses key 0, setter uses changed key 1: `[1, 11]` |
| inout_reference_index | Original cell becomes 11 | Later argument rebinds reference; new cell becomes 12 |
| inout_key_call | Key call, later argument, result 11 | Internal error: no frozen Mid input recipe |
| inout_key_control | Saved key remains 0 | Passes |
| inout_reference_control | Non-indexed place retains original cell | Passes |
| local_array_replace | Indexed read retains owned value | Passes even when later argument empties the array |

Expected output files must not be changed to accept the current defect. The
compiler implementation and seed are not modified by this diagnostic.
