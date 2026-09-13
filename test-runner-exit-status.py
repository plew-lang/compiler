#!/usr/bin/env python3
"""Exercise the actual test.sh workers with controlled compiler/linker doubles."""
import os
from pathlib import Path
import re
import subprocess
import tempfile

source = Path(__file__).with_name('test.sh').read_text()
workers = {}
for phase in ('run', 'part'):
    match = re.search(rf'{phase}_results=.*?sh -c \'\n(.*?)\n\' sh \| progress_stream {phase} ', source, re.S)
    assert match, phase
    workers[phase] = match.group(1)

with tempfile.TemporaryDirectory(prefix='plew-runner-status-') as directory:
    root = Path(directory)
    tools = root / 'tools'
    tools.mkdir()
    compiler = tools / 'compiler'
    compiler.write_text('#!/bin/sh\ncat "$1"\n')
    linker = tools / 'clang'
    linker.write_text('''#!/bin/sh
while [ "$#" -gt 0 ]; do
    case "$1" in
        *.ll) input="$1" ;;
        -o) shift; output="$1" ;;
    esac
    shift
done
cp "$input" "$output"
chmod +x "$output"
''')
    compiler.chmod(0o755)
    linker.chmod(0o755)
    env = {**os.environ, 'PATH': str(tools) + os.pathsep + os.environ['PATH'],
           'PLEWC': str(compiler), 'PLEW_RT': '', 'PLEW_LD': ''}
    cases = [('normal', 'printf "expected\\n"', True),
             ('nonzero', 'printf "expected\\n"; exit 7', False),
             ('signal', 'printf "expected\\n"; kill -TERM $$', False),
             ('mismatch', 'printf "wrong\\n"', False)]
    for phase, worker in workers.items():
        # Isolate the production workers' scratch paths without changing their logic.
        worker = worker.replace('/tmp/t_', str(root / 't_'))
        for name, body, expected_pass in cases:
            for stdin in (False, True) if phase == 'run' else (False,):
                case = name + ('_stdin' if stdin else '')
                path = root / ('tests/run/' + case + '.pw' if phase == 'run'
                               else 'tests/part/' + case + '/Main.pw')
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('#!/bin/sh\n' + ('read value\n' if stdin else '') + body + '\n')
                path.with_suffix('.out').write_text('expected\n')
                if stdin:
                    path.with_suffix('.in').write_text('input\n')
                result = subprocess.run(['sh', '-c', worker, 'sh', str(path.relative_to(root))],
                                        cwd=root, env=env, text=True, capture_output=True)
                label = case if phase == 'run' else 'part/' + case
                if expected_pass:
                    assert result.stdout == f'PASS {label}\n', result
                else:
                    assert result.stdout.startswith(f'FAIL {label}'), result
                    if name in ('nonzero', 'signal'):
                        assert '(exit:' in result.stdout, result
                assert result.returncode == 0, result
                print(f'PASS {phase}/{case}', flush=True)
    gen_source = Path(__file__).with_name('test-gen.sh').read_text()
    gen_worker = gen_source.split('    # 5. run + compare\n', 1)[1].split('\ndone', 1)[0]
    work = root / 'gen'
    work.mkdir()
    (work / 'App.out').write_text('expected\n')
    for name, body, expected_pass in cases:
        app = work / 'app'
        app.write_text('#!/bin/sh\n' + body + '\n')
        app.chmod(0o755)
        script = ('work=$1; dir=$1; name=fixture; pass=0; fail=0; failed=""\n'
                  'for iteration in once; do\n' + gen_worker +
                  '\ndone\nprintf "%s %s" "$pass" "$fail"\n')
        result = subprocess.run(['sh', '-c', script, 'sh', str(work)],
                                text=True, capture_output=True)
        assert result.returncode == 0, result
        assert result.stdout == ('1 0' if expected_pass else '0 1'), result
        print(f'PASS gen/{name}', flush=True)

# Exercise the actual generation compile/reject guards with controlled exits.
with tempfile.TemporaryDirectory(prefix='plew-gen-status-') as directory:
    root = Path(directory)
    compiler = root / 'compiler'
    source = Path(__file__).with_name('test-gen.sh').read_text()
    blocks = {
        'harness': source.split('    # 1. harness IR\n', 1)[1].split('    # 2+3.', 1)[0],
        'app': source.split('    # 4. build the app (auto-parts App.gen.pw)\n', 1)[1].split('    if ! clang', 1)[0],
        'reject': source.split('    status=0\n    "$PLEWC" --gen', 1)[1].split('\ndone', 1)[0],
    }
    blocks['reject'] = '    status=0\n    "$PLEWC" --gen' + blocks['reject']
    for phase, block in blocks.items():
        for code in (0, 1, 7, 143):
            compiler.write_text(f'#!/bin/sh\necho diagnostic >&2\nexit {code}\n')
            compiler.chmod(0o755)
            script = ('work=$1; PLEWC=$2; name=fixture; fail=0; failed=""; rpass=0\n'
                      'for iteration in once; do\n' + block +
                      '\ndone\nprintf "%s %s" "$fail" "$rpass"\n')
            result = subprocess.run(['sh', '-c', script, 'sh', str(root), str(compiler)],
                                    capture_output=True, text=True)
            accepted = code == (1 if phase == 'reject' else 0)
            expected = ('0 1' if phase == 'reject' else '0 0') if accepted else '1 0'
            assert result.returncode == 0 and result.stdout == expected, (phase, code, result)
            print(f'PASS gen-status/{phase}/{code}', flush=True)

