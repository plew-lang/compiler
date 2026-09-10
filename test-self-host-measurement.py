#!/usr/bin/env python3
"""Exercise real LLVM links, generation transitions and failure publication."""
import json
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path.cwd()
CONFIG = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')

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
        subprocess.run(['clang', '-S', '-emit-llvm', '-O0', str(path), '-o', str(work / (name + '.ll'))], check=True)

    def run(label, first, expected=0, generation=None, runtime='\n'):
        carrier = work / ('carrier-' + label)
        carrier.write_text('#!/usr/bin/env python3\nimport sys\nfrom pathlib import Path\nif sys.argv[1] == "--runtime":\n sys.stdout.write(' + repr(runtime) + ')\nelse:\n sys.stderr.write("[trace-phase] fixture:start\\n")\n sys.stdout.write(Path(' + repr(str(work / (first + '.ll'))) + ').read_text())\n sys.stderr.write("[trace-phase] fixture:done\\n")\n')
        carrier.chmod(0o755)
        output = work / label
        result = subprocess.run(['./measure-self-host.sh'], env={**os.environ, 'CARRIER': str(carrier), 'SOURCE': str(source / '_.pw'), 'OUT_DIR': str(output), 'LLVM_CONFIG': CONFIG}, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True)
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
        print('PASS', label, flush=True)

    compiler('stable', 'stable')
    compiler('transition', 'stable')
    compiler('cycle-a', 'cycle-b')
    compiler('cycle-b', 'cycle-a')
    compiler('runtime', 'runtime', runtime='// successor runtime')
    compiler('failure', 'failure', failure=23)
    compiler('unstable', 'unstable', nondeterministic=True)
    compiler('mutation', 'mutation', mutate=True)
    run('immediate', 'stable', generation=2)
    run('one-transition', 'transition', generation=3)
    run('no-convergence', 'cycle-a', expected=65)
    run('runtime-transition', 'runtime', generation=3)
    run('compiler-failure', 'failure', expected=23)
    run('repeat-mismatch', 'unstable', expected=65)
    run('input-mutation', 'mutation', expected=65)
    # Invalid LLVM must propagate clang's failure and never publish a time.
    (work / 'invalid.ll').write_text('invalid llvm\n')
    run('link-failure', 'invalid', expected=1)
