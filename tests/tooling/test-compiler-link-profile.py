#!/usr/bin/env python3
"""Explicit ThinLTO inputs cannot silently degrade to ordinary object linking."""
from pathlib import Path
import sys
import unittest
import tempfile
import subprocess
import os
from unittest import mock

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import llvm_link
import native_build


class CompilerLinkProfile(unittest.TestCase):
    def command(self, kind='llvm', thin=True, platform='darwin', libraries=()):
        return llvm_link.link_command('/selected/clang', 'program', 'runtime.c',
                                      'output', libraries, input_kind=kind,
                                      compiler_thinlto=thin, platform=platform)

    def test_text_and_lto_object_share_runtime_and_policy(self):
        for kind in ('llvm', 'thinlto-object'):
            with self.subTest(kind=kind):
                command = self.command(kind)
                self.assertIn('-flto=thin', command)
                self.assertIn('-Wl,-export_dynamic', command)
                self.assertIn('runtime.c', command)
                self.assertIn('program', command)
                self.assertEqual(command[-2:], ['-o', 'output'])

    def test_plain_machine_object_keeps_existing_flags(self):
        command = self.command('machine-object', False)
        self.assertNotIn('-flto=thin', command)
        self.assertNotIn('-Wl,-export_dynamic', command)
        self.assertIn('program', command)

    def test_machine_object_cannot_claim_program_lto(self):
        with self.assertRaisesRegex(ValueError, 'machine object'):
            self.command('machine-object')

    def test_lto_object_requires_explicit_profile(self):
        with self.assertRaisesRegex(ValueError, 'ThinLTO profile'):
            self.command('thinlto-object', False)

    def test_unknown_artifact_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'input kind'):
            self.command('unknown')

    def test_libraries_cannot_override_the_profile(self):
        for flag in ('-fno-lto', '-flto=full', '@flags', '-Xclang',
                     '-Wl,-unexported_symbols_list,hidden', '-fuse-ld=foreign'):
            with self.subTest(flag=flag):
                with self.assertRaisesRegex(ValueError, 'library'):
                    self.command(libraries=[flag])

    def test_library_and_rpath_inputs_remain_available(self):
        command = self.command(libraries=['-L', '/some library', '-lLLVM',
                                          'backend.a', '-Wl,-rpath,/runtime',
                                          '-Wl,-rpath,@loader_path/../lib',
                                          '-Wl,-rpath,@executable_path'])
        self.assertIn('/some library', command)
        self.assertIn('-Wl,-rpath,/runtime', command)
        self.assertIn('-Wl,-rpath,@loader_path/../lib', command)
        self.assertIn('-Wl,-rpath,@executable_path', command)

    def test_backend_export_policy_is_not_duplicated(self):
        command = self.command(libraries=['backend.a', '-Wl,-export_dynamic'])
        self.assertEqual(command.count('-Wl,-export_dynamic'), 1)

    def test_elf_export_policy(self):
        command = self.command(platform='linux')
        self.assertIn('-Wl,--export-dynamic', command)
        self.assertNotIn('-Wl,-export_dynamic', command)


