#!/usr/bin/env python3
"""Exercise production normal-phase adapters with controlled compiler/dispatch processes."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
PHASES = ('run', 'panic', 'reject', 'part', 'partreject')
ENDS = ('# Architecture,', '# --- reject/', '# --- part/', '# --- partreject/', '\necho "----"')
MODES = ('zero-error', 'zero-success', 'partial', 'duplicate', 'foreign',
         'after-results-error', 'interrupted', 'reverse', 'complete', 'case-failure')
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--report', type=Path)
args = parser.parse_args()
source = (ROOT / 'tests/harness/test.sh').read_text()
# The legacy path is only for establishing RED before the shared adapter exists.
# The final regression uses the production phase adapter through these same callers.
legacy = not (ROOT / 'tests/harness/case-phase.sh').exists()
helpers = source[source.index('progress_start() {'):source.index('# --- suite hygiene:')] if legacy else ''
results = []
real_xargs = shutil.which('xargs')
assert real_xargs
with tempfile.TemporaryDirectory(prefix='plew-normal-dispatch-') as directory:
    root = Path(directory)
    for name in ('scripts/support/watch-command.py', 'scripts/support/trace-command.py',
                 'scripts/support/process_watch.py', 'scripts/support/normal-case-dispatch.py',
                 'tests/harness/case-phase.sh'):
        if (ROOT / name).exists():
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
    tool('sh', '''#!/bin/sh
for last do :; done
case "$DISPATCH_MODE:$last" in interrupted:*alpha.pw|interrupted:*alpha/Main.pw) kill -TERM $$ ;; esac
exec /bin/sh "$@"
''')
    tool('xargs', '#!' + sys.executable + '\n' + '''import os,subprocess,sys
mode=os.environ['DISPATCH_MODE'];data=sys.stdin.buffer.read();delimiter=b'\\0' if b'\\0' in data else b'\\n'
items=[x for x in data.split(delimiter) if x]
if mode.startswith('zero-'):sys.exit(1 if mode=='zero-error' else 0)
if mode=='foreign':
 print('PASS foreign-case',flush=True);sys.exit(0)
if mode=='partial':items=items[:1]
elif mode=='duplicate':items=items[:1]*2
elif mode=='reverse':items=items[::-1]
p=subprocess.run([os.environ['REAL_XARGS'],*sys.argv[1:]],input=delimiter.join(items)+delimiter)
sys.exit(7 if mode=='after-results-error' else p.returncode)
''')
    env = {**os.environ, 'PATH': str(tools) + os.pathsep + os.environ['PATH'],
           'PLEWC': str(compiler), 'PLEW_RT': '', 'PLEW_LD': '', 'REAL_XARGS': real_xargs,
           'PYTHONDONTWRITEBYTECODE': '1'}
    env.pop('PLEW_WATCH_EVENTS', None)  # Expected faults are not failures of the outer supervisor.
    for phase, end in zip(PHASES, ENDS):
        prefix = 'pr' if phase == 'partreject' else phase
        total_name = 'partreject' if phase == 'partreject' else phase
        block = source[source.index(f'{total_name}_total='):].split(end, 1)[0]
        # Legacy workers use global /tmp names; isolate only those scratch paths.
        block = block.replace('/tmp/t_', str(root / 't_'))
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
        for progress in ('1', '0'):
            for mode in MODES:
                if mode == 'case-failure':
                    # All five workers must still report a legitimate case failure.
                    if phase in ('run', 'part'):fixtures[1].with_suffix('.out').write_text('wrong\n')
                    elif phase == 'panic':fixtures[1].with_suffix('.panic').write_text('wrong-panic\n')
                    else:fixtures[1].with_suffix('.err').write_text('wrong-rejection\n')
                script = ('set -e\nJOBS=2; export JOBS; hygiene=""; fail=0; failed=""\n' + helpers + block + '\n[ "$fail" -eq 0 ]\n')
                p = subprocess.run(['/bin/sh', '-c', script], cwd=root,
                                   env={**env, 'DISPATCH_MODE': mode, 'PLEW_TEST_PROGRESS': progress},
                                   capture_output=True, text=True, timeout=25)
                expected = 0 if mode in ('complete', 'reverse') else 1
                ok = (p.returncode == 0) == (expected == 0)
                # Complete case failures must retain the actual fixture label/reason.
                if mode == 'case-failure':ok = ok and p.returncode == 1
                results.append(dict(phase=phase, mode=mode, progress=progress,
                                    actual_exit=p.returncode, expected_success=expected == 0,
                                    passed=ok, stdout=p.stdout, stderr=p.stderr))
                print(('PASS' if ok else 'FAIL') + f' normal-dispatch/{phase}/{mode}/progress={progress}', flush=True)
                for path in fixtures:
                    path.with_suffix('.out').write_text('expected\n')
                    path.with_suffix('.panic').write_text('expected-panic\n')
                    path.with_suffix('.err').write_text('expected-rejection\n')
        for path in fixtures:
            shutil.rmtree(path.parent) if phase in ('part', 'partreject') else [q.unlink() for q in path.parent.glob(path.stem + '.*')]
if args.report:
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(dict(harness_sha256=hashlib.sha256(source.encode()).hexdigest(),
                                          legacy_red_only=legacy, scenarios=results), indent=2) + '\n')
raise SystemExit(0 if all(x['passed'] for x in results) else 1)
