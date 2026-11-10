#!/usr/bin/env python3
"""The private value ABI is shared by declarations and direct/indirect calls."""
import os
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'bin/plewc')).absolute()
result = subprocess.run([str(compiler), '--require-mid', str(root / 'tests/fixtures/run/mid_value_abi.pw')], capture_output=True, text=True, timeout=55)
if result.returncode:
    raise SystemExit(result.stderr)
llvm = result.stdout
assert re.search(r'^target datalayout = "[^"]+"$', llvm, re.M), 'private ABI planning requires an admitted target data layout before LLVM emission'
attributes = lambda text: re.findall(r'\b(byval|byref)\(([^)]+)\)(?: align (\d+))?', text)
definitions = {}
empty_types = re.findall(r'^(%[\w.]+) = type \{\s*\}', llvm, re.M)
for line in llvm.splitlines():
    match = re.match(r'^define\b.*?@([\w.]+)\((.*)\)\s*\{', line)
    if match:
        definitions[match[1]] = attributes(match[2])
        for empty in empty_types:
            assert not re.search(re.escape(empty) + r'\s', match[2]), 'empty value parameter must have no physical lane'
assert any(definitions.values()), 'no indirect aggregate value parameter was emitted'
assert any(kind == 'byref' for lanes in definitions.values() for kind, _, _ in lanes), 'copyable borrowed aggregates must use guaranteed transport'
assert re.search(r'^define i32 @main\(', llvm, re.M), 'C entry linkage must remain external'
assert not re.search(r'^declare[^\n]*byval', llvm, re.M), 'foreign declarations must keep their C ABI'
checked = 0
for line in llvm.splitlines():
    match = re.search(r'\bcall\b.*?@([\w.]+)\((.*)\)', line)
    if match and match[1] in definitions:
        assert attributes(match[2]) == definitions[match[1]], f'{match[1]}: call/definition aggregate transport disagreement'
        checked += bool(definitions[match[1]])
assert checked, 'fixture must exercise direct aggregate calls'
assert re.search(r'\bcall\b[^\n]*%[\w.]+\([^\n]*byref\(', llvm), 'fixture must exercise indirect guaranteed aggregate calls'
# The normal run suite checks O0 output with mid_value_abi.out.exact.
print(f'PASS value ABI: {checked} direct aggregate calls, indirect calls, physical ABI')

# A field reader must not receive the whole large value after the common passes.
# Snapshot behavior must also survive callbacks, aliasing inout, and escaping values.
import sys
sys.path.insert(0, str(root / 'scripts/support'))
import llvm_link
fixture = root / 'tests/fixtures/run/value_snapshot_callback.pw'
raw = subprocess.check_output([str(compiler), '--require-mid', str(fixture)], text=True, timeout=55)
assert re.search(r'^target triple = "[^"]+"$', raw, re.M), 'native target must be explicit before optimization'
large_types = [name for name, body in re.findall(r'^(%[\w.]+) = type \{ ([^\n]+) \}', raw, re.M) if body.count('i64') >= 12]
readers = []
for aggregate in large_types:
    readers += re.findall(r'^define internal i64 @([\w.]+)\(ptr byref\(' + re.escape(aggregate) + r'\) align \d+ %[\w.]+\)', raw, re.M)
assert len(readers) == 1, 'fixture must contain one large single-field reader'
config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
with tempfile.TemporaryDirectory(prefix='plew-aggregate-argument-') as directory:
    directory = Path(directory)
    source, optimized = directory / 'raw.ll', directory / 'optimized.ll'
    source.write_text(raw)
    runtime = subprocess.check_output([str(compiler), '--runtime'], timeout=55)
    (directory / 'runtime.c').write_bytes(runtime)
    subprocess.run(llvm_link.optimization_command(config, source, optimized), check=True, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, timeout=55)
    reduced = optimized.read_text()
    assert 'target datalayout = ' in reduced, 'layout-sensitive optimization must have a native data layout'
    # Inlining/constant folding may remove the reader entirely. A remaining
    # reader must still have only the projected scalar parameter.
    if '@' + readers[0] + '(' in reduced:
        assert re.search(r'^define internal i64 @' + re.escape(readers[0]) + r'\(i64 [^,)]*\)', reduced, re.M), 'large field reader must receive only its scalar field'
    for material in (source, optimized):
        executable = directory / material.stem
        subprocess.run([llvm_link.selected_clang(config), '-w', '-O0', str(material), str(directory / 'runtime.c'), '-o', str(executable)], check=True, timeout=55)
        assert subprocess.check_output([str(executable)], timeout=55) == fixture.with_suffix('.out').read_bytes(), material
print('PASS aggregate argument reduction: scalar field, callback/inout snapshots, escaping closure, raw and optimized O0 output')

