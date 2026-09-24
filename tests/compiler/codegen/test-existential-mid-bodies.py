#!/usr/bin/env python3
"""Require positive Mid emission evidence for every reachable member witness.

Copy/drop vtable glue is audited separately. A fallback-free compilation alone
cannot prove that the member's transfer, conversion and cleanup passed Mid.
"""
import os
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
cases = [
    'any_basic', 'any_self_return', 'any_heap_self_member_return',
    'any_inout', 'mid_existential_call_ownership', 'mid_unit_call_results',
]
with tempfile.TemporaryDirectory(prefix='plew-witness-mid-') as directory:
    for index, name in enumerate(cases, 1):
        output = Path(directory) / (name + '.ll')
        with output.open('w') as stream:
            result = subprocess.run(
                [str(compiler), '--require-mid', '--emit-mid-coverage',
                 str(root / 'tests/fixtures/run' / (name + '.pw'))],
                cwd=root, stdout=stream, stderr=subprocess.PIPE, text=True,
                timeout=55,
            )
        if result.returncode:
            raise SystemExit(result.stderr)
        definitions = re.findall(r'^define\b[^\n]*@(pfvt\d[\w.]*)\(', output.read_text(), re.M)
        evidence = re.findall(r'^mid-body symbol=(\S+) canonical=\d+$', result.stderr, re.M)
        if not definitions:
            raise SystemExit(f'{name}: no member witness; fixture cannot establish coverage')
        for symbol in definitions:
            if evidence.count(symbol) != 1:
                raise SystemExit(f'{name}: {symbol} must have exactly one Mid emission record')
        print(f'[witness-mid] {index}/{len(cases)} PASS {name}: {len(definitions)} member bodies', flush=True)
