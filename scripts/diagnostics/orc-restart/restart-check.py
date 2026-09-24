#!/usr/bin/env python3
"""Measure explicit source-to-ready restarts with a persistent ORC host."""
import argparse
import json
import math
import platform
from pathlib import Path
import shlex
import statistics
import subprocess
import sys
import time
sys.dont_write_bytecode = True
from check import ROOT, HERE, digest, apply
from source_variants import variant

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--runs', type=int, default=21)
    parser.add_argument('--scenario', choices=['body','mixed'], default='body')
    parser.add_argument('--functions', type=int, default=0)
    parser.add_argument('--expression-shape', choices=['flat','deep'], default='flat')
    args = parser.parse_args()
    if args.functions < 0: parser.error('functions must be nonnegative')
    if args.runs < 3: parser.error('runs must be >= 3')
    out = args.out.resolve(); out.mkdir(parents=True, exist_ok=False)
    prefix = Path('/opt/homebrew/opt/llvm').resolve(); apply()
    watch = [sys.executable, '-B', str(ROOT/'scripts/support/watch-command.py'), '--']
    inputs = [ROOT/'plewc', ROOT/'Plew.toml', ROOT/'Plew.lock', *sorted(HERE.glob('*.*')),
              *sorted((ROOT/'std').rglob('*.pw')), prefix/'lib/libLLVM.dylib', prefix/'bin/clang']
    hashes = {str(p):digest(p) for p in inputs if p.is_file()}
    report = dict(status='running', host=platform.platform(), inputs=hashes, samples=[], checks=[], commands=[],
                  scope='explicit source-to-ready, full compile, persistent ORC, diagnostic managed region',
                  scenario=args.scenario, extra_functions=args.functions, expression_shape=args.expression_shape)
    process = None
    def run(label, command, accepted=0):
        (out/'results.json').write_text(json.dumps(report,indent=2)+'\n')
        print('[restart-check] '+label,flush=True)
        with (out/(label+'.stdout')).open('wb') as stdout, (out/(label+'.stderr')).open('wb') as stderr:
            result = subprocess.run(watch+list(map(str,command)),cwd=ROOT,stdout=stdout,stderr=stderr)
        report['commands'].append(dict(label=label,argv=list(map(str,command)),exit=result.returncode))
        if (accepted == 0 and result.returncode) or (accepted != 0 and not result.returncode):
            raise RuntimeError(f'{label}: unexpected exit {result.returncode}')
        return (out/(label+'.stdout')).read_bytes()
    def exchange(command, terminal):
        process.stdin.write(command+'\n'); process.stdin.flush()
        lines=[]
        while True:
            line=process.stdout.readline()
            if not line: raise RuntimeError('restart host exited unexpectedly')
            lines.append(line)
            if any(line.startswith(value) for value in terminal): return ''.join(lines)
    try:
        run('region-build',[sys.executable,'-B',HERE/'region-check.py','--runs','1','--out',out/'region'])
        flags=shlex.split(subprocess.check_output([prefix/'bin/llvm-config','--cxxflags'],text=True))
        host=out/'restart'
        run('host-build',[prefix/'bin/clang++',*flags,'-O2',HERE/'restart.cpp','-L'+str(prefix/'lib'),'-lLLVM','-o',host])
        hosterr=(out/'host.stderr').open('w')
        process=subprocess.Popen(watch+[str(host),str(out/'region/runtime.dylib')],cwd=ROOT,
                                 stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=hosterr,text=True,bufsize=1)
        if process.stdout.readline()!='HOST_READY\n': raise RuntimeError('host startup failed')
        template=(HERE/'Region.pw').read_text()
        source=out/'App.pw'
        for revision in range(args.runs):
            # Saving happens before the request; nothing compiles on save.
            text, modules, kind=variant(template, revision, args.scenario, args.functions, args.expression_shape)
            for name, contents in modules.items(): (out/name).write_text(contents)
            source.write_text(text)
            start=time.perf_counter_ns()  # Explicit Restart request.
            ir=out/f'{revision}.ll'
            ir.write_bytes(run(f'compile-{revision}',[ROOT/'plewc',source]))
            compiled=time.perf_counter_ns()
            output=exchange(f'LOAD {ir} {revision}', ['READY ','REJECTED'])
            ready=time.perf_counter_ns()
            expected=f'\n1\n6\n{7000012+revision}\nREADY {7000023+revision}\n'
            if output!=expected: raise RuntimeError(f'generation {revision} output mismatch: {output!r}')
            report['samples'].append(dict(revision=revision,kind=kind,modules=modules,total_ms=(ready-start)/1e6,
                source_to_ir_ms=(compiled-start)/1e6,ir_to_ready_ms=(ready-compiled)/1e6,
                source_sha=digest(source),ir_sha=digest(ir),output=output))
            (out/f'{revision}.pw').write_text(text)
            print(f'[restart-check] ready {revision+1}/{args.runs}',flush=True)
        revision=args.runs-1
        source.write_text(template.replace('counter += 1I64', 'counter += \"invalid\"'))
        run('source-reject',[ROOT/'plewc',source],accepted=1)
        if exchange('PING',['PONG '])!=f'PONG {7000024+revision}\n':
            raise RuntimeError('source rejection disturbed old application')
        report['checks'].append('source rejection preserves active handler')
        bad=out/'bad.ll'; bad.write_text('not LLVM IR\n')
        if exchange(f'LOAD {bad} 0',['REJECTED'])!='REJECTED\n': raise RuntimeError('invalid IR accepted')
        if exchange('PING',['PONG '])!=f'PONG {7000025+revision}\n': raise RuntimeError('IR rejection lost old app')
        report['checks'].append('IR rejection preserves active handler')
        ir=out/f'{revision}.ll'
        failed=exchange(f'FAIL_READY {ir} {revision}',['INIT_FAILED'])
        if failed!=f'\n1\n6\n{7000012+revision}\nINIT_FAILED\n': raise RuntimeError('failure injection mismatch')
        if exchange('PING',['INACTIVE'])!='INACTIVE\n': raise RuntimeError('failed initialization still active')
        recovered=exchange(f'LOAD {ir} {revision}',['READY '])
        if recovered!=f'\n1\n6\n{7000012+revision}\nREADY {7000023+revision}\n': raise RuntimeError('recovery failed')
        report['checks'].append('host readiness failure clears environment and subsequent restart recovers')
        if exchange('QUIT',['STOPPED'])!='STOPPED\n': raise RuntimeError('shutdown mismatch')
        if process.wait(timeout=10): raise RuntimeError('host failed on shutdown')
        process=None; hosterr.close()
        # All AOT oracle work is outside the timed restart path.
        for revision in range(args.runs):
            binary=out/f'aot-{revision}'
            run(f'aot-build-{revision}',[prefix/'bin/clang','-w','-O0',out/f'{revision}.ll',out/'region/normal-runtime.c','-o',binary])
            expected=f'\n1\n6\n{7000012+revision}\n999\n6\n'.encode()
            if run(f'aot-{revision}',[binary])!=expected: raise RuntimeError('AOT oracle mismatch')
        if any(digest(Path(p))!=sha for p,sha in hashes.items()): raise RuntimeError('inputs changed')
        warm=sorted(s['total_ms'] for s in report['samples'][1:])
        report.update(status='passed',median_ms=statistics.median(warm),p95_ms=warm[math.ceil(.95*len(warm))-1],
                      max_ms=max(warm),over_500ms=sum(x>500 for x in warm),first_ms=report['samples'][0]['total_ms'])
        print(f'PASS median={report["median_ms"]:.3f} p95={report["p95_ms"]:.3f} max={report["max_ms"]:.3f} ms, over500={report["over_500ms"]}')
        return 0
    except Exception as error:
        report.update(status='failed',error=str(error)); print(error,file=sys.stderr); return 1
    finally:
        if process is not None and process.poll() is None:
            try:
                process.stdin.write('QUIT\n'); process.stdin.flush(); process.communicate(timeout=10)
            except Exception:
                process.terminate(); process.communicate(timeout=10)
        (out/'results.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__': sys.exit(main())
