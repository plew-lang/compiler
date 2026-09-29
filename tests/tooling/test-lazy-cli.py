#!/usr/bin/env python3
"""Common lazy execution contract: late diagnostics, shared data, args and signals."""
import os
from pathlib import Path
import selectors
import signal
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get('PLEWC', ROOT / 'plewc')).absolute()
EVIDENCE = ROOT / 'tmp/lazy-build/cli-contract'
EVIDENCE.mkdir(parents=True, exist_ok=True)
with tempfile.TemporaryDirectory(prefix='lazy-cli-', dir=ROOT / 'tmp') as temporary:
    source = Path(temporary) / 'Program.pw'
    def run(name, text, expected, output=None, mode='--run', arguments=()):
        source.write_text(text)
        result = subprocess.run([str(COMPILER), mode, str(source), *arguments], capture_output=True, timeout=60)
        (EVIDENCE / (name + '.out')).write_bytes(result.stdout)
        (EVIDENCE / (name + '.err')).write_bytes(result.stderr)
        assert result.returncode == expected, (name, result.returncode, result.stderr.decode())
        if output is not None:
            assert result.stdout == output, (name, result.stdout)
        print('PASS lazy CLI ' + name, flush=True)
        return result
    unused = 'import @Std/Io with { print }\nfn main() { print(42I64) }\nfn unused() { missing() }\n'
    run('unused', unused, 0, b'42\n')
    run('check-unused', unused, 1, mode='--check')
    late = 'import @Std/Io with { eprint }\nfn bad() { missing() }\nfn main() { eprint(text: "entered\\n") bad() }\n'
    failed = run('late-error', late, 1)
    assert failed.stderr.startswith(b'entered\n'), failed.stderr
    arguments = 'import @Std/Process with { argCount, argAt }\nimport @Std/Io with { print }\nfn main() { print(argCount()) print(argAt(1I64)) print(argAt(2I64)) }\n'
    run('arguments', arguments, 0, b'3\n--check\none argument\n', arguments=('--check', 'one argument'))
    run('exit-status', 'import @Std/Process with { exit }\nfn main() { exit(code: 7I64) }\n', 7)
    shared = '''import @Std/Io with { print }
trait Value { fn value() -> I64 }
struct Item { val number: I64 }
impl Item as Value { fn value() -> I64 { return self.number } }
fn first() -> any Value { return <Item number=1I64 /> }
fn second() -> any Value { return <Item number=2I64 /> }
fn main() { val a = first() val b = second() print(a.value()) print(b.value()) }
'''
    run('shared-witness', shared, 0, b'1\n2\n')
    source.write_text('import @Std/Io with { eprint }\nimport @Std/Async with { sleep }\nasync fn main() { eprint(text: "ready\\n") while true { await sleep(ms: 100) } }\n')
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
