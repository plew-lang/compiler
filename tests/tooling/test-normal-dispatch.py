#!/usr/bin/env python3
"""Check real normal-phase callers, dispatch and workers with controlled subprocess faults."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
PHASES = ('run', 'panic', 'reject', 'part', 'partreject')
ENDS = ('# Architecture,', '# --- reject/', '# --- part/', '# --- partreject/', '\necho "----"')
PASS_VARS = ('pass', 'ppass', 'rpass', 'qpass', 'prpass')
MODES = ('zero-error', 'zero-success', 'partial', 'duplicate', 'foreign-equal',
         'extra', 'malformed', 'unterminated', 'after-results-error',
         'interrupted', 'worker-error', 'reverse', 'complete', 'case-failure')
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--report', type=Path)
args = parser.parse_args()
source = (ROOT / 'tests/harness/test.sh').read_text()
assert (ROOT / 'tests/harness/case-phase.sh').is_file()
budget = source[source.index('JOBS='):source.index('# --- suite hygiene:')]
results = []
real_xargs = shutil.which('xargs')
assert real_xargs
with tempfile.TemporaryDirectory(prefix='plew-normal-dispatch-') as directory:
    root = Path(directory)
    for name in ('scripts/support/watch-command.py', 'scripts/support/trace-command.py',
                 'scripts/support/process_watch.py', 'scripts/support/normal-case-dispatch.py',
                 'tests/harness/case-phase.sh'):
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(ROOT / name, root / name)
    tools = root / 'tools'
    tools.mkdir()
    def tool(name, text):
        p = tools / name
        p.write_text(text)
        p.chmod(0o755)
        return p
    compiler = tool('compiler', '''#!/bin/sh
case "$1" in
 tests/fixtures/reject/*|tests/fixtures/partreject/*) echo expected-rejection >&2; exit 1 ;;
 *) cat "$1" ;;
esac
''')
    tool('clang', '''#!/bin/sh
while [ "$#" -gt 0 ]; do
 case "$1" in *.ll) input="$1";; -o) shift; output="$1";; esac
 shift
done
cp "$input" "$output"
chmod +x "$output"
''')
    tool('sysctl', '#!/bin/sh\nprintf "2\\n"\n')
    tool('sh', '''#!/bin/sh
for last do :; done
case "$DISPATCH_MODE:$last" in
 interrupted:*alpha.pw|interrupted:*alpha/Main.pw) kill -TERM $$ ;;
 worker-error:*alpha.pw|worker-error:*alpha/Main.pw) exit 9 ;;
esac
exec /bin/sh "$@"
''')
    tool('xargs', '#!' + sys.executable + '\n' + '''import json,os,subprocess,sys
from pathlib import Path
mode=os.environ['DISPATCH_MODE'];data=sys.stdin.buffer.read();items=[x for x in data.split(b'\\0') if x]
args=sys.argv[1:];Path(os.environ['XARGS_LOG']).write_text(json.dumps(args))
if mode.startswith('zero-'):sys.exit(1 if mode=='zero-error' else 0)
if mode=='parent-exits':
 child=subprocess.Popen([sys.executable,'-c','import time;time.sleep(50)'])
 Path(os.environ['CHILD_PID']).write_text(str(child.pid));sys.exit(0)
if mode=='partial':items=items[:1]
elif mode=='duplicate':items=items[:1]*2
# Serial real workers make deliberately reversed output deterministic. The
# production collector must accept this order without assuming declaration order.
if mode=='reverse':items=items[::-1];args[args.index('-P')+1]='1'
transform=mode in ('foreign-equal','extra','malformed','unterminated')
p=subprocess.run([os.environ['REAL_XARGS'],*args],input=b'\\0'.join(items)+b'\\0',stdout=subprocess.PIPE if transform else None)
if transform:
 lines=p.stdout.splitlines(keepends=True)
 if mode=='foreign-equal':lines[-1]=b'PASS foreign-case\\n'
 elif mode=='extra':lines.append(b'PASS foreign-case\\n')
 elif mode=='malformed':lines[-1]=b'not-a-terminal-result\\n'
 elif mode=='unterminated':lines[-1]=lines[-1].rstrip(b'\\n')
 sys.stdout.buffer.write(b''.join(lines));sys.stdout.buffer.flush()
sys.exit(7 if mode=='after-results-error' else p.returncode)
''')
    env = {**os.environ, 'PATH': str(tools) + os.pathsep + os.environ['PATH'],
           'PLEWC': str(compiler), 'PLEW_RT': '', 'PLEW_LD': '', 'REAL_XARGS': real_xargs,
           'PYTHONDONTWRITEBYTECODE': '1', 'TMPDIR': str(root), 'TEST_ROOT': str(root),
           'XARGS_LOG': str(root / 'xargs.json'), 'CHILD_PID': str(root / 'child.pid')}
    for key in ('PLEW_WATCH_EVENTS', 'PLEW_TEST_JOBS', 'JOBS'):
        env.pop(key, None)  # Expected faults must not poison the outer supervisor.
    def record(phase, mode, progress, p, ok):
        results.append(dict(phase=phase, mode=mode, progress=progress, actual_exit=p.returncode,
                            passed=ok, stdout=p.stdout, stderr=p.stderr))
        print(('PASS' if ok else 'FAIL') + f' normal-dispatch/{phase}/{mode}/progress={progress}', flush=True)
    for phase, end, pass_var in zip(PHASES, ENDS, PASS_VARS):
        result_var = 'pr' if phase == 'partreject' else phase
        block = source[source.index(f'{result_var}_results='):].split(end, 1)[0]
        # Consume the actual production budget setup and per-phase aggregation.
        script = ('set -e\nLC=true; RUNTIME_DIR="$TEST_ROOT"\n' + budget +
                  'hygiene=""; fail=0; failed=""\n' + block +
                  f'\nprintf "%s\\n" "${{{result_var}_results}}"\n' +
                  f'printf "OBSERVED pass=%s fail=%s failed=%s\\n" "${pass_var}" "$fail" "$failed"\n' +
                  '[ "$fail" -eq 0 ]\n')
        fixtures = []
        for name in ('alpha', 'beta'):
            path = root / f'tests/fixtures/{phase}/{name}.pw' if phase not in ('part', 'partreject') else root / f'tests/fixtures/{phase}/{name}/Main.pw'
            path.parent.mkdir(parents=True, exist_ok=True)
            body = '#!/bin/sh\nprintf "expected\\n"\n'
            if phase == 'panic':body = '#!/bin/sh\nprintf "expected-panic\\n" >&2\nexit 134\n'
            path.write_text(body)
            path.with_suffix('.out').write_text('expected\n')
            path.with_suffix('.panic').write_text('expected-panic\n')
            path.with_suffix('.err').write_text('expected-rejection\n')
            fixtures.append(path)
        labels = [name if phase == 'run' else f'{phase}/{name}' for name in ('alpha', 'beta')]
        for progress in ('1', '0'):
            for mode in MODES:
                if mode == 'case-failure':
                    suffix = '.out' if phase in ('run', 'part') else '.panic' if phase == 'panic' else '.err'
                    fixtures[1].with_suffix(suffix).write_text('wrong\n')
                p = subprocess.run(['/bin/sh', '-c', script], cwd=root,
                                   env={**env, 'DISPATCH_MODE': mode, 'PLEW_TEST_PROGRESS': progress},
                                   capture_output=True, text=True, timeout=25)
                complete = mode in ('complete', 'reverse', 'case-failure')
                ok = p.returncode == (0 if mode in ('complete', 'reverse') else 1)
                if complete:
                    terminals = [line for line in p.stdout.splitlines() if line.startswith(('PASS ', 'FAIL '))]
                    if mode == 'case-failure':
                        ok &= f'PASS {labels[0]}' in terminals and any(line.startswith('FAIL '+labels[1]) for line in terminals)
                        ok &= f'OBSERVED pass=1 fail=1 failed= {labels[1]}' in p.stdout
                    else:
                        ok &= sorted(terminals) == sorted('PASS '+name for name in labels)
                        ok &= 'OBSERVED pass=2 fail=0 failed=\n' in p.stdout
                        if mode == 'reverse':ok &= terminals == ['PASS '+name for name in labels[::-1]]
                else:
                    reason = 'dispatcher exited 7' if mode == 'after-results-error' else 'invalid or duplicate result' if mode in ('duplicate','foreign-equal','extra','malformed','unterminated') else 'missing results'
                    ok &= f'plewc: {phase} dispatch:' in p.stderr and reason in p.stderr
                    ok &= 'OBSERVED' not in p.stdout
                if progress == '1':
                    ok &= f'plewc: {phase} started (2 cases; 2 workers)' in p.stderr
                    if complete:
                        updates = re.findall(rf'^plewc: {phase} (\d+)/2 complete: (.+)$', p.stderr, re.M)
                        ok &= [n for n, _ in updates] == ['1', '2']
                        ok &= [line for _, line in updates] == terminals
                else:
                    ok &= ' started (' not in p.stderr and ' complete:' not in p.stderr
                actual_args = json.loads((root / 'xargs.json').read_text())
                ok &= actual_args[actual_args.index('-P')+1] == '2'
                record(phase, mode, progress, p, bool(ok))
                for path in fixtures:
                    path.with_suffix('.out').write_text('expected\n')
                    path.with_suffix('.panic').write_text('expected-panic\n')
                    path.with_suffix('.err').write_text('expected-rejection\n')
        p = subprocess.run(['/bin/sh','-c',script],cwd=root,capture_output=True,text=True,timeout=25,
                           env={**env,'DISPATCH_MODE':'complete','PLEW_TEST_JOBS':'3','PLEW_TEST_PROGRESS':'1'})
        record(phase,'configured-workers','1',p,p.returncode==0 and '2 cases; 3 workers' in p.stderr)
        # The dispatcher can exit before a child that still owns its output pipe.
        # Cancellation must reclaim that process group even after the parent exits.
        pidfile = root / 'child.pid'
        pidfile.unlink(missing_ok=True)
        p = subprocess.Popen(['/bin/sh',str(root/'tests/harness/case-phase.sh'),phase],cwd=root,
                             env={**env,'DISPATCH_MODE':'parent-exits','PLEW_TEST_PROGRESS':'0'},
                             stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
        child = None
        try:
            deadline = time.monotonic()+5
            while not pidfile.exists():
                assert p.poll() is None and time.monotonic()<deadline
                time.sleep(0.02)
            child = int(pidfile.read_text())
            time.sleep(0.05)
            p.terminate()
            timed_out = False
            try:
                stdout,stderr = p.communicate(timeout=5)
            except subprocess.TimeoutExpired:
                timed_out = True
                os.killpg(os.getpgid(child),signal.SIGKILL)
                if p.poll() is None:p.kill()
                stdout,stderr = p.communicate(timeout=5)
            live = True
            deadline = time.monotonic()+2
            while time.monotonic()<deadline:
                try:os.kill(child,0)
                except ProcessLookupError:live=False;break
                time.sleep(0.02)
            result = subprocess.CompletedProcess(p.args,p.returncode,stdout,stderr)
            record(phase,'cancel-after-dispatcher-exit','0',result,p.returncode==143 and not live and not timed_out)
        finally:
            if p.poll() is None:p.kill();p.wait()
            if child is not None:
                try:os.killpg(os.getpgid(child),signal.SIGKILL)
                except ProcessLookupError:
                    try:os.kill(child,signal.SIGKILL)
                    except ProcessLookupError:pass
        for path in fixtures:
            if phase in ('part','partreject'):shutil.rmtree(path.parent)
            else:
                for q in path.parent.glob(path.stem+'.*'):q.unlink()
        p = subprocess.run(['/bin/sh','-c',script],cwd=root,capture_output=True,text=True,timeout=25,
                           env={**env,'DISPATCH_MODE':'complete','PLEW_TEST_PROGRESS':'1'})
        record(phase,'empty-selection','1',p,p.returncode==1 and 'empty selection' in p.stderr)
if args.report:
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(dict(harness_sha256=hashlib.sha256(source.encode()).hexdigest(),
                                          scenarios=results),indent=2)+'\n')
raise SystemExit(0 if all(x['passed'] for x in results) else 1)
