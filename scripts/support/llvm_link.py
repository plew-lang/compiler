#!/usr/bin/env python3
"""Shared optimized link of raw Plew LLVM; raw fixed-point materials stay intact."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys

PIPELINE = 'function(sroa,early-cse),cgscc(argpromotion)'
ROOT = Path(__file__).resolve().parents[2]


def optimizer(config):
    configured = os.environ.get('LLVM_OPT')
    path = shutil.which(configured) if configured else str(Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'opt')
    if not path or not os.access(path, os.X_OK):
        raise ValueError('selected LLVM opt is unavailable; set LLVM_OPT explicitly')
    return path


def optimization_command(config, source, destination):
    return [optimizer(config), '-debug-pass-manager', '-passes=' + PIPELINE,
            '-S', str(source), '-o', str(destination)]


def link(config, log_prefix, source, runtime, destination, libraries=(), clang=None):
    prefix = Path(log_prefix)
    prefix.parent.mkdir(parents=True, exist_ok=True)
    optimized = Path(str(prefix) + '.optimized.ll')
    steps = [
        (str(prefix) + '.opt.log', optimization_command(config, source, optimized)),
        (str(prefix) + '.log', [clang or shutil.which('clang'), '-Xclang', '-fdebug-pass-manager',
                               '-mllvm', '-debug-pass=Executions', '-w', '-O2', str(optimized),
                               str(runtime), *libraries, '-o', str(destination)]),
    ]
    for log, command in steps:
        print(f'[llvm-link] {log}: {command[0]}', file=sys.stderr, flush=True)
        subprocess.run([sys.executable, str(ROOT / 'scripts/support/trace-command.py'), log, '--', *command], check=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config', required=True)
    parser.add_argument('--log-prefix', required=True)
    parser.add_argument('--llvm', required=True)
    parser.add_argument('--runtime', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('libraries', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    libraries = args.libraries[1:] if args.libraries[:1] == ['--'] else args.libraries
    try:
        config = shutil.which(args.config)
        if not config:
            raise ValueError('selected llvm-config unavailable')
        link(config, args.log_prefix, args.llvm, args.runtime, args.output, libraries)
    except subprocess.CalledProcessError as error:
        return error.returncode if error.returncode >= 0 else 128 - error.returncode
    except (ValueError, OSError) as error:
        print(f'llvm-link: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
