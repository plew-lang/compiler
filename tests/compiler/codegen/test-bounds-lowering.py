#!/usr/bin/env python3
"""Check the physical bounds predicate at O0/O2, including signed extremes."""
import os
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
source = root / 'tests/fixtures/run/mid_index_place_runtime_cfg_lowering.pw'
result = subprocess.run([str(compiler), '--require-mid', str(source)], capture_output=True, timeout=55)
if result.returncode:
    raise SystemExit(result.stderr.decode())
llvm = result.stdout.decode()
assert re.search(r'^define internal void @pw_bounds\(', llvm, re.M), 'bounds must be optimizable physical glue'
assert 'call void @pw_bounds' in llvm, 'index projection lost its guard'
# Expose the generated helper to a C driver with dynamic inputs. This also
# checks otherwise unreachable negative counts against the signed contract.
llvm, removed = re.subn(r'^define[^\n]* @main\([^\n]*\) \{\n.*?^\}\n', '', llvm, count=1, flags=re.M | re.S)
assert removed == 1, 'expected exactly one program entry'
llvm += '''\ndefine void @plew_test_bounds(i64 %index, i64 %count) {
  call void @pw_bounds(i64 %index, i64 %count)
  ret void
}
'''
cases = [(0, 1, True), (1, 2, True), (2, 3, True), ((1 << 63) - 2, (1 << 63) - 1, True),
         (-1, 1, False), (0, 0, False), (1, 1, False), (-1, -1, False), (0, -1, False),
         (-(1 << 63), 1, False), ((1 << 63) - 1, (1 << 63) - 1, False)]
with tempfile.TemporaryDirectory(prefix='plew-bounds-') as temporary:
    directory = Path(temporary)
    (directory / 'guard.ll').write_text(llvm)
    (directory / 'runtime.c').write_bytes(subprocess.check_output([str(compiler), '--runtime'], timeout=55))
    (directory / 'driver.c').write_text('''#include <stdlib.h>
extern void plew_test_bounds(long long, long long);
int main(int argc, char **argv) {
  if (argc != 3) return 2;
  plew_test_bounds(strtoll(argv[1], 0, 10), strtoll(argv[2], 0, 10));
  return 0;
}
''')
    for optimization in ('-O0', '-O2'):
        program = directory / ('guard' + optimization)
        subprocess.run(['clang', '-w', optimization, str(directory / 'guard.ll'),
                        str(directory / 'runtime.c'), str(directory / 'driver.c'), '-o', str(program)], check=True, timeout=55)
        for index, count, valid in cases:
            result = subprocess.run([str(program), str(index), str(count)], capture_output=True, timeout=5)
            if valid:
                assert result.returncode == 0 and not result.stderr, (optimization, index, count, result)
            else:
                assert result.returncode != 0 and result.stderr == b'panic: index out of bounds\n', (optimization, index, count, result)
        print(f'PASS bounds {optimization}: {len(cases)} cases', flush=True)
