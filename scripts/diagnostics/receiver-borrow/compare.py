#!/usr/bin/env python3
"""Manual, bounded receiver lowering experiment; NOT a borrow checker or gate."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import statistics
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment
import llvm_link

CASES = {'root': 'item', 'field': 'holder.item', 'index': 'items[0U64]', 'ref': 'reference->', 'ref_parameter': 'reference->'}


def source(case, mode):
    target = CASES[case]
    access = target if case in ['ref', 'ref_parameter'] else target + '.'
    call = (access + 'inspect(extra: probeStep(iteration))' if mode == 'late'
            else access + 'inspectEarly(iteration: iteration)')
    setup = {
        'root': 'val item = <Item value=7I64 data=[11I64, 12I64, 13I64] />',
        'field': 'val holder = <Holder item=<Item value=7I64 data=[11I64, 12I64, 13I64] /> />',
        'index': 'val items: Array[Item] = [<Item value=7I64 data=[11I64, 12I64, 13I64] />]',
        'ref': 'val reference = <MutableRef value=<Item value=7I64 data=[11I64, 12I64, 13I64] /> />',
        'ref_parameter': 'val reference = <MutableRef value=<Item value=7I64 data=[11I64, 12I64, 13I64] /> />',
    }[case]
    helper = ''
    if case == 'ref_parameter':
        helper = 'fn inspectReference(reference: MutableRef[Item], iteration: I64) -> I64 { return ' + call + ' }'
        call = 'inspectReference(reference: reference, iteration: iteration)'
    return '''import @Std/Io with { print }
import @Std/Core with { MutableRef }
extern(c) {
    fn probeStep(iteration~: I64) -> I64
    fn probeLimit() -> I64
    fn probeBegin() -> I64
    fn probeReport() -> I64
}
struct Item { pub val value: I64 pub val data: Array[I64] }
pub impl Item {
    factory
    fn inspect(extra: I64) -> I64 { return self.value + self.data[0U64] + extra }
    // Borrowed self is bound before the opaque, receiver-disjoint step.
    // This models placement of a borrow, not checking arbitrary early borrows.
    fn inspectEarly(iteration: I64) -> I64 {
        return self.inspect(extra: probeStep(iteration))
    }
}
struct Holder { pub val item: Item }
pub impl Holder { factory }
HELPER
fn main() {
    SETUP
    val limit = probeLimit()
    probeBegin()
    mut val iteration: I64 = 0I64
    mut val checksum: I64 = 0I64
    while iteration < limit {
        checksum += CALL
        iteration += 1I64
    }
    probeReport()
    print(checksum)
}
'''.replace('HELPER', helper).replace('SETUP', setup).replace('CALL', call)


SUPPORT = '''#include <stdlib.h>
#include <stdio.h>
#include <time.h>
static struct timespec started;
void probeClockStart(void) { clock_gettime(CLOCK_MONOTONIC, &started); }
void probeClockStop(void) { struct timespec ended; clock_gettime(CLOCK_MONOTONIC, &ended); fprintf(stderr, "SECONDS %.9f\\n", (ended.tv_sec-started.tv_sec)+(ended.tv_nsec-started.tv_nsec)*1e-9); }
static volatile long long observed;
long long probeLimit(void) { const char *s=getenv("PROBE_ITERATIONS"); return s ? atoll(s) : 1000000; }
__attribute__((noinline)) long long probeStep(long long i) { observed = i & 7; return observed; }
'''


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, default=ROOT/'plewc')
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--iterations', type=int, default=20000000)
    parser.add_argument('--runs', type=int, default=7)
    parser.add_argument('--cases', nargs='+', choices=CASES, default=list(CASES))
    args = parser.parse_args()
    if args.iterations < 1 or args.runs < 3:
        parser.error('positive iterations and at least three measured runs required')
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    clang_environment.apply()
    env = os.environ.copy()
    env['PYTHONDONTWRITEBYTECODE'] = '1'
    config = env.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
    compiler = args.compiler.resolve()
    inputs = {str(p): digest(p) for p in [compiler, Path(__file__), ROOT/'Plew.lock', *sorted((ROOT/'scripts/support').glob('*.py')), *sorted((ROOT/'std').rglob('*.pw'))]}
    watch = [sys.executable, str(ROOT/'scripts/support/watch-command.py'), '--']

    def command(argv, prefix, environment=env):
        with prefix.with_suffix('.stdout').open('wb') as stdout, prefix.with_suffix('.stderr').open('wb') as stderr:
            start = time.monotonic()
            result = subprocess.run(watch + list(map(str, argv)), cwd=ROOT, env=environment,
                                    stdout=stdout, stderr=stderr)
            elapsed = time.monotonic() - start
        if result.returncode:
            raise RuntimeError(f'{argv[0]} failed ({result.returncode}); see {prefix}.stderr')
        return elapsed

    command([compiler, '--runtime'], out/'runtime-emit')
    runtime = (out/'runtime-emit.stdout').read_text()
    (out/'runtime.c').write_text(runtime + '\nextern void probeClockStart(void); extern void probeClockStop(void);\nlong long probeBegin(void){probeClockStart();return 0;}\nlong long probeReport(void){probeClockStop();return 0;}\n')
    instrumented = 'static unsigned long long probeRetains, probeReleases;\n' + runtime
    for signature, counter in [('void plew_rawbuf_retain(void* p){', 'probeRetains'),
                               ('long long plew_rawbuf_release(void* p){', 'probeReleases'),
                               ('void plew_rawbuf_drop(void* p){', 'probeReleases')]:
        if instrumented.count(signature) != 1:
            raise RuntimeError('runtime instrumentation signature changed')
        instrumented = instrumented.replace(signature, signature + f'if(p) {counter}++;', 1)
    instrumented += '\nextern void probeClockStart(void); extern void probeClockStop(void);\nlong long probeBegin(void){probeRetains=probeReleases=0;probeClockStart();return 0;}\nlong long probeReport(void){probeClockStop();fprintf(stderr,"ARC %llu %llu\\n",probeRetains,probeReleases);return 0;}\n'
    (out/'runtime-counted.c').write_text(instrumented)
    (out/'support.c').write_text(SUPPORT)
    report = {'scope': 'source-level early-borrow lowering model; no general safety checker',
              'inputs': inputs, 'iterations': args.iterations, 'runs': args.runs,
              'pipeline': llvm_link.PIPELINE, 'toolchain': subprocess.check_output([config,'--version'], text=True).strip(),
              'builds': [], 'samples': [], 'counts': [], 'medians': {}}
    for case in args.cases:
        for mode in ['late', 'early']:
            stem = f'{case}-{mode}'
            pw = out/(stem+'.pw')
            pw.write_text(source(case, mode))
            elapsed = command([compiler, '--trace-phases', pw], out/(stem+'-compile'))
            raw = out/(stem+'.ll')
            raw.write_bytes((out/(stem+'-compile.stdout')).read_bytes())
            for counted in [False, True]:
                suffix = '-counted' if counted else ''
                runtime_path = out/('runtime-counted.c' if counted else 'runtime.c')
                command([sys.executable, ROOT/'scripts/support/llvm_link.py', '--config', config,
                         '--log-prefix', out/(stem+suffix+'-link'), '--llvm', raw,
                         '--runtime', runtime_path, '--output', out/(stem+suffix), '--', out/'support.c'],
                        out/(stem+suffix+'-build'))
            report['builds'].append({'case':case,'mode':mode,'diagnostic_compile_seconds':elapsed,
                                     'source_sha256':digest(pw),'llvm_sha256':digest(raw)})
            print(f'built {stem}', flush=True)
        # Alternating order, one warmup per binary, unchanged C/runtime inputs.
        for iteration in range(args.runs+1):
            for mode in (['late','early'] if iteration%2 == 0 else ['early','late']):
                label = f'{case}-{mode}'
                runenv = dict(env, PROBE_ITERATIONS=str(args.iterations))
                prefix = out/f'{label}-run-{iteration}'
                wall = command([out/label], prefix, runenv)
                timing = [line for line in prefix.with_suffix('.stderr').read_text().splitlines() if line.startswith('SECONDS ')]
                if len(timing) != 1: raise RuntimeError('missing loop timing')
                elapsed = float(timing[0].split()[1])
                actual = prefix.with_suffix('.stdout').read_text().strip()
                n = args.iterations
                expected = str(n*18 + (n//8)*28 + sum(range(n%8)))
                if actual != expected:
                    raise RuntimeError(f'wrong result: {label}: {actual} != {expected}')
                report['samples'].append({'case':case,'mode':mode,'iteration':iteration,'seconds':elapsed,'process_seconds':wall,'checksum':actual})
            print(f'completed {case} pair {iteration}/{args.runs}', flush=True)
        for mode in ['late','early']:
            label = f'{case}-{mode}'
            command([out/(label+'-counted')], out/(label+'-arc'), dict(env, PROBE_ITERATIONS='10000'))
            lines = (out/(label+'-arc.stderr')).read_text().splitlines()
            arc = [line for line in lines if line.startswith('ARC ')]
            if len(arc) != 1:
                raise RuntimeError('missing ARC count')
            report['counts'].append({'case':case,'mode':mode,'iterations':10000,'arc':arc[0]})
            report['medians'][label] = statistics.median(r['seconds'] for r in report['samples']
                                                        if r['case']==case and r['mode']==mode and r['iteration']>0)
    if any(digest(Path(p)) != sha for p,sha in inputs.items()):
        raise RuntimeError('inputs changed during experiment')
    report['inputs_unchanged'] = True
    (out/'results.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({'medians':report['medians'],'counts':report['counts'],'result':str(out/'results.json')},indent=2), flush=True)

if __name__ == '__main__':
    main()