class CompilerLinkTools(unittest.TestCase):
    config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')

    def test_actual_tools_are_recorded(self):
        clang = llvm_link.selected_clang(self.config)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'main.ll'
            source.write_text('define i32 @main() { ret i32 0 }\n')
            runtime = root / 'runtime.c'
            runtime.write_text('int runtime_value(void) { return 42; }\n')
            command = llvm_link.link_command(clang, source, runtime, root / 'program', compiler_thinlto=True)
            info = llvm_link.compiler_link_provenance(self.config, command)
            self.assertEqual(Path(info['clang']['path']).resolve(), Path(clang).resolve())
            for name in ('clang', 'optimizer', 'linker'):
                self.assertEqual(len(info[name]['sha256']), 64)
            self.assertTrue(info['driver_commands'])
            if sys.platform == 'darwin':
                self.assertEqual(len(info['lto_library']['sha256']), 64)

    def test_clang_override_cannot_mix_toolchains(self):
        with self.assertRaisesRegex(ValueError, 'clang'):
            llvm_link.compiler_link_provenance(self.config, ['/foreign/clang'])

    def test_actual_non_lto_compilation_cannot_publish_provenance(self):
        llvm_link.clang_environment.apply()
        clang = llvm_link.selected_clang(self.config)
        tools = llvm_link.selected_profile_tools(self.config, clang)
        wrong = subprocess.CompletedProcess([], 0, stdout='', stderr='"' + clang + '" "-cc1" "-emit-obj"\n')
        with mock.patch.object(llvm_link.subprocess, 'run', return_value=wrong):
            with self.assertRaisesRegex(ValueError, 'actual clang compilation'):
                llvm_link._record_compiler_link_driver(self.config, [clang], tools)

    def test_machine_bytes_are_not_lto_bitcode(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'object.o'
            source.write_bytes(b'not bitcode')
            with self.assertRaisesRegex(ValueError, 'bitcode'):
                llvm_link.validate_thinlto_object(self.config, source)

    def test_full_lto_summary_is_not_a_thin_summary(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'object.o'
            source.write_bytes(b'BC\xc0\xde')
            analyzed = subprocess.CompletedProcess([], 0, stdout='Block ID #24 (FULL_LTO_GLOBALVAL_SUMMARY_BLOCK)', stderr='')
            with mock.patch.object(llvm_link.subprocess, 'run', return_value=analyzed):
                with self.assertRaisesRegex(ValueError, 'summary'):
                    llvm_link.validate_thinlto_object(self.config, source)

    def test_real_summary_and_bare_bitcode_are_distinct(self):
        clang = llvm_link.selected_clang(self.config)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'source.c'
            source.write_text('int value(void) { return 42; }\n')
            thin = root / 'thin.o'
            bare = root / 'bare.o'
            native_build.run([clang, '-flto=thin', '-c', str(source), '-o', str(thin)], check=True, clang=True, trace_prefix=Path(source).parent / 'compile')
            native_build.run([clang, '-emit-llvm', '-c', str(source), '-o', str(bare)], check=True, clang=True, trace_prefix=Path(source).parent / 'compile')
            llvm_link.validate_thinlto_object(self.config, thin)
            with self.assertRaisesRegex(ValueError, 'summary'):
                llvm_link.validate_thinlto_object(self.config, bare)
            for name in ('GLOBALVAL_SUMMARY_BLOCK.o', 'innocent\n  Block ID #20 (GLOBALVAL_SUMMARY_BLOCK):\n.o'):
                with self.subTest(filename=name):
                    renamed = root / name
                    renamed.write_bytes(bare.read_bytes())
                    with self.assertRaisesRegex(ValueError, 'summary'):
                        llvm_link.validate_thinlto_object(self.config, renamed)
            renamed_thin = root / 'thin-GLOBALVAL_SUMMARY_BLOCK.o'
            renamed_thin.write_bytes(thin.read_bytes())
            llvm_link.validate_thinlto_object(self.config, renamed_thin)


class CompilerLinkExecution(unittest.TestCase):
    config = CompilerLinkTools.config

    def test_real_cross_translation_unit_links(self):
        llvm_link.clang_environment.apply()
        clang = llvm_link.selected_clang(self.config)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            program = root / 'main.c'
            program.write_text('extern int runtime_value(void); int main(void) { return runtime_value() != 42; }\n')
            runtime = root / 'runtime.c'
            runtime.write_text('int runtime_value(void) { return 42; }\n')
            text, thin, machine = [root / name for name in ('main.ll', 'thin.o', 'machine.o')]
            native_build.run([clang, '-O1', '-S', '-emit-llvm', str(program), '-o', str(text)], check=True, clang=True, trace_prefix=Path(program).parent / 'compile')
            native_build.run([clang, '-O1', '-flto=thin', '-c', str(program), '-o', str(thin)], check=True, clang=True, trace_prefix=Path(program).parent / 'compile')
            native_build.run([clang, '-O1', '-c', str(program), '-o', str(machine)], check=True, clang=True, trace_prefix=Path(program).parent / 'compile')
            for kind, source in [('llvm', text), ('thinlto-object', thin), ('machine-object', machine)]:
                with self.subTest(kind=kind):
                    prefix = root / 'reused-link'
                    output = root / (kind + '.bin')
                    llvm_link.link(self.config, prefix, source, runtime, output,
                                   object_input=kind == 'machine-object',
                                   lto_object_input=kind == 'thinlto-object',
                                   compiler_thinlto=kind != 'machine-object')
                    result = subprocess.run([str(output)], capture_output=True)
                    self.assertEqual((result.returncode, result.stdout, result.stderr), (0, b'', b''))
                    if kind != 'machine-object':
                        import json
                        info = json.loads(Path(str(prefix) + '.toolchain.json').read_text())
                        self.assertEqual(info['input_kind'], kind)
                        bindir = Path(clang).parent
                        symbols = subprocess.check_output([str(bindir / 'llvm-nm'), '-g', '--defined-only', str(output)], text=True)
                        self.assertIn('runtime_value', symbols)
                        entry = '_main' if sys.platform == 'darwin' else 'main'
                        assembly = subprocess.check_output([str(bindir / 'llvm-objdump'), '-d', '--disassemble-symbols=' + entry, str(output)], text=True)
                        self.assertNotIn('runtime_value', assembly, 'cross-TU constant call was not optimized')
                    else:
                        self.assertFalse(Path(str(prefix) + '.toolchain.json').exists())

    def test_invalid_profile_preserves_destination_and_skips_backend(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            destination = root / 'existing'
            destination.write_bytes(b'keep')
            prefix = root / 'logs' / 'link'
            with mock.patch.object(llvm_link, 'compiler_backend') as backend:
                with self.assertRaisesRegex(ValueError, 'machine object'):
                    llvm_link.link(self.config, prefix, root / 'input.o', root / 'runtime.c', destination,
                                   object_input=True, compiler_thinlto=True, with_backend=True)
                backend.assert_not_called()
            self.assertEqual(destination.read_bytes(), b'keep')
            self.assertFalse(prefix.parent.exists())

    def test_competing_flags_fail_before_output_preparation(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            destination = root / 'existing'
            destination.write_bytes(b'keep')
            prefix = root / 'logs' / 'link'
            with mock.patch.object(llvm_link, 'compiler_backend') as backend:
                with self.assertRaisesRegex(ValueError, 'library'):
                    llvm_link.link(self.config, prefix, root / 'input.ll', root / 'runtime.c', destination,
                                   ['-fno-lto'], compiler_thinlto=True, with_backend=True)
                backend.assert_not_called()
            self.assertEqual(destination.read_bytes(), b'keep')
            self.assertFalse(prefix.parent.exists())

    def test_incompatible_optimizer_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            optimizer = Path(directory) / 'opt'
            optimizer.write_text('#!/bin/sh\nprintf "LLVM version 999.0.0\\n"\n')
            optimizer.chmod(0o755)
            with mock.patch.dict(os.environ, {'LLVM_OPT': str(optimizer)}):
                with self.assertRaisesRegex(ValueError, 'optimizer version'):
                    llvm_link.selected_profile_tools(self.config, llvm_link.selected_clang(self.config))


if __name__ == '__main__':
    unittest.main()
