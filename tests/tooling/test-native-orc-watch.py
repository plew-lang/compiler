#!/usr/bin/env python3
"""Exercise native ORC build supervision through the actual test entry point."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class NativeOrcWatchTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='orc build watch ')
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.entry = self.root / 'tests/compiler/codegen/test-orc-native.py'
        self.entry.parent.mkdir(parents=True)
        shutil.copyfile(ROOT / 'tests/compiler/codegen/test-orc-native.py', self.entry)
        support = self.root / 'scripts/support'
        support.mkdir(parents=True)
        for name in ('trace-command.py', 'watch-command.py', 'process_watch.py', 'clang_environment.py'):
            shutil.copyfile(ROOT / 'scripts/support' / name, support / name)
        for path in ('native/llvm_backend.cpp', 'tests/compiler/codegen/OrcNative.cpp'):
            target = self.root / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text('// input hash fixture\n')
        tools = self.root / 'toolchain/bin'
        tools.mkdir(parents=True)
        (tools.parent / 'lib').mkdir()
        (tools.parent / 'lib/libLLVM.dylib').touch()
        self.config = tools / 'llvm-config'
        self.config.write_text('#!' + sys.executable + '\n' + '''import sys
from pathlib import Path
root=Path(__file__).resolve().parents[1]
print({'--bindir':str(root/'bin'),'--includedir':str(root/'include'),
       '--libdir':str(root/'lib'),'--version':'20.1.1'}[sys.argv[1]])
''')
        self.config.chmod(0o755)
        compiler = tools / 'clang++'
        compiler.write_text('#!' + sys.executable + '\n' + '''import json,os,signal,sys,time
from pathlib import Path
record=Path(os.environ['BUILD_ARGV'])
commands=json.loads(record.read_text()) if record.exists() else []
commands.append(sys.argv[1:])
record.write_text(json.dumps(commands))
for index in range(4):
 print('Running pass: FixturePass'+str(index),file=sys.stderr,flush=True)
 time.sleep(0.03)
mode=os.environ.get('FAKE_BUILD_MODE','success')
if mode=='failure':
 print('fixture C++ compile error',file=sys.stderr,flush=True)
 sys.exit(7)
if mode=='signal': os.kill(os.getpid(),signal.SIGTERM)
binary=Path(sys.argv[sys.argv.index('-o')+1])
binary.write_text('#!'+sys.executable+'\\n'+os.environ['NATIVE_SOURCE'])
binary.chmod(0o755)
''')
        compiler.chmod(0o755)
        self.events = self.root / 'events.jsonl'
        self.environment = dict(os.environ, LLVM_CONFIG=str(self.config),
            PLEW_WATCH_EVENTS=str(self.events), BUILD_ARGV=str(self.root / 'argv.json'),
            NATIVE_SOURCE="import sys\nprint('Symbols not found; duplicate definition; does not have terminator',file=sys.stderr)\nfor label in ['absent','matching','incompatible']:\n print('CHECK declaration-layout '+label,file=sys.stderr)\n if label=='incompatible': print('incompatible LLVM data layout',file=sys.stderr)\n print('END declaration-layout '+label,file=sys.stderr)\n")

    def invoke(self, mode='success', asan=False):
        result = subprocess.run([sys.executable, '-B', str(self.entry), *(['--asan'] if asan else [])],
            env=dict(self.environment, FAKE_BUILD_MODE=mode), capture_output=True, text=True, timeout=15)
        rows = [json.loads(line) for line in self.events.read_text().splitlines()] if self.events.exists() else []
        output = self.root / 'tmp/lazy-build/orc-native' / ('asan' if asan else 'normal')
        return result, rows, output

    def test_normal_build_progress_reaches_worker_channel_and_log(self):
        result, rows, output = self.invoke()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(any(row['kind'] == 'progress' and row['counter'] >= 4 for row in rows), rows)
        self.assertIn('FixturePass', (output / 'build.log').read_text())
        self.assertEqual(json.loads((output / 'summary.json').read_text())['status'], 'passed')
        commands = json.loads((self.root / 'argv.json').read_text())
        self.assertEqual(len(commands), 3)
        for command in commands[:2]:
            self.assertIn('-c', command)
            self.assertIn('-g', command)
            self.assertIn('-fdebug-pass-manager', command)
        self.assertNotIn('-g', commands[-1])
        self.assertTrue(all((output / name).exists() for name in ('backend.o', 'OrcNative.o')))
        self.assertEqual((output / 'stdout').read_bytes(), b'')

    def test_asan_uses_same_progress_transport(self):
        result, rows, output = self.invoke(asan=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(any(row['kind'] == 'progress' for row in rows), rows)
        self.assertTrue(all('-fsanitize=address' in command for command in json.loads((self.root / 'argv.json').read_text())))
        self.assertTrue((output / 'summary.json').exists())

    def test_compile_error_fails_and_cannot_publish_stale_success(self):
        output = self.root / 'tmp/lazy-build/orc-native/normal'
        output.mkdir(parents=True)
        for name in ('summary.txt', 'summary.json'):
            (output / name).write_text('stale success')
        result, rows, output = self.invoke(mode='failure')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('fixture C++ compile error', (output / 'build.log').read_text())
        self.assertTrue(any(row['kind'] == 'end' and row.get('exit_code') == 7 for row in rows), rows)
        self.assertFalse((output / 'summary.json').exists())
        self.assertFalse((output / 'summary.txt').exists())

    def test_compile_signal_remains_failure(self):
        result, rows, output = self.invoke(mode='signal')
        self.assertNotEqual(result.returncode, 0)
        self.assertTrue(any(row['kind'] == 'end' and row.get('exit_code') == -15 for row in rows), rows)
        self.assertFalse((output / 'summary.json').exists())


if __name__ == '__main__':
    unittest.main()