# Three field loads exceed argument promotion's small-element budget. The
# common module cleanup must remove this private snapshot before ASan can turn
# it into an instrumented memcpy. The external sink keeps all fields observable.
with tempfile.TemporaryDirectory(prefix='plew-aggregate-pre-sanitizer-') as directory:
    directory = Path(directory)
    source, optimized, instrumented = (directory / name for name in ('raw.ll', 'optimized.ll', 'asan.ll'))
    triple = re.search(r'^target triple = "[^"]+"$', raw, re.M)[0]
    source.write_text(triple + '\n' + """
%Triple = type { i64, i64, i64 }
declare void @sink(i64, i64, i64)
define internal void @consume(ptr byval(%Triple) %p) sanitize_address {
  %v = load %Triple, ptr %p
  %a = extractvalue %Triple %v, 0
  %b = extractvalue %Triple %v, 1
  %c = extractvalue %Triple %v, 2
  call void @sink(i64 %a, i64 %b, i64 %c)
  ret void
}
define void @entry(ptr %p) sanitize_address {
  call void @consume(ptr byval(%Triple) %p)
  ret void
}
""")
    subprocess.run(llvm_link.optimization_command(config, source, optimized), check=True, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, timeout=55)
    reduced = optimized.read_text()
    assert 'byval(' not in reduced and 'alloca ' not in reduced, 'private field snapshot must disappear before instrumentation'
    assert re.search(r'call void @sink\(', reduced), 'all snapshot fields must remain observable'
    assert 'sanitize_address' in reduced, 'optimization must preserve sanitizer eligibility'
    subprocess.run([llvm_link.optimizer(config), '-passes=asan', '-S', str(optimized), '-o', str(instrumented)], check=True, timeout=55)
    checked = instrumented.read_text()
    assert '__asan_report_load' in checked, 'surviving loads must be instrumented'
    assert not re.search(r'\bcall\b[^\n]*@(?:llvm\.memcpy|__asan_memcpy)', checked), 'ASan must not reintroduce the eliminated snapshot copy'
print('PASS pre-sanitizer aggregate cleanup: observable fields, no snapshot copy, surviving accesses instrumented')

# This source routes one plain value through forward/recursive/generic/default,
# method, closure, witness and suspended async entries. In raw IR the incoming
# synchronous guaranteed home must forward without materializing the aggregate.
fixture = root / 'tests/fixtures/run/mid_guaranteed_indirect_roundtrip.pw'
raw = subprocess.check_output([str(compiler), '--require-mid', str(fixture)], text=True, timeout=55)
pair_types = [name for name, body in re.findall(r'^(%[\w.]+) = type \{ ([^\n]+) \}', raw, re.M)
              if re.fullmatch(r'i64, i64', body)]
assert pair_types, 'missing two-field value layout'
forwarded = recursive = closure_forwarded = False
for aggregate in pair_types:
    if 'byref(' + aggregate + ')' not in raw:
        continue
    assert 'byval(' + aggregate + ')' not in raw, 'copyable Borrow lane still has an ABI copy'
    for match in re.finditer(r'^define internal [^\n]*@([\w.]+)\(([^\n]*)\) \{\n(.*?)^\}', raw, re.M | re.S):
        parameters, body = match[2], match[3]
        lane = re.search(r'ptr byref\(' + re.escape(aggregate) + r'\) align \d+ (%[\w.]+)', parameters)
        if not lane:
            continue
        calls = [line for line in body.splitlines() if re.search(r'\bcall\b', line) and
                 re.search(r'ptr byref\(' + re.escape(aggregate) + r'\) align \d+ ' + re.escape(lane[1]) + r'[,)]', line)]
        if calls:
            assert not re.search(r'\b(?:alloca|load|store) ' + re.escape(aggregate) + r'\b', body), 'forwarding entry still transfers whole value'
            forwarded = True
            recursive |= any('@' + match[1] + '(' in line for line in calls)
            closure_forwarded |= parameters.startswith('ptr %0, ptr byref(')
assert forwarded and recursive and closure_forwarded, 'missing normal/recursive/indirect incoming-home forwarding'
with tempfile.TemporaryDirectory(prefix='plew-guaranteed-transport-') as directory:
    directory = Path(directory)
    source, optimized = directory / 'raw.ll', directory / 'optimized.ll'
    source.write_text(raw)
    (directory / 'runtime.c').write_bytes(subprocess.check_output([str(compiler), '--runtime'], timeout=55))
    subprocess.run(llvm_link.optimization_command(config, source, optimized), check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, timeout=55)
    for material in (source, optimized):
        executable = directory / material.stem
        subprocess.run([llvm_link.selected_clang(config), '-w', '-O0', str(material), str(directory / 'runtime.c'),
                        '-o', str(executable)], check=True, timeout=55)
        assert subprocess.check_output([str(executable)], timeout=55) == fixture.with_suffix('.out').read_bytes(), material
print('PASS guaranteed transport: raw forwarding/recursion/indirect entries and raw/optimized async roundtrip')
