#!/usr/bin/env python3
"""Check observation records separately from the fail-closed Mid requirement."""
from collections import Counter
import os
from pathlib import Path
import re
import subprocess

FALLBACK = re.compile(r'mid-coverage body=[0-9]+ fn=[0-9]+ name=[A-Za-z][A-Za-z0-9]* category=[a-z-]+(?::[a-z-]+){0,2}')
EMISSION = re.compile(r'mid-body symbol=([A-Za-z0-9_.$-]+) canonical=([1-9][0-9]*)')


def observe(llvm, diagnostics):
    definitions = Counter(re.findall(r'^define\b[^\n]*@([A-Za-z0-9_.$-]+)\(', llvm, re.M))
    emitted = set()
    fallbacks = []
    for line in diagnostics.splitlines():
        if FALLBACK.fullmatch(line):
            if line.endswith('category=preflight:call'):
                raise ValueError('call fallback lacks its closed reason')
            fallbacks.append(line)
            continue
        record = EMISSION.fullmatch(line)
        if not record:
            raise ValueError('unknown or malformed observation: ' + line)
        symbol = record[1]
        if symbol in emitted or definitions[symbol] != 1:
            raise ValueError('Mid emission must identify one LLVM definition: ' + symbol)
        emitted.add(symbol)
    return fallbacks


def check_requirement(fallbacks, status, diagnostics):
    if status != (1 if fallbacks else 0) or diagnostics.splitlines() != fallbacks:
        raise ValueError('required Mid result disagrees with observed fallbacks')


def check_reader():
    llvm = 'define i32 @main() {\nret i32 0\n}\n'
    body = 'mid-body symbol=main canonical=1\n'
    fallback = 'mid-coverage body=1 fn=0 name=main category=eligibility:async\n'
    assert observe(llvm, body + fallback) == [fallback.strip()]
    check_requirement([], 0, '')
    check_requirement([fallback.strip()], 1, fallback)
    for invalid in ['unexpected\n', body + body, body.replace('main', 'missing'), body.replace('=1', '=0'), fallback.replace('eligibility:async', 'preflight:call')]:
        try:
            observe(llvm, invalid)
        except ValueError:
            continue
        raise AssertionError('invalid observation was accepted: ' + invalid)
    for args in [([], 1, ''), ([], 0, body), ([fallback.strip()], 0, fallback), ([fallback.strip()], 1, '')]:
        try:
            check_requirement(*args)
        except ValueError:
            continue
        raise AssertionError('inconsistent requirement was accepted')


def main():
    check_reader()
    root = Path(__file__).resolve().parents[2]
    compiler = str(Path(os.environ.get('PLEWC', root / 'plewc')).resolve())
    source = str(root / 'tests/run/generic_extension_receiver_record_direct_field.pw')
    observed = subprocess.run([compiler, '--emit-mid-coverage', source], cwd=root, capture_output=True, text=True, timeout=55)
    if observed.returncode:
        raise ValueError('coverage compilation failed: ' + observed.stderr)
    fallbacks = observe(observed.stdout, observed.stderr)
    required = subprocess.run([compiler, '--require-mid', source], cwd=root, capture_output=True, text=True, timeout=55)
    check_requirement(fallbacks, required.returncode, required.stderr)
    if not fallbacks and required.stdout != observed.stdout:
        raise ValueError('observation changed LLVM output')
    print('PASS mid-coverage')


if __name__ == '__main__':
    main()
