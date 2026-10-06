#!/usr/bin/env python3
"""Source transfers reject successors; analyzed noncontinuation only warns."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
PRELUDE = 'use @Std/Io only { print }\n'
WARNING = 'unreachable code: preceding control flow cannot continue here (spec/11)'
ERROR = 'code after a source control transfer is not allowed (spec/11)'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, default=ROOT / 'bin/plewc')
    compiler = parser.parse_args().compiler.absolute()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']
    # The first ERROR is required. WARN locations are checked on accepted inputs.
    # lazy_unused means run must not demand the invalid/unreachable unused body.
    cases = [
        ('return', '''fn main() {
    return
    print(99I64) // ERROR
}
''', '', False),
        ('give-nested', '''fn main() {
    val value = { val inner = { give 2I64
        print(99I64) // ERROR
    }
    give inner
    }
    print(value)
}
''', '', False),
        ('if-exit', '''fn main() {
    if true { return } else { return }
    print(99I64) // ERROR
}
''', '', False),
        ('match-exit', '''enum Choice { First Second }
fn main() {
    match <Choice.First /> {
        Choice.First => { return }
        Choice.Second => { return }
    }
    print(99I64) // ERROR
}
''', '', False),
        ('continue', '''fn main() {
    while true {
        continue
        print(99I64) // ERROR
    }
}
''', '', False),
        ('break', '''fn main() {
    while true {
        break
        print(99I64) // ERROR
    }
}
''', '', False),
        ('panic', '''fn main() {
    panic("stop")
    print(99I64) // ERROR
}
''', '', False),
        ('empty-match', '''enum Empty {}
fn unused(value: Empty) {
    match value {}
    print(99I64) // ERROR
}
fn main() {}
''', '', True),
        ('conditional-exit', '''fn main() {
    if false { return }
    val value = if true { give 4I64 } else { give 5I64 }
    print(value)
}
''', '4\n', False),
        ('consumed-exits', '''fn main() {
    val value = { give 2I64 }
    print(value)
    while true { break }
    print(3I64)
}
''', '2\n3\n', False),
        ('unused', '''fn unused() {
    return
    print(99I64) // ERROR
}
fn main() {}
''', '', True),
        ('generic', '''fn pick[T](value: T) -> I64 {
    return 6I64
    print(99I64) // ERROR
}
fn main() {
    print(pick(value: 1I64))
    print(pick(value: 1U64))
}
''', '', False),
        ('loop-return', '''fn body() {
    while true { return }
    print(99I64) // WARN
}
fn main() { body() }
''', '', False),
        ('mixed-loop-return', '''fn body(flag: Bool) {
    if flag { return } else { while true {} }
    print(99I64) // WARN
}
fn main() { body(flag: true) }
''', '', False),
        ('loop-warning-unused', '''fn unused() {
    while true {}
    print(99I64) // WARN
}
fn main() {}
''', '', True),
        ('dead-region-transfer', '''fn main() {
    while true {}
    return // WARN
    print(99I64) // ERROR
}
''', '', False),
    ]
    with tempfile.TemporaryDirectory(prefix='plew-unreachable-diagnostics-') as directory:
        for name, body, output, lazy_unused in cases:
            source = PRELUDE + body
            path = Path(directory) / (name + '.pw')
            path.write_text(source)
            warning_lines = [str(i) for i, line in enumerate(source.splitlines(), 1) if '// WARN' in line]
            error_lines = [str(i) for i, line in enumerate(source.splitlines(), 1) if '// ERROR' in line]
            for mode in ('--check', 'build', '--run'):
                result = subprocess.run([*wrapper, str(compiler), *([] if mode == 'build' else [mode]), str(path)], capture_output=True, text=True)
                demanded = mode != '--run' or not lazy_unused
                if error_lines and demanded:
                    assert result.returncode == 1, (name, mode, result.returncode, result.stderr)
                    assert f'plewc: error: {path}:{error_lines[0]}: {ERROR}' in result.stderr, (name, mode, result.stderr)
                    assert 'internal error' not in result.stderr, (name, mode, result.stderr)
                    continue
                assert result.returncode == 0, (name, mode, result.stderr)
                warnings = [line for line in result.stderr.splitlines() if line.startswith(f'plewc: warning: {path}:')]
                expected = warning_lines if demanded else []
                assert warnings == [f'plewc: warning: {path}:{line}: {WARNING}' for line in expected], (name, mode, warnings, expected)
                if mode == '--run':
                    assert result.stdout == output, (name, mode, result.stdout)
                elif mode == '--check':
                    assert not result.stdout, (name, mode, result.stdout)
                else:
                    assert 'define ' in result.stdout, (name, mode, 'missing LLVM')
            print(f'unreachable-diagnostics: {name} passed', flush=True)
    print('unreachable-diagnostics: passed (16 cases, 48 invocations)')


if __name__ == '__main__':
    main()
