#!/usr/bin/env python3
"""Exercise stage budgets, barriers, failure cancellation and signal cleanup."""
from contextlib import ExitStack
import importlib.util
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import tempfile
import time
from unittest.mock import patch

sys.dont_write_bytecode = True
root = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('schedule', root / 'tests/sanitizer/asan-schedule.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
with tempfile.TemporaryDirectory() as directory, ExitStack() as stack:
    work = Path(directory)
    # Expected interruptions are fixture evidence, not failures of the outer gate.
    # Retain their logs locally and never publish them to its worker channel.
    original_popen = subprocess.Popen
    diagnostics = stack.enter_context((work / 'expected-interruptions.log').open('wb'))
    def isolated_popen(*args, **kwargs):
        env = dict(kwargs.get('env', os.environ))
        env.pop('PLEW_WATCH_EVENTS', None)
        kwargs['env'] = env
        if kwargs.get('stderr') is None:
            kwargs['stderr'] = diagnostics
        return original_popen(*args, **kwargs)
    stack.enter_context(patch.object(module.subprocess, 'Popen', side_effect=isolated_popen))
    stage = work / 'stage.py'
    stage.write_text('''import json,os,sys,time
from pathlib import Path
out=Path(sys.argv[1]);name=sys.argv[2]
(out/(name+'.start')).write_text(json.dumps([time.monotonic(),int(os.environ['PLEW_TEST_JOBS'])]))
time.sleep(0.2)
(out/(name+'.end')).write_text(str(time.monotonic()))
sys.exit(int(sys.argv[3]))
''')
    def args(name, code=0):
        return [sys.executable, str(stage), str(work), name, str(code)]
    for jobs in (1, 2, 8):
        assert module.run_stages(args('corpus'), args('prepare'), jobs) == 0
        cs, cj = json.loads((work / 'corpus.start').read_text())
        ps, pj = json.loads((work / 'prepare.start').read_text())
        ce = float((work / 'corpus.end').read_text())
        pe = float((work / 'prepare.end').read_text())
        if jobs == 1:
            assert ps >= ce and cj == pj == 1
        else:
            assert max(cs, ps) < min(ce, pe) and cj + pj == jobs and pj == 1
    for failing in ('corpus', 'prepare'):
        assert module.run_stages(args('corpus', 7 if failing == 'corpus' else 0),
                                 args('prepare', 7 if failing == 'prepare' else 0), 2) != 0
    # Real supervisors must forward cancellation to children with their own groups.
    sleepy = work / 'sleepy.py'
    sleepy.write_text('import os,sys,time\nfrom pathlib import Path\nPath(sys.argv[1]).write_text(str(os.getpid()))\ntime.sleep(50)\n')
    for failing in ('corpus', 'prepare'):
        pidfile = work / ('failed-peer-' + failing)
        live = [sys.executable, str(root / 'scripts/support/watch-command.py'), '--',
                sys.executable, str(sleepy), str(pidfile)]
        failed = args('failing', 7)
        start = time.monotonic()
        code = module.run_stages(failed if failing == 'corpus' else live,
                                 failed if failing == 'prepare' else live, 2)
        assert code != 0 and time.monotonic() - start < 8
        if pidfile.exists():
            try:
                os.kill(int(pidfile.read_text()), 0)
            except ProcessLookupError:
                pass
            else:
                raise AssertionError('failed stage left its peer running')
    wrapper = work / 'wrapper.py'
    pidfiles = [work / 'one.pid', work / 'two.pid']
    # Use explicit argv serialization so the supervisor command is identical in both stages.
    wrapper.write_text('import importlib.util,json,sys\n'
                       's=importlib.util.spec_from_file_location("s",sys.argv[1]);m=importlib.util.module_from_spec(s);s.loader.exec_module(m)\n'
                       'raise SystemExit(m.run_stages(*json.loads(sys.argv[2]),2))\n')
    commands = [[sys.executable, str(root / 'scripts/support/watch-command.py'), '--',
                 sys.executable, str(sleepy), str(path)] for path in pidfiles]
    child = subprocess.Popen([sys.executable, '-B', str(wrapper), str(root / 'tests/sanitizer/asan-schedule.py'), json.dumps(commands)],
                             stdout=subprocess.DEVNULL)
    try:
        deadline = time.monotonic() + 10
        while not all(p.exists() for p in pidfiles):
            assert time.monotonic() < deadline
            time.sleep(0.02)
        child.send_signal(signal.SIGTERM)
        status = child.wait(timeout=8)
        assert status == 143, status
        for path in pidfiles:
            try:
                os.kill(int(path.read_text()), 0)
            except ProcessLookupError:
                pass
            else:
                raise AssertionError('supervised child survived cancellation')
    finally:
        if child.poll() is None:
            child.kill(); child.wait()
print('PASS asan scheduling budgets, barrier, failures and descendant cleanup')
