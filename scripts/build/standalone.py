#!/usr/bin/env python3
"""Build an isolated, statically linked compiler candidate (not a release yet).

Build-machine LLVM/clang and explicitly supplied static support libraries are
required. Nothing is installed or downloaded, and canonical binaries/seeds are
never outputs. The candidate still uses the checkout's std via a staging link.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import shlex
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment
import llvm_link


def digest(path):
    value = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            value.update(block)
    return value.hexdigest()


def query(config, *args):
    return subprocess.check_output([config, *args], text=True).strip()


def static_archive(path):
    path = Path(path).resolve(strict=True)
    if path.suffix != '.a' or not path.is_file():
        raise ValueError(f'expected a static archive: {path}')
    return str(path)


def audit_dependencies(output):
    dependencies = []
    for line in output.splitlines()[1:]:
        name = line.strip().split(' (compatibility version', 1)[0]
        if not name:
            continue
        if not name.startswith(('/usr/lib/', '/System/Library/')) or '..' in Path(name).parts:
            raise ValueError(f'non-OS dynamic dependency: {name}')
        dependencies.append(name)
    if not dependencies:
        raise ValueError('empty dynamic dependency inspection')
    return dependencies


def input_files():
    # Record source inputs, not generated candidates or unrelated scratch files.
    files = [ROOT / 'Plew.toml', ROOT / 'Plew.lock']
    for directory in ('src', 'std', 'native'):
        files.extend(sorted(path for path in (ROOT / directory).rglob('*') if path.is_file()))
    return {str(path.relative_to(ROOT)): digest(path) for path in files}


def build(args):
    recipe_path = Path(__file__).with_name('standalone-toolchain.json')
    recipe = json.loads(recipe_path.read_text())
    if (sys.platform, platform.machine()) != (recipe['platform'], recipe['machine']):
        raise ValueError('this initial distribution recipe supports macOS/arm64 only')
    config = shutil.which(args.llvm_config)
    if not config:
        raise ValueError('selected llvm-config is unavailable')
    version = query(config, '--version')
    if version != recipe['llvm_version']:
        raise ValueError(f'expected LLVM {recipe["llvm_version"]}, got {version}')
    archives = [static_archive(path) for path in shlex.split(
        query(config, '--link-static', '--libfiles', *recipe['components']))]
    archives.extend(static_archive(path) for path in args.static_dependency)
    carrier = Path(args.carrier).resolve(strict=True)
    output = Path(args.output).resolve()
    # A fresh directory is the output contract; no merge with previous evidence.
    output.mkdir(parents=True, exist_ok=False)
    (output / 'std').symlink_to(ROOT / 'std', target_is_directory=True)
    source_inputs = input_files()
    manifest = {
        'scope': 'static compiler candidate; resources/CLI not yet bundled',
        'recipe': recipe, 'recipe_sha256': digest(recipe_path),
        'llvm_config': config, 'llvm_version': version,
        'host_target': query(config, '--host-target'),
        'carrier': str(carrier), 'carrier_sha256': digest(carrier),
        'source_inputs': source_inputs,
        'archives': {path: digest(path) for path in archives},
        'environment': clang_environment.apply(),
        'optimizer': llvm_link.optimizer(config),
        'clang': llvm_link.selected_clang(config),
        'pipeline': llvm_link.PIPELINE,
        'commands': [],
    }
    for name in ('optimizer', 'clang'):
        manifest[name + '_sha256'] = digest(manifest[name])
    record = output / 'build.json'

    def run(command, destination=None, trace=None):
        manifest['commands'].append(command)
        record.write_text(json.dumps(manifest, indent=2) + '\n')
        wrapper = ROOT / 'scripts/support' / ('trace-command.py' if trace else 'watch-command.py')
        watched = [sys.executable, str(wrapper)]
        if trace:
            watched.append(str(output / trace))
        watched.extend(['--', *command])
        if destination:
            with destination.open('wb') as stream:
                subprocess.run(watched, stdout=stream, check=True, cwd=ROOT)
        else:
            subprocess.run(watched, check=True, cwd=ROOT)

    raw = output / 'compiler.ll'
    runtime = output / 'runtime.c'
    binary = output / 'plewc'
    print('[standalone] compile source', file=sys.stderr, flush=True)
    run([str(carrier), '--trace-phases', str(ROOT / 'src/_.pw')], raw, 'compile.log')
    run([str(carrier), '--runtime'], runtime)
    libraries = [*archives, *recipe['system_libraries'], *recipe['link_flags']]
    deployment = '-mmacosx-version-min=' + recipe['minimum_macos']
    # This build worker is not a second distributed executable. Its library API
    # is the same entry the single-file driver will call directly.
    worker = output / 'llvm-object'
    clangxx = str(Path(query(config, '--bindir')) / 'clang++')
    manifest['clangxx_sha256'] = digest(clangxx)
    print('[standalone] build native object backend', file=sys.stderr, flush=True)
    run([clangxx, '-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
         '-isystem', query(config, '--includedir'), deployment,
         str(ROOT / 'native/llvm_backend.cpp'), str(ROOT / 'native/llvm_object_main.cpp'),
         *archives, *[flag for flag in recipe['system_libraries'] if flag != '-lc++'],
         *recipe['link_flags'], '-o', str(worker)])
    manifest['worker_dynamic_dependencies'] = audit_dependencies(
        subprocess.check_output(['/usr/bin/otool', '-L', str(worker)], text=True))
    print('[standalone] emit native object', file=sys.stderr, flush=True)
    run([str(worker), str(raw), str(output / 'compiler.o'), recipe['target_cpu'], '--trace'],
        trace='object.log')
    # The user-side linker sees only native objects. Compilation of runtime C
    # belongs to the distribution build and will become an embedded resource.
    run(['/usr/bin/clang', deployment, '-O2', '-c', str(runtime),
         '-o', str(output / 'runtime.o')])
    run(['/usr/bin/clang', deployment, str(output / 'compiler.o'), str(output / 'runtime.o'),
         *libraries, '-o', str(binary)])
    print('[standalone] audit dynamic dependencies', file=sys.stderr, flush=True)
    inspection = subprocess.check_output(['/usr/bin/otool', '-L', str(binary)], text=True)
    (output / 'dependencies.txt').write_text(inspection)
    manifest['dynamic_dependencies'] = audit_dependencies(inspection)
    if source_inputs != input_files() or manifest['carrier_sha256'] != digest(carrier):
        raise ValueError('compiler inputs changed during build')
    manifest.update(binary_sha256=digest(binary), binary_bytes=binary.stat().st_size,
                    raw_llvm_sha256=digest(raw), runtime_sha256=digest(runtime), status='success')
    record.write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'[standalone] PASS: {binary} ({manifest["binary_bytes"]} bytes)', flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--llvm-config', required=True)
    parser.add_argument('--carrier', default=str(ROOT / 'plewc'))
    parser.add_argument('--output', required=True, help='new staging directory')
    parser.add_argument('--static-dependency', action='append', default=[],
                        help='explicit support .a, e.g. libzstd.a; repeatable')
    args = parser.parse_args()
    try:
        build(args)
    except subprocess.CalledProcessError as error:
        return error.returncode if error.returncode > 0 else 128 - error.returncode
    except (ValueError, OSError) as error:
        print(f'standalone: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
