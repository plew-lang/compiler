#!/usr/bin/env python3
"""Build and check generation-scoped managed-memory disposal (macOS)."""
import argparse
import json
from pathlib import Path
import shlex
import subprocess
import sys
sys.dont_write_bytecode = True
from check import ROOT, HERE, digest, apply

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', required=True, type=Path)
    parser.add_argument('--runs', default=101, type=int)
    args = parser.parse_args()
    if args.runs < 1: parser.error('runs must be positive')
    out = args.out.resolve(); out.mkdir(parents=True, exist_ok=False)
    prefix = Path('/opt/homebrew/opt/llvm').resolve()
    apply()
    inputs = [ROOT / 'plewc', *sorted(HERE.glob('*.*')), *sorted((ROOT/'std').rglob('*.pw')),
              ROOT/'Plew.toml', ROOT/'Plew.lock', prefix/'bin/clang', prefix/'lib/libLLVM.dylib']
    hashes = {str(p): digest(p) for p in inputs if p.is_file()}
    report = dict(status='running', inputs=hashes, commands=[], runs=args.runs)
    def run(name, command):
        print('[region-check] '+name, flush=True)
        with (out/(name+'.stdout')).open('wb') as stdout, (out/(name+'.stderr')).open('wb') as stderr:
            status = subprocess.run([sys.executable, '-B', str(ROOT/'scripts/support/watch-command.py'),
                '--', *map(str, command)], cwd=ROOT, stdout=stdout, stderr=stderr).returncode
        report['commands'].append(dict(name=name, argv=list(map(str,command)), exit=status))
        if status: raise RuntimeError(f'{name} failed: {out/(name+".stderr")}')
        return (out/(name+'.stdout')).read_bytes()
    try:
        runtime = run('runtime', [ROOT/'plewc','--runtime'])
        normal = out/'normal-runtime.c'; normal.write_bytes(runtime)
        cache = b'static char* e=0;'
        if runtime.count(cache) != 1: raise RuntimeError('empty-string cache layout changed')
        runtime = runtime.replace(cache, cache + b'static unsigned long long epoch=0; if(epoch!=region_epoch){e=0;epoch=region_epoch;}')
        wrapped = out/'runtime.c' 
        wrapped.write_bytes((HERE/'region-prefix.c').read_bytes()+runtime+(HERE/'region-suffix.c').read_bytes())
        library = out/'runtime.dylib'
        run('runtime-build',[prefix/'bin/clang','-O2','-w','-dynamiclib',wrapped,'-o',library])
        ir = out/'app.ll'; ir.write_bytes(run('app',[ROOT/'plewc',HERE/'Region.pw']))
        aot = out/'aot'
        run('aot-build', [prefix/'bin/clang','-w','-O0',ir,normal,'-o',aot])
        if run('aot', [aot]) != b'\n1\n6\n7000012\n999\n6\n': raise RuntimeError('normal AOT oracle mismatch')
        flags = shlex.split(subprocess.check_output([prefix/'bin/llvm-config','--cxxflags'],text=True))
        host = out/'region'
        run('host',[prefix/'bin/clang++',*flags,'-O2',HERE/'region.cpp','-L'+str(prefix/'lib'),'-lLLVM','-o',host])
        result = run('lifecycle',[host,ir,library,args.runs])
        if result != b'\n1\n6\n7000012\n'*args.runs: raise RuntimeError('stale state or post-shutdown callback output')
        if any(digest(Path(p))!=sha for p,sha in hashes.items()): raise RuntimeError('inputs changed')
        report.update(status='passed',output_sha=__import__('hashlib').sha256(result).hexdigest())
        print(f'PASS {args.runs} suspended generations reclaimed')
        return 0
    except Exception as error:
        report.update(status='failed',error=str(error)); print(error,file=sys.stderr); return 1
    finally:
        (out/'results.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__': sys.exit(main())
