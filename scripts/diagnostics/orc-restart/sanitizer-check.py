#!/usr/bin/env python3
"""Instrument ORC host/runtime/JIT IR and validate sanitizer detection controls."""
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
sys.dont_write_bytecode = True
from check import ROOT, HERE, digest, apply

def main():
    import argparse
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out',required=True,type=Path)
    args=parser.parse_args(); out=args.out.resolve(); out.mkdir(parents=True,exist_ok=False)
    llvm=Path('/opt/homebrew/opt/llvm').resolve()
    clang=Path('/opt/homebrew/opt/llvm@22/bin/clang').resolve()
    apply(); os.environ['ASAN_OPTIONS']='detect_leaks=1:abort_on_error=0'
    inputs=[ROOT/'plewc',*sorted(HERE.glob('*.*')),*sorted((ROOT/'std').rglob('*.pw')),
            llvm/'lib/libLLVM.dylib',clang,ROOT/'tests/sanitizer/nonvolatile-unused-uaf.ll']
    hashes={str(p):digest(p) for p in inputs if p.is_file()}
    report=dict(status='running',inputs=hashes,commands=[],asan_options=os.environ['ASAN_OPTIONS'])
    watch=[sys.executable,'-B',str(ROOT/'scripts/support/watch-command.py'),'--']
    def run(name,command,expected=0,contains=None,input=None):
        print('[orc-sanitizer] '+name,flush=True)
        with (out/(name+'.stdout')).open('wb') as stdout,(out/(name+'.stderr')).open('wb') as stderr:
            status=subprocess.run(watch+list(map(str,command)),cwd=ROOT,stdout=stdout,stderr=stderr,input=input).returncode
        report['commands'].append(dict(name=name,argv=list(map(str,command)),exit=status))
        diagnostics=(out/(name+'.stderr')).read_text(errors='replace')
        if status!=expected or (contains and contains not in diagnostics):
            raise RuntimeError(f'{name}: exit {status}; inspect stderr')
        if not expected and ('ERROR: AddressSanitizer' in diagnostics or 'ERROR: LeakSanitizer' in diagnostics):
            raise RuntimeError(name+': sanitizer diagnostic')
        return (out/(name+'.stdout')).read_bytes()
    try:
        run('prepare',[sys.executable,'-B',HERE/'region-check.py','--runs','1','--out',out/'prepared'])
        library=out/'runtime.dylib'
        run('runtime',[clang,'-w','-O1','-g','-fsanitize=address','-dynamiclib',out/'prepared/runtime.c','-o',library])
        flags=shlex.split(subprocess.check_output([llvm/'bin/llvm-config','--cxxflags'],text=True))
        cxx=clang.parent/'clang++'
        def build(source,name):
            binary=out/name
            run('build-'+name,[cxx,*flags,'-O1','-g','-fno-omit-frame-pointer','-fsanitize=address',
                '-DORC_PROBE_ASAN',HERE/source,'-L'+str(llvm/'lib'),'-lLLVM','-o',binary])
            return binary
        runner=build('runner.cpp','runner')
        control=out/'uaf.ll'
        control.write_text((ROOT/'tests/sanitizer/nonvolatile-unused-uaf.ll').read_text().replace('@main()', '@main(i32 %argc, ptr %argv)'))
        run('uaf-control',[runner,control,library,'asan'],expected=1,contains='ERROR: AddressSanitizer: heap-use-after-free')
        leak=out/'leak.ll'
        leak.write_text('declare ptr @malloc(i64)\ndefine void @leak() noinline sanitize_address { %p = call ptr @malloc(i64 123) ret void }\ndefine i32 @main(i32 %argc, ptr %argv) sanitize_address { call void @leak() ret i32 0 }\n')
        run('leak-control',[runner,leak,library,'asan'],expected=1,contains='ERROR: LeakSanitizer: detected memory leaks')
        host=build('region.cpp','region')
        actual=run('region',[host,out/'prepared/app.ll',library,'101'])
        if actual != b'\n1\n6\n7000012\n'*101: raise RuntimeError('region output mismatch')
        restart=build('restart.cpp','restart')
        ir=out/'prepared/app.ll'
        commands=''
        expected='HOST_READY\n'
        for iteration in range(21):
            commands+=f'LOAD {ir} 0\n'
            expected+='\n1\n6\n7000012\nREADY 7000023\n'
        commands+=f'FAIL_READY {ir} 0\nPING\nLOAD {ir} 0\nQUIT\n'
        expected+='\n1\n6\n7000012\nINIT_FAILED\nINACTIVE\n\n1\n6\n7000012\nREADY 7000023\nSTOPPED\n'
        if run('restart',[restart,library],input=commands.encode()) != expected.encode():
            raise RuntimeError('restart output mismatch')
        if any(digest(Path(p))!=sha for p,sha in hashes.items()): raise RuntimeError('inputs changed')
        report['status']='passed'; print('PASS: JIT UAF/leak controls, 101 instrumented generations and restart recovery')
        return 0
    except Exception as error:
        report.update(status='failed',error=str(error)); print(error,file=sys.stderr); return 1
    finally: (out/'results.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__': sys.exit(main())
