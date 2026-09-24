# Compiler builds

`dev-rebuild.sh` and `bootstrap.sh` remain the development and fixed-point
entries, normally invoked through the meta repository's `validate` command.

`standalone.py` creates a **static compiler candidate**, not a finished
single-file distribution. It neither changes `plewc` nor promotes the seed.
The initial recipe supports macOS/arm64 and pins LLVM 20.1.1. Build prerequisites
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
comparison materials. Optimization uses the shared development pipeline and
preserves those originals. Compiler/LLVM steps use the existing progress
watchdogs; evidence remains in the output directory. A failed build retains
diagnostic evidence without a success status; retry into a new directory.

Run `python3 -B tests/tooling/test-standalone-build.py` for the dependency audit
unit tests (also in the normal suite). End-to-end acceptance additionally needs
raw self-host output comparison, representative accepted/rejected inputs, and
eventually resource/CLI integration, clean-host validation, and release gates.
