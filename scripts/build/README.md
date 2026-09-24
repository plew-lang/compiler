# Compiler builds

`dev-rebuild.sh` and `bootstrap.sh` remain the development and fixed-point
entries, normally invoked through the meta repository's `validate` command.

`standalone.py` creates a **static compiler candidate**, not a finished
single-file distribution. It neither changes `plewc` nor promotes the seed.
The initial recipe supports macOS 26/arm64 and pins LLVM 20.1.1. Build prerequisites
are the matching LLVM development tools/archives, Python, and the OS SDK.
These are build-machine requirements, not promises about user prerequisites.

Example, from the compiler checkout:

```sh
python3 -B scripts/build/standalone.py \
  --llvm-config /opt/homebrew/opt/llvm/bin/llvm-config \
  --static-dependency /opt/homebrew/opt/zstd/lib/libzstd.a \
  --output "$PWD/tmp/standalone/candidate"
```

The output directory must not exist. The recipe does not copy the result of
`llvm-config --system-libs`: that list may include external dynamic libraries.
Explicit support archives are recorded by hash. Any remaining non-OS dynamic
dependency fails the build. The candidate retains a staging symlink to `std/`
until the embedded-resource loader is implemented. The shell CLI and resolver
are not bundled at this stage.

`build.json` records input/compiler/tool/archive hashes, recipe, commands,
pipeline, and output inspection. `compiler.ll` and `runtime.c` are the raw
comparison materials. `native/llvm_backend.cpp` owns in-process optimization
and native PIC object generation through LLVM's API. Its borrowed-module API is
separate from `llvm_object_main.cpp`, a build-machine worker, not another user
distribution requirement. The raw modules remain unchanged on disk.

The first optimization stage shares `native/llvm_pipeline.h` with the development
link helper; `default<O2>` supplies the subsequent IR optimization stage formerly
run by clang. Native target initialization, layout, verification, and object
generation run in the worker. Foreign triples are rejected, not silently
retargeted. The OS clang sees only native objects at final link. Runtime C is
compiled once at distribution-build time. The candidate recipe explicitly uses
Apple M1 and macOS 26; the current zstd archive requires macOS 26, so support for
older systems requires rebuilding distribution dependencies and validation.

Compiler/LLVM steps use the existing progress
watchdogs; evidence remains in the output directory. A failed build retains
diagnostic evidence without a success status; retry into a new directory.

Run `python3 -B tests/tooling/test-standalone-build.py` for the dependency audit
unit tests (also in the normal suite). End-to-end acceptance additionally needs
raw self-host output comparison, representative accepted/rejected inputs, and
eventually resource/CLI integration, clean-host validation, and release gates.

The native object backend has an explicit integration gate:

```sh
python3 -B tests/tooling/test-native-object.py \
  --worker tmp/standalone/candidate/llvm-object \
  --compiler tmp/standalone/candidate/plewc \
  --runtime-object tmp/standalone/candidate/runtime.o
```

It checks malformed IR, incompatible targets, verifier rejection, and observable
behavior for async, ownership, closures, CoW, and imports using only the OS linker.
