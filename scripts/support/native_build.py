#!/usr/bin/env python3
"""Adapt native test commands to the existing semantic-progress supervisor."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile
import os


def prepared(command, *, clang=False):
    command = list(map(str, command))
    if clang:
        command[1:1] = ['-Xclang', '-fdebug-pass-manager', '-mllvm', '-debug-pass=Executions']
    return command


def run(command, *, trace_log=None, trace_prefix=None, clang=False, **options):
    if trace_prefix is not None:
        if trace_log is not None:
            raise ValueError('choose an exact trace log or a unique trace prefix')
        path = Path(trace_prefix)
        path.parent.mkdir(parents=True, exist_ok=True)
        descriptor, trace_log = tempfile.mkstemp(prefix=path.name + '-', suffix='.log', dir=path.parent)
        os.close(descriptor)
    prefix = [sys.executable, '-B', str(Path(__file__).resolve())]
    if trace_log is not None:
        prefix += ['--log', str(trace_log)]
    if clang:
        prefix += ['--clang']
    return subprocess.run([*prefix, '--', *map(str, command)], **options)


def check_output(command, **options):
    return run(command, stdout=subprocess.PIPE, check=True, **options).stdout


def logged(command, *, stdout_path, stderr_path, trace_log=None, clang=False,
           cwd=None, env=None, check=True):
    with Path(stdout_path).open('wb') as out, Path(stderr_path).open('wb') as error:
        return run(command, stdout=out, stderr=error, trace_log=trace_log,
                   clang=clang, cwd=cwd, env=env, check=check)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--log', type=Path)
    parser.add_argument('--clang', action='store_true')
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ['--'] else args.command
    if not command or (args.clang and args.log is None):
        parser.error('command is required; clang progress also requires --log')
    from process_watch import run as supervise
    sys.exit(supervise(prepared(command, clang=args.clang),
                       log_path=args.log, traced=args.log is not None))
