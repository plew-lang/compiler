"""Manual Mid boundary audit; expected outputs describe the specification."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[3]
CASES = Path(__file__).resolve().parent
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--out', type=Path, required=True)
parser.add_argument('--cases', type=Path)
parser.add_argument('--asan', action='store_true')
parser.add_argument('--compiler', type=Path, default=ROOT / 'plewc')
parser.add_argument('--llvm-prefix', type=Path, default=Path('/opt/homebrew/opt/llvm@22'))
args = parser.parse_args()
CASES = args.cases.resolve() if args.cases else ROOT / 'tests/fixtures/run'
names = ['generic_deinit', 'generic_deinit_impl', 'generic_deinit_unused', 'generic_deinit_lifetimes', 'generic_callee_binder_identity', 'view_parenthesized', 'view_parenthesized_places']
sources = sorted(CASES.glob('*.pw')) if args.cases else [CASES / (name + '.pw') for name in names]
out = args.out.resolve()
out.mkdir(parents=True, exist_ok=False)
compiler = args.compiler.resolve()
clang = str(args.llvm_prefix / 'bin/clang')
watch = [sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--']
env = dict(os.environ, CLANG_NO_DEFAULT_CONFIG='1')
if sys.platform == 'darwin' and not env.get('SDKROOT'):
    env['SDKROOT'] = subprocess.check_output(['xcrun', '--show-sdk-path'], text=True).strip()
if args.asan:
    env.update(ASAN_OPTIONS='detect_leaks=1:exitcode=86', LSAN_OPTIONS='exitcode=87')
flags = ['-fsanitize=address'] if args.asan else []

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = [compiler, Path(__file__).resolve(), *sources, *(source.with_suffix('.out') for source in sources)]
hashes = {str(path): digest(path) for path in inputs}

def execute(command, stdout, stderr):
    with stdout.open('wb') as output, stderr.open('wb') as error:
        return subprocess.run(watch + command, cwd=ROOT, env=env,
                              stdout=output, stderr=error, timeout=180).returncode

assert execute([str(compiler), '--runtime'], out/'runtime.c', out/'runtime.log') == 0
assert execute([clang, *flags, '-w', '-c', str(out/'runtime.c'), '-o', str(out/'runtime.o')],
               out/'runtime-build.out', out/'runtime-build.log') == 0
results = []
for source in sources:
    name = source.stem
    llvm = out / (name + '.ll')
    expected = source.with_suffix('.out').read_text()
    item = dict(case=name, expected=expected)
    command = [str(compiler), *(['--asan'] if args.asan else []), str(source)]
    item['compile_exit'] = execute(command, llvm, out/(name+'.compile.log'))
    if item['compile_exit'] == 0:
        if args.asan:
            instrumented = out/(name+'.asan.ll')
            assert execute([str(args.llvm_prefix/'bin/opt'), '-passes=asan', '-S',
                            str(llvm), '-o', str(instrumented)],
                           out/(name+'.instrument.out'), out/(name+'.instrument.log')) == 0
            assert '__asan_' in instrumented.read_text()
            llvm = instrumented
        executable = out/name
        item['link_exit'] = execute([clang, *flags, '-O0', '-w', str(llvm),
                                     str(out/'runtime.o'), '-o', str(executable)],
                                    out/(name+'.link.out'), out/(name+'.link.log'))
        if item['link_exit'] == 0:
            item['run_exit'] = execute([str(executable)], out/(name+'.stdout'), out/(name+'.stderr'))
            item['actual'] = (out/(name+'.stdout')).read_text()
            item['stderr'] = (out/(name+'.stderr')).read_text()
    item['passed'] = item.get('run_exit') == 0 and item.get('actual') == expected and not item.get('stderr')
    results.append(item)
    print(json.dumps(item), flush=True)
unchanged = all(digest(Path(path)) == value for path, value in hashes.items())
summary = dict(asan=args.asan, compiler=str(compiler), input_sha256=hashes,
               inputs_unchanged=unchanged, cases=results)
(out/'summary.json').write_text(json.dumps(summary, indent=2)+'\n')
sys.exit(0 if unchanged and all(item['passed'] for item in results) else 1)
