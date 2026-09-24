# Compiler and distribution builds

`dev-rebuild.sh` and `bootstrap.sh` remain the development and fixed-point
entries, normally invoked through the meta repository's `validate` command.
They do not publish the standalone distribution or change its resource bundle.

## Single-file candidate

From the compiler checkout:

```sh
python3 -B scripts/build/standalone.py --distribution \
  --llvm-config /opt/homebrew/opt/llvm/bin/llvm-config \
  --static-dependency /opt/homebrew/opt/zstd/lib/libzstd.a \
  --static-license /opt/homebrew/opt/zstd/LICENSE \
  --output "$PWD/tmp/standalone/candidate"
```

The output directory must not exist. `plew` is the only user executable to copy
out of that directory. Compiler, resolver, LLVM optimization/object generation,
standard sources, runtime object, version identity, and dependency license texts
are embedded. The build's `llvm-object` worker and intermediate files are not
user dependencies. Omit `--distribution` to build a low-level static `plewc`
candidate with a staging `std/` symlink instead.

The initial recipe targets **macOS 26/arm64**, Apple M1, and LLVM 20.1.1. Build
prerequisites are Python 3.11+, the matching LLVM development tools/archives,
explicit support archives/licenses, and the OS SDK. The current zstd archive
requires macOS 26. Supporting older systems requires rebuilding the distribution
libraries and validating that target; changing only the deployment flag is not
sufficient. The builder rejects remaining non-OS dynamic dependencies and does
not copy the potentially dynamic flags from `llvm-config --system-libs`.

User operations require no LLVM installation, Python, adjacent standard library,
or separate compiler/resolver. Native linking uses the OS C toolchain/SDK
(`/usr/bin/cc`, or a compiler executable selected by `CC`). Git dependencies still
need git and the package cache; these project dependencies are not bundled.
Installation and tool-version management belong to external tools such as mise.
The executable can also be installed directly.

## Commands and boundaries

- `plew build file.pw [-o output]`, or `plew file.pw`, builds a native executable.
- `plew run file.pw [args...]` retains the current AOT compile-and-run behavior.
  The separately planned lazy run/check/Hot Restart implementation is not supplied
  by this packaging work.
- `plew gen file.pw...` and `plew resolve [directory|file]` share the existing
  Plew macro compiler and resolver. Outputs are replaced only after success.
- `plew --compiler [options] file.pw` is the low-level LLVM-text compiler entry;
  `--compiler --runtime` emits the C runtime. A `plewc` symlink selects this mode
  for existing development/test scripts.
- `plew --version` identifies the bundled inputs and LLVM version;
  `plew --licenses` prints the included dependency notices.
- `PLEW_STD=/explicit/directory` chooses checkout sources. Otherwise `@Std` uses
  immutable embedded sources under the diagnostic namespace `plew:std/`.
  Missing embedded sources never fall back to a neighboring filesystem tree.
- `PLEW_TRACE_BUILD=1` enables compiler/LLVM pass progress for supervised builds.

Compiler semantics and resolution remain in Plew modules. `distribution/_.pw`
selects their worker entries; `native/tool.cpp` owns OS process, output, and linker
operations. Workers are self-spawned from the same executable, so compiler state
is reclaimed at process exit. Native linkers see object files, not Plew LLVM IR.
The runtime object is compiled at distribution-build time, never per user build.

## LLVM and evidence

`native/llvm_backend.cpp` provides a borrowed-module API for verification,
optimization, and native PIC object generation. It rejects incompatible target
triples/layouts. `native/llvm_pipeline.h` is shared with the development link
helper; the additional `default<O2>` supplies the subsequent IR optimization
formerly run by clang. The build-machine `llvm_object_main.cpp` worker uses this
same API. Raw fixed-point materials are preserved on disk.

`build.json` records compiler/source/dependency/tool/archive/license hashes,
recipe, commands, pipeline, and output inspection. Compiler/LLVM steps use the
existing progress watchdogs. Failed builds retain diagnostic evidence without a
success status; retry into a new output directory. Canonical compiler and seed
are never overwritten. A successful candidate build is not a signed public
release or proof of compatibility with another machine.

Focused gates:

```sh
python3 -B tests/tooling/test-standalone-build.py
python3 -B tests/tooling/test-native-object.py \
  --worker tmp/standalone/candidate/llvm-object \
  --compiler ./plewc \
  --runtime-object tmp/standalone/candidate/runtime.o
python3 -B tests/tooling/test-distribution.py \
  --binary tmp/standalone/candidate/plew \
  --evidence tmp/standalone/relocation-check
```

The distribution gate copies only the executable and uses an OS-only PATH. It
checks resources, CLI behavior, output preservation, and macro generation. This
local isolation test complements the dynamic dependency audit; it does not
replace clean-host, minimum-OS, signing/notarization, full-suite, sanitizer, and
self-host validation before release/promotion.
