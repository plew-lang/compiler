#!/usr/bin/env python3
"""Native object progress is independent of expensive per-pass logging."""
import argparse
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--worker', type=Path, required=True)
    args = parser.parse_args()
    worker = args.worker.resolve()
    wrapper = [sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--']
    environment = dict(os.environ, PLEW_LLVM_TRACE='0')

    def run(arguments, *, verbose=False, expected=0):
        result = subprocess.run([*wrapper, str(worker), *map(str, arguments)],
                                env=dict(environment, PLEW_LLVM_TRACE='1' if verbose else '0'),
                                capture_output=True)
        assert result.returncode == expected, (arguments, result.returncode, result.stderr)
        return result

    with tempfile.TemporaryDirectory(prefix='plew-llvm-progress-') as temporary:
        directory = Path(temporary)
        source, output = directory / 'input.ll', directory / 'output.o'
        source.write_text('''@value = global i64 1
 define i64 @choose(i64 %x) {
 entry:
   switch i64 %x, label %other [i64 0, label %zero i64 1, label %one]
 zero: ret i64 3
 one: ret i64 7
 other: %v = load i64, ptr @value
   %n = add i64 %v, %x
   ret i64 %n
 }
 define i32 @main() { ret i32 0 }
''')
        quiet = run([source, output])
        original = output.read_bytes()
        assert quiet.stdout == b'' and quiet.stderr == b'', quiet
        assert run([source, output], verbose=True).stderr == b''
        assert output.read_bytes() == original
        print('PASS llvm-progress quiet and env-only quiet', flush=True)

        progress = run([source, output, '', '--trace'])
        assert progress.stdout == b''
        assert b'Running pass:' not in progress.stderr and b'Executing Pass' not in progress.stderr, progress.stderr
        for stage in ('ir-shared', 'ir-o2', 'codegen'):
            lines = re.findall(rb'\[trace-phase\] llvm:' + stage.encode() + rb' completed=(\d+)([^\n]*)', progress.stderr)
            assert lines and b' done' in lines[-1][1], (stage, progress.stderr)
            counts = [int(count) for count, _ in lines]
            assert counts[-1] > 0 and all(a <= b for a, b in zip(counts, counts[1:])), (stage, counts)
        assert output.read_bytes() == original
        print('PASS llvm-progress bounded IR and codegen checkpoints', flush=True)

        detailed = run([source, output, '', '--trace'], verbose=True)
        assert b'Running pass:' in detailed.stderr and b'Executing Pass' in detailed.stderr, detailed.stderr
        assert b'llvm:codegen completed=' in detailed.stderr
        assert output.read_bytes() == original
        print('PASS llvm-progress verbose opt-in preserves object', flush=True)

        source.write_text('define i32 @main() { ret i32 %missing }')
        for verbose in (False, True):
            output.write_bytes(b'previous artifact')
            broken = run([source, output, '', '--trace'], verbose=verbose, expected=1)
            assert b'error:' in broken.stderr and output.read_bytes() == b'previous artifact'
        print('PASS llvm-progress invalid input preserves diagnostics and output', flush=True)

        source.write_text('define i32 @main() { ret i32 0 }')
        failed = run([source, directory / 'missing/output.o', '', '--trace'], expected=1)
        assert b'output.o' in failed.stderr
        print('PASS llvm-progress output error propagates', flush=True)

        source.write_text('''define i32 @main() sanitize_address {
 entry:
   %p = alloca i32
   store volatile i32 4, ptr %p
   %v = load volatile i32, ptr %p
   ret i32 %v
 }
''')
        sanitized = run([source, output, '', '--trace'])
        assert b'llvm:asan completed=' in sanitized.stderr
        assert b'__asan_' in output.read_bytes()
        print('PASS llvm-progress sanitizer pipeline is retained', flush=True)


if __name__ == '__main__':
    main()
