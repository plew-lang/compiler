#!/usr/bin/env python3
"""Release-free cleanup has no payload load or call to an empty drop witness."""
import os
from pathlib import Path
import re
import subprocess
import sys

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).resolve()
result = subprocess.run(
    [sys.executable, '-B', str(root / 'scripts/support/watch-command.py'), '--',
     str(compiler), str(root / 'tests/fixtures/run/trivial_drop.pw')],
    text=True, capture_output=True, timeout=60,
)
if result.returncode:
    print(result.stderr, file=sys.stderr)
    raise SystemExit('FAIL mid-trivial-drop: compilation failed')
llvm = result.stdout
bodies = re.findall(r'^define [^\n]+\{\n.*?^}', llvm, re.M | re.S)
assert bodies, 'no LLVM function definitions found'
dead = []
for body in bodies:
    uses = re.findall(r'%[0-9]+\b', body)
    for name in re.findall(r'^\s*(%[0-9]+) = load\b', body, re.M):
        if uses.count(name) == 1:
            dead.append((body.splitlines()[0], name))
assert not dead, f'unused cleanup payload loads: {dead}'
assert not re.search(r'call void @pwdrop[^ (]*\(', llvm), 'empty drop witness call remains'
print('PASS mid-trivial-drop')
