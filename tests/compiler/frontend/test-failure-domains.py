#!/usr/bin/env python3
"""Manual scoped diagnostic-domain API test; full producer/CLI gates are separate."""
import argparse
import hashlib
import json
import os
import shutil
from pathlib import Path
import subprocess
import sys

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--compiler', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
root = Path(__file__).resolve().parents[3]
carrier = args.compiler.resolve()
out = args.out.resolve()
out.mkdir(parents=True, exist_ok=False)
sys.path.insert(0, str(root / 'scripts/support'))
from clang_environment import apply
apply()
config = os.environ.get('LLVM_CONFIG') or shutil.which('llvm-config') or '/opt/homebrew/opt/llvm/bin/llvm-config'
clang = Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang'
watch = [sys.executable, '-B', str(root / 'scripts/support/watch-command.py'), '--']
trace = [sys.executable, '-B', str(root / 'scripts/support/trace-command.py')]
def input_hashes():
    paths = sorted([*root.glob('src/**/*.pw'), *root.glob('std/**/*.pw'),
                    root / 'Plew.toml', root / 'Plew.lock', Path(__file__).resolve(),
                    *Path(__file__).parent.glob('*FailureDomains.*'),
                    *Path(__file__).parent.glob('DiagnosticValues.*')])
    return {str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in paths if p.is_file()}

inputs = input_hashes()
(out / 'inputs.json').write_text(json.dumps(inputs, indent=2) + '\n')
report = {'scope': 'scoped diagnostic values and named producer/cache conversions; not CLI/consumer completion',
          'link_compiler': str(clang), 'link_optimization': '-O0',
          'carrier_sha256': hashlib.sha256(carrier.read_bytes()).hexdigest(),
          'diag_sha256': hashlib.sha256((root / 'src/Diag.pw').read_bytes()).hexdigest(),
          'inputs_sha256': hashlib.sha256((out / 'inputs.json').read_bytes()).hexdigest(),
          'cases': []}
try:
    with (out / 'runtime.c').open('wb') as output:
        subprocess.run([*watch, str(carrier), '--runtime'], cwd=root, stdout=output, check=True)
    for name in ['DiagnosticValues', 'FailureDomains', 'ProducerFailureDomains']:
        source = Path(__file__).with_name(name + '.pw')
        llvm, executable = out / (name + '.ll'), out / name
        case = {'name': name, 'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest()}
        report['cases'].append(case)
        with (out / (name + '.compile.stderr')).open('wb') as log, llvm.open('wb') as output:
            compiled = subprocess.run([*trace, str(out / (name + '.compile.log')), '--',
                str(carrier), '--trace-phases', str(source)],
                cwd=root, stderr=log, stdout=output)
        case['compile_exit'] = compiled.returncode
        if compiled.returncode:
            raise AssertionError(f'{name}: compilation failed; see {name}.compile.stderr')
        subprocess.run([*watch, str(clang), '-O0', str(llvm), str(out / 'runtime.c'),
                        '-o', str(executable)], check=True)
        ran = subprocess.run([*watch, str(executable)], capture_output=True)
        (out / (name + '.stdout')).write_bytes(ran.stdout)
        (out / (name + '.stderr')).write_bytes(ran.stderr)
        case['run_exit'] = ran.returncode
        assert ran.returncode == 0, (name, ran.returncode, ran.stderr)
        assert ran.stdout == source.with_suffix('.out').read_bytes(), (name, ran.stdout)
        assert ran.stderr == source.with_suffix('.err').read_bytes(), (name, ran.stderr)
        case['result'] = 'passed'
    assert input_hashes() == inputs, 'test inputs changed during execution'
    report['result'] = 'passed'
except (AssertionError, OSError, subprocess.SubprocessError) as error:
    report['result'] = 'failed'
    report['error'] = str(error)
finally:
    (out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report), flush=True)
sys.exit(0 if report['result'] == 'passed' else 1)
