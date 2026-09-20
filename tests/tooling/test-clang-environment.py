#!/usr/bin/env python3
"""Real clang must ignore changing automatic cfg, while retaining explicit SDK."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'scripts/support'))
import clang_environment

config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
clang = str(Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang')
settings = clang_environment.settings()
with tempfile.TemporaryDirectory() as directory:
    root = Path(directory)
    triple = subprocess.check_output([clang, '-dumpmachine'], text=True).strip()
    # Clang searches both the target-only and target-driver config names.
    paths = [root / (triple + '.cfg'), root / (triple + '-clang.cfg'), root / 'clang.cfg']
    command = [clang, '--config-system-dir=' + directory, '--config-user-dir=' + directory, '-E', '-P', '-x', 'c', '-']
    for value in (1, 2):
        for path in paths:
            path.write_text(f'-DREVIEW_CONFIG={value}\n')
        output = subprocess.check_output(command, input='REVIEW_CONFIG\n', text=True,
                                         env={**os.environ, **settings})
        assert output.strip() == 'REVIEW_CONFIG', output
    explicit = clang_environment.settings({'SDKROOT': directory})
    assert explicit['SDKROOT'] == str(root.resolve())
    try:
        clang_environment.settings({'SDKROOT': str(root / 'missing')})
    except ValueError:
        pass
    else:
        raise AssertionError('invalid explicit SDK accepted')
if sys.platform == 'darwin':
    result = subprocess.run([clang, '-###', '-c', '-x', 'c', '/dev/null'], env={**os.environ, **settings}, capture_output=True, text=True, check=True)
    assert '"-isysroot" "' + settings['SDKROOT'] + '"' in result.stderr, result.stderr
print('PASS clang-explicit-environment')
