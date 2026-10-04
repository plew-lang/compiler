#!/usr/bin/env python3
"""Match warnings are nonfatal, source ordered, and shared by check/build/run."""
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
    compiler = parser.parse_args().compiler.absolute()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']
    cases = [
        ('bool', '''use @Std/Io only { print }
fn main() {
    print(match false {
        true => 1I64
        false => 2I64
        false => 3I64
    })
}
''', ['6'], '2\n', 1),
        ('enum', '''use @Std/Io only { print }
enum E { A B }
fn main() {
    print(match <E.A /> {
        E.A => 1I64
        E.A => 2I64
        E.B => 3I64
    })
}
''', ['6'], '1\n', 1),
        ('catchall', '''use @Std/Io only { print }
fn main() {
    print(match 2I64 {
        val value => value
        2I64 => 7I64
        _ => 9I64
    })
}
''', ['5', '6'], '2\n', 2),
        ('effectful-value', '''use @Std/Io only { print }
use @Std/Core only { Eq }
enum E { A B }
mut val calls = 0I64
impl E as Eq {
    assoc fn eq(lhs~: Self, rhs~: Self) -> Bool {
        calls += 1I64
        return calls == 2I64
    }
}
fn main() {
    val expected = <E.A />
    print(match <E.A /> {
        expected => 1I64
        expected => 2I64
        E.B => 3I64
        _ => 4I64
    })
    print(calls)
}
''', [], '2\n2\n', 0),
        ('unused', '''fn unused() -> I64 {
    return match false { true => 1I64 false => 2I64 false => 3I64 }
}
fn main() {}
''', ['2'], '', 0),
        ('generic', '''use @Std/Io only { print }
fn pick[T](value: T) -> I64 {
    return match false { true => 1I64 false => 2I64 false => 3I64 }
}
fn main() {
    print(pick(value: 1I64))
    print(pick(value: 1U64))
}
''', ['3'], '2\n2\n', 1),
    ]
    with tempfile.TemporaryDirectory(prefix='plew-match-diagnostics-') as temporary:
        for name, source, lines, output, lazy_count in cases:
            path = Path(temporary) / (name + '.pw')
            path.write_text(source)
            for mode in ('--check', 'build', '--run'):
                command = [*wrapper, str(compiler), *([] if mode == 'build' else [mode]), str(path)]
                result = subprocess.run(command, capture_output=True, text=True)
                assert result.returncode == 0, (name, mode, result.stderr)
                assert 'internal error:' not in result.stderr, (name, mode, result.stderr)
                warnings = [line for line in result.stderr.splitlines()
                            if line.startswith(f'plewc: warning: {path}:')]
                expected_lines = lines if mode != '--run' else lines[:lazy_count]
                assert len(warnings) == len(expected_lines), (name, mode, warnings, expected_lines)
                for warning, line in zip(warnings, expected_lines):
                    assert warning == f'plewc: warning: {path}:{line}: unreachable match arm: earlier patterns already cover it (spec/11)', warning
                if mode == '--check':
                    assert result.stdout == '', (name, mode, result.stdout)
                elif mode == '--run':
                    assert result.stdout == output, (name, mode, result.stdout)
                else:
                    assert 'define ' in result.stdout, (name, mode, 'missing LLVM output')
    print('match-diagnostics: passed')


if __name__ == '__main__':
    main()
