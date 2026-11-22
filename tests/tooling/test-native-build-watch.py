#!/usr/bin/env python3
"""Build supervision through native harness entries, with their assertions intact."""
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('orc_watch_fixture', Path(__file__).with_name('test-native-orc-watch.py'))
fixture_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(fixture_module)


class NativeBuildWatchTests(unittest.TestCase):
    def setUp(self):
        self.fixture = fixture_module.NativeOrcWatchTests()
        self.fixture.setUp()
        self.addCleanup(self.fixture.doCleanups)
        self.root = self.fixture.root
        self.entry = self.root / 'tests/compiler/codegen/test-physical-signature.py'
        self.entry.write_bytes((ROOT / 'tests/compiler/codegen/test-physical-signature.py').read_bytes())
        for name in ('PhysicalSignature.pw', 'PhysicalSignature.c'):
            self.entry.with_name(name).write_text('// input fixture\n')
        support = self.root / 'scripts/support'
        helper = ROOT / 'scripts/support/native_build.py'
        if helper.exists():
            (support / helper.name).write_bytes(helper.read_bytes())
        tools = self.root / 'toolchain/bin'
        (tools / 'clang').symlink_to('clang++')
        compiler = tools / 'plewc'
        compiler.write_text('#!' + sys.executable + '\nimport sys\nprint("; fixture IR" if "--runtime" not in sys.argv else "/* runtime */")\n')
        compiler.chmod(0o755)
        optimizer = tools / 'opt'
        optimizer.write_text('#!' + sys.executable + '\nfrom pathlib import Path\nimport sys\nPath(sys.argv[sys.argv.index("-o")+1]).write_text("; __asan_report_load8\\n")\n')
        optimizer.chmod(0o755)
        self.environment = dict(self.fixture.environment, PLEWC=str(compiler),
                                NATIVE_SOURCE='print("ok")\n')

    def invoke(self, mode='success', asan=False):
        result = subprocess.run([sys.executable, '-B', str(self.entry), *(['--asan'] if asan else [])],
            env=dict(self.environment, FAKE_BUILD_MODE=mode), capture_output=True, text=True, timeout=15)
        events = [json.loads(line) for line in self.fixture.events.read_text().splitlines()] if self.fixture.events.exists() else []
        output = self.root / 'tmp/value-abi/physical-signature' / ('asan' if asan else 'normal')
        return result, events, output

    def test_shared_backend_build_reports_actual_progress(self):
        compiler = self.root / 'toolchain/bin/clang++'
        compiler.write_text(compiler.read_text().replace('for index in range(4):',
            "for index in range(4 if '-fdebug-pass-manager' in sys.argv else 0):"))
        support = self.root / 'scripts/support'
        (support / 'llvm_link.py').write_bytes((ROOT / 'scripts/support/llvm_link.py').read_bytes())
        (self.root / 'native/llvm_pipeline.h').write_bytes((ROOT / 'native/llvm_pipeline.h').read_bytes())
        for name in ('compiler_callbacks.cpp', 'compiler_execution.cpp'):
            (self.root / 'native' / name).write_text('// fixture input\n')
        archiver = self.root / 'toolchain/bin/llvm-ar'
        archiver.write_text('#!' + sys.executable + '\nimport sys\nfrom pathlib import Path\nPath(sys.argv[2]).write_bytes(b"archive")\n')
        archiver.chmod(0o755)
        code = ('import sys;sys.path.insert(0,' + repr(str(support)) + ');'
                'import llvm_link;llvm_link.compiler_backend('
                + repr(str(self.fixture.config)) + ',' + repr(str(self.root / 'backend.o')) + ')')
        result = subprocess.run([sys.executable, '-B', '-c', code], env=self.environment,
                                capture_output=True, text=True, timeout=15)
        self.assertEqual(result.returncode, 0, result.stderr)
        events = [json.loads(line) for line in self.fixture.events.read_text().splitlines()]
        self.assertEqual(sum(row['kind'] == 'progress' and row['counter'] >= 4 for row in events), 3)
        self.assertTrue((self.root / 'backend.o.a').exists())

    def test_unique_trace_prefix_preserves_each_stage(self):
        support = self.root / 'scripts/support'
        command = [sys.executable, '-c', 'import sys;print(123,file=sys.stderr)']
        code = ('import sys;sys.path.insert(0,' + repr(str(support)) + ');import native_build;'
                'command=' + repr(command) + ';'
                'native_build.run(command,trace_prefix=' + repr(str(self.root / 'trace')) + ',check=True);'
                'native_build.run(command,trace_prefix=' + repr(str(self.root / 'trace')) + ',check=True)')
        result = subprocess.run([sys.executable, '-B', '-c', code], env=self.environment,
                                capture_output=True, text=True, timeout=15)
        self.assertEqual(result.returncode, 0, result.stderr)
        logs = list(self.root.glob('trace-*.log'))
        self.assertEqual(len(logs), 2)
        self.assertTrue(all(path.read_bytes() == b'123\n' for path in logs))

    def test_physical_build_retains_debug_objects_and_real_progress(self):
        result, events, output = self.invoke()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(any(row['kind'] == 'progress' and row['counter'] >= 4 for row in events), events)
        self.assertTrue((output / 'summary.txt').read_text().startswith('status=passed\n'))
        commands = json.loads((self.root / 'argv.json').read_text())
        self.assertGreaterEqual(len(commands), 4)
        for command in commands[:-1]:
            self.assertIn('-c', command)
            self.assertIn('-g', command)
            self.assertIn('-fdebug-pass-manager', command)
            self.assertNotIn('-debug-pass=Executions', command)
        self.assertNotIn('-g', commands[-1])
        self.assertFalse(any(name.endswith(('.cpp', '.c', '.ll')) for name in commands[-1]))
        self.assertEqual((output / 'stdout').read_bytes(), b'ok\n')
        self.assertEqual((output / 'stdout.log').read_bytes(), b'')

    def test_asan_keeps_instrumentation_and_progress(self):
        result, events, output = self.invoke(asan=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(any(row['kind'] == 'progress' for row in events), events)
        self.assertTrue((output / 'summary.txt').exists())
        self.assertTrue(all('-fsanitize=address' in command for command in json.loads((self.root / 'argv.json').read_text())))

    def test_native_build_failure_is_non_success(self):
        result, events, output = self.invoke(mode='failure')
        self.assertNotEqual(result.returncode, 0)
        self.assertTrue(any(row['kind'] == 'end' and row.get('exit_code') == 7 for row in events), events)
        self.assertFalse((output / 'summary.txt').exists())


if __name__ == '__main__':
    unittest.main()
