#!/usr/bin/env python3
# Backend variant of methodize.py: methodize the `st: inout LlvmCtx`-receiver free
# functions of a Backend/Llvm file into `pub impl LlvmCtx { }` blocks. Two forms
# become methods (receiver = st; a `c: inout Comp` stays a leading PARAMETER):
#   fn NAME(c: inout Comp, st: inout LlvmCtx, REST) -> R   ->  inout fn NAME(c: inout Comp, REST) -> R
#   fn NAME(st: inout LlvmCtx, REST) -> R                  ->  inout fn NAME(REST) -> R
# Body `st.` -> `self.` (word-boundary). MIXED files handled: `c`-only functions
# (which can't be LlvmCtx methods, and must NOT become `impl Comp` here — that would
# break spec coherence, Comp's module is Frontend) and pure helpers stay free in
# place. Existing `pub impl …` blocks preserved verbatim. Call sites rewritten across
# src. Source order preserved.
#
# Usage: methodize_st.py <file.pw>
import re, sys, glob

SRC = "compiler/src"
path = sys.argv[1]
# optional allow-list (2nd arg, comma-separated): only methodize these names; others
# stay free. For bisecting which function's methodization triggers a codegen bug.
ALLOW = set(sys.argv[2].split(",")) if len(sys.argv) > 2 and sys.argv[2] else None
lines = open(path).read().split("\n")

_decl_re = re.compile(r'^(export |pub )*(struct|enum|trait|newtype|extern|val|mut val)\b')
_bad = [L for L in lines if _decl_re.match(L)]
if _bad:
    print(f"REFUSE: {path} has top-level non-fn declarations that would be dropped:", file=sys.stderr)
    for L in _bad:
        print(f"    {L}", file=sys.stderr)
    sys.exit(2)

# A body-local named `self` collides with the synthesized receiver: the `st`->`self`
# rewrite then resolves `self.field` to the LOCAL (a non-struct value), yielding a
# backend "field access only on a registered struct" error. Refuse so the human
# renames the local first (e.g. `self` -> `promiseSelf`).
_self_local = [L for L in lines if re.search(r'^\s*(mut )?val self\b', L)]
if _self_local:
    print(f"REFUSE: {path} declares a local named `self` (collides with the receiver):", file=sys.stderr)
    for L in _self_local:
        print(f"    {L.strip()}", file=sys.stderr)
    print("Rename the local before methodizing.", file=sys.stderr)
    sys.exit(2)

fn_start = re.compile(r'^(export )?fn ')
impl_start = re.compile(r'^(pub )?impl ')
# (c, st) forms — keep the c parameter, drop st (it becomes self)
cst_ret = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp, st: inout LlvmCtx(, )?(.*)\) -> (.+) \{$')
cst_nor = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp, st: inout LlvmCtx(, )?(.*)\) \{$')
# (st) forms — drop st (becomes self)
st_ret = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(st: inout LlvmCtx(, )?(.*)\) -> (.+) \{$')
st_nor = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(st: inout LlvmCtx(, )?(.*)\) \{$')

def consume_fn(i):
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

def classify(sig):
    # -> (name, exported, newparams, ret) if methodizable, else None
    for rx, hasret, keepc in ((cst_ret, True, True), (cst_nor, False, True),
                              (st_ret, True, False), (st_nor, False, False)):
        m = rx.match(sig)
        if not m:
            continue
        exported = bool(m.group(1)); name = m.group(2); rest = m.group(4)
        if ALLOW is not None and name not in ALLOW:
            return None
        ret = m.group(5) if hasret else None
        if keepc:
            newparams = "c: inout Comp" + (", " + rest if rest else "")
        else:
            newparams = rest
        return (name, exported, newparams, ret)
    return None

segments = []
i = 0
header = []
while i < len(lines) and not (fn_start.match(lines[i]) or impl_start.match(lines[i])):
    header.append(lines[i]); i += 1
segments.append(("header", header))

pending = []
while i < len(lines):
    if impl_start.match(lines[i]):
        block, ni = consume_fn(i)
        segments.append(("raw", pending + block)); pending = []; i = ni
    elif fn_start.match(lines[i]):
        block, ni = consume_fn(i)
        info = classify(block[0])
        if info:
            name, exported, newparams, ret = info
            segments.append(("method", pending, exported, name, newparams, ret, block[1:-1]))
        else:
            segments.append(("raw", pending + block))
        pending = []; i = ni
    else:
        pending.append(lines[i]); i += 1
if pending:
    segments.append(("raw", pending))

def xf(s):  # method body: st. -> self. ; inout st -> inout self (word-boundary)
    s = s.replace("inout st,", "inout self,").replace("inout st)", "inout self)")
    return re.sub(r'\bst\.', 'self.', s)

methodized = []
out = []
impl_open = False
for seg in segments:
    if seg[0] in ("header", "raw"):
        if impl_open:
            out.append("}"); impl_open = False
        out.extend(seg[1])
    else:
        _, pend, exported, name, newparams, ret, body = seg
        if not impl_open:
            if out and out[-1].strip() != "":
                out.append("")
            out.append("pub impl LlvmCtx {"); impl_open = True
        for pl in pend:
            out.append(("    " + pl) if pl.strip() else pl)
        out.append(f"    inout fn {name}({newparams})" + (f" -> {ret} {{" if ret else " {"))
        for bl in body:
            out.append(("    " + xf(bl)) if bl.strip() else bl)
        out.append("    }")
        methodized.append((name, exported))
if impl_open:
    out.append("}")

open(path, "w").write("\n".join(out).rstrip("\n") + "\n")

# rewrite call sites repo-wide (skip `fn …` definition lines).
names = [n for n, _ in methodized]
for f in glob.glob(SRC + "/**/*.pw", recursive=True):
    s = open(f).read(); orig = s
    res = []
    for ln in s.split("\n"):
        if not fn_start.match(ln):
            for n in names:
                ln = re.sub(r'\b' + n + r'\(c: inout (\w+), st: inout (\w+), ', r'\2.' + n + r'(c: inout \1, ', ln)
                ln = re.sub(r'\b' + n + r'\(c: inout (\w+), st: inout (\w+)\)', r'\2.' + n + r'(c: inout \1)', ln)
                ln = re.sub(r'\b' + n + r'\(st: inout (\w+), ', r'\1.' + n + r'(', ln)
                ln = re.sub(r'\b' + n + r'\(st: inout (\w+)\)', r'\1.' + n + r'()', ln)
        res.append(ln)
    s = "\n".join(res)
    if s != orig:
        open(f, "w").write(s)

print("methodized:", ", ".join(f"{n}{'(export)' if e else ''}" for n, e in methodized))
print("exported (drop from Backend import if present):", ", ".join(n for n, e in methodized if e))
