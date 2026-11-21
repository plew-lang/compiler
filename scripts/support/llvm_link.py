#!/usr/bin/env python3
"""Shared optimized link of raw Plew LLVM; raw fixed-point materials stay intact."""
import argparse
import hashlib
import json
import shlex
import os
import re
from pathlib import Path
import shutil
import subprocess
import sys

import clang_environment
import native_build

# Split aggregate loads immediately before promoting each SCC's private byval
# arguments, after its callees have been simplified and promoted.
# Finish ordinary module optimization before any sanitizer instrumentation.
# Field splitting alone can leave byval snapshots that ASan turns into copies.
# Keep fixpoint verification enabled; generated bodies can need several rounds.
ROOT = Path(__file__).resolve().parents[2]
PIPELINE_HEADER = ROOT / 'native/llvm_pipeline.h'
_pipeline_definition = re.findall(r'^#define PLEW_LLVM_PIPELINE "([^"\\]+)"$',
                                  PIPELINE_HEADER.read_text(), re.MULTILINE)
if len(_pipeline_definition) != 1:
    raise ValueError('invalid shared LLVM optimization pipeline definition')
PIPELINE = _pipeline_definition[0]


def optimizer(config):
    configured = os.environ.get('LLVM_OPT')
    path = shutil.which(configured) if configured else str(Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'opt')
    if not path or not os.access(path, os.X_OK):
        raise ValueError('selected LLVM opt is unavailable; set LLVM_OPT explicitly')
    return path


