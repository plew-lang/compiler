#!/usr/bin/env python3
"""Exercise real LLVM links, generation transitions and failure publication."""
import json
import os
from pathlib import Path
import shutil
import sys
import subprocess
import tempfile

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "scripts/support"))
import clang_environment
import llvm_link
clang_environment.apply()
CONFIG = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
CLANG = str(Path(subprocess.check_output([CONFIG, '--bindir'], text=True).strip()) / 'clang')

with tempfile.TemporaryDirectory(prefix='plew-self-host-') as temporary:
    work = Path(temporary)
    source = work / 'source'
    source.mkdir()
    (source / '_.pw').write_text('fn main() {}\n')
    # Each linked compiler emits the exact stored LLVM of its successor.
    # This makes both convergence and a cycle explicit, without a real self-host.
    def compiler(name, successor, runtime='', failure=0, nondeterministic=False, mutate=False):
        code = '''#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
 if (argc > 1 && strcmp(argv[1], "--runtime") == 0) { puts(RUNTIME); return 0; }
 fprintf(stderr, "[trace-phase] fixture:start\\n");
 if (FAILURE) return FAILURE;
 MUTATION
 FILE *f = fopen(SUCCESSOR, "r"); if (!f) return 90;
 int c; while ((c = fgetc(f)) != EOF) putchar(c); fclose(f);
 NONDETERMINISM
 fprintf(stderr, "[trace-phase] fixture:done\\n"); return 0;
}
'''.replace('RUNTIME', json.dumps(runtime)).replace('FAILURE', str(failure)).replace('SUCCESSOR', json.dumps(str(work / (successor + '.ll'))))
        marker = work / (name + '.seen')
        code = code.replace('NONDETERMINISM', f'FILE *m = fopen({json.dumps(str(marker))}, "r"); if (m) {{ fclose(m); puts("; changed"); }} else {{ m = fopen({json.dumps(str(marker))}, "w"); fclose(m); }}' if nondeterministic else '')
        code = code.replace('MUTATION', f'FILE *m = fopen({json.dumps(str(source / "_.pw"))}, "a"); fputs("// changed\\n", m); fclose(m);' if mutate else '')
        path = work / (name + '.c')
        path.write_text(code)
        subprocess.run([CLANG, '-S', '-emit-llvm', '-O0', str(path), '-o', str(work / (name + '.ll'))], check=True)

    def run(label, first, expected=0, generation=None, runtime='\n'):
        carrier = work / ('carrier-' + label)
        carrier.write_text('#!/usr/bin/env python3\nimport sys\nfrom pathlib import Path\nif sys.argv[1] == "--runtime":\n sys.stdout.write(' + repr(runtime) + ')\nelse:\n sys.stderr.write("[trace-phase] fixture:start\\n")\n sys.stdout.write(Path(' + repr(str(work / (first + '.ll'))) + ').read_text())\n sys.stderr.write("[trace-phase] fixture:done\\n")\n')
        carrier.chmod(0o755)
        output = work / label
        result = subprocess.run(['./scripts/diagnostics/measure-self-host.sh'], env={**os.environ, 'CARRIER': str(carrier), 'SOURCE': str(source / '_.pw'), 'OUT_DIR': str(output), 'LLVM_CONFIG': CONFIG}, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True)
        assert result.returncode == expected, (label, result.returncode, result.stderr)
        state = json.loads((output / 'summary.json').read_text())
        summary = (output / 'summary.txt').read_text()
        if expected:
            assert state['status'] == 'failed' and 'self_compile_median_seconds=' not in summary, state
        else:
            assert state['fixed_point_generation'] == generation, state
            assert len(state['measurements']) == 3, state
            assert len({r['compiler_sha256'] for r in state['measurements']}) == 1, state
            assert 'self_compile_median_seconds=' in summary
            assert '-fdebug-pass-manager' in state['link_command'], state
            bindir = Path(subprocess.check_output([CONFIG, '--bindir'], text=True).strip())
            assert Path(state['link_command'][0]) == bindir / 'clang', state
            expected_opt = shutil.which(os.environ['LLVM_OPT']) if os.environ.get('LLVM_OPT') else str(bindir / 'opt')
            assert Path(state['optimization_command'][0]) == Path(expected_opt), state
            assert state['clang_environment'] == clang_environment.settings(), state
            assert '-passes=cgscc(function(sroa,early-cse,instcombine<verify-fixpoint;max-iterations=8>),argpromotion),default<O1>' in state['optimization_command'], state
            assert state['optimizer_version'], state
            for row in state['generations']:
                if 'successor' in row:
                    link_log = output / row['artifact'] / 'link.log'
                    assert link_log.is_file() and 'Running pass:' in link_log.read_text(), link_log
                    opt_log = link_log.with_name('link.opt.log')
                    assert opt_log.is_file() and 'Running pass:' in opt_log.read_text(), opt_log
                    assert link_log.with_name('link.optimized.ll').is_file()
        print('PASS', label, flush=True)
        print('[trace-phase] self-host-test:' + label + ':done', file=sys.stderr, flush=True)

    compiler('stable', 'stable')
    compiler('transition', 'stable')
    compiler('cycle-a', 'cycle-b')
    compiler('cycle-b', 'cycle-a')
    compiler('runtime', 'runtime', runtime='// successor runtime')
    compiler('failure', 'failure', failure=23)
    compiler('unstable', 'unstable', nondeterministic=True)
    compiler('mutation', 'mutation', mutate=True)
    run('immediate', 'stable', generation=2)
    override = work / 'opt-override'
    override.symlink_to(shutil.which(os.environ.get('LLVM_OPT', str(Path(CLANG).with_name('opt')))))
    saved_opt = os.environ.get('LLVM_OPT')
    os.environ['LLVM_OPT'] = str(override)
    run('optimizer-override', 'stable', generation=2)
    if saved_opt is None:
        del os.environ['LLVM_OPT']
    else:
        os.environ['LLVM_OPT'] = saved_opt
    run('one-transition', 'transition', generation=3)
    run('no-convergence', 'cycle-a', expected=65)
    run('runtime-transition', 'runtime', generation=3)
    run('compiler-failure', 'failure', expected=23)
    run('repeat-mismatch', 'unstable', expected=65)
    run('input-mutation', 'mutation', expected=65)
    # Invalid LLVM must propagate clang's failure and never publish a time.
    (work / 'invalid.ll').write_text('invalid llvm\n')
    run('link-failure', 'invalid', expected=1)

    # The caller must be simplified after the callee's signature is promoted.
    # A module-wide cleanup before argpromotion leaves delegate's outer byval.
    nested = work / 'nested-delegate.ll'
    nested.write_text("""%Inner = type { i64, i64, i64, i64 }
%Outer = type { i64, %Inner, i64 }
define internal i64 @leaf(ptr byval(%Inner) %input) noinline {
  %field = getelementptr %Inner, ptr %input, i32 0, i32 2
  %value = load i64, ptr %field
  ret i64 %value
}
define internal i64 @delegate(ptr byval(%Outer) %input) noinline {
  %slot = alloca %Inner
  %whole = load %Outer, ptr %input
  %inner = extractvalue %Outer %whole, 1
  store %Inner %inner, ptr %slot
  %value = call i64 @leaf(ptr byval(%Inner) %slot)
  ret i64 %value
}
define i64 @entry(ptr %input) {
  %value = call i64 @delegate(ptr byval(%Outer) %input)
  ret i64 %value
}
""")
    optimized = work / 'nested-delegate.optimized.ll'
    with (work / 'nested-delegate.opt.log').open('wb') as log:
        subprocess.run(llvm_link.optimization_command(CONFIG, nested, optimized),
                       stderr=log, check=True)
    signatures = [line for line in optimized.read_text().splitlines() if line.startswith('define ')]
    assert all('%Outer' not in line and '%Inner' not in line for line in signatures), signatures
    driver = work / 'nested-delegate.c'
    driver.write_text('#include <stdint.h>\n'
                      'struct Inner { int64_t a,b,c,d; };\n'
                      'struct Outer { int64_t head; struct Inner inner; int64_t tail; };\n'
                      'extern int64_t entry(struct Outer *);\n'
                      'int main(void) { struct Outer value={1,{2,3,7,5},6}; '
                      'return entry(&value)==7 ? 0 : 1; }\n')
    executable = work / 'nested-delegate'
    subprocess.run([CLANG, '-w', '-O2', str(optimized), str(driver), '-o', str(executable)], check=True)
    subprocess.run([str(executable)], check=True)
    print('PASS nested-delegate', flush=True)
    print('[trace-phase] self-host-test:nested-delegate:done', file=sys.stderr, flush=True)
