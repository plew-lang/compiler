#!/usr/bin/env python3
"""Controlled failure-domain checks on the actual normal, expose and ASan B paths.

This task-start regression deliberately fails until com-fsuq has an authoritative
source-rejection channel. It is not yet registered in the standard harness.
No Plew compiler, generated application or sanitizer instrumentation is run.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--report', type=Path, required=True)
args = parser.parse_args()
scenarios = [
    ('source-rejection', True), ('accepted', False), ('silent-one', False),
    ('internal-one', False), ('internal-after-reason', False),
    ('wrong-status-after-reason', False), ('signal-after-reason', False),
    ('timeout-status', False), ('supervisor-status', False), ('asan-after-reason', False),
]
expose = (ROOT / 'tests/compiler/codegen/test-expose.py').read_text()
fixture_block = expose[expose.index("for name in ['expose_labels'"):expose.index('# Separate modules')]
collision_block = expose[expose.index("with tempfile.TemporaryDirectory(prefix='plew-expose-collision-'"):expose.index('# Choose a generated private name')]
managed_block = expose[expose.index("with tempfile.TemporaryDirectory(prefix='plew-expose-managed-'"):expose.index("print('PASS expose:")]
results = []
with tempfile.TemporaryDirectory(prefix='plew-rejection-domains-') as directory:
    root = Path(directory)
    copied = ('tests/harness/case-phase.sh', 'tests/harness/asan-compile-corpus.sh',
              'scripts/support/normal-case-dispatch.py', 'scripts/support/watch-command.py',
              'scripts/support/trace-command.py', 'scripts/support/process_watch.py')
    for name in copied:
        p = root / name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_bytes((ROOT / name).read_bytes())
    for phase, name in [('reject', 'fixture.pw'), ('partreject', 'fixture/Main.pw'),
                        ('run', 'positive.pw'), ('panic', 'positive.pw')]:
        p = root / 'tests/fixtures' / phase / name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text('controlled source\n')
    for name in ['expose_labels', 'expose_duplicate', 'expose_generic',
                 'expose_method', 'expose_associated', 'expose_main']:
        for suffix in ['.pw', '.err']:
            p = Path('tests/fixtures/reject') / (name + suffix)
            (root / p).write_bytes((ROOT / p).read_bytes())
    compiler = root / 'plewc_asan'
    compiler.write_text('#!' + sys.executable + '\n' + '''import os,sys,signal
from pathlib import Path
p=Path(sys.argv[-1]); mode=os.environ['REJECTION_SCENARIO']
with open(os.environ['INVOCATIONS'],'a') as log: log.write(str(p)+'\\n')
if p.name=='_.pw' or any(s in p.parts for s in ['run','panic']):sys.exit(0)
reason='intended source rejection'
if p.with_suffix('.err').exists():reason=p.with_suffix('.err').read_text().strip()
elif p.exists():
 text=p.read_text()
 if 'extern(c)' in text:reason='conflicting C function ABI for external name'
 elif 'expose fn entry(value~:' in text:reason='expose parameter ABI is not supported'
 elif 'expose fn entry() ->' in text:reason='expose return ABI is not supported'
if mode=='accepted':sys.exit(0)
if mode=='silent-one':sys.exit(1)
if mode=='internal-one':print('plewc: error: internal error: program Mid preparation failed',file=sys.stderr)
else:print('plewc: error: '+reason,file=sys.stderr)
if mode=='internal-after-reason':print('plewc: error: internal error: program Mid preparation failed',file=sys.stderr)
if mode=='asan-after-reason':print('ERROR: AddressSanitizer: controlled failure',file=sys.stderr)
if mode=='signal-after-reason':sys.stderr.flush();os.kill(os.getpid(),signal.SIGTERM)
sys.exit({'wrong-status-after-reason':2,'timeout-status':124,'supervisor-status':125}.get(mode,1))
''')
    compiler.chmod(0o755)
    env = {**os.environ, 'PLEWC': str(compiler), 'PLEW_TEST_JOBS': '1',
           'JOBS': '1', 'TMP': str(root / 'logs'), 'TMPDIR': str(root),
           'PYTHONDONTWRITEBYTECODE': '1', 'LC_ALL': 'C'}
    env.pop('PLEW_WATCH_EVENTS', None)
    (root / 'logs').mkdir()
    lanes = [('reject', False), ('reject', True), ('partreject', False),
             ('partreject', True), ('expose-fixtures', True),
             ('expose-collisions', True), ('expose-managed', True), ('asan-B', False)]
    for lane, companion in lanes:
        for scenario, should_accept in scenarios:
            invocation = root / 'invocations.txt'
            invocation.write_text('')
            local_env = {**env, 'INVOCATIONS': str(invocation), 'REJECTION_SCENARIO': scenario}
            if lane in ['reject', 'partreject']:
                source = root / 'tests/fixtures' / lane / ('fixture.pw' if lane == 'reject' else 'fixture/Main.pw')
                want = source.with_suffix('.err')
                if want.exists():want.unlink()
                if companion:want.write_text('intended source rejection\n')
                command = ['/bin/sh', 'tests/harness/case-phase.sh', '--worker', lane, str(source)]
                p = subprocess.run(command, cwd=root, env=local_env, capture_output=True, text=True, timeout=15)
                terminal = p.stdout.strip()
                recognized = p.returncode == 0 and terminal.startswith(('PASS '+lane+'/', 'FAIL '+lane+'/'))
                accepted = terminal.startswith('PASS ')
                expected_calls = 1
            elif lane == 'asan-B':
                # Execute the complete unchanged A/B stage; positives and A are
                # successful controls, only the selected reject gets the fault.
                command = ['/bin/sh', 'tests/harness/asan-compile-corpus.sh']
                # The six expose files belong only to their separate lane.
                for path in (root/'tests/fixtures/reject').glob('expose_*.pw'):path.rename(path.with_suffix('.hold'))
                p = subprocess.run(command, cwd=root, env=local_env, capture_output=True, text=True, timeout=15)
                for path in (root/'tests/fixtures/reject').glob('expose_*.hold'):path.rename(path.with_suffix('.pw'))
                recognized = p.returncode in (0, 1) and 'asan: B completed=3 ' in p.stderr
                accepted = p.returncode == 0
                expected_calls = 4  # A plus run/reject/panic.
            else:
                block, expected_calls = {'expose-fixtures': (fixture_block, 6),
                                          'expose-collisions': (collision_block, 4),
                                          'expose-managed': (managed_block, 8)}[lane]
                script = 'import subprocess,tempfile\nfrom pathlib import Path\nroot=Path('+repr(str(root))+')\ncompiler=Path('+repr(str(compiler))+')\n' + block
                p = subprocess.run([sys.executable, '-B', '-c', script], cwd=root, env=local_env, capture_output=True, text=True, timeout=15)
                recognized = p.returncode == 0 or (p.returncode == 1 and 'AssertionError' in p.stderr and 'Traceback' in p.stderr)
                accepted = p.returncode == 0
            calls = len(invocation.read_text().splitlines())
            # A failing expose assertion stops at its first invocation. A false
            # success must reach the whole selected production loop.
            recognized &= calls == expected_calls if accepted or not lane.startswith('expose-') else calls == 1
            ok = recognized and accepted == should_accept
            results.append(dict(lane=lane, reason_companion=companion, scenario=scenario,
                                should_accept=should_accept, accepted=accepted, passed=bool(ok),
                                actual_exit=p.returncode, invocation_count=calls,
                                recognized_terminal=bool(recognized), stdout=p.stdout, stderr=p.stderr))
            print(('PASS' if ok else 'FAIL') + f' rejection-domain/{lane}/reason={companion}/{scenario}', flush=True)
args.report.parent.mkdir(parents=True, exist_ok=True)
names = (*copied, 'tests/compiler/codegen/test-expose.py', 'tests/tooling/test-rejection-domains.py')
args.report.write_text(json.dumps(dict(source_hashes={n:hashlib.sha256((ROOT/n).read_bytes()).hexdigest() for n in names},
                                      scenarios=results), indent=2)+'\n')
raise SystemExit(0 if all(r['passed'] for r in results) else 1)
