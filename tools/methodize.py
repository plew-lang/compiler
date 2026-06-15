#!/usr/bin/env python3
# Methodize the `c: inout Comp`-first free functions of a frontend file into one or
# more `pub impl Comp { }` blocks (`fn NAME(c: inout Comp, …)` -> `inout fn NAME(…)`,
# body `c`->`self`), then rewrite call sites `NAME(c: inout RECV, …)` -> `RECV.NAME(…)`
# across src. MIXED files are handled: non-`c`-first free functions (and multi-line
# signatures) are left verbatim and free, in place; only the c-first single-line-sig
# functions become methods. Source order is preserved, so doc comments stay attached.
#
# Usage: methodize.py <file.pw>
# Prints the methodized (exported) names so you can drop them from Backend's import.
import re, sys, glob

SRC = "compiler/src"
path = sys.argv[1]
lines = open(path).read().split("\n")

# Guard: a top-level non-fn declaration (struct/enum/trait/val/...) embedded among
# the functions would be SILENTLY DROPPED — it can't live inside `pub impl Comp`.
# Refuse loudly so the human moves it out first (column-0 keyword = top-level item).
# `impl` is exempt: an existing `pub impl Comp { }` block (e.g. from earlier twin
# work) is preserved verbatim as a raw segment, and new methods join a fresh block.
_decl_re = re.compile(r'^(export |pub )*(struct|enum|trait|newtype|extern|val|mut val)\b')
_bad = [L for L in lines if _decl_re.match(L)]
if _bad:
    print(f"REFUSE: {path} has top-level non-fn declarations that would be dropped:", file=sys.stderr)
    for L in _bad:
        print(f"    {L}", file=sys.stderr)
    print("Move them out (e.g. to the module root) before methodizing.", file=sys.stderr)
    sys.exit(2)

fn_start = re.compile(r'^(export )?fn ')
impl_start = re.compile(r'^(pub )?impl ')
fn_re = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp(, )?(.*)\) -> (.+) \{$')
fn_re_noret = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp(, )?(.*)\) \{$')

def consume_fn(i):
    # Return (block_lines, next_i): lines[i] (the `fn …`/`impl …` line) through its
    # matching closing brace, handling a multi-line signature (the `{` may be later).
    block = [lines[i]]
    depth = lines[i].count("{") - lines[i].count("}")
    opened = depth > 0
    j = i + 1
    while j < len(lines):
        bl = lines[j]; block.append(bl)
        depth += bl.count("{") - bl.count("}")
        if not opened and depth > 0:
            opened = True
        j += 1
        if opened and depth == 0:
            break
    return block, j

# Parse the file into ordered segments: file header, raw blocks (free fns / comments
# kept verbatim), and methodized c-first fns (with their leading comment lines).
segments = []
i = 0
header = []
while i < len(lines) and not (fn_start.match(lines[i]) or impl_start.match(lines[i])):
    header.append(lines[i]); i += 1
segments.append(("header", header))

pending = []  # comment/blank lines since the last fn — attach to the next fn
while i < len(lines):
    if impl_start.match(lines[i]):
        # an existing `impl … { }` block: preserve it verbatim (its methods are
        # already methodized); flush pending comments before it.
        block, ni = consume_fn(i)
        segments.append(("raw", pending + block))
        pending = []
        i = ni
    elif fn_start.match(lines[i]):
        block, ni = consume_fn(i)
        sig = block[0]
        m = fn_re.match(sig); ret = None
        if m:
            ret = m.group(5)
        else:
            m = fn_re_noret.match(sig)
        if m:  # c-first, single-line signature -> a method
            segments.append(("method", pending, bool(m.group(1)), m.group(2), m.group(4), ret, block[1:-1]))
        else:  # non-c-first or multi-line sig -> stays a free function, verbatim
            segments.append(("raw", pending + block))
        pending = []
        i = ni
    else:
        pending.append(lines[i]); i += 1
if pending:
    segments.append(("raw", pending))

def xf(s):  # method body: c. -> self. ; inout c -> inout self
    # `\bc\.` (word-boundary) so a local like `sc.field` / `src.x` is NOT mangled
    # (naive `c.`->`self.` turned `sc.hasCond` into `sself.hasCond`).
    s = s.replace("inout c,", "inout self,").replace("inout c)", "inout self)")
    return re.sub(r'\bc\.', 'self.', s)

methodized = []
out = []
impl_open = False
for seg in segments:
    if seg[0] in ("header", "raw"):
        if impl_open:
            out.append("}"); impl_open = False
        # trim a leading run of blank lines on a raw block right after `}` is cosmetic;
        # keep verbatim (formatting does not affect the fixpoint).
        out.extend(seg[1])
    else:
        _, pend, exported, name, rest, ret, body = seg
        if not impl_open:
            if out and out[-1].strip() != "":
                out.append("")
            out.append("pub impl Comp {"); impl_open = True
        for pl in pend:
            out.append(("    " + pl) if pl.strip() else pl)
        out.append(f"    inout fn {name}({rest})" + (f" -> {ret} {{" if ret else " {"))
        for bl in body:
            out.append(("    " + xf(bl)) if bl.strip() else bl)
        out.append("    }")
        methodized.append((name, exported))
if impl_open:
    out.append("}")

open(path, "w").write("\n".join(out).rstrip("\n") + "\n")

# rewrite call sites repo-wide (INCLUDING the transformed file itself — its own
# intra-file calls, now `NAME(c: inout self, …)`, must become `self.NAME(…)`).
# Skip `fn …` DEFINITION lines so a twin overload's signature in another (mixed)
# file is not mangled into `fn Comp.NAME(…)`; methodize such a partner by hand.
names = [n for n, _ in methodized]
for f in glob.glob(SRC + "/**/*.pw", recursive=True):
    s = open(f).read(); orig = s
    res = []
    for ln in s.split("\n"):
        if not fn_start.match(ln):
            for n in names:
                ln = re.sub(r'\b' + n + r'\(c: inout (\w+)\)', r'\1.' + n + r'()', ln)
                ln = re.sub(r'\b' + n + r'\(c: inout (\w+), ', r'\1.' + n + r'(', ln)
        res.append(ln)
    s = "\n".join(res)
    if s != orig:
        open(f, "w").write(s)

print("methodized:", ", ".join(f"{n}{'(export)' if e else ''}" for n, e in methodized))
print("exported (drop from Backend import if present):", ", ".join(n for n, e in methodized if e))
