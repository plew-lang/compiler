#!/usr/bin/env python3
"""Sampling must not stop draining stderr or outlive the measured compiler."""
import os
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parent
with tempfile.TemporaryDirectory(prefix='measure-sampling-', dir=root / 'tmp') as directory:
    temp = Path(directory)
    (temp / 'src').mkdir()
    (temp / 'src/_.pw').write_text('fixture\n')
    carrier = temp / 'carrier'
    carrier.write_text('''#!/usr/bin/env python3
import os, sys, time
from pathlib import Path
root = Path(os.environ['SAMPLE_TEST_ROOT'])
print('[trace-phase] fixture:start', file=sys.stderr, flush=True)
while not (root / 'sampling').exists(): time.sleep(0.001)
sys.stderr.write('[trace-codegen] ' + 'x' * 500000 + '\\n')
sys.stderr.flush()
(root / 'drained').touch()
time.sleep(0.4)
sys.stderr.write('last bytes without newline')
sys.stdout.write('fixture llvm')
sys.exit(7)
''')
    sampler = temp / 'sampler'
    sampler.write_text('''#!/usr/bin/env python3
import os, sys, time
from pathlib import Path
root = Path(os.environ['SAMPLE_TEST_ROOT'])
(root / 'sampler-pid').write_text(str(os.getpid()))
(root / 'sampling').touch()
time.sleep(0.2)
(root / 'observed').write_text('drained' if (root / 'drained').exists() else 'blocked')
time.sleep(1)
Path(sys.argv[4]).write_text('sample')
''')
    carrier.chmod(0o755)
    sampler.chmod(0o755)
    env = dict(os.environ, PLEWC=str(carrier), SOURCE=str(temp / 'src/_.pw'),
               OUT_DIR=str(temp / 'out'), TRACE_CODEGEN='1', SAMPLE_TEST_ROOT=str(temp),
               PLEW_PERF_SAMPLE_COMMAND=str(sampler),
               PLEW_PERF_SAMPLE_INTERVAL_SECONDS='0.1', PLEW_PERF_SAMPLE_DURATION_SECONDS='1')
    result = subprocess.run(['sh', str(root / 'measure-self-compile.sh')], cwd=root,
                            env=env, capture_output=True, timeout=15)
    assert result.returncode == 7, result.stderr.decode()
    assert (temp / 'observed').read_text() == 'drained', 'sampler blocked stderr draining'
    assert (temp / 'out/compiler.ll').read_bytes() == b'fixture llvm'
    expected = b'[trace-phase] fixture:start\n[trace-codegen] ' + b'x' * 500000 + b'\nlast bytes without newline'
    assert (temp / 'out/stderr.log').read_bytes() == expected
    assert 'compiler-ended' in (temp / 'out/cpu-sample-status.tsv').read_text()
    pid = int((temp / 'sampler-pid').read_text())
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        pass
    else:
        raise AssertionError('sampler was not reaped')
print('PASS sampling drains stderr, preserves bytes/status, and reaps sampler')
