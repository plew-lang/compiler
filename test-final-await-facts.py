#!/usr/bin/env python3
"""Grounded await facts must cover each site without changing generated code."""
from pathlib import Path
import os
import re
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parent
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).resolve()
cases = [('async_basic', 3, 'I64'), ('async_bool', 1, 'Bool'), ('async_control', 3, 'I64')]
with tempfile.TemporaryDirectory(prefix='final-await-', dir=root / 'tmp') as scratch:
    directory = Path(scratch)
    runtime = directory / 'runtime.c'
    runtime.write_bytes(subprocess.check_output([str(compiler), '--runtime'], timeout=55))
    for index, (name, expected_count, payload) in enumerate(cases, 1):
        source = root / 'tests/run' / (name + '.pw')
        results = []
        for flags in (['--require-mid'], ['--require-mid', '--trace-codegen', '--emit-mid-coverage']):
            print(f'final-await {index}/{len(cases)} compile {name} trace={'--trace-codegen' in flags}', file=sys.stderr, flush=True)
            result = subprocess.run([str(compiler), *flags, str(source)], capture_output=True, timeout=55)
            if result.returncode:
                raise SystemExit(result.stderr.decode(errors='replace'))
            results.append(result)
        if results[0].stdout != results[1].stdout:
            raise SystemExit(f'{name}: tracing changed LLVM')
        resumes = set(re.findall(rb'^define[^\n]*@(__af[0-9]+_resume)\(', results[1].stdout, re.M))
        emitted = re.findall(rb'^mid-body symbol=(__af[0-9]+_resume) canonical=[1-9][0-9]*$', results[1].stderr, re.M)
        if not resumes or set(emitted) != resumes or len(emitted) != len(resumes):
            raise SystemExit(f'{name}: every async resume must have exactly one Mid emission record')
        facts = {}
        for line in results[1].stderr.decode().splitlines():
            if not line.startswith('[trace-codegen] final-await '):
                continue
            match = re.fullmatch(r'\[trace-codegen\] final-await body=(\d+) expr=(\d+) promise=(\S+) result=(\S+)', line)
            if not match or int(match[1]) == 0:
                raise SystemExit(f'{name}: malformed await fact: {line}')
            key, types = (match[1], match[2]), (match[3], match[4])
            if key in facts and facts[key] != types:
                raise SystemExit(f'{name}: inconsistent await fact for {key}')
            facts[key] = types
        if len(facts) != expected_count or any(types != (f'Promise[{payload}]', payload) for types in facts.values()):
            raise SystemExit(f'{name}: expected {expected_count} Promise[{payload}] -> {payload} facts, got {facts}')
        llvm, executable = directory / (name + '.ll'), directory / name
        llvm.write_bytes(results[0].stdout)
        subprocess.run(['clang', '-w', str(llvm), str(runtime), '-o', str(executable)], check=True, timeout=55)
        actual = subprocess.check_output([str(executable)], timeout=55)
        if actual.rstrip(b'\n') != source.with_suffix('.out').read_bytes().rstrip(b'\n'):
            raise SystemExit(f'{name}: output mismatch')
        print(f'PASS final-await {name}: {len(facts)} grounded sites', file=sys.stderr, flush=True)
