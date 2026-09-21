#!/usr/bin/env python3
"""Supplement failures must propagate, including a broken sanitizer control."""
import contextlib
import importlib.util
import io
import os
from pathlib import Path
import subprocess
import tempfile
from unittest.mock import patch

root = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('ownership', root / 'tests/sanitizer/asan-ownership.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
with tempfile.TemporaryDirectory() as directory:
    sandbox = Path(directory)
    (sandbox / 'tests/sanitizer').mkdir(parents=True)
    (sandbox / 'input.pw').write_text('fixture')
    (sandbox / 'tests/sanitizer/asan-ownership-cases.txt').write_text('input.pw\n')
    env = {'TMP': directory, 'OPT': '/fixture/bin/opt', 'CLANG': '/fixture/bin/clang', 'RT': '/fixture/runtime.c', 'PLEW_TEST_JOBS': '1'}
    for failure in (None, 'control-missed', 'instrument', 'link', 'compile', 'diagnostic'):
        def run(argv, **kwargs):
            label = Path(argv[2]).stem
            code, log = 0, ''
            if label == 'control-run':
                code = 1
                log = 'ERROR: AddressSanitizer: heap-use-after-free'
                if failure == 'control-missed':
                    code, log = 0, ''
            if label == failure or (failure == 'compile' and label.startswith('compile-')):
                code = 7
            if failure == 'diagnostic' and label.startswith('compile-'):
                log = 'ERROR: AddressSanitizer: heap-use-after-free'
            Path(argv[2]).write_text(log)
            if label == 'control-run':
                assert kwargs['stderr'] is not None
            return subprocess.CompletedProcess(argv, code)
        with patch.object(module, 'ROOT', sandbox), patch.dict(os.environ, env), \
             patch.object(module.clang_environment, 'apply'), patch.object(module.subprocess, 'run', side_effect=run), \
             contextlib.redirect_stdout(io.StringIO()):
            try:
                module.main()
            except RuntimeError:
                assert failure is not None, failure
            else:
                assert failure is None, failure
        assert not (sandbox / 'plewc_asan_ownership').exists()
    labels = []
    def staged_run(argv, **kwargs):
        label = Path(argv[2]).stem
        labels.append(label)
        text = 'ERROR: AddressSanitizer: heap-use-after-free' if label == 'control-run' else ''
        Path(argv[2]).write_text(text)
        if label == 'link':
            Path(argv[-1]).touch()
        return subprocess.CompletedProcess(argv, 1 if label == 'control-run' else 0)
    with patch.object(module, 'ROOT', sandbox), patch.dict(os.environ, env), \
         patch.object(module.clang_environment, 'apply'), patch.object(module.subprocess, 'run', side_effect=staged_run), \
         contextlib.redirect_stdout(io.StringIO()):
        module.main('prepare')
        assert (sandbox / 'plewc_asan_ownership').is_file()
        assert labels == ['control-instrument', 'control-link', 'control-run', 'instrument', 'link']
        labels.clear()
        module.main('check')
        assert labels == ['compile-0']
        assert not (sandbox / 'plewc_asan_ownership').exists()
        try:
            module.main('check')
        except RuntimeError:
            pass
        else:
            raise AssertionError('missing prepared compiler was accepted')
print('PASS raw-asan-failure-propagation')
