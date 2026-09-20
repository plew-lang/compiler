#!/usr/bin/env python3
"""The private value ABI is shared by declarations and direct/indirect calls."""
import os
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[2]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).resolve()
result = subprocess.run([str(compiler), '--require-mid', str(root / 'tests/run/mid_value_abi.pw')], capture_output=True, text=True, timeout=55)
if result.returncode:
    raise SystemExit(result.stderr)
llvm = result.stdout
attributes = lambda text: re.findall(r'\bbyval\(([^)]+)\)', text)
definitions = {}
empty_types = re.findall(r'^(%[\w.]+) = type \{\s*\}', llvm, re.M)
for line in llvm.splitlines():
    match = re.match(r'^define\b.*?@([\w.]+)\((.*)\)\s*\{', line)
    if match:
        definitions[match[1]] = attributes(match[2])
        for empty in empty_types:
            assert not re.search(re.escape(empty) + r'\s', match[2]), 'empty value parameter must have no physical lane'
assert any(definitions.values()), 'no indirect aggregate value parameter was emitted'
assert re.search(r'^define i32 @main\(', llvm, re.M), 'C entry linkage must remain external'
assert not re.search(r'^declare[^\n]*byval', llvm, re.M), 'foreign declarations must keep their C ABI'
checked = 0
for line in llvm.splitlines():
    match = re.search(r'\bcall\b.*?@([\w.]+)\((.*)\)', line)
    if match and match[1] in definitions:
        assert attributes(match[2]) == definitions[match[1]], f'{match[1]}: call/definition byval disagreement'
        checked += bool(definitions[match[1]])
assert checked, 'fixture must exercise direct aggregate calls'
assert re.search(r'\bcall\b[^\n]*%[\w.]+\([^\n]*byval\(', llvm), 'fixture must exercise indirect aggregate calls'
# O0 protects correctness independently of argument promotion/inlining.
with tempfile.TemporaryDirectory(prefix='plew-value-abi-') as directory:
    directory = Path(directory)
    (directory / 'program.ll').write_text(llvm)
    runtime = subprocess.run([str(compiler), '--runtime'], capture_output=True, check=True, timeout=55)
    (directory / 'runtime.c').write_bytes(runtime.stdout)
    subprocess.run(['clang', '-w', '-O0', str(directory / 'program.ll'), str(directory / 'runtime.c'), '-o', str(directory / 'program')], check=True, timeout=55)
    output = subprocess.check_output([str(directory / 'program')], timeout=55)
    assert output == (root / 'tests/run/mid_value_abi.out').read_bytes()
print(f'PASS value ABI: {checked} direct aggregate calls, indirect calls, O0 output')

# A field reader must not receive the whole large value after the common passes.
# Snapshot behavior must also survive callbacks, aliasing inout, and escaping values.
import sys
sys.path.insert(0, str(root / 'scripts/support'))
import llvm_link
fixture = root / 'tests/run/value_snapshot_callback.pw'
raw = subprocess.check_output([str(compiler), '--require-mid', str(fixture)], text=True, timeout=55)
assert re.search(r'^target triple = "[^"]+"$', raw, re.M), 'native target must be explicit before optimization'
large_types = [name for name, body in re.findall(r'^(%[\w.]+) = type \{ ([^\n]+) \}', raw, re.M) if body.count('i64') >= 12]
readers = []
for aggregate in large_types:
    readers += re.findall(r'^define internal i64 @([\w.]+)\(ptr byval\(' + re.escape(aggregate) + r'\) %[\w.]+\)', raw, re.M)
assert len(readers) == 1, 'fixture must contain one large single-field reader'
config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
with tempfile.TemporaryDirectory(prefix='plew-aggregate-argument-') as directory:
    directory = Path(directory)
    source, optimized = directory / 'raw.ll', directory / 'optimized.ll'
    source.write_text(raw)
    (directory / 'runtime.c').write_bytes(runtime.stdout)
    subprocess.run(llvm_link.optimization_command(config, source, optimized), check=True, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, timeout=55)
    reduced = optimized.read_text()
    assert 'target datalayout = ' in reduced, 'layout-sensitive optimization must have a native data layout'
    assert re.search(r'^define internal i64 @' + re.escape(readers[0]) + r'\(i64 [^,)]*\)', reduced, re.M), 'large field reader must receive only its scalar field'
    for material in (source, optimized):
        executable = directory / material.stem
        subprocess.run(['clang', '-w', '-O0', str(material), str(directory / 'runtime.c'), '-o', str(executable)], check=True, timeout=55)
        assert subprocess.check_output([str(executable)], timeout=55) == fixture.with_suffix('.out').read_bytes(), material
print('PASS aggregate argument reduction: scalar field, callback/inout snapshots, escaping closure, raw and optimized O0 output')
