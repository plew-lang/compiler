#!/usr/bin/env python3
"""Unreachable suffixes warn without changing checking, execution, or lazy scope."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
PRELUDE = 'use @Std/Io only { print }\n'
MESSAGE = 'unreachable code: preceding control flow cannot continue here (spec/11)'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, default=ROOT / 'bin/plewc')
    compiler = parser.parse_args().compiler.absolute()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']
    # WARN marks the first statement in each unreachable suffix.
    cases = [
        ('return', '''fn main() {
    print(1I64)
    return
    print(99I64) // WARN
    print(100I64)
}
''', '1\n', None),
        ('give-nested', '''fn main() {
    val value = { val inner = { give 2I64
        print(99I64) // WARN
    }
    print(inner)
    give 3I64
    print(99I64) // WARN
    }
    print(value)
}
''', '2\n3\n', None),
        ('if-exit', '''fn main() {
    if true { return } else { return }
    print(99I64) // WARN
}
''', '', None),
        ('match-exit', '''enum Choice { First Second }
fn main() {
    match <Choice.First /> {
        Choice.First => { return }
        Choice.Second => { return }
    }
    print(99I64) // WARN
}
''', '', None),
        ('loop-exits', '''fn main() {
    mut val count = 0I64
    while count < 2I64 {
        count += 1I64
        continue
        print(99I64) // WARN
    }
    while true {
        break
        print(99I64) // WARN
    }
    print(count)
}
''', '2\n', None),
        ('conditional-exit', '''fn main() {
    if false { return }
    val value = if true { give 4I64 } else { give 5I64 }
    print(value)
}
''', '4\n', None),
        ('unused', '''fn unused() {
    return
    print(99I64) // WARN
}
fn main() {}
''', '', 0),
        ('generic', '''fn pick[T](value: T) -> I64 {
    return 6I64
    print(99I64) // WARN
}
fn main() {
    print(pick(value: 1I64))
    print(pick(value: 1U64))
}
''', '6\n6\n', None),
    ]
    with tempfile.TemporaryDirectory(prefix='plew-unreachable-diagnostics-') as directory:
        for name, body, output, lazy_count in cases:
            source = PRELUDE + body
            path = Path(directory) / (name + '.pw')
            path.write_text(source)
            lines = [str(index) for index, line in enumerate(source.splitlines(), 1) if '// WARN' in line]
            for mode in ('--check', 'build', '--run'):
                command = [*wrapper, str(compiler), *([] if mode == 'build' else [mode]), str(path)]
                result = subprocess.run(command, capture_output=True, text=True)
                assert result.returncode == 0, (name, mode, result.stderr)
                warnings = [line for line in result.stderr.splitlines() if line.startswith(f'plewc: warning: {path}:')]
                expected = lines if mode != '--run' or lazy_count is None else lines[:lazy_count]
                assert warnings == [f'plewc: warning: {path}:{line}: {MESSAGE}' for line in expected], (name, mode, warnings, expected)
                if mode == '--run':
                    assert result.stdout == output, (name, mode, result.stdout)
                elif mode == '--check':
                    assert not result.stdout, (name, mode, result.stdout)
                else:
                    assert 'define ' in result.stdout, (name, mode, 'missing LLVM')
            print(f'unreachable-diagnostics: {name} passed', flush=True)
    print('unreachable-diagnostics: passed')


if __name__ == '__main__':
    main()
