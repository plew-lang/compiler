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
