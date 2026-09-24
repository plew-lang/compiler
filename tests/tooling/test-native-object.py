#!/usr/bin/env python3
"""End-to-end embedded LLVM backend checks; run with a built object worker."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--worker', type=Path, required=True)
    parser.add_argument('--compiler', type=Path, default=ROOT / 'plewc')
    parser.add_argument('--runtime-object', type=Path, required=True)
    args = parser.parse_args()
    worker = args.worker.resolve()
    compiler = args.compiler.resolve()
    runtime = args.runtime_object.resolve()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']

    def run(command, expected=0):
        result = subprocess.run([*wrapper, *map(str, command)], capture_output=True)
        if result.returncode != expected:
            raise AssertionError((command, result.returncode, result.stderr.decode(errors='replace')))
        return result

    with tempfile.TemporaryDirectory(prefix='plew-native-object-') as temporary:
        directory = Path(temporary)
        source = directory / 'input.ll'
        object_file = directory / 'output.o'
        invalid_modules = [
            ('syntax', 'not LLVM IR', b'error:'),
            ('target', 'target triple = "wasm32-unknown-unknown"\ndefine i32 @main() { ret i32 0 }', b'requires native triple'),
            ('layout', 'target datalayout = "e-p:32:32"\ndefine i32 @main() { ret i32 0 }', b'incompatible LLVM data layout'),
            ('dominance', 'define i32 @main() {\nentry: br label %end\nbad: %x = add i32 1, 2\nbr label %end\nend: ret i32 %x\n}', b'does not dominate'),
        ]
        for name, text, diagnostic in invalid_modules:
            source.write_text(text)
            object_file.write_bytes(b'previous artifact')
            result = run([worker, source, object_file], expected=1)
            assert diagnostic in result.stderr, (name, result.stderr)
            assert object_file.read_bytes() == b'previous artifact', name
            print(f'PASS native-object reject {name}', flush=True)

        cases = ['run/async_match', 'run/unique_enum_arc', 'run/closure_return_boundaries',
                 'run/cow_gw_field_array_append', 'part/publicapiclosure_reexport/Main']
        for case in cases:
            fixture = ROOT / 'tests/fixtures' / (case + '.pw')
            source.write_bytes(run([compiler, fixture]).stdout)
            run([worker, source, object_file, 'apple-m1'])
            binary = directory / 'app'
            run(['/usr/bin/clang', object_file, runtime, '-o', binary])
            result = run([binary])
            assert result.stdout.rstrip(b'\n') == fixture.with_suffix('.out').read_bytes().rstrip(b'\n'), case
            print(f'PASS native-object execute {case}', flush=True)


if __name__ == '__main__':
    main()
