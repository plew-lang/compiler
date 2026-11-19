#!/usr/bin/env python3
"""Exercise the owned-module native ThinLTO producer and ordinary object control."""
from pathlib import Path
import argparse
import json
import os
import subprocess
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment
import llvm_link


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--llvm-config', default='/opt/homebrew/opt/llvm/bin/llvm-config')
    parser.add_argument('--output-dir', type=Path, required=True)
    parser.add_argument('--compiler', type=Path, help='fresh compiler exposing the explicit ThinLTO worker mode')
    parser.add_argument('--worker', type=Path)
    parser.add_argument('--sanitize-worker', action='store_true')
    args = parser.parse_args()
    clang_environment.apply()
    root = args.output_dir.resolve()
    root.mkdir(parents=True, exist_ok=True)
    config = args.llvm_config
    bindir = Path(subprocess.check_output([config, '--bindir'], text=True).strip())
    include = subprocess.check_output([config, '--includedir'], text=True).strip()
    library = Path(config).parent.parent / 'lib'
    if not (library / 'libLLVM.dylib').exists():
        library = Path(subprocess.check_output([config, '--libdir'], text=True).strip())
    worker = args.worker.resolve() if args.worker else root / 'worker'
    if not args.worker:
        command = [str(bindir / 'clang++'), '-std=c++17', '-O0', '-isystem', include,
                   str(ROOT / 'native/llvm_backend.cpp'), str(ROOT / 'native/llvm_object_main.cpp'),
                   '-L' + str(library), '-lLLVM', '-o', str(worker)]
        if args.sanitize_worker:
            command += ['-fsanitize=address', '-fno-omit-frame-pointer']
        with (root / 'build.log').open('wb') as log:
            subprocess.run([sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--', *command],
                           stdout=log, stderr=subprocess.STDOUT, check=True)
    worker_env = dict(os.environ)
    if args.sanitize_worker:
        worker_env['ASAN_OPTIONS'] = 'detect_leaks=1:halt_on_error=1'
        symbols = subprocess.check_output([str(bindir / 'llvm-nm'), '-u', str(worker)], text=True)
        assert '__asan_report_load' in symbols and '__asan_report_store' in symbols
    lifetime = root / 'lifetime'
    lifetime_command = [str(bindir / 'clang++'), '-std=c++17', '-O0', '-isystem', include,
                        str(ROOT / 'native/llvm_backend.cpp'), str(ROOT / 'tests/compiler/codegen/ThinLtoObjectLifetime.cpp'),
                        '-L' + str(library), '-lLLVM', '-o', str(lifetime)]
    if args.sanitize_worker:
        lifetime_command += ['-fsanitize=address', '-fno-omit-frame-pointer']
    with (root / 'lifetime-build.log').open('wb') as log:
        subprocess.run([sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--', *lifetime_command], stdout=log, stderr=subprocess.STDOUT, check=True)
    kept = subprocess.run([str(lifetime), str(root)], capture_output=True, env=worker_env)
    (root / 'lifetime.stderr').write_bytes(kept.stderr)
    assert kept.returncode == 0 and kept.stdout == b'PASS borrowed module remains live\n', kept
    assert b'missing/lifetime.o' in kept.stderr and b'Sanitizer' not in kept.stderr
    source = root / 'input.ll'
    source.write_text('declare i32 @runtime_value()\ndefine i32 @main() {\n %value = call i32 @runtime_value()\n %ok = icmp eq i32 %value, 42\n %result = select i1 %ok, i32 0, i32 1\n ret i32 %result\n}\n')
    output = root / 'thin.o'
    command = [str(worker), str(source), str(output), '', '--thinlto', '--trace']
    result = subprocess.run(command, capture_output=True, env=worker_env)
    (root / 'producer.stderr').write_bytes(result.stderr)
    assert result.returncode == 0, ('ThinLTO producer unavailable or failed', result.returncode, result.stderr.decode())
    llvm_link.validate_thinlto_object(config, output)
    assert b'llvm:ir-shared completed=' in result.stderr and b'llvm:thinlto-prelink completed=' in result.stderr
    assert b'llvm:codegen completed=' not in result.stderr
    disassembled = subprocess.check_output([str(bindir / 'llvm-dis'), str(output), '-o', '-'], text=True)
    assert '"target-cpu"="generic"' in disassembled
    if sys.platform == 'darwin':
        assert 'apple-macosx' in disassembled and 'apple-darwin' not in disassembled
    runtime = root / 'runtime.c'
    runtime.write_text('int runtime_value(void) { return 42; }\n')
    binary = root / 'program'
    llvm_link.link(config, root / 'link', output, runtime, binary,
                   lto_object_input=True, compiler_thinlto=True)
    assert subprocess.run([str(binary)]).returncode == 0
    machine = root / 'machine.o'
    assert subprocess.run([str(worker), str(source), str(machine), ''], capture_output=True, env=worker_env).returncode == 0
    try:
        llvm_link.validate_thinlto_object(config, machine)
    except ValueError:
        pass
    else:
        raise AssertionError('ordinary object became bitcode')
    machine_binary = root / 'machine-program'
    llvm_link.link(config, root / 'machine-link', machine, runtime, machine_binary, object_input=True)
    assert subprocess.run([str(machine_binary)]).returncode == 0
    failures = []
    for label, text, expected in [
        ('foreign-target', 'target triple = "wasm32-unknown-unknown"\ndefine i32 @main(){ret i32 0}\n', 'requires native triple'),
        ('wrong-layout', 'target datalayout = "e-p:32:32"\ndefine i32 @main(){ret i32 0}\n', 'incompatible LLVM data layout'),
        ('sanitizer', 'define i32 @main() sanitize_address {ret i32 0}\n', 'do not support sanitizer output'),
        ('invalid-ir', 'define i32 @main(){ret i64 0}\n', 'error:')]:
        invalid = root / (label + '.ll')
        invalid.write_text(text)
        preserved = root / (label + '.o')
        preserved.write_bytes(b'previous artifact')
        failed = subprocess.run([str(worker), str(invalid), str(preserved), '', '--thinlto'], capture_output=True, env=worker_env)
        assert failed.returncode == 1 and expected in failed.stderr.decode(), (label, failed.returncode, failed.stderr)
        assert preserved.read_bytes() == b'previous artifact'
        failures.append(label)
    failed = subprocess.run([str(worker), str(source), str(root / 'missing/output.o'), '', '--thinlto'], capture_output=True, env=worker_env)
    assert failed.returncode == 1 and not (root / 'missing/output.o').exists()
    failures.append('output-error')
    if args.compiler:
        compiler = args.compiler.resolve()
        plew_source = root / 'Main.pw'
        plew_source.write_text('use @Std/Io only { print }\nfn main() { print("42") }\n')
        plew_runtime = root / 'plew.runtime.c'
        plew_runtime.write_bytes(subprocess.check_output([str(compiler), '--runtime']))
        outputs = []
        for thin in [False, True]:
            artifact = root / ('plew-thin.o' if thin else 'plew-machine.o')
            mode = '--emit-thinlto-object' if thin else '--emit-object'
            emitted = subprocess.run([str(compiler), mode, str(artifact), '--target-cpu', 'apple-m1', str(plew_source)], capture_output=True)
            assert emitted.returncode == 0 and emitted.stdout == b'', emitted.stderr
            program = root / ('plew-thin' if thin else 'plew-machine')
            llvm_link.link(config, root / ('plew-thin-link' if thin else 'plew-machine-link'), artifact, plew_runtime, program,
                           object_input=not thin, lto_object_input=thin, compiler_thinlto=thin)
            executed = subprocess.run([str(program)], capture_output=True)
            assert executed.returncode == 0 and executed.stdout == b'42\n', executed
            outputs.append(executed.stdout)
        assert outputs[0] == outputs[1]
    (root / 'result.json').write_text(json.dumps({'status': 0, 'fresh_plew_cli': bool(args.compiler), 'thin_summary': True, 'program_status': 0, 'ordinary_machine_control': True, 'failure_controls': failures, 'sanitized_worker': args.sanitize_worker, 'borrowed_module_lifetime': True, 'asan_options': worker_env.get('ASAN_OPTIONS') if args.sanitize_worker else None}, indent=2) + '\n')
    print('PASS native ThinLTO producer, runtime link and ordinary machine control')


if __name__ == '__main__':
    main()
