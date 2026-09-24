#!/usr/bin/env python3
"""Fail-closed distribution boundaries; no installed LLVM needed for this gate."""
import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('standalone', ROOT / 'scripts/build/standalone.py')
standalone = importlib.util.module_from_spec(spec)
spec.loader.exec_module(standalone)


class DistributionBoundaries(unittest.TestCase):
    def test_accept_os_libraries(self):
        output = 'plewc:\n\t/usr/lib/libSystem.B.dylib (compatibility version 1.0.0)\n'
        self.assertEqual(standalone.audit_dependencies(output), ['/usr/lib/libSystem.B.dylib'])

    def test_reject_external_or_relative_dynamic_dependencies(self):
        for name in ('/opt/homebrew/lib/libLLVM.dylib', '@rpath/libLLVM.dylib',
                     '@loader_path/libzstd.dylib', 'libLLVM.dylib',
                     '/usr/lib/../../opt/other.dylib'):
            with self.subTest(name=name), self.assertRaises(ValueError):
                standalone.audit_dependencies(f'plewc:\n\t{name} (compatibility version 1.0.0)\n')

    def test_reject_empty_inspection(self):
        with self.assertRaises(ValueError):
            standalone.audit_dependencies('plewc:\n')

    def test_reject_dylib_support_dependency(self):
        with tempfile.TemporaryDirectory() as temporary:
            library = Path(temporary) / 'libSupport.dylib'
            library.touch()
            with self.assertRaises(ValueError):
                standalone.static_archive(library)

    def test_reject_archive_symlink_to_dylib(self):
        with tempfile.TemporaryDirectory() as temporary:
            library = Path(temporary) / 'libSupport.dylib'
            library.touch()
            alias = Path(temporary) / 'libSupport.a'
            alias.symlink_to(library)
            with self.assertRaises(ValueError):
                standalone.static_archive(alias)


if __name__ == '__main__':
    unittest.main()