# Actual ASan run-status branch, without requiring a sanitizer installation.
asan = Path(__file__).with_name('asan-gate.sh').read_text()
worker = asan.split('    run_exit=0\n', 1)[1].split("\n' sh", 1)[0]
worker = '    run_exit=0\n' + worker
with tempfile.TemporaryDirectory(prefix='plew-asan-status-') as directory:
    root = Path(directory)
    (root/'tests/run').mkdir(parents=True)
    binary = root/'app'
    for name, body, expected_pass in cases:
        for stdin in (False, True):
            infile = root/'tests/run/fixture.in'
            if stdin: infile.write_text('input\n')
            elif infile.exists(): infile.unlink()
            binary.write_text('#!/bin/sh\n' + ('read value\n' if stdin else '') + body + '\n')
            binary.chmod(0o755)
            script = 'name=fixture; bin=$1; err=$2\n' + worker
            result = subprocess.run(['sh','-c',script,'sh',str(binary),str(root/'error')],
                                    cwd=root,capture_output=True,text=True)
            # This gate checks memory/exit status; golden comparison is test.sh's job.
            expected = name in ('normal', 'mismatch')
            assert result.returncode == 0, result
            assert result.stdout.startswith('RAN ' if expected else 'FAIL '), result
            print(f'PASS asan-status/{name}/stdin={stdin}', flush=True)

# Compile corpus must reject only expected diagnostics, never crashes.
asan = Path(__file__).with_name('asan-gate.sh').read_text()
worker = asan.split('    compile_exit=0\n', 1)[1].split("\n' sh", 1)[0]
worker = 'compile_exit=0\n' + worker
with tempfile.TemporaryDirectory(prefix='plew-asan-compile-') as directory:
    root = Path(directory)
    (root/'trace-command.py').write_bytes(Path(__file__).with_name('trace-command.py').read_bytes())
    compiler = root/'plewc_asan'
    for reject in (False, True):
        for code in (0, 1, 7, 143):
            compiler.write_text(f'#!/bin/sh\necho "plewc: error: diagnostic" >&2\nexit {code}\n')
            compiler.chmod(0o755)
            path = 'tests/reject/fixture.pw' if reject else 'tests/run/fixture.pw'
            result = subprocess.run(['sh','-c','f=$1; err=$2\n'+worker,'sh',path,str(root/'error')],
                                    cwd=root,capture_output=True,text=True)
            expected = code == (1 if reject else 0)
            assert result.returncode == 0, result
            assert result.stdout.startswith('RAN ' if expected else 'FAIL '), result
            print(f'PASS asan-compile/reject={reject}/exit={code}', flush=True)

    compiler.write_text('#!/bin/sh\necho "[trace-phase] fixture:start" >&2\nexit 1\n')
    compiler.chmod(0o755)
    result = subprocess.run(['sh','-c','f=$1; err=$2\n'+worker,'sh','tests/reject/fixture.pw',str(root/'error')],
                            cwd=root,capture_output=True,text=True)
    assert result.returncode == 0 and result.stdout.startswith('FAIL '), result
    assert 'missing rejection diagnostic' in result.stdout, result
    print('PASS asan-compile/trace-is-not-diagnostic', flush=True)

# Every preparation failure must produce a result instead of disappearing.
asan = Path(__file__).with_name('asan-gate.sh').read_text()
with tempfile.TemporaryDirectory(prefix='plew-asan-preparation-') as directory:
    root = Path(directory)
    guards = [line for line in asan.splitlines()
              if 'diagnostic: $err.' in line and 'exit 0;' in line]
    assert len(guards) == 6, guards
    for index, guard in enumerate(guards):
        script = ('PLEWC=false; OPT=false; CLANG=false; f=fixture; '
                  'll=$1/input.ll; err=$1/error; bin=$1/binary; RT=; extra_c=; PLEW_LD=\n' + guard)
        result = subprocess.run(['sh','-c',script,'sh',str(root)],capture_output=True,text=True)
        assert result.returncode == 0 and result.stdout.startswith('FAIL '), result
        assert 'diagnostic:' in result.stdout, result
        print(f'PASS asan-preparation/{index}', flush=True)

# Dependency CLI checks must not hide a failing command behind matching stdout.
deps = Path(__file__).with_name('test-deps.sh').read_text()
helpers = deps.split('fail=0\n', 1)[1].split('# --- consumer 1:', 1)[0]
for code in (0, 7, 143):
    script = 'fail=0\n' + helpers + '\ncheck_run fixture expected sh -c "printf expected; exit $1"\nexit "$fail"\n'
    result = subprocess.run(['sh','-c',script,'sh',str(code)],capture_output=True,text=True)
    assert result.returncode == (0 if code == 0 else 1), result
    print(f'PASS deps-status/{code}', flush=True)
