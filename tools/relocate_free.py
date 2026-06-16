#!/usr/bin/env python3
# Move every top-level FREE `fn` (with its leading doc-comment block) out of a part
# file into the Frontend module root (compiler/src/Frontend.pw), so the part is left
# with only `impl` blocks (the spec/15 part=impl-only ideal). `impl` blocks, the file
# header, and `import`/`part` lines stay put. Same-module scope, so call sites are
# unchanged. Run per file; build + fixpoint after a batch.
#
# Usage: relocate_free.py [--root <module-root.pw>] [--types] <part-file.pw> [...]
# --root  defaults to the Frontend module root.
# --types also relocate top-level TYPE decls (struct/enum/trait/newtype/extern),
#         not just free `fn` — for a module whose parts still hold types (e.g.
#         @Std/Syntax's AST). Both fns and types are brace-balanced so `consume`
#         segments them identically.
import re, sys

ROOT = "compiler/src/Frontend.pw"
argv = sys.argv[1:]
MOVE_TYPES = False
while argv and argv[0].startswith("--"):
    if argv[0] == "--root":
        ROOT = argv[1]; argv = argv[2:]
    elif argv[0] == "--types":
        MOVE_TYPES = True; argv = argv[1:]
    else:
        sys.exit("unknown flag: " + argv[0])
if MOVE_TYPES:
    movable_start = re.compile(r'^(export )?(fn|struct|enum|trait|newtype|extern) ')
else:
    movable_start = re.compile(r'^(export )?fn ')
fn_start = movable_start
impl_start = re.compile(r'^(pub )?impl ')

def consume(lines, i):
    depth = lines[i].count("{") - lines[i].count("}")
    opened = "{" in lines[i]
    if opened and depth == 0:
        return [lines[i]], i + 1
    block = [lines[i]]; j = i + 1
    while j < len(lines):
        bl = lines[j]; block.append(bl)
        depth += bl.count("{") - bl.count("}")
        if "{" in bl:
            opened = True
        j += 1
        if opened and depth == 0:
            break
    return block, j

moved = []   # relocated free-fn blocks (with leading comments)
for path in argv:
    lines = open(path).read().split("\n")
    out = []; i = 0; pending = []
    # file header (comments/blanks/imports until first fn/impl) stays
    while i < len(lines) and not (fn_start.match(lines[i]) or impl_start.match(lines[i])):
        out.append(lines[i]); i += 1
    while i < len(lines):
        if impl_start.match(lines[i]):
            block, ni = consume(lines, i)
            out.extend(pending); out.extend(block); pending = []; i = ni
        elif fn_start.match(lines[i]):
            block, ni = consume(lines, i)
            # a FREE fn: relocate it (with its leading comment/blank `pending`)
            seg = [pl for pl in pending if pl.strip() != ""] + block
            moved.append("\n".join(seg))
            pending = []; i = ni
        else:
            pending.append(lines[i]); i += 1
    out.extend(pending)
    open(path, "w").write("\n".join(out).rstrip("\n") + "\n")
    print(f"{path}: relocated {sum(1 for m in moved)} cumulative")

if moved:
    root = open(ROOT).read().rstrip("\n")
    block = "\n\n".join(moved)
    root += "\n\n// ---- relocated free helpers (were in parts; kept at module root so parts are impl-only) ----\n\n" + block + "\n"
    open(ROOT, "w").write(root)
print("MOVED:", len(moved), "functions ->", ROOT)
