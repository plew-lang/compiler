#!/usr/bin/env python3
"""Whole-target checking must not execute, discover concrete bodies, or emit code."""
import argparse
import os
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, default=Path(os.environ.get('PLEWC', ROOT / 'bin/plewc')))
    args = parser.parse_args()
    compiler = args.compiler.absolute()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']
    with tempfile.TemporaryDirectory(prefix='plew check ') as temporary:
        directory = Path(temporary)
        cases = [
            ('not-executed', 'fn main() { panic "application must not run" }', 0),
            ('unused-type-error', 'fn unused[T](value: T) -> I64 { return value } fn main() {}', 1),
            ('unused-global-conflict', 'mut val value = 1I64 fn update(target: inout I64) { target = value } fn unused() { update(target: inout value) } fn main() {}', 1),
        ]
        for name, source, expected in cases:
            path = directory / (name + '.pw')
            path.write_text(source)
            before = set(directory.iterdir())
            result = subprocess.run([*wrapper, str(compiler), '--check', '--trace-phases', str(path)], capture_output=True, text=True)
            assert result.returncode == expected, (name, result.returncode, result.stderr)
            assert result.stdout == '', (name, result.stdout)
            assert not any(marker in result.stderr for marker in ('finalize-callables:start', 'backend:emit:start', 'backend:print-module:start')), result.stderr
            assert 'internal error:' not in result.stderr, result.stderr
            assert set(directory.iterdir()) == before, 'check created output artifacts'
            if expected:
                assert 'plewc: error:' in result.stderr, result.stderr
                built = subprocess.run([*wrapper, str(compiler), '--trace-phases', str(path)], capture_output=True, text=True)
                assert built.returncode == expected and built.stdout == '', (name, built)
                diagnostic = lambda text: [line for line in text.splitlines() if line.startswith('plewc: error:')]
                assert diagnostic(built.stderr) == diagnostic(result.stderr), (name, built.stderr, result.stderr)
                assert 'finalize-callables:start' not in built.stderr, 'build concretized before rejecting a static error'

        for name in ('closure_generic_capture_enum', 'polymorphic_recursion'):
            source = ROOT / 'tests/fixtures' / ('run' if name == 'closure_generic_capture_enum' else 'reject') / (name + '.pw')
            result = subprocess.run([*wrapper, str(compiler), '--check', str(source)], capture_output=True, text=True)
            assert result.returncode == 0 and result.stdout == '' and result.stderr == '', (name, result)
    print('check-command: passed')


if __name__ == '__main__':
    main()
