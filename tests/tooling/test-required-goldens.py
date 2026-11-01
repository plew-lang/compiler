#!/usr/bin/env python3
"""Check required part/gen golden reads through production consumers and final exits.

Controlled compiler/linker programs isolate the I/O contract. The actual part
caller/collector/worker, gen positive loop and final summaries are read unchanged
from production sources; no replacement output comparator is used.
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
parser.add_argument('--report', type=Path)
args = parser.parse_args()
normal = (ROOT / 'tests/harness/test.sh').read_text()
gen = (ROOT / 'tests/harness/test-gen.sh').read_text()
part_block = normal[normal.index('part_results='):normal.index('# --- partreject/')]
normal_end = '\necho "----"' + normal.rsplit('\necho "----"', 1)[1]
gen_loop = gen[gen.index('mkdir -p tmp'):gen.index('# genreject/')]
gen_end = '\necho "----"' + gen.rsplit('\necho "----"', 1)[1]
scenarios = [
    ('missing-empty', None, '', False, ''),
    ('missing-nonempty', None, 'expected\n', False, ''),
    ('unreadable-empty', '', '', False, 'unreadable'),
    ('unreadable-nonempty', 'expected\n', 'expected\n', False, 'unreadable'),
    ('failed-read-after-matching-bytes', 'expected\n', 'expected\n', False, 'partial'),
    ('valid-empty', '', '', True, ''),
    ('valid-newline-only', '\n\n', '', True, ''),
    ('valid-nonempty', 'expected\n', 'expected\n', True, ''),
    ('valid-legacy-trailing-newlines', 'expected\n\n', 'expected', True, ''),
    ('mismatch-empty-output', 'expected\n', '', False, ''),
    ('mismatch-nonempty-output', '', 'expected\n', False, ''),
]
results = []
with tempfile.TemporaryDirectory(prefix='plew-required-goldens-') as directory:
    root = Path(directory)
    copied = ('tests/harness/case-phase.sh', 'scripts/support/normal-case-dispatch.py',
              'scripts/support/watch-command.py', 'scripts/support/trace-command.py',
              'scripts/support/process_watch.py')
    for name in copied:
        p = root / name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_bytes((ROOT / name).read_bytes())
    tools = root / 'tools'
    tools.mkdir()
    def tool(name, body):
        p = tools / name
        p.write_text(body)
        p.chmod(0o755)
        return p
    compiler = tool('compiler', '''#!/bin/sh
case "$1" in
 --runtime) printf '// controlled runtime\n' ;;
 --gen) printf '#!/bin/sh\nprintf generated\n' ;;
 *) cat "$1" ;;
esac
''')
    tool('clang', '''#!/bin/sh
while [ "$#" -gt 0 ]; do
 case "$1" in *.ll) input="$1" ;; -o) shift; output="$1" ;; esac
 shift
done
cp "$input" "$output"
chmod +x "$output"
''')
    real_cat = shutil.which('cat')
    assert real_cat
    tool('cat', '#!' + sys.executable + '\n' + '''import os,sys
from pathlib import Path
if len(sys.argv)==2 and Path(sys.argv[1]).resolve()==Path(os.environ['GOLDEN_PATH']).resolve():
 fault=os.environ.get('GOLDEN_FAULT','')
 if fault:
  if fault=='partial':sys.stdout.buffer.write(Path(sys.argv[1]).read_bytes());sys.stdout.buffer.flush()
  print('controlled golden read failure',file=sys.stderr);sys.exit(7)
os.execv(os.environ['REAL_CAT'],[os.environ['REAL_CAT'],*sys.argv[1:]])
''')
    env = {**os.environ, 'PATH': str(tools) + os.pathsep + os.environ['PATH'],
           'PLEWC': str(compiler), 'PLEW_RT': '', 'PLEW_LD': '', 'JOBS': '1',
           'PLEW_TEST_JOBS': '1', 'PYTHONDONTWRITEBYTECODE': '1',
           'TMPDIR': str(root), 'REAL_CAT': real_cat, 'LC_ALL': 'C'}
    env.pop('PLEW_WATCH_EVENTS', None)  # Intended faults must not poison outer monitoring.
    for phase in ('part', 'gen'):
        path = root / ('tests/fixtures/part/fixture/Main.pw' if phase == 'part'
                       else 'tests/fixtures/gen/fixture/App.pw')
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text('#!/bin/sh\nprintf "%s" "$APP_OUTPUT"\n')
        golden = path.with_suffix('.out')
        script = ('set -e\npass=0; mcpass=0; mbrrpass=0; ppass=0; rpass=0; '
                  'prpass=0; skip=0; fail=0; failed=""\n' + part_block + normal_end
                  if phase == 'part' else 'set -e\nLC=true; rpass=0\n' + gen_loop + gen_end)
        for name, expected, output, success, fault in scenarios:
            if golden.exists():
                golden.chmod(0o600)
                golden.unlink()
            mechanism = fault
            if expected is not None:
                golden.write_text(expected)
            if fault == 'unreadable':
                golden.chmod(0)
                # Root can read chmod000. Keep a deterministic read-error control
                # there instead of silently skipping the required scenario.
                fault = '' if not os.access(golden, os.R_OK) else 'deny'
                mechanism = 'permissions' if not fault else 'controlled-permission-denial'
            p = subprocess.run(['/bin/sh', '-c', script], cwd=root,
                               env={**env, 'GOLDEN_PATH': str(golden), 'GOLDEN_FAULT': fault,
                                    'APP_OUTPUT': output}, capture_output=True, text=True, timeout=30)
            summary = (f'plewc: run=0  midcoverage=0  midborrowedread=0  panic=0  reject=0  part={int(success)}  partreject=0  skip=0  fail={int(not success)}'
                       if phase == 'part' else f'llvm-gen: pass={int(success)}  reject=0  skip=0  fail={int(not success)}')
            ok = p.returncode == (0 if success else 1) and summary in p.stdout
            terminal = p.stderr if phase == 'gen' else p.stdout
            if success:
                ok &= 'failing:' not in p.stdout
                if phase == 'gen':ok &= 'PASS gen/fixture' in terminal
            else:
                label = 'part/fixture' if phase == 'part' else 'fixture'
                failed_rows = [line for line in p.stdout.splitlines() if line.startswith('failing:')]
                # A compiler/link/program failure is not a golden-read RED.
                ok &= failed_rows in ([f'failing: {label}'], [f'failing: {label}(golden)'])
            if expected is None or mechanism:
                ok &= bool(p.stderr.strip())  # Keep actual read diagnostics visible.
            results.append(dict(phase=phase, scenario=name, read_fault=mechanism,
                                expected_exit=0 if success else 1, actual_exit=p.returncode,
                                passed=bool(ok), stdout=p.stdout, stderr=p.stderr))
            print(('PASS' if ok else 'FAIL') + f' required-golden/{phase}/{name}', flush=True)
        if golden.exists():golden.chmod(0o600)
if args.report:
    args.report.parent.mkdir(parents=True, exist_ok=True)
    names = ('tests/harness/test.sh', 'tests/harness/test-gen.sh',
             'tests/harness/case-phase.sh', 'scripts/support/normal-case-dispatch.py',
             'tests/tooling/test-required-goldens.py')
    args.report.write_text(json.dumps(dict(source_hashes={n:hashlib.sha256((ROOT/n).read_bytes()).hexdigest() for n in names},
                                          scenarios=results), indent=2)+'\n')
raise SystemExit(0 if all(r['passed'] for r in results) else 1)
