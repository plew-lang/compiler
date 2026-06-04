# Array as a Plew struct over RawBuffer — design record

**Status: done** (merged to main; tags `array-rawbuffer-floor`, `array-plew-struct`).
This keeps the durable *why* of the migration; the step-by-step execution is in the
git history under those tags. The end state:

```plew
// std/Prelude.pw — ambient, no import (like the Array lang-item type / `[…]`)
struct Array[T] {
    mut val data: RawBuffer[T]
    pub(get) mut val count: U64
}
impl[T] Array[T] {
    inout fn append(value~: T) { arrayPush(a: inout self, v: value) }
    fn get(i: U64) -> T { return arrayGet(a: self, i: i) }
    inout fn set(i: U64, value: T) { arraySet(a: inout self, i: i, v: value) }
}
```

`Array[T]` is a real Plew struct: its C typedef (`struct Array_E { E* data;
uint64_t count; }`) comes from this declaration via emitMonoForward/emitMonoStruct,
not a hand-written typedef. This is **Swift's model exactly** — `Array` is a struct,
its methods are thin Plew wrappers over a small *Builtin floor* (`arrayPush`/
`arrayGet`/`arraySet`/`arrayLen`, the `extern "plew-intrinsic"` ops the compiler
lowers to a deep-copy-aware per-element runtime). The floor is the legitimate unsafe
boundary, not a hack.

## Why the methods stay floor-wrappers (not raw-floor-direct)

The tempting "fully pure-Plew methods" (rewrite append/set to use `rawAlloc`/
`rawStore`/`rawCap` directly, like `tests/run/raw_struct_cow`'s `VecI.push`) is
**wrong for the general case**. Array's value semantics (CoW make-unique) need
*element-aware deep copy/release*: a `Ref` element is retained, a struct element is
deep-copied, so a CoW split yields independent elements (else release double-frees).
The raw floor (`rawLoad`/`rawStore`) is type-erased and **shallow** (`b[i]`), so a
pure-Plew CoW over it aliases non-scalar elements. The compiler itself stores
`Array[TypeRef]`, `Array[Bind]` (struct elements with nested arrays), so a shallow
pure-Plew Array would corrupt the compiler's own data. Element-aware deep copy needs
the *type*, which only the compiler can supply (the generated `Array_E_copy/share/
release/unique` runtime). So the floor intrinsics — which encapsulate that runtime —
are the right abstraction; the methods on top are already pure Plew. `get` returns a
`T` by value (the caller's binding deep-copies it), so the read path needs no floor
magic, but the mutating paths do.

This is the same reason Rust's `Vec` has `unsafe`/compiler-special internals behind a
safe API: collection value semantics can't be expressed in the safe surface language.

## Why a representation swap is bootstrap-delicate (the seam)

The compiler compiles itself with its own arrays. A representation swap must be
compilable by the *previous* compiler into a *working* new compiler. The trap:
pure-Plew struct method bodies (`self.data: RawBuffer`, `self.count = …`) are
*mis-compiled* by the old (builtin-`PlewArray`) compiler — it sees `self` as a
`PlewArray` (`.len`, no `.count` store) — so the methods the compiler itself calls
break. The bodies can only be compiled correctly by a struct-aware compiler, which
is the very compiler being built (circular).

The escape is a **stable seam**: keep the method bodies as thin wrappers over the
intrinsic floor (`arrayPush` etc.), which both compilers lower correctly (old →
`PlewArray_E_push`, new → the struct runtime). The migration then went representation-
first (`PlewArray_<E>{data,len,cap,rc}` → RawBuffer-backed `{data,len}` with cap/rc in
the buffer header, tag `array-rawbuffer-floor`), then promoted the builtin type to a
genInst struct from the prelude `struct Array[T]` (tag `array-plew-struct`), each via
reseed ×2. A dormant `isGenericInst(Array)=false` guard let the struct definition land
before the flip without the old compiler double-emitting its methods.

## Containment decisions (why it stayed small)

- Arrays keep the **kind-3 path** for everything but the typedef: literals `[…]`,
  index `[i]`, `for`, `.count`, value semantics, and method dispatch still route
  through the array-special machinery. `exprType` reports an array local / array-
  returning function as **kind 3** even though `Array[E]` is now a genInst — so the
  isGenericInst checks in exprType had to test `isArray` *first* (the one regression
  class the swap introduced).
- Array genInst struct **bodies are emitted before the nominal bodies** (a nominal
  struct like Comp holds arrays by value): `Array_E` is pointer-based, so its element
  only needs a forward declaration, unlike other genInsts which can hold a type by
  value and so stay in the post-order mono pass.
- `Array[U8]` is the lone **hand-written exception**: file paths / `String.bytes`
  need it unconditionally (even when no source mentions `Array[U8]`), so a narrow
  guard keeps it out of the genInst machinery and `genU8ArrayTypedef` always emits it.
- `String.bytes` was a borrowed, header-less `PlewArray_U8` view; value semantics
  (binding shares the buffer, reading its header) forced it to materialize an
  **independent owned `Array[U8]`** by copying — value-semantics-honest, hidden O(n).
- **(A) return-context inference was not needed**: Array values are only built by
  literals, which the compiler lowers with the element type known from context;
  context-free `val xs = []` stays an error (annotation required, Swift-like). It
  remains independently useful → deferred as a separate additive.

## Remaining gap (next harvest)

The element-aware deep copy/release lives in an **array-specific** runtime
(`Array_E_copy/share/release/unique`). Future `RawBuffer`-backed collections
(`Dictionary`, `Set`) need the same — so the next collection work is generalizing it
into a reusable "value semantics for a `RawBuffer` of N `T`s" mechanism the compiler
emits for any such struct, not just Array.
