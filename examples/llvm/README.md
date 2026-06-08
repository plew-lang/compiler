# examples/llvm — driving libLLVM-C from Plew (FFI first light)

Plew building **real LLVM IR** through the LLVM-C API, entirely via Plew's
`extern(c)` FFI (spec/15 "外部コード統合"). This is the groundwork for an LLVM
backend: the same bindings the backend will use to emit IR.

- **`Llvm.pw`** — hand-written `extern(c)` bindings for a focused IR-construction
  subset of `<llvm-c/Core.h>` (opaque handles + builder API). Raw/unsafe floor;
  positional (C has no labels). 1:1 with the header — a future `bindgen` could
  generate it.
- **`BuildAdd.pw`** — builds `i32 add(i32, i32) { ret a + b }` and prints its IR.

## Build & run

The compiler self-emits C prototypes/typedefs from the `extern(c)` declarations,
so **no libLLVM header (`#include`) is needed** — only linking. (Requires LLVM
installed, e.g. `brew install llvm`.)

```sh
LC=$(brew --prefix llvm)/bin/llvm-config        # or: which llvm-config
compiler/plewc examples/llvm/BuildAdd.pw > /tmp/build_add.c
clang /tmp/build_add.c $("$LC" --ldflags --libs core) \
      -Wl,-rpath,"$("$LC" --libdir)" -o /tmp/build_add
/tmp/build_add
```

Expected output (verified against Homebrew LLVM 22):

```llvm
; ModuleID = 'plew'
source_filename = "plew"

define i32 @add(i32 %0, i32 %1) {
entry:
  %sum = add i32 %0, %1
  ret i32 %sum
}
```

## What it exercises

- Opaque foreign handles — `extern(c) { type LLVMModuleRef }` → `typedef void*`.
- Raw C pointers — `CPtr[U8]` (`const char*`) and `CPtr[LLVMTypeRef]` (handle
  array for `LLVMFunctionType`'s param list).
- `@Std/Ffi` boundary helpers — `cString` / `stringFromCString` / `arrayCPtr`.
- Positional `extern(c)` calls (no argument labels).
- Cross-module bindings (`export extern(c)` in `Llvm.pw`, imported by `BuildAdd.pw`).

Linking against the **real** libLLVM is just the link line above; the Plew code
is unchanged from how it ran against a local stub during bring-up.
