# ii-b: Array as a Plew struct over RawBuffer (the flag-day blueprint)

Status: in progress on branch `array-struct`. main has the complete, working ii-a
(Array generic methods + prelude + `.append` in pure Plew; `.count`/`[i]` still
builtin). This file is the concrete target + execution plan for the representation
swap. It is a **destructive flag-day**: an `Array[T]` value has exactly one
representation, so literals / `[i]` / `.count` / `for` / CoW / the compiler's own
arrays all switch together — there is no partial-migration that keeps the suite
green, so it must be done as one coherent change and verified before merging.

## Target (the あるべき姿, in pure Plew, in `std/Prelude.pw`)

```plew
struct Array[T] {
    data: RawBuffer[T]
    pub(get) mut val count: U64   // .count reads this field (no computed property);
                                  // count == len, not redundant data. (A `count()`
                                  // method over a `len` field is equally fine — user
                                  // OK'd either; field is simplest.)
}

impl[T] Array[T] {
    inout fn append(value~: T) {
        val cap: U64 = rawCap(b: self.data)
        if self.count >= cap {
            // grow: alloc a larger buffer, copy, swap. (rawGrow/rawCopy helper.)
        }
        // CoW: if the buffer is shared, copy it private before mutating.
        if rawIsUnique(b: self.data) { } else { /* copy-on-write */ }
        rawStore(b: self.data, i: self.count, v: value)
        self.count = self.count + 1
    }
    fn get(i: U64) -> T {
        if i >= self.count { panic "index out of range" }
        return rawLoad(b: self.data, i: i)
    }
    inout fn set(i: U64, value~: T) {
        if i >= self.count { panic "index out of range" }
        // CoW first, then store.
        rawStore(b: self.data, i: i, v: value)
    }
}
// `xs[i]` desugars to an Index trait method (-> get); `for x in xs` to count+get.
```

Open core-lib details (do at implement time): the empty literal `[]` needs an
empty Array (count 0, data = a 0-cap buffer or a shared static); growth policy
(double, min 4 — same as the current PlewArray push); whether `set`/`append` share
a `makeUnique` helper; whether `data`/`rawAlloc` need return-context inference (A)
for `[]` (no element witness) — likely yes, so **landing return-context inference
(A) is a prerequisite for the empty literal**, or `[]` is special-cased to build a
0-cap Array without rawAlloc.

## Key insight that shrinks the flag-day

Make `Array[T]` a **normal generic struct** (registered from the prelude). Then the
existing machinery handles most of it for free:
- type lowering `Array[I32]` → `Array_I32` (emitMonoStruct), not `PlewArray_I32`.
- `.count` / `.data` → ordinary struct field access.
- value semantics (copy-on-bind, release-on-drop) → the struct machinery already
  retains/releases heap-owning fields; a `RawBuffer` field just needs to be wired
  like a `Ref` field (share/release) — see below.
- methods → ordinary generic method machinery (emitMonoMethods); Array becomes a
  genInst, so `emitArrayMethods` (the ii-a parallel pass) is no longer needed.

So the special-casing that remains is only: **literals `[…]`**, **index `[i]`**,
**`for`**, and **ambient-ness** (the lang-item, no import — already handled).

## Execution order (each step compiles; the swap itself is one commit)

1. **RawBuffer value semantics** (additive, do first, testable alone): mirror `Ref`
   at every share/release site so a `RawBuffer` field/local/capture is retained on
   copy and released on drop. Sites (share = `plew_rawbuf_share`, release =
   `plew_rawbuf_release` — note release frees `p-2`, the block start, NOT `p-1`):
   - capture init share: Expr.pw ~62 (next to the `Ref` case).
   - bind/copy share: Decl.pw ~530 (genCopyValue Ref case).
   - struct field copy/share/release: the `Name_copy`/`_share`/`_release` field loops
     in Decl.pw (find the Ref-field handling, add RawBuffer).
   - local scope-drop release: emitScopeDrops / emitRefRelease (Resolve.pw ~556).
   - closure env drop: Decl.pw ~1087.
   Skip the non-value-semantics `isRefInst` sites (type lowering, pointee field
   access, exprType) — those don't apply to RawBuffer (it's never `->field`'d).
   Test: a RawBuffer bound to two vars then dropped doesn't double-free/leak.
