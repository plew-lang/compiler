# Test layout and ownership

Run the standard profiles from the meta repository: `./validate test`, `gen`,
`deps`, and `asan`. The compiler repository's root shell wrappers remain public
entry points. Each profile has a different contract; passing one does not imply
that the others passed.

## Where tests belong

| Directory | Responsibility | Entry / discovery |
|---|---|---|
| `fixtures/run/` | Executable regression inputs and stdout goldens | normal test; ASan B/C |
| `fixtures/reject/` | Expected compiler rejection; optional diagnostic substring | normal test; ASan B |
| `fixtures/panic/` | Runtime abort and required panic text | normal test; ASan B/D |
| `fixtures/part/`, `fixtures/partreject/` | Multi-module accepted/rejected programs | normal test, `Main.pw` entries |
| `fixtures/gen/`, `fixtures/genreject/` | Macro generation accepted/rejected programs | gen profile |
| `fixtures/genast/` | Input AST generation expectations | gen profile, `compiler/codegen/test-gen-input-ast.sh` |
| `compiler/architecture/` | Implementation responsibility and structural invariants | explicit checks in normal harness |
| `compiler/codegen/` | Generated LLVM, ABI, Mid emission and trace assertions | explicit checks in normal/gen harnesses; exception below |
| `compiler/frontend/` | Focused tests importing the compiler implementation | manual diagnostics; see its README |
| `tooling/` | Runner, watchdog, build/measurement and sanitizer orchestration correctness | normal harness and focused Python/shell checks |
| `sanitizer/` | Sanitizer detection control and raw ownership supplement | ASan E |
| `harness/` | Normal, generation, dependency and ASan suite orchestration | standard profile entry points |

`fixtures/` is shared input, not a claim that every fixture is a language
specification test. Some inputs import compiler internals. Classify by the
assertion's responsibility, not prefixes such as `mid_` or the tool used.

`compiler/codegen/test-mid-return-transfer.py` is a manual diagnostic, not a
standard gate. Its `--asan` option does not instrument Plew LLVM load/store
accesses; use the standard ASan gate for memory-safety evidence. Tooling tests
may also be invoked explicitly; filenames alone do not register a test.
Dependency tests create isolated packages in scratch; their implementation is
`harness/test-deps.sh`, not another copied fixture corpus.

`fixtures/genast/` is not automatically enumerated: adding an input also
requires registering its checks in `compiler/codegen/test-gen-input-ast.sh`.

## Shared inputs and companions

Keep one input and all its companions together. A run fixture requires `.out`;
optional `.in` supplies stdin, `.c` supplies FFI support, `.ll.expect` requires a
literal in emitted LLVM, and `.out.exact` requests byte-exact stdout. Without
`.out.exact`, the normal runner ignores trailing newlines. Auxiliary `.data`
files belong beside their consumer. Panic uses `.panic`; reject may use `.err`.
Multi-module fixtures retain their local imports and support files together.

ASan B compiles the same run/reject/panic inputs with an instrumented compiler.
C/D instrument and execute the generated run/panic programs. They do not replace
normal golden comparison or cover part/gen suites. A self-compiles the compiler.
E instruments the compiler before optimization and compiles the inputs listed
in `sanitizer/asan-ownership-cases.txt`, including self-compilation; the unused
nonvolatile UAF control must be detected. Keep that manifest as references to
shared inputs, never copies. Coverage must not be inferred beyond these sets.

## Adding or changing a test

1. Search existing inputs and assertions for the same behavior and failure
   mechanism, including internal and sanitizer checks.
2. Reuse a fixture for another independent IR/trace assertion when it already
   exercises the required path. Keep runtime verification in the normal suite
   unless the additional execution tests a distinct compiler mode or contract.
3. Add a separate input when it needs a distinct failure, ownership path,
   language construct, or compile mode. Explain that distinction in its comment;
   matching stdout alone neither proves redundancy nor justifies a new copy.
4. Place inputs with companions; place assertions under their owning category.
   Add explicit harness calls for new checker scripts and update this map if
   their suite coverage differs. A manual diagnostic must say it is manual.
5. Update sanitizer E's shared-input manifest for new ownership paths as needed.
   Never substitute compiler crashes for expected rejection, skip missing
   expectations, or weaken instrumentation to make the suite green.
6. For relocation, update every consumer, relative root/import and document.
   Compare the entire input/companion set before and after; keep deletion or
   assertion changes in a separate change. Validate all affected profiles.

Build and diagnostic utilities live in `../scripts/{build,diagnostics,support}/`;
production helpers are not test assertions. Scratch and generated artifacts stay
under ignored `tmp/`, outside committed fixtures.
