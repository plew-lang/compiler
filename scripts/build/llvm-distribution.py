#!/usr/bin/env python3
"""Build optimized LLVM libraries in an isolated prefix for standalone.py.

No Homebrew installation is modified. The source archive is version/hash pinned;
clang is a build-machine input, not a dependency of the distributed executable.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shlex
import shutil
import subprocess
import sys
import tarfile

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment
import llvm_lto

VERSION = '20.1.1'
SOURCE_SHA256 = '4d5ebbd40ce1e984a650818a4bb5ae86fc70644dec2e6d54e78b4176db3332e0'
SOURCE_URL = f'https://github.com/llvm/llvm-project/releases/download/llvmorg-{VERSION}/llvm-project-{VERSION}.src.tar.xz'


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def observed(command):
    # Adapt real CMake compile/link/install events to the existing watchdog.
    # No timer or process-liveness event extends the progress deadline.
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    for line in process.stdout:
        progress = line.startswith('-- ') or re.search(r'Building |Linking |Built target ', line)
        print(('[trace-phase] ' if progress else '') + line.rstrip(), file=sys.stderr, flush=True)
    return process.wait()


def configure_options(clang, clangxx, tablegen, sdk, prefix):
    return [
        '-G', 'Unix Makefiles', '-DCMAKE_BUILD_TYPE=Release',
        f'-DCMAKE_C_COMPILER={clang}', f'-DCMAKE_CXX_COMPILER={clangxx}',
        '-DCMAKE_C_FLAGS_RELEASE=-O3 -DNDEBUG', '-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG',
        f'-DCMAKE_OSX_SYSROOT={sdk}', '-DCMAKE_OSX_DEPLOYMENT_TARGET=26.0',
        f'-DCMAKE_INSTALL_PREFIX={prefix}', '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON',
        '-DLLVM_TARGETS_TO_BUILD=AArch64', '-DLLVM_ENABLE_ASSERTIONS=OFF',
        '-DLLVM_ENABLE_RTTI=ON', '-DLLVM_ENABLE_EH=OFF', '-DLLVM_ENABLE_LTO=OFF',
        # Build both from the same objects for a controlled static/dylib comparison.
        '-DLLVM_BUILD_LLVM_DYLIB=ON', '-DLLVM_LINK_LLVM_DYLIB=OFF',
        '-DLLVM_INCLUDE_TESTS=OFF', '-DLLVM_INCLUDE_BENCHMARKS=OFF',
        '-DLLVM_INCLUDE_EXAMPLES=OFF', '-DLLVM_ENABLE_ZSTD=OFF',
        '-DLLVM_ENABLE_ZLIB=ON', '-DLLVM_ENABLE_LIBXML2=OFF',
        '-DLLVM_ENABLE_LIBEDIT=OFF', '-DLLVM_ENABLE_TERMINFO=OFF',
        '-DLLVM_ENABLE_FFI=OFF', f'-DLLVM_TABLEGEN={tablegen}',
    ]


def build(args):
    if (sys.platform, platform.machine()) != ('darwin', 'arm64'):
        raise ValueError('the current distribution recipe supports macOS/arm64 only')
    archive = Path(args.source_archive).resolve(strict=True)
    if digest(archive) != SOURCE_SHA256:
        raise ValueError('LLVM source archive checksum mismatch')
    config = shutil.which(args.llvm_tools_config)
    if not config:
        raise ValueError('build-machine llvm-config is unavailable')
    def query(*options):
        return subprocess.check_output([config, *options], text=True).strip()
    if query('--version') != VERSION:
        raise ValueError(f'build tools must be LLVM {VERSION}')
    tools = Path(query('--bindir'))
    cmake = shutil.which('cmake')
    if not cmake:
        raise ValueError('cmake is unavailable')
    environment = clang_environment.apply()
    lto = llvm_lto.settings(config, args.jobs) if args.lto == 'thin' else None
    output = Path(args.output).resolve()
    output.mkdir(parents=True, exist_ok=False)
    prefix, build_dir = output / 'install', output / 'build'
    record = output / 'build.json'
    manifest = dict(source_url=SOURCE_URL, source_sha256=SOURCE_SHA256,
                    environment=environment, commands=[], status='building', lto=lto,
                    tools={str(p): digest(p) for p in [Path(cmake), Path(config),
                           tools / 'clang', tools / 'clang++', tools / 'llvm-tblgen']})
    if lto:
        for name in ('library', 'archiver'):
            manifest['tools'][lto[name]] = digest(lto[name])
    def run(command):
        manifest['commands'].append(command)
        record.write_text(json.dumps(manifest, indent=2) + '\n')
        with (output / 'build.log').open('ab') as log:
            subprocess.run([sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--',
                            sys.executable, __file__, '--observe', *command],
                           stdout=log, stderr=log, check=True)
    try:
        with tarfile.open(archive) as source:
            top = f'llvm-project-{VERSION}.src/'
            members = [m for m in source.getmembers()
                       if any(m.name.startswith(top + name + '/') for name in ('llvm', 'cmake', 'third-party'))]
            source.extractall(output, members=members, filter='data')
        source_dir = output / f'llvm-project-{VERSION}.src' / 'llvm'
        options = configure_options(str(tools / 'clang'), str(tools / 'clang++'),
                                    str(tools / 'llvm-tblgen'), environment['SDKROOT'], str(prefix))
        if lto:
            options.remove('-DLLVM_ENABLE_LTO=OFF')
            options.extend(['-DLLVM_ENABLE_LTO=Thin', f'-DCMAKE_LIBTOOL={lto["archiver"]}',
                            '-DCMAKE_EXE_LINKER_FLAGS=' + shlex.join(lto['flags']),
                            '-DCMAKE_SHARED_LINKER_FLAGS=' + shlex.join(lto['flags'])])
        run([cmake, '-S', str(source_dir), '-B', str(build_dir), *options])
        run([cmake, '--build', str(build_dir), '--parallel', str(args.jobs),
             '--target', 'LLVM', 'llvm-config', 'opt'])
        built_config = build_dir / 'bin/llvm-config'
        recipe = json.loads(Path(__file__).with_name('standalone-toolchain.json').read_text())
        libraries = subprocess.check_output([str(built_config), '--link-static', '--libnames',
                                             *recipe['components']], text=True).split()
        components = ['llvm-headers', 'llvm-config', 'opt', 'LLVM',
                      *[name.removeprefix('lib').removesuffix('.a') for name in libraries]]
        for component in dict.fromkeys(components):
            run([cmake, '--install', str(build_dir), '--component', component])
        shutil.copyfile(source_dir / 'LICENSE.TXT', prefix / 'LICENSE.TXT')
        manifest['archives'] = {name: digest(prefix / 'lib' / name) for name in libraries}
        manifest['cmake_cache_sha256'] = digest(build_dir / 'CMakeCache.txt')
        manifest['compile_commands_sha256'] = digest(build_dir / 'compile_commands.json')
        for tool, expected in manifest['tools'].items():
            if digest(tool) != expected:
                raise ValueError(f'build tool changed: {tool}')
        manifest['status'] = 'success'
    except BaseException:
        manifest['status'] = 'failed'
        raise
    finally:
        record.write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'PASS: {prefix}/bin/llvm-config')


def main():
    if sys.argv[1:2] == ['--observe']:
        return observed(sys.argv[2:])
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-archive', required=True, help=SOURCE_URL)
    parser.add_argument('--llvm-tools-config', required=True)
    parser.add_argument('--output', required=True, help='new isolated directory')
    parser.add_argument('--jobs', type=int, default=max(1, (os.cpu_count() or 1) // 2))
    parser.add_argument('--lto', choices=('off', 'thin'), default='off')
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error('--jobs must be positive')
    try:
        build(args)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f'llvm-distribution: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
