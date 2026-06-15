#!/usr/bin/env python3
# Methodize an "all-c" frontend file: every top-level `fn NAME(c: inout Comp, …)`
# becomes an `inout fn NAME(…)` inside one `pub impl Comp { }`, body `c`→`self`;
# then rewrite call sites `NAME(c: inout RECV, …)` → `RECV.NAME(…)` across src.
#
# Usage: methodize.py <file.pw>   (assumes ALL top-level fns take c: inout Comp first)
# Prints the methodized (exported) names so you can drop them from Backend's import.
import re, sys, glob, os

SRC = "compiler/src"
path = sys.argv[1]
text = open(path).read()
lines = text.split("\n")

# Guard: this script only handles "all-c" files (every top-level fn takes
# `c: inout Comp` first). A mixed file would have its non-c fns silently dropped.
_tot = sum(1 for L in lines if re.match(r'^(export )?fn ', L))
_cf = sum(1 for L in lines if re.match(r'^(export )?fn [A-Za-z0-9_]+\(c: inout Comp', L))
if _tot != _cf:
    print(f"REFUSE: {path} is mixed ({_cf}/{_tot} c-first). Handle non-c fns manually.", file=sys.stderr)
    sys.exit(2)

# Guard: a top-level non-fn declaration (struct/enum/trait/val/...) embedded among
# the functions would be SILENTLY DROPPED — the body-collection loop below only
# keeps `fn` blocks. Refuse loudly so the human moves it out first (a struct can't
# live inside `pub impl Comp` anyway). Column-0 keyword = top-level item.
_decl_re = re.compile(r'^(export |pub )*(struct|enum|trait|newtype|extern|impl|val|mut val)\b')
_bad = [L for L in lines if _decl_re.match(L)]
if _bad:
    print(f"REFUSE: {path} has top-level non-fn declarations that would be dropped:", file=sys.stderr)
    for L in _bad:
        print(f"    {L}", file=sys.stderr)
    print("Move them out (e.g. to the module root) before methodizing.", file=sys.stderr)
    sys.exit(2)

fn_re = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp(, )?(.*)\) -> (.+) \{$')
fn_re_noret = re.compile(r'^(export )?fn ([A-Za-z0-9_]+)\(c: inout Comp(, )?(.*)\) \{$')

methodized = []   # (name, exported)
out = []          # leading non-fn lines (header)
bodies = []       # list of (sig_line_replacement, [body lines])
i = 0
# collect leading header (comments / blank) until first fn
while i < len(lines) and not (lines[i].startswith("fn ") or lines[i].startswith("export fn ")):
    out.append(lines[i]); i += 1

while i < len(lines):
    line = lines[i]
    if not (line.startswith("fn ") or line.startswith("export fn ")):
        i += 1
        continue
    m = fn_re.match(line); ret = None
    if m: ret = m.group(5)
    else:
        m = fn_re_noret.match(line)
    if not m:
        print(f"!! SKIP (not c-first or multiline sig): {line}", file=sys.stderr)
        # consume to matching brace to avoid mis-parsing
        i += 1; continue
    exported = bool(m.group(1)); name = m.group(2); rest = m.group(4)
    methodized.append((name, exported))
    newsig = f"    inout fn {name}({rest})" + (f" -> {ret} {{" if ret else " {")
    # gather body until matching close brace (brace count from the sig line's `{`)
    depth = 1; i += 1; body = []
    while i < len(lines) and depth > 0:
        bl = lines[i]
        depth += bl.count("{") - bl.count("}")
        if depth == 0:
            break   # this line is the closing `}` of the fn
        body.append(bl); i += 1
    i += 1  # skip closing brace line
    bodies.append((newsig, body))

# transform bodies: c. -> self. ; inout c -> inout self
def xf(s):
    s = s.replace("inout c,", "inout self,").replace("inout c)", "inout self)")
    s = s.replace("c.", "self.")
    return s

newfile = "\n".join(out).rstrip("\n") + "\n\npub impl Comp {\n"
for sig, body in bodies:
    newfile += sig + "\n"
    for bl in body:
        newfile += ("    " + xf(bl) if bl.strip() else bl) + "\n"
    newfile += "    }\n\n"
newfile = newfile.rstrip("\n") + "\n}\n"
open(path, "w").write(newfile)

# rewrite call sites repo-wide (INCLUDING the transformed file itself — its own
# intra-file calls, now `NAME(c: inout self, …)`, must become `self.NAME(…)`).
names = [n for n, _ in methodized]
for f in glob.glob(SRC + "/**/*.pw", recursive=True):
    s = open(f).read(); orig = s
    for n in names:
        s = re.sub(r'\b' + n + r'\(c: inout (\w+)\)', r'\1.' + n + r'()', s)
        s = re.sub(r'\b' + n + r'\(c: inout (\w+), ', r'\1.' + n + r'(', s)
    if s != orig:
        open(f, "w").write(s)

print("methodized:", ", ".join(f"{n}{'(export)' if e else ''}" for n, e in methodized))
print("exported (drop from Backend import if present):", ", ".join(n for n, e in methodized if e))
