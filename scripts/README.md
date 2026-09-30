# Script layout

Keep the product CLI `plew` at the repository root. Compiler executables live
in `bin/`. Do not add root shell wrappers for scripts that already have an entry
under the directories below.

| Directory | Responsibility | Main entries |
|---|---|---|
| `scripts/build/` | Compiler bootstrap, rebuild and distribution | `bootstrap.sh`, `dev-rebuild.sh`; see [build guide](build/README.md) |
| `scripts/diagnostics/` | Explicit performance, coverage and leak investigations | `measure-self-host.sh`, `measure-self-compile.sh`, `leak-survey.sh` |
| `scripts/support/` | Shared linking, environment and process helpers | Used by build, diagnostics and test runners |
| `tests/harness/` | Test suite orchestration | `test.sh`, `test-gen.sh`, `test-deps.sh`, `asan-gate.sh` |
| `tests/compiler/` | Compiler architecture and generated-code checks | Invoked by harnesses or documented focused diagnostics |
| `tests/tooling/` | Runner and development-tool checks | Invoked by harnesses or directly |

From the meta checkout, prefer `./validate build`, `bootstrap`, `test`, `gen`,
`deps`, and `asan`. From a standalone compiler checkout, use the corresponding
script path above. Run derive generation with `./plew gen <file.pw>`.

Keep test scripts with the behavior they check rather than collecting all
`.sh` files into one directory. Test discovery and ownership are documented in
[the test guide](../tests/README.md). Temporary generated scripts remain in
ignored `tmp/` alongside their experiment artifacts.

`support/progress.sh` only displays elapsed time and the last stderr line for a
manual command. Its timer is not evidence of progress and it does not implement
the mandatory no-progress watchdog; standard gates use the dedicated process
supervisors instead.
