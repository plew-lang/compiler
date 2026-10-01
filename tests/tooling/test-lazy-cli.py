#!/usr/bin/env python3
"""Common lazy execution contract: late diagnostics, shared data, args and signals."""
import os
from pathlib import Path
import selectors
import signal
import sys
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get('PLEWC', ROOT / 'bin/plewc')).absolute()
EVIDENCE = ROOT / 'tmp/lazy-build/cli-contract'
EVIDENCE.mkdir(parents=True, exist_ok=True)
with tempfile.TemporaryDirectory(prefix='lazy-cli-', dir=ROOT / 'tmp') as temporary:
    source = Path(temporary) / 'Program.pw'
    def run(name, text, expected, output=None, mode='--run', arguments=()):
        source.write_text(text)
        result = subprocess.run([str(COMPILER), *([mode] if mode else []), str(source), *arguments], capture_output=True, timeout=60)
        (EVIDENCE / (name + '.out')).write_bytes(result.stdout)
        (EVIDENCE / (name + '.err')).write_bytes(result.stderr)
        assert result.returncode == expected, (name, result.returncode, result.stderr.decode())
        if output is not None:
            assert result.stdout == output, (name, result.stdout)
        print('PASS lazy CLI ' + name, flush=True)
        return result
    unused = 'use @Std/Io only { print }\nfn main() { print(42I64) }\nfn unused() { missing() }\n'
    run('unused', unused, 0, b'42\n')
    run('check-unused', unused, 1, mode='--check')
    late = 'use @Std/Io only { eprint }\nfn bad() { missing() }\nfn main() { eprint(text: "entered\\n") bad() }\n'
    failed = run('late-error', late, 1)
    assert failed.stderr.startswith(b'entered\n'), failed.stderr
    # Identical validators must defer body-local uses while retaining whole
    # check/build rejection and eager declaration-signature checks.
    (source.parent / 'Types.pw').write_text('pub struct Hidden { val value: I64 }\n')
    cases = {
        'any-local': 'val x: any Missing = 1I64',
        'any-nested': 'val x: Array[any Missing] = []',
        'any-cast': 'val x = 1I64 as any Missing',
        'any-closure': 'val f = fn(x: any Missing) {}',
        'call-import': 'print(1I64)',
        'type-import': 'val x: Hidden = <Types.Hidden value=1I64 />',
    }
    prefix = 'use @Std/Io only { eprint }\nuse ./Types as Types\n'
    for name, body in cases.items():
        unused = prefix + 'fn main() { eprint(text: "entered\\n") }\nfn bad() { ' + body + ' }\n'
        assert run(name + '-unused', unused, 0).stderr == b'entered\n'
        run(name + '-check', unused, 1, mode='--check')
        run(name + '-build', unused, 1, mode=None)
        late = unused.replace('"entered\\n") }', '"entered\\n") bad() }')
        assert run(name + '-late', late, 1).stderr.startswith(b'entered\n')
        branch = prefix + 'fn main() { eprint(text: "entered\\n") if false { ' + body + ' } }\n'
        assert not run(name + '-branch', branch, 1).stderr.startswith(b'entered\n')
    declaration = prefix + 'fn main() { eprint(text: "entered\\n") }\nfn bad(x: any Missing) {}\n'
    assert not run('declaration-type', declaration, 1).stderr.startswith(b'entered\n')

    # Native exit callbacks run after main returns. Compare the same application
    # via AOT and JIT, including string storage rather than only argc.
    fixture = ROOT / 'tests/compiler/codegen/ExitArguments.pw'
    support = fixture.with_suffix('.c')
    shared = source.parent / ('exit-arguments.dylib' if sys.platform == 'darwin' else 'exit-arguments.so')
    flags = ['-dynamiclib', '-undefined', 'dynamic_lookup'] if sys.platform == 'darwin' else ['-shared', '-fPIC']
    subprocess.run([*shlex.split(os.environ.get('CC', 'clang')), *flags, str(support), '-o', str(shared)], check=True, timeout=60)
    environment = dict(os.environ)
    environment['DYLD_INSERT_LIBRARIES' if sys.platform == 'darwin' else 'LD_PRELOAD'] = str(shared)
    app_arguments = ['one argument', '日本語']
    expected = '3\nexit argc=3: one argument / 日本語\n'.encode()
    result = subprocess.run([str(COMPILER), '--run', str(fixture), *app_arguments], env=environment, capture_output=True, timeout=60)
    assert (result.returncode, result.stdout, result.stderr) == (0, expected, b''), result
    obj = source.parent / 'exit.o'
    runtime = source.parent / 'runtime.c'
    binary = source.parent / 'exit-arguments'
    subprocess.run([str(COMPILER), '--emit-object', str(obj), str(fixture)], check=True, capture_output=True, timeout=60)
    with runtime.open('wb') as output:
        subprocess.run([str(COMPILER), '--runtime'], stdout=output, check=True, timeout=60)
    subprocess.run([*shlex.split(os.environ.get('CC', 'clang')), '-w', str(obj), str(runtime), str(support), '-o', str(binary)], check=True, timeout=60)
    result = subprocess.run([str(binary), *app_arguments], capture_output=True, timeout=60)
    assert (result.returncode, result.stdout, result.stderr) == (0, expected, b''), result
    print('PASS lazy CLI exit callback arguments match AOT', flush=True)
    arguments = 'use @Std/Process only { argCount, argAt }\nuse @Std/Io only { print }\nfn main() { print(argCount()) print(argAt(1I64)) print(argAt(2I64)) }\n'
    run('arguments', arguments, 0, b'3\n--check\none argument\n', arguments=('--check', 'one argument'))
    run('exit-status', 'use @Std/Process only { exit }\nfn main() { exit(code: 7I64) }\n', 7)
    shared = '''use @Std/Io only { print }
trait Value { fn value() -> I64 }
struct Item { val number: I64 }
impl Item as Value { fn value() -> I64 { return self.number } }
fn first() -> any Value { return <Item number=1I64 /> }
fn second() -> any Value { return <Item number=2I64 /> }
fn main() { val a = first() val b = second() print(a.value()) print(b.value()) }
'''
    run('shared-witness', shared, 0, b'1\n2\n')
    source.write_text('use @Std/Io only { eprint }\nuse @Std/Async only { sleep }\nasync fn main() { eprint(text: "ready\\n") while true { await sleep(ms: 100) } }\n')
    for sig in (signal.SIGINT, signal.SIGTERM):
        process = subprocess.Popen([str(COMPILER), '--run', str(source)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            with selectors.DefaultSelector() as ready:
                ready.register(process.stderr, selectors.EVENT_READ)
                assert ready.select(timeout=60), 'application did not start'
            assert process.stderr.readline() == b'ready\n'
            process.send_signal(sig)
            out, err = process.communicate(timeout=10)
            assert process.returncode == -sig, (sig, process.returncode, err)
        finally:
            if process.poll() is None:
                process.kill()
                process.communicate()
        print('PASS lazy CLI ' + sig.name, flush=True)
(EVIDENCE / 'summary.txt').write_text('status=passed\n')
