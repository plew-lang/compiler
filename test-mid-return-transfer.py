#!/usr/bin/env python3
"""Run focused ownership regressions with a chosen compiler, preserving evidence."""
import argparse
import json
import os
import re
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument('--compiler', required=True, type=Path)
parser.add_argument('--output', required=True, type=Path)
parser.add_argument('--asan', action='store_true')
parser.add_argument('--case', action='append', dest='cases')
args = parser.parse_args()
compiler = args.compiler.resolve()
output = args.output.resolve()
output.mkdir(parents=True, exist_ok=False)
clang = '/opt/homebrew/opt/llvm@22/bin/clang' if args.asan else 'clang'
cases = [
    'mid_return_transfer', 'mid_return_bytes_cow', 'mid_return_resource', 'mid_return_resource_nested',
    'mid_free_function_copy_return_cfg_lowering',
    'mid_free_function_move_return_cfg_lowering',
    'mid_any_return_call_box', 'mid_any_generic_return_box',
    'mid_generic_record_owned_return', 'return_owned_local_move_arc',
    'cow_construct_share', 'mid_ownership_dataflow', 'mid_canonical_freeze',
    'mid_default_enum_owner_return',
]
if args.cases:
    cases = args.cases
with (output / 'runtime.c').open('wb') as stream:
    subprocess.run([str(compiler), '--runtime'], stdout=stream, check=True, timeout=55)
results = []
for index, name in enumerate(cases, 1):
    print(f'[return-transfer] {index}/{len(cases)} compile {name}', flush=True)
    source = Path('tests/run') / (name + '.pw')
    artifacts = output / name
    llvm = artifacts / 'compiler.ll'
    environment = os.environ.copy()
    environment.update(PLEWC=str(compiler), SOURCE=str(source.resolve()), OUT_DIR=str(artifacts))
    # The shared observer relays phase/counter progress and enforces the
    # no-progress deadline. A healthy larger fixture has no total-time cutoff.
    compiled = subprocess.run(['./measure-self-compile.sh'], env=environment)
    row = {'case': name, 'compile': compiled.returncode}
    if compiled.returncode == 0:
        flags = ['-O1', '-g', '-fsanitize=address', '-fno-omit-frame-pointer'] if args.asan else ['-O2']
        binary = output / (name + '.bin')
        with (output / (name + '.link.log')).open('wb') as errors:
            linked = subprocess.run([clang, '-w', *flags, str(llvm), str(output / 'runtime.c'), '-L/opt/homebrew/opt/llvm/lib', '-lLLVM', '-o', str(binary)], stderr=errors, timeout=55)
        row['link'] = linked.returncode
        if linked.returncode == 0:
            environment = os.environ.copy()
            if args.asan:
                environment['ASAN_OPTIONS'] = 'detect_leaks=1:halt_on_error=1'
            with (output / (name + '.out')).open('wb') as stream, (output / (name + '.run.log')).open('wb') as errors:
                ran = subprocess.run([str(binary)], stdout=stream, stderr=errors, env=environment, timeout=55)
            row['run'] = ran.returncode
            row['golden_equal'] = (output / (name + '.out')).read_bytes() == source.with_suffix('.out').read_bytes()
    if name == 'mid_return_bytes_cow' and compiled.returncode == 0:
        # This fixture has one raw-buffer-to-Array wrapper (Array.overBuffer).
        # Discover its symbol/type from its ABI, not unstable gf/gs numbering.
        wrappers = [match.group() for match in re.finditer(r'define (%gs[0-9]+) @[^ (]+\(ptr %0\) \{\n.*?\n\}', llvm.read_text(), re.S)
                    if 'insertvalue ' + match.group(1) in match.group()]
        row['buffer_wrapper_count'] = len(wrappers)
        row['minimal_return_arc'] = len(wrappers) == 1 and wrappers[0].count('@plew_rawbuf_retain(') == 1 and not re.search(r'@(?:pwdrop|plew_rawbuf_drop)', wrappers[0])
    row['passed'] = row.get('run') == 0 and row.get('golden_equal') is True and row.get('minimal_return_arc', True)
    results.append(row)
    (output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
    print(f"[return-transfer] {index}/{len(cases)} {'PASS' if row['passed'] else 'FAIL'} {name}", flush=True)
raise SystemExit(0 if all(row['passed'] for row in results) else 1)