2. **Define `struct Array[T]` + methods in the prelude** (the target above). This
   collides with builtin Array until step 3, so 2+3 land together.
3. **Stop special-casing Array as builtin; route through the struct machinery**:
   - type lowering: remove the `kw:"Array"` → `PlewArray_<E>` cases (Mono.pw ~223,
     emitConcreteCType / genCTypeOf) so Array flows to the generic-struct mangle
     `Array_<E>`. genCElem's Array handling too.
   - `.count`: remove the builtin `.count`→`.len` Field special-case (it becomes a
     normal field read of the struct's `count`).
   - literals `[1,2,3]` / `[]`: construct the struct (alloc RawBuffer, store each,
     set count) instead of PlewArray_new + push loop (Stmt/Expr genArrayValue/
     genArrayLiteral).
   - `[i]`: desugar to the Index method (`.get(i)`).
   - `for x in xs`: iterate via count + get.
   - CoW/value-semantics: drop the PlewArray_copy/share/release special path — the
     struct's RawBuffer field (step 1) now carries it.
   - remove `emitArrayMethods` + the ii-a `Array_<E>_<selector>` dispatch (Array is
     a genInst now; methods go through emitMonoMethods + the normal kind-2 method
     dispatch). Keep `genArrayUserMethod` only if still needed for `[i]`/for lowering.
4. **Remove the PlewArray runtime** (Array.pw genArrayTypedef/genArrayRuntimeFns and
   their callers in _.pw). The array intrinsics (`arrayPush/Get/Set/Len`) either go
   away (replaced by raw* in the methods) or stay as thin shims — prefer removing
   them so the floor is uniformly `RawBuffer`.
5. **Reseed** (twice — codegen output changes), run the full suite + fixpoint, only
   then merge `array-struct` → main.

## Validated + discovered prerequisites (from the `Vec`/`VecI` spike)

✅ **The core value-semantics/CoW is proven** (`tests/run/raw_struct_cow`): a struct
`{ data: RawBuffer; count }` with share-on-bind (RawBuffer retained by step-1 struct
value-semantics) + copy-on-write in `push` (`rawIsUnique` → realloc+copy when shared)
behaves correctly — after `val w = v; v.push(x)`, `w` is unchanged. So the design
holds; the work left is wiring it to the builtin Array syntax.

The spike surfaced **3 prerequisites** that block the *generic, ambient* Array and
must land before step 3:
1. **Return-context type inference (A)** — generic struct construction `<Array …/>`
   where T is hidden inside the `RawBuffer[T]` field (and the empty literal `[]`,
   which has no element witness) can't infer T from the fields; it currently emits
   the bare `(Array){…}` instead of `(Array_I32){…}`. Decision A is already taken
   (design-decisions); it must actually be implemented. Without it, `[]`/construction
   need a witness or a special case.
2. **`pub(get)` field parsing** — `pub(get) mut val count: U64` currently lexes as
   separate `pub` / `(` / `get` / `)` / `count` fields (garbage struct). Needed so
   `.count` is externally readable but internally-only writable. (Plain `mut val
   count` works within a module but isn't the right visibility for an ambient type.)
3. **Sibling method calls on `self`** — `self.helper()` inside a generic struct
   method fails ("no such method on this type"); the spike inlined the helper. Either
   fix self-method dispatch, or keep Array's methods flat (inline the grow/CoW helper
   into append/set).

Recommended order now: implement (A) return-context inference (independently useful,
unblocks empty literals + construction), then `pub(get)` fields, then the step-3 swap.

## Why this is gated, not rushed

The compiler compiles itself with its own arrays; if any array operation breaks
mid-swap it cannot reach a fixpoint, and a bad value-semantics wire is a
use-after-free, not a compile error. So the whole of step 3 lands at once on the
branch and is proven (suite + fixpoint) before touching main. Bootstrap: the seed
(builtin-Array compiler) compiles the new source's array *syntax* fine (syntax is
unchanged); the new compiler emits the struct form; reseed converges as usual.