def selected_clang(config):
    # opt may introduce IR syntax/intrinsics newer than the system compiler.
    # Use the linker driver distributed with the selected LLVM toolchain.
    path = str(Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang')
    if not os.access(path, os.X_OK):
        raise ValueError('selected LLVM clang is unavailable')
    return path


def optimization_command(config, source, destination, clang=None):
    # Older bootstrap material has no triple. Never let opt simplify offsets
    # using its target-independent layout before the native clang link.
    clang_environment.apply()
    native_clang = clang or selected_clang(config)
    triple = subprocess.check_output([native_clang, '-dumpmachine'], text=True).strip()
    return [optimizer(config), '-mtriple=' + triple, '-debug-pass-manager', '-passes=' + PIPELINE,
            '-S', str(source), '-o', str(destination)]


def runtime_export_flags(platform=None):
    return ['-Wl,-export_dynamic'] if (platform or sys.platform) == 'darwin' else ['-Wl,--export-dynamic']


def profile_rpath(value):
    parts = value.split(',')
    if len(parts) != 3 or parts[:2] != ['-Wl', '-rpath']:
        return False
    path = parts[2]
    if not path or path.startswith('-'):
        return False
    if not path.startswith('@'):
        return True
    return any(path == base or path.startswith(base + '/')
               for base in ('@loader_path', '@executable_path'))


def validate_profile_libraries(libraries, platform=None):
    """Library inputs do not own compiler, target or export policy."""
    index = 0
    while index < len(libraries):
        value = libraries[index]
        if value in ('-L', '-l'):
            index += 1
            if index >= len(libraries) or not libraries[index] or libraries[index].startswith(('-', '@')):
                raise ValueError('invalid compiler ThinLTO library argument')
        elif value in ('-lto_library', '-load'):
            raise ValueError('compiler ThinLTO library arguments cannot select compiler plugins')
        elif value in runtime_export_flags(platform) or value == '-pthread':
            pass
        elif value.startswith(('-L', '-l')):
            pass
        elif profile_rpath(value):
            pass
        elif not value or value.startswith(('-', '@')):
            raise ValueError('compiler ThinLTO library arguments cannot override the link profile: ' + value)
        index += 1


def link_command(clang, source, runtime, destination, libraries=(), *,
                 input_kind='llvm', compiler_thinlto=False, platform=None):
    """One physical link policy, independent of how its input was produced."""
    if input_kind not in ('llvm', 'machine-object', 'thinlto-object'):
        raise ValueError('unknown link input kind')
    if compiler_thinlto and input_kind == 'machine-object':
        raise ValueError('a machine object cannot supply compiler ThinLTO')
    if input_kind == 'thinlto-object' and not compiler_thinlto:
        raise ValueError('a ThinLTO object requires the explicit ThinLTO profile')
    libraries = [str(value) for value in libraries]
    flags = []
    if compiler_thinlto:
        validate_profile_libraries(libraries, platform)
        flags.append('-flto=thin')
        flags.extend(flag for flag in runtime_export_flags(platform) if flag not in libraries)
        if (platform or sys.platform) == 'darwin':
            flags.append('-Wl,-mllvm,-debug-pass=Executions')
        else:
            flags.extend(['-fuse-ld=' + str(Path(clang).parent / 'ld.lld'),
                          '-Wl,--mllvm=-debug-pass=Executions'])
    return [str(clang), '-Xclang', '-fdebug-pass-manager', '-mllvm',
            '-debug-pass=Executions', '-w', '-O2', *flags, str(source),
            str(runtime), *libraries, '-o', str(destination)]


def tool_record(path, *, version=False):
    path = Path(path).resolve()
    if not path.is_file():
        raise ValueError('selected link tool is unavailable: ' + str(path))
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    result = {'path': str(path), 'sha256': digest.hexdigest()}
    if version:
        result['version'] = subprocess.check_output([str(path), '--version'], text=True).strip()
    return result


def selected_profile_tools(config, clang):
    selected = selected_clang(config)
    if Path(clang).resolve() != Path(selected).resolve():
        raise ValueError('compiler ThinLTO clang must belong to the selected LLVM toolchain')
    llvm_version = subprocess.check_output([config, '--version'], text=True).strip()
    major = int(llvm_version.split('.')[0])
    tools = {'llvm_version': llvm_version,
             'clang': tool_record(clang, version=True),
             'optimizer': tool_record(optimizer(config), version=True)}
    for name in ('clang', 'optimizer'):
        found = re.search(r'(?:clang|LLVM) version\s+(\d+)', tools[name]['version'])
        if not found or int(found.group(1)) != major:
            raise ValueError('compiler ThinLTO ' + name + ' version does not match selected LLVM')
    return tools


def compiler_link_provenance(config, command):
    return _record_compiler_link_driver(config, command, selected_profile_tools(config, command[0]))


def _record_compiler_link_driver(config, command, tools):
    clang_environment.apply()
    dry = subprocess.run([command[0], '-###', *command[1:]], text=True,
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
    commands = [shlex.split(line) for line in dry.stderr.splitlines() if line.lstrip().startswith('"')]
    compilations = [args for args in commands if '-cc1' in args]
    if not compilations or any('-flto=thin' not in args or '-emit-llvm-bc' not in args or '-emit-obj' in args for args in compilations):
        raise ValueError('actual clang compilation does not match the ThinLTO profile')
    drivers = [args for args in commands if args and Path(args[0]).name in ('ld', 'ld64', 'ld.lld', 'ld64.lld')]
    if len(drivers) != 1:
        raise ValueError('cannot identify actual compiler ThinLTO linker')
    driver = drivers[0]
    tools['linker'] = tool_record(driver[0], version=sys.platform != 'darwin')
    tools['driver_commands'] = dry.stderr
    tools['clang_environment'] = {name: os.environ.get(name) for name in ('CLANG_NO_DEFAULT_CONFIG', 'SDKROOT')}
    if sys.platform == 'darwin':
        selected = Path(subprocess.check_output([command[0], '--print-file-name=libLTO.dylib'], text=True).strip()).resolve()
        libraries = [Path(driver[index + 1]).resolve() for index, arg in enumerate(driver[:-1]) if arg == '-lto_library']
        if libraries != [selected]:
            raise ValueError('actual linker libLTO differs from selected LLVM clang')
        tools['lto_library'] = tool_record(selected)
    else:
        expected = (Path(command[0]).parent / 'ld.lld').resolve()
        if Path(driver[0]).resolve() != expected:
            raise ValueError('actual ThinLTO linker differs from selected LLVM lld')
        major = int(tools['llvm_version'].split('.')[0])
        found = re.search(r'LLD (\d+)', tools['linker']['version'])
        if not found or int(found.group(1)) != major:
            raise ValueError('ThinLTO linker version does not match selected LLVM')
    return tools


def validate_thinlto_object(config, source):
    with Path(source).open('rb') as stream:
        if stream.read(4) not in (b'BC\xc0\xde', b'\xde\xc0\x17\x0b'):
            raise ValueError('ThinLTO object is not LLVM bitcode')
    analyzer = Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'llvm-bcanalyzer'
    # Keep user-controlled filenames out of the analyzer's human-readable header.
    # Read the actual block record, never a matching filename or a full-LTO block.
    with Path(source).open('rb') as stream:
        result = subprocess.run([str(analyzer), '--disable-histogram', '-'], stdin=stream,
                                text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
    if not re.search(r'^\s*Block ID #\d+ \(GLOBALVAL_SUMMARY_BLOCK\):\s*$', result.stdout, re.MULTILINE):
        raise ValueError('LLVM bitcode lacks a ThinLTO summary')


def compiler_backend(config, output, sanitize=False):
    """Build the native module consumer against the compiler's selected LLVM."""
    clangxx = Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang++'
    include = subprocess.check_output([config, '--includedir'], text=True).strip()
    objects = []
    for name in ('llvm_backend', 'compiler_callbacks', 'compiler_execution'):
        target = Path(str(output) + '.' + name + '.o')
        command = [str(clangxx), '-std=c++17', '-O2', '-isystem', include,
                   '-c', str(ROOT / 'native' / (name + '.cpp')), '-o', str(target)]
        if sanitize:
            command += ['-fsanitize=address', '-fno-omit-frame-pointer']
        native_build.run(command, trace_log=Path(str(target) + '.trace.log'), clang=True, check=True)
        objects.append(str(target))
    # Optional compiler adapters are pulled only by execution hosts that use
    # them. Generic LLVM tools and bootstrap carriers need no callback symbol.
    archive = Path(str(output) + '.a')
    archive.unlink(missing_ok=True)
    native_build.run([str(clangxx.parent / 'llvm-ar'), 'rcs', str(archive), *objects], check=True)
    exports = runtime_export_flags()
    return [str(archive), '-lc++' if sys.platform == 'darwin' else '-lstdc++', *exports]



def link(config, log_prefix, source, runtime, destination, libraries=(), clang=None, *, with_backend=False, object_input=False, compiler_thinlto=False, lto_object_input=False):
    libraries = tuple(str(value) for value in libraries)
    if object_input and lto_object_input:
        raise ValueError('machine object and ThinLTO object inputs are exclusive')
    input_kind = 'thinlto-object' if lto_object_input else ('machine-object' if object_input else 'llvm')
    native_clang = clang or selected_clang(config)
    # Validate the requested contract before preparing outputs or a backend.
    link_command(native_clang, source, runtime, destination, libraries,
                 input_kind=input_kind, compiler_thinlto=compiler_thinlto)
    profile_tools = selected_profile_tools(config, native_clang) if compiler_thinlto else None
    if lto_object_input:
        validate_thinlto_object(config, source)
    prefix = Path(log_prefix)
    prefix.parent.mkdir(parents=True, exist_ok=True)
    if with_backend:
        libraries = [*libraries, *compiler_backend(config, Path(str(prefix) + '.backend.o'))]
    optimized = Path(str(prefix) + '.optimized.ll')
    steps = [] if object_input or lto_object_input else [
        (str(prefix) + '.opt.log', optimization_command(config, source, optimized, clang=clang)),
    ]
    steps += [
        (str(prefix) + '.log', link_command(native_clang,
            source if object_input or lto_object_input else optimized,
            runtime, destination, libraries, input_kind=input_kind,
            compiler_thinlto=compiler_thinlto)),
    ]
    for log, command in steps:
        if compiler_thinlto and log == str(prefix) + '.log':
            provenance = _record_compiler_link_driver(config, command, profile_tools)
            provenance['input_kind'] = input_kind
            provenance['command'] = command
            Path(str(prefix) + '.toolchain.json').write_text(json.dumps(provenance, indent=2) + '\n')
        print(f'[llvm-link] {log}: {command[0]}', file=sys.stderr, flush=True)
        subprocess.run([sys.executable, str(ROOT / 'scripts/support/trace-command.py'), log, '--', *command], check=True)
    if not compiler_thinlto:
        # Reused build prefixes must not attest a previous ThinLTO link.
        Path(str(prefix) + '.toolchain.json').unlink(missing_ok=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config', required=True)
    parser.add_argument('--log-prefix', required=True)
    inputs = parser.add_mutually_exclusive_group(required=True)
    inputs.add_argument('--llvm')
    inputs.add_argument('--object')
    inputs.add_argument('--lto-object')
    parser.add_argument('--compiler-thinlto', action='store_true')
    parser.add_argument('--compiler-backend', action='store_true')
    parser.add_argument('--runtime', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('libraries', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    libraries = args.libraries[1:] if args.libraries[:1] == ['--'] else args.libraries
    try:
        config = shutil.which(args.config)
        if not config:
            raise ValueError('selected llvm-config unavailable')
        link(config, args.log_prefix, args.object or args.lto_object or args.llvm, args.runtime, args.output, libraries, with_backend=args.compiler_backend, object_input=bool(args.object), compiler_thinlto=args.compiler_thinlto, lto_object_input=bool(args.lto_object))
    except subprocess.CalledProcessError as error:
        return error.returncode if error.returncode >= 0 else 128 - error.returncode
    except (ValueError, OSError) as error:
        print(f'llvm-link: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
