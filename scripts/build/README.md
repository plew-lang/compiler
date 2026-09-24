# Compiler and distribution builds

`dev-rebuild.sh` and `bootstrap.sh` remain the development and fixed-point
entries, normally invoked through the meta repository's `validate` command.
They do not publish the standalone distribution or change its resource bundle.

## Single-file candidate

Build distribution libraries with explicit optimization before packaging. A
`Release` label from an arbitrary `llvm-config` does not prove that the archive's
machine code was optimized: a packager may convert LTO bitcode afterward with
different code-generation flags. The pinned source recipe avoids this conversion.

```sh
python3 -B scripts/build/llvm-distribution.py \
  --source-archive /path/to/llvm-project-20.1.1.src.tar.xz \
  --llvm-tools-config /opt/homebrew/opt/llvm/bin/llvm-config \
  --output "$PWD/tmp/optimized-llvm"
```

The source URL is printed by `--help`; its SHA256 is pinned in the script. CMake
and LLVM 20.1.1 build tools are required. LLVM is built with `-O3 -DNDEBUG`, no
LTO conversion, and an explicit macOS SDK. Static libraries and a diagnostic
dylib share the same compiled objects. AArch64, ORC, IR verification, optimization,
and object generation are retained. Optional non-OS compression/XML/editing/FFI
dependencies are disabled. Nothing is installed into Homebrew or the system.
`build.json` records inputs and commands; `build.log` contains actual CMake
compile/link/install progress, monitored with the standard 60-second watchdog.
Use `--jobs` to control build concurrency (default half the CPU cores to limit
C++ build memory). The output directory must be new.

Package using those libraries and matching build-machine tools:

```sh
python3 -B scripts/build/standalone.py --distribution \
  --llvm-config "$PWD/tmp/optimized-llvm/install/bin/llvm-config" \
  --llvm-tools-config /opt/homebrew/opt/llvm/bin/llvm-config \
  --output "$PWD/tmp/standalone/optimized-candidate"
```

`--llvm-config` selects headers and libraries; optional `--llvm-tools-config`
selects build-machine clang/opt of the same LLVM version. These tools are not
runtime dependencies. Use the following only for an explicit external-toolchain
comparison, recording its archive build conditions:

To compare ThinLTO without PGO, pass `--lto thin` to both
`llvm-distribution.py` and `standalone.py`, using new output directories. The LLVM
archives retain bitcode through the final executable link. Matching build-machine
`libLTO.dylib` and `llvm-libtool-darwin` are selected explicitly and fingerprinted;
they are not distributed dependencies. `--jobs` controls LLVM build/ThinLTO
parallelism, and `standalone.py --lto-jobs` controls packaging link parallelism.
The default remains `--lto off` while comparing candidates. ThinLTO pass execution
diagnostics provide actual link progress to the watchdog; package link logs are
saved in `worker-link.log` and `link.log`. No PGO training stage is added.

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
are embedded. The build's `llvm-object` reference worker and intermediate files are not
user dependencies. The carrier emits the compiler object directly; it must
support `--emit-object` (bootstrap older carriers before building a distribution). Omit `--distribution` to build a low-level static `plewc`
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
- `plew --compiler --emit-object output.o [--target-cpu cpu] [options] file.pw`
  emits an optimized native object in the compiler worker. The development CLI
  and `dev-rebuild.sh` use the same direct entry. Default CPU is the host CPU;
  distribution builds explicitly use the recipe CPU.
- `plew --compiler [options] file.pw` is the diagnostic/seed LLVM-text entry;
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
operations. Workers are self-spawned from the same executable. Each worker lowers to an
owned `LlvmModule`, calls the native backend with the live module, then disposes
the module and its context in that order. The parent receives an object file;
there is no LLVM text serialization or parsing on this path. Native linkers see object files, not Plew LLVM IR.
The runtime object is compiled at distribution-build time, never per user build.

## LLVM and evidence

`native/llvm_backend.cpp` provides a borrowed-module API for verification,
optimization, and native PIC object generation. It rejects incompatible target
triples/layouts. `native/llvm_pipeline.h` is shared with the development link
helper; the additional `default<O2>` supplies the subsequent IR optimization
formerly run by clang. The build-machine `llvm_object_main.cpp` worker uses this
same API for explicit LLVM-file tests. Raw fixed-point materials remain text;
ordinary object builds do not generate an intermediate `.ll`. Workers initialize
LLVM machine-pass diagnostics when tracing is enabled. Modules marked
`sanitize_address` are instrumented after optimization; linking those objects
requires the matching ASan runtime.

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
