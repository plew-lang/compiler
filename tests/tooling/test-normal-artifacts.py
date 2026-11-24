#!/usr/bin/env python3
"""Exercise real normal workers and their run-owned scratch lifetime."""
import importlib.util
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import tempfile
import time
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]


class ScratchLifetime(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='plew-artifact-control-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for name in ['tests/harness/case-phase.sh', *[
                str(p.relative_to(ROOT)) for p in (ROOT / 'scripts/support').glob('*.py')]]:
            target = self.root / name
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(ROOT / name, target)
        tools = self.root / 'tools'
        tools.mkdir()
        compiler = tools / 'compiler'
        compiler.write_text('#!' + sys.executable + '\n' + '''import os,sys
from pathlib import Path
if '/reject/' in sys.argv[1] or '/partreject/' in sys.argv[1]:
 os.write(int(os.environ['_PLEW_COMPILER_FAILURE_FD']),b'plew.compiler.failure.v1\\n'+os.environ['_PLEW_COMPILER_FAILURE_ID'].encode()+b'\\nsource\\n')
 print('expected rejection',file=sys.stderr);sys.exit(1)
sys.stdout.buffer.write(Path(sys.argv[1]).read_bytes())
''')
        compiler.chmod(0o755)
        clang = tools / 'clang'
        clang.write_text('''#!/bin/sh
while [ "$#" -gt 0 ]; do
 case "$1" in *.ll) input="$1";; -o) shift; output="$1";; esac
 shift
done
cp "$input" "$output"
chmod +x "$output"
''')
        clang.chmod(0o755)
        self.env = {**os.environ, 'PATH': str(tools) + os.pathsep + os.environ['PATH'],
                    'PLEWC': str(compiler), 'PLEW_RT': '', 'PLEW_LD': '',
                    'TMPDIR': str(self.root), 'PYTHONDONTWRITEBYTECODE': '1'}
        for key in ['PLEW_WATCH_EVENTS', '_PLEW_NORMAL_CASE_ROOT', 'PLEW_NORMAL_ARTIFACT_ROOT']:
            self.env.pop(key, None)

    def fixture(self, phase='run', body='printf "expected\\n"', golden='expected\n'):
        p = self.root / 'tests/fixtures' / phase
        p = p / 'sample/Main.pw' if phase in ('part', 'partreject') else p / 'sample.pw'
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text('#!/bin/sh\n' + body + '\n')
        p.with_suffix('.out').write_text(golden)
        p.with_suffix('.panic').write_text('expected panic\n')
        p.with_suffix('.err').write_text('expected rejection\n')
        return str(p.relative_to(self.root))

    def command(self, phase, path):
        return ['/bin/sh', 'tests/harness/case-phase.sh', '--worker', phase, path]

    def records(self):
        return [json.loads(p.read_text()) for p in (self.root / 'tmp/normal-cases').rglob('*.json')
                if not p.name.endswith('.tmp')]

    def execute(self, phase, body='printf "expected\\n"', golden='expected\n'):
        path = self.fixture(phase, body, golden)
        return subprocess.run(self.command(phase, path), cwd=self.root, env=self.env,
                              capture_output=True, timeout=20)

    def test_success_has_durable_record_and_retires_payload(self):
        result = self.execute('run')
        self.assertEqual((result.returncode, result.stdout), (0, b'PASS sample\n'))
        rows = self.records()
        self.assertEqual(len(rows), 1, 'successful worker has no durable case result; generated LLVM remains in shared TMPDIR')
        row = rows[0]
        self.assertEqual(row['status'], 'pass')
        self.assertTrue(row['retired'])
        self.assertGreater(row['artifact_bytes'], 0)
        self.assertFalse(Path(row['directory']).exists())
        self.assertFalse((self.root / 't_sample.ll').exists())

    def test_all_five_phase_outcomes_keep_accounting(self):
        for phase in ['run', 'panic', 'reject', 'part', 'partreject']:
            body = 'printf "expected panic\\n" >&2; exit 134' if phase == 'panic' else 'printf "expected\\n"'
            result = self.execute(phase, body)
            self.assertEqual(result.returncode, 0)
            self.assertTrue(result.stdout.startswith(b'PASS '), result)
        self.assertEqual(len(self.records()), 5)
        self.assertTrue(all(r['status'] == 'pass' and r['retired'] for r in self.records()))

    def test_fail_and_program_crash_retain_artifacts_despite_worker_exit_zero(self):
        for body in ['printf "wrong\\n"', 'printf "expected\\n"; exit 7', 'kill -TERM $$']:
            result = self.execute('run', body)
            self.assertEqual(result.returncode, 0)
            self.assertTrue(result.stdout.startswith(b'FAIL '))
        rows = self.records()
        self.assertEqual(len(rows), 3)
        for row in rows:
            self.assertEqual(row['status'], 'fail')
            self.assertFalse(row['retired'])
            self.assertTrue((Path(row['directory']) / 't_sample.ll').is_file())

    def test_simultaneous_identical_cases_are_isolated(self):
        path = self.fixture(body='sleep 0.1; printf "expected\\n"')
        jobs = [subprocess.Popen(self.command('run', path), cwd=self.root, env=self.env,
                                 stdout=subprocess.PIPE, stderr=subprocess.PIPE) for _ in range(2)]
        for p in jobs:
            out, err = p.communicate(timeout=20)
            self.assertEqual((p.returncode, out), (0, b'PASS sample\n'), err)
        rows = self.records()
        self.assertEqual(len({r['directory'] for r in rows}), 2)
        self.assertTrue(all(r['retired'] for r in rows))

    def test_simultaneous_dispatch_runs_are_isolated(self):
        path = self.fixture(body='sleep 0.1; printf "expected\\n"')
        command = [sys.executable, '-B', 'scripts/support/normal-case-dispatch.py', 'run', path]
        jobs = [subprocess.Popen(command, cwd=self.root, env={**self.env, 'JOBS': '1'},
                                 stdout=subprocess.PIPE, stderr=subprocess.PIPE) for _ in range(2)]
        for p in jobs:
            out, err = p.communicate(timeout=20)
            self.assertEqual((p.returncode, out), (0, b'PASS sample\n'), err)
        rows = self.records()
        self.assertEqual(len(rows), 2)
        self.assertEqual(len({str(Path(r['directory']).parent) for r in rows}), 2)
        self.assertTrue(all(r['retired'] for r in rows))

    def test_temp_creation_failure_does_not_fall_back(self):
        parent = self.root / 'not-a-directory'
        parent.write_text('protected')
        self.env['_PLEW_NORMAL_CASE_ROOT'] = str(parent)
        result = self.execute('run')
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn(b'PASS ', result.stdout)
        self.assertEqual(parent.read_text(), 'protected')
        self.assertFalse((self.root / 't_sample.ll').exists())

    def test_dispatch_cancellation_retains_pending_and_recovers_children(self):
        path = self.fixture(body='echo $$ > "$PIDFILE"; exec sleep 50')
        pidfile = self.root / 'child.pid'
        env = {**self.env, 'PIDFILE': str(pidfile), 'JOBS': '1'}
        p = subprocess.Popen([sys.executable, '-B', 'scripts/support/normal-case-dispatch.py', 'run', path],
                             cwd=self.root, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            deadline = time.monotonic() + 10
            while not pidfile.exists():
                self.assertIsNone(p.poll())
                self.assertLess(time.monotonic(), deadline)
                time.sleep(0.02)
            child = int(pidfile.read_text())
            p.terminate()
            p.communicate(timeout=8)
            self.assertEqual(p.returncode, 143)
            rows = self.records()
            self.assertEqual(len(rows), 1)
            self.assertEqual(rows[0]['status'], 'pending')
            self.assertTrue(Path(rows[0]['directory']).is_dir())
            deadline = time.monotonic() + 2
            while time.monotonic() < deadline:
                try: os.kill(child, 0)
                except ProcessLookupError: break
                time.sleep(0.02)
            else: self.fail('cancelled case left running child')
        finally:
            if p.poll() is None: p.kill(); p.wait()
            p.stdout.close(); p.stderr.close()

    def artifact_module(self):
        spec = importlib.util.spec_from_file_location('normal_artifacts', ROOT / 'scripts/support/normal_case_artifacts.py')
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module

    def test_record_is_published_before_deletion_and_write_failure_preserves_payload(self):
        module = self.artifact_module()
        for failed in [False, True]:
            work = module.begin(self.root / 'owned', 'run', Path('sample.pw'))
            payload = work / 'sample.ll'; payload.write_text('ir')
            original = module.shutil.rmtree
            def delete(path):
                record = json.loads(Path(str(work) + '.json').read_text())
                self.assertEqual(record['result'], 'PASS sample')
                self.assertEqual(record['status'], 'pass')
                original(path)
            if failed:
                with mock.patch.object(module, 'publish', side_effect=OSError('write refused')):
                    with self.assertRaises(OSError): module.finish(work, 'PASS sample')
                self.assertTrue(payload.exists())
            else:
                with mock.patch.object(module.shutil, 'rmtree', side_effect=delete): module.finish(work, 'PASS sample')
                self.assertFalse(work.exists())

    def test_real_publication_boundaries_preserve_payload_on_io_failure(self):
        module = self.artifact_module()
        for operation in ['file-sync', 'rename', 'directory-sync']:
            with self.subTest(operation=operation):
                work = module.begin(self.root / 'owned', 'run', Path('sample.pw'))
                payload = work / 'sample.ll'; payload.write_text('ir')
                if operation == 'rename':
                    patch = mock.patch.object(module.os, 'replace', side_effect=OSError('rename refused'))
                else:
                    real_sync = module.os.fsync
                    calls = []
                    def sync(fd):
                        calls.append(fd)
                        if len(calls) == (1 if operation == 'file-sync' else 2):
                            raise OSError('sync refused')
                        real_sync(fd)
                    patch = mock.patch.object(module.os, 'fsync', side_effect=sync)
                with patch:
                    with self.assertRaises(OSError): module.finish(work, 'PASS sample')
                self.assertTrue(payload.exists())
                record = json.loads(Path(str(work) + '.json').read_text())
                self.assertFalse(record['retired'])

    def test_symlink_outside_owned_directory_is_never_followed(self):
        module = self.artifact_module()
        outside = self.root / 'keep'; outside.mkdir(); (outside / 'asset').write_text('keep')
        work = module.begin(self.root / 'owned', 'run', Path('sample.pw'))
        (work / 'outside').symlink_to(outside, target_is_directory=True)
        module.finish(work, 'PASS sample')
        self.assertEqual((outside / 'asset').read_text(), 'keep')
        work = module.begin(self.root / 'owned', 'run', Path('sample.pw'))
        work.rmdir(); work.symlink_to(outside, target_is_directory=True)
        with self.assertRaises(ValueError): module.finish(work, 'PASS sample')
        self.assertEqual((outside / 'asset').read_text(), 'keep')


if __name__ == '__main__':
    unittest.main()
